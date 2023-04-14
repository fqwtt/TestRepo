#include "employee.h"


Employee::Employee(int id, string name, int dI) {
	this->ID = id;
	this->Name = name;
	this->DeptID = dI;
}

void Employee::showInfo() {
	cout << "职工编号：" << this->ID
		<< "\t职工姓名：" << this->Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责: 完成经理交给的任务" << endl;
}

string Employee::getDeptName() {
	return string("员工");
}