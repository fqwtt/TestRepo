#pragma once
#include <iostream>
#include <string>
using namespace std;

//ְ��������
class Worker {
public:
	// ��ʾְ����Ϣ
	virtual void showInfo() = 0;

	// ��ȡ��λ����
	virtual string getDeptName() = 0;

	// ��ȡID
	virtual int getID();

	// ��ȡ����
	virtual string getName();

	// ��ȡ���ű��
	virtual int getDeptID();

protected:
	int ID; //ְ�����
	string Name; //ְ������
	int DeptID; //ְ�����ڲ��ű��

};