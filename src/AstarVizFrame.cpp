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
// 'AstarViz.cpp' - For more info see 'AstarViz.h'.
//
//==================================================================================================

#include "AstarVizFrame.h"

//--------------------------------------------------------------------------------------------------
//
// AstarVizFrame
//
//--------------------------------------------------------------------------------------------------

AstarVizFrame::AstarVizFrame()
	: AstarVizFrameBase( NULL )
{
	SetIcon( wxIcon( AstarVizIcon ) );
	cCanvas = new Canvas( cCanvasPanel );

	SetTitle( _T( PROGRAM_TITLE ) );

	cCanvasSettingPanel
		= new CanvasSettingPanel( this );
	cSideSizer->Add( cCanvasSettingPanel, 0, wxEXPAND, 5 );
	cCanvasSettingPanel->SetCanvas( cCanvas );

	cPathQueryPanel
		= new PathQueryPanel( this );
	cSideSizer->Add( cPathQueryPanel, 0, wxEXPAND, 5 );
	cPathQueryPanel->SetCanvas( cCanvas );

	cSearchSpecPanel
		= new SearchSpecPanel( this );
	cSideSizer->Add( cSearchSpecPanel, 0, wxEXPAND, 5 );

	cPathSpecPanel
		= new PathSpecPanel( this );
	cSideSizer->Add( cPathSpecPanel, 1, wxEXPAND, 5 );

	cCanvas->SetStatusBar( cStatusBar );
	cCanvas->SetCanvasSettingPanel( cCanvasSettingPanel );
	cCanvas->SetPathSpecPanel( cPathSpecPanel );
	cCanvas->SetSearchSpecPanel( cSearchSpecPanel );
	cCanvas->SetPathQueryPanel( cPathQueryPanel );
}

AstarVizFrame::~AstarVizFrame()
{
	delete cPathQueryPanel;
	delete cSearchSpecPanel;
	delete cPathSpecPanel;
	delete cCanvas;
}

void AstarVizFrame::Init()
{
	cCanvas->SetRealTime( false );
	cCanvas->Init();
	cCanvas->SetRealTime( true );
}

void AstarVizFrame::OnCanvasPaint( wxPaintEvent& inEvent )
{
	cCanvas->OnPaint( inEvent );
	inEvent.Skip();
}

void AstarVizFrame::OnCanvasMotion( wxMouseEvent& inEvent )
{
	cCanvas->OnMotion( inEvent );
	inEvent.Skip();
}
void AstarVizFrame::OnCanvasLeftDown( wxMouseEvent& inEvent )
{
	cCanvas->OnLeftDown( inEvent );
	inEvent.Skip();
}
void AstarVizFrame::OnCanvasRightDown( wxMouseEvent& inEvent )
{
	cCanvas->OnRightDown( inEvent );
	inEvent.Skip();
}

void AstarVizFrame::OnCanvasLeaveWindow( wxMouseEvent& inEvent )
{
	cCanvas->OnLeaveWindow( inEvent );
	inEvent.Skip();
}

void AstarVizFrame::OnCanvasSize( wxSizeEvent& inEvent )
{
	cCanvas->OnSize( inEvent );
	inEvent.Skip();
}