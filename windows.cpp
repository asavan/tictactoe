#include "button.h"
#include <memory>
#include <Windows.h>
#include <WindowsX.h>
#include <string>
#include <tchar.h>
static constexpr int button_size = 40;
static constexpr int field_size = 15;
HWND hMainWnd = 0;
INT_PTR CALLBACK DlgProc(HWND hwd, UINT msg, WPARAM wp, LPARAM lp);

std::unique_ptr<field> main_field;
static std::unique_ptr<field> InitMainWindow() {
    return std::make_unique<field>(field_size);
}

int MakeXY(int z) {
    return 5 + z * button_size;
}
void button::paint_cross() {
    Edit_SetText(hW, _T("X"));
    // EnableWindow(hW, false);
}
void button::paint_zero() {
    Edit_SetText(hW, _T("0"));
    // EnableWindow(hW, false);
}
void Victory(bool is_first) {
    std::string str;
    if (is_first) {
        str += "CROSS ";
    } else {
        str += "ZERO ";
    }
    str += "WIN";
	std::wstring stemp = std::wstring(str.begin(), str.end());
    MessageBox(hMainWnd, stemp.c_str(), _T("Победа"), MB_OK);
    EndDialog(hMainWnd, 0);
    DialogBox(NULL, _T("Ex4_Dlg"), HWND_DESKTOP, DlgProc);
}

void button::InitWindow() {
    hW = CreateWindow(_T("button"), NULL, WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
                      MakeXY(i), MakeXY(j), button_size, button_size, hMainWnd, (HMENU)BN_ID, NULL, NULL);
}

INT_PTR CALLBACK DlgProc(HWND hwd, UINT msg, WPARAM wp, LPARAM /*lp*/) {
    switch (msg) {
    case WM_CLOSE:
        main_field.reset();
        EndDialog(hwd, 0);
        break;
    case WM_INITDIALOG:
        hMainWnd = hwd;
        main_field = InitMainWindow();
        SetWindowPos(hwd, NULL, 0, 0, button_size * main_field->size() + 20, button_size * main_field->size() + 20 + 20, SWP_NOZORDER | SWP_NOMOVE);
        SetFocus(hwd);
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case IDCANCEL:
            EndDialog(hwd, 0);
            DialogBox(NULL, _T("Ex4_Dlg"), HWND_DESKTOP, DlgProc);
            break;
        default:
            if (LOWORD(wp) >= 1000 && LOWORD(wp) < 2516)
                main_field->push(LOWORD(wp));
            break;
        }
    }
    return FALSE;
}

int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int /*nShowCmd*/) {
    DialogBox(hInst, _T("Ex4_Dlg"), HWND_DESKTOP, DlgProc);
    return 0;
}
