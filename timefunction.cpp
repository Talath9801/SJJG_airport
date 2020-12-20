#include <timefunction.h>
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
