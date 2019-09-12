/** 
 *                                     数据结构课程设计 
 *                            利用huffman树，对文件的编码和译码 
 */ 
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<algorithm>
using namespace std;
//节点
typedef struct Tree
{
	unsigned char character;
	int count;
	int left;
	int right;
	int parent;
	char code;
}Tree;
//重构huffmanTree
typedef struct HuffmanTree
{
	unsigned char character;
	char code;
	struct HuffmanTree *left;
	struct HuffmanTree *right;
 }HuffmanTree;
//每个字符的编码
typedef struct CharCode
{
	int count;
	char code[256];
}CharCode;
//统计各字符出现的频率和不同字符的个数
void getEveryCharAndCount(char *sourceFileName,int *chars,int *count);
//初始化哈夫曼树将前count各节点（叶子节点）附字符和频率
void IninHuffmanTree(Tree *tree,int length,int *chars);
//排序策略
bool compare(Tree a,Tree b);
//构建哈夫曼树
void createHuffmanTree(Tree *tree,int length);
//选择字符串中次数最小的两个数 
void selectFirstMinAndSecondMin(Tree *tree,int length,int *FirstMin,int *SecondMin);
//编码字符
void encodeEveryCharacterFromHuffmanTree(Tree *tree,int length,CharCode *code);
//各个字符 频率 编码输出到密码本中 
void PrintCharacterAndCode(CharCode *code,int length,char *passwordFileName);
//将编码后的文件输出到文件中 
void PrintEncodeString(CharCode *code,char *sourceFileName,char *targetFileName); 
//对编码后的字符串进行解码
void decodeAfterEncodeString(Tree *tree,char *encodeString,int length);
//将密码本中的内容放到存储密码的数组中
void readCodeFromPasswordToCode(CharCode *code,int *count,char *passwordFileName); 
//根据code数组重新构建哈夫曼树
void reBuildHuffmanTree(HuffmanTree **tree,CharCode *code);
//将编码后的文件解码
void decodeAfterEncodeFile(HuffmanTree *tree,char *sourceFileName,char *targetFileName);
//编码后的示信息 
void PrintInfoAfterEncodeFile(char *targetFileName,char *password);
//解码后的提示信息 
void PrintInfoAfterDecodeFile(char *targetFileName); 
void PrintInfoAfterDecodeFile(char *targetFileName)
{
	printf("\n\n\t\t\t\t\t\t文件解码完成！！！\n"); 
	printf("\n\t\t\t\t\t  生成了解码文件:%s\n",targetFileName);
	printf("\n\t\t\t如果需要对普通文件进行编码，请重新运行此程序，输入参数模板:\n");
	printf("\n\t\t\t\t     编码解码程序  普通文件  编码文件\n\n\n");
}
void PrintInfoAfterEncodeFile(char *targetFileName,char *password)
{
	printf("\n\n\t\t\t\t\t\t文件编码完成！！！\n"); 
	printf("\n\t\t\t\t\t  生成了编码文件:%s\n",targetFileName);
	printf("\n\t\t\t\t\t  生成了密码文件:%s\n",password);
	printf("\n\t\t\t如果需要对编码文件进行解码，请重新运行此程序，输入参数模板:\n");
	printf("\n\t\t\t\t编码解码程序  编码文件  密码文件 解码文件\n\n\n");
}
//将编码后的文件解码
void decodeAfterEncodeFile(HuffmanTree *tree,char *sourceFileName,char *targetFileName)
{
	//打开被压缩的文件 
 	FILE *fIn = fopen(sourceFileName,"r");
 	//打开解压后的文件的位置 
 	FILE *fOut = fopen(targetFileName,"w");
 	char code;
 	//得到树的根节点 
 	HuffmanTree *p = tree;
 	//按路径每个字符读取 
 	while((code = fgetc(fIn))!=EOF)
 	{
 		//如果该路径为0，则向左走 
 		if(code == '0')
 		{
 			p = p->left;	
		}
		//否则，向右走 
		else
		{
			p = p->right;
		}
		//判断是不是叶子结点，如果是则读取该字符 
		if(p->left == NULL&&p->right == NULL)
		{
			//将该字符输出到解压文件中 
			fputc(p->character,fOut);
			//重置索引节点 
			p = tree;
		}
	}
 }
//根据code数组重新构建哈夫曼树
void reBuildHuffmanTree(HuffmanTree **tree,CharCode *code)
{
	//构建根节点
	(*tree) = (HuffmanTree *)malloc(sizeof(HuffmanTree));
	//重构huffman树的指针 
	HuffmanTree *p = (*tree);
	p->left = NULL;
	p->right = NULL;
	for(int i = 0;i<256;i++)
	{
		//如果该字符存在 
		if(code[i].count!=0)
		{
			//重置索引指针 
			p = (*tree); 
			//遍历该字符的路径重构huffman树 
			//i记录着该字符 
			for(int j = 0;code[i].code[j];j++)
			{
				//如果当前路径为0，则向左走 
				if(code[i].code[j] == '0')
				{
					//如果将要到达的节点为空，则建立该节点 
					if(p->left == NULL)
					{
						//建立该节点 
						p->left = (HuffmanTree *)malloc(sizeof(HuffmanTree));
						//到达该节点 
						p = p->left;
						//初始化左右孩子 
						p->left = NULL;
						p->right = NULL;
					}
					//如果将要到达的节点不为空，则到达该节点 
					else
					{
						p = p->left;
					}
				}
				//如果当前路径为1，则向右走
				else
				{
					//如果将要到达的节点为空，则建立该节点 
					if(p->right == NULL)
					{
						//建立该节点 
						p->right = (HuffmanTree *)malloc(sizeof(HuffmanTree));
						//到达该节点 
						p = p->right;
						//初始化左右孩子 
						p->left = NULL;
						p->right = NULL;
					}
					//如果将要到达的节点不为空，则到达该节点 
					else
					{
						p = p->right;
					}
				//	printf("d");
				}
			}
			//到达了该字符的位置，将该位置的字符赋值 
			p->character = i;
		}
	}
} 
//将密码本中的内容放到存储密码的数组中
void readCodeFromPasswordToCode(CharCode *code,int *count,char *passwordFileName)
{
	//打开密码本文件 
	FILE *fp = fopen(passwordFileName,"r");
	unsigned char character;
	unsigned int num;
	char charCode[256];
	//如果密码本不存在，程序终止 
	if(fp == NULL)
		return;
	//格式化读入数据 
	while(fscanf(fp,"%c %d %s",&character,&num,charCode)!=EOF)
	{
		//记录读入了多少不同的字符 
		(*count)++;
		//设置该字符的频率 
		code[character].count = num;
		//设置该字符的编码 
		strcat(code[character].code,charCode);
		//跳过文件的空格 
		fgetc(fp);
	}
}
//将编码后的文件输出到文件中 
void PrintEncodeString(CharCode *code,char *sourceFileName,char *targetFileName)
{
	//打开源文件 
	FILE *fIn = fopen(sourceFileName,"r");
	//打开要压缩到的文件 
	FILE *fOut = fopen(targetFileName,"w");
	unsigned int ch;
	//如果源文件不存在程序终止 
	if(fIn == NULL)
		return;
	ch=(unsigned int)fgetc(fIn);
	while(!feof(fIn))
	{
		//将字符的编码写到要压缩的文件中 
		fputs(code[(unsigned int)ch].code,fOut);
		ch=(unsigned int)fgetc(fIn);
	}
	//关闭打开的文件 
	fclose(fIn);
	fclose(fOut);
}
//各个字符 频率 编码输出到密码本中 
void PrintCharacterAndCode(CharCode *code,int length,char *passwordFileName)
{
	//打开密码本文件 
	FILE *fp = fopen(passwordFileName,"w");
	for(int i = 0;i<256;i++)
		//如果该字符在文件中存在 
		if(code[i].count)
			//格式化将该字符，频率，路径输出到文件中 
			fprintf(fp,"%c %d %s ",i,code[i].count,code[i].code);
}
//编码字符
void encodeEveryCharacterFromHuffmanTree(Tree *tree,int length,CharCode *code)
{
	int i,k,child,j,t;
	unsigned char character;
	char encode[256];
	//自低向上找到到达根节点的路径就是该字符的编码 
	for(i = 0;i<length;i++)
	{
		k = 0;
		child = i;
		//当前叶子结点的字符 
		character = tree[i].character;
		//一层一层找到根节点并记录路径 
		while(tree[child].parent)
		{
			encode[k++] = tree[child].code;
			//找到child节点的父节点 
			child = tree[child].parent;
		}
		//截至路径 
		encode[k] = '\0';
		t = 0;
		//printf("%d",character);
		//因为路径是倒序的，要获得正确的路径，需要将他从后往前读一遍 
		for(j = k-1;j>=0;j--)
		{
			code[character].code[t++] = encode[j];
		}
		//将该字符的路径截至 
		code[character].code[t] = '\0';
		//设置该字符的频率 
		code[character].count = tree[i].count;
	}
}
//选择字符串中次数最小的两个数 
void selectFirstMinAndSecondMin(Tree *tree,int length,int *FirstMin,int *SecondMin)
{
	//记录频率最小的两个节点的下标 
	int fmin = -1,smin = -1;
	for(int i = 0;i<length;i++)
	{
		//如果该节点还没有父节点 
		if(!tree[i].parent)
		{
			if(fmin == -1||tree[i].count<tree[fmin].count)
			{
				smin = fmin;
				fmin = i;
			}
			else if(smin == -1||tree[i].count<tree[smin].count)
			{
				smin = i;
			}
		}
	}
	//将下标设置到传入的形参中 
	(*FirstMin) = fmin;
	(*SecondMin) = smin;
}
//构建哈夫曼树
void createHuffmanTree(Tree *tree,int length)
{
	//最小值的节点下标，次最小值的节点下标
	int FirstMin,SecondMin;
	//记录每次生成的父节点的下标
	int k = length;
	int i;
	for(i = 0;i<length-1;i++)
	{
		//在没有父母的节点中找两个频率最小的节点的下标 
		selectFirstMinAndSecondMin(tree,k,&FirstMin,&SecondMin);
		//该节点作为父节点，与找到的两个节点建立关系 
		tree[k].left = FirstMin;
		tree[k].right = SecondMin;
		//该节点的频率为两个孩子节点的频率之和 
		tree[k].count = tree[FirstMin].count + tree[SecondMin].count;
		//将两个孩子节点的父节点修改为当前结点 
		tree[FirstMin].parent = k;
		tree[SecondMin].parent = k;
		//到达左孩子的路径为0 
		tree[FirstMin].code = '0'; 
		//到达右孩子的路径为1 
		tree[SecondMin].code = '1';
		//增加父节点 
		k++;
	}
}
//比较策略，从小到大 
bool compare(Tree a,Tree b)
{
	return a.count<b.count;
}
//初始化哈夫曼树将前count各节点（叶子节点）附字符和频率
void InituffmanTree(Tree *tree,int length,int *chars)
{
	int i,k = 0;
	//用到了ascii的补充字符 
	for(i = 0;i<256;i++)
	{
		//如果文件中出现了该字符，则将该字符，频率都初始化的huffman树中 
		if(chars[i])
		{
			//记录当前字符 
			tree[k].character = i;
		//	printf("%c\n",tree[k].character);
			//记录当前字符的频率 
			tree[k].count = chars[i];
			//将指向都变为空 
			tree[k].left = 0;
			tree[k].right = 0;
			tree[k].parent = 0;
			//树的叶子节点自增 
			k++;
		}
	}
/*	for(i = 0;i<k;i++)
		printf("%c",tree[i].character);*/
	sort(tree,tree+k,compare);
	for(;k<length;k++)
	{
		tree[k].count = 0;
		tree[k].left = 0;
		tree[k].right = 0;
		tree[k].parent = 0;
	}
}
//统计各字符出现的频率和不同字符的个数
void getEveryCharAndCount(char *sourceFileName,int *chars,int *count)
{
	int i;
	/*用来记录读取的字符，因为要用的ascii的补充128个字符 ，
	将用来存储字符的变量都声明成无符号unsigned */
	unsigned int ch = 0;
	//打开要压缩的文件 
	FILE *fp = fopen(sourceFileName,"r");
	//如果文件不存在，程序结束 
	if(fp == NULL)
	{
		return;
	}
	//按字符读取文件 
	while((ch=(unsigned int)fgetc(fp))!=EOF)
	{	
		//记录不同的字符的个数 
		if(chars[(unsigned int)ch] == 0)
			(*count)++;
		//统计字符的频率 
		chars[(unsigned int)ch]++;
		//printf("%d\n",chars[(unsigned int)ch]);
		//ch=(unsigned int)fgetc(fp);
	}
	//关闭文件 
	fclose(fp);
}
int main(int fileNum,char **fileName)
{
	CharCode code[256] = {0,0};
	//用来记录各字符出现的频率
	int chars[256] = {0};
	//总共输入的不同字符的个数
	int count = 0;
	//构建哈夫曼树的节点总个数
	int length;
	//哈夫曼树组的首地址
	Tree *tree = NULL;
	//重构哈夫曼树
	HuffmanTree *huffmanTree = NULL; 
	char targetFileName[200] = "\0";
	//创建密码本
	char *password = "password.json"; 
	//对文件进行压缩 
	if(fileNum == 3)
	{
		//源文件   压缩文件 
		strcpy(targetFileName,fileName[2]);
		strcat(targetFileName,".txt");
		getEveryCharAndCount(fileName[1],chars,&count);
		//计算哈夫曼节点的个数
		length = 2*count-1;
		//申请一个长度为length的数组用来构建哈夫曼树
		tree = (Tree *)malloc(sizeof(Tree)*length);
	//	printf("%c",-70);
		//初始化叶子节点
		InituffmanTree(tree,length,chars);
		//构建哈夫曼树
		createHuffmanTree(tree,count);
		printf("%c",tree[2].character);
		//对各字符进行编码
		encodeEveryCharacterFromHuffmanTree(tree,count,code);
		//输出各个字符 编码到密码本 
		PrintCharacterAndCode(code,count,password);
		//编码后的字符串
		PrintEncodeString(code,fileName[1],targetFileName);
		//提示信息
		PrintInfoAfterEncodeFile(targetFileName,password);
	}
	//对文件进行解压 
	else if(fileNum == 4)
	{
		//压缩文件 密码本 解压文件 
		strcpy(targetFileName,fileName[3]);
		strcat(targetFileName,".txt");
		//读取密码本 password 到code中 
		readCodeFromPasswordToCode(code,&count,password);
		//根据code重新构建HuffmanTree 
		reBuildHuffmanTree(&huffmanTree,code);
		//将编码后的文件解码
		decodeAfterEncodeFile(huffmanTree,fileName[1],targetFileName);
		//解码后的提示信息 
		PrintInfoAfterDecodeFile(targetFileName); 
	}
}
