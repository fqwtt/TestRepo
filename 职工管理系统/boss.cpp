#include "boss.h"


Boss::Boss(int id, string name, int dI) {
	this->ID = id;
	this->Name = name;
	this->DeptID = dI;
}

void Boss::showInfo() {
	cout << "ְ����ţ�" << this->ID
		<< "\tְ��������" << this->Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ��: ����˾����ʵ��" << endl;
}

string Boss::getDeptName() {
	return string("�ܲ�");
}