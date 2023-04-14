#include "workerManager.h"

//����
WokerManager::WokerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1.�ļ�������
	if (!ifs.is_open()) {
		//cout << "�ļ������ڣ�" << endl;
		/*this->workNum = 0;
		this->workers = NULL;
		this->FileEmpty = true;*/
		ifs.close();
		return;
	}
	//2.�ļ����ڵ�������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ��!" << endl;
		ifs.close();
		return;
	}
	//3.�ļ����ڣ������м�¼����
	int num = this->getWorkerNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->workNum = num;
	this->workers = new Worker * [num];
	this->FileEmpty = false;

	this->init_workers();
	/*for (int i = 0; i < num; i++) {
		cout << workers[i]->getID() << workers[i]->getName() << endl;
	}*/
}

//����
WokerManager::~WokerManager() {
	if (this->workers != NULL) {
		for (int i = 0; i < this->workNum; i++) {
			if (this->workers[i] != NULL) {
				delete this->workers[i];
				this->workers[i] = NULL;
			}
		}
		delete[] this->workers;
		this->workers = NULL;
	}
}

//չʾ�˵�
void WokerManager::showMenu() {
	cout << "*****************************************" << endl;
	cout << "********  ��ӭʹ��ְ������ϵͳ�� ********" << endl;
	cout << "************  0.�˳�������� ************" << endl;
	cout << "************  1.����ְ����Ϣ ************" << endl;
	cout << "************  2.��ʾְ����Ϣ ************" << endl;
	cout << "************  3.ɾ����ְְ�� ************" << endl;
	cout << "************  4.�޸�ְ����Ϣ ************" << endl;
	cout << "************  5.����ְ����Ϣ ************" << endl;
	cout << "************  6.���ձ������ ************" << endl;
	cout << "************  7.��������ĵ� ************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void WokerManager::ExitSystem() {
	cout << "��ӭ�ٴ�ʹ��" << endl;
	system("pause");
	exit(0);
}

//���Ա��
void WokerManager::AddWorker() {
	cout << "���������ְ��������";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->workNum + addNum;
		Worker** newSpace = new Worker * [newSize];
		if (this->workers != NULL) {
			for (int i = 0; i < workNum; i++) {
				newSpace[i] = this->workers[i];
			}
		}

		// �������������
		for (int i = 0; i < addNum; i++) {
			int id; //ְ�����
			string name; //ְ������
			int dSelect; //����ѡ��
			cout << "�������" << i + 1 << "����Ա����ID��";
			cin >> id;
			cout << "�������" << i + 1 << "����Ա����������";
			cin >> name;
			cout << "��ѡ���ְ����λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->workNum + i] = worker;
		}
		//�ͷ�ԭ�пռ�
		delete[] this->workers;

		//�����¿ռ�ָ��
		this->workers = newSpace;

		//����ְ������
		this->workNum = newSize;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����Ա��" << endl;

		//����
		this->save();

		//�ļ��ǿ�
		this->FileEmpty = false;
	}
	else {
		cout << "������������" << endl;
	}

	//������������ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//ͳ��ְ������
int WokerManager::getWorkerNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dI;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dI) {
		num++;
	}
	ifs.close();
	return num;
}

//��ʼ��ְ��
void WokerManager::init_workers() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dI;
	int idx = 0;
	while (ifs >> id && ifs >> name && ifs >> dI) {
		Worker* worker = NULL;
		if (dI == 1) { //��ְͨ��
			worker = new Employee(id, name, dI);
		}
		else if (dI == 2) { //����
			worker = new Manager(id, name, dI);
		}
		else if (dI == 3) { //�ܲ�
			worker = new Boss(id, name, dI);
		}
		else {
			cout << "�ļ�����" << endl;
			ifs.close();
			exit(0);
		}
		this->workers[idx] = worker;

		idx++;
	}
	// �ر��ļ�
	ifs.close();
}

//�����ļ�
void WokerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->workNum; i++) {
		ofs << workers[i]->getID() << " "
			<< workers[i]->getName() << " "
			<< workers[i]->getDeptID() << endl;
	}
	ofs.close();
}

//չʾְ����Ϣ
void WokerManager::showWorkers() {
	if (this->FileEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < this->workNum; i++) {
			this->workers[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
int WokerManager::isExist(int id) {
	int index = -1;
	for (int i = 0; i < this->workNum; i++) {
		if (this->workers[i]->getID() == id) {
			index = i;
			break;
		}
	}
	return index;
}

//ɾ��ְ��
void WokerManager::delWorker() {
	if (this->FileEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "��������Ҫɾ����ְ����ţ�";
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1) {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
		else {
			delete workers[index];
			for (int i = index; i < this->workNum - 1; i++) {
				//����ǰ��
				this->workers[i] = this->workers[i + 1];
			}
			this->workNum -= 1;
			// ͬ�����µ��ļ���
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

//�޸�ְ��
void WokerManager::modWorker() {
	if (this->FileEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "��������Ҫ�޸ĵ�ְ����ţ�";
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1) {
			cout << "�޸�ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
		else {
			int newId = 0;
			string newName = "";
			int newDSelect = 0;
			cout << "�������޸ĺ�ְ����ţ�";
			cin >> newId;
			cout << "�������޸ĺ�ְ�����֣�";
			cin >> newName;
			cout << "�������޸ĺ�ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
			cin >> newDSelect;
			Worker* worker = NULL;
			if (newDSelect == 1) {
				worker = new Employee(newId, newName, newDSelect);
			}
			else if (newDSelect == 2) {
				worker = new Manager(newId, newName, newDSelect);
			}
			else {
				worker = new Boss(newId, newName, newDSelect);
			}
			this->workers[index] = worker;
			cout << "�޸ĳɹ���" << endl;
			this->save();
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WokerManager::findWorker() {
	if (this->FileEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1������ְ����Ų���" << endl;
		cout << "2������ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "��������ҵ�ְ����ţ�";
			cin >> id;
			int index = this->isExist(id);
			if (index == -1) {
				cout << "���޴���" << endl;
			}
			else {
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->workers[index]->showInfo();
			}
		}
		else if (select == 2) {
			string name;
			cout << "������Ҫ���ҵ�������";
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->workNum; i++) {
				if (this->workers[i]->getName() == name) {
					this->workers[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false) {
				cout << "���޴���" << endl;
			}
		}
		else {
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����ְ��
void WokerManager::sortWorkers() {
	if (this->FileEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.��ְ������������" << endl;
		cout << "2.��ְ���Ž�������" << endl;
		int select;
		cin >> select;
		for (int i = 0; i < this->workNum; i++) {
			int minOrMax = i;
			for (int j = i + 1; j < this->workNum; j++) {
				if (select == 1) { //����
					if (this->workers[j]->getID() < this->workers[minOrMax]->getID()) {
						minOrMax = j;
					}
				}
				else { //����
					if (this->workers[j]->getID() > this->workers[minOrMax]->getID()) {
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax) {
				Worker* tmp = this->workers[i];
				this->workers[i] = this->workers[minOrMax];
				this->workers[minOrMax] = tmp;
			}
		}
		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();
		this->showWorkers();
	}
}

//����ļ�
void WokerManager::cleanFile() {
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->workers != NULL) {
			for (int i = 0; i < this->workNum; i++) {
				if (this->workers[i] != NULL) {
					delete this->workers[i];
					this->workers[i] = NULL;
				}
			}
		}
		this->workNum = 0;
		this->FileEmpty = true;
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}