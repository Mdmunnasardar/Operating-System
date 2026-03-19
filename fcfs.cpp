#include <iostream>
#include <vector>
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

    for (int i = 0; i < n; i++) {
        p[i].pid = "P" + to_string(i + 1);
        cout << "Arrival Time for " << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Burst Time for " << p[i].pid << ": ";
        cin >> p[i].bt;
    }

    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    int time = 0;

    cout << "\nGantt Chart:\n";
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        cout << "| " << p[i].pid << " ";
        time += p[i].bt;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
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