#include "refreshContent.h"

refreshContent::refreshContent(wxBoxSizer* parent, wxPanel* parentpn) : 
    wxPanel(parentpn, wxID_ANY, wxPoint(-1, -1), wxSize(-1, -1))
{
    //Parent setting    
    NotesParent = parentpn;

    //Bitmaps
    wxBitmap refresh(wxT("refresh.png"), wxBITMAP_TYPE_PNG);

    //Sizers
    wxBoxSizer* PanelContentSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* LeftPanelSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* LeftPanelCtSizer = new wxBoxSizer(wxHORIZONTAL);

    //Definition
    wxPanel* LeftPanel = new wxPanel(this, 41, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN);
    //wxPanel* RightContent = new wxPanel(PanelContent, 42, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN);
    wxStaticText* m_text = new wxStaticText(LeftPanel, -1, wxT("Refresh"),
        wxPoint(0, 0), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
    wxPanel* LeftPanelCt = new wxPanel(LeftPanel, 4, wxPoint(-1, -1),
        wxSize(-1, -1), wxTOP | wxBORDER_SUNKEN);
    wxBitmapButton* refreshBtn = new wxBitmapButton(LeftPanelCt, wxID_ANY, refresh);

    //Add Sizers
    parent->Add(this, 15, wxEXPAND | wxBOTTOM, 0);
    PanelContentSizer->Add(LeftPanel, 4, wxEXPAND | wxRight, 1);
    LeftPanelSizer->Add(m_text, 1, wxEXPAND | wxBOTTOM, 0);
    LeftPanelSizer->Add(LeftPanelCt, 40, wxEXPAND | wxBOTTOM, 0);
    //PanelContentSizer->Add(RightContent, 8, wxEXPAND | wxALL, 0);
    LeftPanelCtSizer->Add(refreshBtn, 1, wxEXPAND | wxBOTTOM, 0);

    //Set Sizers 
    this->SetSizer(PanelContentSizer);
    LeftPanel->SetSizer(LeftPanelSizer);
    LeftPanelCt->SetSizer(LeftPanelCtSizer);

    //BackgroundColors
    m_text->SetBackgroundColour("#e7e7e7");
    
    //Fonts
    wxFont sum_font = m_text->GetFont();
    sum_font.SetWeight(wxFONTWEIGHT_BOLD);
    m_text->SetFont(sum_font);
   
}
void refreshContent::hide() {
    this->Hide();
}
void refreshContent::show() {
    this->SetClientSize(this->NotesParent->GetClientSize());
    this->Show();
}