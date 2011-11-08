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
// 'Canvas.h' - About canvas drawing and modification.
//
// Main functionality dealing with UI and program flow.
//
//==================================================================================================

#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <wx/wx.h>
#include <stack>
#include "Search.h"
#include "AstarVizFrameBase.h"

#define NODE_DRAW_RADIUS 2
#define MOUSE_DRAW_RADIUS 4

#define COLOR_BG      0xFF, 0xFF, 0xFF
#define COLOR_EDGE    0xBF, 0xBF, 0xBF
#define COLOR_NODE    0x5F, 0x5F, 0x5F

#define COLOR_START   0x00, 0xFF, 0x00
#define COLOR_END     0xFF, 0x00, 0x00
#define COLOR_MOUSE   0xFF, 0xFF, 0x00

#define COLOR_OPEN    0xFF, 0x00, 0x7F
#define COLOR_CLOSED  0x00, 0x7F, 0xFF
#define COLOR_PATH    0xFF, 0x7F, 0x00

#define CANVAS_WIDTH   01.00f
#define CANVAS_HEIGHT  01.00f

/**
 * 'Point', a location in 2D space ( [0, 1] x [0, 1] ).
 */
struct Point
{
	float x, y;

	Point() : x( 0 ), y( 0 ) {}

	Point( float inX, float inY ) : x( inX ), y( inY ) {}

	Point operator + ( const Point& inPoint ) const
	{
		return Point( x + inPoint.x, y + inPoint.y );
	}

	Point operator - ( const Point& inPoint ) const
	{
		return Point( x - inPoint.x, y - inPoint.y );
	}

	float operator | ( const Point& inPoint ) const
	{
		return x * inPoint.x + y * inPoint.y;
	}

	bool operator == ( const Point& inPoint ) const
	{
		return x == inPoint.x && y == inPoint.y;
	}

	float size() const
	{
		return sqrt( x * x + y * y );
	}
};

/**
 * 'Node', a node in a 2D search graph. Uses euclidian measure.
 */
struct Node
{
	Point pos;

	std::vector<struct Edge> successors;
	float estimate, heuristic;
	int stateId;
	Node* pathPrev, * pathNext;
	Node* listPrev, * listNext;

	float GetHeuristic( const Node* const inNode ) const
	{
		return ( inNode->pos - pos ).size();
	}

	bool operator < ( const Node& inNode ) const
	{
		return pos.x < inNode.pos.x;
	}
};

/**
* 'Edge', an edge that connects two nodes ( directional ).
*/
struct Edge
{
	Node *node;
	float weight;

	Edge(): node( 0 ), weight( 0.f ) {}
	Edge( Node *inNode, float inWeight ): node( inNode ), weight( inWeight ) {}
};

/**
* 'Canvas', the drawing panel for the search graph, expanded nodes, and path ( if found ).
*/
class Canvas
{

public:

	// CORE: construct
	Canvas::Canvas( wxPanel* inPanel )
		: cPanel( inPanel ){}
	void Init();

	// CORE: get/set
	void SetRandomize( int inRandSeed );
	void SetNodeCount( int inNodeCount );
	void SetEdgeDensity( float inEdgeDensity );
	void SetAlgorithm( ESearchAlgorithm inAlgorithm );
	void SetOptimality( float inOptimality );

	// UI: get/set
	void SetStatusBar( wxStatusBar* inStatusBar );
	void SetRealTime( bool inRealtime )
	{ bRealtime = inRealtime; }
	void SetCanvasSettingPanel( class CanvasSettingPanel* inCanvasSettingPanel )
	{ cCanvasSettingPanel = inCanvasSettingPanel; }
	void SetPathQueryPanel( class PathQueryPanel* inPathQueryPanel )
	{ cPathQueryPanel = inPathQueryPanel; }
	void SetSearchSpecPanel( SearchSpecPanel* inSearchSpecPanel )
	{ cSearchSpecPanel = inSearchSpecPanel; }
	void SetPathSpecPanel( PathSpecPanel* inPathSpecPanel )
	{ cPathSpecPanel = inPathSpecPanel; }

	// UI: event handling
	void OnPaint( wxPaintEvent& );
	void OnMotion( wxMouseEvent& );
	void OnLeftDown( wxMouseEvent& );
	void OnRightDown( wxMouseEvent& );
	void OnLeaveWindow( wxMouseEvent& );
	void OnSize( wxSizeEvent& );

	// CORE: pathfinding
	void InitPath();
	void FindPath();

private:

	// CORE: data struct
	std::vector<Node> nodes;
	int randSeed;
	int nodeCount;
	float edgeDensity;
	float optimality;
	ESearchAlgorithm algorithm;
	Pathfinder<Node, Edge> pathfinder;

	// UI: components
	wxPanel* cPanel;
	wxStatusBar* cStatusBar;
	CanvasSettingPanel* cCanvasSettingPanel;
	PathQueryPanel* cPathQueryPanel;
	SearchSpecPanel* cSearchSpecPanel;
	PathSpecPanel* cPathSpecPanel;

	// UI: drawing
	void RenderCanvas();
	void Refresh( bool inDirty = false );
	wxMemoryDC drawBuffer;
	wxMemoryDC renderBuffer;

	// UI: logging, status
	void PushStatus( const char* inStatus );
	void PopStatus();
	std::stack<const char*> statusStack;

	// UI: mouse handling
	int mouseNodeIndex;
	int mouseStartIndex;
	int mouseEndIndex;

	// UI: misc
	bool bRealtime;
	bool dirty;

};

/**
* 'CanvasSettingPanel', handles the graph settings.
*/
class CanvasSettingPanel : public CanvasSettingPanelBase
{

private:

	Canvas* canvas;

public:

	virtual void OnRandomizeSpin( wxSpinEvent& inEvent )
	{
		canvas->SetRandomize( cRandomizeSpin->GetValue() );
		inEvent.Skip();
	}

	virtual void OnRandomizeSpin( wxCommandEvent& inEvent )
	{
		wxSpinEvent initEvent( wxEVT_NULL, 0 );
		OnRandomizeSpin( initEvent );
		inEvent.Skip();
	}

	virtual void OnNodeCountSpin( wxSpinEvent& inEvent )
	{
		canvas->SetNodeCount( cNodeCountSpin->GetValue() );
		inEvent.Skip();
	}

	virtual void OnNodeCountSpin( wxCommandEvent& inEvent )
	{
		wxSpinEvent initEvent( wxEVT_NULL, 0 );
		OnNodeCountSpin( initEvent );
		inEvent.Skip();
	}

	virtual void OnEdgeDensitySpin( wxSpinEvent& inEvent )
	{
		canvas->SetEdgeDensity( cEdgeDensitySpin->GetValue() / 10.f );
		inEvent.Skip();
	}

	virtual void OnEdgeDensitySpin( wxCommandEvent& inEvent )
	{
		wxSpinEvent initEvent( wxEVT_NULL, 0 );
		OnEdgeDensitySpin( initEvent );
		inEvent.Skip();
	}

	void SetCanvas( Canvas* inCanvas )
	{
		canvas = inCanvas;
	}

	CanvasSettingPanel( wxWindow* inParent ) : CanvasSettingPanelBase( inParent ) {}

};

/**
* 'PathQueryPanel', handles the search settings.
*/
class PathQueryPanel : public PathQueryPanelBase
{

private:

	Canvas* canvas;

public:

	virtual void OnAlgorithmChoice( wxCommandEvent& inEvent )
	{
		switch( cAlgorithmChoice->GetSelection() )
		{
		case 0:	canvas->SetAlgorithm( BreadthFirst ); break;
		case 1:	canvas->SetAlgorithm( DepthFirst ); break;
		case 2:	canvas->SetAlgorithm( NearestFirst ); break;
		case 3: canvas->SetAlgorithm( AstarHeap ); break;
		case 4:	canvas->SetAlgorithm( AstarList ); break;
		}
		inEvent.Skip();
	}

	virtual void OnOptimalitySpin( wxSpinEvent& inEvent )
	{
		canvas->SetOptimality( cOptimalitySpin->GetValue() / 100.f );
		inEvent.Skip();
	}

	virtual void OnOptimalitySpin( wxCommandEvent& inEvent )
	{
		wxSpinEvent initEvent( wxEVT_NULL, 0 );
		OnOptimalitySpin( initEvent );
		inEvent.Skip();
	}

	void SetCanvas( Canvas* inCanvas )
	{
		canvas = inCanvas;
	}

	PathQueryPanel( wxWindow* inParent ) : PathQueryPanelBase( inParent ) {}

};

#endif