/**
Name: Hossain, Mohammad Mubdiul
ID: 1161303847
**/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include "windows.h"
#include "process.h"
#include "RoundRobin.h"
#include "ThreeLevelQueue.h"
using namespace std;
void Roundrobin(vector<Process> &listProcess);
void Threelevelqueue(vector<Process> &listProcess);

void registerProcess(vector<Process> &listProcess);
void displayTable(const vector<Process> &listProcess);
int getInput(string text, int start, int end);
bool checkRange(int input, int start, int end);
string intToString(int i);
int main()
{
    vector<Process> processList;

    Process p0("P0",0,6,3);
    Process p1("P1",1,4,3);
    Process p2("P2",5,6,1);
    Process p3("P3",6,6,1);
    Process p4("P4",7,6,5);
    Process p5("P5",8,6,6);

    processList.push_back(p0);
    processList.push_back(p1);
    processList.push_back(p2);
    processList.push_back(p3);
    processList.push_back(p4);
    processList.push_back(p5);



    string inputString;
    int input;
    do
    {
        cout<<"CPU Scheduling with priority"<<endl<<endl;
        cout << endl;
        cout << "[1] Register Process" << endl;
        cout << "[2] Round Robin Scheduling with Priority" << endl;
        cout << "[3] Three-level Queue Scheduling" << endl;
        cout << "[4] Quit" << endl;
        cout << endl;
        cout << "Enter: ";
        cin >> inputString;
        input = getInput(inputString,1,4);
        cout << endl;

        if(input == 1)
        {
            registerProcess(processList);
            system("CLS");
        }
        else
        {
            if (input == 2)
            {
                Roundrobin(processList);
                system("CLS");
            }
            else
            {
                if (input == 3)
                {
                    Threelevelqueue(processList);
                    system("CLS");
                }
            }
        }
    }while(input != 4);
}
void Roundrobin(vector<Process> &listProcess)
{
    cout << "Round Robin Scheduling with Priority" << endl;
    cout << endl;
    if (listProcess.size() == 0)
    {
        cout << "Register new process" << endl;
        registerProcess(listProcess);
    }
    else
    {
        string sInput;
        int input;

        displayTable(listProcess);
        cout << "[1] Use Existing Processes" << endl;
        cout << "[2] Register New Process" << endl;
        cin >> sInput;
        input = getInput(sInput,1,2);
        if(input == 2)
        {
            cout << "Register new process" << endl;
            registerProcess(listProcess);
        }
    }
    //displayTable(listProcess);
    int quantum;
    cout << "Time quantum: ";
    cin >> quantum;
    RoundRobin r(listProcess);
    //r(listProcess);
    r.calculateRoundRobin(quantum);
    r.display();
    cout << endl;
    system("pause");
}
void Threelevelqueue(vector<Process> &listProcess)
{
    cout << "Three-level Queue Scheduling" << endl;
    cout << endl;
    if (listProcess.size() == 0)
    {
        cout << "Register new processes" << endl;
        registerProcess(listProcess);
    }
    else
    {
        string sInput;
        int input;

        displayTable(listProcess);
        cout << "[1] Use Existing Processes" << endl;
        cout << "[2] Register New Process" << endl;
        cin >> sInput;
        input = getInput(sInput,1,2);

        if(input == 2)
        {
            cout << "Register new processes" << endl;
            registerProcess(listProcess);
        }
    }
    //displayTable(listProcess);
    int quantum;
    cout << "Time quantum: ";
    cin >> quantum;
    ThreeLevelQueue threeLevel(listProcess);
    threeLevel.calculateThreeLevelQueue(quantum);
    threeLevel.display();
    cout << endl;
    system("pause");
}
void displayTable(const vector<Process> &listProcess)
{
    cout << "| " << "PID" << " | " << "Arrival Time" << " | " << "Burst Time" << " | " << "Priority" << " |" << endl;
    for(int i = 0; i < listProcess.size(); i++)
    {
        cout  << "| " << setw(3) << listProcess[i].getId() << " | " << setw(12) << listProcess[i].getArrivalTime() << " | " << setw(10) << listProcess[i].getBurstTime() << " | " << setw(8) << listProcess[i].getPriority() << " |" << endl;
    }
    cout<<endl;
}
int getInput(string text, int start, int end)
{
    int convert = atoi(text.c_str());
    if (convert == 0 || convert < start || convert > end)
    {
        cout << "Error Input! Enter correct number: ";
        cin >> text;
        getInput(text,start,end);
    }
    else
    {
        return convert;
    }
}
void registerProcess(vector<Process> &listProcess)
{
    listProcess.clear();      //clear process list

    string amountInput;
    string id;
    int amount;
    int arrival;
    int burst;
    int priority;

    cout << "Define number of processes (3-10)" << endl;
    cout << "Enter: ";
    cin >> amountInput;
    amount = getInput(amountInput,3,10);
    cout << "Enter information of processes (Arrival_Time, Burst_Time, Priority)" << endl;
    for (unsigned int i = 0; i < amount; i++)
    {
        id = "P" + intToString(i);
        cout << setw(3) << id << ": ";
        cin >> arrival >> burst >> priority;
        while(!checkRange(priority,1,6))
        {
            cout << "Enter Priority Range between 1-6: ";
            cin >> priority;
        }
        listProcess.push_back(Process(id, arrival, burst, priority));
    }
}
string intToString(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}
bool checkRange(int input, int start, int end)
{
    if (input < start || input > end)
    {
        return false;
    }
    return true;
}
