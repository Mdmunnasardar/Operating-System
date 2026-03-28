#include <iostream>
#include <vector>
using namespace std;

struct Process {
    string pid;
    int at, bt, ct, wt, tat;
    bool completed = false;
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

    int time = 0;
    vector<int> timeline;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
        } else {
            timeline.push_back(time);

            time += p[idx].bt;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].completed = true;
            completed++;
        }
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

    for (int i = 0; i < timeline.size(); i++) {
        cout << timeline[i] << "\t";
    }
    cout << endl;

    float total_wt = 0, total_tat = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "----------------------------------------\n";

    for (auto &proc : p) {
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