#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define gets gets_s
#define scanf scanf_s
#define MAX_INFONUM 100

//用于存储日志的结构体及time_t变量
time_t logt;
struct tm *loglt;

//定义用于储存班费管理信息的结构体
struct current
{
	int id;
	char type[10];
	char reason[20];
	int amount;
	int balance;
	int count;
	char remark[20];
	char name[20];
	struct tm sctime;
};

//用于光标定位的PointXY函数，x，y为要将光标移至的坐标
void PointXY(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//用于打印班费管理信息的函数
void printData(struct current sf[], int index, int pos)
{
	PointXY(3, pos);
	printf("%03d", sf[index].id);
	PointXY(11, pos);
	printf("%s", sf[index].type);
	PointXY(17, pos);
	printf("%s", sf[index].name);
	PointXY(27, pos);
	printf("%s", sf[index].reason);
	PointXY(39, pos);
	printf("%d", sf[index].amount);
	PointXY(46, pos);
	printf("%d", sf[index].count);
	PointXY(51, pos);
	printf("%d", sf[index].balance);
	PointXY(57, pos);
	printf("%d.%d.%d", (sf[index].sctime.tm_year + 1900), (sf[index].sctime.tm_mon + 1), sf[index].sctime.tm_mday);
	PointXY(69, pos);
	printf("%s\n", sf[index].remark);
}


//模块1：班费信息录入
//*******************************************************************************************
//定义用于输出操作日志的函数
void writeLogToFile(int index, int id, FILE *fp)
{
	//获取当前时间
	time(&logt);
	loglt = localtime(&logt);
	//打印信息至日志文件
	fprintf(fp, "%04d.%02d.%02d 在索引为%d的位置添加了一条编号为%d的数据\n", ((loglt->tm_year) + 1900), ((loglt->tm_mon) + 1), loglt->tm_mday, index, id);
}
//录入班费信息模块
int inputInfo(struct current sf[], int size, FILE *fp)
{
	int i;							//循环用临时变量
	time_t t;						//获取当前系统时间用变量
	struct tm *lt;					//获取当前系统时间结构体
	int opt = 0;					//接收用户操作项变量

									//导航排版
	system("cls");
	printf("主菜单->录入信息\n");
	printf("****************************************************************************\n");
	//提示用户输入相关信息
	printf("班费收支编号：\n");
	printf("收入还是支出：\n");
	printf("经办人：\n");
	printf("原因：\n");
	printf("金额：\n");
	printf("人数：\n");
	printf("余额：\n");
	printf("备注：\n");
	printf("时间(1:系统时间;2:自定义)：\n");


	//1.班费编号
	do
	{
		PointXY(14, 2);
		scanf("%d", &sf[size].id);
		getchar();

		//遍历结构体数组，判断id是否已经存在
		for (i = 0; i < size; i++)
		{
			if (sf[i].id == sf[size].id)
			{
				PointXY(14, 2);
				printf("        <!>不允许重复id，请重新设置！");
				sf[size].id = -1;
			}
		}
	} while (sf[size].id == -1);	  //若id为-1即用户输入的id是重复的，执行循环，使得用户重新输入
	PointXY(20, 2);
	printf("                                     ");   //用于删除用户输入错误信息的错误提示

	//2.收入或支出
	while (1)
	{
		PointXY(14, 3);
		gets(sf[size].type);

		//异常输入判断
		if (size == 0 && !strcmp(sf[size].type, "支出"))			//判断用户是否在第一次入帐的时候输入了支出
		{
			PointXY(14, 3);
			printf("        <!>第一次入账，无法支出！请重新输入！");
		}
		else if (!strcmp(sf[size].type, "收入") || !strcmp(sf[size].type, "支出"))	//判断用户是否输入了正确的信息，若正确跳出循环
		{
			PointXY(20, 3);
			printf("                                     ");
			break;
		}
		else	//对用户输入的不正确信息进行报错提示
		{
			PointXY(14, 3);
			printf("        <!>你输入了无效字符，请重新输入！    ");
		}

	}

	//3.经办人
	PointXY(8, 4);
	gets(sf[size].name);

	//4.原因
	PointXY(6, 5);
	gets(sf[size].reason);

	//5.金额
	PointXY(6, 6);
	scanf("%d", &sf[size].amount);

	//6.人数
	PointXY(6, 7);
	getchar();
	scanf("%d", &sf[size].count);

	//7.余额(自动生成)
	PointXY(6, 8);
	if (!strcmp(sf[size].type, "收入"))
	{
		if (size == 0)
		{
			sf[size].balance = sf[size].count * sf[size].amount;
		}
		else
		{
			sf[size].balance = sf[size - 1].balance + sf[size].count * sf[size].amount;
		}
	}
	else
	{
		sf[size].balance = sf[size - 1].balance - sf[size].count * sf[size].amount;
	}
	printf("%d", sf[size].balance);

	//8.备注
	PointXY(6, 9);
	getchar();
	gets(sf[size].remark);

	//9.时间
	PointXY(27, 10);
	scanf("%d", &opt);				//接收用户选择的操作数
	getchar();						//接收回车字符
	if (opt == 1)					//当用户输入的操作数为1时获取系统时间
	{
		//获取当前系统时间
		time(&t);
		lt = localtime(&t);
		//将当前系统时间赋值给当前班费结构体变量
		sf[size].sctime.tm_year = lt->tm_year;
		sf[size].sctime.tm_mon = lt->tm_mon;
		sf[size].sctime.tm_mday = lt->tm_mday;
	}
	else if (opt == 2)			 //当用户输入的操作数为2时接收用户输入的时间
	{
		printf("自定义：");
		//接受用户输入的时间信息
		scanf("%04d.%02d.%02d", &sf[size].sctime.tm_year, &sf[size].sctime.tm_mon, &sf[size].sctime.tm_mday);
		sf[size].sctime.tm_year -= 1900;		//结构体tm中的year变量记录的是1900后多少年份，将其相应的处理
		sf[size].sctime.tm_mon -= 1;			//结构体tm中的mon变量记录的是从0至11的月份，将其进行相应的处理
		getchar();			//捕获前面scanf遗留下来的回车按键
	}

	//导航排版
	system("cls");
	printf("主菜单->浏览信息->成功录入的信息\n");
	printf("****************************************************************************\n");
	printf("班费编码  收/支  经办人      原因      金额  人数  余额     时间       备注  \n");
	printData(sf, size, 3);

	//将添加的操作记录记录到文件系统中
	writeLogToFile(size, sf[size].id, fp);

	//提示用户按任意键返回菜单
	printf("\n按任意键回到主菜单！\n");
	system("pause>nul");
	return ++size;
}

//模块2：班费信息浏览
//*******************************************************************************************
//浏览班费信息模块
void showInfo(struct current sf[], int size)
{
	int i;								//用于循环操作的临时变量
	//导航排版
	system("cls");
	printf("主菜单->浏览信息\n");
	printf("****************************************************************************\n");

	//打印全部班费记录信息
	if (size == 0)						//判断结构体数组是否为空
	{
		printf("当前系统没有录入任何信息！\n");
	}
	else								//遍历结构体数组，并打印其信息
	{
		printf("班费编码  收/支  经办人      原因      金额  人数  余额     时间       备注  \n");
		for (i = 0; i < size; i++)
		{
			printData(sf, i, i + 3);
		}
	}

	//提示用户按任意键返回菜单
	printf("\n请点击任意键返回主菜单！\n");
	system("pause>nul");
	return;
}

//模块3：班费信息查询
//*******************************************************************************************
//查询班费信息模块
void searchInfo(struct current sf[], int size)
{
	char opt = 0;							//选择要执行的操作，
	int searchId;							//储存要查询的班费编码
	int foundCount;						//储存查找到的信息数量
	int i;									//循环用临时变量
	char searchName[20];					//储存要查询的经办人
	struct tm compareFrom;				//用于存储时间范围开始的结构体
	struct tm compareTo;					//用于存储时间范围结束的结构体

											//导航排版
	system("cls");
	printf("主菜单->查询信息\n");
	printf("****************************************************************************\n");
	//选项内容
	printf("(a) 按照班费编码进行查询\n");
	printf("(b) 按照班费时间范围进行查询\n");
	printf("(c) 按照经办人进行查询\n");
	printf("\n请输入查询方式对应的字母：\n");

	//获取输入的操作序数
	//	getchar();								//用于接收主菜单操作传来的回车字符
	opt = getchar();						//接收用户输出的操作数

											//实现用户操作的功能
	switch (opt)
	{
		//按班费编码查询(a)
	case 'a':
		//导航排版
		system("cls");
		printf("主菜单->查询信息->按照班费编码查询\n");
		printf("****************************************************************************\n");
		//提示用户要输入的内容
		printf("输入需要查询的班费编码：\n");
		//格式排版
		printf("****************************************************************************\n");
		printf("班费编码  收/支  经办人      原因      金额  人数  余额     时间       备注  \n");

		//将光标移动至“输入需要查询的班费编码：”的后方，接收用户输入的数值
		PointXY(24, 2);
		scanf("%d", &searchId);
		getchar();

		//初始化相关变量
		foundCount = 0;


		//遍历结构体数组，寻找数组中班费一致的元素，并打印其数据
		for (i = 0; i < size; i++)
		{
			if (sf[i].id == searchId)
			{
				printData(sf, i, foundCount + 5);		//打印查找到的数据
				foundCount++;

				break;
			}
		}
		if (foundCount == 0)								//判断是否查找到数据
		{
			//打印提示用户没有查找到信息
			PointXY(0, 4);
			printf("您所要查找的信息不存在。                                                    ");
		}
		break;
		//按照班费时间范围查询(b)
	case 'b':
		//导航排版
		system("cls");
		printf("主菜单->查询信息->按照班费时间范围进行查询\n");
		printf("****************************************************************************\n");
		//提示用户输入相关信息
		printf("输入需要查询的开始时间：\n");
		printf("输入需要查询的结束时间：\n");
		//格式排版
		printf("****************************************************************************\n");
		printf("班费编码  收/支  经办人      原因      金额  人数  余额     时间       备注  \n");
		//将光标移至“输入需要查询的开始时间：”后，接收用户输入开始的时间范围
		PointXY(24, 2);
		scanf("%04d.%02d.%02d", &compareFrom.tm_year, &compareFrom.tm_mon, &compareFrom.tm_mday);
		getchar();
		//将光标移至“输入需要查询的结束时间：：”后，接收用户输入结束的时间范围
		PointXY(24, 3);
		scanf("%04d.%02d.%02d", &compareTo.tm_year, &compareTo.tm_mon, &compareTo.tm_mday);
		getchar();

		//对相关变量的值进行调整
		compareTo.tm_year -= 1900;
		compareFrom.tm_year -= 1900;
		compareTo.tm_mon -= 1;
		compareFrom.tm_mon -= 1;
		foundCount = 0;

		//遍历结构体数组，寻找数组中符合时间范围内的元素，并打印其数据
		for (i = 0; i < size; i++)
		{
			if (sf[i].sctime.tm_year > compareFrom.tm_year && sf[i].sctime.tm_year < compareTo.tm_year)
			{
				printData(sf, i, foundCount + 6);
				foundCount++;
			}
			else if (sf[i].sctime.tm_year == compareFrom.tm_year)
			{
				if (sf[i].sctime.tm_mon > compareFrom.tm_mon)
				{
					printData(sf, i, foundCount + 6);
					foundCount++;
				}
				else if (sf[i].sctime.tm_mon == compareFrom.tm_mon)
				{
					if (sf[i].sctime.tm_mday >= compareFrom.tm_mday)
					{
						printData(sf, i, foundCount + 6);
						foundCount++;
					}
				}
			}
			else if (sf[i].sctime.tm_year == compareTo.tm_year)
			{
				if (sf[i].sctime.tm_mon < compareTo.tm_mon)
				{
					printData(sf, i, foundCount + 6);
					foundCount++;
				}
				else if (sf[i].sctime.tm_mon == compareTo.tm_mon)
				{
					if (sf[i].sctime.tm_mday <= compareTo.tm_mday)
					{
						printData(sf, i, foundCount + 6);
						foundCount++;
					}
				}
			}

		}
		if (foundCount == 0)
		{
			PointXY(0, 5);
			printf("您所要查找的信息不存在。                                                    ");
		}


		break;
		//按照经办人进行查询(c)
	case 'c':
		//导航排版
		system("cls");
		printf("主菜单->查询信息->按照经办人进行查询\n");
		printf("****************************************************************************\n");
		//提示用户输入相关信息
		printf("输入需要查询的经办人名称：\n");
		//格式排版
		printf("****************************************************************************\n");
		printf("班费编码  收/支  经办人      原因      金额  人数  余额     时间       备注  \n");
		//将光标移动至“输入需要查询的经办人名称：”后，接收用户输入的信息
		PointXY(26, 2);
		getchar();
		gets(searchName);

		//对相关变量的值进行调整
		foundCount = 0;

		//遍历结构体数组中，寻找数组中经纪人一致的元素，并打印其数据
		for (i = 0; i < size; i++)
		{
			if (!strcmp(sf[i].name, searchName))
			{
				printData(sf, i, foundCount + 5);
				foundCount++;
			}
		}
		if (foundCount == 0)
		{
			PointXY(0, 4);
			printf("您所要查找的信息不存在。                                                    ");
		}
		break;
	default:
		printf("你输入了无效的字符，请重新输入：\n");
		break;
	}
	system("pause>nul");
}

//模块4：班费信息修改
//*******************************************************************************************
//定义用于输出操作日志的函数
void writeLogToFile_change(int index, int id, char *type, char *from, char *to, FILE *fp)
{
	time(&logt);
	loglt = localtime(&logt);
	fprintf(fp, "%04d.%02d.%02d 将索引为%d,编号为%d的%s从%s修改为%s\n", ((loglt->tm_year) + 1900), ((loglt->tm_mon) + 1), loglt->tm_mday, index, id, type, from, to);
}
//修改班费信息模块
void changeInfo(struct current sf[], int size, FILE *fp)
{
	int id;
	int i, j;
	int count;
	char opt;
	int choice;
	char logFrom[20];
	char logTo[20];
	int tmp;

	system("cls");
	printf("主菜单->修改信息\n");
	printf("****************************************************************************\n");
	printf("输入需要修改的班费编码：");
	PointXY(24, 2);
	//	getchar();
	scanf("%d", &id);
	printf("****************************************************************************\n");
	count = 0;
	for (i = 0; i < size; i++)
	{
		if (sf[i].id == id)
		{
			printf("班费编码  收/支  经办人      原因      金额  人数  余额     时间       备注  \n");
			printData(sf, i, count + 5);
			count++;
			break;
		}
	}
	if (count == 0)
	{
		printf("您所要查找的信息不存在。\n");
	}
	else
	{
		printf("是否进行修改？(y/n)\n");
		getchar();
		if (opt = getchar() == 'y')
		{

			do
			{
				system("cls");
				printf("主菜单->修改信息->所修改的编号为:%d\n", id);
				printf("****************************************************************************\n");
				printf("请选择其中一项进行修改：\n");
				printf("1) 班费编码\n");
				printf("2) 收入还是支出\n");
				printf("3) 经办人\n");
				printf("4) 原因\n");
				printf("5) 金额（每位同学）\n");
				printf("6) 人数\n");
				printf("7) 备注\n");
				printf("8) 时间\n");

				printf("\n输入选择：");
				scanf("%d", &choice);
				getchar();
				switch (choice)
				{
				case 1:
					printf("请输入新的班费编码：");
					itoa(sf[i].id, logFrom, 10);
					tmp = sf[i].id;
					scanf("%d", &sf[i].id);
					getchar();
					itoa(sf[i].id, logTo, 10);
					writeLogToFile_change(i, tmp, "班费编码", logFrom, logTo, fp);

					break;
				case 2:

					while (1)
					{
						printf("请输入新的类型：");
						strcpy(logFrom, sf[i].type);
						gets(sf[i].type);
						strcpy(logTo, sf[i].type);
						writeLogToFile_change(i, sf[i].id, "类型", logFrom, logTo, fp);

						if (i == 0 && !strcmp(sf[i].type, "支出"))
						{
							printf("\n<!>第一次入账，无法支出！请重新输入！\n");
						}
						else if (!strcmp(sf[i].type, "收入") || !strcmp(sf[i].type, "支出"))
						{
							for (j = i; j < size; j++)
							{
								if (!strcmp(sf[j].type, "收入"))
								{
									if (j == 0)
									{
										sf[j].balance = sf[j].count * sf[j].amount;
									}
									else
									{
										sf[j].balance = sf[j - 1].balance + sf[j].count * sf[j].amount;
									}
								}
								else
								{
									sf[j].balance = sf[j - 1].balance - sf[j].count * sf[j].amount;
								}
							}
							break;
						}
						else
						{
							printf("\n<!>你输入了无效字符，请重新输入！\n");
						}
					}
					break;
				case 3:
					printf("请输入新的经办人：");
					strcpy(logFrom, sf[i].name);
					gets(sf[i].name);
					strcpy(logTo, sf[i].name);
					writeLogToFile_change(i, sf[i].id, "经办人", logFrom, logTo, fp);
					break;
				case 4:
					printf("请输入新的原因：");
					strcpy(logFrom, sf[i].reason);
					gets(sf[i].reason);
					strcpy(logTo, sf[i].reason);
					writeLogToFile_change(i, sf[i].id, "原因", logFrom, logTo, fp);
					break;
				case 5:
					printf("请输入新的金额(每位同学)：");
					itoa(sf[i].amount, logFrom, 10);
					scanf("%d", &sf[i].amount);
					getchar();
					itoa(sf[i].amount, logTo, 10);
					writeLogToFile_change(i, sf[i].id, "金额", logFrom, logTo, fp);
					for (j = i; j < size; j++)
					{
						if (!strcmp(sf[j].type, "收入"))
						{
							if (j == 0)
							{
								sf[j].balance = sf[j].count * sf[j].amount;
							}
							else
							{
								sf[j].balance = sf[j - 1].balance + sf[j].count * sf[j].amount;
							}
						}
						else
						{
							sf[j].balance = sf[j - 1].balance - sf[j].count * sf[j].amount;
						}
					}
					break;
				case 6:
					printf("请输入新的人数：");
					itoa(sf[i].count, logFrom, 10);
					scanf("%d", &sf[i].count);
					itoa(sf[i].count, logTo, 10);
					writeLogToFile_change(i, sf[i].id, "人数", logFrom, logTo, fp);
					getchar();
					for (j = i; j < size; j++)
					{
						if (!strcmp(sf[j].type, "收入"))
						{
							if (j == 0)
							{
								sf[j].balance = sf[j].count * sf[j].amount;
							}
							else
							{
								sf[j].balance = sf[j - 1].balance + sf[j].count * sf[j].amount;
							}
						}
						else
						{
							sf[j].balance = sf[j - 1].balance - sf[j].count * sf[j].amount;
						}
					}
					break;
				case 7:
					printf("请输入新的备注：");
					strcpy(logFrom, sf[i].remark);
					gets(sf[i].remark);
					strcpy(logTo, sf[i].remark);
					writeLogToFile_change(i, sf[i].id, "备注", logFrom, logTo, fp);
					break;
				case 8:
					printf("请输入新的时间：");
					time(&logt);
					loglt = localtime(&logt);
					fprintf(fp, "%d.%d.%d 将索引为%d,编号为%d的时间从%d.%d.%d", ((loglt->tm_year) + 1900), ((loglt->tm_mon) + 1), loglt->tm_mday, i, sf[i].id, (sf[i].sctime.tm_year + 1900), (sf[i].sctime.tm_mon + 1), sf[i].sctime.tm_mday);
					scanf("%04d.%02d.%02d", &sf[i].sctime.tm_year, &sf[i].sctime.tm_mon, &sf[i].sctime.tm_mday);
					getchar();

					sf[i].sctime.tm_year -= 1900;
					sf[i].sctime.tm_mon -= 1;
					fprintf(fp, "修改为%d.%d.%d\n", (sf[i].sctime.tm_year + 1900), (sf[i].sctime.tm_mon + 1), sf[i].sctime.tm_mday);
					break;
				default:
					break;
				}
				printf("是否更新其他字段(y/n)：");
			} while (opt = getchar() == 'y');
			system("cls");
			printf("主菜单->修改信息->修改后的信息\n");
			printf("****************************************************************************\n");
			printf("班费编码  收/支  经办人      原因      金额  人数  余额     时间       备注  \n");
			printData(sf, i, count + 3);
		}
	}
}


//模块5：班费信息删除
//*******************************************************************************************
//定义用于输出操作日志的函数
void writeLogToFile_delete(int index, int id, FILE *fp)
{
	time(&logt);
	loglt = localtime(&logt);
	fprintf(fp, "%04d.%02d.%02d 在索引为%d的位置删除了一条编号为%d的数据\n", ((loglt->tm_year) + 1900), ((loglt->tm_mon) + 1), loglt->tm_mday, index, id);
}
//删除班费信息模块
int delInfo(struct current sf[], int size, FILE *fp)
{
	int id;				//用于存储用户输入的要删除的班费编号
	int i, j;			//用于循环的临时变量
	char opt = 0;		//用于存储用户的操作数

	//导航排版
	system("cls");
	printf("主菜单->删除信息\n");
	printf("****************************************************************************\n");
	//提示用户输入相关信息
	printf("输入需要删除的班费编号：");
	scanf("%d", &id);
	printf("****************************************************************************\n");
	for (i = 0; i < size; i++)
	{
		if (sf[i].id == id)
		{
			printf("班费编码  收/支  经办人      原因      金额  人数  余额     时间       备注  \n");
			printData(sf, i, 5);
			break;
		}
	}
	printf("****************************************************************************\n");
	printf("是否进行删除：");
	getchar();
	if (opt = getchar() == 'y')
	{
		writeLogToFile_delete(i, sf[i].id, fp);
		for (j = i; j < size; j++)
		{
			sf[j] = sf[j + 1];
		}
		size--;

	}
	return size;
}



//模块6：文件读写模块
//*******************************************************************************************
//文件读入模块
int readFromFile(struct current * sf)
{
	FILE *pFile;
	int size;
	struct current tmp;
	if ((pFile = fopen("SchoolFee.dat", "rb")) == NULL)
	{
		return 0;
	}
	else
	{
		printf("检测到有保存的信息，是否导入(y/n):");
		if (getchar() != 'y')
		{
			return 0;
		}
	}
	fread(&size, sizeof(int), 1, pFile);
	while (fread(&tmp, sizeof(current), 1, pFile) == 1)
	{
		sf->id = tmp.id;
		strcpy(sf->name, tmp.name);
		sf->amount = tmp.amount;
		sf->balance = tmp.balance;
		strcpy(sf->reason, tmp.reason);
		strcpy(sf->remark, tmp.remark);
		sf->count = tmp.amount;
		strcpy(sf->type, tmp.type);
		sf->sctime = tmp.sctime;
		sf++;
	}
	fclose(pFile);
	return size;
}
//文件写入模块
void saveToFile(current sf[], int size)
{
	printf("\n正在保存……\n");
	FILE *pFile;
	int i;
	if ((pFile = fopen("SchoolFee.dat", "wb")) == NULL)
	{
		printf("无法打开文件");
		return;
	}
	if (fwrite(&size, sizeof(int), 1, pFile) != 1)
	{
		printf("文件无法写入");
	}
	for (i = 0; i < size; i++)
	{
		if (fwrite(&sf[i], sizeof(current), 1, pFile) != 1)
		{
			printf("文件无法写入");
		}
	}
	fclose(pFile);
	return;
}

//主函数
int main()
{
	struct current schoolFee[MAX_INFONUM];
	int size = 0;
	int opt = 0;
	FILE *fp;
	fp = fopen("ChangeLog.txt", "a");

	size = readFromFile(schoolFee);
	do
	{

		system("cls");
		printf("主菜单\n");
		printf("****************************************************************************\n");
		printf("欢迎使用班费管理系统!\n\n");//9
		printf("(1) 录入班费信息\n");
		printf("(2) 浏览所有班费信息\n");
		printf("(3) 查询班费信息\n");
		printf("(4) 修改班费信息\n");
		printf("(5) 删除班费信息\n");
		printf("(0) 退出系统\n");
		printf("\n请输入你所要执行的操作的数字编号：\n");

		scanf("%d", &opt);
		getchar();

		switch (opt)
		{
		case 0:
			saveToFile(schoolFee, size);
			break;
		case 1:
			size = inputInfo(schoolFee, size, fp);
			break;
		case 2:
			showInfo(schoolFee, size);
			break;
		case 3:
			searchInfo(schoolFee, size);
			break;
		case 4:
			changeInfo(schoolFee, size, fp);
			break;
		case 5:
			size = delInfo(schoolFee, size, fp);
			break;
		default:
			printf("您输入了无效的数字！");
			break;
		}
	} while (opt != 0);

	fclose(fp);
	return 0;
}
