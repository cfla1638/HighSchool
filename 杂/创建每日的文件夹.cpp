#include <cstdio>
#include <windows.h>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>										//用于数字与字符串类型的转换
using namespace std;
 
//结构体
typedef struct 
{
	int everyDayFlag;									//文件创建标记
	int day;
	int fileDisplayDay;
}DataChangeType;

//函数声明
void InitDataChangeType(DataChangeType &DCT);			//初始化数据交换的结构体，测试用
void CreateDir(string DirLocation);						//创建指定的目录
void SaveFile(DataChangeType DCT);						//保存数据，以便于下次执行
void ReadFile(DataChangeType &DCT);						//将数据读取到程序中，以便于下次执行
void DisPlay(DataChangeType DCT);						//测试用
void MarkDirLocation(string &dirLocation, int date, string subjectType);	//制作目录地址
string _ToString(int n);								//数字转成字符串，用于制作地址时int与string的转换

//主函数
int main(int argc, char const *argv[])
{

	DataChangeType DCT;

	ReadFile(DCT);										//读档

	//获取当前的时间，以便于比较
	time_t nowTime;
	struct tm *tmTime;
	nowTime = time(NULL);
	tmTime = localtime(&nowTime);
	
	//比较当前时间与读取的时间是否相同
	//如果不同则同步时间并设置everyDayFlag
	if (tmTime->tm_yday != DCT.day)
	{
		DCT.everyDayFlag = 0;
		DCT.day = tmTime->tm_yday;
	}

	//创建目录
	if (!DCT.everyDayFlag)
	{
		string dirLocation;
		MarkDirLocation(dirLocation, DCT.fileDisplayDay, "Math");
		CreateDir(dirLocation);
		MarkDirLocation(dirLocation, DCT.fileDisplayDay, "biology");
		CreateDir(dirLocation);
		MarkDirLocation(dirLocation, DCT.fileDisplayDay, "Chemistry");
		CreateDir(dirLocation);
		MarkDirLocation(dirLocation, DCT.fileDisplayDay, "English");
		CreateDir(dirLocation);
		MarkDirLocation(dirLocation, DCT.fileDisplayDay, "physical");
		CreateDir(dirLocation);
		MarkDirLocation(dirLocation, DCT.fileDisplayDay, "Chinese");
		CreateDir(dirLocation);
		DCT.everyDayFlag = 1;
		DCT.fileDisplayDay++;
	}

	//保存当前的数据，以便于下次程序执行
	SaveFile(DCT);
	
	return 0;
}

void DisPlay(DataChangeType DCT)
{
	cout<<"everyDayFlag:"<<DCT.everyDayFlag<<endl;
	cout<<"day:"<<DCT.day<<endl;
}

void ReadFile(DataChangeType &DCT)
{
	FILE *fp;

	fp=fopen("DataChangeFile.txt","r");
	fscanf(fp, "everyDayFlag:%d\nday:%d\n", &DCT.everyDayFlag, &DCT.day);
	fscanf(fp, "fileDisplayDay:%d\n", &DCT.fileDisplayDay);
	fclose(fp);
}

void SaveFile(DataChangeType DCT)
{
	FILE *fp;

	fp=fopen("DataChangeFile.txt", "w");
	fprintf(fp, "everyDayFlag:%d\nday:%d\n", DCT.everyDayFlag, DCT.day);
	fprintf(fp, "fileDisplayDay:%d\n", DCT.fileDisplayDay);
	fclose(fp);
}

void InitDataChangeType(DataChangeType &DCT)
{
	time_t nowTime;
	struct tm *tmTime;

	nowTime = time(NULL);
	tmTime = localtime(&nowTime);

	DCT.everyDayFlag = 0;
	DCT.day = tmTime->tm_yday;
	DCT.fileDisplayDay = 32;
}

void CreateDir(string DirLocation)
{
	CreateDirectory(DirLocation.c_str(), NULL);
}

void MarkDirLocation(string &dirLocation, int date,string subjectType)
{
	string strDate;

	dirLocation = "E:\\HomeStudy\\";
	dirLocation = dirLocation + subjectType + "\\";
	strDate = _ToString(date);
	dirLocation = dirLocation + strDate;
}

string _ToString(int n)
{
	ostringstream stream;
	stream<<n;
	return stream.str();
}
