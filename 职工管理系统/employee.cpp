#include "employee.h"


Employee::Employee(int id, string name, int dI) {
	this->ID = id;
	this->Name = name;
	this->DeptID = dI;
}

void Employee::showInfo() {
	cout << "ְ����ţ�" << this->ID
		<< "\tְ��������" << this->Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ��: ��ɾ�����������" << endl;
}

string Employee::getDeptName() {
	return string("Ա��");
}