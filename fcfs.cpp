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
    vector<int> timeline;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        timeline.push_back(time);

        time += p[i].bt;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    timeline.push_back(time);

    cout << "\nGantt Chart:\n";

    for (int i = 0; i < n; i++) {
        cout << "--------";
    }
    cout << "-\n";

    for (int i = 0; i < n; i++) {
        cout << "|  " << p[i].pid << "  ";
    }
    cout << "|\n";

    for (int i = 0; i < n; i++) {
        cout << "--------";
    }
    cout << "-\n";

    for (int i = 0; i <= n; i++) {
        cout << timeline[i] << "\t";
    }
    cout << endl;

    float total_wt = 0, total_tat = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "----------------------------------------\n";

    for (auto proc : p) {
        cout << proc.pid << "\t"
             << proc.at << "\t"
             << proc.bt << "\t"
             << proc.ct << "\t"
             << proc.tat << "\t"
             << proc.wt << endl;

        total_wt += proc.wt;
        total_tat += proc.tat;
    }

    cout << "\nAverage WT: " << total_wt / n;
    cout << "\nAverage TAT: " << total_tat / n << endl;

    return 0;
}