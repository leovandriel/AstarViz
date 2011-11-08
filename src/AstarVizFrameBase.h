///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 20 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __AstarVizFrameBase__
#define __AstarVizFrameBase__

#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>
#include <wx/textctrl.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AstarVizFrameBase
///////////////////////////////////////////////////////////////////////////////
class AstarVizFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxPanel* cCanvasPanel;
		wxBoxSizer* cSideSizer;
		wxStatusBar* cStatusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCanvasLeaveWindow( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnCanvasLeftDown( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnCanvasMotion( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnCanvasPaint( wxPaintEvent& event ){ event.Skip(); }
		virtual void OnCanvasRightDown( wxMouseEvent& event ){ event.Skip(); }
		virtual void OnCanvasSize( wxSizeEvent& event ){ event.Skip(); }
		
	
	public:
		AstarVizFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("AstarViz"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~AstarVizFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CanvasSettingPanelBase
///////////////////////////////////////////////////////////////////////////////
class CanvasSettingPanelBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText51;
		wxSpinCtrl* cRandomizeSpin;
		wxStaticText* m_staticText5;
		wxSpinCtrl* cNodeCountSpin;
		wxStaticText* m_staticText1;
		wxSpinCtrl* cEdgeDensitySpin;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnRandomizeSpin( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnRandomizeSpin( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnNodeCountSpin( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnNodeCountSpin( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnEdgeDensitySpin( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnEdgeDensitySpin( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		CanvasSettingPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~CanvasSettingPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PathQueryPanelBase
///////////////////////////////////////////////////////////////////////////////
class PathQueryPanelBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText2;
		wxStaticText* m_staticText21;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAlgorithmChoice( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOptimalitySpin( wxSpinEvent& event ){ event.Skip(); }
		virtual void OnOptimalitySpin( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		wxChoice* cAlgorithmChoice;
		wxSpinCtrl* cOptimalitySpin;
		PathQueryPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~PathQueryPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SearchSpecPanel
///////////////////////////////////////////////////////////////////////////////
class SearchSpecPanel : public wxPanel 
{
	private:
	
	protected:
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText7;
		wxStaticText* m_staticText81;
		wxStaticText* m_staticText811;
	
	public:
		wxTextCtrl* cFoundText;
		wxTextCtrl* cTimeText;
		wxTextCtrl* cNodeExpandText;
		wxTextCtrl* cSuccExpandText;
		SearchSpecPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~SearchSpecPanel();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PathSpecPanel
///////////////////////////////////////////////////////////////////////////////
class PathSpecPanel : public wxPanel 
{
	private:
	
	protected:
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticText7;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText81;
		wxStaticLine* m_staticline31;
	
	public:
		wxTextCtrl* cEstLengthText;
		wxTextCtrl* cLengthText;
		wxTextCtrl* cNodesText;
		wxTextCtrl* cOutputText;
		PathSpecPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~PathSpecPanel();
	
};

#endif //__AstarVizFrameBase__
