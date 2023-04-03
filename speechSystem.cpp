#include "speechManger.h"

int main()
{
	srand((unsigned int)time(NULL));
	SpeechManger sm;
	int choice = 0;
	
	while (true)
	{
		sm.showMenu();
		cin >> choice;

		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看往届记录
			sm.showRecord();
			break;
		case 3://清空文件记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;
}