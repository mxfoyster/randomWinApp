//about dialog code
void AboutDlg(HWND hwnd)
{
            HINSTANCE hInstance = GetModuleHandle(NULL);
            MessageBox(hwnd, "PADDLE LENGTH CALCULATOR v1.00\n\nBy Mark Foyster.\n\nCreated April 2022", "About", MB_OK | MB_ICONINFORMATION);
}

//exit dialog
int CloseDlg(HWND hwnd)
{
            int mbResult;
			HINSTANCE hInstance = GetModuleHandle(NULL);
            mbResult = MessageBox(hwnd, "Are you sure you wish to leave?", "Quit", MB_YESNO | MB_ICONQUESTION);
            return mbResult;
}

//Instructions dialog
int InstructionsDlg(HWND hwnd)
{
            int mbResult;
			HINSTANCE hInstance = GetModuleHandle(NULL);
            mbResult = MessageBox(hwnd, "Enter your height in Centimetres into the box\n\nThen select the type of paddling.\n\nPress CALCULATE and your result will be displayed", "INSTRUCTIONS", MB_OK | MB_ICONINFORMATION);
            return mbResult;
}