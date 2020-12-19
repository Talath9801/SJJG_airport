#ifndef ADJLIST_H
#define ADJLIST_H

#include <vector>
#include <string>
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


        //全部信息已经输入newarc中，下面将新构造的边加入邻接表中
        //要把这个新的边连到这个结点上：mylist[newarc->arcInfo.deparAirport-1]
        newarc->nextarc=mylist[newarc->arcInfo.deparAirport-1].firstArc;
        mylist[newarc->arcInfo.deparAirport-1].firstArc=newarc;
    }
}



#endif // ADJLIST_H
