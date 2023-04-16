#include <iostream>
#include <string>
#include "speechManager.h"

using namespace std;


int main() {
	SpeechManager sm;
	int choice;
	srand((unsigned int)time(NULL));
	while (true) {
		sm.showManu();
		cout << "ÇëÊä³öÄúµÄÑ¡Ôñ£º";
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.StartSpeech();
			break;
		case 2:
			sm.loadRecord();
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	return 0;
}