#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include <String>

using namespace std;

class Process{
    private:
        string id;
        int arrivalTime;
        int burstTime;
        int priority;
        int totalRunTime;
        int endTime;
        bool active;
    public:
        Process();
        Process(string id, int arrivalTime,int burstTime,int priority);
        Process(const Process &p);
        void setArrivalTime(int arrivalTime);
        void setBurstTime(int burstTime);
        void setPriority(int priority);
        void setActive(bool active);
        void runProcess(int runTime, int currentTime);

        string getId() const;
        int getArrivalTime() const;
        int getBurstTime() const;
        int getPriority() const;
        int getTotalRunTime() const;
        int getBalanceTime() const;
        int getEndTime() const;
        bool getActive() const;
        int getWaitingTime() const;
        int getTurnAroundTime() const;
};
#endif // PROCESS_H

//turn around = end time - arrival time
//end time = arrival time + turn around
//waiting time = turn around - burst time = end time - arrival time - burst time;
