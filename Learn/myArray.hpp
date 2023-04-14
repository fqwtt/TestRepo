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

	//ǳ����
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

	//β�巨
	void push_back(const T& value) {
		//�ж������Ƿ���ڴ�С
		if (this->Capcity == this->Size) {
			return;
		}
		this->pAddress[this->Size] = value;
		this->Size++;
	}

	//βɾ��
	void pop_back() {
		//�ж������Ƿ���ڴ�С
		if (this->Size == 0) {
			return;
		}
		this->Size--;
	}

	//ͨ���±����Ԫ��
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
	//����
	T* pAddress;

	//����
	int Capcity;

	//��С
	int Size;
};
