#include "Main.h"
#include "TaskClass1.h"
#include <wx/wx.h>
#include <wx/list.h>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
/*
hello, this is a gui application used for storing tasks. think of it like a list one would write task they would want to complete in order to remember them.
each task is also associated with a date.i will now write things i want this program to do once finished and things i have already implemented from that list.
these lists were created after this project has been in development for a while so they dont show the full roadmap followed.
done:
basic gui
add button
listbox with task names
delete button
clear button
to do:
create a class to make objects that contain name and date for tasks
implement task class
add edit function for date of a task
add edit function for name of task ( probably would require object deletion and new object creation )
learn sizebox to make the window resizable
decide if we need wxList or not so that i can delete that line
*/

bool containsUnderscore(const wxString& str)
{
    return str.Find('_') != wxNOT_FOUND;
}

Main::Main(const wxString& title):wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);// creates  a basic panel
//title
    wxStaticText* titleCard = new wxStaticText(panel, wxID_ANY, "Task List", wxPoint(0, 20), wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);// Creates a title displayed within frame, centered and bold with big font
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(titleCard, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    panel->SetSizerAndFit(sizer);
    wxFont titleFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD, true);
    titleCard->SetFont(titleFont);
//extras
    taskList = new wxList();// list might be useful in later  stage of project, right now unused
//temp
    panel->Bind(wxEVT_MOTION, &Main::MousePos, this);//possible delete later, used to have a visual on possible control positions
//controls construction
    listBox = new wxListBox(panel, wxID_ANY, wxPoint(80, 125), wxSize (610, 440), 0, NULL, wxLB_MULTIPLE | wxLB_HSCROLL | wxLB_NEEDED_SB);//list box
    wxCheckBox* addCheck = new wxCheckBox(panel, wxID_ANY, "Set Parameters", wxPoint(675, 96));
    wxButton* addButton = new wxButton(panel, wxID_ANY, "Add Task", wxPoint(480, 90), wxSize(180, -1));//buttons
    wxButton* deleteButton = new wxButton(panel, wxID_ANY, "Delete Selected Tasks", wxPoint(80, 570), wxSize(180, -1));
    wxButton* clearButton = new wxButton(panel, wxID_ANY, "Clear ALL Tasks", wxPoint(280, 570), wxSize(180, -1));
    inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(80, 90), wxSize(370, -1), wxTE_PROCESS_ENTER);//input field
//initialization configs
    addCheck->SetValue(true);
    taskList->DeleteContents(true);
//events
    inputField->Bind(wxEVT_TEXT_ENTER, &Main::OnTextEnter, this);
    addButton->Bind(wxEVT_BUTTON, &Main::OnTextEnter, this);
    clearButton->Bind(wxEVT_BUTTON, &Main::ClearTasks, this);
    deleteButton->Bind(wxEVT_BUTTON, &Main::DeleteSelection, this);
//standards
    std::ifstream file("tasks.txt");
        std::string line;
        listBox->Clear();
        while(std::getline(file, line))
        {
            listBox->Append(wxString(line));
        }
    file.close();

    panel->SetFocus();//sets focus to panel on initialize
    wxStatusBar* statusBar = CreateStatusBar();// creates a status bar for logs
    statusBar->SetDoubleBuffered(true);// this is to get rid of flickering
    wxLogStatus("Log");
}

void Main::MousePos(wxMouseEvent& evt)//this is a method to return mouse position used during the creation proccess of this app
{
    wxPoint mouseP = evt.GetPosition();
    wxString str = wxString::Format("x=  %d  y= %d", mouseP.x, mouseP.y);
    wxLogStatus(str);
}
void Main::OnTextEnter(wxCommandEvent&)//method that adds typed text in listbox and clears textctrl
{
    wxString str = inputField->GetValue();
    if (containsUnderscore(str)){//underscores are not allowed to avoid crashes. might get fixed at later date. this would require a different way of using the taskclass
        wxMessageBox("Task name contains underscore(s) '_', which is not allowed in the current version of this app. Please delete the underscore(s) and proceed.", "Warning",
                     wxOK | wxICON_WARNING, this);
        return;
    }
    std::string stdStr = str.ToStdString();
    //here i will probably create a class object with stdStr------------------------------------------------------------------------
    inputField->Clear();
    if (!str.IsEmpty()){ //adds text to list only if its not empty
        listBox->Append(str);//adds tasks to listbox
        std::ofstream file("tasks.txt", std::ios::app);//adds same task to file by appending to existing file
            file << str << std::endl;
        file.close();
    }
}
void Main::ClearTasks(wxCommandEvent& evt)
{
    listBox->Clear();
    std::ofstream file("tasks.txt");//overwrites file with empty one. another way is the parameter std::ios::trunc
        file << "";
    file.close();
}
void Main::DeleteSelection(wxCommandEvent& evt)
{
    wxArrayInt selections;
    listBox->GetSelections(selections);
    if (selections.GetCount() == 0 )
    {
        wxMessageBox("No tasks were selected", "Error", wxOK | wxICON_WARNING, this);//if button is pressed without any selections
        return;
    }
    for (int i = selections.GetCount() - 1; i >= 0; --i)//deletes selections from bottom up
    {
        listBox->Delete(selections[i]);
    }
    std::ofstream file("tasks.txt");
        for (size_t i = 0; i < listBox->GetCount(); ++i)// after listbox is updated after deletion this just overwrites the txt file with a new one containing items only in the updated listbox
        {
            file << listBox->GetString(i).ToStdString() << std::endl;
        }
    file.close();
    wxMessageBox("Tasks Deleted", "Complete", wxOK | wxICON_INFORMATION, this);
}
