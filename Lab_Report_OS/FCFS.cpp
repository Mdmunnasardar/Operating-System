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

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = "P" + to_string(i + 1);
        cout << "Arrival Time for " << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Burst Time for " << p[i].pid << ": ";
        cin >> p[i].bt;
    }

    // Sort by arrival time
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    int time = 0;

    // Execution
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
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