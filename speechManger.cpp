#include "speechManger.h"

SpeechManger::SpeechManger()
{
	//��ʼ����Ա����
	this->initSpeech();

	//����ѡ�ֶ���
	this->createSpeaker();

	//���������¼
	this->loadRecord();
}

void SpeechManger::showMenu()
{
	cout << "***************************************************" << endl;
	cout << "*****************  ��ӭ�μ��ݽ����� ***************" << endl;
	cout << "*****************  1.��ʼ�ݽ�����   ***************" << endl;
	cout << "*****************  2.�鿴�����¼   ***************" << endl;
	cout << "*****************  3.��ձ�����¼   ***************" << endl;
	cout << "*****************  0.�˳���������   ***************" << endl;
	cout << "***************************************************" << endl;
}

//�˳�ϵͳ
void SpeechManger::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

//��ʼ����Ա����
void SpeechManger::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m.clear();
	this->index = 1;
	this->m_Record.clear();
}

//����ѡ�ֶ���
void SpeechManger::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		//��ʼ��ѡ��
		Speaker sp;
		sp.m_Name = "ѡ��";
		sp.m_Name += nameSeed[i];
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//����һ��ѡ�ֵı�ŷ���v1��
		this->v1.push_back(i + 10001);
		//����ż���ѡ�ַ���map����
		this->m.insert(make_pair(i + 10001, sp));
	}
}

//������������
void SpeechManger::startSpeech()
{
	//��һ�ֱ���
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore();

	//�ڶ��ֱ���
	this->index++;
    //1.��ǩ
    this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���ս��
	this->showScore();

	//�����ļ�
	this->saveRecord();

	//���ñ���
	//��ʼ����Ա����
	this->initSpeech();
	//����ѡ�ֶ���
	this->createSpeaker();
	//���������¼
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");

}

//��ǩ����
void SpeechManger::speechDraw()
{
	cout << "��<<" << this->index << ">>" << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

	if (this->index == 1)
	{
		random_shuffle(v1.begin(), v1.end());

		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());

		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------" << endl;
	system("pause");
	cout << endl;
}

//���ϵͳ
void SpeechManger::speechContest()
{
	cout << "-------��" << this->index << "�ֱ�����ʽ��ʼ--------" << endl;

	//����mutimap���С��ɼ�
	multimap<double, int, greater<double>> groupScore;

	int num = 0; //��¼С��������û6����Ϊһ��

	vector<int> v_Src;
	if (this->index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//��������ѡ�ֿ�ʼ����
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
        //10����ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			//�������60~100��С��
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(),greater<double>());

        //ȥ����߷ֺ���ͷ�
		d.pop_back();
		d.pop_front();

		//��ƽ��
		int sum = accumulate(d.begin(), d.end(), 0.0f);
		double average = sum / (double)d.size();

		//��ƽ���ַ��뵽map������
		this->m[*it].m_Score[this->index - 1] = average;

		//��������ݷ�����ʱ������
		groupScore.insert(make_pair(average, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��ı�������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���: " << it->second << " ����: " << this->m[it->second].m_Name << " �ɼ��� "
					<< this->m[it->second].m_Score[this->index - 1] << endl;
			}
			//ȡ��ǰ����
			int count = 0;
			for (multimap<double, int, greater<>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++)
			{
				if (this->index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					victory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "-------��" << this->index << "�ֱ������-------" << endl;
	system("pause");
} 

//չʾ����ѡ��
void SpeechManger::showScore()
{
	cout << "-------��" << this->index << "�ֱ�������ѡ������-------" << endl;

	vector<int> v;
	if (this->index == 1)
	{
		v = v2;
	}
	else
	{
		v = victory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "���:  " << *it << "  ������" << this->m[*it].m_Name << "  �ɼ��� " << this->m[*it].m_Score[this->index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

//�����¼
void SpeechManger::saveRecord()
{ 
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//��׷�ӵķ�ʽд�ļ�

	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
	{
		ofs << *it << "," << this->m[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ��ѱ���" << endl;

	this->fileIsEmpty = false;
}

//��ȡ��¼
void SpeechManger::loadRecord()
{
	//�ļ�������
	ifstream ifs("speech.csv", ios::in);//���ļ�
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		ifs.close();  
		return;
	}

	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڲ�Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ��Ż���
	string data;
	int index = 0;

	while (ifs >> data)
	{
		int pos = -1;  //��ȡ","��λ�ñ���
		int start = 0;
		//10010, 86.625, 10009, 81.25, 10007, 78.5,
		vector<string> v; //���6���ַ�������Ϣ
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}


//��ʾ��¼
void SpeechManger::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ����ļ�������!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "��"
				<< "�ھ���ţ� " << this->m_Record[i][0] << "  �ھ��÷�  " << this->m_Record[i][1]<<"  "
				<< "�Ǿ���ţ� " << this->m_Record[i][2] << "  �Ǿ��÷�  " << this->m_Record[i][3]<<"  "
				<< "������ţ� " << this->m_Record[i][4] << "  �����÷�  " << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManger::clearRecord()
{
	cout << "ȷ��Ҫ�����" << endl;
	cout << "1.��" << endl;
	cout << "0.��" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ����Ա����
		this->initSpeech();

		//����ѡ�ֶ���
		this->createSpeaker();

		//���������¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");

}

SpeechManger::~SpeechManger()
{

}
