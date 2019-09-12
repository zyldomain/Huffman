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
//�ع�huffmanTree
typedef struct HuffmanTree
{
	unsigned char character;
	char code;
	struct HuffmanTree *left;
	struct HuffmanTree *right;
 }HuffmanTree;
//ÿ���ַ��ı���
typedef struct CharCode
{
	int count;
	char code[256];
}CharCode;
//ͳ�Ƹ��ַ����ֵ�Ƶ�ʺͲ�ͬ�ַ��ĸ���
void getEveryCharAndCount(char *sourceFileName,int *chars,int *count);
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
//�����ַ� Ƶ�� ������������뱾�� 
void PrintCharacterAndCode(CharCode *code,int length,char *passwordFileName);
//���������ļ�������ļ��� 
void PrintEncodeString(CharCode *code,char *sourceFileName,char *targetFileName); 
//�Ա������ַ������н���
void decodeAfterEncodeString(Tree *tree,char *encodeString,int length);
//�����뱾�е����ݷŵ��洢�����������
void readCodeFromPasswordToCode(CharCode *code,int *count,char *passwordFileName); 
//����code�������¹�����������
void reBuildHuffmanTree(HuffmanTree **tree,CharCode *code);
//���������ļ�����
void decodeAfterEncodeFile(HuffmanTree *tree,char *sourceFileName,char *targetFileName);
//������ʾ��Ϣ 
void PrintInfoAfterEncodeFile(char *targetFileName,char *password);
//��������ʾ��Ϣ 
void PrintInfoAfterDecodeFile(char *targetFileName); 
void PrintInfoAfterDecodeFile(char *targetFileName)
{
	printf("\n\n\t\t\t\t\t\t�ļ�������ɣ�����\n"); 
	printf("\n\t\t\t\t\t  �����˽����ļ�:%s\n",targetFileName);
	printf("\n\t\t\t�����Ҫ����ͨ�ļ����б��룬���������д˳����������ģ��:\n");
	printf("\n\t\t\t\t     ����������  ��ͨ�ļ�  �����ļ�\n\n\n");
}
void PrintInfoAfterEncodeFile(char *targetFileName,char *password)
{
	printf("\n\n\t\t\t\t\t\t�ļ�������ɣ�����\n"); 
	printf("\n\t\t\t\t\t  �����˱����ļ�:%s\n",targetFileName);
	printf("\n\t\t\t\t\t  �����������ļ�:%s\n",password);
	printf("\n\t\t\t�����Ҫ�Ա����ļ����н��룬���������д˳����������ģ��:\n");
	printf("\n\t\t\t\t����������  �����ļ�  �����ļ� �����ļ�\n\n\n");
}
//���������ļ�����
void decodeAfterEncodeFile(HuffmanTree *tree,char *sourceFileName,char *targetFileName)
{
	//�򿪱�ѹ�����ļ� 
 	FILE *fIn = fopen(sourceFileName,"r");
 	//�򿪽�ѹ����ļ���λ�� 
 	FILE *fOut = fopen(targetFileName,"w");
 	char code;
 	//�õ����ĸ��ڵ� 
 	HuffmanTree *p = tree;
 	//��·��ÿ���ַ���ȡ 
 	while((code = fgetc(fIn))!=EOF)
 	{
 		//�����·��Ϊ0���������� 
 		if(code == '0')
 		{
 			p = p->left;	
		}
		//���������� 
		else
		{
			p = p->right;
		}
		//�ж��ǲ���Ҷ�ӽ�㣬��������ȡ���ַ� 
		if(p->left == NULL&&p->right == NULL)
		{
			//�����ַ��������ѹ�ļ��� 
			fputc(p->character,fOut);
			//���������ڵ� 
			p = tree;
		}
	}
 }
//����code�������¹�����������
void reBuildHuffmanTree(HuffmanTree **tree,CharCode *code)
{
	//�������ڵ�
	(*tree) = (HuffmanTree *)malloc(sizeof(HuffmanTree));
	//�ع�huffman����ָ�� 
	HuffmanTree *p = (*tree);
	p->left = NULL;
	p->right = NULL;
	for(int i = 0;i<256;i++)
	{
		//������ַ����� 
		if(code[i].count!=0)
		{
			//��������ָ�� 
			p = (*tree); 
			//�������ַ���·���ع�huffman�� 
			//i��¼�Ÿ��ַ� 
			for(int j = 0;code[i].code[j];j++)
			{
				//�����ǰ·��Ϊ0���������� 
				if(code[i].code[j] == '0')
				{
					//�����Ҫ����Ľڵ�Ϊ�գ������ýڵ� 
					if(p->left == NULL)
					{
						//�����ýڵ� 
						p->left = (HuffmanTree *)malloc(sizeof(HuffmanTree));
						//����ýڵ� 
						p = p->left;
						//��ʼ�����Һ��� 
						p->left = NULL;
						p->right = NULL;
					}
					//�����Ҫ����Ľڵ㲻Ϊ�գ��򵽴�ýڵ� 
					else
					{
						p = p->left;
					}
				}
				//�����ǰ·��Ϊ1����������
				else
				{
					//�����Ҫ����Ľڵ�Ϊ�գ������ýڵ� 
					if(p->right == NULL)
					{
						//�����ýڵ� 
						p->right = (HuffmanTree *)malloc(sizeof(HuffmanTree));
						//����ýڵ� 
						p = p->right;
						//��ʼ�����Һ��� 
						p->left = NULL;
						p->right = NULL;
					}
					//�����Ҫ����Ľڵ㲻Ϊ�գ��򵽴�ýڵ� 
					else
					{
						p = p->right;
					}
				//	printf("d");
				}
			}
			//�����˸��ַ���λ�ã�����λ�õ��ַ���ֵ 
			p->character = i;
		}
	}
} 
//�����뱾�е����ݷŵ��洢�����������
void readCodeFromPasswordToCode(CharCode *code,int *count,char *passwordFileName)
{
	//�����뱾�ļ� 
	FILE *fp = fopen(passwordFileName,"r");
	unsigned char character;
	unsigned int num;
	char charCode[256];
	//������뱾�����ڣ�������ֹ 
	if(fp == NULL)
		return;
	//��ʽ���������� 
	while(fscanf(fp,"%c %d %s",&character,&num,charCode)!=EOF)
	{
		//��¼�����˶��ٲ�ͬ���ַ� 
		(*count)++;
		//���ø��ַ���Ƶ�� 
		code[character].count = num;
		//���ø��ַ��ı��� 
		strcat(code[character].code,charCode);
		//�����ļ��Ŀո� 
		fgetc(fp);
	}
}
//���������ļ�������ļ��� 
void PrintEncodeString(CharCode *code,char *sourceFileName,char *targetFileName)
{
	//��Դ�ļ� 
	FILE *fIn = fopen(sourceFileName,"r");
	//��Ҫѹ�������ļ� 
	FILE *fOut = fopen(targetFileName,"w");
	unsigned int ch;
	//���Դ�ļ������ڳ�����ֹ 
	if(fIn == NULL)
		return;
	ch=(unsigned int)fgetc(fIn);
	while(!feof(fIn))
	{
		//���ַ��ı���д��Ҫѹ�����ļ��� 
		fputs(code[(unsigned int)ch].code,fOut);
		ch=(unsigned int)fgetc(fIn);
	}
	//�رմ򿪵��ļ� 
	fclose(fIn);
	fclose(fOut);
}
//�����ַ� Ƶ�� ������������뱾�� 
void PrintCharacterAndCode(CharCode *code,int length,char *passwordFileName)
{
	//�����뱾�ļ� 
	FILE *fp = fopen(passwordFileName,"w");
	for(int i = 0;i<256;i++)
		//������ַ����ļ��д��� 
		if(code[i].count)
			//��ʽ�������ַ���Ƶ�ʣ�·��������ļ��� 
			fprintf(fp,"%c %d %s ",i,code[i].count,code[i].code);
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
		//printf("%d",character);
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
	//��¼Ƶ����С�������ڵ���±� 
	int fmin = -1,smin = -1;
	for(int i = 0;i<length;i++)
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
		//����ļ��г����˸��ַ����򽫸��ַ���Ƶ�ʶ���ʼ����huffman���� 
		if(chars[i])
		{
			//��¼��ǰ�ַ� 
			tree[k].character = i;
		//	printf("%c\n",tree[k].character);
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
//ͳ�Ƹ��ַ����ֵ�Ƶ�ʺͲ�ͬ�ַ��ĸ���
void getEveryCharAndCount(char *sourceFileName,int *chars,int *count)
{
	int i;
	/*������¼��ȡ���ַ�����ΪҪ�õ�ascii�Ĳ���128���ַ� ��
	�������洢�ַ��ı������������޷���unsigned */
	unsigned int ch = 0;
	//��Ҫѹ�����ļ� 
	FILE *fp = fopen(sourceFileName,"r");
	//����ļ������ڣ�������� 
	if(fp == NULL)
	{
		return;
	}
	//���ַ���ȡ�ļ� 
	while((ch=(unsigned int)fgetc(fp))!=EOF)
	{	
		//��¼��ͬ���ַ��ĸ��� 
		if(chars[(unsigned int)ch] == 0)
			(*count)++;
		//ͳ���ַ���Ƶ�� 
		chars[(unsigned int)ch]++;
		//printf("%d\n",chars[(unsigned int)ch]);
		//ch=(unsigned int)fgetc(fp);
	}
	//�ر��ļ� 
	fclose(fp);
}
int main(int fileNum,char **fileName)
{
	CharCode code[256] = {0,0};
	//������¼���ַ����ֵ�Ƶ��
	int chars[256] = {0};
	//�ܹ�����Ĳ�ͬ�ַ��ĸ���
	int count = 0;
	//�������������Ľڵ��ܸ���
	int length;
	//������������׵�ַ
	Tree *tree = NULL;
	//�ع���������
	HuffmanTree *huffmanTree = NULL; 
	char targetFileName[200] = "\0";
	//�������뱾
	char *password = "password.json"; 
	//���ļ�����ѹ�� 
	if(fileNum == 3)
	{
		//Դ�ļ�   ѹ���ļ� 
		strcpy(targetFileName,fileName[2]);
		strcat(targetFileName,".txt");
		getEveryCharAndCount(fileName[1],chars,&count);
		//����������ڵ�ĸ���
		length = 2*count-1;
		//����һ������Ϊlength����������������������
		tree = (Tree *)malloc(sizeof(Tree)*length);
	//	printf("%c",-70);
		//��ʼ��Ҷ�ӽڵ�
		InituffmanTree(tree,length,chars);
		//������������
		createHuffmanTree(tree,count);
		printf("%c",tree[2].character);
		//�Ը��ַ����б���
		encodeEveryCharacterFromHuffmanTree(tree,count,code);
		//��������ַ� ���뵽���뱾 
		PrintCharacterAndCode(code,count,password);
		//�������ַ���
		PrintEncodeString(code,fileName[1],targetFileName);
		//��ʾ��Ϣ
		PrintInfoAfterEncodeFile(targetFileName,password);
	}
	//���ļ����н�ѹ 
	else if(fileNum == 4)
	{
		//ѹ���ļ� ���뱾 ��ѹ�ļ� 
		strcpy(targetFileName,fileName[3]);
		strcat(targetFileName,".txt");
		//��ȡ���뱾 password ��code�� 
		readCodeFromPasswordToCode(code,&count,password);
		//����code���¹���HuffmanTree 
		reBuildHuffmanTree(&huffmanTree,code);
		//���������ļ�����
		decodeAfterEncodeFile(huffmanTree,fileName[1],targetFileName);
		//��������ʾ��Ϣ 
		PrintInfoAfterDecodeFile(targetFileName); 
	}
}
