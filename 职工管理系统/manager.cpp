#include "manager.h"


Manager::Manager(int id, string name, int dI) {
	this->ID = id;
	this->Name = name;
	this->DeptID = dI;
}

void Manager::showInfo() {
	cout << "职工编号：" << this->ID
		<< "\t职工姓名：" << this->Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责: 完成老板交给的任务，并下发任务给普通员工" << endl;
}

string Manager::getDeptName() {
	return string("经理");
}