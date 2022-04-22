//about dialog code
void AboutDlg(HWND hwnd)
{
            HINSTANCE hInstance = GetModuleHandle(NULL);
            MessageBox(hwnd, "Random Windows Program v1.00", "About", MB_OK | MB_ICONINFORMATION);
}

//exit dialog
int CloseDlg(HWND hwnd)
{
            int mbResult;
			HINSTANCE hInstance = GetModuleHandle(NULL);
            mbResult =MessageBox(hwnd, "Are you sure you wish to leave?", "Quit", MB_YESNO | MB_ICONQUESTION);
            return mbResult;
}