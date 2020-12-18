#ifndef __SORT_H__
#define __SORT_H__
#include <stdio.h>
#include <stdint.h>
#include <BaseTsd.h>

void Sort_Bubbling(UINT8 mode,int *dat,UINT16 len);
void Sort_Quick(int *dat,UINT8 start,UINT8 end);
void Sort_Insert(int *dat,UINT8 len);
void Sort_Shell(int *dat,UINT8 len);
void Sort_Select(int* dat,UINT8 len);
void Sort_Heat(int *arr,int len);
void Sort_Merge(int *arr,int size);
void Sort_Merge_Nor(int *arr,int size);

#endif