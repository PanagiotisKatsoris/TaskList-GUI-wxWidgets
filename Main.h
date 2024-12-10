#ifndef MAIN_H
#define MAIN_H
#include <wx/wx.h>
#include <wx/list.h>
#include <string>
#include <vector>
#include <array>
#include "TaskClass1.h"

class Main:public wxFrame
{
    public:
        Main(const wxString& title);

    protected:

    private:
        wxList* taskList;
        wxTextCtrl* inputField;
        wxListBox* listBox;

        void MousePos(wxMouseEvent& evt);
        void OnTextEnter(wxCommandEvent& evt);
        void ClearTasks(wxCommandEvent& evt);
        void DeleteSelection(wxCommandEvent& evt);
};

bool containsUnderscore(const wxString& str);
std::vector<TaskClass1> taskObjects;
std::array<int, 3> tempDateTemplate;

#endif // MAIN_H
