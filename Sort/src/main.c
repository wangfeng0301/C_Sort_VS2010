#include <stdio.h>
#include <string.h>
#include "Sort.h"

void display(int *dat,UINT8 len)
{
	UINT8 i;
	for(i = 0;i<len;i++)
		printf("%d ",dat[i]);
	printf("\r\n");
}

//int testdat[20] = {10,20,55,23,26,28,44,41,10,5,6,9,8,3,63,32,87,12,34,21};
//int decdat[20];

int main()
{
	int testdat[20] = {10,20,55,23,26,28,44,41,10,5,6,9,8,3,63,32,87,12,34,21};
	int decdat[20];

	printf("This is a sort test.\r\n");
	printf("ԭʼ���У�");
	display(testdat,sizeof(decdat)/sizeof(testdat[0]));
	
	printf("ð������(����)    ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Bubbling(0,decdat,sizeof(decdat)/4);
	display(decdat,sizeof(testdat)/4);

	printf("ð������(����)    ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Bubbling(1,decdat,sizeof(decdat)/4);
	display(decdat,sizeof(testdat)/4);

	printf("��������(����)    ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Quick(decdat,0,sizeof(decdat)/4-1);
	display(decdat,sizeof(testdat)/4);

	printf("ֱ�Ӳ�������(����)��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Insert(decdat,sizeof(decdat)/4);
	display(decdat,sizeof(testdat)/4);

	printf("ϣ������(����)    ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Shell(decdat,sizeof(decdat)/4);
	display(decdat,sizeof(testdat)/4);

	printf("ֱ��ѡ������(����)��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Select(decdat,sizeof(decdat)/4);
	display(decdat,sizeof(testdat)/4);

	printf("������(����)        ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Heat(decdat,sizeof(decdat)/4);
	display(decdat,sizeof(testdat)/4);

	printf("�鲢����(����)      ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Merge(decdat,sizeof(decdat)/4);
	display(decdat,sizeof(testdat)/4);

	printf("�鲢����(�ǵݹ�)    ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Merge_Nor(decdat,sizeof(decdat)/4);
	display(decdat,sizeof(testdat)/4);

	printf("Ͱʽ����            ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Bucket(decdat,sizeof(decdat)/4,90);
	display(decdat,sizeof(testdat)/4);

	printf("��������_˳��       ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Radix_InTurn(decdat,sizeof(decdat)/4,2,10);
	display(decdat,sizeof(testdat)/4);

	printf("��������_��̬��     ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Radix_Link(decdat,sizeof(decdat)/4,2,10);
	display(decdat,sizeof(testdat)/4);

	printf("��������            ��");
	memcpy(decdat,testdat,sizeof(testdat));
	Sort_Index_Insert(decdat,sizeof(decdat)/sizeof(decdat[0]));
	display(decdat,sizeof(testdat)/sizeof(decdat[0]));

	system("pause");
	return 0;
}
