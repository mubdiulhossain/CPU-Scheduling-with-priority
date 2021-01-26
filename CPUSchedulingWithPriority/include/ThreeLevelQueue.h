/**
Name: Hossain, Mohammad Mubdiul
ID: 1161303847
**/

#ifndef THREELEVELQUEUE_H
#define THREELEVELQUEUE_H
#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
#include "process.h"

class ThreeLevelQueue
{
    private:

        vector<Process> processList;
        int requiredBurstTime;

        vector<Process> recordSchedule;
        vector<pair<Process,int> > displayProcessSchedule;

        void addProcessByArrival(vector<Process> &listProcess, const Process &p);
        void addProccesByPriority(vector<Process> &listProcess, const Process &p);
        void addProccesByID(vector<Process> &listProcess, const Process &p);
    public:
        ThreeLevelQueue();
        ThreeLevelQueue(const vector<Process> &listProcess);
        virtual ~ThreeLevelQueue();
        void calculateThreeLevelQueue(int quantum);
        void setProccessSchedule(vector<pair<Process,int> > &schedule, const Process &p);
        void setProccessSchedule(vector<pair<Process,int> > &schedule, const Process &p, int runTime);
        void displayProcessTable(const vector<Process> &listProcess);
        void display();
};

#endif // THREELEVELQUEUE_H
