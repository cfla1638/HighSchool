#include <cstdlib>
using namespace std;

int main(int argc, char const *argv[])
{
	system("taskkill /F /IM rainmeter.exe");
	system("start D:\\Rainmeter\\rainmeter.exe");
	return 0;
}