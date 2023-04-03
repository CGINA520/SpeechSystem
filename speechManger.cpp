#include "speechManger.h"

SpeechManger::SpeechManger()
{
	//初始化成员属性
	this->initSpeech();

	//创建选手对象
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();
}

void SpeechManger::showMenu()
{
	cout << "***************************************************" << endl;
	cout << "*****************  欢迎参加演讲比赛 ***************" << endl;
	cout << "*****************  1.开始演讲比赛   ***************" << endl;
	cout << "*****************  2.查看往届记录   ***************" << endl;
	cout << "*****************  3.清空比赛记录   ***************" << endl;
	cout << "*****************  0.退出比赛程序   ***************" << endl;
	cout << "***************************************************" << endl;
}

//退出系统
void SpeechManger::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//初始化成员属性
void SpeechManger::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m.clear();
	this->index = 1;
	this->m_Record.clear();
}

//创建选手对象
void SpeechManger::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		//初始化选手
		Speaker sp;
		sp.m_Name = "选手";
		sp.m_Name += nameSeed[i];
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//将第一轮选手的编号放入v1中
		this->v1.push_back(i + 10001);
		//将编号及其选手放入map容器
		this->m.insert(make_pair(i + 10001, sp));
	}
}

//整个比赛流程
void SpeechManger::startSpeech()
{
	//第一轮比赛
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();

	//第二轮比赛
	this->index++;
    //1.抽签
    this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->showScore();

	//保存文件
	this->saveRecord();

	//重置比赛
	//初始化成员属性
	this->initSpeech();
	//创建选手对象
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");

}

//抽签函数
void SpeechManger::speechDraw()
{
	cout << "第<<" << this->index << ">>" << "轮比赛选手正在抽签" << endl;
	cout << "-----------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

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

//打分系统
void SpeechManger::speechContest()
{
	cout << "-------第" << this->index << "轮比赛正式开始--------" << endl;

	//创建mutimap存放小组成绩
	multimap<double, int, greater<double>> groupScore;

	int num = 0; //记录小组人数，没6个人为一组

	vector<int> v_Src;
	if (this->index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有选手开始比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
        //10个评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			//随机生成60~100的小数
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(),greater<double>());

        //去掉最高分和最低分
		d.pop_back();
		d.pop_front();

		//求平均
		int sum = accumulate(d.begin(), d.end(), 0.0f);
		double average = sum / (double)d.size();

		//将平均分放入到map容器中
		this->m[*it].m_Score[this->index - 1] = average;

		//将打分数据放入临时容器中
		groupScore.insert(make_pair(average, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组的比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号: " << it->second << " 姓名: " << this->m[it->second].m_Name << " 成绩： "
					<< this->m[it->second].m_Score[this->index - 1] << endl;
			}
			//取走前三名
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
	cout << "-------第" << this->index << "轮比赛完毕-------" << endl;
	system("pause");
} 

//展示晋级选手
void SpeechManger::showScore()
{
	cout << "-------第" << this->index << "轮比赛晋级选手如下-------" << endl;

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
		cout << "编号:  " << *it << "  姓名：" << this->m[*it].m_Name << "  成绩： " << this->m[*it].m_Score[this->index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

//保存记录
void SpeechManger::saveRecord()
{ 
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//以追加的方式写文件

	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
	{
		ofs << *it << "," << this->m[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "文件已保存" << endl;

	this->fileIsEmpty = false;
}

//读取记录
void SpeechManger::loadRecord()
{
	//文件不存在
	ifstream ifs("speech.csv", ios::in);//读文件
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		ifs.close();  
		return;
	}

	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//将上面读取的单个字符放回来
	string data;
	int index = 0;

	while (ifs >> data)
	{
		int pos = -1;  //截取","的位置变量
		int start = 0;
		//10010, 86.625, 10009, 81.25, 10007, 78.5,
		vector<string> v; //存放6个字符串的信息
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


//显示记录
void SpeechManger::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空或者文件不存在!" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届"
				<< "冠军编号： " << this->m_Record[i][0] << "  冠军得分  " << this->m_Record[i][1]<<"  "
				<< "亚军编号： " << this->m_Record[i][2] << "  亚军得分  " << this->m_Record[i][3]<<"  "
				<< "季军编号： " << this->m_Record[i][4] << "  季军得分  " << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManger::clearRecord()
{
	cout << "确定要清空吗？" << endl;
	cout << "1.是" << endl;
	cout << "0.否" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化成员属性
		this->initSpeech();

		//创建选手对象
		this->createSpeaker();

		//加载往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");

}

SpeechManger::~SpeechManger()
{

}
