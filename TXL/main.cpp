#include <iostream>
#include <string>
#define MAX_SIZE 1000

using namespace std;
struct Friend {
	string Name;
	int Sex;
	int Age;
	string Phone;
	string Addr;
};

struct TXL {
	Friend friends[MAX_SIZE];
	int size = 0;
};

void showMenu() {
	string commands[] = {
		"1、add friend",
		"2、show friend",
		"3、del friend",
		"4、serch friend",
		"5、change friend",
		"6、clear friend",
		"0、quit"
	};
	for (string command : commands) {
		cout << command << endl;
	}
}

void addFriend(TXL& txl) {
	if (txl.size < MAX_SIZE) {
		// Name
		string name;
		cout << "Please enter name:";
		cin >> name;
		txl.friends[txl.size].Name = name;
		// Sex
		cout << "Please enter sex(1--man 0--woman):";
		int sex;
		while (true) {
			cin >> sex;
			if (sex == 1 || sex == 0) {
				break;
			}
			else {
				cout << "Enter error, please enter again:";
			}
		}
		txl.friends[txl.size].Sex = sex;
		// Age
		cout << "Please enter age:";
		int age;
		cin >> age;
		txl.friends[txl.size].Age = age;
		// Phone
		cout << "Please enter phone:";
		string phone;
		cin >> phone;
		txl.friends[txl.size].Phone = phone;
		// Address
		cout << "Please enter address:";
		string address;
		cin >> address;
		txl.friends[txl.size].Addr = address;
		txl.size += 1;
		cout << "Add success!" << endl;
	}
	else {
		cout << "Reach maximum capacity!" << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
}

void dispFriend(TXL& txl) {
	cout << "Name\tSex\tAge\tPhone\t\tAddress\t" << endl;
	for (int i = 0; i < txl.size; i++) {
		string sex;
		sex = txl.friends[i].Sex == 0 ? "woman" : "man";
		cout << txl.friends[i].Name << "\t"
			<< sex << "\t"
			<< txl.friends[i].Age << "\t"
			<< txl.friends[i].Phone << "\t"
			<< txl.friends[i].Addr << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
}

void delFriend(TXL& txl) {
	string name;
	cout << "Which friend do you want to delete:";
	cin >> name;
	int idx[MAX_SIZE];
	int count = 0;
	for (int i = 0; i < txl.size; i++) {
		if (txl.friends[i].Name == name) {
			idx[count] = i;
			count++;
		}
	}
	int delIdx = 0;
	if (count == 0) {
		cout << "There is no such person" << endl;
		return;
	}
	else if (count > 1) {
		cout << "A total of " << count << " " << name << " have been found" << endl;
		cout << endl << "Number\tName\tSex\tAge\tPhone\t\tAddress\t" << endl;
		for (int i = 0; i < count; i++) {
			cout << i + 1 << "\t"
				<< txl.friends[idx[i]].Name << "\t"
				<< (txl.friends[idx[i]].Sex == 0 ? "woman" : "man") << "\t"
				<< txl.friends[idx[i]].Age << "\t"
				<< txl.friends[idx[i]].Phone << "\t"
				<< txl.friends[idx[i]].Addr << endl;
		}
		cout << "Which one do you want to delete? Please enter the index:";
		while (true) {
			cin >> delIdx;
			if (delIdx > count || delIdx < 1) {
				cout << "Exceeded index, please re-enter:";
			}
			else {
				delIdx = idx[delIdx - 1];
				break;
			}
		}
	}
	else
		delIdx = idx[0];
	for (int i = delIdx; i < txl.size - 1; i++) {
		txl.friends[i] = txl.friends[i + 1];
	}
	txl.size--;
	cout << "delete successed" << endl;
}

void searchFriend(TXL& txl) {
	string name;
	cout << "Which friend do you want to search:";
	cin >> name;
	int idx[MAX_SIZE];
	int count = 0;
	for (int i = 0; i < txl.size; i++) {
		if (txl.friends[i].Name == name) {
			idx[count] = i;
			count++;
		}
	}
	if (count == 0) {
		cout << "There is no such person" << endl;
	}
	else {
		cout << "A total of " << count << " " << name << " have been found" << endl;
		cout << endl << "Number\tName\tSex\tAge\tPhone\t\tAddress\t" << endl;
		for (int i = 0; i < count; i++) {
			cout << i + 1 << "\t"
				<< txl.friends[idx[i]].Name << "\t"
				<< (txl.friends[idx[i]].Sex == 0 ? "woman" : "man") << "\t"
				<< txl.friends[idx[i]].Age << "\t"
				<< txl.friends[idx[i]].Phone << "\t"
				<< txl.friends[idx[i]].Addr << endl;
		}
	}
	system("pause");
	system("cls");
}

void changeFriend(TXL& txl) {
	string name;
	cout << "Which friend do you want to change:";
	cin >> name;
	int idx[MAX_SIZE];
	int count = 0;
	for (int i = 0; i < txl.size; i++) {
		if (txl.friends[i].Name == name) {
			idx[count] = i;
			count++;
		}
	}
	int changeIdx = 0;
	if (count == 0) {
		cout << "There is no such person" << endl;
		return;
	}
	else if (count > 1) {
		cout << "A total of " << count << " " << name << " have been found" << endl;
		cout << endl << "Number\tName\tSex\tAge\tPhone\t\tAddress\t" << endl;
		for (int i = 0; i < count; i++) {
			cout << i + 1 << "\t"
				<< txl.friends[idx[i]].Name << "\t"
				<< (txl.friends[idx[i]].Sex == 0 ? "woman" : "man") << "\t"
				<< txl.friends[idx[i]].Age << "\t"
				<< txl.friends[idx[i]].Phone << "\t"
				<< txl.friends[idx[i]].Addr << endl;
		}
		cout << "Which one do you want to delete? Please enter the index:";
		while (true) {
			cin >> changeIdx;
			if (changeIdx > count || changeIdx < 1) {
				cout << "Exceeded index, please re-enter:";
			}
			else {
				changeIdx = idx[changeIdx - 1];
				break;
			}
		}
	}
	else
		changeIdx = idx[0];
	cout << "Changed name:";
	cin >> txl.friends[changeIdx].Name;
	cout << "Changed sex(1--man 0--woman):";
	cin >> txl.friends[changeIdx].Sex;
	cout << "Changed age:";
	cin >> txl.friends[changeIdx].Age;
	cout << "Changed phone:";
	cin >> txl.friends[changeIdx].Phone;
	cout << "Changed address:";
	cin >> txl.friends[changeIdx].Addr;
}

void clearTxl(TXL& txl){
	txl.size = 0;
	system("pause");
	system("cls");
}

int main() {
	int select;
	TXL txl;
	while (true) {
		showMenu();
		cout << "please enter command:";
		cin >> select;
		cout << endl;
		switch (select) {
		case 1:
			addFriend(txl);
			break;
		case 2:
			dispFriend(txl);
			break;
		case 3:
			delFriend(txl);
			system("pause");
			system("cls");
			break;
		case 4:
			searchFriend(txl);
			break;
		case 5:
			changeFriend(txl);
			system("pause");
			system("cls");
			break;
		case 6:
			clearTxl(txl);
			break;
		case 0:
			cout << "quit successed!" << endl;
			return 0;
		default:
			cout << "Invalid command" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}