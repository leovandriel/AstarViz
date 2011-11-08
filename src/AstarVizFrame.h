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
// 'AstarViz.h' - Wrapping Wx around 'Canvas'.
//
// Functionality of this program is mainly distributed over:
// - 'Canvas.h' for UI/program stuff.
// - 'Search.h' for A* graph search algorithm.
//
//==================================================================================================

#ifndef _ASTARVIZFRAME_H_
#define _ASTARVIZFRAME_H_

#include <wx/wx.h>
#include "AstarVizFrameBase.h"
#include "Canvas.h"

#ifdef _DEBUG
#define PROGRAM_TITLE "AstarViz v.1 [DEBUG]"
#else
#define PROGRAM_TITLE "AstarViz v.1"
#endif

class AstarVizFrame : public AstarVizFrameBase
{

private:

	Canvas* cCanvas;
	CanvasSettingPanel* cCanvasSettingPanel;
	PathQueryPanel* cPathQueryPanel;
	SearchSpecPanel* cSearchSpecPanel;
	PathSpecPanel* cPathSpecPanel;

protected:

	virtual void OnCanvasPaint( wxPaintEvent& );
	virtual void OnCanvasMotion( wxMouseEvent& );
	virtual void OnCanvasLeftDown( wxMouseEvent& );
	virtual void OnCanvasRightDown( wxMouseEvent& );
	virtual void OnCanvasLeaveWindow( wxMouseEvent& );
	virtual void OnCanvasSize( wxSizeEvent& );

public:

	AstarVizFrame();
	~AstarVizFrame();
	void Init();

};

static char* AstarVizIcon[] = {
	"32 32 6 1",
	"  c #000000",
	"0 c #FF007F",
	"o c #007FFF",
	"O c #FF7F00",
	"+ c #FFFFFF",
	". c #000000",
	"                                ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" +++++++++++++++++++oooo+++++++ ",
	" ++++++++++++++++++oooooo++++++ ",
	" ++++++++++++++++++oooooo++++++ ",
	" ++++++++++++++++++oooooo++++++ ",
	" +++++++++++++++++++oooo+++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" +++++OOOO+++++++++++++++++++++ ",
	" ++++OOOOOO++++++++++++++++++++ ",
	" ++++OOOOOO++++++++++++++++++++ ",
	" ++++OOOOOO++++++++++++++++++++ ",
	" +++++OOOO+++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++0000++++++++ ",
	" +++++++++++++++++000000+++++++ ",
	" +++++++++++++++++000000+++++++ ",
	" +++++++++++++++++000000+++++++ ",
	" ++++++++++++++++++0000++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	" ++++++++++++++++++++++++++++++ ",
	"                                "
};

#endif