#include <adjlist.h>
#include <timefunction.h>


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


void con_twoTrans(AdjList adjlist,int matrix[VEX_NUM][VEX_NUM],int from,int to,int hr1,int m1,int hr2,int m2,int hr3,int m3,int hr4,int m4,char model,mypath *timepath,mypath *feepath)
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
                        if(transAbility(*h2,*h3)&&h3->adjvex==to
                                &&cmpTime2(h1->arcInfo.deparHour,h1->arcInfo.deparMinute,hr2,m2)!=-1
                                &&cmpTime2(hr1,m1,h1->arcInfo.deparHour,h1->arcInfo.deparMinute)!=-1
                                &&cmpTime2(hr3,m3,h3->arcInfo.arriHour,h3->arcInfo.arriMinute)!=-1
                                &&cmpTime2(h3->arcInfo.arriHour,h3->arcInfo.arriMinute,hr4,m4)!=-1
                                &&(h1->arcInfo.planeModel==model||model=='0')
                                &&(h2->arcInfo.planeModel==model||model=='0')
                                &&(h3->arcInfo.planeModel==model||model=='0'))
                        {
                            cout<<h1->arcInfo.deparAirport
                               <<" --flight "<<h1->arcInfo.flightID
                              <<" - flight "<<h2->arcInfo.flightID
                             <<" - flight "<<h3->arcInfo.flightID
                            <<"-->"<<h3->arcInfo.ArriAirport<<endl;
                            if(timepath->timeLength>timeSpan(h1,h3))
                            {
                                timepath->timeLength=timeSpan(h1,h3);
                                timepath->flightList[0]=h1;
                                timepath->flightList[1]=h2;
                                timepath->flightList[2]=h3;
                            }
                            int temp=h1->arcInfo.airFare+h2->arcInfo.airFare+h3->arcInfo.airFare;
                            if(feepath->cost>temp)
                            {
                                feepath->cost=temp;
                                feepath->flightList[0]=h1;
                                feepath->flightList[1]=h2;
                                feepath->flightList[2]=h3;
                            }
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
void con_3trans(AdjList adjlist,int matrix[VEX_NUM][VEX_NUM],int from,int to,int hr1,int m1,int hr2,int m2,int hr3,int m3,int hr4,int m4,char model,mypath *timepath,mypath *feepath)
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
                                if(transAbility(*h3,*h4)&&h4->adjvex==to
                                        &&cmpTime2(h1->arcInfo.deparHour,h1->arcInfo.deparMinute,hr2,m2)!=-1
                                        &&cmpTime2(hr1,m1,h1->arcInfo.deparHour,h1->arcInfo.deparMinute)!=-1
                                        &&cmpTime2(hr3,m3,h4->arcInfo.arriHour,h4->arcInfo.arriMinute)!=-1
                                        &&cmpTime2(h4->arcInfo.arriHour,h4->arcInfo.arriMinute,hr4,m4)!=-1
                                        &&(h1->arcInfo.planeModel==model||model=='0')
                                        &&(h2->arcInfo.planeModel==model||model=='0')
                                        &&(h3->arcInfo.planeModel==model||model=='0')
                                        &&(h4->arcInfo.planeModel==model||model=='0'))
                                {
                                    cout<<h1->arcInfo.deparAirport
                                       <<" --flight "<<h1->arcInfo.flightID
                                      <<" - flight "<<h2->arcInfo.flightID
                                     <<" - flight "<<h3->arcInfo.flightID
                                    <<" - flight "<<h4->arcInfo.flightID
                                    <<"-->"<<h4->arcInfo.ArriAirport<<endl;
                                    if(timepath->timeLength>timeSpan(h1,h4))
                                    {
                                        timepath->timeLength=timeSpan(h1,h4);
                                        timepath->flightList[0]=h1;
                                        timepath->flightList[1]=h2;
                                        timepath->flightList[2]=h3;
                                        timepath->flightList[3]=h4;
                                    }
                                    int temp=h1->arcInfo.airFare+h2->arcInfo.airFare+h3->arcInfo.airFare+h4->arcInfo.airFare;
                                    if(feepath->cost>temp)
                                    {
                                        feepath->cost=temp;
                                        feepath->flightList[0]=h1;
                                        feepath->flightList[1]=h2;
                                        feepath->flightList[2]=h3;
                                        feepath->flightList[3]=h4;
                                    }
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
void con_fromTo(AdjList adjlist,int matrix[VEX_NUM][VEX_NUM],int from,int to,int h1,int m1,int h2,int m2,int h3,int m3,int h4,int m4,char model)
{
    mypath *timePath;
    mypath *feePath;
    timePath=(mypath*)malloc(sizeof (mypath));
    feePath=(mypath*)malloc(sizeof (mypath));
    timePath->timeLength=999999999;
    feePath->cost=999999999;
    for(int i=0;i<4;i++)
    {
        timePath->flightList[i]=NULL;
        feePath->flightList[i]=NULL;
    }

    if(matrix[from][to]==0)//直飞
    {

        con_direct(adjlist,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        con_oneTrans(adjlist,matrix,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        con_twoTrans(adjlist,matrix,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        con_3trans(adjlist,matrix,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        if(timePath->flightList[0])//路径存在
        {
            cout<<"the shortest time is "<<timePath->timeLength<<" minutes"<<endl;
            cout<<"path: "<<endl;
            for(int i=0;i<4;i++)
            {
                if(timePath->flightList[i])
                {
                    cout<<"flight"<<timePath->flightList[i]->arcInfo.flightID<<" ";
                }
            }
            cout<<endl;
            cout<<endl;

            cout<<"the cheapest fee is "<<feePath->cost<<endl;
            cout<<"path:"<<endl;
            for (int i=0;i<4;i++)
            {
                if(feePath->flightList[i])
                {
                    cout<<"flight"<<feePath->flightList[i]->arcInfo.flightID<<" ";
                }
            }
            cout<<endl;
            cout<<endl;
        }
        else//路径不存在
        {
            cout<<"no choice"<<endl;
        }
    }
    else if(matrix[from][to]==1)//一次转机
    {
        con_oneTrans(adjlist,matrix,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        con_twoTrans(adjlist,matrix,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        con_3trans(adjlist,matrix,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        if(timePath->flightList[0])//路径存在
        {
            cout<<"the shortest time is "<<timePath->timeLength<<" minutes"<<endl;
            cout<<"path: "<<endl;
            for(int i=0;i<4;i++)
            {
                if(timePath->flightList[i])
                {
                    cout<<"flight"<<timePath->flightList[i]->arcInfo.flightID<<" ";
                }
            }
            cout<<endl;
            cout<<endl;

            cout<<"the cheapest fee is "<<feePath->cost<<endl;
            cout<<"path:"<<endl;
            for (int i=0;i<4;i++)
            {
                if(feePath->flightList[i])
                {
                    cout<<"flight"<<feePath->flightList[i]->arcInfo.flightID<<" ";
                }
            }
            cout<<endl;
            cout<<endl;
        }
        else//路径不存在
        {
            cout<<"no choice"<<endl;
        }
    }
    else if(matrix[from][to]==2)//两次转机
    {
        con_twoTrans(adjlist,matrix,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        con_3trans(adjlist,matrix,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        if(timePath->flightList[0])//路径存在
        {
            cout<<"the shortest time is "<<timePath->timeLength<<" minutes"<<endl;
            cout<<"path: "<<endl;
            for(int i=0;i<4;i++)
            {
                if(timePath->flightList[i])
                {
                    cout<<"flight"<<timePath->flightList[i]->arcInfo.flightID<<" ";
                }
            }
            cout<<endl;
            cout<<endl;

            cout<<"the cheapest fee is "<<feePath->cost<<endl;
            cout<<"path:"<<endl;
            for (int i=0;i<4;i++)
            {
                if(feePath->flightList[i])
                {
                    cout<<"flight"<<feePath->flightList[i]->arcInfo.flightID<<" ";
                }
            }
            cout<<endl;
            cout<<endl;
        }
        else//路径不存在
        {
            cout<<"no choice"<<endl;
        }
    }
    else  //三次转机
    {
        con_3trans(adjlist,matrix,from,to,h1,m1,h2,m2,h3,m3,h4,m4,model,timePath,feePath);
        if(timePath->flightList[0])//路径存在
        {
            cout<<"the shortest time is "<<timePath->timeLength<<" minutes"<<endl;
            cout<<"path: "<<endl;
            for(int i=0;i<4;i++)
            {
                if(timePath->flightList[i])
                {
                    cout<<"flight"<<timePath->flightList[i]->arcInfo.flightID<<" ";
                }
            }
            cout<<endl;
            cout<<endl;

            cout<<"the cheapest fee is "<<feePath->cost<<endl;
            cout<<"path:"<<endl;
            for (int i=0;i<4;i++)
            {
                if(feePath->flightList[i])
                {
                    cout<<"flight"<<feePath->flightList[i]->arcInfo.flightID<<" ";
                }
            }
            cout<<endl;
            cout<<endl;
        }
        else//路径不存在
        {
            cout<<"no choice"<<endl;
        }
    }
}
