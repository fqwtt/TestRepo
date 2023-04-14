#pragma once
#include <iostream>
#include <fstream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#define FILENAME "workerFile.txt"
using namespace std;

class WokerManager {
public:

	//构造
	WokerManager();

	//析构
	~WokerManager();

	//展示菜单
	void showMenu();

	//退出系统
	void ExitSystem();

	//添加职工
	void AddWorker();

	// 统计职工人数
	int getWorkerNum();

	//初始化职工
	void init_workers();

	//保存文件
	void save();

	//展示职工信息
	void showWorkers();

	//判断职工是否存在
	int isExist(int id);

	//删除职工
	void delWorker();

	//修改职工
	void modWorker();

	//查找职工
	void findWorker();

	//排序职工
	void sortWorkers();

	//清空文件
	void cleanFile();

private:
	int workNum = 0;
	Worker** workers = NULL;
	bool FileEmpty = true;
};
