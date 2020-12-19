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

bool transAbility(ArcNode arc1,ArcNode arc2)
//两个航班能否构成转机关系
{
    if(arc1.arcInfo.ArriAirport!=arc2.arcInfo.deparAirport)
        return 0;
    if(cmpTime(arc1.arcInfo.arriDate,arc1.arcInfo.arriHour,arc1.arcInfo.arriMinute
               ,arc2.arcInfo.deparDate,arc2.arcInfo.deparHour,arc2.arcInfo.deparMinute)==1)
    {
        return 1;
    }
    return 0;
}

ArcNode* firstAdjArc(AdjList adjlist, ArcNode *cur_arc)
//返回由当前弧的弧尾发出的第一条可以构成转机的弧，如果不存在，返回空指针
{
    ArcNode *p;
    int v=cur_arc->arcInfo.ArriAirport-1;//上一班飞机目标机场的存储位置
    p=adjlist[v].firstArc;
    while(p)
    {
        if(transAbility(*cur_arc,*p))//如果满足转机条件
        {
            //cout<<cur_arc->arcInfo.flightID<<"   first->"<<p->arcInfo.flightID<<endl;
            return p;
        }
        //如果不满足转机条件
        p=p->nextarc;
    }
    return NULL;
}

ArcNode* nextAdjArc(AdjList adjlist,ArcNode *vvv,ArcNode *w)
//返回由vvv的弧尾顶点发出的相对于弧w之后的一条可以形成转机的弧，如果不存在，返回空指针
{
    int v=vvv->arcInfo.ArriAirport-1;//上一班飞机目标机场的存储位置
    ArcNode *p;
    p=adjlist[v].firstArc;
    while(p)
    {
        if(p==w&&p->nextarc)//找到w且还不是最后一条边
        {
            p=p->nextarc;
            if(p==NULL)
                return NULL;
            while(p)
            {
                if(transAbility(*vvv,*p))//如果满足转机条件
                {
                    //cout<<vvv->arcInfo.flightID<<"after"<<w->arcInfo.flightID<<"next"<<p->arcInfo.flightID<<endl;
                    return p;
                }
                //如果不满足转机条件
                p=p->nextarc;
                if(p==NULL)
                    return NULL;
            }
        }
        p=p->nextarc;
    }
    return NULL;
}
int printArc(ArcNode* arc)
{
    cout.flags(ios::left);
    cout<<setw(3)<<arc->arcInfo.deparAirport<<"-- flight "
       <<arc->arcInfo.flightID<<" -->"<<arc->arcInfo.ArriAirport<<" "<<endl;
}

void BFStraverse(AdjList adjlist, int v,int(*visit)(ArcNode* arc))
//从存储位置为v的机场出发，广度优先遍历，非递归
{
    int depthlimit=9;
    int count=0;
    queue<ArcNode> myqueue;
    //先把起始点后面的弧都压到队列里面
    ArcNode* h;
    h=adjlist[v].firstArc;
    while(h)
    {
        //cout<<h->arcInfo.flightID<<"(->"<<h->arcInfo.ArriAirport<<")"<<" "<<endl;
        visit(h);
        myqueue.push(*h);
        h=h->nextarc;
    }

    count++;
    if(count>depthlimit)
        exit(1);

    while(!myqueue.empty())
    {
        ArcNode *head=&myqueue.front();
        myqueue.pop();
        for(ArcNode* w=firstAdjArc(adjlist,head);w!=NULL;w=nextAdjArc(adjlist,head,w))
        {
            //cout<<w->arcInfo.flightID<<"(->"<<w->arcInfo.ArriAirport<<")"<<" "<<endl;
            visit(w);
            myqueue.push(*w);
        }
        count++;
        if(count>depthlimit)
            exit(1);
    }
    cout<<"end";
}

#endif // ADJLIST_H
