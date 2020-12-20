#ifndef ADJLIST_H
#define ADJLIST_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <queue>
#include <timefunction.h>
using namespace std;
#define VEX_NUM 79
typedef struct AInfo
{
    int flightID;//航班ID
    int deparAirport;
    int ArriAirport;

    char deparDate;//日
    int deparHour;
    int deparMinute;

    char arriDate;//日
    int arriHour;
    int arriMinute;

    char planeModel;//机型
    int airFare;//费用

};//弧的信息

typedef int VInfo;
typedef struct ArcNode
{
    int adjvex;//该弧指向的顶点的位置
    struct ArcNode *nextarc;//指向下一条弧的指针
    AInfo arcInfo;//弧的相关信息

}ArcNode;
typedef struct VNode
{
    VInfo airport_NO;//机场号
    ArcNode *firstArc;
}VNode,AdjList[VEX_NUM];




void CreateAdjList(AdjList &mylist,vector<vector<string>> str);

bool transAbility(ArcNode arc1,ArcNode arc2);
//两个航班能否构成转机关系

ArcNode* firstAdjArc(AdjList adjlist, ArcNode *cur_arc);
//返回由当前弧的弧尾发出的第一条可以构成转机的弧，如果不存在，返回空指针

ArcNode* nextAdjArc(AdjList adjlist,ArcNode *vvv,ArcNode *w);
//返回由vvv的弧尾顶点发出的相对于弧w之后的一条可以形成转机的弧，如果不存在，返回空指针

int printArc(ArcNode* arc);


void BFStraverse(AdjList adjlist, int v,int(*visit)(ArcNode* arc));
//从存储位置为v的机场出发，广度优先遍历，非递归

#endif // ADJLIST_H
