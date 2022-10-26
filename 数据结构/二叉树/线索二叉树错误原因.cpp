/*
	主函数中：
	InThreading(T);
	traverse_PreOrder(T);
	这两个单独调用均没有任何问题
	但两个同时调用是是却陷入死循环
	因为 InThreading(T);
	这个线索化函数是二叉树的空指针被改为它的前驱或后继
	所以不能同时调用
*/

//线索二叉树及其相关操作
#include <iostream>
#include <cstdio>

using namespace std;
//结构体
typedef struct BiTNode
{
	char data;
	struct BiTNode *left, *right;
	int LTag, RTag;
} BiTNode, *BiTree;
//全局变量
BiTree Pre;

//函数声明
void CreateBiTree(BiTree &T);	   //手动创建二叉树
void IniBiTree(BiTree &T);		   //初始化二叉树
void traverse_InOrder(BiTree T);   //中序遍历
void traverse_PreOrder(BiTree T);  //先序遍历
void traverse_PostOrder(BiTree T); //后序遍历
void InThreading(BiTree &T);	   //中序线索化
//主函数
int main()
{
	BiTree T;
	Pre = new BiTNode;
	Pre->right = NULL;
	IniBiTree(T);
	//错误在这里
	InThreading(T);
	traverse_PreOrder(T);
	//到这里
	return 0;
}
//创建二叉树
void CreateBiTree(BiTree &T)
{
	char ch;
	cout << "请输入：";
	cin >> ch;
	if (ch == '#')
	{
		T = NULL;
	}
	else
	{
		T = new BiTNode;
		T->data = ch;
		CreateBiTree(T->left);
		CreateBiTree(T->right);
	}
}
//直接创建二叉树（初始化）
void IniBiTree(BiTree &T)
{
	//根节点
	T = new BiTNode;
	T->data = 'a';
	T->right = NULL;						   //根节点没有右子树
	T->left = new BiTNode;					   //申请B节点
	T->left->data = 'b';					   //设置b节点的数据域
	T->left->left = new BiTNode;			   //申请c节点
	T->left->left->data = 'c';				   //设置c节点的数据域
	T->left->left->left = NULL;				   // c节点无左子树
	T->left->left->right = NULL;			   // c节点无右子树
	T->left->right = new BiTNode;			   //申请d节点
	T->left->right->data = 'd';				   //设置d节点的数据域
	T->left->right->left = new BiTNode;		   //申请e节点
	T->left->right->left->data = 'e';		   //设置e结点的数据域
	T->left->right->left->left = NULL;		   // e节点没有左子树
	T->left->right->left->right = new BiTNode; //申请g节点
	T->left->right->left->right->data = 'g';   //设置g节点的数据域
	T->left->right->left->right->left = NULL;
	T->left->right->left->right->right = NULL;
	T->left->right->right = new BiTNode; //申请f节点
	T->left->right->right->data = 'f';
	T->left->right->right->left = NULL;
	T->left->right->right->right = NULL;
}
void traverse_InOrder(BiTree T)
{
	if (T)
	{
		traverse_InOrder(T->left);
		cout << T->data << " ";
		traverse_InOrder(T->right);
	}
}
//先序遍历：
void traverse_PreOrder(BiTree T)
{
	if (T)
	{
		cout << T->data << " ";
		traverse_PreOrder(T->left);
		traverse_PreOrder(T->right);
	}
}
//后序遍历：
void traverse_PostOrder(BiTree T)
{
	if (T)
	{
		traverse_PostOrder(T->left);
		traverse_PostOrder(T->right);
		cout << T->data << " ";
	}
}
//中序线索化
void InThreading(BiTree &T)
{
	system("pause");
	if (T) //根节点非空
	{
		InThreading(T->left); //左子树线索化
		if (!T->left)		  // T的左孩子为空
		{
			T->LTag = 1;
			T->left = Pre;
		}
		else
		{
			T->LTag = 0;
		}
		if (!Pre->right) // T的右孩子为空
		{
			Pre->RTag = 1;
			Pre->right = T;
		}
		else
		{
			Pre->RTag = 0;
		}
		Pre = T;
		InThreading(T->right);
	}
}
