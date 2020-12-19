/*********************************************************************
*wangfeng
*2020.10.19-2020.12.4
*参考资料：https://blog.csdn.net/sx2448826571/article/details/80487531
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
 *冒泡排序法：时间复杂度：n^2,稳定
 *输入：mode 0:升序；1：降序
 *		dat  要排序的数据
 *		len  数据的长度
 *返回：无
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
				if(dat[j]<dat[j+1])//降序，注意这里一定是小于，不能是小于等于，否则排序不稳定
					swap_int(&dat[j],&dat[j+1]);
			}
			else
			{
				if(dat[j]>dat[j+1])//升序，注意这里一定是大于，不能是大于等于，否则排序不稳定
					swap_int(&dat[j],&dat[j+1]);
			}
		}
	}
}

/******************************
 *快速排序法:时间复杂度：nlogn，不稳定
 *输入：dat  要排序的数据
 *		start 数据开始下标
 *		end  数据结束下标
 *返回：无
 *****************************/
void Sort_Quick(int *dat,int start,int end)
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
 *稳定性：稳定
 *思想：1.选中1个要比较的值；
 *		2.以该值为最右，从右向左比较，如果左边值大，左值向右移，空出位置
 *		3.直到找到比该值小的数，或找到最左，结束
 *		4.选下一个要比较的值，重复2-3步，直到整个序列结束
 *输入：dat  要排序的数据
 *		len 数据长度
 *返回：无
 *****************************/
void Sort_Insert(int *dat,int len)
{
	int i,key,end;
	for(i = 1;i<len;i++)
	{
		key = dat[i];//保存每次要比较的值
		end = i-1;
		while(end >= 0 && key<dat[end])//向前比较，直到找到比自己小的，插入。一定是key<dat[end]，不能小于等于，否则不稳定。
		{
			dat[end+1] = dat[end];//插入的方法为：将前一个值赋值到后一个值，最后将key值赋值到当前。完成插入
			end--;

		}
		dat[end+1] = key;
	}
}

/******************************
 *希尔排序法（直接插入排序法的优化）:时间复杂度：n^2
 *稳定性：不稳定
 *思想：1.分组
 *		2.对分组进行插入排序
 *		3.减小分组间距，减小序列个数
 *输入：dat  要排序的数据
 *		len 数据长度
 *返回：无
 *****************************/
void Sort_Shell(int *dat,int len)
{
	int gap = len/2;
	int key,end,i=0;
	for(gap;gap>0;gap/=2)//增量也可以取其他值
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
 *思想：1.找出第i小的值，放到第i个位置
 *稳定性：不稳定
 *输入：dat  要排序的数据
 *		len 数据长度
 *返回：无
 *****************************/
void Sort_Select(int* dat,int len)
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
 *思想：1.对所有数据建立最大堆
 *		2.取出堆顶最大值与末端交换
 *		3.调整为最大堆，重复2-3
 *稳定性：不稳定
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
	
	/* 调整：此时数组已经是大顶堆，交换堆顶和最后一个元素，重新调整为大顶堆 */
	while(end > 0)
	{
		swap_int(&arr[0],&arr[end]);//arr[0]为堆顶，arr[end]为最后一个元素
		HeapAdjust(arr,end--,0);//重新调整为大顶堆
	}
}

/*****************************************************************************************************************/
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
		if(arr[index1] <= arr[index2])//为保证稳定性，相等时优先选左边的
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
static void _MergeSort(int *arr,int left,int right,int *temp)
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
 *归并排序：将待排序的元素序列分为两个长度相等的子序列,对每个子序列进行排序,
 *			然后将他们合并成一个序列,合并两个子序列的过程称为二路归并.
 *时间复杂度：nlogn
 *稳定性：稳定
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
/******************************
 *归并排序：非递归方式
 *时间复杂度：nlogn
 *稳定性：稳定
 *输入：arr:输入的数据；
 *		size:排序数据大小
 *输出：arr:排序完的数据
 *返回：无
 *****************************/
void Sort_Merge_Nor(int *arr,int size)
{
	int gap,i;
	int left,right,mid;
	int *temp = (int *)malloc(sizeof(arr[0])*size);
	if(NULL == temp)
	{
		printf("申请内存失败\r\n");
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
			//if(mid >= size)//确保所有数据都能分组
			//	mid = size - 1;
			if(mid >= size-1)//中间数大于最大下标，说明到了最后一组，最后一组已经排好序了，所以直接退出循环
				break;
			if(right >= size)//确保所有数据都能分组
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
 *桶式排序:需要事先直到排序数组中的最大值
 *时间复杂度：m+n
 *稳定性：稳定
 *输入：arr:输入的数据；
 *		size:排序数据大小
 *		max:待排序数组中的最大值
 *输出：arr:排序完的数据
 *返回：无
 *****************************/
void Sort_Bucket(int *arr,int size,int max)
{
	int *temp,*count;
	int i;

	temp = (int *)malloc(sizeof(arr[0])*size);
	if(temp == NULL)
	{
		printf("申请内存失败\r\n");
		return;
	}
	count = (int *)malloc(sizeof(int)*max);
	if(count == NULL)
	{
		free(temp);
		temp = NULL;
		printf("申请内存失败\r\n");
		return;
	}

	for(i = 0;i<size;i++)//带排序数组赋值到临时变量
		temp[i] = arr[i];
	for(i = 0;i<max;i++)//计数器清零
		count[i] = 0;
	for(i = 0;i<size;i++)//统计每个数字出现的次数
		count[temp[i]] ++;
	for(i = 1;i<max;i++)//count[i]记录了i+1的起始位置
		count[i] = count[i - 1] + count[i];
	for(i = size - 1;i >= 0;i--)//从尾部开始顺序输出，保证排序的稳定性
		arr[--count[temp[i]]] = temp[i];
}