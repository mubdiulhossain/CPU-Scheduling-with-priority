/**
Name: Hossain, Mohammad Mubdiul
ID: 1161303847
**/

#include "RoundRobin.h"

RoundRobin::RoundRobin():requiredBurstTime(0)
{
    processList.clear();
}
RoundRobin::RoundRobin(const vector<Process> &listProcess):requiredBurstTime(0)
{
    processList = listProcess;
    for(int i = 0; i < listProcess.size();i++)
    {
        requiredBurstTime = requiredBurstTime + processList[i].getBurstTime();
    }
}
RoundRobin::~RoundRobin()
{

}
void RoundRobin::addProccesByPriority(vector<Process> &listProcess, const Process &p)
{
    if(listProcess.size() == 0)
    {
        listProcess.push_back(p);
        return;
    }
    else
    {
        for(int i = 0; i < listProcess.size(); i++)
        {
            if(p.getPriority() < listProcess[i].getPriority())
            {
                listProcess.insert(listProcess.begin()+i,p);
                return;
            }
        }
    }
    listProcess.push_back(p);
}
void RoundRobin::setProccessSchedule(vector<pair<Process,int> > &schedule, const Process &p)
{
    if(schedule.size() == 0)
    {
        schedule.push_back(make_pair(p,1));
    }
    else
    {
        if(schedule[schedule.size()-1].first.getId() == p.getId())
        {
            schedule[schedule.size()-1].second++;
        }
        else
        {
            schedule.push_back(make_pair(p,1));
        }
    }
}
void RoundRobin::setProccessSchedule(vector<pair<Process,int> > &schedule, const Process &p, int runTime)
{
    if(schedule.size() == 0)
    {
        schedule.push_back(make_pair(p,runTime));
    }
    else
    {
        if(schedule[schedule.size()-1].first.getId() == p.getId())
        {
            schedule[schedule.size()-1].second = schedule[schedule.size()-1].second + runTime;
        }
        else
        {
            schedule.push_back(make_pair(p,runTime));
        }
    }
}
void RoundRobin::displayProcessTable(const vector<Process> &listProcess)
{
    double sumTurnAround = 0;
    double sumWaitingTime = 0;
    cout<< "RR output"<<endl;
    cout << "| " << "Name" << " | " << "Arrival Time" << " | " << "Burst Time" << " | " << "Priority" << " | " << "Finished Time" << " | " << "Turn Around Time" << " | " << "Waiting Time" << " | " << endl;

    for(int i = 0; i < listProcess.size(); i++)
    {
        cout << "| " << setw(4);
        cout << listProcess[i].getId();
        cout << " | " << setw(12) << listProcess[i].getArrivalTime()<< " | " << setw(10) << listProcess[i].getBurstTime() << " | " << setw(8) << listProcess[i].getPriority()
        << " | " << setw(13) << listProcess[i].getEndTime() << " | " << setw(16) << listProcess[i].getTurnAroundTime() << " | " << setw(12) << listProcess[i].getWaitingTime()<<  " | " << endl;
        sumTurnAround = sumTurnAround + listProcess[i].getTurnAroundTime();
        sumWaitingTime = sumWaitingTime + listProcess[i].getWaitingTime();
    }
    cout << endl;
    cout << "Average Turn Around Time : " << sumTurnAround / listProcess.size() << endl;
    cout << "Average Waiting Time     : " << sumWaitingTime / listProcess.size() << endl;
    return;
}
void RoundRobin::display()
{
    int timer = 0;
    cout<<"Gantt Chart: "<<endl;
    cout << "|0|";
    for (int i = 0; i < displayProcesses.size(); i++)
    {
        cout << "--" << displayProcesses[i].first.getId() << "--";
        timer = timer + displayProcesses[i].second;
        cout << "|" << timer << "|";
    }
    cout << endl << endl;
    displayProcessTable(recordedProcess);
}
void RoundRobin::addProccesByID(vector<Process> &listProcess, const Process &p)
{
    if(listProcess.size() == 0)
    {
        listProcess.push_back(p);
        return;
    }
    else
    {
        for(int i = 0; i < listProcess.size(); i++)
        {
            while(p.getId().length() > listProcess[i].getId().length())
            {
                i++;
                if(i == listProcess.size())
                {
                    listProcess.push_back(p);
                    return;
                }
            }
            if(p.getId() < listProcess[i].getId())
            {
                listProcess.insert(listProcess.begin()+i,p);
                return;
            }
        }
    }
    listProcess.push_back(p);
}
void RoundRobin::calculateRoundRobin(int quantum)
{
    int timer = 0;
    int totalRunTime = 0;

    vector<Process> newProccess = processList;
    vector<Process> running;

    Process next;
    Process buffer;
    recordedProcess.clear();

    while(totalRunTime < requiredBurstTime)
    {
        int counter = 0;
        while (counter < newProccess.size())
        {
            if(newProccess[counter].getArrivalTime() == timer)
            {
                addProccesByPriority(running,newProccess[counter]);
                newProccess.erase(newProccess.begin() + counter);
                counter--;
            }
            counter++;
        }
        if(buffer.getActive() == true)
        {
            addProccesByPriority(running,buffer);
            buffer = Process (); //reset
        }
        if(running.size() == 0 && next.getActive() == false)
        {
            setProccessSchedule(displayProcesses,Process());
        }
        else
        {
            if(next.getActive() == false)
            {
                next = running[0];
                running.erase(running.begin());
            }
            next.runProcess(1,timer+1);
            setProccessSchedule(displayProcesses,next);
            totalRunTime++;

            if(next.getBalanceTime() == 0)
            {
                addProccesByID(recordedProcess,next);
                next = Process();
            }
            else if(next.getTotalRunTime() != 0 && next.getTotalRunTime()%quantum == 0)
            {
                buffer = next;

                if (running.size() != 0)
                {
                    next = running[0];
                    running.erase(running.begin());
                }
                else
                {
                    next = Process();
                }
            }
        }
        timer++;
    }
}












