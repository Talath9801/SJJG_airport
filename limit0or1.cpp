#include <adjlist.h>
//限制直飞或一次转机，求航班

void limitDirect(AdjList adjlist,int from,int to)
//从from到to的直飞路线，from  to 都是存储位置
{
    ArcNode *h;
    h=adjlist[from].firstArc;
    while(h)
    {
        int arriNO=h->arcInfo.ArriAirport;
        if(arriNO==to+1)
        {
            //cout<<"flight"<<h->arcInfo.flightID<<endl;
            printArc(h);
            //break;
        }
        h=h->nextarc;
    }

}
void limitOneTrans(AdjList adjlist, int matrix[VEX_NUM][VEX_NUM],int from, int to)
//从from到to的一次转机路线，from  to 都是存储位置
{
    ArcNode *h=adjlist[from].firstArc;
    while(h)
    {
        if(matrix[h->adjvex][to]!=0)
        {
            h=h->nextarc;
            continue;
        }

        else  //当前这个中转点是可行的
        {
            ArcNode *p=adjlist[h->adjvex].firstArc;
            while(p)
            {
                if(transAbility(*h,*p)&&p->adjvex==to)//可以中转
                {
                    cout<<h->arcInfo.deparAirport<<" --flight "<<h->arcInfo.flightID<<" - flight "<<p->arcInfo.flightID<<"-->"<<p->arcInfo.ArriAirport<<endl;

                }
                p=p->nextarc;
            }
            h=h->nextarc;
        }
    }

}

void con_direct(AdjList adjlist,int from,int to,int h1,int m1,int h2,int m2,int h3,int m3,int h4,int m4,char model,mypath *timepath,mypath *feepath)
//conditional有限制的情况
{
    ArcNode *h;
    h=adjlist[from].firstArc;
    while(h)
    {
        int arriNO=h->arcInfo.ArriAirport;
        if(arriNO==to+1
                &&cmpTime2(h->arcInfo.deparHour,h->arcInfo.deparMinute,h2,m2)!=-1
                &&cmpTime2(h1,m1,h->arcInfo.deparHour,h->arcInfo.deparMinute)!=-1
                &&cmpTime2(h3,m3,h->arcInfo.arriHour,h->arcInfo.arriMinute)!=-1
                &&cmpTime2(h->arcInfo.arriHour,h->arcInfo.arriMinute,h4,m4)!=-1
                &&(h->arcInfo.planeModel==model||model=='0'))
        {
            //cout<<"flight"<<h->arcInfo.flightID<<endl;
            printArc(h);
            if(timepath->timeLength>timeSpan(h,h))//最短时间更新
            {
                timepath->timeLength=timeSpan(h,h);
                timepath->flightList[0]=h;
            }
            if(feepath->cost>h->arcInfo.airFare)//最少费用更新
            {
                feepath->cost=h->arcInfo.airFare;
                feepath->flightList[0]=h;
            }
            //break;
        }
        h=h->nextarc;
    }
}
void con_oneTrans(AdjList adjlist,int matrix[VEX_NUM][VEX_NUM], int from,int to,int h1,int m1,int h2,int m2,int h3,int m3,int h4,int m4,char model,mypath *timepath,mypath *feepath)
{
    ArcNode *h=adjlist[from].firstArc;
    while(h)
    {
        if(matrix[h->adjvex][to]!=0)
        {
            h=h->nextarc;
            continue;
        }

        else  //当前这个中转点是可行的
        {
            ArcNode *p=adjlist[h->adjvex].firstArc;
            while(p)
            {
                if(transAbility(*h,*p)&&p->adjvex==to
                        &&cmpTime2(h->arcInfo.deparHour,h->arcInfo.deparMinute,h2,m2)!=-1
                        &&cmpTime2(h1,m1,h->arcInfo.deparHour,h->arcInfo.deparMinute)!=-1
                        &&cmpTime2(h3,m3,p->arcInfo.arriHour,p->arcInfo.arriMinute)!=-1
                        &&cmpTime2(p->arcInfo.arriHour,p->arcInfo.arriMinute,h4,m4)!=-1
                        &&(h->arcInfo.planeModel==model||model=='0')
                        &&(p->arcInfo.planeModel==model||model=='0'))//可以中转
                {
                    cout<<h->arcInfo.deparAirport<<" --flight "<<h->arcInfo.flightID<<" - flight "<<p->arcInfo.flightID<<"-->"<<p->arcInfo.ArriAirport<<endl;
                    if(timepath->timeLength>timeSpan(h,p))//更新最短时间
                    {
                        timepath->timeLength=timeSpan(h,p);
                        timepath->flightList[0]=h;
                        timepath->flightList[1]=p;
                    }
                    if(feepath->cost>h->arcInfo.airFare+p->arcInfo.airFare)
                    {
                        feepath->cost=h->arcInfo.airFare+p->arcInfo.airFare;
                        feepath->flightList[0]=h;
                        feepath->flightList[1]=p;
                    }

                }
                p=p->nextarc;
            }
            h=h->nextarc;
        }
    }

}
