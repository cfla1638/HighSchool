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
	printf("您是否需要读取存档？\n\n");
	printf("●读取存档 输入'1'\n\n●重建 输入'2'\n\n●退出：0\n\n");
	printf("请选择（默认:1）:");
	scanf("%d", &n);
	if (n == 1)
	{
		printf("\n");
		printf("********************************************************************************\n");
		head = load();
		printf("读取成功！\n\n");
		printf("任意键继续....");
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
		printf("输入失败，请重试！");
		sleep(1);
		system("cls");
		goto lab1;
	}

lab2:
	printf("\n\n");
	printf("\t\t\t\t主界面\n");
	printf("\t\t*****************************************\n\t\t*\t\t\t\t\t*\n\t\t*");
	printf("\t登陆:1\t注册:2\t退出:0\t\t*\n\t\t*\t\t\t\t\t*\n");
	printf("\t\t*****************************************\n");
	printf("\t\t请输入:");
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
			printf("\t\t\t\t主界面\n");
			printf("\t\t*****************************************\n\t\t*\t\t\t\t\t*\n\t\t*");
			printf("\t登陆:1\t注册:2\t退出:0\t\t*\n\t\t*\t\t\t\t\t*\n");
			printf("\t\t*****************************************\n");
			printf("\t\t请输入:");
			scanf("%d", &x);
			break;
		case 2:
			re_gister(head);
			system("cls");
			printf("\n\n");
			printf("\n\n");
			printf("\t\t\t\t主界面\n");
			printf("\t\t*****************************************\n\t\t*\t\t\t\t\t*\n\t\t*");
			printf("\t登陆:1\t注册:2\t退出:0\t\t*\n\t\t*\t\t\t\t\t*\n");
			printf("\t\t*****************************************\n");
			printf("\t\t请输入:");
			scanf("%d", &x);
			break;
		case 0:
			over(head);
		default:
			printf("错误，请重试!");
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
		printf("请输入管理员账号：");
		scanf("%s", head->account);
		printf("请输入管理员密码：");
		scanf("%s", head->password);
		strcpy(head->txt, "ADMINISTRATOR"); //给管理元加标记
		head->point = NULL;
		end = head;
		return head;
	}
	else
	{
		printf("失败,请重试！");
		getch();
		system("cls");
		return NULL;
	}
}

int menu()
{
	int k;
	printf("\n");
	printf("\t\t\t\t主界面\n");
	printf("    *********************************************************************\n");
	printf("    *\t查看:1\t查找:2\t清除:3\t储存:4\t退出:0\t\t\t\t*\n");
	printf("    *\t\t\t\t\t\t\t\t\t*\n");
	printf("    *********************************************************************\n");
	printf("    请输入要执行的操作：");
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
	printf("请输入账号:");
	scanf("%s", acco_unt);
	printf("请输入密码:");
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
				return 0; //管理元返还0
			}
			else
			{
				return 1; //费管理员1
			}
		}
		else
		{
			printf("密码错误！");
			getch();
			system("cls");
			return 3;
		}
	}
	else
	{
		printf("没有这个账号！");
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
		printf("请输入要注册的账号：");
		scanf("%s", acco_unt);
		q = search(head, acco_unt);
		if (q == NULL)
		{
			strcpy(n->account, acco_unt);
			printf("请输入要注册账号的密码：");
			scanf("%s", n->password);
			printf("请输入要储存的文本：");
			scanf("%s", n->txt);
			end->point = n;
			n->point = NULL;
			end = n;
			system("cls");
		}
		else
		{
			printf("账号已存在！");
			getch();
			system("cls");
		}
	}
	else
	{
		system("cls");
		printf("链表未建立");
		getch();
		system("cls");
	}
}

void wrong()
{
	system("cls");
	printf("输入错误");
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
			printf("第%d个的文本是:%s\n", a, p->txt);
			p = p->point;
			a++;
		}
		getch();
		system("cls");
	}
	else
	{
		system("cls");
		printf("链表未建立");
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
		printf("请输入要查看的账号：");
		scanf("%s", acc_ount);
		p = search(head, acc_ount);
		if (p != NULL)
		{
			printf("您要查看的元素的文本为：\n%s", p->txt);
			getch();
			system("cls");
		}
		else
		{
			printf("没有这个账号！");
			getch();
			system("cls");
		}
	}
	else
	{
		system("cls");
		printf("链表未建立");
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
		printf("请输入要清空的账号:");
		scanf("%s", acco_unt);
		q = search(p, acco_unt);
		if (q != NULL)
		{
			for (i = 0; i < A; i++)
			{
				q->txt[i] = '\0';
			}
			printf("已清除!");
			getch();
			system("cls");
		}
		else
		{
			printf("没有这个账号");
			getch();
			system("cls");
		}
	}
	else
	{
		printf("链表未建立!");
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
		printf("请输入要写入的账号:");
		scanf("%s", acco_unt);
		q = search(p, acco_unt);
		if (q != NULL)
		{
			printf("请输入要写入的文本:");
			scanf("%s", q->txt);
			printf("已写入!");
			getch();
			system("cls");
		}
		else
		{
			printf("找不到账号!");
		}
	}
	else
	{
		printf("链表未建立!");
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
	f = fopen("链表操作.dat", "w+");
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
		printf("文件不能打开!");
		;
	}
	fclose(f);
}

node *load()
{
	FILE *f;
	node *head, *next, *end;
	f = fopen("链表操作.dat", "r+");
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
	printf("管理员登录成功！\n");
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
	printf("登陆成功！！！\n");
	printf("********************************************************************************\n");
	printf("%s\n\n", temp->txt);
	printf("********************************************************************************\n");
	printf("您可以进行以下操作：\n\n");
	printf("储存:1\t修改密码:2\t退出:0\n\n");
	printf("请选择:");
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
			printf("请输入要储存的内容:");
			scanf("%s", temp->txt);
			printf("\n已储存！");
			getch();
			system("cls");
			printf("********************************************************************************\n");
			printf("%s\n\n", temp->txt);
			printf("********************************************************************************\n");
			printf("您可以进行以下操作：\n\n");
			printf("储存:1\t修改密码:2\t退出:0\n\n");
			printf("请选择:");
			scanf("%d", &u);
			break;
		case 2:
			system("cls");
			printf("\n\n请输入新密码:");
			scanf("%s", first);
			printf("请再次输入:");
			scanf("%s", second);
			if (strcmp(first, second) == 0)
			{
				strcpy(temp->password, first);
				printf("修改成功!");
				getch();
				system("cls");
			}
			else
			{
				printf("错误!!!\n请重试！");
				getch();
			}
			system("cls");
			printf("********************************************************************************\n");
			printf("%s\n\n", temp->txt);
			printf("********************************************************************************\n");
			printf("您可以进行以下操作：\n\n");
			printf("储存:1\t修改密码:2\t退出:0\n\n");
			printf("请选择:");
			scanf("%d", &u);
			break;
		default:
			wrong();
			printf("********************************************************************************\n");
			printf("%s\n\n", temp->txt);
			printf("********************************************************************************\n");
			printf("您可以进行以下操作：\n\n");
			printf("储存:1\t修改密码:2\t退出:0\n\n");
			printf("请选择:");
			scanf("%d", &u);
		}
	}
}
