#ifndef __SORT_H__
#define __SORT_H__
#include <stdio.h>
#include <stdint.h>
#include <BaseTsd.h>

void Sort_Bubbling(UINT8 mode,int *dat,int len);
void Sort_Quick(int *dat,int start,int end);
void Sort_Insert(int *dat,int len);
void Sort_Shell(int *dat,int len);
void Sort_Select(int* dat,int len);
void Sort_Heat(int *arr,int len);
void Sort_Merge(int *arr,int size);
void Sort_Merge_Nor(int *arr,int size);
void Sort_Bucket(int *arr,int size,int max);
void Sort_Radix_InTurn(int *arr,int n,int d,int r);

#endif