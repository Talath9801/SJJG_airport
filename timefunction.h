#ifndef TIMEFUNCTION_H
#define TIMEFUNCTION_H

typedef struct Time
{
    char Date;//日
    int Hour;
    int Minute;
};
int cmpTime(char date1,int hour1,int minute1,char date2,int hour2,int minute2);
//如果第一个时间早于第二个时间，返回1，晚于第二个时间返回-1，相同返回0
int cmpTime1(Time t1,Time t2);
int cmpTime2(int hr1,int min1,int hr2,int min2);

#endif // TIMEFUNCTION_H
