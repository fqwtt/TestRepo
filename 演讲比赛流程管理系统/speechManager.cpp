#include "speechManager.h"


// 构造函数
SpeechManager::SpeechManager() {
	this->initSpeech();
	this->CreateSpeaker();
}

// 菜单功能
void SpeechManager::showManu() {
	cout << "***************************************" << endl;
	cout << "*********** 欢迎参加演讲比赛 **********" << endl;
	cout << "**********  1、开始演讲比赛  **********" << endl;
	cout << "**********  2、查看往届记录  **********" << endl;
	cout << "**********  3、清空比赛记录  **********" << endl;
	cout << "**********  0、退出比赛程序  **********" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}

// 退出功能
void SpeechManager::exitSystem() {
	cout << "欢迎再次使用" << endl;
	system("pause");
	exit(0);
}

// 初始化系统
void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->Speakers.clear();
	this->index = 1;
}

// 初始化选手
void SpeechManager::CreateSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.Name = name;

		for (int j = 0; j < 2; j++) {
			sp.Socre[j] = 0;
		}

		// 创建选手编号并放入v1容器
		this->v1.push_back(i + 10001);

		// 选手编号及对应选手放入map容器中
		this->Speakers.insert(make_pair(i + 10001, sp));
	}
}

// 开始比赛
void SpeechManager::StartSpeech() {
	this->initSpeech();
	this->CreateSpeaker();

	//第一轮比赛
	//1.抽签
	this->SpeechDraw();

	//2.比赛
	this->SpeechContest();

	//3.显示晋级结果
	this->showScore();
	this->index++;
	//第二轮比赛
	//1.抽签
	this->SpeechDraw();

	//2.比赛
	this->SpeechContest();

	//3.显示比赛结果
	this->showScore();

	//4.保存分数
	this->saveRecord();

	cout << "本届比赛完毕" << endl;
	system("pause");
	system("cls");
}

// 抽签
void SpeechManager::SpeechDraw() {
	cout << "第 << " << this->index << " >> 轮比赛选手正在抽签" << endl;
	cout << "-----------------------" << endl;
	cout << "抽签结果如下：" << endl;
	if (this->index == 1) {
		// 第一轮比赛抽签
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
	}
	else {
		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
	}

	cout << endl << "-----------------------" << endl;
	system("pause");
}

// 比赛
void SpeechManager::SpeechContest() {
	cout << "--------第 << " << this->index << " >> 轮比赛正式开始--------" << endl;

	multimap<double, int, greater<double>> groupScore;
	int num = 0; //记录人数
	vector<int> src;
	if (this->index == 1) {
		src = this->v1;
	}
	else {
		src = this->v2;
	}

	//遍历选手
	for (vector<int>::iterator it = src.begin(); it != src.end(); it++) {
		deque<double> d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//cout << "编号： " << *it << " 姓名： " << this->Speakers[*it].Name << "  获取平均分： " << avg << endl;
		this->Speakers[*it].Socre[this->index - 1] = avg;
		groupScore.insert(make_pair(avg, *it));

		if (++num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (pair<int, double> score : groupScore) {
				cout << "编号： " << score.second << " 姓名：" << this->Speakers[score.second].Name
					<< " 成绩：" << this->Speakers[score.second].Socre[this->index - 1] << endl;
			}
			int count = 0;
			for (auto it = groupScore.begin(); it != groupScore.end() && count != 3; it++, count++) {
				if (this->index == 1) {
					this->v2.push_back((*it).second);
				}
				else {
					this->victory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "----------第 << " << this->index << " >> 轮比赛完毕----------" << endl;
	system("pause");
}

// 显示比赛结果
void SpeechManager::showScore() {
	cout << "--------第" << this->index << "轮晋级选手信息如下：---------" << endl;
	vector<int> v;
	if (this->index == 1) {
		v = this->v2;
	}
	else {
		v = this->victory;
	}
	for (auto x : v) {
		cout << "编号： " << x << " 姓名：" << this->Speakers[x].Name
			<< " 成绩：" << this->Speakers[x].Socre[this->index - 1] << endl;
	}
	cout << endl;
}

// 保存比赛记录
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (auto x : this->victory) {
		ofs << x << "," << this->Speakers[x].Socre[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "保存完毕" << endl;
}

// 读取往届记录
void SpeechManager::loadRecord() {
	this->Record.clear();
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	if (!ifs.is_open()) {
		cout << "没有往届记录" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "没有往届记录" << endl;
		ifs.close();
		return;
	}
	ifs.putback(ch);
	string data;
	int index = 0;
	while (ifs >> data) {
		index++;
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			start = pos + 1;
			v.push_back(temp);
		}
		this->Record.insert(make_pair(index, v));
	}
	ifs.close();
}

// 展示往届记录
void SpeechManager::showRecord() {
	for (pair<int, vector<string>> x : this->Record) {
		cout << "第" << x.first << "届"
			<< " 冠军编号：" << x.second[0] << " 成绩：" << x.second[1] << "\t"
			<< " 亚军编号：" << x.second[2] << " 成绩：" << x.second[3] << "\t"
			<< " 季军编号：" << x.second[4] << " 成绩：" << x.second[5] << endl;
	}
	system("pause");
	system("cls");
}

// 清除比赛记录
void SpeechManager::clearRecord() {
	cout << "确定要清空比赛记录？" << endl;
	cout << "1.是" << "  2.否" << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1) {
		ofstream ofs;
		ofs.open("speech.csv", ios::out);
		ofs.close();
		cout << "已清除所有比赛记录" << endl;
	}
	system("pause");
	system("cls");
}

// 析构函数
SpeechManager::~SpeechManager() {

}