/**
Name: Hossain, Mohammad Mubdiul
ID: 1161303847
**/

#include "ThreeLevelQueue.h"

ThreeLevelQueue::ThreeLevelQueue():requiredBurstTime(0)
{
    processList.clear();
}
ThreeLevelQueue::ThreeLevelQueue(const vector<Process> &listProcess):requiredBurstTime(0)
{
    processList = listProcess;
    for(int i = 0; i < listProcess.size();i++)
    {
        requiredBurstTime = requiredBurstTime + processList[i].getBurstTime();
    }
}
ThreeLevelQueue::~ThreeLevelQueue()
{
    //dtor
}
void ThreeLevelQueue::addProcessByArrival(vector<Process> &listProcess, const Process &p)
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
            if(p.getArrivalTime() < listProcess[i].getArrivalTime())
            {
                listProcess.insert(listProcess.begin()+i,p);
                return;
            }
        }
    }
    listProcess.push_back(p);
}

void ThreeLevelQueue::setProccessSchedule(vector<pair<Process,int> > &schedule, const Process &p)
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
void ThreeLevelQueue::setProccessSchedule(vector<pair<Process,int> > &schedule, const Process &p, int runTime)
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
void ThreeLevelQueue::addProccesByID(vector<Process> &listProcess, const Process &p)
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
void ThreeLevelQueue::calculateThreeLevelQueue(int quantum)
{
    int timer = 0;
    int totalRunTime = 0;

    vector<Process> newQueue = processList;
    vector<Process> queueOne;
    vector<Process> queueTwo;
    vector<Process> queueThree;

    Process buffer1;
    recordSchedule.clear();

    while(totalRunTime < requiredBurstTime)
    {
        int counter = 0;
        while (counter < newQueue.size())
        {
            if(newQueue[counter].getArrivalTime() == timer)
            {
                if(newQueue[counter].getPriority() == 1 || newQueue[counter].getPriority() == 2)
                {
                    addProcessByArrival(queueOne,newQueue[counter]);
                }
                else if(newQueue[counter].getPriority() == 3 || newQueue[counter].getPriority() == 4)
                {
                    addProcessByArrival(queueTwo,newQueue[counter]);
                }
                else
                {
                    addProcessByArrival(queueThree,newQueue[counter]);
                }
                newQueue.erase(newQueue.begin() + counter);
                counter--;
            }
            counter++;
        }
        if(buffer1.getActive() == true)
        {
            queueOne.push_back(buffer1);
            //addProcessToEnd(queueOne,buffer1);
            buffer1 = Process(); //reset
        }
        if(queueOne.size() == 0 && queueTwo.size() == 0 &&  queueThree.size() == 0)
        {
            if(queueOne.size() == 0)
            {
                setProccessSchedule(displayProcessSchedule,Process());
            }
            else
            {
                if(queueTwo.size() == 0)
                {
                    setProccessSchedule(displayProcessSchedule,Process());
                }
                else
                {
                    if(queueThree.size() == 0)
                    {
                        setProccessSchedule(displayProcessSchedule,Process());
                    }
                }
            }
        }
        else
        {
            if(queueOne.size() != 0)
            {
                queueOne[0].runProcess(1,timer+1);
                setProccessSchedule(displayProcessSchedule,queueOne[0]);
                if(queueOne[0].getBalanceTime() == 0)
                {
                    addProccesByID(recordSchedule,queueOne[0]);
                    queueOne.erase(queueOne.begin());

                }
                else if(queueOne[0].getTotalRunTime() != 0 && queueOne[0].getTotalRunTime()%quantum == 0)
                {
                    buffer1 = queueOne[0];
                    queueOne.erase(queueOne.begin());
                }
            }
            else if(queueTwo.size() != 0)
            {

                queueTwo[0].runProcess(1,timer+1);
                setProccessSchedule(displayProcessSchedule,queueTwo[0]);

                if(queueTwo[0].getBalanceTime() == 0)
                {
                    addProccesByID(recordSchedule,queueTwo[0]);
                    queueTwo.erase(queueTwo.begin());

                    if(queueTwo.size() == 0 && queueThree.size() != 0)
                    {
                        while(queueThree.size() != 0)
                        {
                            queueTwo.push_back(queueThree[0]);
                            queueThree.erase(queueThree.begin());
                        }
                    }
                }
            }
            else
            {

                while(queueThree.size() != 0)
                {
                    queueTwo.push_back(queueThree[0]);
                    queueThree.erase(queueThree.begin());
                }

                queueTwo[0].runProcess(1,timer+1);
                setProccessSchedule(displayProcessSchedule,queueTwo[0]);

                if(queueTwo[0].getBalanceTime() == 0)
                {
                    addProccesByID(recordSchedule,queueTwo[0]);
                    queueTwo.erase(queueTwo.begin());
                }

            }
            totalRunTime++;
        }
        timer++;
    }
}
void ThreeLevelQueue::displayProcessTable(const vector<Process> &listProcess)
{
    double sumTurnAround = 0;
    double sumWaitingTime = 0;
    cout<< "Three level queue output"<<endl;
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
void ThreeLevelQueue::display()
{
    int timer = displayProcessSchedule[0].first.getArrivalTime();
    cout<<"Gantt Chart: "<<endl;
    cout <<"|"<< timer<<"|";
    for (int i = 0; i < displayProcessSchedule.size(); i++)
    {
        cout << "--" << displayProcessSchedule[i].first.getId() << "--";
        timer = timer + displayProcessSchedule[i].second;
        cout << "|" << timer << "|";
    }
    cout << endl << endl;
    displayProcessTable(recordSchedule);
}
