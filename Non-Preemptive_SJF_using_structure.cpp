#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define db double

struct process
{
    int id, bt, ct, tat, wt, rt;
};
vector<process> processes;
bool sortBurstTime(process a, process b)
{
    return a.bt < b.bt;
}

void inputView()
{
    cout << "Process\t Burst_time(BT)" << endl;
    for (auto p : processes)
    {
        cout << "P" << p.id << "\t\t" << p.bt << endl;
    }
}
int main()
{
    cout << "Enter the total number of processes: ";
    int n;
    cin >> n;
    cout << "Enter burst time: ";
    for (int i = 0; i < n; i++)
    {
        process p;
        p.id = i + 1;
        cin >> p.bt;
        processes.push_back(p);
    }
    cout << "Input View:" << endl;
    inputView();
    sort(processes.begin(), processes.end(), sortBurstTime);
    cout << endl
         << "Input View after sort:" << endl;
    inputView();

    // Calculations
    processes[0].ct = processes[0].bt;
    processes[0].rt = 0;
    for (int i = 0; i < processes.size(); i++)
    {
        processes[i + 1].ct = processes[i].ct + processes[i + 1].bt;
        processes[i].tat = processes[i].ct;
        processes[i].wt = processes[i].tat - processes[i].bt;
        processes[i + 1].rt = processes[i].ct;
    }
    // Gantt Chart
    cout << "\n\t Gantt Chart:\n\n";
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "--------";
    }
    cout << endl;
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "|  P" << processes[i].id << "   ";
    }
    cout << "|" << endl;
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "--------";
    }
    cout << endl;
    cout << 0 << "\t";
    for (int i = 0; i < processes.size(); i++)
    {
        cout << processes[i].ct << "\t";
    }
    // output
    cout << "\n|t Final Result\n";
    cout << "\nProcess\t Burst_Time(BT)\t Completion_Time(CT)\tTurn_Around_Time(TAT)\tWaiting_Time(WT)\tResponse_Time(RT)\n";
    for (auto p : processes)
    {
        cout << "P" << p.id << "\t\t" << p.bt << "\t\t" << p.ct << "\t\t\t" << p.tat << "\t\t\t" << p.wt << "\t\t\t" << p.rt << endl;
    }
    // Average waiting time
    db avg_wt = 0;
    for (auto p : processes)
    {
        avg_wt += p.wt;
    }
    avg_wt /= processes.size();
    cout << "\nAverage Waiting Time: " << avg_wt << endl;
    return 0;
}