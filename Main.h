#ifndef MAIN_H
#define MAIN_H
#include <wx/wx.h>
#include <wx/list.h>
#include <string>
#include <array>

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

#endif // MAIN_H
