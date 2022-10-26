//二叉树及相关操作
#include <iostream>
#define MAXTSIZE 100
using namespace std;
//树的结构体
typedef struct BiTNode
{
	char data;					  //节点的数据域
	struct BiTNode *left, *right; //节点的左右孩子
} BiTNode, *BiTree;
//函数的声明：
void createtree(BiTree &T);
void traverse_InOrder(BiTree T);
void traverse_PreOrder(BiTree T);
void traverse_PostOrder(BiTree T);
//主函数
int main()
{
	BiTree T;
	createtree(T);
	cout << "中序遍历：";
	traverse_InOrder(T);
	cout << endl;
	cout << "先序遍历：";
	traverse_PreOrder(T);
	cout << endl;
	cout << "后序遍历：";
	traverse_PostOrder(T);
	cout << endl;
	return 0;
}
//先序遍历建立二叉链表
void createtree(BiTree &T)
{
	char ch;
	cout << "请输入:";
	cin >> ch;
	if (ch == '#')
	{
		T = NULL;
	}
	else
	{
		T = new BiTNode;
		T->data = ch;
		createtree(T->left);
		createtree(T->right);
	}
}
//二叉树的中序遍历
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
