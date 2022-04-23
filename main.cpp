#include <windows.h>
#include <string>
#include "dialogs.h" //My dialogs
#include "controls.h"
#include "calculations.h"

//Constants for event loops, etc
#define ID_FILE_EXIT 901
#define ID_STUFF_GO 902
#define ID_HELP_ABOUT 912 



//function prototypes
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void MakeMenu(HWND hwnd);//menu code function

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) //error handler for couldn't register window class
	{
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Paddle Length Selector",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) //Error handler for no window created
	{
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	//The main event loop
	while(GetMessage(&msg, NULL, 0, 0) > 0) /* If no error is received... */
	{ 
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) 
{
	LPSTR heightBoxLabel = (LPSTR)"Enter Height:";
	LPSTR paddleStyleSelectLabel = (LPSTR)"Choose Paddle Type:";
	LPSTR resultText = (LPSTR)"";
	TCHAR heightFromUser[20]; //we'll put the user data here
	static HWND hHeight; //The handle for the height input box
	 
	//Handle SYSTEM msg's HERE!!! (Inc mouse clicks etc)
	switch(Message) 
	{
		case WM_CREATE:
		{
			MakeMenu(hwnd);	
            hHeight = HeightBox(hwnd); //Function returns the handle so we can get the input later
            PaddleSelectRadioButtons(hwnd);
            ResultButton(hwnd);
		}
		return 0; //instead of break
		
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
			TextOut(hdc, 100, 42, heightBoxLabel, strlen(heightBoxLabel));
			TextOut(hdc, 46, 82, paddleStyleSelectLabel, strlen(paddleStyleSelectLabel));
			TextOut(hdc, 46, 200, resultText, strlen(resultText));
		}
		break;
		
		
		//this is the event loop FOR OUR EVENTS
		case WM_COMMAND:
			 switch(LOWORD(wParam))
            {
                //if our button is pressed
				case IDC_RESULT_BTN:
				{
					GetWindowText(hHeight, heightFromUser, 20); //get the inputted height
					int height = ConvertHeight(heightFromUser); //sanitise and convert
					bool isWW = false; //flag we set from radiobuttons
					if (IsDlgButtonChecked(hwnd, IDC_CHK1) == BST_CHECKED) isWW = true; //from our radiobuttons
					
					if (height == -1) WarnText(hwnd, "Invalid Number, try again");
					else 
					{
						CalculateLength(isWW, height, hwnd);
						//ResultText(hwnd, paddleLength);
					}
				}
				break;
				
				case ID_HELP_ABOUT: //help > about pressed
        		{
            		AboutDlg(hwnd);	
        		}
        		break;
        		
				case ID_FILE_EXIT: //file > exit pressed
				{	
					if (CloseDlg(hwnd) == IDYES) PostQuitMessage(0); //if we choose exit, check sure using our dialog box
				}
                break;
                case ID_STUFF_GO:

                break;
                // END OF WM_COMMAND EVENT DETECTION
            }
            break;
		
		case WM_DESTROY: //window closed with corner X
		{
			PostQuitMessage(0);	
		}
		break;
		//All the messages we don't handle ourselves
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

//menu building function
void MakeMenu(HWND hwnd)
{
    HICON hIcon, hIconSm;
	HMENU hMenu, hSubMenu;

    hMenu = CreateMenu();

    hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&File"); //UINT Cast now UINT_PTR to get around 32bit vs 64 bit *NOT IDEAL*

    hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_STUFF_GO, "&Go");
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&Stuff");
    
    //Let's build my help menu here
	hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_HELP_ABOUT, "&About");
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&Help");

    SetMenu(hwnd, hMenu);
}

