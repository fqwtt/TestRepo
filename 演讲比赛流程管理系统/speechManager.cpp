#include "speechManager.h"


// ���캯��
SpeechManager::SpeechManager() {
	this->initSpeech();
	this->CreateSpeaker();
}

// �˵�����
void SpeechManager::showManu() {
	cout << "***************************************" << endl;
	cout << "*********** ��ӭ�μ��ݽ����� **********" << endl;
	cout << "**********  1����ʼ�ݽ�����  **********" << endl;
	cout << "**********  2���鿴�����¼  **********" << endl;
	cout << "**********  3����ձ�����¼  **********" << endl;
	cout << "**********  0���˳���������  **********" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}

// �˳�����
void SpeechManager::exitSystem() {
	cout << "��ӭ�ٴ�ʹ��" << endl;
	system("pause");
	exit(0);
}

// ��ʼ��ϵͳ
void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->Speakers.clear();
	this->index = 1;
}

// ��ʼ��ѡ��
void SpeechManager::CreateSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.Name = name;

		for (int j = 0; j < 2; j++) {
			sp.Socre[j] = 0;
		}

		// ����ѡ�ֱ�Ų�����v1����
		this->v1.push_back(i + 10001);

		// ѡ�ֱ�ż���Ӧѡ�ַ���map������
		this->Speakers.insert(make_pair(i + 10001, sp));
	}
}

// ��ʼ����
void SpeechManager::StartSpeech() {
	this->initSpeech();
	this->CreateSpeaker();

	//��һ�ֱ���
	//1.��ǩ
	this->SpeechDraw();

	//2.����
	this->SpeechContest();

	//3.��ʾ�������
	this->showScore();
	this->index++;
	//�ڶ��ֱ���
	//1.��ǩ
	this->SpeechDraw();

	//2.����
	this->SpeechContest();

	//3.��ʾ�������
	this->showScore();

	//4.�������
	this->saveRecord();

	cout << "����������" << endl;
	system("pause");
	system("cls");
}

// ��ǩ
void SpeechManager::SpeechDraw() {
	cout << "�� << " << this->index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------" << endl;
	cout << "��ǩ������£�" << endl;
	if (this->index == 1) {
		// ��һ�ֱ�����ǩ
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

// ����
void SpeechManager::SpeechContest() {
	cout << "--------�� << " << this->index << " >> �ֱ�����ʽ��ʼ--------" << endl;

	multimap<double, int, greater<double>> groupScore;
	int num = 0; //��¼����
	vector<int> src;
	if (this->index == 1) {
		src = this->v1;
	}
	else {
		src = this->v2;
	}

	//����ѡ��
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
		//cout << "��ţ� " << *it << " ������ " << this->Speakers[*it].Name << "  ��ȡƽ���֣� " << avg << endl;
		this->Speakers[*it].Socre[this->index - 1] = avg;
		groupScore.insert(make_pair(avg, *it));

		if (++num % 6 == 0) {
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (pair<int, double> score : groupScore) {
				cout << "��ţ� " << score.second << " ������" << this->Speakers[score.second].Name
					<< " �ɼ���" << this->Speakers[score.second].Socre[this->index - 1] << endl;
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
	cout << "----------�� << " << this->index << " >> �ֱ������----------" << endl;
	system("pause");
}

// ��ʾ�������
void SpeechManager::showScore() {
	cout << "--------��" << this->index << "�ֽ���ѡ����Ϣ���£�---------" << endl;
	vector<int> v;
	if (this->index == 1) {
		v = this->v2;
	}
	else {
		v = this->victory;
	}
	for (auto x : v) {
		cout << "��ţ� " << x << " ������" << this->Speakers[x].Name
			<< " �ɼ���" << this->Speakers[x].Socre[this->index - 1] << endl;
	}
	cout << endl;
}

// ���������¼
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (auto x : this->victory) {
		ofs << x << "," << this->Speakers[x].Socre[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�������" << endl;
}

// ��ȡ�����¼
void SpeechManager::loadRecord() {
	this->Record.clear();
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	if (!ifs.is_open()) {
		cout << "û�������¼" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "û�������¼" << endl;
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

// չʾ�����¼
void SpeechManager::showRecord() {
	for (pair<int, vector<string>> x : this->Record) {
		cout << "��" << x.first << "��"
			<< " �ھ���ţ�" << x.second[0] << " �ɼ���" << x.second[1] << "\t"
			<< " �Ǿ���ţ�" << x.second[2] << " �ɼ���" << x.second[3] << "\t"
			<< " ������ţ�" << x.second[4] << " �ɼ���" << x.second[5] << endl;
	}
	system("pause");
	system("cls");
}

// ���������¼
void SpeechManager::clearRecord() {
	cout << "ȷ��Ҫ��ձ�����¼��" << endl;
	cout << "1.��" << "  2.��" << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1) {
		ofstream ofs;
		ofs.open("speech.csv", ios::out);
		ofs.close();
		cout << "��������б�����¼" << endl;
	}
	system("pause");
	system("cls");
}

// ��������
SpeechManager::~SpeechManager() {

}