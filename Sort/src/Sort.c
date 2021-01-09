/*********************************************************************
*wangfeng
*2020.10.19-2021.1.9
*�ο����ϣ�https://blog.csdn.net/sx2448826571/article/details/80487531
**********************************************************************/
#include "Sort.h"
#include "malloc.h"
#include "string.h"

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
 *ð�����򷨣�ʱ�临�Ӷȣ�n^2,�ȶ�
 *���룺mode 0:����1������
 *		dat  Ҫ���������
 *		len  ���ݵĳ���
 *���أ���
 *****************************/
void Sort_Bubbling(UINT8 mode,int *dat,int len)
{
	UINT16 i,j;
	for(i = 0;i<len-1;i++)
	{
		for(j = 0;j<len-1-i;j++)
		{
			if(mode)
			{
				if(dat[j]<dat[j+1])//����ע������һ����С�ڣ�������С�ڵ��ڣ����������ȶ�
					swap_int(&dat[j],&dat[j+1]);
			}
			else
			{
				if(dat[j]>dat[j+1])//����ע������һ���Ǵ��ڣ������Ǵ��ڵ��ڣ����������ȶ�
					swap_int(&dat[j],&dat[j+1]);
			}
		}
	}
}

/******************************
 *��������:ʱ�临�Ӷȣ�nlogn�����ȶ�
 *���룺dat  Ҫ���������
 *		start ���ݿ�ʼ�±�
 *		end  ���ݽ����±�
 *���أ���
 *****************************/
void Sort_Quick(int *dat,int start,int end)
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
 *�ȶ��ԣ��ȶ�
 *˼�룺1.ѡ��1��Ҫ�Ƚϵ�ֵ��
 *		2.�Ը�ֵΪ���ң���������Ƚϣ�������ֵ����ֵ�����ƣ��ճ�λ��
 *		3.ֱ���ҵ��ȸ�ֵС���������ҵ����󣬽���
 *		4.ѡ��һ��Ҫ�Ƚϵ�ֵ���ظ�2-3����ֱ���������н���
 *���룺dat  Ҫ���������
 *		len ���ݳ���
 *���أ���
 *****************************/
void Sort_Insert(int *dat,int len)
{
	int i,key,end;
	for(i = 1;i<len;i++)
	{
		key = dat[i];//����ÿ��Ҫ�Ƚϵ�ֵ
		end = i-1;
		while(end >= 0 && key<dat[end])//��ǰ�Ƚϣ�ֱ���ҵ����Լ�С�ģ����롣һ����key<dat[end]������С�ڵ��ڣ������ȶ���
		{
			dat[end+1] = dat[end];//����ķ���Ϊ����ǰһ��ֵ��ֵ����һ��ֵ�����keyֵ��ֵ����ǰ����ɲ���
			end--;

		}
		dat[end+1] = key;
	}
}

/******************************
 *ϣ�����򷨣�ֱ�Ӳ������򷨵��Ż���:ʱ�临�Ӷȣ�n^2
 *�ȶ��ԣ����ȶ�
 *˼�룺1.����
 *		2.�Է�����в�������
 *		3.��С�����࣬��С���и���
 *���룺dat  Ҫ���������
 *		len ���ݳ���
 *���أ���
 *****************************/
void Sort_Shell(int *dat,int len)
{
	int gap = len/2;
	int key,end,i=0;
	for(gap;gap>0;gap/=2)//����Ҳ����ȡ����ֵ
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
 *˼�룺1.�ҳ���iС��ֵ���ŵ���i��λ��
 *�ȶ��ԣ����ȶ�
 *���룺dat  Ҫ���������
 *		len ���ݳ���
 *���أ���
 *****************************/
void Sort_Select(int* dat,int len)
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
 *˼�룺1.���������ݽ�������
 *		2.ȡ���Ѷ����ֵ��ĩ�˽���
 *		3.����Ϊ���ѣ��ظ�2-3
 *�ȶ��ԣ����ȶ�
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
	
	/* ��������ʱ�����Ѿ��Ǵ󶥶ѣ������Ѷ������һ��Ԫ�أ����µ���Ϊ�󶥶� */
	while(end > 0)
	{
		swap_int(&arr[0],&arr[end]);//arr[0]Ϊ�Ѷ���arr[end]Ϊ���һ��Ԫ��
		HeapAdjust(arr,end--,0);//���µ���Ϊ�󶥶�
	}
}

/*****************************************************************************************************************/
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
		if(arr[index1] <= arr[index2])//Ϊ��֤�ȶ��ԣ����ʱ����ѡ��ߵ�
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
static void _MergeSort(int *arr,int left,int right,int *temp)
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
 *�鲢���򣺽��������Ԫ�����з�Ϊ����������ȵ�������,��ÿ�������н�������,
 *			Ȼ�����Ǻϲ���һ������,�ϲ����������еĹ��̳�Ϊ��·�鲢.
 *ʱ�临�Ӷȣ�nlogn
 *�ȶ��ԣ��ȶ�
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
/******************************
 *�鲢���򣺷ǵݹ鷽ʽ
 *ʱ�临�Ӷȣ�nlogn
 *�ȶ��ԣ��ȶ�
 *���룺arr:��������ݣ�
 *		size:�������ݴ�С
 *�����arr:�����������
 *���أ���
 *****************************/
void Sort_Merge_Nor(int *arr,int size)
{
	int gap,i;
	int left,right,mid;
	int *temp = (int *)malloc(sizeof(arr[0])*size);
	if(NULL == temp)
	{
		printf("�����ڴ�ʧ��\r\n");
		return;
	}
	gap = 1;
	while(gap < size)
	{
		for(i = 0;i<size;i += 2*gap)
		{
			left = i;
			mid = left + gap -1;
			right = mid + gap;
			if(mid >= size)//ȷ���������ݶ��ܷ���
				mid = size - 1;
			if(right >= size)//ȷ���������ݶ��ܷ���
				right = size-1;
			MergeData(arr,left,mid,right,temp+i);
		}
		memcpy((UINT8*)arr,(UINT8*)temp,sizeof(arr[0])*size);
		gap *= 2;
	}
	free(temp);
	temp = NULL;
}

/*****************************************************************************************************************/
/******************************
 *Ͱʽ����:��Ҫ����ֱ�����������е����ֵ
 *ʱ�临�Ӷȣ�m+n
 *�ȶ��ԣ��ȶ�
 *���룺arr:��������ݣ�
 *		size:�������ݴ�С
 *		max:�����������е����ֵ
 *�����arr:�����������
 *���أ���
 *****************************/
void Sort_Bucket(int *arr,int size,int max)
{
	int *temp,*count;
	int i;

	temp = (int *)malloc(sizeof(arr[0])*size);
	if(temp == NULL)
	{
		printf("�����ڴ�ʧ��\r\n");
		return;
	}
	count = (int *)malloc(sizeof(int)*max);
	if(count == NULL)
	{
		free(temp);
		temp = NULL;
		printf("�����ڴ�ʧ��\r\n");
		return;
	}

	for(i = 0;i<size;i++)//���������鸳ֵ����ʱ����
		temp[i] = arr[i];
	for(i = 0;i<max;i++)//����������
		count[i] = 0;
	for(i = 0;i<size;i++)//ͳ��ÿ�����ֳ��ֵĴ���
		count[temp[i]] ++;
	for(i = 1;i<max;i++)//count[i]��¼��i+1����ʼλ��
		count[i] = count[i - 1] + count[i];
	for(i = size - 1;i >= 0;i--)//��β����ʼ˳���������֤������ȶ���
		arr[--count[temp[i]]] = temp[i];

	free(temp);
	free(count);
}

/******************************
 *��������-˳��洢:Ͱʽ�������չ
 *ʱ�临�Ӷȣ�d*(n+r)
 *�ȶ��ԣ��ȶ�
 *���룺arr:��������ݣ�
 *		n:�������ݵĸ���
 *		d:����������������ռ�����������λ������d=2��3λ������d=3
 *		r:��������10������������ȡ10
 *�����arr:�����������
 *���أ���
 *ע����������ǰ���������������Ԫ�ء���3λʮ����������������0-9��
 *****************************/
void Sort_Radix_InTurn(int *arr,int n,int d,int r)
{
	int *temp,*count;
	int i,j,k;
	int Radix = 1;//ģ

	temp = (int *)malloc(sizeof(arr[0])*n);//����������ʱ����
	if(temp == NULL)
	{
		printf("�����ڴ�ʧ��\r\n");
		return;
	}
	count = (int *)malloc(sizeof(int)*r);//Ͱ������������count[i]�洢��i��Ͱ�е����ݸ���
	if(count == NULL)
	{
		free(temp);
		temp = NULL;
		printf("�����ڴ�ʧ��\r\n");
		return;
	}

	for(i = 1;i <= d;i++)//ʹ��d��Ͱʽ����
	{
		for(j = 0;j < r;j++)//����������
			count[j] = 0;
		for(j = 0;j<n;j++)//ͳ��ÿ����������ֵĴ���
		{
			k = (arr[j]/Radix)%r;//ȡarr[j]�ĵ�iλ�����룬��3λ�����Ǹ�λʮλ��λ
			count[k] ++;
		}
		for(j = 1;j < r;j++)//�����r��Ͱ
			count[j] = count[j - 1] + count[j];//count[j]��¼��j+1����ʼλ��
		for(j = n - 1;j >= 0;j--)//��β����ʼ˳���ռ�����֤������ȶ���
		{
			k = (arr[j]/Radix)%r;
			count[k]--;//ʹ���˵�k��Ͱ��һ��λ�ã�Ͱʣ�����ļ�������1
			temp[count[k]] = arr[j];
		}
		for(j = 0;j < n;j++)//���������鸴�Ƶ�arr�У��Ա���һ������
			arr[j] = temp[j];
		Radix *= r;//�޸�ģRadix			
	}
	free(temp);
	free(count);
}

/******************************
 *��������-��̬��:Ͱʽ�������չ
 *ʱ�临�Ӷȣ�d*(n+r)
 *�ȶ��ԣ��ȶ�
 *���룺arr:��������ݣ�
 *		n:�������ݵĸ���
 *		d:����������������ռ�����������λ������d=2��3λ������d=3
 *		r:��������10������������ȡ10
 *�����arr:�����������
 *���أ���
 *ע����������ǰ���������������Ԫ�ء���3λʮ����������������0-9��
 *****************************/
typedef struct{
	int key;//������ֵ
	int next;//��һ���ڵ��������е��±�
}Node_t;
typedef struct{
	int head;
	int tail;
}StatiQueue_t;
static void distribute(Node_t *arr,int first,int i,int r,StatiQueue_t *queue);
static void collect(Node_t *arr,int *first,int r,StatiQueue_t *queue);
static void addr_sort(Node_t *arr,int n,int first,int *temp);
void Sort_Radix_Link(int *arr,int n,int d,int r)
{
	int i;
	int first = 0;//firstָ��̬���еĵ�һ�����ݣ���Ĭ���±�=0
	Node_t *temp;
	StatiQueue_t *queue;

	temp = (Node_t *)malloc(sizeof(Node_t)*n);//����������ʱ����
	if(temp == NULL)
	{
		printf("�����ڴ�ʧ��\r\n");
		return;
	}
	
	queue = (StatiQueue_t *)malloc(sizeof(StatiQueue_t)*r);//���r��Ͱ�ľ�̬����
	if(queue == NULL)
	{
		free(temp);
		temp = NULL;
		printf("�����ڴ�ʧ��\r\n");
		return;
	}
	/* ���ݸ��Ƶ���ʱ�����У�����ʹ�ö������� */
	/* ���������������ݱ������Node_t��ʽ�ģ�������ʱ���� */
	for(i = 0;i < n;i++)
		temp[i].key = arr[i];
	/* ��ʼ���������������ݵľ�ָ̬������Ϊ������ */
	for(i = 0;i < n-1;i++)
		temp[i].next = i+1;
	temp[n-1].next = -1;//��βnextΪ��

	/* �Ե�i����������з�����ռ�����d�� */
	for(i = 0;i < d;i++)
	{
		distribute(temp, first, i, r, queue);
		collect(temp, &first, r, queue);
	}
	addr_sort(temp, n, first, arr);
	free(temp);
	free(queue);
}
/******************************
 *�������
 *���룺arr:��������ݣ�
 *		first:��̬���е�һ�����ݵ��±�
 *		i:��i��������
 *		r:��������10������������ȡ10
 *		queue:���У���ΪͰ�ļ�����
 *�����arr:�����������
 *���أ���
 *ע����������ǰ���������������Ԫ�ء���3λʮ����������������0-9��
 *****************************/
static void distribute(Node_t *arr,int first,int i,int r,StatiQueue_t *queue)
{
	int j,k,a;
	int curr = first;//��ǰҪ�������ݵ��±�
	/* ��ʼ��r������ */
	for(j = 0;j < r;j++)
		queue[j].head = -1;

	/* ��������̬�����з��䣬������Ѱ�� */
	while(curr != -1)
	{
		k = arr[curr].key;//ȡ����
		for(a = 0;a < i;a++)//ȡ��iλ������k
			k = k/r;
		k = k%r;

		/* ��arr[curr]���䵽��k��Ͱ�� */
		if(queue[k].head == -1)//��ͰΪ�գ�arr[curr]����Ͱ�е�һ������
			queue[k].head = curr;
		else//����ӵ�Ͱ��β��
			arr[queue[k].tail].next = curr;
		queue[k].tail = curr;//��ǰ���������ݵ��±���ΪͰ��β��
		curr = arr[curr].next;//��ָ̬���ƶ���ָ����һ������������ݣ���������
	}
}
/******************************
 *�ռ�����
 *���룺arr:���������
 *		r:��������10������������ȡ10
 *		queue:���У���ΪͰ�ļ�����
 *�����arr:�����������
 *		first:��̬���е�һ�����ݵ��±꣬������Ϊ����ֵ����distribute����
 *���أ���
 *ע����������ǰ���������������Ԫ�ء���3λʮ����������������0-9��
 *****************************/
static void collect(Node_t *arr,int *first,int r,StatiQueue_t *queue)
{
	int k = 0,last;
	/* �ҵ���һ���ǿն��� */
	while(queue[k].head == -1)
		k++;

	*first = queue[k].head;//��¼���������еĵ�һ���±�
	last = queue[k].tail;//��¼��ǰ�����д������������һ���±�

	/* ÿ��Ͱ�����ռ� */
	/* ��������󣬴�����������Ѿ�����������ֳ�һ��һ���ĵ����� */
	/* �����ռ�ֻ��ͨ�����н������������������� */
	while(k < r-1)
	{
		k++;
		while(k < r-1 && queue[k].head == -1)
			k++;
		if(queue[k].head != -1)
		{
			arr[last].next = queue[k].head;//��β����
			last = queue[k].tail;//��¼���һ���±�
		}
	}
	arr[last].next = -1;//�ռ���ϣ��ź������ݵ����һ��ָ���
}
/******************************
 *�����������
 *���룺arr:���������
 *		n:���������ݵ�����
 *		first:��̬���е�һ�����ݵ��±�
 *�����temp:�����������
 *���أ���
 *****************************/
static void addr_sort(Node_t *arr,int n,int first,int *temp)
{
	int i,j;
	j = first;
	for(i = 0;i < n;i++)
	{
		temp[i] = arr[j].key;
		j = arr[j].next;
	}
}

/******************************
 *��������:�򵥲������������IndexArr[i]��ʾarr��i��λ��Ӧ�÷�arr[IndexArr[i]]
 *ʱ�临�Ӷȣ�
 *�ȶ��ԣ��ȶ�
 *���룺arr:�����������
 *		size:���������ݵĸ���
 *�����arr:�����������
 *���أ���
 *****************************/
void Sort_Index_Insert(int *arr, int size)
{
	int i,j,k;
	int *IndexArr;
	int temp;//��ʱ�洢�ռ�

	IndexArr = (int *)malloc(sizeof(arr[0])*size);
	if(NULL == IndexArr)
	{
		printf("�����ڴ�ʧ��\r\n");
		return;
	}
	/* ��ʼ�������±� */
	for(i = 0;i < size;i++)
		IndexArr[i] = i;

	/* �򵥲�������ĵ�ַ������� */
	for(i = 0;i < size;i++)
	{
		for(j = i;j > 0;j--)
		{
			/* ���������е��������������� */
			if(arr[IndexArr[j]] < arr[IndexArr[j-1]])
				swap_int(&IndexArr[j],&IndexArr[j-1]);
			else
				break;
		}
	}
	
	/* ���� */
	for(i = 0;i < size;i++)
	{
		temp = arr[i];
		j = i;
		/* ���ѭ�����������±���i����˳�����е��� */
		/* IndexArr[i]��ʾarr��i��λ��Ӧ�÷�arr[IndexArr[i]] */
		while(IndexArr[j] != i)
		{
			k = IndexArr[j];//k������jָ����±�
			arr[j] = arr[k];//��k�±��е�ֵ���Ƶ�jλ����j��Ԫ����ȷ��λ
			IndexArr[j] = j;//�Ѿ���ȷ��λ����j��������
			j = k;
		}
		arr[j] = temp;
		IndexArr[j] = j;//�Ѿ���ȷ��λ����j��������
	}
}