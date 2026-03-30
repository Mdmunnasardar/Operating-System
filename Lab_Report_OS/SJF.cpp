#include <iostream>
#include <vector>
using namespace std;

struct Process {
    string pid;
    int at, bt, ct, wt, tat;
    bool done = false;
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

    int time = 0, completed = 0;

    // Execution loop
    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].done && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        p[idx].done = true;
        completed++;
    }

    // Output Table
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "----------------------------------------\n";

    float totalWT = 0, totalTAT = 0;

    for (auto x : p) {
        cout << x.pid << "\t"
             << x.at << "\t"
             << x.bt << "\t"
             << x.ct << "\t"
             << x.tat << "\t"
             << x.wt << endl;

        totalWT += x.wt;
        totalTAT += x.tat;
    }

    cout << "\nAverage WT: " << totalWT / n;
    cout << "\nAverage TAT: " << totalTAT / n << endl;

    return 0;
}