/** 
 *                                     数据结构课程设计 
 *                            利用huffman树，对文件的编码和译码 
 */  
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<windows.h>
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
//每个字符的编码
typedef struct CharCode
{
	int count;
	char code[256];
}CharCode;
//统计各字符出现的频率和不同字符的个数
void getEveryCharAndCount(unsigned char *str,int *chars,int *count);
//初始化哈夫曼树将前count各节点（叶子节点）附字符和频率
void InitHuffmanTree(Tree *tree,int length,int *chars);
//排序策略
bool compare(Tree a,Tree b);
//构建哈夫曼树
void createHuffmanTree(Tree *tree,int length);
//选择字符串中次数最小的两个数 
void selectFirstMinAndSecondMin(Tree *tree,int length,int *FirstMin,int *SecondMin);
//编码字符
void encodeEveryCharacterFromHuffmanTree(Tree *tree,int length,CharCode *code);
//各个字符 频率 编码
void PrintCharacterAndCountAndCode(CharCode *code,int length);
//输出原始字符串
void PrintSrcString(char *str);
//编码字符串并输出
void PrintEncodeString(CharCode *code,unsigned char *str);
//对根据路径进行解码
void decodeAfterEncodeString(Tree *tree,char *encodeString,int length);
//显示菜单项
int ChooseFunction();
//建树 
void BuidTree(Tree *tree,int length,int *chars,int count);
//编码 
void EncodeAndPrint(Tree *tree,int count,CharCode *code,unsigned char *str);
//统计 
Tree *getEveryCharAndCountAndMallocTree(unsigned char *str,int *chars,int *count,int *length);
Tree *getEveryCharAndCountAndMallocTree(unsigned char *str,int *chars,int *count,int *length)
{
	Tree *tree = NULL;
	getEveryCharAndCount(str,chars,count);
	//计算哈夫曼节点的个数
	*length = 2*(*count)-1;
	//申请一个长度为length的数组用来构建哈夫曼树
	tree = (Tree *)malloc(sizeof(Tree)*(*length));
	return tree;
}
void EncodeAndPrint(Tree *tree,int count,CharCode *code,unsigned char *str)
{
	//对各字符进行编码
	encodeEveryCharacterFromHuffmanTree(tree,count,code);
	//输出各个字符 频率 编码
	printf("\n\t\t\t\t对输入字符串构建huffman树后的统计结果:\n\n->"); 
	PrintCharacterAndCountAndCode(code,count);
	//编码后的字符串
	printf("\n\t\t\t\t\t对输入字符串编码后的结果:\n\n->"); 
	PrintEncodeString(code,str);
}

void BuidTree(Tree *tree,int length,int *chars,int count)
{
	//初始化叶子节点
	InitHuffmanTree(tree,length,chars);
	//构建哈夫曼树
	createHuffmanTree(tree,count);
};
//执行哈夫曼编码过程
void excuteHuffManEncode()
{
	
}         
//对根据路径进行解码
void decodeAfterEncodeString(Tree *tree,char *encodeString,int length)
{
	//得到树的根节点 
	int index = length-1;
	for(int i = 0;encodeString[i];i++)
	{
		//如果该路径为0，则向左走
		if(encodeString[i] == '0')
		{
			index = tree[index].left;
		}
		//否则，向右走
		else if(encodeString[i] == '1')
		{
			index = tree[index].right;
		}
		else
		{
			printf("输入的路径有误，请重新输入！！！\n\n");
			break;
		}
		//判断是不是叶子结点，如果是则读取该字符 
		if(tree[index].left == tree[index].right)
		{
			//将该字符输出到
			printf("%c",tree[index].character);
			//重置索引节点 
			index = length-1;
		}
	}
}
//将编码后的文件输出
void PrintEncodeString(CharCode *code,unsigned char *str)
{
	for(int i = 0;str[i];i++)
	{
		//将字符的编码写输出
		printf("%s",code[str[i]].code);
	}
	printf("\n");
}
//输出源字符串 
void PrintSrcString(char *str)
{
	puts(str);
}
//各个字符 频率 编码输出到密码本中 
void PrintCharacterAndCountAndCode(CharCode *code,int length)
{
	printf("\t\t\t\t字  符\t\t频  率\t\t路  径\n"); 
	for(int i = 0;i<256;i++)
		//如果该字符在文件中存在 
		if(code[i].count)
			//格式化将该字符，频率，路径输出到文件中
			printf("\t\t\t\t%3c \t\t%d\t\t%s\n",i,code[i].count,code[i].code);
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
	int i,fmin = -1,smin = -1;
	//记录频率最小的两个节点的下标 
	for(i = 0;i<length;i++)
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
void InitHuffmanTree(Tree *tree,int length,int *chars)
{
	int i,k = 0;
	//用到了ascii的补充字符 
	for(i = 0;i<256;i++)
	{
		//如果字符串中出现了该字符，则将该字符，频率都初始化的huffman树中
		if(chars[i])
		{
			//记录当前字符 
			tree[k].character = i;
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
	sort(tree,tree+k,compare);
	for(;k<length;k++)
	{
		tree[k].count = 0;
		tree[k].left = 0;
		tree[k].right = 0;
		tree[k].parent = 0;
	}
}
void getEveryCharAndCount(unsigned char *str,int *chars,int *count)
{
	int i;
	int k = 0;
	/*用来记录读取的字符，因为要用的ascii的补充128个字符 ，
	将用来存储字符的变量都声明成无符号unsigned */
	unsigned int ch = 0;
	//输入字符串
	printf("\n\t\t\t\t\t\t请输入字符串:\n\n->");
	//按字符读取
	while((ch = (unsigned int)getchar())!='\n')
	{
		//记录不同的字符的个数 
		if(chars[(unsigned int)ch] == 0)
			(*count)++;
		//统计字符的频率 
		chars[(unsigned int)ch]++;
		str[k++] = (unsigned int)ch;
	}
}
int ChooseFunction()
{
	char ch;
	printf("\n\n\t\t\t\t\t请选择接下来要执行的功能:\n");
	printf("\n\n\t\t\t\t\t     1. 输入字符串\n");
	printf("\n\n\t\t\t\t\t     2. 输入路径\n"); 
	printf("\n\n\t\t\t\t\t     3. 查看各字符的编码\n"); 
	printf("\n\n\t\t\t\t\t     4. 查看原字符串的编码\n"); 
	printf("\n\n\t\t\t\t\t     0. 退出系统\n\n->"); 
	ch = getchar();
	return ch - 48;
}  
int main()
{
	CharCode code[256] = {0,0};
	//用来记录各字符出现的频率
	int chars[256] = {0};
	//路径
	char road[255]; 
	//输入的字符串
	unsigned char str[255];
	//编码后的字符串
	char encodeString[255]; 
	//总共输入的不同字符的个数
	int count = 0;
	//构建哈夫曼树的节点总个数
	int length;
	//哈夫曼树组的首地址
	Tree *tree = NULL;
	//接收命令
	int ch; 
	printf("\n\t\t\t\t\t      Huffman编码译码器\n");
	tree = getEveryCharAndCountAndMallocTree(str,chars,&count,&length);
	BuidTree(tree,length,chars,count);
	EncodeAndPrint(tree,count,code,str);	
	//输入指定的命令
	//printf("\n\n\t\t\t\t\t请输入命令(输入'#'结束):\n\n->");
	ch = ChooseFunction();
	//printf("\n\n\t\t\t\t\t请输入路径(输入'#'结束):\n\n->"); 
	while(ch)
	{
		getchar();
		//重新输入字符串 
		if(ch == 1)
		{
			tree = getEveryCharAndCountAndMallocTree(str,chars,&count,&length);
			BuidTree(tree,length,chars,count);
			EncodeAndPrint(tree,count,code,str);
		}
		//输入路径 
		else if(ch == 2)
		{
			printf("\n\n\t\t\t\t\t请输入路径(输入'#'结束):\n\n->"); 
			gets(road);
			while(road[0]!='#')
			{
				printf("\n\n\t\t\t\t\t\t解码后的结果:\n\n->"); 
				decodeAfterEncodeString(tree,road,length);
				printf("\n\n\t\t\t\t\t请输入路径(输入'#'结束):\n\n->"); 
				gets(road);
			}	
			system("cls");
		}
		//查看各字符的编码
		else if(ch == 3)
		{
			printf("\n\t\t\t\t对输入字符串构建huffman树后的统计结果:\n\n->"); 
			PrintCharacterAndCountAndCode(code,count);
		}
		//查看原字符串的编码 
		else if(ch == 4)
		{
			printf("\n\t\t\t\t\t对输入字符串编码后的结果:\n\n->"); 
			PrintEncodeString(code,str);
		}
		ch = ChooseFunction();
	} 
}

