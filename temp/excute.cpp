#include<stdio.h>
#include<stdlib.h>
int chooseFunction();
int chooseFunction()
{
	char ch;
	printf("\n\n\t\t\t\t\t请选择接下来要执行的功能:\n");
	printf("\n\n\t\t\t\t\t     1. 对文件进行压缩\n");
	printf("\n\n\t\t\t\t\t     2. 对字符串进行解码译码\n"); 
	printf("\n\n\t\t\t\t\t     0. 退出系统\n\n->"); 
	ch = getchar();
	return ch - 48;	
}
int main()
{
	int function;
	function = chooseFunction();
	//执行文件功能 
	if(function == 1)
	{
		system("HuffmanToFile.exe");
	} 
	//执行字符串功能 
	else if(function == 2)
	{
		system("HuffmanToString.exe");
	}
	//退出系统 
	else if(function == 3)
	{
		exit(0);
	}
}
