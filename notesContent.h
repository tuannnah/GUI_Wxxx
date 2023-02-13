#pragma once
#include <wx/wx.h>
#include <string>
#include <wx/notebook.h>
#include <wx/srchctrl.h>
#include "RandWExcel.h"
#include"mathplot.h"

class notesContent : public wxPanel
{
public:
	string* fileDir;
	notesContent(wxBoxSizer* parent, wxPanel* parentpn, string* filePath);
	wxPanel* NotesParent;
	wxBoxSizer* PanelContentSizer;
	CSVReader* ReadEx;
	CSVWriter* writeNote;
	wxListBox* LList;
	wxListBox* RList;
	wxPanel* LeftPanelCt;
	wxSearchCtrl* SearchCtrl;
	wxStaticText* NotesLabel;
	//
	wxBitmapButton* refreshBtn;
	//
	wxTextCtrl* Tnote;
	//
	wxButton* TnoteBtn1;
	wxButton* TnoteBtn2;
	//
	string curDayDir;
	string* note;
	wxPanel* SearchListPn;
	wxListBox* SearchList;
	//
	mpWindow* m_plot;
	mpFXYVector* vectorLayer;
	std::vector<double> vectorx, vectory;
	std::string max = "0";
	std::vector<std::string> maxtime;
	std::string min = "0";
	std::vector<std::string> mintime;

public:
	void hide();
	void show();
	DECLARE_EVENT_TABLE()
	void refreshFunc(wxCommandEvent& WXUNUSED(event));
	void modifiedFunc(wxCommandEvent& WXUNUSED(event));
	void okFunc(wxCommandEvent& WXUNUSED(event));
	void searchFunc(wxCommandEvent& WXUNUSED(event));
	void onClickSearchListFunc(wxCommandEvent& WXUNUSED(event));

};

