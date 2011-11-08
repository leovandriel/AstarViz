///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 20 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "AstarVizFrameBase.h"

///////////////////////////////////////////////////////////////////////////

AstarVizFrameBase::AstarVizFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* cSizer;
	cSizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* cCenterSizer;
	cCenterSizer = new wxBoxSizer( wxVERTICAL );
	
	cCanvasPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	cCenterSizer->Add( cCanvasPanel, 1, wxEXPAND, 5 );
	
	cSizer->Add( cCenterSizer, 1, wxEXPAND, 5 );
	
	cSideSizer = new wxBoxSizer( wxVERTICAL );
	
	cSizer->Add( cSideSizer, 0, wxEXPAND, 5 );
	
	this->SetSizer( cSizer );
	this->Layout();
	cStatusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	cCanvasPanel->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( AstarVizFrameBase::OnCanvasLeaveWindow ), NULL, this );
	cCanvasPanel->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( AstarVizFrameBase::OnCanvasLeftDown ), NULL, this );
	cCanvasPanel->Connect( wxEVT_MOTION, wxMouseEventHandler( AstarVizFrameBase::OnCanvasMotion ), NULL, this );
	cCanvasPanel->Connect( wxEVT_PAINT, wxPaintEventHandler( AstarVizFrameBase::OnCanvasPaint ), NULL, this );
	cCanvasPanel->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AstarVizFrameBase::OnCanvasRightDown ), NULL, this );
	cCanvasPanel->Connect( wxEVT_SIZE, wxSizeEventHandler( AstarVizFrameBase::OnCanvasSize ), NULL, this );
}

AstarVizFrameBase::~AstarVizFrameBase()
{
	// Disconnect Events
	cCanvasPanel->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( AstarVizFrameBase::OnCanvasLeaveWindow ), NULL, this );
	cCanvasPanel->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( AstarVizFrameBase::OnCanvasLeftDown ), NULL, this );
	cCanvasPanel->Disconnect( wxEVT_MOTION, wxMouseEventHandler( AstarVizFrameBase::OnCanvasMotion ), NULL, this );
	cCanvasPanel->Disconnect( wxEVT_PAINT, wxPaintEventHandler( AstarVizFrameBase::OnCanvasPaint ), NULL, this );
	cCanvasPanel->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AstarVizFrameBase::OnCanvasRightDown ), NULL, this );
	cCanvasPanel->Disconnect( wxEVT_SIZE, wxSizeEventHandler( AstarVizFrameBase::OnCanvasSize ), NULL, this );
}

CanvasSettingPanelBase::CanvasSettingPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer6->Add( m_staticline1, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxVERTICAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText51 = new wxStaticText( this, wxID_ANY, wxT("Randomize"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	m_staticText51->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText51, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	cRandomizeSpin = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 10000, 0 );
	cRandomizeSpin->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cRandomizeSpin->SetToolTip( wxT("Set the seed for all randomize processes.") );
	
	fgSizer2->Add( cRandomizeSpin, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Node Count"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	m_staticText5->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	cNodeCountSpin = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 100000, 5000 );
	cNodeCountSpin->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cNodeCountSpin->SetToolTip( wxT("The number of nodes that will be sampled onto the canvas.") );
	
	fgSizer2->Add( cNodeCountSpin, 0, wxALL, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Edge Density"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	cEdgeDensitySpin = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 100, 13 );
	cEdgeDensitySpin->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cEdgeDensitySpin->SetToolTip( wxT("The maximum distance over which edges will exist. (made invariant to the node count)") );
	
	fgSizer2->Add( cEdgeDensitySpin, 0, wxALL, 5 );
	
	bSizer6->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer6 );
	this->Layout();
	bSizer6->Fit( this );
	
	// Connect Events
	cRandomizeSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSettingPanelBase::OnRandomizeSpin ), NULL, this );
	cRandomizeSpin->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CanvasSettingPanelBase::OnRandomizeSpin ), NULL, this );
	cNodeCountSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSettingPanelBase::OnNodeCountSpin ), NULL, this );
	cNodeCountSpin->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CanvasSettingPanelBase::OnNodeCountSpin ), NULL, this );
	cEdgeDensitySpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSettingPanelBase::OnEdgeDensitySpin ), NULL, this );
	cEdgeDensitySpin->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CanvasSettingPanelBase::OnEdgeDensitySpin ), NULL, this );
}

CanvasSettingPanelBase::~CanvasSettingPanelBase()
{
	// Disconnect Events
	cRandomizeSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSettingPanelBase::OnRandomizeSpin ), NULL, this );
	cRandomizeSpin->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CanvasSettingPanelBase::OnRandomizeSpin ), NULL, this );
	cNodeCountSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSettingPanelBase::OnNodeCountSpin ), NULL, this );
	cNodeCountSpin->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CanvasSettingPanelBase::OnNodeCountSpin ), NULL, this );
	cEdgeDensitySpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CanvasSettingPanelBase::OnEdgeDensitySpin ), NULL, this );
	cEdgeDensitySpin->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CanvasSettingPanelBase::OnEdgeDensitySpin ), NULL, this );
}

PathQueryPanelBase::PathQueryPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer6->Add( m_staticline1, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxVERTICAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Algorithm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxString cAlgorithmChoiceChoices[] = { wxT("Breadth"), wxT("Depth"), wxT("Nearest"), wxT("A* Heap"), wxT("A* List") };
	int cAlgorithmChoiceNChoices = sizeof( cAlgorithmChoiceChoices ) / sizeof( wxString );
	cAlgorithmChoice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cAlgorithmChoiceNChoices, cAlgorithmChoiceChoices, 0 );
	cAlgorithmChoice->SetSelection( 4 );
	cAlgorithmChoice->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cAlgorithmChoice->SetToolTip( wxT("The algorithm that will be run for pathfinding.") );
	cAlgorithmChoice->SetMinSize( wxSize( 64,-1 ) );
	
	fgSizer2->Add( cAlgorithmChoice, 0, wxALL, 5 );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Optimality (%)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	m_staticText21->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	cOptimalitySpin = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxSP_ARROW_KEYS|wxSP_WRAP, 0, 10000, 100 );
	cOptimalitySpin->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cOptimalitySpin->SetToolTip( wxT("Multiplier for the euclidian distance heuristic.") );
	
	fgSizer2->Add( cOptimalitySpin, 0, wxALL, 5 );
	
	bSizer6->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer6 );
	this->Layout();
	bSizer6->Fit( this );
	
	// Connect Events
	cAlgorithmChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PathQueryPanelBase::OnAlgorithmChoice ), NULL, this );
	cOptimalitySpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PathQueryPanelBase::OnOptimalitySpin ), NULL, this );
	cOptimalitySpin->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( PathQueryPanelBase::OnOptimalitySpin ), NULL, this );
}

PathQueryPanelBase::~PathQueryPanelBase()
{
	// Disconnect Events
	cAlgorithmChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PathQueryPanelBase::OnAlgorithmChoice ), NULL, this );
	cOptimalitySpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PathQueryPanelBase::OnOptimalitySpin ), NULL, this );
	cOptimalitySpin->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( PathQueryPanelBase::OnOptimalitySpin ), NULL, this );
}

SearchSpecPanel::SearchSpecPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer7->Add( m_staticline2, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxVERTICAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Found"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	cFoundText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxTE_READONLY );
	cFoundText->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cFoundText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	fgSizer2->Add( cFoundText, 0, wxALL, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Time (ms)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	m_staticText7->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	cTimeText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxTE_READONLY );
	cTimeText->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cTimeText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	fgSizer2->Add( cTimeText, 0, wxALL, 5 );
	
	m_staticText81 = new wxStaticText( this, wxID_ANY, wxT("Node Expand"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	m_staticText81->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText81, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	cNodeExpandText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxTE_READONLY );
	cNodeExpandText->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cNodeExpandText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	fgSizer2->Add( cNodeExpandText, 0, wxALL, 5 );
	
	m_staticText811 = new wxStaticText( this, wxID_ANY, wxT("Succ. Expand"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText811->Wrap( -1 );
	m_staticText811->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText811, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	cSuccExpandText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxTE_READONLY );
	cSuccExpandText->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cSuccExpandText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	fgSizer2->Add( cSuccExpandText, 0, wxALL, 5 );
	
	bSizer7->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer7 );
	this->Layout();
	bSizer7->Fit( this );
}

SearchSpecPanel::~SearchSpecPanel()
{
}

PathSpecPanel::PathSpecPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer8->Add( m_staticline3, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxVERTICAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Est Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	m_staticText7->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	cEstLengthText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxTE_READONLY );
	cEstLengthText->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cEstLengthText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	fgSizer2->Add( cEstLengthText, 0, wxALL, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Length"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	cLengthText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxTE_READONLY );
	cLengthText->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cLengthText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	fgSizer2->Add( cLengthText, 0, wxALL, 5 );
	
	m_staticText81 = new wxStaticText( this, wxID_ANY, wxT("Nodes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	m_staticText81->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer2->Add( m_staticText81, 0, wxALL, 5 );
	
	cNodesText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 64,-1 ), wxTE_READONLY );
	cNodesText->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	cNodesText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	fgSizer2->Add( cNodesText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer8->Add( fgSizer2, 0, wxEXPAND, 5 );
	
	m_staticline31 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer8->Add( m_staticline31, 0, wxEXPAND | wxALL, 5 );
	
	cOutputText = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_READONLY );
	cOutputText->SetFont( wxFont( 7, 74, 90, 90, false, wxT("Tahoma") ) );
	cOutputText->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	bSizer8->Add( cOutputText, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer8 );
	this->Layout();
	bSizer8->Fit( this );
}

PathSpecPanel::~PathSpecPanel()
{
}
