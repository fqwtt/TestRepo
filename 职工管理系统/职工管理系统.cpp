#include <iostream>
#include <string>
#include <fstream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;


int main() {
	WokerManager wm;
	char choice = '0';
	while (true) {
		wm.showMenu();
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ£º";
		cin >> choice;
		switch (choice)
		{
		case '0':
			wm.ExitSystem();
			break;
		case '1':
			wm.AddWorker();
			break;
		case '2':
			wm.showWorkers();
			break;
		case '3':
			wm.delWorker();
			break;
		case '4':
			wm.modWorker();
			break;
		case '5':
			wm.findWorker();
			break;
		case '6':
			wm.sortWorkers();
			break;
		case '7':
			wm.cleanFile();
			break;
		default:
			system("cls");
			break;
		}
	}


	system("pause");
	return 0;
}