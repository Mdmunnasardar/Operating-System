#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    string pid;
    int at, bt, ct, wt, tat;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = "P" + to_string(i + 1);
        cout << "Arrival Time for " << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Burst Time for " << p[i].pid << ": ";
        cin >> p[i].bt;
    }

    int q;
    cout << "Enter Time Quantum: ";
    cin >> q;

    // Sort by arrival time
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    vector<int> rem_bt(n);
    for (int i = 0; i < n; i++)
        rem_bt[i] = p[i].bt;

    queue<int> ready;
    int time = p[0].at;
    int i = 1;

    ready.push(0);

    cout << "\nGantt Chart:\n";

    while (!ready.empty()) {
        int idx = ready.front();
        ready.pop();

        int exec = min(q, rem_bt[idx]);

        cout << "| " << p[idx].pid << " ";

        time += exec;
        rem_bt[idx] -= exec;

        // Add newly arrived processes
        while (i < n && p[i].at <= time) {
            ready.push(i);
            i++;
        }

        // If process not finished, push back
        if (rem_bt[idx] > 0) {
            ready.push(idx);
        } else {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    cout << "|\n";

    float total_wt = 0, total_tat = 0;

    cout << "\nPID\tAT\tBT\tWT\tTAT\n";
    for (auto proc : p) {
        cout << proc.pid << "\t" << proc.at << "\t" << proc.bt << "\t"
             << proc.wt << "\t" << proc.tat << endl;

        total_wt += proc.wt;
        total_tat += proc.tat;
    }

    cout << "\nAverage WT: " << total_wt / n;
    cout << "\nAverage TAT: " << total_tat / n << endl;

    return 0;
}