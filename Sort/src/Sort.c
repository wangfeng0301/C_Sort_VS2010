/*********************************************************************
*wangfeng
*2020.10.19-2020.12.4
*参考资料：https://blog.csdn.net/sx2448826571/article/details/80487531
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
 *冒泡排序法：时间复杂度：n^2
 *输入：mode 0:升序；1：降序
 *		dat  要排序的数据
 *		len  数据的长度
 *返回：无
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
				if(dat[i]<dat[j])//降序
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
 *快速排序法:时间复杂度：nlogn
 *输入：dat  要排序的数据
 *		start 数据开始下标
 *		end  数据结束下标
 *返回：无
 *****************************/
void Sort_Quick(int *dat,UINT8 start,UINT8 end)
{
	UINT8 mid = dat[start];//取第一个数作为基准数
	UINT8 low,high;
	if(start >= end)//start 和end 碰头了，排序结束，退出递归
		return;

	low = start;//low来标记左侧从基准数始找比mid大的数的位置
	high = end;//high来标记右侧end向左找比mid小的数的位置

	/* 进行循环，只要low和high没有碰头就一直进行,当low和high相等说明碰头了 */
	while(low < high)
	{
		/* 从high开始向左，找到第一个比mid小或者等于mid的数，标记位置,（如果high的数比mid大，我们就左移high）*/
		/* 并且我们要确定找到之前，如果low和high碰头了，也不找了 */
		while(dat[high] > mid && (low < high))
			high--;

		/* 从low开始向右，找到第一个比mid大的数，标记位置,（如果low的数比mid小，我们就右移low） */
		/* 并且我们要确定找到之前，如果low和high碰头了，也不找了 */
		while((dat[low]<=mid) && (low < high))
			low++;

		/* 找到两个标记后，交换 */
		swap_int(&dat[low],&dat[high]);
	}
	swap_int(&dat[start],&dat[low]);

	Sort_Quick(dat,start,low-1);//递归调用
	Sort_Quick(dat,low+1,end);
}

/******************************
 *直接插入排序法：时间复杂度：n^2
 *输入：dat  要排序的数据
 *		len 数据长度
 *返回：无
 *****************************/
void Sort_Insert(int *dat,UINT8 len)
{
	int i,key,end;
	for(i = 1;i<len;i++)
	{
		key = dat[i];//保存每次要比较的值
		end = i-1;
		while(end >= 0 && key<dat[end])//向前比较，直到找到比自己小的，插入
		{
			dat[end+1] = dat[end];//插入的方法为：将前一个值赋值到后一个值，最后将key值赋值到当前。完成插入
			end--;

		}
		dat[end+1] = key;
	}
}

/******************************
 *希尔排序法（直接插入排序法的优化）:时间复杂度：n^2
 *输入：dat  要排序的数据
 *		len 数据长度
 *返回：无
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
 *直接选择排序：时间复杂度：n^2
 *输入：dat  要排序的数据
 *		len 数据长度
 *返回：无
 *****************************/
void Sort_Select(int* dat,UINT8 len)
{
	int i;
	UINT8 minIndex,maxIndex;
	UINT8 left=0,right=len-1;//左右索引号
	
	while(left < right)
	{
		minIndex = left;
		maxIndex = right;
		for(i = left;i<=right;i++)//找到最大最小值索引号
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
 *向下调整堆，即子节点大于父节点，则与子节点与父节点交换。此处用静态堆实现
 *堆是完全二叉树
 *输入：arr:输入的数据；
 *		size:整个堆的大小；
 *		parent:节点的父节点
 *输出：arr：重新排列的数据
 *返回：无
 *****************************/
static void HeapAdjust(int *arr,int size,int parent)
{
	int child = parent*2 + 1;//静态完全二叉树的性质

	while(child < size)
	{
		if((child + 1 < size) && (arr[child + 1] > arr[child]))//右节点超出堆大小且右节点的值大于左节点的值,子节点定位为右节点
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
 *堆排序：时间复杂度：nlogn
 *输入：arr:输入的数据；
 *		len:输入数据的数量；
 *输出：arr：重新排列的数据
 *返回：无
 *****************************/
void Sort_Heat(int *arr,int len)
{
	/* arr本身就是堆，但不一定是大顶堆，所以需要先构造成大顶堆 */
	/* 构造大顶堆需要从最后一个非叶子结点开始，从左至右，从下到上调整 */
	int root = len/2 - 1;//最后一个非叶子结点
	int end = len - 1;

	for(;root >= 0;root --)
		HeapAdjust(arr,len,root);
	
	/* 调整：此时数组已经是大顶堆，交换对顶和最后一个元素，重新调整为大顶堆 */
	while(end > 0)
	{
		swap_int(&arr[0],&arr[end]);//arr[0]为对顶，arr[end]为最后一个元素
		HeapAdjust(arr,end--,0);//重新调整为大顶堆
	}
}

/******************************
 *二路归并
 *输入：arr:输入的数据；
 *		left:arr中要归并的两组数据的最左索引
 *		right:arr中要归并的两组数据的最右索引
 *		mid:arr中要归并的两组数据的第1组数据的最后索引
 *输出：temp:归并后的数据
 *返回：无
 *****************************/
static void MergeData(int *arr,int left,int mid,int right,int *temp)
{
	int index1 = left;//第1组数据的下角标
	int index2 = mid+1;//第2组数据的下角标
	int i = 0;
	while(index1<=mid && index2<=right)
	{
		if(arr[index1] < arr[index2])
			temp[i++] = arr[index1++];
		else
			temp[i++] = arr[index2++];
	}
	/* 接收剩下的数据 */
	while(index1 <= mid)
		temp[i++] = arr[index1++];
	while(index2 <= right)
		temp[i++] = arr[index2++];
}
/******************************
 *归并排序的分组
 *输入：arr:输入的数据；
 *		left:arr中要归并的两组数据的最左索引
 *		right:arr中要归并的两组数据的最右索引
 *输出：temp:归并后的数据
 *返回：无
 *****************************/
static _MergeSort(int *arr,int left,int right,int *temp)
{
	int mid;
	if((right - left) <= 0)//退出递归的条件
		return;
	mid = left+(right - left)/2;//取中间索引，即第1组数据的最后一个索引
	_MergeSort(arr,left,mid,temp);
	_MergeSort(arr,mid+1,right,temp);
	MergeData(arr,left,mid,right,temp);
	memcpy(arr + left,temp,sizeof(arr[0])*(right - left + 1));
}
/******************************
 *归并排序：将待排序的元素序列分为两个长度相等的子序列,对每个子序列进行排序,然后将他们合并成一个序列,合并两个子序列的过程称为二路归并.
 *时间复杂度：nlogn
 *输入：arr:输入的数据；
 *		size:排序数据大小
 *输出：arr:排序完的数据
 *返回：无
 *****************************/
void Sort_Merge(int *arr,int size)
{
	int *temp = (int *)malloc(sizeof(arr[0])*size);
	if(NULL == temp)
	{
		printf("申请内存失败\r\n");
		return;
	}
	_MergeSort(arr,0,size-1,temp);
	free(temp);
	temp = NULL;
}
