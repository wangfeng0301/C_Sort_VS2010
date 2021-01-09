/*********************************************************************
*wangfeng
*2020.10.19-2021.1.9
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
			if(mid >= size)//确保所有数据都能分组
				mid = size - 1;
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

	free(temp);
	free(count);
}

/******************************
 *基数排序-顺序存储:桶式排序的扩展
 *时间复杂度：d*(n+r)
 *稳定性：稳定
 *输入：arr:输入的数据；
 *		n:排序数据的个数
 *		d:排序码个数，即按照几个排序，如两位正整数d=2，3位正整数d=3
 *		r:基数，如10进制数，基数取10
 *输出：arr:排序完的数据
 *返回：无
 *注：排序码就是按照这个码来排序的元素。如3位十进制数，排序码是0-9。
 *****************************/
void Sort_Radix_InTurn(int *arr,int n,int d,int r)
{
	int *temp,*count;
	int i,j,k;
	int Radix = 1;//模

	temp = (int *)malloc(sizeof(arr[0])*n);//辅助排序临时数组
	if(temp == NULL)
	{
		printf("申请内存失败\r\n");
		return;
	}
	count = (int *)malloc(sizeof(int)*r);//桶容量计数器，count[i]存储第i个桶中的数据个数
	if(count == NULL)
	{
		free(temp);
		temp = NULL;
		printf("申请内存失败\r\n");
		return;
	}

	for(i = 1;i <= d;i++)//使用d次桶式排序
	{
		for(j = 0;j < r;j++)//计数器清零
			count[j] = 0;
		for(j = 0;j<n;j++)//统计每个排序码出现的次数
		{
			k = (arr[j]/Radix)%r;//取arr[j]的第i位排序码，如3位数就是个位十位百位
			count[k] ++;
		}
		for(j = 1;j < r;j++)//分配给r个桶
			count[j] = count[j - 1] + count[j];//count[j]记录了j+1的起始位置
		for(j = n - 1;j >= 0;j--)//从尾部开始顺序收集，保证排序的稳定性
		{
			k = (arr[j]/Radix)%r;
			count[k]--;//使用了第k个桶的一个位置，桶剩余量的计数器减1
			temp[count[k]] = arr[j];
		}
		for(j = 0;j < n;j++)//排序后的数组复制到arr中，以便下一轮排序
			arr[j] = temp[j];
		Radix *= r;//修改模Radix			
	}
	free(temp);
	free(count);
}

/******************************
 *基数排序-静态链:桶式排序的扩展
 *时间复杂度：d*(n+r)
 *稳定性：稳定
 *输入：arr:输入的数据；
 *		n:排序数据的个数
 *		d:排序码个数，即按照几个排序，如两位正整数d=2，3位正整数d=3
 *		r:基数，如10进制数，基数取10
 *输出：arr:排序完的数据
 *返回：无
 *注：排序码就是按照这个码来排序的元素。如3位十进制数，排序码是0-9。
 *****************************/
typedef struct{
	int key;//排序码值
	int next;//下一个节点在数组中的下标
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
	int first = 0;//first指向静态链中的第一个数据，故默认下标=0
	Node_t *temp;
	StatiQueue_t *queue;

	temp = (Node_t *)malloc(sizeof(Node_t)*n);//辅助排序临时数组
	if(temp == NULL)
	{
		printf("申请内存失败\r\n");
		return;
	}
	
	queue = (StatiQueue_t *)malloc(sizeof(StatiQueue_t)*r);//存放r个桶的静态队列
	if(queue == NULL)
	{
		free(temp);
		temp = NULL;
		printf("申请内存失败\r\n");
		return;
	}
	/* 数据复制到临时数组中，方便使用队列排序 */
	/* 如果函数传入的数据本身就是Node_t格式的，则不用临时数组 */
	for(i = 0;i < n;i++)
		temp[i].key = arr[i];
	/* 初始化建链，相邻数据的静态指针连接为单链表 */
	for(i = 0;i < n-1;i++)
		temp[i].next = i+1;
	temp[n-1].next = -1;//链尾next为空

	/* 对第i个排序码进行分配和收集，共d轮 */
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
 *分配过程
 *输入：arr:输入的数据；
 *		first:静态链中第一个数据的下标
 *		i:第i个排序码
 *		r:基数，如10进制数，基数取10
 *		queue:队列，作为桶的计数器
 *输出：arr:排序完的数据
 *返回：无
 *注：排序码就是按照这个码来排序的元素。如3位十进制数，排序码是0-9。
 *****************************/
static void distribute(Node_t *arr,int first,int i,int r,StatiQueue_t *queue)
{
	int j,k,a;
	int curr = first;//当前要排序数据的下标
	/* 初始化r个队列 */
	for(j = 0;j < r;j++)
		queue[j].head = -1;

	/* 对整个静态链进行分配，沿着链寻找 */
	while(curr != -1)
	{
		k = arr[curr].key;//取数据
		for(a = 0;a < i;a++)//取第i位排序码k
			k = k/r;
		k = k%r;

		/* 把arr[curr]分配到第k个桶中 */
		if(queue[k].head == -1)//若桶为空，arr[curr]就是桶中第一个数据
			queue[k].head = curr;
		else//否则加到桶的尾部
			arr[queue[k].tail].next = curr;
		queue[k].tail = curr;//当前待排序数据的下标标记为桶的尾部
		curr = arr[curr].next;//静态指针移动，指向下一个带排序的数据，继续分配
	}
}
/******************************
 *收集过程
 *输入：arr:输入的数据
 *		r:基数，如10进制数，基数取10
 *		queue:队列，作为桶的计数器
 *输出：arr:排序完的数据
 *		first:静态链中第一个数据的下标，这里作为返回值，供distribute调用
 *返回：无
 *注：排序码就是按照这个码来排序的元素。如3位十进制数，排序码是0-9。
 *****************************/
static void collect(Node_t *arr,int *first,int r,StatiQueue_t *queue)
{
	int k = 0,last;
	/* 找到第一个非空队列 */
	while(queue[k].head == -1)
		k++;

	*first = queue[k].head;//记录待排序链中的第一个下标
	last = queue[k].tail;//记录当前队列中待排序链的最后一个下标

	/* 每个桶依次收集 */
	/* 经过分配后，待排序的数据已经按照排序码分成一个一个的单向链 */
	/* 所以收集只是通过队列将各个单向链连接起来 */
	while(k < r-1)
	{
		k++;
		while(k < r-1 && queue[k].head == -1)
			k++;
		if(queue[k].head != -1)
		{
			arr[last].next = queue[k].head;//收尾相连
			last = queue[k].tail;//记录最后一个下标
		}
	}
	arr[last].next = -1;//收集完毕，排好序数据的最后一个指向空
}
/******************************
 *线性整理过程
 *输入：arr:输入的数据
 *		n:待排序数据的数量
 *		first:静态链中第一个数据的下标
 *输出：temp:排序完的数据
 *返回：无
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
 *索引排序:简单插入的索引排序。IndexArr[i]表示arr第i个位置应该放arr[IndexArr[i]]
 *时间复杂度：
 *稳定性：稳定
 *输入：arr:待排序的数据
 *		size:待排序数据的个数
 *输出：arr:排序完的数据
 *返回：无
 *****************************/
void Sort_Index_Insert(int *arr, int size)
{
	int i,j,k;
	int *IndexArr;
	int temp;//临时存储空间

	IndexArr = (int *)malloc(sizeof(arr[0])*size);
	if(NULL == IndexArr)
	{
		printf("申请内存失败\r\n");
		return;
	}
	/* 初始化索引下标 */
	for(i = 0;i < size;i++)
		IndexArr[i] = i;

	/* 简单插入排序的地址排序过程 */
	for(i = 0;i < size;i++)
	{
		for(j = i;j > 0;j--)
		{
			/* 对索引进行调整，后期再整理 */
			if(arr[IndexArr[j]] < arr[IndexArr[j-1]])
				swap_int(&IndexArr[j],&IndexArr[j-1]);
			else
				break;
		}
	}
	
	/* 调整 */
	for(i = 0;i < size;i++)
	{
		temp = arr[i];
		j = i;
		/* 如果循环链中索引下表不是i，则顺链进行调整 */
		/* IndexArr[i]表示arr第i个位置应该放arr[IndexArr[i]] */
		while(IndexArr[j] != i)
		{
			k = IndexArr[j];//k是链接j指向的下标
			arr[j] = arr[k];//把k下标中的值复制到j位，第j大元素正确归位
			IndexArr[j] = j;//已经正确归位，故j就是自身
			j = k;
		}
		arr[j] = temp;
		IndexArr[j] = j;//已经正确归位，故j就是自身
	}
}