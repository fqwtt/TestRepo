#include "manager.h"


Manager::Manager(int id, string name, int dI) {
	this->ID = id;
	this->Name = name;
	this->DeptID = dI;
}

void Manager::showInfo() {
	cout << "ְ����ţ�" << this->ID
		<< "\tְ��������" << this->Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ��: ����ϰ彻�������񣬲��·��������ͨԱ��" << endl;
}

string Manager::getDeptName() {
	return string("����");
}