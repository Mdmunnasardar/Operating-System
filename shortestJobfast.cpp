#include <iostream>
#include <vector>
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
    vector<bool> done(n, false);

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = "P" + to_string(i + 1);
        cout << "Arrival Time for " << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Burst Time for " << p[i].pid << ": ";
        cin >> p[i].bt;
    }

    int time = 0, completed = 0;

    cout << "\nGantt Chart:\n";

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        // Find shortest job among arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !done[i]) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        // If no process is ready
        if (idx == -1) {
            time++;
            continue;
        }

        cout << "| " << p[idx].pid << " ";

        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        done[idx] = true;
        completed++;
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