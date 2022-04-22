#define IDC_HEIGHT_EDIT 500 //text box for height
#define IDC_CHK1 801 //Whitewater paddle radiobutton
#define IDC_CHK2 802 //Touring paddle radiobutton
#define IDC_RESULT_BTN 851 //Calculate Result Button

void HeightBox (HWND hwnd)
{

	static HWND hHeight;
	//We use CreateWindowEx instead of CreateWindow in this case because it gives us a nicer box
	hHeight = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
            WS_CHILD | WS_VISIBLE, 
            200, 40, 100, 25, hwnd, (HMENU)IDC_HEIGHT_EDIT, GetModuleHandle(NULL), NULL);
    
	if(hHeight == NULL) MessageBox(hwnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);
}

void PaddleSelectRadioButtons(HWND hwnd)
{
	static HWND hPaddleWhitewater, hPaddleTouring;
	hPaddleWhitewater = CreateWindow(TEXT("BUTTON"), TEXT("Whitewater "), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
    	200, 80, 100, 25, hwnd, (HMENU) IDC_CHK1, GetModuleHandle(NULL), NULL);
	
	hPaddleTouring = CreateWindow(TEXT("BUTTON"), TEXT("Touring "), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
    	200, 110, 100, 25, hwnd, (HMENU) IDC_CHK2, GetModuleHandle(NULL), NULL);
    	
    CheckRadioButton(hwnd, IDC_CHK1, IDC_CHK2, IDC_CHK1); //winHandle, first, last, one we want selected
}

void ResultButton(HWND hwnd)
{
	static HWND hResultButton;
	
	hResultButton = CreateWindow(TEXT("BUTTON"), TEXT("CALCULATE"), WS_CHILD | WS_VISIBLE | BS_CENTER, 
		200, 150, 100, 25, hwnd, (HMENU) IDC_RESULT_BTN, GetModuleHandle(NULL), NULL);
}