//==================================================================================================
//
// AstarViz v.1 - To visualize the workings of the A* graph search algorithm.
//
// Copyright (C) 2008  Leo Vandriel  (mail@leovandriel.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//==================================================================================================

//==================================================================================================
//
// 'Search.h' - About arbitrary graph search.
//
// Various implementations of the A* algorithm to search a graph using some path measure:
// - 'Breadth' expand nodes FIFO style ( queue, std slow ).
// - 'Depth' expand nodes LIFO style ( stack ).
// - 'Nearest' expand node with smallest heuristic ( queue, std slow ).
// - 'A*Heap' A* using a slow heap sort ( vector heap, std slow ).
// - 'A*List' A* using an optimized linked list ( linked list ).
//
//==================================================================================================

#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <vector>
#include <queue>

/**
 * 'ESearchAlgorithm', the type of search method.
 */
enum ESearchAlgorithm
{
	None = 0,
	BreadthFirst,
	DepthFirst,
	NearestFirst,
	AstarHeap,
	AstarList
};

/**
* 'PathQuery', implicitly specifies a path.
*/
template<class NodeT>
struct PathQuery
{
	/**
	 * 'start', path start node.
	 */
	NodeT * start;

	/**
	* 'end', path end node.
	*/
	NodeT * end;

	/**
	* 'optimality', path optimality ( <=1.0 : optimal ).
	* If set >1.0 the path might be suboptimal, but search proceeds faster.
	*/
	float optimality;

	PathQuery(): start( 0 ), end( 0 ), optimality( -1.f ){}
};

/**
* 'SearchSpec', records search algorithm specs.
*/
struct SearchSpec
{
	/**
	 * 'nodeExpand', the number of nodes that have been visited by the search algorithm.
	 */
	int nodeExpand;

	/**
	 * 'succExpand', the number of iterations in the most inner loop of the search algorithm.
	 */
	int succExpand;

	/**
	 * 'found', indicates whether a path exists.
	 */
	bool found;

	/**
	 * 'searchTime', the amount of seconds the whole search operation took.
	 */
	float searchTime;

	SearchSpec(): nodeExpand( 0L ), found( false ), searchTime( 0.f ), succExpand( 0L ){}
};

/**
* 'PathSpec', explicitly specifies a path.
*/
template<class NodeT>
struct PathSpec
{
	/**
	 * 'estLength', path length according to the search heuristic.
	 */
	float estLength;

	/**
	 * 'pathSequence', sequence of nodes representing a path from 'start' to 'end'.
	 */
	std::vector<NodeT*> pathSequence;

	PathSpec(): estLength( 0.f ){}
};

/**
* 'compateEstimate', used for std sorting routines.
*/
template<class NodeT>
bool compateEstimate ( NodeT* inA, NodeT* inB ){ return inA->estimate > inB->estimate; }

/**
* 'Pathfinder', for finding a path in a search graph.
*/
template<class NodeT, class EdgeT>
class Pathfinder
{

private:

	/**
	 * 'guid', to identify nodes as being visited/unvisited without running a clearing pass over allistIter nodes.
	 */
	int guid;

public:

	Pathfinder() : guid( 0 ) {}

	PathQuery<NodeT> pathQuery;
	SearchSpec searchSpec;
	PathSpec<NodeT> pathSpec;

	/**
	 * 'openId', GUID indicating "openness".
	 */
	int openId;

	/**
	 * 'closeId', GUID indicating "closedness".
	 */
	int closeId;

	/**
	 * 'Search( .. )', core search algorithm routine.
	 */
	void Search( ESearchAlgorithm inAlgorithm );
};

template<class NodeT, class EdgeT>
void Pathfinder<NodeT, EdgeT>::Search( ESearchAlgorithm inAlgorithm )
{
	LARGE_INTEGER timeStart, timeEnd, timeFrequency;
	QueryPerformanceCounter( &timeStart );

	openId = guid++;
	closeId = guid++;

	pathQuery.start->stateId = openId;
	pathQuery.start->heuristic = pathQuery.optimality * pathQuery.start->GetHeuristic( pathQuery.end );
	pathQuery.start->estimate = pathQuery.start->heuristic;
	pathQuery.start->pathPrev = 0;

	switch( inAlgorithm )
	{

	//----------------------------------------------------------------------------------------------
	// BreadthFirst
	//----------------------------------------------------------------------------------------------

	case BreadthFirst:
		{
			// Use queue to keep track of open nodes
			std::queue<NodeT*> Q;
			Q.push( pathQuery.start );

			while( !Q.empty() )
			{
				NodeT* const listHead = Q.front(); Q.pop();
				listHead->stateId = closeId;

				if( listHead != pathQuery.end )
				{
					for( std::vector<EdgeT>::iterator edgeIter = listHead->successors.begin(); edgeIter != listHead->successors.end(); edgeIter++ )
					{
						NodeT* const succIter = edgeIter->node;
						if( succIter->stateId != openId && succIter->stateId != closeId )
						{
							succIter->stateId = openId;
							succIter->heuristic = pathQuery.optimality * succIter->GetHeuristic( pathQuery.end );
							succIter->estimate = listHead->estimate + ( succIter->heuristic - listHead->heuristic ) + edgeIter->weight;
							succIter->pathPrev = listHead;
							Q.push( succIter );
						}
						searchSpec.succExpand++;
					}
					searchSpec.nodeExpand++;
				}
				else
				{
					break;
				}
			}
		}
		break;

	//----------------------------------------------------------------------------------------------
	// DepthFirst
	//----------------------------------------------------------------------------------------------

	case DepthFirst:
		{
			std::stack<NodeT*> S;
			S.push( pathQuery.start );

			while( !S.empty() )
			{
				NodeT* const listHead = S.top(); S.pop();
				listHead->stateId = closeId;

				if( listHead != pathQuery.end )
				{
					std::priority_queue<std::pair<float, NodeT*>> P;

					for( std::vector<EdgeT>::iterator edgeIter = listHead->successors.begin(); edgeIter != listHead->successors.end(); edgeIter++ )
					{
						NodeT* const succIter = edgeIter->node;
						if( succIter->stateId != openId && succIter->stateId != closeId )
						{
							succIter->stateId = openId;
							succIter->heuristic = pathQuery.optimality * succIter->GetHeuristic( pathQuery.end );
							succIter->estimate = listHead->estimate + ( succIter->heuristic - listHead->heuristic ) + edgeIter->weight;
							succIter->pathPrev = listHead;
							P.push( std::make_pair( succIter->GetHeuristic( pathQuery.end ), succIter ) );
						}
						searchSpec.succExpand++;
					}
					searchSpec.nodeExpand++;

					while( !P.empty() )
					{
						S.push( P.top().second ); P.pop();
					}
				}
				else
				{
					break;
				}
			}
		}
		break;

	//----------------------------------------------------------------------------------------------
	// NearestFirst
	//----------------------------------------------------------------------------------------------

	case NearestFirst:
		{
			std::priority_queue<std::pair<float, NodeT*>> Q;
			Q.push( std::make_pair( -pathQuery.start->heuristic, pathQuery.start ) );

			while( !Q.empty() )
			{
				NodeT* const listHead = Q.top().second; Q.pop();
				listHead->stateId = closeId;

				if( listHead != pathQuery.end )
				{
					for( std::vector<EdgeT>::iterator edgeIter = listHead->successors.begin(); edgeIter != listHead->successors.end(); edgeIter++ )
					{
						NodeT* const succIter = edgeIter->node;
						if( succIter->stateId != openId && succIter->stateId != closeId )
						{
							succIter->stateId = openId;
							succIter->heuristic = pathQuery.optimality * succIter->GetHeuristic( pathQuery.end );
							succIter->estimate = listHead->estimate + ( succIter->heuristic - listHead->heuristic ) + edgeIter->weight;
							succIter->pathPrev = listHead;
							Q.push( std::make_pair( -succIter->heuristic - edgeIter->weight, succIter ) );
						}
						searchSpec.succExpand++;
					}
					searchSpec.nodeExpand++;
				}
				else
				{
					break;
				}
			}
		}
		break;

	//----------------------------------------------------------------------------------------------
	// AstarHeap
	//----------------------------------------------------------------------------------------------

	case AstarHeap:
		{
			std::vector<NodeT*> V;
			V.push_back( pathQuery.start );	make_heap( V.begin(), V.end(), compateEstimate<NodeT> );

			while( !V.empty() )
			{
				NodeT* const listHead = V.front();pop_heap( V.begin(), V.end(), compateEstimate<NodeT> ); V.pop_back();
				listHead->stateId = closeId;
				if( listHead != pathQuery.end )
				{
					for( std::vector<EdgeT>::iterator edgeIter = listHead->successors.begin(); edgeIter != listHead->successors.end(); edgeIter++ )
					{
						NodeT* const succIter = edgeIter->node;
						if( succIter->stateId != openId && succIter->stateId != closeId )
						{
							succIter->stateId = openId;
							succIter->heuristic = pathQuery.optimality * succIter->GetHeuristic( pathQuery.end );
							succIter->estimate = listHead->estimate + ( succIter->heuristic - listHead->heuristic ) + edgeIter->weight;
							succIter->pathPrev = listHead;
							V.push_back( succIter );push_heap( V.begin(), V.end(), compateEstimate<NodeT> );
						}
						else if( succIter->stateId == openId
							&& succIter->estimate > listHead->estimate + ( succIter->heuristic - listHead->heuristic ) + edgeIter->weight )
						{
							succIter->estimate = listHead->estimate + ( succIter->heuristic - listHead->heuristic ) + edgeIter->weight;
							succIter->pathPrev = listHead;
							make_heap( V.begin(), V.end(), compateEstimate<NodeT> );
						}
						searchSpec.succExpand++;
					}
					searchSpec.nodeExpand++;
				}
				else
				{
					break;
				}
			}
		}
		break;

	//----------------------------------------------------------------------------------------------
	// AstarList
	//----------------------------------------------------------------------------------------------

	case AstarList:
		{
			// prep doubly linked list
			NodeT nullNode = NodeT();
			NodeT* const listTail = &nullNode;
			pathQuery.start->listPrev = listTail;
			listTail->listNext = pathQuery.start;

			// both 'listTail' and 'listHead' are not included in the sorted open linked list
			for( NodeT* listHead = pathQuery.start; listHead != listTail; listHead = listHead->listPrev )
			{
				listHead->stateId = closeId;
				if( listHead != pathQuery.end )
				{
					for( std::vector<EdgeT>::iterator edgeIter = listHead->successors.begin(); edgeIter != listHead->successors.end(); edgeIter++ )
					{
						NodeT* const succIter = edgeIter->node;
						if( succIter->stateId != openId && succIter->stateId != closeId )
						{
							// reset estimate and previous
							succIter->stateId = openId;
							succIter->heuristic = pathQuery.optimality * succIter->GetHeuristic( pathQuery.end );
							succIter->estimate = listHead->estimate + ( succIter->heuristic - listHead->heuristic ) + edgeIter->weight;
							succIter->pathPrev = listHead;

							// add to sorted open list
							// best guess for starting linear search is at 'listHead' and go backwards
							// ( 'succIter' will probably be one of the better ones on the open list )
							NodeT* listIter = listHead;
							while( succIter->estimate >= listIter->listPrev->estimate && listIter->listPrev != listTail )
							{
								listIter = listIter->listPrev;
							}
							succIter->listPrev = listIter->listPrev;
							succIter->listNext = listIter;
							listIter->listPrev->listNext = succIter;
							listIter->listPrev = succIter;
						}
						else if( succIter->stateId == openId
							&& succIter->estimate > listHead->estimate + ( succIter->heuristic - listHead->heuristic ) + edgeIter->weight )
						{
							// reset estimate and previous
							succIter->estimate = listHead->estimate + ( succIter->heuristic - listHead->heuristic ) + edgeIter->weight;
							succIter->pathPrev = listHead;

							// remove from open list (ah, that's easy)
							succIter->listNext->listPrev = succIter->listPrev;
							succIter->listPrev->listNext = succIter->listNext;

							// add to sorted open list
							// best node to start looking would be the location 'succIter' was removed from and go forward
							// ( 'succIter' probably improved a bit and surely did not become worse )
							NodeT* listIter = succIter->listPrev;
							while( succIter->estimate <= listIter->listNext->estimate && listIter->listNext != listHead)
							{
								listIter = listIter->listNext;
							}
							succIter->listNext = listIter->listNext;
							succIter->listPrev = listIter;
							listIter->listNext->listPrev = succIter;
							listIter->listNext = succIter;
						}
						searchSpec.succExpand++;
					}
					searchSpec.nodeExpand++;
				}
				else
				{
					break;
				}
			}
		}
		break;

	}

	searchSpec.found = ( pathQuery.end->stateId == closeId );

	if( searchSpec.found )
	{
		pathSpec.estLength = pathQuery.end->estimate;

		// construct path

		pathQuery.end->pathNext = 0;

		for( NodeT* n = pathQuery.end, * m = pathQuery.end->pathPrev; m; n = m, m = m->pathPrev )
		{
			m->pathNext = n;
			if( m == pathQuery.start )
			{
				break;
			}
		}

		for( NodeT* n = pathQuery.start; n; n = n->pathNext )
		{
			pathSpec.pathSequence.push_back( n );
		}
	}

	QueryPerformanceCounter( &timeEnd );
	QueryPerformanceFrequency( &timeFrequency );

	searchSpec.searchTime = ( float )( ( double )( timeEnd.QuadPart-timeStart.QuadPart )
		/ ( double )( timeFrequency.QuadPart ) );

}

#endif

