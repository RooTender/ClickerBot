#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	//Setup variables for point targeting
	POINT cursorPosition;
	int x, y;
	bool interrupt = false;
	const int userResponse = 3;
	const int countdown = 20;

	//Introduction message
	cout << "I will get you <" << userResponse << "> seconds to switch to the proper tab." << endl;
	cout << "TIP: You can use ALT+TAB to move between windows" << endl << endl;
	cout << "Press anything when you'll be ready!" << endl;
	system("pause > nul");

	//Countdown to switch the windows
	for (int i = 0; i < userResponse * 2; i++) {
		Sleep(500);
		printf("%c",'.');
	}

	resume:

	//Allocate X and Y for temporary usage
	if (GetCursorPos(&cursorPosition))
	{
		x = cursorPosition.x;
		y = cursorPosition.y;
	}

	//Launching thread
	system("cls");
	cout << "Thread is running..." << endl;

	while (x == cursorPosition.x && y == cursorPosition.y) {
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, NULL, NULL);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, NULL, NULL);
		Sleep(countdown);
		GetCursorPos(&cursorPosition);
	}

	cout << "Thread suspended! Waiting for interrupt";

	for (int i = 0; i < userResponse * 4; i++) {
		Sleep(250);
		printf("%c", '.');

		//Interrupt if right button pressed [32 and 64 bits suported]
		if ((GetKeyState(VK_RBUTTON) && (0x100 != 0 || 0x80 != 0))) {
			interrupt = true;
			break;
		}
	}
	
	if (interrupt == false) goto resume;

    return 0;
}

