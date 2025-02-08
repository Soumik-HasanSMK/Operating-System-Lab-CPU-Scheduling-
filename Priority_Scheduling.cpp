#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define db double

struct process
{
    int at, bt, priority, ct, tat, wt, rt;
    string p;
};

vector<process> processes;
bool compare(process p1, process p2)
{
    return p1.priority < p2.priority;
}

void inputView()
{
    cout << "Process    Arrival_Time    Burst_Time    Priority" << endl;
    for (int i = 0; i < processes.size(); i++)
    {
        cout << processes[i].p << "\t\t" << processes[i].at << "\t\t" << processes[i].bt << "\t    " << processes[i].priority << endl;
    }
}
int main()
{
    cout << "Enter the total number of processes: ";
    int n;
    cin >> n;
    processes.resize(n);
    cout << "Enter process(string), arrival time, burst time & priority" << endl;
    int mn = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        cin >> processes[i].p >> processes[i].at >> processes[i].bt >> processes[i].priority;
    }
    // input view
    cout << "\nInput view\n\n";
    inputView();

    for (int i = 0; i < n; i++)
    {
        if (mn > processes[i].at)
        {
            mn = processes[i].at;
            processes[0].p = processes[i].p;
            processes[0].at = processes[i].at;
            processes[0].bt = processes[i].bt;
            processes[0].priority = processes[i].priority;
        }
    }
    sort(processes.begin() + 1, processes.end(), compare);

    // calculations
    processes[0].ct = processes[0].at + processes[0].bt;
    processes[0].rt = 0;
    for (int i = 0; i < processes.size(); i++)
    {
        processes[i + 1].ct = processes[i].ct + processes[i + 1].bt;
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        processes[i + 1].rt = processes[i].ct - processes[i + 1].at;
    }

    // Gantt Chart
    cout << "\n\t Gantt Chart\n";
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "--------";
    }
    cout << endl;
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "|  " << processes[i].p << "   ";
    }
    cout << "|" << endl;
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "--------";
    }
    cout << endl;
    cout << processes[0].at;
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "\t" << processes[i].ct;
    }

    cout << endl;

    // Final output
    cout << "\n\t Final Result\n";
    cout << "\nProcess\t AT\t BT\t Priority\t CT\t TAT\t WT\t RT\n";
    for (auto p : processes)
    {
        cout << p.p << "\t " << p.at << "\t " << p.bt << "\t  " << p.priority << "\t\t " << p.ct << "\t " << p.tat << "\t " << p.wt << "\t " << p.rt << endl;
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