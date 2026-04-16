#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process
{
    string pid;
    int at, bt, rt, ct, tat, wt;
};

int main()
{
    int n, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Time Quantum: ";
    cin >> tq;

    vector<Process> p(n);
    // here input process start
    for (int i = 0; i < n; i++)
    {
        p[i].pid = "P" + to_string(i + 1);
        cout << "Arrival Time for " << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Burst Time for " << p[i].pid << ": ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt;
    }

    queue<int> q;
    vector<int> order, timeline;

    int time = 0, completed = 0, i = 0;

    vector<int> idx(n);
    for (int j = 0; j < n; j++)
        idx[j] = j;

    for (int a = 0; a < n; a++)
    {
        for (int b = a + 1; b < n; b++)
        {
            if (p[a].at > p[b].at)
            {
                swap(p[a], p[b]);
            }
        }
    }
    
    q.push(0);
    time = p[0].at;
    i = 1;
    // round robin excution loop
    while (!q.empty())
    {
        int id = q.front();
        q.pop();

        order.push_back(id);
        timeline.push_back(time);

        int exec = min(tq, p[id].rt);
        time += exec;
        p[id].rt -= exec;

        for (int j = 0; j < n; j++)
        {
            if (p[j].at <= time && p[j].rt > 0)
            {
                bool already = false;
                queue<int> temp = q;
                while (!temp.empty())
                {
                    if (temp.front() == j)
                        already = true;
                    temp.pop();
                }
                if (!already && j != id && p[j].rt > 0)
                    q.push(j);
            }
        }

        if (p[id].rt > 0)
        {
            q.push(id);
        }
        else
        {
            p[id].ct = time;
            completed++;
        }

        if (q.empty())
        {
            for (int j = 0; j < n; j++)
            {
                if (p[j].rt > 0)
                {
                    q.push(j);
                    time = max(time, p[j].at);
                    break;
                }
            }
        }
    }

    timeline.push_back(time);

    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    // gantt chart excutiom
    cout << "\nGantt Chart:\n";
    cout << "-------------------------------------------------\n";

    for (int id : order)
        cout << "| " << p[id].pid << " ";

    cout << "|\n-------------------------------------------------\n";

    for (int t : timeline)
        cout << t << "    ";

    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "----------------------------------------\n";

    float total_wt = 0, total_tat = 0;

    for (auto &x : p)
    {
        cout << x.pid << "\t"
             << x.at << "\t"
             << x.bt << "\t"
             << x.ct << "\t"
             << x.tat << "\t"
             << x.wt << "\n";

        total_wt += x.wt;
        total_tat += x.tat;
    }
    // average calculation
    cout << "\nAverage WT: " << total_wt / n;
    cout << "\nAverage TAT: " << total_tat / n << endl;

    return 0;
}