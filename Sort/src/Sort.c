/*********************************************************************
*wangfeng
*2020.10.19-2020.12.4
*�ο����ϣ�https://blog.csdn.net/sx2448826571/article/details/80487531
**********************************************************************/
#include "Sort.h"
#include "malloc.h"

void swap_u8(UINT8 *dat1,UINT8 *dat2)
{
	UINT8 temp;
	temp = *dat1;
	*dat1 = *dat2;
	*dat2 = temp;
}
void swap_int(int *dat1,int *dat2)
{
	int temp;
	temp = *dat1;
	*dat1 = *dat2;
	*dat2 = temp;
}
/******************************
 *ð�����򷨣�ʱ�临�Ӷȣ�n^2
 *���룺mode 0:����1������
 *		dat  Ҫ���������
 *		len  ���ݵĳ���
 *���أ���
 *****************************/
void Sort_Bubbling(UINT8 mode,int *dat,UINT16 len)
{
	UINT16 i,j;
	for(i = 0;i<len-1;i++)
	{
		for(j = i;j<len;j++)
		{
			if(mode)
			{
				if(dat[i]<dat[j])//����
					swap_int(&dat[i],&dat[j]);
			}
			else
			{
				if(dat[i]>dat[j])
					swap_int(&dat[i],&dat[j]);
			}
		}
	}
}

/******************************
 *��������:ʱ�临�Ӷȣ�nlogn
 *���룺dat  Ҫ���������
 *		start ���ݿ�ʼ�±�
 *		end  ���ݽ����±�
 *���أ���
 *****************************/
void Sort_Quick(int *dat,UINT8 start,UINT8 end)
{
	UINT8 mid = dat[start];//ȡ��һ������Ϊ��׼��
	UINT8 low,high;
	if(start >= end)//start ��end ��ͷ�ˣ�����������˳��ݹ�
		return;

	low = start;//low��������ӻ�׼��ʼ�ұ�mid�������λ��
	high = end;//high������Ҳ�end�����ұ�midС������λ��

	/* ����ѭ����ֻҪlow��highû����ͷ��һֱ����,��low��high���˵����ͷ�� */
	while(low < high)
	{
		/* ��high��ʼ�����ҵ���һ����midС���ߵ���mid���������λ��,�����high������mid�����Ǿ�����high��*/
		/* ��������Ҫȷ���ҵ�֮ǰ�����low��high��ͷ�ˣ�Ҳ������ */
		while(dat[high] > mid && (low < high))
			high--;

		/* ��low��ʼ���ң��ҵ���һ����mid����������λ��,�����low������midС�����Ǿ�����low�� */
		/* ��������Ҫȷ���ҵ�֮ǰ�����low��high��ͷ�ˣ�Ҳ������ */
		while((dat[low]<=mid) && (low < high))
			low++;

		/* �ҵ�������Ǻ󣬽��� */
		swap_int(&dat[low],&dat[high]);
	}
	swap_int(&dat[start],&dat[low]);

	Sort_Quick(dat,start,low-1);//�ݹ����
	Sort_Quick(dat,low+1,end);
}

/******************************
 *ֱ�Ӳ������򷨣�ʱ�临�Ӷȣ�n^2
 *���룺dat  Ҫ���������
 *		len ���ݳ���
 *���أ���
 *****************************/
void Sort_Insert(int *dat,UINT8 len)
{
	int i,key,end;
	for(i = 1;i<len;i++)
	{
		key = dat[i];//����ÿ��Ҫ�Ƚϵ�ֵ
		end = i-1;
		while(end >= 0 && key<dat[end])//��ǰ�Ƚϣ�ֱ���ҵ����Լ�С�ģ�����
		{
			dat[end+1] = dat[end];//����ķ���Ϊ����ǰһ��ֵ��ֵ����һ��ֵ�����keyֵ��ֵ����ǰ����ɲ���
			end--;

		}
		dat[end+1] = key;
	}
}

/******************************
 *ϣ�����򷨣�ֱ�Ӳ������򷨵��Ż���:ʱ�临�Ӷȣ�n^2
 *���룺dat  Ҫ���������
 *		len ���ݳ���
 *���أ���
 *****************************/
void Sort_Shell(int *dat,UINT8 len)
{
	int gap = len/2;
	int key,end,i=0;
	for(gap;gap>0;gap/=2)
	{
		for(i = gap;i<len;i++)
		{
			key = dat[i];
			end = i-gap;
			while(end >=0 && key < dat[end])
			{
				dat[end+gap] = dat[end];
				end -= gap;
			}
			dat[end+gap] = key;
		}	
	}
}

/******************************
 *ֱ��ѡ������ʱ�临�Ӷȣ�n^2
 *���룺dat  Ҫ���������
 *		len ���ݳ���
 *���أ���
 *****************************/
void Sort_Select(int* dat,UINT8 len)
{
	int i;
	UINT8 minIndex,maxIndex;
	UINT8 left=0,right=len-1;//����������
	
	while(left < right)
	{
		minIndex = left;
		maxIndex = right;
		for(i = left;i<=right;i++)//�ҵ������Сֵ������
		{
			if(dat[minIndex]>dat[i])
				minIndex = i;
			if(dat[maxIndex]<dat[i])
				maxIndex = i;
		}
		swap_int(&dat[minIndex],&dat[left]);
		if(maxIndex == left)
			maxIndex = minIndex;
		swap_int(&dat[maxIndex],&dat[right]);

		left ++;
		right --;
	}	
}

/******************************
 *���µ����ѣ����ӽڵ���ڸ��ڵ㣬�����ӽڵ��븸�ڵ㽻�����˴��þ�̬��ʵ��
 *������ȫ������
 *���룺arr:��������ݣ�
 *		size:�����ѵĴ�С��
 *		parent:�ڵ�ĸ��ڵ�
 *�����arr���������е�����
 *���أ���
 *****************************/
static void HeapAdjust(int *arr,int size,int parent)
{
	int child = parent*2 + 1;//��̬��ȫ������������

	while(child < size)
	{
		if((child + 1 < size) && (arr[child + 1] > arr[child]))//�ҽڵ㳬���Ѵ�С���ҽڵ��ֵ������ڵ��ֵ,�ӽڵ㶨λΪ�ҽڵ�
			child += 1;
		if(arr[parent] < arr[child])
		{
			swap_int(&arr[parent],&arr[child]);
			parent = child;
			child = parent*2 + 1;
		}
		else
			return;
	}
}
/******************************
 *������ʱ�临�Ӷȣ�nlogn
 *���룺arr:��������ݣ�
 *		len:�������ݵ�������
 *�����arr���������е�����
 *���أ���
 *****************************/
void Sort_Heat(int *arr,int len)
{
	/* arr������Ƕѣ�����һ���Ǵ󶥶ѣ�������Ҫ�ȹ���ɴ󶥶� */
	/* ����󶥶���Ҫ�����һ����Ҷ�ӽ�㿪ʼ���������ң����µ��ϵ��� */
	int root = len/2 - 1;//���һ����Ҷ�ӽ��
	int end = len - 1;

	for(;root >= 0;root --)
		HeapAdjust(arr,len,root);
	
	/* ��������ʱ�����Ѿ��Ǵ󶥶ѣ������Զ������һ��Ԫ�أ����µ���Ϊ�󶥶� */
	while(end > 0)
	{
		swap_int(&arr[0],&arr[end]);//arr[0]Ϊ�Զ���arr[end]Ϊ���һ��Ԫ��
		HeapAdjust(arr,end--,0);//���µ���Ϊ�󶥶�
	}
}

/******************************
 *��·�鲢
 *���룺arr:��������ݣ�
 *		left:arr��Ҫ�鲢���������ݵ���������
 *		right:arr��Ҫ�鲢���������ݵ���������
 *		mid:arr��Ҫ�鲢���������ݵĵ�1�����ݵ��������
 *�����temp:�鲢�������
 *���أ���
 *****************************/
static void MergeData(int *arr,int left,int mid,int right,int *temp)
{
	int index1 = left;//��1�����ݵ��½Ǳ�
	int index2 = mid+1;//��2�����ݵ��½Ǳ�
	int i = 0;
	while(index1<=mid && index2<=right)
	{
		if(arr[index1] < arr[index2])
			temp[i++] = arr[index1++];
		else
			temp[i++] = arr[index2++];
	}
	/* ����ʣ�µ����� */
	while(index1 <= mid)
		temp[i++] = arr[index1++];
	while(index2 <= right)
		temp[i++] = arr[index2++];
}
/******************************
 *�鲢����ķ���
 *���룺arr:��������ݣ�
 *		left:arr��Ҫ�鲢���������ݵ���������
 *		right:arr��Ҫ�鲢���������ݵ���������
 *�����temp:�鲢�������
 *���أ���
 *****************************/
static _MergeSort(int *arr,int left,int right,int *temp)
{
	int mid;
	if((right - left) <= 0)//�˳��ݹ������
		return;
	mid = left+(right - left)/2;//ȡ�м�����������1�����ݵ����һ������
	_MergeSort(arr,left,mid,temp);
	_MergeSort(arr,mid+1,right,temp);
	MergeData(arr,left,mid,right,temp);
	memcpy(arr + left,temp,sizeof(arr[0])*(right - left + 1));
}
/******************************
 *�鲢���򣺽��������Ԫ�����з�Ϊ����������ȵ�������,��ÿ�������н�������,Ȼ�����Ǻϲ���һ������,�ϲ����������еĹ��̳�Ϊ��·�鲢.
 *ʱ�临�Ӷȣ�nlogn
 *���룺arr:��������ݣ�
 *		size:�������ݴ�С
 *�����arr:�����������
 *���أ���
 *****************************/
void Sort_Merge(int *arr,int size)
{
	int *temp = (int *)malloc(sizeof(arr[0])*size);
	if(NULL == temp)
	{
		printf("�����ڴ�ʧ��\r\n");
		return;
	}
	_MergeSort(arr,0,size-1,temp);
	free(temp);
	temp = NULL;
}
