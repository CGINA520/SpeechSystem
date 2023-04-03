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
	//���캯��
	SpeechManger();

	//�˵�����:
	void showMenu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ����Ա����
	void initSpeech();

	//����ѡ�ֶ���
	void createSpeaker();

	//������������
	void startSpeech();

	//��ǩ����
	void speechDraw();

	//���ϵͳ
	void speechContest();

	//չʾ����ѡ��
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

    //��ʾ��¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//��������
	~SpeechManger();

	//��Ա����
	//��һ�ֵ�ѡ��
	vector<int> v1;

	//�ڶ��ֵ�ѡ��
	vector<int> v2;

	//��ʤѡ��
	vector<int> victory;

	//ѡ�ּ�����
	map<int, Speaker> m;

	//����������
	int index;

    //�ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��ʤ�߼�¼
	map<int, vector<string>> m_Record;
};
