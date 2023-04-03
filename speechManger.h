#pragma once
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
#include <ctime>

class SpeechManger 
{
public:
	//构造函数
	SpeechManger();

	//菜单功能:
	void showMenu();

	//退出系统
	void exitSystem();

	//初始化成员属性
	void initSpeech();

	//创建选手对象
	void createSpeaker();

	//整个比赛流程
	void startSpeech();

	//抽签函数
	void speechDraw();

	//打分系统
	void speechContest();

	//展示晋级选手
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

    //显示记录
	void showRecord();

	//清空记录
	void clearRecord();

	//析构函数
	~SpeechManger();

	//成员属性
	//第一轮的选手
	vector<int> v1;

	//第二轮的选手
	vector<int> v2;

	//获胜选手
	vector<int> victory;

	//选手及其编号
	map<int, Speaker> m;

	//比赛的轮数
	int index;

    //文件是否为空
	bool fileIsEmpty;

	//获胜者记录
	map<int, vector<string>> m_Record;
};
