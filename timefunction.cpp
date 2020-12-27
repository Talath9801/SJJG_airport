#include <timefunction.h>
#include <adjlist.h>
int cmpTime(char date1,int hour1,int minute1,char date2,int hour2,int minute2)
//如果第一个时间早于第二个时间，返回1，晚于第二个时间返回-1，相同返回0
{
    if(date1<date2)
        return 1;
    if(date1>date2)
        return -1;
    if(hour1<hour2)
        return 1;
    if(hour1>hour2)
        return -1;
    if(minute1<minute2)
        return 1;
    if(minute1>minute2)
        return -1;
    return 0;
}
int cmpTime1(Time t1,Time t2)
{
    return cmpTime(t1.Date,t1.Hour,t1.Minute,t2.Date,t2.Hour,t2.Minute);
}
int cmpTime2(int hr1,int min1,int hr2,int min2)
{
    if(hr1<hr2)
        return 1;//1早
    if(hr1>hr2)
        return -1;
    if(min1<min2)
        return 1;
    if(min1>min2)
        return -1;
    return 0;
}
int timeSpan(ArcNode *depar,ArcNode *arri)
{
    int day,hour,min;
    int totalMin;//总共的分钟数
    day=arri->arcInfo.arriDate-depar->arcInfo.deparDate;
    hour=arri->arcInfo.arriHour-depar->arcInfo.deparHour;
    min=arri->arcInfo.arriMinute-depar->arcInfo.deparMinute;

    totalMin=24*60*day+60*hour+min;
}
