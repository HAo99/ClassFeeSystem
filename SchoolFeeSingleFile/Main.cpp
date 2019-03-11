#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define gets gets_s
#define scanf scanf_s
#define MAX_INFONUM 100

//���ڴ洢��־�Ľṹ�弰time_t����
time_t logt;
struct tm *loglt;

//�������ڴ����ѹ�����Ϣ�Ľṹ��
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

//���ڹ�궨λ��PointXY������x��yΪҪ���������������
void PointXY(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//���ڴ�ӡ��ѹ�����Ϣ�ĺ���
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


//ģ��1�������Ϣ¼��
//*******************************************************************************************
//�����������������־�ĺ���
void writeLogToFile(int index, int id, FILE *fp)
{
	//��ȡ��ǰʱ��
	time(&logt);
	loglt = localtime(&logt);
	//��ӡ��Ϣ����־�ļ�
	fprintf(fp, "%04d.%02d.%02d ������Ϊ%d��λ�������һ�����Ϊ%d������\n", ((loglt->tm_year) + 1900), ((loglt->tm_mon) + 1), loglt->tm_mday, index, id);
}
//¼������Ϣģ��
int inputInfo(struct current sf[], int size, FILE *fp)
{
	int i;							//ѭ������ʱ����
	time_t t;						//��ȡ��ǰϵͳʱ���ñ���
	struct tm *lt;					//��ȡ��ǰϵͳʱ��ṹ��
	int opt = 0;					//�����û����������

									//�����Ű�
	system("cls");
	printf("���˵�->¼����Ϣ\n");
	printf("****************************************************************************\n");
	//��ʾ�û����������Ϣ
	printf("�����֧��ţ�\n");
	printf("���뻹��֧����\n");
	printf("�����ˣ�\n");
	printf("ԭ��\n");
	printf("��\n");
	printf("������\n");
	printf("��\n");
	printf("��ע��\n");
	printf("ʱ��(1:ϵͳʱ��;2:�Զ���)��\n");


	//1.��ѱ��
	do
	{
		PointXY(14, 2);
		scanf("%d", &sf[size].id);
		getchar();

		//�����ṹ�����飬�ж�id�Ƿ��Ѿ�����
		for (i = 0; i < size; i++)
		{
			if (sf[i].id == sf[size].id)
			{
				PointXY(14, 2);
				printf("        <!>�������ظ�id�����������ã�");
				sf[size].id = -1;
			}
		}
	} while (sf[size].id == -1);	  //��idΪ-1���û������id���ظ��ģ�ִ��ѭ����ʹ���û���������
	PointXY(20, 2);
	printf("                                     ");   //����ɾ���û����������Ϣ�Ĵ�����ʾ

	//2.�����֧��
	while (1)
	{
		PointXY(14, 3);
		gets(sf[size].type);

		//�쳣�����ж�
		if (size == 0 && !strcmp(sf[size].type, "֧��"))			//�ж��û��Ƿ��ڵ�һ�����ʵ�ʱ��������֧��
		{
			PointXY(14, 3);
			printf("        <!>��һ�����ˣ��޷�֧�������������룡");
		}
		else if (!strcmp(sf[size].type, "����") || !strcmp(sf[size].type, "֧��"))	//�ж��û��Ƿ���������ȷ����Ϣ������ȷ����ѭ��
		{
			PointXY(20, 3);
			printf("                                     ");
			break;
		}
		else	//���û�����Ĳ���ȷ��Ϣ���б�����ʾ
		{
			PointXY(14, 3);
			printf("        <!>����������Ч�ַ������������룡    ");
		}

	}

	//3.������
	PointXY(8, 4);
	gets(sf[size].name);

	//4.ԭ��
	PointXY(6, 5);
	gets(sf[size].reason);

	//5.���
	PointXY(6, 6);
	scanf("%d", &sf[size].amount);

	//6.����
	PointXY(6, 7);
	getchar();
	scanf("%d", &sf[size].count);

	//7.���(�Զ�����)
	PointXY(6, 8);
	if (!strcmp(sf[size].type, "����"))
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

	//8.��ע
	PointXY(6, 9);
	getchar();
	gets(sf[size].remark);

	//9.ʱ��
	PointXY(27, 10);
	scanf("%d", &opt);				//�����û�ѡ��Ĳ�����
	getchar();						//���ջس��ַ�
	if (opt == 1)					//���û�����Ĳ�����Ϊ1ʱ��ȡϵͳʱ��
	{
		//��ȡ��ǰϵͳʱ��
		time(&t);
		lt = localtime(&t);
		//����ǰϵͳʱ�丳ֵ����ǰ��ѽṹ�����
		sf[size].sctime.tm_year = lt->tm_year;
		sf[size].sctime.tm_mon = lt->tm_mon;
		sf[size].sctime.tm_mday = lt->tm_mday;
	}
	else if (opt == 2)			 //���û�����Ĳ�����Ϊ2ʱ�����û������ʱ��
	{
		printf("�Զ��壺");
		//�����û������ʱ����Ϣ
		scanf("%04d.%02d.%02d", &sf[size].sctime.tm_year, &sf[size].sctime.tm_mon, &sf[size].sctime.tm_mday);
		sf[size].sctime.tm_year -= 1900;		//�ṹ��tm�е�year������¼����1900�������ݣ�������Ӧ�Ĵ���
		sf[size].sctime.tm_mon -= 1;			//�ṹ��tm�е�mon������¼���Ǵ�0��11���·ݣ����������Ӧ�Ĵ���
		getchar();			//����ǰ��scanf���������Ļس�����
	}

	//�����Ű�
	system("cls");
	printf("���˵�->�����Ϣ->�ɹ�¼�����Ϣ\n");
	printf("****************************************************************************\n");
	printf("��ѱ���  ��/֧  ������      ԭ��      ���  ����  ���     ʱ��       ��ע  \n");
	printData(sf, size, 3);

	//����ӵĲ�����¼��¼���ļ�ϵͳ��
	writeLogToFile(size, sf[size].id, fp);

	//��ʾ�û�����������ز˵�
	printf("\n��������ص����˵���\n");
	system("pause>nul");
	return ++size;
}

//ģ��2�������Ϣ���
//*******************************************************************************************
//��������Ϣģ��
void showInfo(struct current sf[], int size)
{
	int i;								//����ѭ����������ʱ����
	//�����Ű�
	system("cls");
	printf("���˵�->�����Ϣ\n");
	printf("****************************************************************************\n");

	//��ӡȫ����Ѽ�¼��Ϣ
	if (size == 0)						//�жϽṹ�������Ƿ�Ϊ��
	{
		printf("��ǰϵͳû��¼���κ���Ϣ��\n");
	}
	else								//�����ṹ�����飬����ӡ����Ϣ
	{
		printf("��ѱ���  ��/֧  ������      ԭ��      ���  ����  ���     ʱ��       ��ע  \n");
		for (i = 0; i < size; i++)
		{
			printData(sf, i, i + 3);
		}
	}

	//��ʾ�û�����������ز˵�
	printf("\n����������������˵���\n");
	system("pause>nul");
	return;
}

//ģ��3�������Ϣ��ѯ
//*******************************************************************************************
//��ѯ�����Ϣģ��
void searchInfo(struct current sf[], int size)
{
	char opt = 0;							//ѡ��Ҫִ�еĲ�����
	int searchId;							//����Ҫ��ѯ�İ�ѱ���
	int foundCount;						//������ҵ�����Ϣ����
	int i;									//ѭ������ʱ����
	char searchName[20];					//����Ҫ��ѯ�ľ�����
	struct tm compareFrom;				//���ڴ洢ʱ�䷶Χ��ʼ�Ľṹ��
	struct tm compareTo;					//���ڴ洢ʱ�䷶Χ�����Ľṹ��

											//�����Ű�
	system("cls");
	printf("���˵�->��ѯ��Ϣ\n");
	printf("****************************************************************************\n");
	//ѡ������
	printf("(a) ���հ�ѱ�����в�ѯ\n");
	printf("(b) ���հ��ʱ�䷶Χ���в�ѯ\n");
	printf("(c) ���վ����˽��в�ѯ\n");
	printf("\n�������ѯ��ʽ��Ӧ����ĸ��\n");

	//��ȡ����Ĳ�������
	//	getchar();								//���ڽ������˵����������Ļس��ַ�
	opt = getchar();						//�����û�����Ĳ�����

											//ʵ���û������Ĺ���
	switch (opt)
	{
		//����ѱ����ѯ(a)
	case 'a':
		//�����Ű�
		system("cls");
		printf("���˵�->��ѯ��Ϣ->���հ�ѱ����ѯ\n");
		printf("****************************************************************************\n");
		//��ʾ�û�Ҫ���������
		printf("������Ҫ��ѯ�İ�ѱ��룺\n");
		//��ʽ�Ű�
		printf("****************************************************************************\n");
		printf("��ѱ���  ��/֧  ������      ԭ��      ���  ����  ���     ʱ��       ��ע  \n");

		//������ƶ�����������Ҫ��ѯ�İ�ѱ��룺���ĺ󷽣������û��������ֵ
		PointXY(24, 2);
		scanf("%d", &searchId);
		getchar();

		//��ʼ����ر���
		foundCount = 0;


		//�����ṹ�����飬Ѱ�������а��һ�µ�Ԫ�أ�����ӡ������
		for (i = 0; i < size; i++)
		{
			if (sf[i].id == searchId)
			{
				printData(sf, i, foundCount + 5);		//��ӡ���ҵ�������
				foundCount++;

				break;
			}
		}
		if (foundCount == 0)								//�ж��Ƿ���ҵ�����
		{
			//��ӡ��ʾ�û�û�в��ҵ���Ϣ
			PointXY(0, 4);
			printf("����Ҫ���ҵ���Ϣ�����ڡ�                                                    ");
		}
		break;
		//���հ��ʱ�䷶Χ��ѯ(b)
	case 'b':
		//�����Ű�
		system("cls");
		printf("���˵�->��ѯ��Ϣ->���հ��ʱ�䷶Χ���в�ѯ\n");
		printf("****************************************************************************\n");
		//��ʾ�û����������Ϣ
		printf("������Ҫ��ѯ�Ŀ�ʼʱ�䣺\n");
		printf("������Ҫ��ѯ�Ľ���ʱ�䣺\n");
		//��ʽ�Ű�
		printf("****************************************************************************\n");
		printf("��ѱ���  ��/֧  ������      ԭ��      ���  ����  ���     ʱ��       ��ע  \n");
		//�����������������Ҫ��ѯ�Ŀ�ʼʱ�䣺���󣬽����û����뿪ʼ��ʱ�䷶Χ
		PointXY(24, 2);
		scanf("%04d.%02d.%02d", &compareFrom.tm_year, &compareFrom.tm_mon, &compareFrom.tm_mday);
		getchar();
		//�����������������Ҫ��ѯ�Ľ���ʱ�䣺�����󣬽����û����������ʱ�䷶Χ
		PointXY(24, 3);
		scanf("%04d.%02d.%02d", &compareTo.tm_year, &compareTo.tm_mon, &compareTo.tm_mday);
		getchar();

		//����ر�����ֵ���е���
		compareTo.tm_year -= 1900;
		compareFrom.tm_year -= 1900;
		compareTo.tm_mon -= 1;
		compareFrom.tm_mon -= 1;
		foundCount = 0;

		//�����ṹ�����飬Ѱ�������з���ʱ�䷶Χ�ڵ�Ԫ�أ�����ӡ������
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
			printf("����Ҫ���ҵ���Ϣ�����ڡ�                                                    ");
		}


		break;
		//���վ����˽��в�ѯ(c)
	case 'c':
		//�����Ű�
		system("cls");
		printf("���˵�->��ѯ��Ϣ->���վ����˽��в�ѯ\n");
		printf("****************************************************************************\n");
		//��ʾ�û����������Ϣ
		printf("������Ҫ��ѯ�ľ��������ƣ�\n");
		//��ʽ�Ű�
		printf("****************************************************************************\n");
		printf("��ѱ���  ��/֧  ������      ԭ��      ���  ����  ���     ʱ��       ��ע  \n");
		//������ƶ�����������Ҫ��ѯ�ľ��������ƣ����󣬽����û��������Ϣ
		PointXY(26, 2);
		getchar();
		gets(searchName);

		//����ر�����ֵ���е���
		foundCount = 0;

		//�����ṹ�������У�Ѱ�������о�����һ�µ�Ԫ�أ�����ӡ������
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
			printf("����Ҫ���ҵ���Ϣ�����ڡ�                                                    ");
		}
		break;
	default:
		printf("����������Ч���ַ������������룺\n");
		break;
	}
	system("pause>nul");
}

//ģ��4�������Ϣ�޸�
//*******************************************************************************************
//�����������������־�ĺ���
void writeLogToFile_change(int index, int id, char *type, char *from, char *to, FILE *fp)
{
	time(&logt);
	loglt = localtime(&logt);
	fprintf(fp, "%04d.%02d.%02d ������Ϊ%d,���Ϊ%d��%s��%s�޸�Ϊ%s\n", ((loglt->tm_year) + 1900), ((loglt->tm_mon) + 1), loglt->tm_mday, index, id, type, from, to);
}
//�޸İ����Ϣģ��
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
	printf("���˵�->�޸���Ϣ\n");
	printf("****************************************************************************\n");
	printf("������Ҫ�޸ĵİ�ѱ��룺");
	PointXY(24, 2);
	//	getchar();
	scanf("%d", &id);
	printf("****************************************************************************\n");
	count = 0;
	for (i = 0; i < size; i++)
	{
		if (sf[i].id == id)
		{
			printf("��ѱ���  ��/֧  ������      ԭ��      ���  ����  ���     ʱ��       ��ע  \n");
			printData(sf, i, count + 5);
			count++;
			break;
		}
	}
	if (count == 0)
	{
		printf("����Ҫ���ҵ���Ϣ�����ڡ�\n");
	}
	else
	{
		printf("�Ƿ�����޸ģ�(y/n)\n");
		getchar();
		if (opt = getchar() == 'y')
		{

			do
			{
				system("cls");
				printf("���˵�->�޸���Ϣ->���޸ĵı��Ϊ:%d\n", id);
				printf("****************************************************************************\n");
				printf("��ѡ������һ������޸ģ�\n");
				printf("1) ��ѱ���\n");
				printf("2) ���뻹��֧��\n");
				printf("3) ������\n");
				printf("4) ԭ��\n");
				printf("5) ��ÿλͬѧ��\n");
				printf("6) ����\n");
				printf("7) ��ע\n");
				printf("8) ʱ��\n");

				printf("\n����ѡ��");
				scanf("%d", &choice);
				getchar();
				switch (choice)
				{
				case 1:
					printf("�������µİ�ѱ��룺");
					itoa(sf[i].id, logFrom, 10);
					tmp = sf[i].id;
					scanf("%d", &sf[i].id);
					getchar();
					itoa(sf[i].id, logTo, 10);
					writeLogToFile_change(i, tmp, "��ѱ���", logFrom, logTo, fp);

					break;
				case 2:

					while (1)
					{
						printf("�������µ����ͣ�");
						strcpy(logFrom, sf[i].type);
						gets(sf[i].type);
						strcpy(logTo, sf[i].type);
						writeLogToFile_change(i, sf[i].id, "����", logFrom, logTo, fp);

						if (i == 0 && !strcmp(sf[i].type, "֧��"))
						{
							printf("\n<!>��һ�����ˣ��޷�֧�������������룡\n");
						}
						else if (!strcmp(sf[i].type, "����") || !strcmp(sf[i].type, "֧��"))
						{
							for (j = i; j < size; j++)
							{
								if (!strcmp(sf[j].type, "����"))
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
							printf("\n<!>����������Ч�ַ������������룡\n");
						}
					}
					break;
				case 3:
					printf("�������µľ����ˣ�");
					strcpy(logFrom, sf[i].name);
					gets(sf[i].name);
					strcpy(logTo, sf[i].name);
					writeLogToFile_change(i, sf[i].id, "������", logFrom, logTo, fp);
					break;
				case 4:
					printf("�������µ�ԭ��");
					strcpy(logFrom, sf[i].reason);
					gets(sf[i].reason);
					strcpy(logTo, sf[i].reason);
					writeLogToFile_change(i, sf[i].id, "ԭ��", logFrom, logTo, fp);
					break;
				case 5:
					printf("�������µĽ��(ÿλͬѧ)��");
					itoa(sf[i].amount, logFrom, 10);
					scanf("%d", &sf[i].amount);
					getchar();
					itoa(sf[i].amount, logTo, 10);
					writeLogToFile_change(i, sf[i].id, "���", logFrom, logTo, fp);
					for (j = i; j < size; j++)
					{
						if (!strcmp(sf[j].type, "����"))
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
					printf("�������µ�������");
					itoa(sf[i].count, logFrom, 10);
					scanf("%d", &sf[i].count);
					itoa(sf[i].count, logTo, 10);
					writeLogToFile_change(i, sf[i].id, "����", logFrom, logTo, fp);
					getchar();
					for (j = i; j < size; j++)
					{
						if (!strcmp(sf[j].type, "����"))
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
					printf("�������µı�ע��");
					strcpy(logFrom, sf[i].remark);
					gets(sf[i].remark);
					strcpy(logTo, sf[i].remark);
					writeLogToFile_change(i, sf[i].id, "��ע", logFrom, logTo, fp);
					break;
				case 8:
					printf("�������µ�ʱ�䣺");
					time(&logt);
					loglt = localtime(&logt);
					fprintf(fp, "%d.%d.%d ������Ϊ%d,���Ϊ%d��ʱ���%d.%d.%d", ((loglt->tm_year) + 1900), ((loglt->tm_mon) + 1), loglt->tm_mday, i, sf[i].id, (sf[i].sctime.tm_year + 1900), (sf[i].sctime.tm_mon + 1), sf[i].sctime.tm_mday);
					scanf("%04d.%02d.%02d", &sf[i].sctime.tm_year, &sf[i].sctime.tm_mon, &sf[i].sctime.tm_mday);
					getchar();

					sf[i].sctime.tm_year -= 1900;
					sf[i].sctime.tm_mon -= 1;
					fprintf(fp, "�޸�Ϊ%d.%d.%d\n", (sf[i].sctime.tm_year + 1900), (sf[i].sctime.tm_mon + 1), sf[i].sctime.tm_mday);
					break;
				default:
					break;
				}
				printf("�Ƿ���������ֶ�(y/n)��");
			} while (opt = getchar() == 'y');
			system("cls");
			printf("���˵�->�޸���Ϣ->�޸ĺ����Ϣ\n");
			printf("****************************************************************************\n");
			printf("��ѱ���  ��/֧  ������      ԭ��      ���  ����  ���     ʱ��       ��ע  \n");
			printData(sf, i, count + 3);
		}
	}
}


//ģ��5�������Ϣɾ��
//*******************************************************************************************
//�����������������־�ĺ���
void writeLogToFile_delete(int index, int id, FILE *fp)
{
	time(&logt);
	loglt = localtime(&logt);
	fprintf(fp, "%04d.%02d.%02d ������Ϊ%d��λ��ɾ����һ�����Ϊ%d������\n", ((loglt->tm_year) + 1900), ((loglt->tm_mon) + 1), loglt->tm_mday, index, id);
}
//ɾ�������Ϣģ��
int delInfo(struct current sf[], int size, FILE *fp)
{
	int id;				//���ڴ洢�û������Ҫɾ���İ�ѱ��
	int i, j;			//����ѭ������ʱ����
	char opt = 0;		//���ڴ洢�û��Ĳ�����

	//�����Ű�
	system("cls");
	printf("���˵�->ɾ����Ϣ\n");
	printf("****************************************************************************\n");
	//��ʾ�û����������Ϣ
	printf("������Ҫɾ���İ�ѱ�ţ�");
	scanf("%d", &id);
	printf("****************************************************************************\n");
	for (i = 0; i < size; i++)
	{
		if (sf[i].id == id)
		{
			printf("��ѱ���  ��/֧  ������      ԭ��      ���  ����  ���     ʱ��       ��ע  \n");
			printData(sf, i, 5);
			break;
		}
	}
	printf("****************************************************************************\n");
	printf("�Ƿ����ɾ����");
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



//ģ��6���ļ���дģ��
//*******************************************************************************************
//�ļ�����ģ��
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
		printf("��⵽�б������Ϣ���Ƿ���(y/n):");
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
//�ļ�д��ģ��
void saveToFile(current sf[], int size)
{
	printf("\n���ڱ��桭��\n");
	FILE *pFile;
	int i;
	if ((pFile = fopen("SchoolFee.dat", "wb")) == NULL)
	{
		printf("�޷����ļ�");
		return;
	}
	if (fwrite(&size, sizeof(int), 1, pFile) != 1)
	{
		printf("�ļ��޷�д��");
	}
	for (i = 0; i < size; i++)
	{
		if (fwrite(&sf[i], sizeof(current), 1, pFile) != 1)
		{
			printf("�ļ��޷�д��");
		}
	}
	fclose(pFile);
	return;
}

//������
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
		printf("���˵�\n");
		printf("****************************************************************************\n");
		printf("��ӭʹ�ð�ѹ���ϵͳ!\n\n");//9
		printf("(1) ¼������Ϣ\n");
		printf("(2) ������а����Ϣ\n");
		printf("(3) ��ѯ�����Ϣ\n");
		printf("(4) �޸İ����Ϣ\n");
		printf("(5) ɾ�������Ϣ\n");
		printf("(0) �˳�ϵͳ\n");
		printf("\n����������Ҫִ�еĲ��������ֱ�ţ�\n");

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
			printf("����������Ч�����֣�");
			break;
		}
	} while (opt != 0);

	fclose(fp);
	return 0;
}
