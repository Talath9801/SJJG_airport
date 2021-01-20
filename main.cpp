#include <iostream>
#include <fstream> //定义读写已命名文件的类型
#include <vector>
#include <sstream> //多定义的类型则用于读写存储在内存中的string对象
#include <adjlist.h>
using namespace std;

int main()
{
    //读文件C:\Users\lenovo\Desktop
    ifstream inFile("C:\\Users\\lenovo\\Desktop\\data.csv",ios::in);//inFile来自fstream,ifstream为输入文件流(从文件读入)
    string lineStr;
    vector<vector<string>> strArray;
    while(getline(inFile,lineStr)) //getline来自sstream
    {
        //存成二维表结构
        stringstream ss(lineStr);//来自sstream
        string str;
        vector<string> lineArray;
        //按照逗号分隔
        while(getline(ss,str,','))
        {
            lineArray.push_back(str);//一行数据以vector保存
        }
        strArray.push_back(lineArray);//每一行vector数据都放到strArray中去
    }

    AdjList mylist;
    CreateAdjList(mylist,strArray);//构建邻接表

    int adjMatrix[VEX_NUM][VEX_NUM];
    list2Mat(mylist,adjMatrix);
        //printMat(adjMatrix);

    int mode;
    cout<<"choose the operation: "<<endl;
    cout<<"1 for DFS/BFS travers"<<endl;
    cout<<"2 for adjmatrix"<<endl;
    cout<<"4 for 0 or 1 transition"<<endl;
    cout<<"5 for between 2 airport, all possible flight with no limit"<<endl;
    cout<<"6 for between 2 airport, all possible flight with limitation"<<endl;
    cin>>mode;
    while(mode)
    {
        if(mode==1)
        {
            int n1;
            int temp;
            cout<<"input one airport number, then input a number, 1 for DFS, 2 for BFS"<<endl;
            cin>>n1>>temp;
            if(n1>79||n1<1)
            {
                cout<<"airport do not exist"<<endl;
                cout<<"************************************************"<<endl;
                cout<<"input mode"<<endl;
                cin>>mode;
                continue;
            }
            if(temp==1)
            {
                DFStraverse_Time(mylist,n1-1,printArc);
            }
            else if(temp==2)
            {
                BFStraverse_Time(mylist,n1-1,printArc);
            }
            else
            {
                cout<<"input error"<<endl;
            }
            cout<<"************************************************"<<endl;
            cout<<"input mode"<<endl;
            cin>>mode;
            continue;
        }
        else if(mode==2)
        {
            cout<<"input x1,x2, meaning from airport x1 to airport x2"<<endl;
            cout<<"to see if can be reached directly/ with 1 transfer/ 2 transfter"<<endl;
            int i,j;
            cin>>i>>j;
            int t=adjMatrix[i-1][j-1];
            if(t==-1)
                cout<<"cannot reach"<<endl;
            else if(t==0)
                cout<<"directly"<<endl;
            else if(t==1)
                cout<<"with 1 transfer"<<endl;
            else if(t==2)
                cout<<"with 2 transfer"<<endl;

            cout<<"************************************************"<<endl;
            cout<<"input mode"<<endl;
            cin>>mode;
            continue;
        }
        else if(mode==4)//直飞或一次中转
        {
            cout<<"input 2 airport"<<endl;
            int n1,n2;
            cin>>n1>>n2;
            if(adjMatrix[n1-1][n2-1]==0)
            {
                limitDirect(mylist,n1-1,n2-1);
                limitOneTrans(mylist,adjMatrix,n1-1,n2-1);
            }
            else if(adjMatrix[n1-1][n2-1]==1)
            {
                limitOneTrans(mylist,adjMatrix,n1-1,n2-1);
            }
            else cout<<"cannot reach within limit"<<endl;
            cout<<"************************************************"<<endl;
            cout<<"input mode"<<endl;
            cin>>mode;
            continue;
        }
        else if(mode==5)
        {
            cout<<"input 2 airport"<<endl;
            int n1,n2;
            cin>>n1>>n2;
            fromTo(mylist,adjMatrix,n1-1,n2-1);
            cout<<"************************************************"<<endl;
            cout<<"input mode"<<endl;
            cin>>mode;
            continue;
        }
        else if(mode==6)//有限制的所有备选航线
        {
            cout<<"input 2 airport"<<endl;
            int n1,n2;
            cin>>n1>>n2;
            int hour1,min1,hour2,min2,hour3,min3,hour4,min4;
            char model;
            cout<<"input the limit: depart time range, arrive time range, planeModel"<<endl;
            cout<<"for example 8:00~12:00  15:00~20:00  1"<<endl;
            char ch;

            cin>>hour1>>ch>>min1>>ch>>hour2>>ch>>min2;
            cin>>hour3>>ch>>min3>>ch>>hour4>>ch>>min4;
            cin>>model;

            con_fromTo(mylist,adjMatrix,n1-1,n2-1,hour1,min1,hour2,min2,hour3,min3,hour4,min4,model);

            cout<<"************************************************"<<endl;
            cout<<"input mode"<<endl;
            cin>>mode;
            continue;
        }
        else
        {
            cout<<"input error"<<endl;

            cout<<"input mode"<<endl;
            cin>>mode;
            continue;
        }
    }



}
