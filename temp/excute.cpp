#include<stdio.h>
#include<stdlib.h>
int chooseFunction();
int chooseFunction()
{
	char ch;
	printf("\n\n\t\t\t\t\t��ѡ�������Ҫִ�еĹ���:\n");
	printf("\n\n\t\t\t\t\t     1. ���ļ�����ѹ��\n");
	printf("\n\n\t\t\t\t\t     2. ���ַ������н�������\n"); 
	printf("\n\n\t\t\t\t\t     0. �˳�ϵͳ\n\n->"); 
	ch = getchar();
	return ch - 48;	
}
int main()
{
	int function;
	function = chooseFunction();
	//ִ���ļ����� 
	if(function == 1)
	{
		system("HuffmanToFile.exe");
	} 
	//ִ���ַ������� 
	else if(function == 2)
	{
		system("HuffmanToString.exe");
	}
	//�˳�ϵͳ 
	else if(function == 3)
	{
		exit(0);
	}
}
