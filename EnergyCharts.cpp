#include "EnergyCharts.h"

//IMPLEMENT_DYNAMIC_CLASS(EnergyCharts, wxPanel)
BEGIN_EVENT_TABLE(EnergyCharts, wxPanel)
EVT_BUTTON(6666, EnergyCharts::onPlus)
EVT_BUTTON(6667, EnergyCharts::onDecrease)
EVT_BUTTON(6668, EnergyCharts::onSet)
EVT_BUTTON(6669, EnergyCharts::onRefresh)
EVT_TIMER(5555, EnergyCharts::OnProgressTimer)
END_EVENT_TABLE()

EnergyCharts::EnergyCharts(wxPanel* parentpn, CSerialCommHelper* portCom, string* filePath, int& saveInterval)
    : wxPanel(parentpn, -1, wxPoint(-1, -1), wxSize(-1, -1))
{
    //Parents setting
    com = portCom;
    fileDir = filePath;

    // Create a mpFXYVector layer
    vectorLayerTL = new mpFXYVector(_("tl"));
    vectorLayerTR = new mpFXYVector(_("tr"));
    vectorLayerBL = new mpFXYVector(_("bl"));
    vectorLayerBR = new mpFXYVector(_("br"));
    vectorLayerV = new mpFXYVector(_("Voltage"));
        //Top Left
        vectorLayerTL->SetContinuity(true);
        wxPen vectorpen1(*wxBLUE, 2, wxPENSTYLE_SOLID);
        vectorLayerTL->SetPen(vectorpen1);
        vectorLayerTL->SetDrawOutsideMargins(false);
        //Top Right 
        vectorLayerTR->SetContinuity(true);
        wxPen vectorpen2(*wxRED, 2, wxPENSTYLE_SOLID);
        vectorLayerTR->SetPen(vectorpen2);
        vectorLayerTR->SetDrawOutsideMargins(false);
        //Bottom Left
        vectorLayerBL->SetContinuity(true);
        wxPen vectorpen3(*wxGREEN, 2, wxPENSTYLE_SOLID);
        vectorLayerBL->SetPen(vectorpen3);
        vectorLayerBL->SetDrawOutsideMargins(false);
        //Bottom Right
        vectorLayerBR->SetContinuity(true);
        wxPen vectorpen4(*wxYELLOW, 2, wxPENSTYLE_SOLID);
        vectorLayerBR->SetPen(vectorpen4);
        vectorLayerBR->SetDrawOutsideMargins(false);
        //Voltage
        vectorLayerV->SetContinuity(true);
        wxPen vectorpen5(*wxBLACK, 2, wxPENSTYLE_SOLID);
        vectorLayerV->SetPen(vectorpen5);
        vectorLayerV->SetDrawOutsideMargins(false);
        //
    //Definition
    m_plot = new mpWindow(this, 5555);
    m_log = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(0, 0));
    wxStaticText* m_text = new wxStaticText(m_log, -1, wxT("Settings:"),
        wxPoint(0, 0), wxSize(-1, -1), wxALIGN_LEFT);
    mpScaleX* xaxis = new mpScaleX(wxT("Time(s)"), mpALIGN_BOTTOM, true, mpX_NORMAL);
    mpScaleY* yaxis = new mpScaleY(wxT("Voltage/LightIntensity(analog)"), mpALIGN_LEFT, true);
    wxPanel* m_logCt = new wxPanel(m_log, wxID_ANY);
    wxPanel* m_logLCt = new wxPanel(m_logCt, wxID_ANY, wxPoint(-1, -1),
        wxSize(-1, -1), wxBORDER_SUNKEN);
    wxPanel* m_logRCt = new wxPanel(m_logCt, wxID_ANY, wxPoint(-1, -1),
        wxSize(-1, -1), wxBORDER_SUNKEN);
    comLabel = new wxTextCtrl(m_logRCt, wxID_ANY, "Gate: " + com->GetPort() + "\n",
        wxPoint(0, 0), wxSize(-1, 50), wxTE_MULTILINE);
    wxStaticText* m_sliderLable = new wxStaticText(m_logLCt, wxID_ANY, " -Angle adjustment: (o)",
        wxPoint(0, 0), wxSize(120, -1));
    m_slider = new wxSlider(m_logLCt, wxID_ANY, 90, 0, 180, wxPoint(0, 15),
        wxSize(150, -1), wxSL_LABELS);
    Setbutton = new wxButton(m_logLCt, 6668, "turn on",
        wxPoint(155, 30), wxSize(50, -1));
    Refreshbutton = new wxButton(m_logLCt, 6669, "Refresh",
        wxPoint(215, 30), wxSize(50, -1));

    //Font
    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxFont sum_font = m_text->GetFont();
    sum_font.SetWeight(wxFONTWEIGHT_BOLD);
    m_text->SetFont(sum_font);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);

    //Timer
    saveIntervalPoint = &saveInterval;
    static const int INTERVAL = 1000; // milliseconds
    m_timer = new wxTimer(this, 5555);
    m_timer->Start(INTERVAL);

    //SetDrawOutsideMargins
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);

    //SetMargins
    m_plot->SetMargins(30, 30, 50, 50);

    //Add layer
    m_plot->AddLayer(xaxis);
    m_plot->AddLayer(yaxis);
    m_plot->AddLayer(vectorLayerTL);
    m_plot->AddLayer(vectorLayerTR);
    m_plot->AddLayer(vectorLayerBL);
    m_plot->AddLayer(vectorLayerBR);
    m_plot->AddLayer(vectorLayerV);
    m_plot->AddLayer(new mpInfoCoords(wxRect(80, 20, 10, 10), wxTRANSPARENT_BRUSH)); //&hatch));
    m_plot->AddLayer(new mpInfoLegend(wxRect(200, 20, 40, 40), wxTRANSPARENT_BRUSH)); //&hatch2));

    
    //Sizers
    wxBoxSizer* parentsz = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* m_logSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* m_logCtSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* m_logRCtSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);

    //SetSizer
    this->SetSizer(topsizer);
    parentpn->SetSizer(parentsz);
    m_log->SetSizer(m_logSizer);
    m_logCt->SetSizer(m_logCtSizer);
    m_logRCt->SetSizer(m_logRCtSizer);

    //BackgroundColor
    m_text->SetBackgroundColour("#afafaf");
    m_logLCt->SetBackgroundColour("#e7e7e7");
    comLabel->SetBackgroundColour("white");

    //Add Sizer
    parentsz->Add(this, 1, wxEXPAND);
    m_logSizer->Add(m_text, 1, wxEXPAND);
    m_logSizer->Add(m_logCt, 11, wxEXPAND);
    m_logCtSizer->Add(m_logLCt, 7, wxEXPAND | wxALL, 0);
    m_logCtSizer->Add(m_logRCt, 5, wxEXPAND | wxALL, 0);
    m_logRCtSizer->Add(comLabel, 1, wxEXPAND | wxALL, 0);
    topsizer->Add(m_plot, 8, wxEXPAND);
    topsizer->Add(m_log, 4, wxEXPAND | wxALL, 1);

    //Enable
    comLabel->Enable(false);
    m_slider->Enable(false);

}
//Functions 
EnergyCharts::~EnergyCharts() {
    m_timer->Stop();
}
void EnergyCharts::onPlus(wxCommandEvent& WXUNUSED(event)) {
    wxPen vectorpen2(*wxRED, 2, wxPENSTYLE_SOLID);
    vectorLayerTL->SetPen(vectorpen2);
    m_plot->UpdateAll();

}
void EnergyCharts::onDecrease(wxCommandEvent& WXUNUSED(event)) {
    wxPen vectorpen2(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayerTL->SetPen(vectorpen2);
    m_plot->UpdateAll();
}
void EnergyCharts::onSet(wxCommandEvent& WXUNUSED(event)) {
    if (!m_slider->IsEnabled()) {
        m_slider->Enable(true);
        com->Write("a", 1);
        Setbutton->SetLabel("Turn off");
    }
    else if (m_slider->IsEnabled()) {
        m_slider->Enable(false);
        com->Write("b", 1);
        Setbutton->SetLabel("Turn on");
    }
}
void EnergyCharts::onRefresh(wxCommandEvent& WXUNUSED(event)) {
    vectorxTL.clear();
    vectoryTL.clear();
    vectorxTR.clear();
    vectoryTR.clear();
    vectorxBL.clear();
    vectoryBL.clear();
    vectorxBR.clear();
    vectoryBR.clear();
    vectorxV.clear();
    vectoryV.clear();
    vectorLayerTL->Clear();
    vectorLayerTR->Clear();
    vectorLayerBL->Clear();
    vectorLayerBR->Clear();
    vectorLayerV->Clear();
    comLabel->Clear();
    
}
void EnergyCharts::OnProgressTimer(wxTimerEvent& WXUNUSED(event)){
    srand(time(NULL));
    now = time(0);
    ltm = gmtime(&now);
    comLabel->Clear();
    comLabel->AppendText("Gate: " + com->GetPort() + "\t" + "Baud Rate: " 
        + to_string(com->GetBaudRate()) +"\t"+ "Open: " + to_string(com->IsConnection()) + "\n");
    comLabel->AppendText("Time: " + to_string(ltm->tm_hour + 7) + "h : " 
        + to_string(ltm->tm_min) + "m : " + to_string(ltm->tm_sec) + "s\n");

    if (com->IsConnection()) {
        com->Write("d", 1);
        com->Read_Upto(data, '?', alCount, 800);
        stringstream s(data);
        std::string word = "";
        std::vector<string> dataVector;
        while (getline(s, word, ',')) {
            dataVector.push_back(word);
        }
        if (ltm->tm_sec == 0 && dataVector.size() == 7) {
            vectorxTL.clear();
            vectoryTL.clear();
            vectorLayerTL->SetContinuity(false);
            vectorxTL.push_back(ltm->tm_sec);
            resy = stoi(dataVector[0]);
            vectoryTL.push_back(resy);
            vectorLayerTL->SetData(vectorxTL, vectoryTL);
            //
            vectorxTR.clear();
            vectoryTR.clear();
            vectorLayerTR->SetContinuity(false);
            vectorxTR.push_back(ltm->tm_sec);
            resy = stoi(dataVector[1]);
            vectoryTR.push_back(resy);
            vectorLayerTR->SetData(vectorxTR, vectoryTR);
            //
            vectorxBL.clear();
            vectoryBL.clear();
            vectorLayerBL->SetContinuity(false);
            vectorxBL.push_back(ltm->tm_sec);
            resy = stoi(dataVector[2]);
            vectoryBL.push_back(resy);
            vectorLayerBL->SetData(vectorxBL, vectoryBL);
            //
            vectorxBR.clear();
            vectoryBR.clear();
            vectorLayerBR->SetContinuity(false);
            vectorxBR.push_back(ltm->tm_sec);
            resy = stoi(dataVector[3]);
            vectoryBR.push_back(resy);
            vectorLayerBR->SetData(vectorxBR, vectoryBR);
            //
            vectorxV.clear();
            vectoryV.clear();
            vectorLayerV->SetContinuity(false);
            vectorxV.push_back(ltm->tm_sec);
            resy = stoi(dataVector[4]);
            vectoryV.push_back(resy);
            vectorLayerV->SetData(vectorxV, vectoryV);

        }
        else if (ltm->tm_sec > 0 && dataVector.size() == 7) {
            vectorLayerTL->SetContinuity(true);
            vectorLayerTR->SetContinuity(true);
            vectorLayerBL->SetContinuity(true);
            vectorLayerBR->SetContinuity(true);
            vectorLayerV->SetContinuity(true);

            vectorxTL.push_back(ltm->tm_sec);
            resy = stoi(dataVector[0]);
            vectoryTL.push_back(resy);
            vectorLayerTL->SetData(vectorxTL, vectoryTL);
            //
            vectorxTR.push_back(ltm->tm_sec);
            resy = stoi(dataVector[1]);
            vectoryTR.push_back(resy);
            vectorLayerTR->SetData(vectorxTR, vectoryTR);
            //
           
            vectorxBL.push_back(ltm->tm_sec);
            resy = stoi(dataVector[2]);
            vectoryBL.push_back(resy);
            vectorLayerBL->SetData(vectorxBL, vectoryBL);
            //
            
            vectorxBR.push_back(ltm->tm_sec);
            resy = stoi(dataVector[3]);
            vectoryBR.push_back(resy);
            vectorLayerBR->SetData(vectorxBR, vectoryBR);
            //
            
            vectorxV.push_back(ltm->tm_sec);
            resy = stoi(dataVector[4]);
            vectoryV.push_back(resy);
            vectorLayerV->SetData(vectorxV, vectoryV);

        }
        
        m_plot->Fit();
        //
        if (dataVector.size() == 7) {
            comLabel->AppendText("Horizontal: " + dataVector[5] + "*" "\n");
            comLabel->AppendText("Vertical: " + dataVector[6] + "*" "\n");
        }
        if (saveCycleCount * 1000 < *saveIntervalPoint) {
            saveCycleCount += 1;
        }
        if (saveCycleCount * 1000 >= *saveIntervalPoint && dataVector.size() == 7) {
            saveCycleCount = 0;
            string_name = dataVector[4];
            Excel->writeEx(string_name, fileDir);
            Excel->writeAllDays(fileDir);
        }
    }

    else if (!com->IsConnection()) {
        vectorxTL.clear();
        vectoryTL.clear();
        vectorxTR.clear();
        vectoryTR.clear();
        vectorxBL.clear();
        vectoryBL.clear();
        vectorxBR.clear();
        vectoryBR.clear();
        vectorxV.clear();
        vectoryV.clear();
        vectorLayerTL->Clear();
        vectorLayerTR->Clear();
        vectorLayerBL->Clear();
        vectorLayerBR->Clear();
        vectorLayerV->Clear();
        //m_plot->Fit();
    }
}