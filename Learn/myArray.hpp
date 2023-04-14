#pragma once
#include <iostream>
#include <string>
using namespace std;


template <typename T>
class myArray {
public:

	myArray(int capcity) {
		this->Capcity = capcity;
		this->Size = 0;
		this->pAddress = new T[this->Capcity];
	}

	myArray(const myArray& arr) {
		this->Capcity = arr.Capcity;
		this->Size = arr.Size;
		this->pAddress = new T[this->Capcity];
		for (int i = 0; i < this->Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	//浅拷贝
	myArray& operator=(const myArray& arr) {
		if (this->pAddress != NULL) {
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->Size = 0;
			this->Capcity = 0;
		}
		this->Capcity = arr.Capcity;
		this->Size = arr.Size;
		this->pAddress = new T[this->Capcity];
		for (int i = 0; i < this->Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	//尾插法
	void push_back(const T& value) {
		//判断容量是否等于大小
		if (this->Capcity == this->Size) {
			return;
		}
		this->pAddress[this->Size] = value;
		this->Size++;
	}

	//尾删法
	void pop_back() {
		//判断容量是否等于大小
		if (this->Size == 0) {
			return;
		}
		this->Size--;
	}

	//通过下标访问元素
	T& operator[](int index) {
		return this->pAddress[index];
	}

	//
	int getCapacity() {
		return this->Capcity;
	}

	int getSize() {
		return this->Size;
	}

	~myArray() {
		if (this->pAddress != NULL) {
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}
private:
	//数组
	T* pAddress;

	//容量
	int Capcity;

	//大小
	int Size;
};
