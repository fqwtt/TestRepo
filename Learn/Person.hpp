#pragma once
#include <iostream>
#include <string>
using namespace std;
template <typename T1, typename T2>
class Person {
public:
	T1 name;
	T2 age;
	Person(T1 name, T2 age);
	void fun();
};

template <typename T1, typename T2>
Person<T1, T2>::Person(T1 name, T2 age) {
	this->name = name;
	this->age = age;
}

template <typename T1, typename T2>
void Person<T1, T2>::fun() {
	cout << this->name << this->age << endl;
}