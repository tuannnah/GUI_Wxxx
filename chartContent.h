#pragma once
#include <wx/wx.h>
#include "EnergyCharts.h"
#include "SerialCommHelper.h"
using namespace std;
class chartContent : wxPanel
{
public:
	chartContent(wxBoxSizer* parent, wxPanel* parentpn, CSerialCommHelper* portCom, string* filePath, int& saveInterval);
	string* fileDir;
	wxPanel* chartParent;
	wxPanel* PanelContent;
	EnergyCharts* chart1;
	void hide();
	void show();

};

