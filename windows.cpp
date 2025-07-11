#include "button.h"
#include <Windows.h>
#include <WindowsX.h>
#include <string>
static size_t button_size = 40;
static size_t field_size = 15;
HWND hMainWnd= 0;
INT_PTR CALLBACK DlgProc(HWND hwd, UINT msg, WPARAM wp, LPARAM lp) ;

static field * main_field = NULL;
static field * InitMainWindow()
{
	return new field(field_size);
}

int MakeXY (size_t z)
{
	return 5+z*button_size;
}
void button::paint_cross()
{
	Edit_SetText( hW, "X");
	//EnableWindow(hW, false);
}
void button::paint_zero()
{
	Edit_SetText( hW, "0");
	//EnableWindow(hW, false);

}
void Victory(bool is_first)
{
	std::string str;
	if (is_first) str+= "CROSS ";
	else str+= "ZERO ";
	str+= "WIN";
	MessageBox(hMainWnd, str.c_str(), "Победа", MB_OK);
	EndDialog(hMainWnd , 0);
	DialogBox(NULL, "Ex4_Dlg", HWND_DESKTOP, DlgProc );


}
void button::InitWindow(){
hW = CreateWindow("button",NULL ,WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE, 
				  MakeXY(i),MakeXY(j),button_size,button_size,hMainWnd,(HMENU)BN_ID,NULL,NULL);
}

INT_PTR CALLBACK DlgProc(HWND hwd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) 
	{
	case WM_CLOSE:
		delete main_field;
		EndDialog(hwd, 0);
		break;
	case WM_INITDIALOG: 
		hMainWnd = hwd;
		main_field = InitMainWindow();
		SetWindowPos(hwd, NULL, 0, 0, button_size * main_field->size() +20 , button_size * main_field->size() +20 +20 , SWP_NOZORDER |SWP_NOMOVE);
		SetFocus(hwd);
		return TRUE;
	case WM_COMMAND:
	  	switch(LOWORD(wp))
		{
		case IDCANCEL:
			EndDialog(hwd, 0);
			DialogBox(NULL, "Ex4_Dlg", HWND_DESKTOP, DlgProc );
			break;
		default:
			if (LOWORD(wp) >= 1000 && LOWORD(wp) < 2516)
				main_field->push(LOWORD(wp));
			break;
		}
	}
	return FALSE;
}

int APIENTRY WinMain(__in HINSTANCE hInst, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd ) {
	DialogBox(hInst, "Ex4_Dlg", HWND_DESKTOP, DlgProc );
	return 0; 
}
