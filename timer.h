#ifndef __TIMER__
#define __TIMER__

#include<sys/resource.h>
#include<sys/time.h>

class Timer{
    struct rusage startu;
    struct rusage endu;
    double duration;

  public:
    Timer(){getrusage(RUSAGE_SELF, &startu); }

    void stopTime(){
        getrusage(RUSAGE_SELF, &endu);
        double start_sec = startu.ru_utime.tv_sec;
        start_sec += startu.ru_utime.tv_usec/1000000.0;
        double end_sec = endu.ru_utime.tv_sec;
        end_sec += endu.ru_utime.tv_usec/1000000.0;

        duration = end_sec - start_sec;
    }

    double getTime(){return duration;}
    double split(){stopTime(); return getTime();}
};

#endif
