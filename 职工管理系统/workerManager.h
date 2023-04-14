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

	//����
	WokerManager();

	//����
	~WokerManager();

	//չʾ�˵�
	void showMenu();

	//�˳�ϵͳ
	void ExitSystem();

	//���ְ��
	void AddWorker();

	// ͳ��ְ������
	int getWorkerNum();

	//��ʼ��ְ��
	void init_workers();

	//�����ļ�
	void save();

	//չʾְ����Ϣ
	void showWorkers();

	//�ж�ְ���Ƿ����
	int isExist(int id);

	//ɾ��ְ��
	void delWorker();

	//�޸�ְ��
	void modWorker();

	//����ְ��
	void findWorker();

	//����ְ��
	void sortWorkers();

	//����ļ�
	void cleanFile();

private:
	int workNum = 0;
	Worker** workers = NULL;
	bool FileEmpty = true;
};
