#include <iostream>
#include <cstdlib>
#include <climits>
#include <thread>
#include <ctime>
#include <vector>
#include <deque>
#include <set>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <array>
#include <queue>
#include <list>
#include <chrono>
#include <Windows.h>
#include <fstream>
#include "myArray.hpp"

using namespace std;

template <typename T>
void print(const T& arr) {
	for (auto& x : arr) {
		cout << x << ", ";
	}
	cout << endl;
}



class Person {
public:
	Person(string name, int age) {
		this->name = name;
		this->age = age;
	}
	string name;
	int age;

};

bool compare(const Person& p1, const Person& p2) {
	if (p1.name < p2.name) {
		return true;
	}
	else if (p1.name > p2.name) {
		return false;
	}
	else {
		if (p1.age > p2.age) {
			return true;
		}
		else {
			return false;
		}
	}
}

int main() {
	vector<Person> l;
	string nameSeed = "BADCGFE";
	for (int i = 0; i < 7; i++) {
		int age = rand() % 30 + 10;
		string name = "";
		name += nameSeed[i];
		Person p(name, age);
		l.push_back(p);
	}
	cout << "ÅÅÐòÇ°" << endl;
	for (auto x : l) {
		cout << x.name << ":" << x.age << endl;
	}
	sort(l.begin(), l.end(), compare);

	cout << "ÅÅÐòºó" << endl;
	for (auto x : l) {
		cout << x.name << ":" << x.age << endl;
	}

	return 0;
}

