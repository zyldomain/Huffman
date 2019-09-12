/** 
 *                                     ���ݽṹ�γ���� 
 *                            ����huffman�������ļ��ı�������� 
 */  
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<algorithm>
using namespace std;
//�ڵ�
typedef struct Tree
{
	unsigned char character;
	int count;
	int left;
	int right;
	int parent;
	char code;
}Tree;
//ÿ���ַ��ı���
typedef struct CharCode
{
	int count;
	char code[256];
}CharCode;
//ͳ�Ƹ��ַ����ֵ�Ƶ�ʺͲ�ͬ�ַ��ĸ���
void getEveryCharAndCount(char *str,int *chars,int *count);
//��ʼ������������ǰcount���ڵ㣨Ҷ�ӽڵ㣩���ַ���Ƶ��
void IninHuffmanTree(Tree *tree,int length,int *chars);
//�������
bool compare(Tree a,Tree b);
//������������
void createHuffmanTree(Tree *tree,int length);
//ѡ���ַ����д�����С�������� 
void selectFirstMinAndSecondMin(Tree *tree,int length,int *FirstMin,int *SecondMin);
//�����ַ�
void encodeEveryCharacterFromHuffmanTree(Tree *tree,int length,CharCode *code);
//�����ַ� Ƶ�� ����
void PrintCharacterAndCountAndCode(CharCode *code,int length);
//���ԭʼ�ַ���
void PrintSrcString(char *str);
//�����ַ��������
void PrintEncodeString(CharCode *code,char *str);
//�Ը���·�����н���
void decodeAfterEncodeString(Tree *tree,char *encodeString,int length);
//��ʾ�˵���
int ChooseFunction();
//ִ�й������������
void excuteHuffManEncode()
{
	
} 
int ChooseFunction()
{
	char ch;
	printf("��ѡ�������Ҫִ�еĹ���:\n");
	printf("1. �����ַ���\n");
	printf("2. ����·��\n"); 
	ch = getchar();
	return ch - 48;
}          
/*//����·������ 
void getStringAccordingToRoad(Tree *tree,char *road,int length);
void getStringAccordingToRoad(Tree *tree,char *road,int length)
{
	int child = length-1;
	for(int i = 0;road[i];i++)
	{
		if(road[i] == '0')
		{
			child = tree[i].left;
		}
		else
		{
			child = tree[i].right;
		}
		if(tree[child].left == tree[child].right)
		{
			printf("%c",tree[child].character);
			child = length-1;
		}
	}
	printf("\n");
}*/ 
//�Ը���·�����н���
void decodeAfterEncodeString(Tree *tree,char *encodeString,int length)
{
	//�õ����ĸ��ڵ� 
	int index = length-1;
	for(int i = 0;encodeString[i];i++)
	{
		//�����·��Ϊ0����������
		if(encodeString[i] == '0')
		{
			index = tree[index].left;
		}
		//����������
		else
		{
			index = tree[index].right;
		}
		//�ж��ǲ���Ҷ�ӽ�㣬��������ȡ���ַ� 
		if(tree[index].left == tree[index].right)
		{
			//�����ַ������
			printf("%c",tree[index].character);
			//���������ڵ� 
			index = length-1;
		}
	}
}
//���������ļ����
void PrintEncodeString(CharCode *code,unsigned char *str)
{
	for(int i = 0;str[i];i++)
	{
		//���ַ��ı���д���
		printf("%s",code[str[i]].code);
		//strcat(encodeString,code[str[i]].code);
	}
	printf("\n");
}
//���Դ�ַ��� 
void PrintSrcString(char *str)
{
	puts(str);
}
//�����ַ� Ƶ�� ������������뱾�� 
void PrintCharacterAndCountAndCode(CharCode *code,int length)
{
	printf("\t\t\t\t��  ��\t\tƵ  ��\t\t·  ��\n"); 
	for(int i = 0;i<256;i++)
		//������ַ����ļ��д��� 
		if(code[i].count)
			//��ʽ�������ַ���Ƶ�ʣ�·��������ļ���
			printf("\t\t\t\t%3c \t\t%d\t\t%s\n",i,code[i].count,code[i].code);
}
//�����ַ�
void encodeEveryCharacterFromHuffmanTree(Tree *tree,int length,CharCode *code)
{
	int i,k,child,j,t;
	unsigned char character;
	char encode[256];
	//�Ե������ҵ�������ڵ��·�����Ǹ��ַ��ı��� 
	for(i = 0;i<length;i++)
	{
		k = 0;
		child = i;
		//��ǰҶ�ӽ����ַ� 
		character = tree[i].character;
		//һ��һ���ҵ����ڵ㲢��¼·�� 
		while(tree[child].parent)
		{
			encode[k++] = tree[child].code;
			//�ҵ�child�ڵ�ĸ��ڵ� 
			child = tree[child].parent;
		}
		//����·��
		encode[k] = '\0';
		t = 0;
		//��Ϊ·���ǵ���ģ�Ҫ�����ȷ��·������Ҫ�����Ӻ���ǰ��һ�� 
		for(j = k-1;j>=0;j--)
		{
			code[character].code[t++] = encode[j];
		}
		//�����ַ���·������ 
		code[character].code[t] = '\0';
		//���ø��ַ���Ƶ�� 
		code[character].count = tree[i].count;
	}
}
//ѡ���ַ����д�����С�������� 
void selectFirstMinAndSecondMin(Tree *tree,int length,int *FirstMin,int *SecondMin)
{
	int i,fmin = -1,smin = -1;
	//��¼Ƶ����С�������ڵ���±� 
	for(i = 0;i<length;i++)
	{
		//����ýڵ㻹û�и��ڵ� 
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
	//���±����õ�������β��� 
	(*FirstMin) = fmin;
	(*SecondMin) = smin;
}
//������������
void createHuffmanTree(Tree *tree,int length)
{
	//��Сֵ�Ľڵ��±꣬����Сֵ�Ľڵ��±�
	int FirstMin,SecondMin;
	//��¼ÿ�����ɵĸ��ڵ���±�
	int k = length;
	int i;
	for(i = 0;i<length-1;i++)
	{
		//��û�и�ĸ�Ľڵ���������Ƶ����С�Ľڵ���±� 
		selectFirstMinAndSecondMin(tree,k,&FirstMin,&SecondMin);
		//�ýڵ���Ϊ���ڵ㣬���ҵ��������ڵ㽨����ϵ 
		tree[k].left = FirstMin;
		tree[k].right = SecondMin;
		//�ýڵ��Ƶ��Ϊ�������ӽڵ��Ƶ��֮�� 
		tree[k].count = tree[FirstMin].count + tree[SecondMin].count;
		//���������ӽڵ�ĸ��ڵ��޸�Ϊ��ǰ���
		tree[FirstMin].parent = k;
		tree[SecondMin].parent = k;
		//�������ӵ�·��Ϊ0 
		tree[FirstMin].code = '0';
		//�����Һ��ӵ�·��Ϊ1 
		tree[SecondMin].code = '1';
		//���Ӹ��ڵ�
		k++;
	}
}
//�Ƚϲ��ԣ���С���� 
bool compare(Tree a,Tree b)
{
	return a.count<b.count;
}
//��ʼ������������ǰcount���ڵ㣨Ҷ�ӽڵ㣩���ַ���Ƶ��
void InituffmanTree(Tree *tree,int length,int *chars)
{
	int i,k = 0;
	//�õ���ascii�Ĳ����ַ� 
	for(i = 0;i<256;i++)
	{
		//����ַ����г����˸��ַ����򽫸��ַ���Ƶ�ʶ���ʼ����huffman����
		if(chars[i])
		{
			//��¼��ǰ�ַ� 
			tree[k].character = i;
			//��¼��ǰ�ַ���Ƶ�� 
			tree[k].count = chars[i];
			//��ָ�򶼱�Ϊ�� 
			tree[k].left = 0;
			tree[k].right = 0;
			tree[k].parent = 0;
			//����Ҷ�ӽڵ����� 
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
	/*������¼��ȡ���ַ�����ΪҪ�õ�ascii�Ĳ���128���ַ� ��
	�������洢�ַ��ı������������޷���unsigned */
	unsigned int ch = 0;
	//�����ַ���
	printf("\n\t\t\t\t\t\t�������ַ���:\n->");
	//���ַ���ȡ
	while((ch = (unsigned int)getchar())!='\n')
	{
		//��¼��ͬ���ַ��ĸ��� 
		if(chars[(unsigned int)ch] == 0)
			(*count)++;
		//ͳ���ַ���Ƶ�� 
		chars[(unsigned int)ch]++;
		str[k++] = (unsigned int)ch;
	}
}
int main()
{
	CharCode code[256] = {0,0};
	//������¼���ַ����ֵ�Ƶ��
	int chars[256] = {0};
	//·��
	char road[255]; 
	//������ַ���
	unsigned char str[255];
	//�������ַ���
	char encodeString[255]; 
	//�ܹ�����Ĳ�ͬ�ַ��ĸ���
	int count = 0;
	//�������������Ľڵ��ܸ���
	int length;
	//������������׵�ַ
	Tree *tree = NULL;
	printf("\n\t\t\t\t\t      Huffman����������\n");
	getEveryCharAndCount(str,chars,&count);
	//����������ڵ�ĸ���
	length = 2*count-1;
	//����һ������Ϊlength����������������������
	tree = (Tree *)malloc(sizeof(Tree)*length);
	//��ʼ��Ҷ�ӽڵ�
	InituffmanTree(tree,length,chars);
	//������������
	createHuffmanTree(tree,count);
	//�Ը��ַ����б���
	encodeEveryCharacterFromHuffmanTree(tree,count,code);
	//���ԭʼ�ַ���
	//PrintSrcString(str);
	//��������ַ� Ƶ�� ����
	printf("\n\t\t\t\t�������ַ�������huffman�����ͳ�ƽ��:\n\n->"); 
	PrintCharacterAndCountAndCode(code,count);
	//�������ַ���
	printf("\n\t\t\t\t\t�������ַ��������Ľ��:\n\n->"); 
	PrintEncodeString(code,str);
	//�Ա������ַ������н��� 
	
	//����ָ����·��
	printf("\n\n\t\t\t\t\t������·��(����'#'����):\n\n->"); 
	gets(road);
	while(road[0]!='#')
	{
		printf("\n\n\t\t\t\t\t\t�����Ľ��:\n\n->"); 
		decodeAfterEncodeString(tree,road,length);
		printf("\n\n\t\t\t\t\t������·��(����'#'����):\n\n->"); 
		gets(road);
	}
}

