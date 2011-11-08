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
// 'Canvas.cpp' - For more info see 'Canvas.h'.
//
//==================================================================================================

#include "Canvas.h"
#include <algorithm>
#include <math.h>

//--------------------------------------------------------------------------------------------------
//
// Canvas::Public
//
//--------------------------------------------------------------------------------------------------

void Canvas::Init()
{
	PushStatus( "Init" );

	wxSizeEvent initSizeEvent = wxSizeEvent();
	OnSize( initSizeEvent );

	wxCommandEvent initCommandEvent = wxCommandEvent();
	cPathQueryPanel->OnAlgorithmChoice( initCommandEvent );

	wxSpinEvent initSpinEvent( wxEVT_NULL, 0 );
	cPathQueryPanel->OnOptimalitySpin( initSpinEvent );
	cCanvasSettingPanel->OnRandomizeSpin( initSpinEvent );
	cCanvasSettingPanel->OnNodeCountSpin( initSpinEvent );
	cCanvasSettingPanel->OnEdgeDensitySpin( initSpinEvent );

	mouseStartIndex = 0;
	mouseEndIndex = 1;

	InitPath();
	FindPath();

	PushStatus( "Ready" );
}

void Canvas::SetStatusBar( wxStatusBar* inStatusBar )
{
	cStatusBar = inStatusBar;
}

void Canvas::SetRandomize( int inRandSeed )
{
	if( randSeed != inRandSeed ) {} else return;

	randSeed = inRandSeed;

	if( bRealtime )
	{
		InitPath();
		FindPath();
		Refresh();
	}
}

void Canvas::SetNodeCount( int inNodeCount )
{
	if( nodeCount != inNodeCount ) {} else return;

	nodeCount = inNodeCount;

	if( bRealtime )
	{
		InitPath();
		FindPath();
		Refresh();
	}
}

void Canvas::SetEdgeDensity( float inEdgeDensity )
{
	if( edgeDensity != inEdgeDensity ) {} else return;

	edgeDensity = inEdgeDensity;

	if( bRealtime )
	{
		InitPath();
		FindPath();
		Refresh();
	}
}

void Canvas::SetAlgorithm( ESearchAlgorithm inAlgorithm )
{
	if( algorithm != inAlgorithm ) {} else return;

	algorithm = inAlgorithm;

	if( bRealtime )
	{
		FindPath();
		Refresh();
	}
}

void Canvas::SetOptimality( float inOptimality )
{
	if( optimality != inOptimality ) {} else return;

	optimality = inOptimality;

	if( bRealtime )
	{
		FindPath();
		Refresh();
	}
}

void Canvas::InitPath()
{
	srand( randSeed );

	mouseNodeIndex  = ( nodeCount - 1 < mouseNodeIndex ) ? nodeCount - 1 : mouseNodeIndex;
	mouseStartIndex = ( nodeCount - 1 < mouseStartIndex ) ? nodeCount - 1 : mouseStartIndex;
	mouseEndIndex   = ( nodeCount - 1 < mouseEndIndex ) ? nodeCount - 1 : mouseEndIndex;

	pathfinder.pathSpec = PathSpec<Node>();
	pathfinder.searchSpec = SearchSpec();
	pathfinder.pathQuery = PathQuery<Node>();

	PushStatus( "Creating nodes.." );

	nodes = std::vector<Node>( nodeCount );
	for( int n = 0; n < nodeCount; n++ )
	{
		nodes[n].pos = Point( CANVAS_WIDTH * rand() / RAND_MAX, CANVAS_HEIGHT * rand() / RAND_MAX );
	}
	sort( nodes.begin(), nodes.end() );

	PopStatus();

	PushStatus( "Creating edges.." );

	float maxd = edgeDensity * sqrt( CANVAS_WIDTH * CANVAS_HEIGHT / nodeCount ), avg = 0;
	for( int n = 0; n < nodeCount; n++ )
	{
		for( int m = n+1; m < nodeCount && nodes[m].pos.x - nodes[n].pos.x < maxd; m++ ){
			if( abs( nodes[n].pos.y - nodes[m].pos.y ) < maxd ){
				const float dist = ( nodes[n].pos-nodes[m].pos ).size();
				if( dist < maxd ){
					nodes[n].successors.push_back( Edge( &nodes[m], dist ) );
					nodes[m].successors.push_back( Edge( &nodes[n], dist ) );
				}
			}
		}
		avg += nodes[n].successors.size() / ( float )nodeCount;
	}

	PopStatus();

	dirty = true;
}


void Canvas::FindPath()
{
	if( mouseStartIndex >= 0 && mouseEndIndex >= 0 ) {} else return;

	srand( randSeed );

	pathfinder.pathSpec = PathSpec<Node>();
	pathfinder.searchSpec = SearchSpec();
	pathfinder.pathQuery = PathQuery<Node>();

	pathfinder.pathQuery.start = &nodes[mouseStartIndex];
	pathfinder.pathQuery.end = &nodes[mouseEndIndex];
	pathfinder.pathQuery.optimality = optimality;

	PushStatus( "Searching path.." );

	pathfinder.Search( algorithm );

	PopStatus();

	wxString buffer;
	cPathSpecPanel->cOutputText->Clear();

	buffer.clear();buffer.Printf( "%u", pathfinder.searchSpec.nodeExpand );
	cSearchSpecPanel->cNodeExpandText->SetValue( buffer );
	buffer.clear();buffer.Printf( "%s", pathfinder.searchSpec.found?"TRUE":"FALSE" );
	cSearchSpecPanel->cFoundText->SetValue( buffer );
	buffer.clear();buffer.Printf( "%.3f", pathfinder.searchSpec.searchTime*1000.f );
	cSearchSpecPanel->cTimeText->SetValue( buffer );
	buffer.clear();buffer.Printf( "%u", pathfinder.searchSpec.succExpand );
	cSearchSpecPanel->cSuccExpandText->SetValue( buffer );

	buffer.clear();buffer.Printf( "NodeExp / ms : %.0f\n"
		, pathfinder.searchSpec.nodeExpand / ( pathfinder.searchSpec.searchTime*1000.f ) );
	cPathSpecPanel->cOutputText->AppendText( buffer );
	buffer.clear();buffer.Printf( "SuccExp / ms : %.0f\n"
		, pathfinder.searchSpec.succExpand / ( pathfinder.searchSpec.searchTime*1000.f ) );
	cPathSpecPanel->cOutputText->AppendText( buffer );
	buffer.clear();buffer.Printf( "SuccExp / NodeExp : %.2f\n"
		, pathfinder.searchSpec.succExpand / ( float ) pathfinder.searchSpec.nodeExpand );
	cPathSpecPanel->cOutputText->AppendText( buffer );

	if( pathfinder.searchSpec.found )
	{
		float length = 0;
		for( int i = 1; i < ( int )pathfinder.pathSpec.pathSequence.size(); i++ )
		{
			const Node& n = *pathfinder.pathSpec.pathSequence[i-1];
			const Node& m = *pathfinder.pathSpec.pathSequence[i];
			length += sqrt( ( n.pos - m.pos ) | ( n.pos - m.pos ) );
		}

		buffer.clear();buffer.Printf( "%.3f", length );
		cPathSpecPanel->cLengthText->SetValue( buffer );
		buffer.clear();buffer.Printf( "%.3f", pathfinder.pathSpec.estLength );
		cPathSpecPanel->cEstLengthText->SetValue( buffer );
		buffer.clear();buffer.Printf( "%u", ( int )pathfinder.pathSpec.pathSequence.size() );
		cPathSpecPanel->cNodesText->SetValue( buffer );

		const float nodes = ( int )pathfinder.pathSpec.pathSequence.size();

		buffer.clear();buffer.Printf( "NodesSq / NodeExp : %.4f\n"
			, nodes * nodes / pathfinder.searchSpec.nodeExpand );
		cPathSpecPanel->cOutputText->AppendText( buffer );
		buffer.clear();buffer.Printf( "NodesSq / SuccExp : %.4f\n"
			, nodes * nodes / pathfinder.searchSpec.succExpand );
		cPathSpecPanel->cOutputText->AppendText( buffer );
	}
	else
	{
		cPathSpecPanel->cLengthText->SetValue( _T( "-" ) );
		cPathSpecPanel->cEstLengthText->SetValue( _T( "-" ) );
		cPathSpecPanel->cNodesText->SetValue( _T( "-" ) );
	}

	dirty = true;
}

void Canvas::Refresh( bool inDirty )
{
	if( inDirty )
	{
		dirty = true;
	}
	cPanel->Refresh( false );
}

//--------------------------------------------------------------------------------------------------
//
// Canvas::Private
//
//--------------------------------------------------------------------------------------------------

void Canvas::RenderCanvas()
{
	PushStatus( "Rendering canvas.." );

	const int width = cPanel->GetClientSize().GetWidth();
	const int height = cPanel->GetClientSize().GetHeight();

	renderBuffer.SetPen( wxPen( wxColour( COLOR_BG ) ) );
	renderBuffer.SetBrush( wxBrush( wxColour( COLOR_BG ) ) );
	renderBuffer.DrawRectangle( 0, 0, width, height );

	// draw edges

	renderBuffer.SetPen( wxPen( wxColour( COLOR_EDGE ) ) );
	renderBuffer.SetBrush( wxBrush( wxColour( COLOR_EDGE ) ) );
	for( int i = 0; i < nodeCount; i++ )
	{
		const Node& node = nodes[i];
		const std::vector<Edge>& s = nodes[i].successors;
		for( std::vector<Edge>::const_iterator j = s.begin(); j != s.end(); j++ )
		{
			const Node& node2 = *j->node;
			renderBuffer.DrawLine( ( int )( node.pos.x*width ), ( int )( node.pos.y*height )
				, ( int )( node2.pos.x*width ), ( int )( node2.pos.y*height ) );
		}
	}

	// draw nodes

	for( int i = 0; i < nodeCount; i++ )
	{
		const Node& node = nodes[i];
		if( node.stateId == pathfinder.openId )
		{
			renderBuffer.SetPen( wxPen( wxColour( COLOR_OPEN ) ) );
			renderBuffer.SetBrush( wxBrush( wxColour( COLOR_OPEN ) ) );
		}
		else if( node.stateId == pathfinder.closeId )
		{
			renderBuffer.SetPen( wxPen( wxColour( COLOR_CLOSED ) ) );
			renderBuffer.SetBrush( wxBrush( wxColour( COLOR_CLOSED ) ) );
		}
		else
		{
			renderBuffer.SetPen( wxPen( wxColour( COLOR_NODE ) ) );
			renderBuffer.SetBrush( wxBrush( wxColour( COLOR_NODE ) ) );
		}
		renderBuffer.DrawCircle( ( int )( node.pos.x*width ), ( int )( node.pos.y*height )
			, NODE_DRAW_RADIUS );
	}

	// start / end

	if( mouseEndIndex >= 0 )
	{
		renderBuffer.SetPen( wxPen( wxColour( COLOR_END ) ) );
		renderBuffer.SetBrush( wxBrush( wxColour( COLOR_END ) ) );
		renderBuffer.DrawCircle( ( int )( nodes[mouseEndIndex].pos.x*width )
			, ( int )( nodes[mouseEndIndex].pos.y*height ), MOUSE_DRAW_RADIUS );
	}

	if( mouseStartIndex >= 0 )
	{
		renderBuffer.SetPen( wxPen( wxColour( COLOR_START ) ) );
		renderBuffer.SetBrush( wxBrush( wxColour( COLOR_START ) ) );
		renderBuffer.DrawCircle( ( int )( nodes[mouseStartIndex].pos.x*width )
			, ( int )( nodes[mouseStartIndex].pos.y*height ), MOUSE_DRAW_RADIUS );
	}

	// draw path

	renderBuffer.SetPen( wxPen( wxColour( COLOR_PATH ) ) );
	renderBuffer.SetBrush( wxBrush( wxColour( COLOR_PATH ) ) );
	for( int i = 0; i < ( int )pathfinder.pathSpec.pathSequence.size(); i++ )
	{
		const Node& node = *pathfinder.pathSpec.pathSequence[i];
		renderBuffer.DrawCircle( ( int )( node.pos.x*width ), ( int )( node.pos.y*height )
			, NODE_DRAW_RADIUS );
		if( i > 0 )
		{
			const Node& node2 = *pathfinder.pathSpec.pathSequence[i-1];
			renderBuffer.DrawLine( ( int )( node.pos.x*width ), ( int )( node.pos.y*height )
				, ( int )( node2.pos.x*width ), ( int )( node2.pos.y*height ) );
		}
	}

	PopStatus();
}

void Canvas::PushStatus( const char* inStatus )
{
	statusStack.push( inStatus );
	cStatusBar->SetStatusText( _T( statusStack.top() ) );
}

void Canvas::PopStatus()
{
	statusStack.pop();
	cStatusBar->SetStatusText( _T( statusStack.top() ) );
}

//--------------------------------------------------------------------------------------------------
//
// Canvas::Event
//
//--------------------------------------------------------------------------------------------------

void Canvas::OnPaint( wxPaintEvent& )
{
	wxPaintDC dc( cPanel );

	if( dirty )
	{
		RenderCanvas();
		dirty = false;
	}

	const int width = cPanel->GetClientSize().GetWidth();
	const int height = cPanel->GetClientSize().GetHeight();

	drawBuffer.Blit( 0, 0, width, height, &renderBuffer, 0, 0 );

	if( mouseNodeIndex >= 0 )
	{
		drawBuffer.SetPen( wxPen( wxColour( COLOR_MOUSE ) ) );
		drawBuffer.SetBrush( wxBrush( wxColour( COLOR_MOUSE ) ) );
		drawBuffer.DrawCircle( ( int )( nodes[mouseNodeIndex].pos.x*width )
			, ( int )( nodes[mouseNodeIndex].pos.y*height ), MOUSE_DRAW_RADIUS );
	}

	dc.Blit( 0, 0, width, height, &drawBuffer, 0, 0 );
}

void Canvas::OnSize( wxSizeEvent& )
{
	const int width = cPanel->GetClientSize().GetWidth();
	const int height = cPanel->GetClientSize().GetHeight();

	wxBitmap drawBitmap = wxBitmap( width, height );
	drawBuffer.SelectObject( drawBitmap );

	wxBitmap renderBitmap = wxBitmap( width, height );
	renderBuffer.SelectObject( renderBitmap );

	Refresh( true );
}

void Canvas::OnMotion( wxMouseEvent& inEvent )
{
	const int width = cPanel->GetClientSize().GetWidth();
	const int height = cPanel->GetClientSize().GetHeight();

	const Point p( inEvent.GetX() / ( float )width, inEvent.GetY() / ( float )height );

	float min = -1.f;
	mouseNodeIndex = -1;

	for( int i = 0; i < nodeCount; i++ )
	{
		if( min < 0.f || min > ( ( nodes[i].pos - p ) | ( nodes[i].pos - p ) ) )
		{
			min = ( nodes[i].pos-p )|( nodes[i].pos-p );
			mouseNodeIndex = i;
		}
	}

	if( inEvent.LeftIsDown() )
	{
		mouseStartIndex = mouseNodeIndex;
		if( bRealtime )
		{
			FindPath();
		}
	}
	else if( inEvent.RightIsDown() )
	{
		mouseEndIndex = mouseNodeIndex;
		if( bRealtime )
		{
			FindPath();
		}
	}

	Refresh();
}

void Canvas::OnLeftDown( wxMouseEvent& )
{
	mouseStartIndex = mouseNodeIndex;
	if( bRealtime )
	{
		FindPath();
	}

	Refresh();
}

void Canvas::OnRightDown( wxMouseEvent& )
{
	mouseEndIndex = mouseNodeIndex;
	if( bRealtime )
	{
		FindPath();
	}

	Refresh();
}

void Canvas::OnLeaveWindow( wxMouseEvent& )
{
	mouseNodeIndex = -1;

	Refresh();
}


