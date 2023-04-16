#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <deque>
#include <numeric>
#include <fstream>
#include "speaker.h"
using namespace std;

class SpeechManager {
public:
	// ���캯��
	SpeechManager();

	// �˵�����
	void showManu();

	// �˳�����
	void exitSystem();

	// ��ʼ��ϵͳ
	void initSpeech();

	// ��ʼ��ѡ��
	void CreateSpeaker();

	// ��ʼ����
	void StartSpeech();

	// ��ǩ
	void SpeechDraw();

	// ����
	void SpeechContest();

	// ��ʾ�������
	void showScore();

	// ���������¼
	void saveRecord();

	// ��ȡ�����¼
	void loadRecord();

	// չʾ�����¼
	void showRecord();

	// ���������¼
	void clearRecord();

	// ��������
	~SpeechManager();

public:
	// ����ѡ�� 12��
	vector<int> v1;

	// ��һ�ֽ���ѡ�� 6��
	vector<int> v2;

	// ǰ����ѡ�� 3��
	vector<int> victory;

	// ��ż�ѡ��
	map<int, Speaker> Speakers;

	// ��������
	int index;

	map<int, vector<string>> Record;
};