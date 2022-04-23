#include <string>
#include <iostream>

#define IDC_RESULT_TEXT 855 // where we display the result

//this is where we do the calculation and return the paddle length
//the use of so many else-if's is concerning, switch doesn't routinely
//get used for ranges.. GCC allows it but I don't think it's ANSI :-/
void CalculateLength(bool isWW, int height, HWND hwnd)
{
	 std::string paddleLength;
	
	if (!isWW)
	{
		if (height < 152) paddleLength = "205";
		else if (height < 161) paddleLength = "210";
		else if (height < 171) paddleLength = "215";
		else if (height < 176) paddleLength = "220";
		else paddleLength = "225";
	}
	else
	{
		if (height < 152) paddleLength = "185";
		else if (height < 161) paddleLength = "191";
		else if (height < 171) paddleLength = "194";
		else if (height < 176) paddleLength = "197";
		else if (height < 183) paddleLength = "200";
		else paddleLength = "203";
	}
	
	std::string textBefore = "Paddle Length Required: ";
	std::string textAfter = " Cms";
	std::string finalMsg = textBefore + paddleLength + textAfter;
	LPCSTR finalMsgLPC = finalMsg.c_str(); //we built our string using c++ <string> and now we must convert it

	//displaying directly from here gets around scope issues
	static HWND hResultText;
	hResultText = CreateWindow("STATIC", finalMsgLPC, WS_CHILD | WS_VISIBLE, 
            200, 200, 300, 25, hwnd, (HMENU)IDC_RESULT_TEXT, GetModuleHandle(NULL), NULL);
}

//here we can sanitise our data and return the integer. We'll set it to -1 if invalid
int ConvertHeight(char *heightStr)
{
	int height = 0;
	try 
	{
    	height = std::stoi(heightStr);
		if (height < 50 || height > 280) height = -1;
	} 
	catch (std::exception const &e) 
	{
    	height = -1;
	}
	
	return height;
}