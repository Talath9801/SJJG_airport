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
