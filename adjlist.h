#ifndef ADJLIST_H
#define ADJLIST_H

#include <vector>
#include <iostream>
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




void CreateAdjList(AdjList &mylist,vector<vector<string>> str)
{
    for(int i=0;i<VEX_NUM;i++)
    {
        mylist[i].firstArc=NULL;
        mylist[i].airport_NO=i+1;
    }
    for(int i=1;i<str.size();i++)//循坏内是一行的信息
    {
        ArcNode *newarc;
        newarc=(ArcNode*)malloc(sizeof(ArcNode));//新的弧，分配空间
        newarc->arcInfo.flightID=0;
        newarc->arcInfo.deparAirport=0;
        newarc->arcInfo.ArriAirport=0;
        newarc->arcInfo.deparHour=0;
        newarc->arcInfo.deparMinute=0;
        newarc->arcInfo.arriHour=0;
        newarc->arcInfo.arriMinute=0;
        newarc->arcInfo.airFare=0;
        newarc->nextarc=NULL;
        //下面录入航班ID
        for(int t=0;t<str[i][0].size();t++)
        {
            newarc->arcInfo.flightID=newarc->arcInfo.flightID*10+str[i][0][t]-'0';
        }
        //下面录入起飞机场
        for(int t=0;t<str[i][4].size();t++)
        {
            newarc->arcInfo.deparAirport=newarc->arcInfo.deparAirport*10+str[i][4][t]-'0';
        }

        //下面录入降落机场
        for(int t=0;t<str[i][5].size();t++)
        {
            newarc->arcInfo.ArriAirport=newarc->arcInfo.ArriAirport*10+str[i][5][t]-'0';
        }

        //下面录入起飞时间
        newarc->arcInfo.deparDate=str[i][6][2];
        int maohao;//冒号位置
        for(maohao=0;maohao<str[i][6].size();maohao++)
        {
            if(str[i][6][maohao]==':')
                break;
        }//找到冒号位置
        if(str[i][6][maohao-2]>='0'&&str[i][6][maohao-2]<='9')
        {
            newarc->arcInfo.deparHour+=(str[i][6][maohao-2]-'0')*10;
        }
        newarc->arcInfo.deparHour+=str[i][6][maohao-1]-'0';
        newarc->arcInfo.deparMinute+=str[i][6][maohao+2]-'0';
        newarc->arcInfo.deparMinute+=(str[i][6][maohao+1]-'0')*10;

        //下面录入降落时间
        newarc->arcInfo.arriDate=str[i][7][2];
        for(maohao=0;maohao<str[i][7].size();maohao++)
        {
            if(str[i][7][maohao]==':')
                break;
        }//找到冒号位置
        if(str[i][7][maohao-2]>='0'&&str[i][7][maohao-2]<='9')
        {
            newarc->arcInfo.arriHour+=(str[i][7][maohao-2]-'0')*10;
        }
        newarc->arcInfo.arriHour+=str[i][7][maohao-1]-'0';
        newarc->arcInfo.arriMinute+=str[i][7][maohao+2]-'0';
        newarc->arcInfo.arriMinute+=(str[i][7][maohao+1]-'0')*10;

        //下面录入机型
        newarc->arcInfo.planeModel=str[i][9][0];

        //下面录入费用
        for(int t=0;t<str[i][10].size();t++)
        {
            newarc->arcInfo.airFare=newarc->arcInfo.airFare*10+str[i][10][t]-'0';
        }

        newarc->adjvex=newarc->arcInfo.ArriAirport-1;

        //全部信息已经输入newarc中，下面将新构造的边加入邻接表中
        //要把这个新的边连到这个结点上：mylist[newarc->arcInfo.deparAirport-1]
        newarc->nextarc=mylist[newarc->arcInfo.deparAirport-1].firstArc;
        mylist[newarc->arcInfo.deparAirport-1].firstArc=newarc;
    }
}

bool transAbility(ArcNode vex1,ArcNode vex2)
//两个航班能否构成转机关系
{
    if(vex1.arcInfo.ArriAirport!=vex2.arcInfo.deparAirport)
        return 0;
    if(cmpTime(vex1.arcInfo.arriDate,vex1.arcInfo.arriHour,vex1.arcInfo.arriMinute
               ,vex2.arcInfo.arriDate,vex2.arcInfo.arriHour,vex2.arcInfo.arriMinute))
    {
        return 1;
    }
    return 0;
}

int FirstAdjVex(AdjList vexlist, int v)
//返回存在下标为v的位置的顶点的第一个邻接顶点的位置，不存在则返回-1
{
    int pos;
    if(vexlist[v].firstArc)
    {
        pos=vexlist[v].firstArc->adjvex;
        return pos;
    }
    return -1;
}
int NextAdjVex(AdjList vexlist,int v,int w)
//返回v的相对于w的下一个邻接顶点，其中v，w都是顶点在list中的存储位置
{
    int pos;
    ArcNode *p;
    p=vexlist[v].firstArc;
    while(p)
    {
        if(p->adjvex==w)
        {
            if(p->nextarc&&p->nextarc->adjvex!=w)//如果w还不是最后一个顶点,且排除两个机场之间多条航线的问题
            {
                pos=p->nextarc->adjvex;
                return pos;
            }
        }
        p=p->nextarc;
    }
    return -1;
}

void DFStraverse(AdjList adjlist,int v,bool *flag)
//从v出发
{
    flag[v]=1;
    cout<<adjlist[v].airport_NO<<" ";
    for(int w=FirstAdjVex(adjlist,v);w>=0;w=NextAdjVex(adjlist,v,w))
    {
        if(flag[w]==0)
            DFStraverse(adjlist,w,flag);
    }
}

void BFStravers(AdjList &adjlist, int port_NO)
//从第port_N个机场出发广度优先遍历
{
    bool flag[VEX_NUM];//是否被遍历过
    for(int i=0;i<VEX_NUM;i++)
        flag[i]=0;

    queue<int> myqueue;//辅助队列
    for(int i=0;i<VEX_NUM;i++)
    {
        if(flag[i]==0)//未被访问过
        {
            flag[i]=1;
            cout<<adjlist[i].airport_NO<<" ";
            myqueue.push(i);
            while(!myqueue.empty())
            {
                int temp=myqueue.front();//队头结点的存储位置
                ArcNode *p;
                p=adjlist[temp].firstArc;//去看它的邻接顶点有哪些

                while(p)
                {
                    //p指向的结点的存储位置为 p->arcInfo.ArriAirport-1
                    if(flag[p->arcInfo.ArriAirport-1]==0)
                    {
                        flag[p->arcInfo.ArriAirport-1]=1;
                        cout<<adjlist[p->arcInfo.ArriAirport-1].airport_NO<<" ";
                        myqueue.push(p->arcInfo.ArriAirport-1);
                    }
                }
            }
        }
    }
}

#endif // ADJLIST_H
