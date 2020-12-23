#include <adjlist.h>

void limitTwoTrans(AdjList adjlist,int matrix[VEX_NUM][VEX_NUM],int from,int to)
//仅限2次转机，2次以内不算
{
    ArcNode *h1=adjlist[from].firstArc;
    while(h1)
    {
        if(matrix[h1->adjvex][to]!=1)
        {
            h1=h1->nextarc;
            continue;
        }
        else  //跳到可以再经过一次中转就到目标的机场
        {
            ArcNode *h2=adjlist[h1->adjvex].firstArc;
            while(h2)
            {
                if(matrix[h2->adjvex][to]!=0||(!transAbility(*h1,*h2)))
                {
                    h2=h2->nextarc;
                    continue;
                }
                else
                {
                    ArcNode *h3=adjlist[h2->adjvex].firstArc;
                    while(h3)
                    {
                        if(transAbility(*h2,*h3)&&h3->adjvex==to)
                        {
                            cout<<h1->arcInfo.deparAirport
                               <<" --flight "<<h1->arcInfo.flightID
                              <<" - flight "<<h2->arcInfo.flightID
                             <<" - flight "<<h3->arcInfo.flightID
                            <<"-->"<<h3->arcInfo.ArriAirport<<endl;
                        }
                        h3=h3->nextarc;
                    }
                    h2=h2->nextarc;
                }
            }
        }
        h1=h1->nextarc;
    }
}
void limitThreeTrans(AdjList adjlist,int matrix[VEX_NUM][VEX_NUM],int from,int to)
{
    ArcNode *h1=adjlist[from].firstArc;
    while(h1)
    {
        if(matrix[h1->adjvex][to]!=2)
        {
            h1=h1->nextarc;
            continue;
        }
        else  //跳到可以再经过一次中转就到目标的机场
        {
            ArcNode *h2=adjlist[h1->adjvex].firstArc;
            while(h2)
            {
                if(matrix[h2->adjvex][to]!=1||(!transAbility(*h1,*h2)))
                {
                    h2=h2->nextarc;
                    continue;
                }
                else
                {
                    ArcNode *h3=adjlist[h2->adjvex].firstArc;
                    while(h3)
                    {
                        if(matrix[h3->adjvex][to]!=0||(!transAbility(*h2,*h3)))
                        {
                            h3=h3->nextarc;
                            continue;
                        }
                        else
                        {
                            ArcNode *h4=adjlist[h3->adjvex].firstArc;
                            while(h4)
                            {
                                if(transAbility(*h3,*h4)&&h4->adjvex==to)
                                {
                                    cout<<h1->arcInfo.deparAirport
                                       <<" --flight "<<h1->arcInfo.flightID
                                      <<" - flight "<<h2->arcInfo.flightID
                                     <<" - flight "<<h3->arcInfo.flightID
                                    <<" - flight "<<h4->arcInfo.flightID
                                    <<"-->"<<h4->arcInfo.ArriAirport<<endl;
                                }
                                h4=h4->nextarc;
                            }
                            h3=h3->nextarc;
                        }
                    }
                    h2=h2->nextarc;
                }
            }
        }
        h1=h1->nextarc;
    }



}

void fromTo(AdjList adjlist,int matrix[VEX_NUM][VEX_NUM],int from,int to)
{
    if(matrix[from][to]==0)//直飞
    {
        limitDirect(adjlist,from,to);//输出直飞的
        limitOneTrans(adjlist,matrix,from,to);
        limitTwoTrans(adjlist,matrix,from,to);
        limitThreeTrans(adjlist,matrix,from,to);
    }
    else if(matrix[from][to]==1)//一次转机
    {
        limitOneTrans(adjlist,matrix,from,to);
        limitTwoTrans(adjlist,matrix,from,to);
        limitThreeTrans(adjlist,matrix,from,to);
    }
    else if(matrix[from][to]==2)//两次转机
    {
        limitTwoTrans(adjlist,matrix,from,to);
        limitThreeTrans(adjlist,matrix,from,to);
    }
    else  //三次转机
    {
        limitThreeTrans(adjlist,matrix,from,to);
    }
}
