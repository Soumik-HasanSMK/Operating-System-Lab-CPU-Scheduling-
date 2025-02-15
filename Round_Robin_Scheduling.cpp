#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int id, AT, BT, remaining_time;
    int CT, TAT, WT, RT;
};

vector<Process> processes;
vector<pair<int, int>> gantt_chart;

void ganttChart()
{
    cout << "\nGantt Chart:\n";
    int timeline = 0;
    for (int i = 0; i < gantt_chart.size(); i++)
    {
        cout << "--------";
    }
    cout << endl;

    for (auto g : gantt_chart)
    {
        cout << "|  P" << g.first << "   ";
    }
    cout << "|" << endl;
    for (int i = 0; i < gantt_chart.size(); i++)
    {
        cout << "--------";
    }
    cout << endl;
    cout << timeline;
    for (auto g : gantt_chart)
    {
        cout << "\t" << (timeline + g.second);
        timeline += g.second;
    }
    cout << "\n";
}

void inputView()
{
    cout << "\nInput view" << endl;
    cout << "Process    Arrival_Time    Burst_Time" << endl;
    for (auto &proc : processes)
    {
        cout << "  P" << proc.id << "\t\t" << proc.AT << "\t\t" << proc.BT << endl;
    }
}

int main()
{
    cout << "Enter the number of processes: ";
    int n, quantum;
    cin >> n;
    processes.resize(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cin >> processes[i].AT >> processes[i].BT;
        processes[i].remaining_time = processes[i].BT;
    }
    cout << "Enter Time Quantum: ";
    cin >> quantum;

    inputView();
    sort(processes.begin(), processes.end(), [](Process a, Process b)
         { return a.AT < b.AT; });
    sort(processes.begin() + 1, processes.end(), [](Process a, Process b)
         { return a.id < b.id; });

    queue<int> readyQueue;
    int time = 0, completed = 0;
    vector<bool> visited(n, false);
    int prev_process = -1, start_time = 0;

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && processes[i].AT <= time)
            {
                readyQueue.push(i);
                visited[i] = true;
            }
        }

        if (!readyQueue.empty())
        {
            int idx = readyQueue.front();
            readyQueue.pop();
            if (prev_process != processes[idx].id)
            {
                if (prev_process != -1)
                    gantt_chart.push_back({prev_process, time - start_time});
                start_time = time;
                prev_process = processes[idx].id;
            }

            if (processes[idx].remaining_time == processes[idx].BT)
                processes[idx].RT = time - processes[idx].AT;

            int exec_time = min(quantum, processes[idx].remaining_time);
            processes[idx].remaining_time -= exec_time;
            time += exec_time;

            for (int i = 0; i < n; i++)
            {
                if (!visited[i] && processes[i].AT <= time)
                {
                    readyQueue.push(i);
                    visited[i] = true;
                }
            }

            if (processes[idx].remaining_time > 0)
                readyQueue.push(idx);
            else
            {
                completed++;
                processes[idx].CT = time;
                processes[idx].TAT = processes[idx].CT - processes[idx].AT;
                processes[idx].WT = processes[idx].TAT - processes[idx].BT;
            }
        }
        else
        {
            if (prev_process != -1)
                gantt_chart.push_back({prev_process, time - start_time});
            prev_process = -1;
            time++;
        }
    }

    if (prev_process != -1)
        gantt_chart.push_back({prev_process, time - start_time});

    ganttChart();

    cout << "\nFinal result\n";
    cout << "Process    AT\t BT\t CT\t TAT\t WT\t RT\n";
    double total_tat = 0, total_wt = 0, total_rt = 0;
    for (auto p : processes)
    {
        cout << "  P" << p.id << "       " << p.AT << "\t " << p.BT << "\t " << p.CT << "\t " << p.TAT << "\t " << p.WT << "\t " << p.RT << "\n";
        total_tat += p.TAT;
        total_wt += p.WT;
        total_rt += p.RT;
    }

    cout << "\nAverage Turnaround Time: " << (total_tat / n);
    cout << "\nAverage Waiting Time: " << (total_wt / n);
    cout << "\nAverage Response Time: " << (total_rt / n) << endl;

    return 0;
}
