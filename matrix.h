#ifndef MATRIX_H
#define MATRIX_H
#include <adjlist.h>

void list2Mat(AdjList adjlist, int mat[VEX_NUM][VEX_NUM]);
//矩阵初始化为-1
//操作的时候，如果直飞，改成0
//如果一次转机，在还是-1的地方改成1
//如果两次转机，在还是-1的地方改成2

#endif // MATRIX_H
