#include "process.h"
#include <sstream>

//default constructor
Process::Process()
:id(" "),arrivalTime(0),burstTime(0),priority(0),totalRunTime(0),endTime(0),active(false)
{
}

//overloading default constructor
Process::Process(string id,int arrivalTime,int burstTime,int priority)
:id(id),arrivalTime(arrivalTime),burstTime(burstTime),priority(priority),totalRunTime(0),endTime(0),active(true)
{
}

//copy constructor
Process::Process(const Process &p)
{
    id = p.id;
    arrivalTime = p.arrivalTime;
    burstTime = p.burstTime;
    priority = p.priority;
    totalRunTime = p.totalRunTime;
    endTime = p.endTime;
    active = p.active;
}

//set arrival time
void Process::setArrivalTime(int arrivalTime)
{
    this->arrivalTime = arrivalTime;
}

//set burst time
void Process::setBurstTime(int burstTime)
{
    this->burstTime = burstTime;
}

//set priority time
void Process::setPriority(int priority)
{
    this->priority = priority;
}

//set run time and finish time
void Process::runProcess(int runTime, int currentTime)
{
    if(runTime > (burstTime - totalRunTime))
    {
        cout << "run time > balance time";
    }
    else
    {
        totalRunTime = totalRunTime + runTime;
        //set end time if process complete
        if (totalRunTime == burstTime)
        {
            endTime = currentTime;
        }
    }
}

//set active
void Process::setActive(bool active)
{
    this->active = active;
}

//get id
string Process::getId() const
{
    return id;
}

//get arrival time
int Process::getArrivalTime() const
{
    return arrivalTime;
}

//get burst time
int Process::getBurstTime() const
{
    return burstTime;
}

//get priority
int Process::getPriority() const
{
    return priority;
}

//get total run time
int Process::getTotalRunTime() const
{
    return totalRunTime;
}

//get balance time
int Process::getBalanceTime() const
{
    return (burstTime - totalRunTime);
}

//get end time
int Process::getEndTime() const
{
    if(endTime == 0)
    {
        cout << "Error end time. Process not complete";
    }
    else
    {
        return endTime;
    }
}

bool Process::getActive() const
{
    return active;
}

int Process::getWaitingTime() const
{
    if(endTime == 0)
    {
        cout << "Error waiting time. Process not complete";
    }
    else
    {
        return (endTime - burstTime - arrivalTime);
    }
}

 int Process::getTurnAroundTime() const
 {
    if(endTime == 0)
    {
        cout << "Error turn around time. Process not complete";
    }
    else
    {
        return (endTime - arrivalTime);
    }
}
