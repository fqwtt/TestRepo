#pragma once
#include "worker.h"
class Manager :public Worker {
public:
	// ����
	Manager(int id, string name, int dI);

	// ��ʾְ����Ϣ
	virtual void showInfo();

	// ��ȡ��λ����
	virtual string getDeptName();
};