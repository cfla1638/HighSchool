#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define A 50
#define B 50
#define C 500

typedef struct massage
{
	char account[A];
	char password[B];
	char txt[C];
	struct massage *point;
} node;

node *temp;

int menu();
int land(node *head);
void re_gister(node *head);
void wrong();
void print(node *head);
void find(node *head);
void over(node *head);
void clean(node *head);
void write(node *head);
void save(node *head);
node *createline();
node *load();
node *search(node *head, char acc_ount[A]);
void admin(node *head);
void noadmin(node *head);

int main()
{
	system("color 02");
	node *head;
	int m, n, x, y, z;
	head = NULL;
lab1:
	printf("���Ƿ���Ҫ��ȡ�浵��\n\n");
	printf("���ȡ�浵 ����'1'\n\n���ؽ� ����'2'\n\n���˳���0\n\n");
	printf("��ѡ��Ĭ��:1��:");
	scanf("%d", &n);
	if (n == 1)
	{
		printf("\n");
		printf("********************************************************************************\n");
		head = load();
		printf("��ȡ�ɹ���\n\n");
		printf("���������....");
		getch();
		system("cls");
		goto lab2;
	}
	else if (n == 2)
	{
		printf("\n");
		printf("********************************************************************************\n");
		head = createline();
		sleep(1);
		system("cls");
		goto lab2;
	}
	else if (n == 0)
	{
		exit(0);
	}
	else
	{
		printf("����ʧ�ܣ������ԣ�");
		sleep(1);
		system("cls");
		goto lab1;
	}

lab2:
	printf("\n\n");
	printf("\t\t\t\t������\n");
	printf("\t\t*****************************************\n\t\t*\t\t\t\t\t*\n\t\t*");
	printf("\t��½:1\tע��:2\t�˳�:0\t\t*\n\t\t*\t\t\t\t\t*\n");
	printf("\t\t*****************************************\n");
	printf("\t\t������:");
	scanf("%d", &x);
	while (1)
	{
		switch (x)
		{
		case 1:
			y = land(head);
			if (y == 0)
			{
				admin(head);
			}
			else if (y == 3)
			{
				goto lab2;
			}
			else
			{
				noadmin(head);
			}
			system("cls");
			printf("\n\n");
			printf("\t\t\t\t������\n");
			printf("\t\t*****************************************\n\t\t*\t\t\t\t\t*\n\t\t*");
			printf("\t��½:1\tע��:2\t�˳�:0\t\t*\n\t\t*\t\t\t\t\t*\n");
			printf("\t\t*****************************************\n");
			printf("\t\t������:");
			scanf("%d", &x);
			break;
		case 2:
			re_gister(head);
			system("cls");
			printf("\n\n");
			printf("\n\n");
			printf("\t\t\t\t������\n");
			printf("\t\t*****************************************\n\t\t*\t\t\t\t\t*\n\t\t*");
			printf("\t��½:1\tע��:2\t�˳�:0\t\t*\n\t\t*\t\t\t\t\t*\n");
			printf("\t\t*****************************************\n");
			printf("\t\t������:");
			scanf("%d", &x);
			break;
		case 0:
			over(head);
		default:
			printf("����������!");
			sleep(1);
		}
	}
	return 0;
}

node *createline()
{
	node *head, *end, *next, *p;
	head = (node *)malloc(sizeof(node));
	if (head != NULL)
	{
		printf("���������Ա�˺ţ�");
		scanf("%s", head->account);
		printf("���������Ա���룺");
		scanf("%s", head->password);
		strcpy(head->txt, "ADMINISTRATOR"); //������Ԫ�ӱ��
		head->point = NULL;
		end = head;
		return head;
	}
	else
	{
		printf("ʧ��,�����ԣ�");
		getch();
		system("cls");
		return NULL;
	}
}

int menu()
{
	int k;
	printf("\n");
	printf("\t\t\t\t������\n");
	printf("    *********************************************************************\n");
	printf("    *\t�鿴:1\t����:2\t���:3\t����:4\t�˳�:0\t\t\t\t*\n");
	printf("    *\t\t\t\t\t\t\t\t\t*\n");
	printf("    *********************************************************************\n");
	printf("    ������Ҫִ�еĲ�����");
	scanf("%d", &k);
	return k;
}

int land(node *head) //	if(strcmp(mim,smim)!=0)
{
	char acco_unt[A];
	char pass_word[B], stand[C] = "ADMINISTRATOR";
	node *p, *q;
	p = head;
	system("cls");
lab3:
	printf("�������˺�:");
	scanf("%s", acco_unt);
	printf("����������:");
	scanf("%s", pass_word);
	q = search(p, acco_unt);
	if (q != NULL)
	{
		if (strcmp(q->password, pass_word) == 0)
		{
			system("cls");
			temp = q;
			if (strcmp(q->txt, stand) == 0)
			{
				return 0; //����Ԫ����0
			}
			else
			{
				return 1; //�ѹ���Ա1
			}
		}
		else
		{
			printf("�������");
			getch();
			system("cls");
			return 3;
		}
	}
	else
	{
		printf("û������˺ţ�");
		getch();
		system("cls");
		return 3;
	}
}

void re_gister(node *head)
{
	char acco_unt[A];
	node *end, *p, *n, *q;
	system("cls");
	if (head != NULL)
	{
		p = head;
		while ((p->point) != NULL)
		{
			p = p->point;
		}
		end = p;
		n = (node *)malloc(sizeof(node));
		printf("������Ҫע����˺ţ�");
		scanf("%s", acco_unt);
		q = search(head, acco_unt);
		if (q == NULL)
		{
			strcpy(n->account, acco_unt);
			printf("������Ҫע���˺ŵ����룺");
			scanf("%s", n->password);
			printf("������Ҫ������ı���");
			scanf("%s", n->txt);
			end->point = n;
			n->point = NULL;
			end = n;
			system("cls");
		}
		else
		{
			printf("�˺��Ѵ��ڣ�");
			getch();
			system("cls");
		}
	}
	else
	{
		system("cls");
		printf("����δ����");
		getch();
		system("cls");
	}
}

void wrong()
{
	system("cls");
	printf("�������");
	getch();
	system("cls");
}

void print(node *head)
{
	node *p;
	p = head;
	int a = 1;
	system("cls");
	if (p != NULL)
	{
		while (p != NULL)
		{
			printf("��%d�����ı���:%s\n", a, p->txt);
			p = p->point;
			a++;
		}
		getch();
		system("cls");
	}
	else
	{
		system("cls");
		printf("����δ����");
		getch();
		system("cls");
	}
}

node *search(node *head, char acc_ount[A])
{
	node *p, *q;
	q = head;
	while (strcmp(acc_ount, q->account) != 0)
	{
		q = q->point;
		if (q == NULL)
		{
			return NULL;
		}
	}
	return q;
}

void find(node *head)
{
	node *p;
	char acc_ount[A];
	system("cls");
	if (head != NULL)
	{
		printf("������Ҫ�鿴���˺ţ�");
		scanf("%s", acc_ount);
		p = search(head, acc_ount);
		if (p != NULL)
		{
			printf("��Ҫ�鿴��Ԫ�ص��ı�Ϊ��\n%s", p->txt);
			getch();
			system("cls");
		}
		else
		{
			printf("û������˺ţ�");
			getch();
			system("cls");
		}
	}
	else
	{
		system("cls");
		printf("����δ����");
		getch();
		system("cls");
	}
}

void over(node *head)
{
	save(head);
	exit(0);
}

void clean(node *head)
{
	system("cls");
	char acco_unt[A], null[A];
	int i;
	node *q, *p;
	p = head;
	if (p != NULL)
	{
		printf("������Ҫ��յ��˺�:");
		scanf("%s", acco_unt);
		q = search(p, acco_unt);
		if (q != NULL)
		{
			for (i = 0; i < A; i++)
			{
				q->txt[i] = '\0';
			}
			printf("�����!");
			getch();
			system("cls");
		}
		else
		{
			printf("û������˺�");
			getch();
			system("cls");
		}
	}
	else
	{
		printf("����δ����!");
		getch();
		system("cls");
	}
}

void write(node *head)
{
	system("cls");
	node *p, *q;
	char acco_unt[A];
	p = head;
	if (p != NULL)
	{
		printf("������Ҫд����˺�:");
		scanf("%s", acco_unt);
		q = search(p, acco_unt);
		if (q != NULL)
		{
			printf("������Ҫд����ı�:");
			scanf("%s", q->txt);
			printf("��д��!");
			getch();
			system("cls");
		}
		else
		{
			printf("�Ҳ����˺�!");
		}
	}
	else
	{
		printf("����δ����!");
		getch();
		system("cls");
	}
}

void save(node *head)
{
	FILE *f;
	node *p;
	p = head;
	f = NULL;
	f = fopen("�������.dat", "w+");
	if (f != NULL)
	{
		while (p != NULL)
		{
			fprintf(f, "%s %s %s ", p->account, p->password, p->txt);
			p = p->point;
		}
	}
	else
	{
		printf("�ļ����ܴ�!");
		;
	}
	fclose(f);
}

node *load()
{
	FILE *f;
	node *head, *next, *end;
	f = fopen("�������.dat", "r+");
	head = (node *)malloc(sizeof(node));
	fscanf(f, "%s %s %s ", head->account, head->password, head->txt);
	head->point = NULL;
	end = head;
	while (!feof(f))
	{
		next = (node *)malloc(sizeof(node));
		fscanf(f, "%s %s %s ", next->account, next->password, next->txt);
		next->point = NULL;
		end->point = next;
		end = next;
	}
	fclose(f);
	return head;
}

void admin(node *head)
{
	printf("����Ա��¼�ɹ���\n");
	printf("********************************************************************************\n");
	int o, p, q;
	p = 1;
	while (p != 0)
	{
		o = menu();
		switch (o)
		{
		case 1:
			print(head);
			break;
		case 2:
			find(head);
			break;
		case 3:
			clean(head);
			break;
		case 4:
			write(head);
			break;
		case 0:
			p = 0;
			break;
		default:
			wrong();
		}
	}
}

void noadmin(node *head)
{
	int u, v;
	char first[B], second[B];
	v = 1;
	printf("��½�ɹ�������\n");
	printf("********************************************************************************\n");
	printf("%s\n\n", temp->txt);
	printf("********************************************************************************\n");
	printf("�����Խ������²�����\n\n");
	printf("����:1\t�޸�����:2\t�˳�:0\n\n");
	printf("��ѡ��:");
	scanf("%d", &u);
	while (v != 0)
	{
		switch (u)
		{
		case 0:
			temp = NULL;
			v = 0;
			break;
		case 1:
			system("cls");
			printf("������Ҫ���������:");
			scanf("%s", temp->txt);
			printf("\n�Ѵ��棡");
			getch();
			system("cls");
			printf("********************************************************************************\n");
			printf("%s\n\n", temp->txt);
			printf("********************************************************************************\n");
			printf("�����Խ������²�����\n\n");
			printf("����:1\t�޸�����:2\t�˳�:0\n\n");
			printf("��ѡ��:");
			scanf("%d", &u);
			break;
		case 2:
			system("cls");
			printf("\n\n������������:");
			scanf("%s", first);
			printf("���ٴ�����:");
			scanf("%s", second);
			if (strcmp(first, second) == 0)
			{
				strcpy(temp->password, first);
				printf("�޸ĳɹ�!");
				getch();
				system("cls");
			}
			else
			{
				printf("����!!!\n�����ԣ�");
				getch();
			}
			system("cls");
			printf("********************************************************************************\n");
			printf("%s\n\n", temp->txt);
			printf("********************************************************************************\n");
			printf("�����Խ������²�����\n\n");
			printf("����:1\t�޸�����:2\t�˳�:0\n\n");
			printf("��ѡ��:");
			scanf("%d", &u);
			break;
		default:
			wrong();
			printf("********************************************************************************\n");
			printf("%s\n\n", temp->txt);
			printf("********************************************************************************\n");
			printf("�����Խ������²�����\n\n");
			printf("����:1\t�޸�����:2\t�˳�:0\n\n");
			printf("��ѡ��:");
			scanf("%d", &u);
		}
	}
}
