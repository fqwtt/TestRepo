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
	Person() = default;
	Person(string name, int age) {
		this->name = name;
		this->age = age;
	}
	~Person() {
		cout << "xigou" << endl;
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

template<typename T>
class smart_pointer {
private:
	T* m_RawPointer;
public:
	smart_pointer(T* p) :m_RawPointer(p) {};
	~smart_pointer() { delete m_RawPointer; };
	T operator=(const T* p) {
		this->m_RawPointer = p;
	}
	T& operator*() {
		return *m_RawPointer;
	}
	T* operator->() {
		return m_RawPointer;
	}
};
int main() {


	unique_ptr<Person[]> p(new Person[2]);
	////Person* p1 = new Person[2133300];

	//system("pause");
	Person* p1 = p.get();
	system("pause");
	return 0;
}

