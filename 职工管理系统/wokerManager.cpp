#include "workerManager.h"

//构造
WokerManager::WokerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1.文件不存在
	if (!ifs.is_open()) {
		//cout << "文件不存在！" << endl;
		/*this->workNum = 0;
		this->workers = NULL;
		this->FileEmpty = true;*/
		ifs.close();
		return;
	}
	//2.文件存在但是数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//cout << "文件为空!" << endl;
		ifs.close();
		return;
	}
	//3.文件存在，并且有记录数据
	int num = this->getWorkerNum();
	//cout << "职工人数为：" << num << endl;
	this->workNum = num;
	this->workers = new Worker * [num];
	this->FileEmpty = false;

	this->init_workers();
	/*for (int i = 0; i < num; i++) {
		cout << workers[i]->getID() << workers[i]->getName() << endl;
	}*/
}

//析构
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

//展示菜单
void WokerManager::showMenu() {
	cout << "*****************************************" << endl;
	cout << "********  欢迎使用职工管理系统！ ********" << endl;
	cout << "************  0.退出管理程序 ************" << endl;
	cout << "************  1.增加职工信息 ************" << endl;
	cout << "************  2.显示职工信息 ************" << endl;
	cout << "************  3.删除离职职工 ************" << endl;
	cout << "************  4.修改职工信息 ************" << endl;
	cout << "************  5.查找职工信息 ************" << endl;
	cout << "************  6.按照编号排序 ************" << endl;
	cout << "************  7.清空所有文档 ************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}

//退出系统
void WokerManager::ExitSystem() {
	cout << "欢迎再次使用" << endl;
	system("pause");
	exit(0);
}

//添加员工
void WokerManager::AddWorker() {
	cout << "请输入添加职工数量：";
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

		// 批量添加新数据
		for (int i = 0; i < addNum; i++) {
			int id; //职工编号
			string name; //职工姓名
			int dSelect; //部门选择
			cout << "请输入第" << i + 1 << "个新员工的ID：";
			cin >> id;
			cout << "请输入第" << i + 1 << "个新员工的姓名：";
			cin >> name;
			cout << "请选择该职工岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
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
		//释放原有空间
		delete[] this->workers;

		//更改新空间指向
		this->workers = newSpace;

		//更新职工人数
		this->workNum = newSize;

		//提示添加成功
		cout << "成功添加" << addNum << "名新员工" << endl;

		//保存
		this->save();

		//文件非空
		this->FileEmpty = false;
	}
	else {
		cout << "输入数据有误" << endl;
	}

	//按任意键返回上级目录
	system("pause");
	system("cls");
}

//统计职工人数
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

//初始化职工
void WokerManager::init_workers() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dI;
	int idx = 0;
	while (ifs >> id && ifs >> name && ifs >> dI) {
		Worker* worker = NULL;
		if (dI == 1) { //普通职工
			worker = new Employee(id, name, dI);
		}
		else if (dI == 2) { //经理
			worker = new Manager(id, name, dI);
		}
		else if (dI == 3) { //总裁
			worker = new Boss(id, name, dI);
		}
		else {
			cout << "文件错误！" << endl;
			ifs.close();
			exit(0);
		}
		this->workers[idx] = worker;

		idx++;
	}
	// 关闭文件
	ifs.close();
}

//保存文件
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

//展示职工信息
void WokerManager::showWorkers() {
	if (this->FileEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i < this->workNum; i++) {
			this->workers[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
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

//删除职工
void WokerManager::delWorker() {
	if (this->FileEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入你要删除的职工编号：";
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1) {
			cout << "删除失败，未找到该职工" << endl;
		}
		else {
			delete workers[index];
			for (int i = index; i < this->workNum - 1; i++) {
				//数据前移
				this->workers[i] = this->workers[i + 1];
			}
			this->workNum -= 1;
			// 同步更新到文件中
			this->save();
			cout << "删除成功" << endl;
		}
	}
	system("pause");
	system("cls");
}

//修改职工
void WokerManager::modWorker() {
	if (this->FileEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入你要修改的职工编号：";
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index == -1) {
			cout << "修改失败，未找到该职工" << endl;
		}
		else {
			int newId = 0;
			string newName = "";
			int newDSelect = 0;
			cout << "请输入修改后职工编号：";
			cin >> newId;
			cout << "请输入修改后职工名字：";
			cin >> newName;
			cout << "请输入修改后职工岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
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
			cout << "修改成功！" << endl;
			this->save();
		}
	}
	system("pause");
	system("cls");
}

//查找职工
void WokerManager::findWorker() {
	if (this->FileEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入查找方式：" << endl;
		cout << "1、按照职工编号查找" << endl;
		cout << "2、按照职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "请输入查找的职工编号：";
			cin >> id;
			int index = this->isExist(id);
			if (index == -1) {
				cout << "查无此人" << endl;
			}
			else {
				cout << "查找成功！该职工信息如下：" << endl;
				this->workers[index]->showInfo();
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入要查找的姓名：";
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->workNum; i++) {
				if (this->workers[i]->getName() == name) {
					this->workers[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false) {
				cout << "查无此人" << endl;
			}
		}
		else {
			cout << "输入有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序职工
void WokerManager::sortWorkers() {
	if (this->FileEmpty) {
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式：" << endl;
		cout << "1.按职工号升序排列" << endl;
		cout << "2.按职工号降序排列" << endl;
		int select;
		cin >> select;
		for (int i = 0; i < this->workNum; i++) {
			int minOrMax = i;
			for (int j = i + 1; j < this->workNum; j++) {
				if (select == 1) { //升序
					if (this->workers[j]->getID() < this->workers[minOrMax]->getID()) {
						minOrMax = j;
					}
				}
				else { //降序
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
		cout << "排序成功！排序后的结果为：" << endl;
		this->save();
		this->showWorkers();
	}
}

//清空文件
void WokerManager::cleanFile() {
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
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
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}