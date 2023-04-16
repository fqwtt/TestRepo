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
	// 构造函数
	SpeechManager();

	// 菜单功能
	void showManu();

	// 退出功能
	void exitSystem();

	// 初始化系统
	void initSpeech();

	// 初始化选手
	void CreateSpeaker();

	// 开始比赛
	void StartSpeech();

	// 抽签
	void SpeechDraw();

	// 比赛
	void SpeechContest();

	// 显示比赛结果
	void showScore();

	// 保存比赛记录
	void saveRecord();

	// 读取往届记录
	void loadRecord();

	// 展示往届记录
	void showRecord();

	// 清除比赛记录
	void clearRecord();

	// 析构函数
	~SpeechManager();

public:
	// 比赛选手 12人
	vector<int> v1;

	// 第一轮晋级选手 6人
	vector<int> v2;

	// 前三名选手 3人
	vector<int> victory;

	// 编号及选手
	map<int, Speaker> Speakers;

	// 比赛轮数
	int index;

	map<int, vector<string>> Record;
};