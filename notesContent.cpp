#include "notesContent.h"
BEGIN_EVENT_TABLE(notesContent, wxPanel)
EVT_BUTTON(555, notesContent::refreshFunc)
EVT_BUTTON(556, notesContent::modifiedFunc)
EVT_BUTTON(557, notesContent::okFunc)
EVT_TEXT(558, notesContent::searchFunc)
EVT_LISTBOX(559, notesContent::onClickSearchListFunc)
END_EVENT_TABLE()
notesContent::notesContent(wxBoxSizer* parent, wxPanel* parentpn, string* filePath):
    wxPanel(parentpn, 333, wxPoint(-1, -1), wxSize(-1, -1))
{
    //Parents reference
    NotesParent = parentpn;
    fileDir = filePath;
    //Bitmaps
    wxBitmap refresh(wxT("refresh.png"), wxBITMAP_TYPE_PNG);

    //Sizers
    wxBoxSizer* PanelContentSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* LeftPanelSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* RightPanelSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* LCtSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* SearchPnSz = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* btnNotePnSz = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* RCtSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* grid1Sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* staticChartPn = new wxBoxSizer(wxVERTICAL);

    // Create a mpFXYVector layer
    vectorLayer = new mpFXYVector(_("Voltage(analog)"));
    vectorLayer->SetContinuity(true);
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayer->SetPen(vectorpen);
    vectorLayer->SetDrawOutsideMargins(false);
    
    //Definition
    wxPanel* LeftPanel = new wxPanel(this, 12, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN);
    wxPanel* RightContent = new wxPanel(this, 1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN);
    wxStaticText* m_text = new wxStaticText(LeftPanel, -1, wxT("Day"),
        wxPoint(0, 0), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
    LeftPanelCt = new wxPanel(LeftPanel, 4, wxPoint(-1, -1),
        wxSize(-1, -1), wxTOP | wxBORDER_SUNKEN);
    wxStaticText* m_text_r = new wxStaticText(RightContent, -1, wxT("Infomations"),
        wxPoint(0, 0), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
    wxPanel* RightPanelCt = new wxPanel(RightContent, 4, wxPoint(-1, -1),
        wxSize(-1, -1), wxTOP | wxBORDER_SUNKEN);
    wxPanel* SearchPn = new wxPanel(LeftPanelCt);
    SearchCtrl = new wxSearchCtrl(SearchPn, 558, wxT(""), wxPoint(0, 0), wxSize(-1, -1));
    wxBitmapButton* refreshBtn = new wxBitmapButton(SearchPn, 555, refresh);
    SearchListPn = new wxPanel(LeftPanelCt, wxID_ANY, wxPoint(0, 0), wxSize(-1, 25));
    SearchList = new wxListBox(SearchListPn, 559, wxPoint(0, 0), wxSize(100, 25));
    NotesLabel = new wxStaticText(LeftPanelCt, wxID_ANY,
        wxT("\nDay: " + ReadEx->Time() + "\n" + "Max: " + "\n" + "Min: "));
    wxPanel* blank = new wxPanel(LeftPanelCt);
    wxStaticText* TextLabel = new wxStaticText(LeftPanelCt, wxID_ANY, wxT("Note:"));
    Tnote = new wxTextCtrl(LeftPanelCt, wxID_ANY, wxT(""), wxPoint(0, 0), wxSize(0, 0), wxTE_MULTILINE);
    wxPanel* btnNotePn = new wxPanel(LeftPanelCt);
    TnoteBtn1 = new wxButton(btnNotePn, 556, wxT("Modify"),
        wxPoint(0, 0), wxSize(-1, -1));
    TnoteBtn2 = new wxButton(btnNotePn, 557, wxT("Ok"),
        wxPoint(0, 0), wxSize(-1, -1));
    wxNotebook* nb = new wxNotebook(RightPanelCt, -1, wxPoint(-1, -1),
        wxSize(-1, -1), wxNB_BOTTOM);
    wxPanel* grid1 = new wxPanel(nb);
    wxPanel* grid2 = new wxPanel(nb);
    RList = new wxListBox(grid1, wxID_ANY, wxPoint(-1, -1),
        wxSize(this->NotesParent->GetClientSize()));
    m_plot = new mpWindow(grid2, 560);
    mpScaleX* xaxis = new mpScaleX(wxT("Time(h)"), mpALIGN_BOTTOM, false, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(wxT("Voltage(analog)"), mpALIGN_LEFT, false);

    //Set Sizers
    this->SetSizer(PanelContentSizer);
    LeftPanel->SetSizer(LeftPanelSizer);
    RightContent->SetSizer(RightPanelSizer);
    LeftPanelCt->SetSizer(LCtSizer);
    SearchPn->SetSizer(SearchPnSz);
    btnNotePn->SetSizer(btnNotePnSz);
    RightPanelCt->SetSizer(RCtSizer);
    grid1->SetSizer(grid1Sizer);
    grid2->SetSizer(staticChartPn);

    //Add Sizers 
    parent->Add(this, 15, wxEXPAND | wxBOTTOM, 0);
    PanelContentSizer->Add(LeftPanel, 4, wxEXPAND | wxRight, 1);
    PanelContentSizer->Add(RightContent, 8, wxEXPAND | wxALL, 0);
    LeftPanelSizer->Add(m_text, 1, wxEXPAND | wxBOTTOM, 0);
    LeftPanelSizer->Add(LeftPanelCt, 40, wxEXPAND | wxBOTTOM, 0);
    RightPanelSizer->Add(m_text_r, 1, wxEXPAND | wxBOTTOM, 0);
    RightPanelSizer->Add(RightPanelCt, 40, wxEXPAND | wxBOTTOM, 0);
    SearchPnSz->Add(SearchCtrl, 2, wxEXPAND | wxBOTTOM, 0);
    SearchPnSz->Add(refreshBtn, 1, wxEXPAND | wxBOTTOM, 0);
    btnNotePnSz->Add(TnoteBtn1, 1, wxEXPAND | wxBOTTOM, 0);
    btnNotePnSz->Add(TnoteBtn2, 1, wxEXPAND | wxBOTTOM, 0);
    LCtSizer->Add(SearchPn, 1, wxEXPAND | wxBOTTOM, 0);
    LCtSizer->Add(SearchListPn, 0, wxEXPAND | wxBOTTOM, 0);
    LCtSizer->Add(NotesLabel, 1, wxEXPAND | wxBOTTOM, 0);
    LCtSizer->Add(blank, 25, wxEXPAND | wxBOTTOM, 0);
    LCtSizer->Add(TextLabel, 1, wxEXPAND | wxBOTTOM, 0);
    LCtSizer->Add(Tnote, 20, wxEXPAND | wxBOTTOM, 0);
    LCtSizer->Add(btnNotePn, 1, wxEXPAND | wxBOTTOM, 0);
    RCtSizer->Add(nb, 1, wxEXPAND | wxBOTTOM, 0);
    grid1Sizer->Add(RList, 1, wxEXPAND | wxBOTTOM, 0);
    staticChartPn->Add(m_plot, 1, wxEXPAND | wxALL, 2);

    //BackgroundColours
    m_text->SetBackgroundColour("#e7e7e7");
    m_text_r->SetBackgroundColour("#e7e7e7");
    NotesLabel->SetBackgroundColour("#e9e9e9");
    blank->SetBackgroundColour("#e9e9e9");
    SearchListPn->SetBackgroundColour("#e9e9e9");
    TextLabel->SetBackgroundColour("#afafaf");

    //Font
    wxFont sum_font = m_text->GetFont();
    sum_font.SetWeight(wxFONTWEIGHT_BOLD);
    m_text->SetFont(sum_font);    
    wxFont sum_font_r = m_text_r->GetFont();
    sum_font_r.SetWeight(wxFONTWEIGHT_BOLD);
    m_text_r->SetFont(sum_font_r);

    //ChartFont
    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxFont sum_font2 = m_text->GetFont();
    sum_font2.SetWeight(wxFONTWEIGHT_BOLD);
    m_text->SetFont(sum_font2);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);

    //SetMargins
    m_plot->SetMargins(30, 30, 50, 50);

    //SetDrawOutsideMargins
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);

    //Add layer
    m_plot->AddLayer(xaxis);
    m_plot->AddLayer(yaxis);
    m_plot->AddLayer(vectorLayer);
    m_plot->AddLayer(new mpInfoCoords(wxRect(80, 20, 10, 10), wxTRANSPARENT_BRUSH)); //&hatch));
    m_plot->AddLayer(new mpInfoLegend(wxRect(200, 20, 40, 40), wxTRANSPARENT_BRUSH)); //&hatch2));
    //Enable
    Tnote->Enable(false);
    TnoteBtn2->Enable(false);
        
    //notebook add pages
    nb->AddPage(grid1, wxT("  Data"));
    nb->AddPage(grid2, wxT("  Chart"));
    
    //Rlist append data
    curDayDir = ReadEx->Time();
    // Get the data from CSV File
    std::vector<std::vector<std::string> > dataList = ReadEx->readEx(curDayDir, fileDir);
    //Print the content of row by row on screen
    if (dataList.size() > 0) {
        max = dataList[0][3];
        min = dataList[0][3];
    }
    else if (dataList.size() == 0) {
        maxtime.push_back("-");
        maxtime.push_back("-");
        maxtime.push_back("-");
        mintime.push_back("-");
        mintime.push_back("-");
        mintime.push_back("-");
    }
    for (int i = dataList.size() - 1; i >= 0; i--) {
        
        if (stoi(dataList[i][3]) > stoi(max)) {
            max = dataList[i][3];
            maxtime.clear();
            maxtime.push_back(dataList[i][0]);
            maxtime.push_back(dataList[i][1]);
            maxtime.push_back(dataList[i][2]);

        }
        if (stoi(dataList[i][3]) < stoi(min)) {
            min = dataList[i][3];
            mintime.clear();
            mintime.push_back(dataList[i][0]);
            mintime.push_back(dataList[i][1]);
            mintime.push_back(dataList[i][2]);
        }
        stringstream time;
        time << dataList[i][2] << " : " << dataList[i][1] << " : " << dataList[i][0];
        RList->AppendString(time.str() + "                Voltage: " + to_string((stod(dataList[i][3]) / 1023) * 5) + " V");
    }
    NotesLabel->SetLabel("\nDay: " + curDayDir + "\n" 
        + "Max: " + to_string((stod(max) / 1023) * 5) + " V" 
        + "\t" + maxtime[2] + ":" + maxtime[1] + ":" + maxtime[0] + "\n"
        + "Min: " + to_string((stod(min) / 1023) * 5) + " V"
        + "\t" + mintime[2] + ":" + mintime[1] + ":" + mintime[0] + "\n"
        );
    std::vector<std::string> text_note = ReadEx->readText(curDayDir, fileDir);
    if (text_note.size() != 0) {
        for (unsigned int i = 0; i < text_note.size(); i++) {
            Tnote->AppendText(text_note[i] + "\n");
        }
    }
    //Set vector
    for (int i = 0; i < 24; i++) {
        double sum = 0;
        double count = 0;
        for (unsigned int j = 0; j < dataList.size(); j++) {
            if (std::stoi(dataList[j][2]) == i) {
                sum += stoi(dataList[j][3]);
                count += 1;
            }
            else if (std::stoi(dataList[j][2]) != i) break;

        }
        if (count != 0) {
            vectory.push_back(sum / count);
        }
        else if (count == 0) {
            vectory.push_back(0);
        }
        vectorx.push_back(i + 1);
        vectorLayer->SetContinuity(true);
        vectorLayer->SetData(vectorx, vectory);
    }
    m_plot->Fit();
    //Others 
    SearchCtrl->ShowCancelButton(false);
    SearchList->Hide();
}

//Functions
void notesContent::hide() {
    this->Hide();
}
void notesContent::show() {
    this->SetClientSize(this->NotesParent->GetClientSize());
    this->Show();
}
void notesContent::refreshFunc(wxCommandEvent& WXUNUSED(event)) {
    RList->Clear();
    SearchCtrl->Clear();
    curDayDir = ReadEx->Time();
    // Get the data from CSV File
    std::vector<std::vector<std::string> > dataList = ReadEx->readEx(curDayDir, fileDir);
    // Print the content of row by row on screen
    if (dataList.size() > 0) {
        max = dataList[0][3];
        min = dataList[0][3];
    }
    else if (dataList.size() == 0) {
        max = "0";
        min = "0";
        maxtime.clear();
        mintime.clear();
        maxtime.push_back("-");
        maxtime.push_back("-");
        maxtime.push_back("-");
        mintime.push_back("-");
        mintime.push_back("-");
        mintime.push_back("-");
    }
    for (int i = dataList.size() - 1; i >= 0; i--) {
        if (stoi(dataList[i][3]) > stoi(max)) {
            max = dataList[i][3];
            maxtime.clear();
            maxtime.push_back(dataList[i][0]);
            maxtime.push_back(dataList[i][1]);
            maxtime.push_back(dataList[i][2]);

        }
        if (stoi(dataList[i][3]) < stoi(min)) {
            min = dataList[i][3];
            mintime.clear();
            mintime.push_back(dataList[i][0]);
            mintime.push_back(dataList[i][1]);
            mintime.push_back(dataList[i][2]);
        }
        stringstream time;
        time << dataList[i][2] << " : " << dataList[i][1] << " : " << dataList[i][0];
        RList->AppendString(time.str() + "                Voltage: " + to_string((stod(dataList[i][3])/1023) * 5) + " V");
    }
    wxSize s = NotesLabel->GetClientSize();
    NotesLabel->SetLabel("\nDay: " + curDayDir + "\n" 
        + "Max: " + to_string((stod(max) / 1023) * 5) + " V" 
        + "\t" + maxtime[2] + ":" + maxtime[1] + ":" + maxtime[0] + "\n"
        + "Min: " + to_string((stod(min) / 1023) * 5) + " V"
        + "\t" + mintime[2] + ":" + mintime[1] + ":" + mintime[0] + "\n"
    );
    NotesLabel->SetSize(s);
    vectorLayer->Clear();
    vectorx.clear();
    vectory.clear();
    for (int i = 0; i < 24; i++) {
        double sum = 0;
        double count = 0;
        for (unsigned int j = 0; j < dataList.size(); j++) {
            if (std::stoi(dataList[j][2]) == i) {
                sum += stoi(dataList[j][3]);
                count += 1;
            }
            else if (std::stoi(dataList[j][2]) != i) break;
        }
        if (count != 0) {
            vectory.push_back(sum / count);
        }
        else if (count == 0) {
            vectory.push_back(0);
        }
        vectorx.push_back(i + 1);
        vectorLayer->SetContinuity(true);
        vectorLayer->SetData(vectorx, vectory);
    }
    m_plot->Fit();
    Tnote->Clear();
    std::vector<std::string> text_note = ReadEx->readText(curDayDir, fileDir);
    if (text_note.size() != 0) {
        for (unsigned int i = 0; i < text_note.size(); i++) {
            Tnote->AppendText(text_note[i] + "\n");
        }
    }
}
void notesContent::modifiedFunc(wxCommandEvent& WXUNUSED(event)) {
    Tnote->Enable(true);
    TnoteBtn1->Enable(false);
    TnoteBtn2->Enable(true);
}
void notesContent::okFunc(wxCommandEvent& WXUNUSED(event)) {
    Tnote->Enable(false);
    TnoteBtn1->Enable(true);
    TnoteBtn2->Enable(false);
    //Convert wxString to string; 
    wxString a = Tnote->GetValue();
    string b = string(a.mb_str(wxConvUTF8));

    writeNote->writeText(curDayDir, fileDir, b);
}
void notesContent::searchFunc(wxCommandEvent&event) {
    if (event.GetString().Length() >= 5) {
        SearchCtrl->ShowCancelButton(true);
    }
    else if (event.GetString().Length() < 5) {
        SearchCtrl->ShowCancelButton(false);
    }
    std::vector<std::string> allDays = ReadEx->readAllDays(fileDir);
    bool checkExist = false;
    for (unsigned int i = 0; i < allDays.size(); i++) {
        if (allDays[i] == event.GetString()) checkExist = true;
    }
    if (checkExist) {
        SearchList->Clear();
        SearchList->Show();
        SearchList->SetSize(SearchListPn->GetClientSize());
        SearchList->AppendString(event.GetString());
        SearchList->Update();
    }
    else if (!checkExist && event.GetString().Length() > 0) {
        SearchList->Clear();
        SearchList->Show();
        SearchList->SetSize(SearchListPn->GetClientSize());
        SearchList->AppendString("none");
        SearchList->Update();
    }
    else if (!checkExist && event.GetString().Length() == 0) {
        SearchList->Hide();
    }
}
void notesContent::onClickSearchListFunc(wxCommandEvent& WXUNUSED(event)) {
    if (SearchList->GetString(0) != "none") {
        SearchList->Hide();
        Tnote->Clear();
        RList->Clear();
        string a = SearchList->GetString(0).ToStdString();
        std::vector<std::vector<std::string> > dataList = ReadEx->readEx(a, fileDir);
        curDayDir = a;
        //Print the content of row by row on screen
        if (dataList.size() > 0) {
            max = dataList[0][3];
            min = dataList[0][3];
        }
        else if (dataList.size() == 0) {
            max = "0";
            min = "0";
            maxtime.clear();
            mintime.clear();
            maxtime.push_back("-");
            maxtime.push_back("-");
            maxtime.push_back("-");
            mintime.push_back("-");
            mintime.push_back("-");
            mintime.push_back("-");
        }
        for (int i = dataList.size() - 1; i >= 0; i--) {
            if (stoi(dataList[i][3]) > stoi(max)) {
                max = dataList[i][3];
                maxtime.clear();
                maxtime.push_back(dataList[i][0]);
                maxtime.push_back(dataList[i][1]);
                maxtime.push_back(dataList[i][2]);

            }
            if (stoi(dataList[i][3]) < stoi(min)) {
                min = dataList[i][3];
                mintime.clear();
                mintime.push_back(dataList[i][0]);
                mintime.push_back(dataList[i][1]);
                mintime.push_back(dataList[i][2]);
            }
            stringstream time;
            time << dataList[i][2] << " : " << dataList[i][1] << " : " << dataList[i][0];
            RList->AppendString(time.str() + "                Voltage: " + to_string((stod(dataList[i][3]) / 1023) * 5) +" V");
        }
        std::vector<std::string> text_note = ReadEx->readText(a, fileDir);
        if (text_note.size() != 0) {
            for (unsigned int i = 0; i < text_note.size(); i++) {
                Tnote->AppendText(text_note[i] + "\n");
            }
        }
        wxSize s = NotesLabel->GetClientSize();
        NotesLabel->SetLabel("\nDay: " + SearchList->GetString(0) + "\n" 
            + "Max: " + to_string((stod(max) / 1023) * 5) + " V" 
            + "\t" + maxtime[2] + ":" + maxtime[1] + ":" + maxtime[0] + "\n"
            + "Min: " + to_string((stod(min) / 1023) * 5) + " V"
            + "\t" + mintime[2] + ":" + mintime[1] + ":" + mintime[0] + "\n"
        );
        NotesLabel->SetSize(s);
        vectorLayer->Clear();
        vectorx.clear();
        vectory.clear();
        for (int i = 0; i < 24; i++) {
            double sum = 0;
            double count = 0;
            for (unsigned int j = 0; j < dataList.size(); j++) {
                if (std::stoi(dataList[j][2]) == i) {
                    sum += stoi(dataList[j][3]);
                    count += 1;
                }
                else if (std::stoi(dataList[j][2]) != i) break;
            }
            if (count != 0) {
                vectory.push_back(sum / count);
            }
            else if (count == 0) {
                vectory.push_back(0);
            }
            vectorx.push_back(i + 1);
            vectorLayer->SetContinuity(true);
            vectorLayer->SetData(vectorx, vectory);
        }
        m_plot->Fit();
    }
}