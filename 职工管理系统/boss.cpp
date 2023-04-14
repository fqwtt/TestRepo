#include "boss.h"


Boss::Boss(int id, string name, int dI) {
	this->ID = id;
	this->Name = name;
	this->DeptID = dI;
}

void Boss::showInfo() {
	cout << "职工编号：" << this->ID
		<< "\t职工姓名：" << this->Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责: 管理公司所有实务" << endl;
}

string Boss::getDeptName() {
	return string("总裁");
}