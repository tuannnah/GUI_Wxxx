#pragma once
#include <wx/wx.h>
#include "SerialCommHelper.h"
#include <stdlib.h>     //for using the function sleep
#include "RandWExcel.h"
#include "setBaudRateDlg.h"

using namespace std;
class settingContent : public wxPanel
{
public:
	CSerialCommHelper* com;
	string* fileDir;
	settingContent(wxBoxSizer* parent, wxPanel* parentpn, CSerialCommHelper* sePort, string& filePath, int& saveInterval);
	wxPanel* NotesParent;
	wxPanel* PanelContent;
	wxBoxSizer* PanelContentSizer;
	wxListBox* settingLabels;
	wxTextCtrl* txtSend;
	wxTextCtrl* txtRx;
	wxButton* openPortBtn;
	wxButton* setBaudBtn;
	setBaudRateDlg* setBaudDialog;
	wxPanel* RightContent1;
	wxPanel* RightContent2;
	wxPanel* RightContent3;
	wxPanel* RightContent4;
	wxTextCtrl* fileHrefTextCtrl;
	CSVWriter* CookieW;
	CSVReader* CookieR;
	wxChoice* saveCycleChoice;
	wxButton* saveCycleBtn;
	int* saveIntervalPt;
	wxString saveCycleList1[4] = { "1sec", "5sec", "1min", "30min" };
	int saveCycleList2[4] = { 1000, 5000, 60000, 1800000 };

	void hide();
	void show();
	DECLARE_EVENT_TABLE()
	void onSelect(wxCommandEvent& WXUNUSED(event));
	void onSetPort(wxCommandEvent& WXUNUSED(event));
	void onOpenPort(wxCommandEvent& WXUNUSED(event));
	void onSetBaud(wxCommandEvent& WXUNUSED(event));
	void onSetFileRef(wxCommandEvent& WXUNUSED(event));
	void onSetSaveCycle(wxCommandEvent& WXUNUSED(event));

};

