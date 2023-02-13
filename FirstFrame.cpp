#include "FirstFrame.h"
#include "mathplot.h"
BEGIN_EVENT_TABLE(FirstFrame, wxFrame)
EVT_BUTTON(1, FirstFrame::OnMenu)
EVT_BUTTON(2, FirstFrame::OnChart)
EVT_BUTTON(3, FirstFrame::OnNotes)
EVT_BUTTON(4, FirstFrame::OnSetting)
EVT_BUTTON(5, FirstFrame::OnRefresh)
END_EVENT_TABLE()

FirstFrame::FirstFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(620, 500))
{
    //Serial port 
    com = new CSerialCommHelper();
    Cookie CK = CookieR->readCookie();
    fileDir = CK.FileDir;
    saveINTERVAL = std::stoi(CK.saveCycle);
    path = &fileDir;
    //AppIcon
    wxImage::AddHandler(new wxPNGHandler);
    wxIcon calendar(wxT("calendar.png"), wxBITMAP_TYPE_PNG);
    this->SetIcon(calendar);

    //Bitmap Png files
    wxBitmap exit(wxT("test2.png"), wxBITMAP_TYPE_PNG);
    wxImage Image = exit.ConvertToImage();
    Image.Rescale(16, 16);
    wxBitmap NewBitmap(Image);
    wxBitmap refresh(wxT("refresh.png"), wxBITMAP_TYPE_PNG);
    wxBitmap settings(wxT("settings.png"), wxBITMAP_TYPE_PNG);
    wxBitmap stats(wxT("stats.png"), wxBITMAP_TYPE_PNG);
    wxBitmap notes(wxT("notes.png"), wxBITMAP_TYPE_PNG);
    wxBitmap house(wxT("house.png"), wxBITMAP_TYPE_PNG);

    //Sizers
    wxBoxSizer* mainBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    PanelToolBarSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* ToolBarBtnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* PanelIncludeSizer = new wxBoxSizer(wxVERTICAL);

    //Definition
    menu = new Menu(this);
    mainPanel = new wxPanel(this, wxID_ANY);
    wxPanel* PanelToolBar = new wxPanel(mainPanel, wxID_ANY, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN);
    button0 = new wxBitmapButton(PanelToolBar, 1, house);
    button1 = new wxBitmapButton(PanelToolBar, 2, stats);
    button2 = new wxBitmapButton(PanelToolBar, 3, notes);
    button3 = new wxBitmapButton(PanelToolBar, 4, settings);
    button4 = new wxBitmapButton(PanelToolBar, 5, refresh);
    wxPanel* PanelInclude = new wxPanel(mainPanel, wxID_ANY);
    menuCt = new menuContent(PanelIncludeSizer, PanelInclude);
    chartCt = new chartContent(PanelIncludeSizer, PanelInclude, com, path, saveINTERVAL);
    notesCt = new notesContent(PanelIncludeSizer, PanelInclude, path);
    settingCt = new settingContent(PanelIncludeSizer, PanelInclude, com, fileDir, saveINTERVAL);
    refreshCt = new refreshContent(PanelIncludeSizer, PanelInclude);

    //Add Sizers 
    ToolBarBtnSizer->Add(button0, 3, wxEXPAND | wxBOTTOM, 0);
    ToolBarBtnSizer->Add(button1, 3, wxEXPAND | wxBOTTOM, 0);
    ToolBarBtnSizer->Add(button2, 3, wxEXPAND | wxBOTTOM, 0);
    ToolBarBtnSizer->Add(button3, 3, wxEXPAND | wxBOTTOM, 0);
    ToolBarBtnSizer->Add(button4, 3, wxEXPAND | wxBOTTOM, 0);
    PanelToolBarSizer->Add(PanelToolBar, 1, wxEXPAND | wxBOTTOM, 0);
    PanelToolBarSizer->Add(PanelInclude, 15, wxEXPAND | wxBOTTOM, 0);
    mainBoxSizer->Add(mainPanel, 1, wxEXPAND | wxALL, 10);

    //Set Sizers
    this->SetSizer(mainBoxSizer);
    PanelToolBar->SetSizer(ToolBarBtnSizer);
    PanelInclude->SetSizer(PanelIncludeSizer);
    mainPanel->SetSizer(PanelToolBarSizer);

    //BackgroundColors
    col3.Set(wxT("#4f5049"));
    col1.Set(wxT("#ffffff"));
    col2.Set(wxT("#e7e7e7"));
    this->SetBackgroundColour(col3);
    mainPanel->SetBackgroundColour(col1);
    button0->SetBackgroundColour("lightgray");
    button1->SetBackgroundColour("#888383");
    button2->SetBackgroundColour("#888383");
    button3->SetBackgroundColour("#888383");
    button4->SetBackgroundColour("#888383");

    //Hide contents
    chartCt->hide();
    notesCt->hide();
    settingCt->hide();
    refreshCt->hide();

    //Center align App
    Centre();
}

//Function
void FirstFrame::OnMenu(wxCommandEvent& event) {
    menuCt->show();
    chartCt->hide();
    notesCt->hide();
    settingCt->hide();
    refreshCt->hide();
    button0->SetBackgroundColour("#e7e7e7");
    button1->SetBackgroundColour("#888383");
    button2->SetBackgroundColour("#888383");
    button3->SetBackgroundColour("#888383");
    button4->SetBackgroundColour("#888383");
    event.Skip();
}
void FirstFrame::OnChart(wxCommandEvent& event) {
    menuCt->hide();
    chartCt->show();
    notesCt->hide();
    settingCt->hide();
    refreshCt->hide();
    //
    button0->SetBackgroundColour("#888383");
    button1->SetBackgroundColour("#e7e7e7");
    button2->SetBackgroundColour("#888383");
    button3->SetBackgroundColour("#888383");
    button4->SetBackgroundColour("#888383");
    event.Skip();
}

void FirstFrame::OnNotes(wxCommandEvent& event) {
    menuCt->hide();
    chartCt->hide();
    notesCt->show();
    settingCt->hide();
    refreshCt->hide();
    //
    button0->SetBackgroundColour("#888383");
    button1->SetBackgroundColour("#888383");
    button2->SetBackgroundColour("#e7e7e7");
    button3->SetBackgroundColour("#888383");
    button4->SetBackgroundColour("#888383");
    event.Skip();
}
void FirstFrame::OnSetting(wxCommandEvent& event) {
    menuCt->hide();
    chartCt->hide();
    notesCt->hide();
    settingCt->show();
    refreshCt->hide();
    //
    button0->SetBackgroundColour("#888383");
    button1->SetBackgroundColour("#888383");
    button2->SetBackgroundColour("#888383");
    button3->SetBackgroundColour("#e7e7e7");
    button4->SetBackgroundColour("#888383");
    event.Skip();
}
void FirstFrame::OnRefresh(wxCommandEvent& event) {
    menuCt->hide();
    chartCt->hide();
    notesCt->hide();
    settingCt->hide();
    refreshCt->show();
    //
    button0->SetBackgroundColour("#888383");
    button1->SetBackgroundColour("#888383");
    button2->SetBackgroundColour("#888383");
    button3->SetBackgroundColour("#888383");
    button4->SetBackgroundColour("#e7e7e7");
    event.Skip();
}