#include <wx/wx.h>
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <map>
#include <string>

class MyApp : public wxApp
{
public:
    virtual bool OnInit() { return true; }
};

wxIMPLEMENT_APP_NO_MAIN(MyApp);

static std::map<int, wxFrame*> windows;
static int nextWindowId = 1;

extern "C" int CreateWindow(const char* title, int width, int height)
{
    if (!wxTheApp) {
        wxDISABLE_DEBUG_SUPPORT();
        wxApp* app = new wxApp();
        wxApp::SetInstance(app);
        int argc = 0;
        char** argv = nullptr;
        if (!wxEntryStart(argc, argv) || !app->CallOnInit()) {
            return -1;
        }
    }

    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, wxString(title, wxConvUTF8), wxDefaultPosition, wxSize(width, height));
    int windowId = nextWindowId++;
    windows[windowId] = frame;
    frame->Show();
    return windowId;
}

extern "C" void AddButton(int windowId, const char* label, int x, int y, int width, int height, void(*callback)(int), int callbackID)
{
    auto it = windows.find(windowId);
    if (it == windows.end()) return;

    wxButton* button = new wxButton(it->second, wxID_ANY, wxString(label, wxConvUTF8), wxPoint(x, y), wxSize(width, height));
    // Capture `callback` and `callbackID` in the lambda
    button->Bind(wxEVT_BUTTON, [callback, callbackID](wxCommandEvent&) {
        if (callback) callback(callbackID);
    });
}

extern "C" void WxShowWindow(int windowId)
{
    auto it = windows.find(windowId);
    if (it == windows.end()) return;
    it->second->Show();
}

extern "C" void WxCloseWindow(int windowId)
{
    auto it = windows.find(windowId);
    if (it == windows.end()) return;
    it->second->Close();
    windows.erase(it);
}

extern "C" void RunEventLoop()
{
    if (wxTheApp) wxTheApp->OnRun();
}

extern "C" void Cleanup()
{
    if (wxTheApp) {
        wxTheApp->OnExit();
        wxEntryCleanup();
    }
}
