#include <adjlist.h>
#define depthLimit
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

ArcNode* firstAdjArc_Time(AdjList adjlist, ArcNode *cur_arc)
//返回由当前弧的弧尾发出的第一条可以构成转机的弧，如果不存在，返回空指针
{
    ArcNode *p;
    //int v=cur_arc->arcInfo.ArriAirport-1;//上一班飞机目标机场的存储位置
    int v=cur_arc->adjvex;
    // cout<<v<<endl;
#define debug1
#ifndef debug1
    //调试段错误
    cout<<v<<endl;
    if(v<0||v>78)//v溢出
    {
        cout<<cur_arc->arcInfo.flightID;
        cout<<"error"<<endl;
    }
#endif
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

ArcNode* nextAdjArc_Time(AdjList adjlist,ArcNode *vvv,ArcNode *w)
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

void BFStraverse_Time(AdjList adjlist, int v,int(*visit)(ArcNode* arc))
//从存储位置为v的机场出发，广度优先遍历，非递归，限制最多两次中转
{
    cout<<"begin BFS"<<endl;

#ifndef depthLimit
    int depthlimit=9;
    int count=0;
#endif
    queue<ArcNode> myqueue;
    queue<int> depthQueue;//平行操作一个队列，记录结点深度
    //先把起始点后面的弧都压到队列里面
    ArcNode* h;
    h=adjlist[v].firstArc;
    while(h)
    {
        //cout<<h->arcInfo.flightID<<"(->"<<h->arcInfo.ArriAirport<<")"<<" "<<endl;
        visit(h);
        myqueue.push(*h);
        depthQueue.push(1);//起点直接连接的结点深度为1
        h=h->nextarc;
    }


#ifndef depthLimit
    count++;
    if(count>depthlimit)
        exit(1);
#endif

    while(!myqueue.empty())
    {
        //ArcNode *head=&myqueue.front();
        //注：这里不能直接把指针指向队头，否则pop之后会出问题
        ArcNode *head;
        head=(ArcNode*)malloc(sizeof (ArcNode));
        head->adjvex=myqueue.front().adjvex;
        head->nextarc=myqueue.front().nextarc;
        head->arcInfo.airFare=myqueue.front().arcInfo.airFare;
        head->arcInfo.arriDate=myqueue.front().arcInfo.arriDate;
        head->arcInfo.arriHour=myqueue.front().arcInfo.arriHour;
        head->arcInfo.flightID=myqueue.front().arcInfo.flightID;
        head->arcInfo.deparDate=myqueue.front().arcInfo.deparDate;
        head->arcInfo.deparHour=myqueue.front().arcInfo.deparHour;
        head->arcInfo.arriMinute=myqueue.front().arcInfo.arriMinute;
        head->arcInfo.planeModel=myqueue.front().arcInfo.planeModel;
        head->arcInfo.deparMinute=myqueue.front().arcInfo.deparMinute;
        head->arcInfo.deparAirport=myqueue.front().arcInfo.deparAirport;
        head->arcInfo.ArriAirport=myqueue.front().arcInfo.ArriAirport;

        int headDepth;
        headDepth=depthQueue.front();//头结点的深度，下面推进去的结点深度要加一
        if(headDepth>2)
        {
            break;//超过转机两次的限制,2
        }

        myqueue.pop();
        depthQueue.pop();
        for(ArcNode* w=firstAdjArc_Time(adjlist,head);w!=NULL;w=nextAdjArc_Time(adjlist,head,w))
        {
#define debug1
#ifndef debug1
            if(w->arcInfo.deparAirport==39)
            {
                cout<<"debug1"<<endl;
            }
#endif
            //cout<<w->arcInfo.flightID<<"(->"<<w->arcInfo.ArriAirport<<")"<<" "<<endl;
            visit(w);
            myqueue.push(*w);
            depthQueue.push(headDepth+1);
        }
#ifndef depthLimit
        count++;
        if(count>depthlimit)
        {
            cout<<"reach depth limit"<<endl;
            //exit(1);
            break;
        }

#endif


    }
    cout<<"end BFS"<<endl;
}

void DFStraverse_Time(AdjList adjlist, int v,int(*visit)(ArcNode* arc))
//从存储位置为v的机场出发，深度优先遍历，非递归
{
    cout<<"begin DFS"<<endl;

    stack<ArcNode> mystack;
    //先把起始点后面的第一个弧压到栈里面
    ArcNode* h;
    h=adjlist[v].firstArc;
    if(h)
    {
        visit(h);
        mystack.push(*h);
    }
    else
    {
        cout<<"empty head! Error! "<<endl;
    }

    while(!mystack.empty())
    {
        ArcNode *head;
        head=(ArcNode*)malloc(sizeof (ArcNode));
        head->adjvex=mystack.top().adjvex;
        head->nextarc=mystack.top().nextarc;
        head->arcInfo.airFare=mystack.top().arcInfo.airFare;
        head->arcInfo.arriDate=mystack.top().arcInfo.arriDate;
        head->arcInfo.arriHour=mystack.top().arcInfo.arriHour;
        head->arcInfo.flightID=mystack.top().arcInfo.flightID;
        head->arcInfo.deparDate=mystack.top().arcInfo.deparDate;
        head->arcInfo.deparHour=mystack.top().arcInfo.deparHour;
        head->arcInfo.arriMinute=mystack.top().arcInfo.arriMinute;
        head->arcInfo.planeModel=mystack.top().arcInfo.planeModel;
        head->arcInfo.deparMinute=mystack.top().arcInfo.deparMinute;
        head->arcInfo.deparAirport=mystack.top().arcInfo.deparAirport;
        head->arcInfo.ArriAirport=mystack.top().arcInfo.ArriAirport;



        mystack.pop();
        ArcNode* w=firstAdjArc_Time(adjlist,head);

        if(w)
        {
            visit(w);
            mystack.push(*w);
        }

    }
    cout<<"end DFS"<<endl;
}

void BFS_depth(AdjList adjlist, int v,int trans,int canVisit[VEX_NUM])
//从存储位置为v的机场出发，广度优先遍历，非递归，限制最多trans中转
{

    for(int i=0;i<VEX_NUM;i++)
        canVisit[i]=-1;
    queue<ArcNode> myqueue;
    queue<int> depthQueue;//平行操作一个队列，记录结点深度
    //先把起始点后面的弧都压到队列里面
    ArcNode* h;
    h=adjlist[v].firstArc;
    while(h)
    {
        //可以直飞，0次转机
        canVisit[h->adjvex]=0;
        myqueue.push(*h);
        depthQueue.push(1);//起点直接连接的结点深度为1
        h=h->nextarc;
    }

    while(!myqueue.empty())
    {
        //ArcNode *head=&myqueue.front();
        //注：这里不能直接把指针指向队头，否则pop之后会出问题
        ArcNode *head;
        head=(ArcNode*)malloc(sizeof (ArcNode));
        head->adjvex=myqueue.front().adjvex;
        head->nextarc=myqueue.front().nextarc;
        head->arcInfo.airFare=myqueue.front().arcInfo.airFare;
        head->arcInfo.arriDate=myqueue.front().arcInfo.arriDate;
        head->arcInfo.arriHour=myqueue.front().arcInfo.arriHour;
        head->arcInfo.flightID=myqueue.front().arcInfo.flightID;
        head->arcInfo.deparDate=myqueue.front().arcInfo.deparDate;
        head->arcInfo.deparHour=myqueue.front().arcInfo.deparHour;
        head->arcInfo.arriMinute=myqueue.front().arcInfo.arriMinute;
        head->arcInfo.planeModel=myqueue.front().arcInfo.planeModel;
        head->arcInfo.deparMinute=myqueue.front().arcInfo.deparMinute;
        head->arcInfo.deparAirport=myqueue.front().arcInfo.deparAirport;
        head->arcInfo.ArriAirport=myqueue.front().arcInfo.ArriAirport;

        int headDepth;
        headDepth=depthQueue.front();//头结点的深度，下面推进去的结点深度要加一
        if(headDepth>trans)//中转次数
        {
            break;
        }

        myqueue.pop();
        depthQueue.pop();
        for(ArcNode* w=firstAdjArc_Time(adjlist,head);w!=NULL;w=nextAdjArc_Time(adjlist,head,w))
        {
            //visit(w);
            if(canVisit[w->adjvex]==-1)
               canVisit[w->adjvex]=canVisit[head->adjvex]+1;
            myqueue.push(*w);
            depthQueue.push(headDepth+1);
        }

    }
}


void list2Mat(AdjList adjlist, int mat[VEX_NUM][VEX_NUM])
//矩阵初始化为-1
//操作的时候，如果直飞，改成0
//如果一次转机，在还是-1的地方改成1
//如果两次转机，在还是-1的地方改成2
{
    for(int i=0;i<VEX_NUM;i++)
    {
        for(int j=0;j<VEX_NUM;j++)
        {
            mat[i][j]=-1;
        }
    }

    for(int i=0;i<VEX_NUM;i++)
    {
        BFS_depth(adjlist,i,0,mat[i]);
    }
    for(int i=0;i<VEX_NUM;i++)
    {
        BFS_depth(adjlist,i,1,mat[i]);
    }
    for(int i=0;i<VEX_NUM;i++)
    {
        BFS_depth(adjlist,i,2,mat[i]);
    }
}

void printMat(int mat[VEX_NUM][VEX_NUM])
{
    for(int i=0;i<VEX_NUM;i++)
    {
        for(int j=0;j<VEX_NUM;j++)
        {
            if(mat[i][j]>=0)
            cout<<mat[i][j];
            else {
                cout<<" ";
            }
        }
        cout<<endl;
    }
}
