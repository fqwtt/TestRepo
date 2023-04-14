#pragma once
#include <iostream>
#include <string>
using namespace std;

//职工抽象类
class Worker {
public:
	// 显示职工信息
	virtual void showInfo() = 0;

	// 获取岗位名称
	virtual string getDeptName() = 0;

	// 获取ID
	virtual int getID();

	// 获取姓名
	virtual string getName();

	// 获取部门编号
	virtual int getDeptID();

protected:
	int ID; //职工编号
	string Name; //职工姓名
	int DeptID; //职工所在部门编号

};