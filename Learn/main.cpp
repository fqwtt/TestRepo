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
#include <functional>
#include "myArray.hpp"

using namespace std;

class Person {
public:
	Person(string name, int age) {
		this->name = name;
		this->age = age;
	}
	string name;
	int age;
	bool operator==(const Person& obj) {
		if (this->name == obj.name && this->age == obj.age) {
			return true;
		}
		else {
			return false;
		}
	}
};

int main() {
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);
	vector<Person> v;
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

	//≤‚ ‘
	auto it = find(v.begin(), v.end(), Person("ddd", 40));
	//asdasdadads
	cout << it->name << ":" << it->age << endl;
	return 0;
}

