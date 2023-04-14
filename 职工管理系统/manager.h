#pragma once
#include "worker.h"
class Manager :public Worker {
public:
	// 构造
	Manager(int id, string name, int dI);

	// 显示职工信息
	virtual void showInfo();

	// 获取岗位名称
	virtual string getDeptName();
};