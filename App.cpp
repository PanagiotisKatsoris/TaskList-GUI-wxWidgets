#include "App.h"
#include "Main.h"
#include "TaskClass1.h"
#include <wx/wx.h>

bool App::OnInit()
{
    Main* main = new Main("TaskList");//basic settings for initializing
    main->SetClientSize(800, 600);
    main->Center();//centers the window
    main->Show();//shows the window :D
    return true;
}
wxIMPLEMENT_APP(App);//basically int main()
