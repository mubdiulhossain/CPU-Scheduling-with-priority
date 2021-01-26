/**
Name: Hossain, Mohammad Mubdiul
ID: 1161303847
**/

#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H
#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
#include "process.h"

class RoundRobin
{
    private:
        int requiredBurstTime;
        vector<pair<Process,int> > displayProcesses;
        vector<Process> recordedProcess;
        vector<Process> processList;
        void addProccesByPriority(vector<Process> &listProcess, const Process &p);
        void addProccesByID(vector<Process> &listProcess, const Process &p);

    public:
        RoundRobin();
        RoundRobin(const vector<Process> &listProcess);
        virtual ~RoundRobin();
        void calculateRoundRobin(int quantum);
        void setProccessSchedule(vector<pair<Process,int> > &schedule, const Process &p);
        void setProccessSchedule(vector<pair<Process,int> > &schedule, const Process &p, int runTime);
        void displayProcessTable(const vector<Process> &listProcess);
        void display();
};

#endif // ROUNDROBIN_H
