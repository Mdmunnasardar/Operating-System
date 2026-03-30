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

    //for input
    for (int i = 0; i < n; i++) {
        p[i].pid = "P" + to_string(i + 1);
        cout << "Arrival Time for " << p[i].pid << ": ";
        cin >> p[i].at;
        cout << "Burst Time for " << p[i].pid << ": ";
        cin >> p[i].bt;
    }

    int time = 0, completed = 0;

    vector<string> order;
    vector<int> timeline;

    //here start excution sjf
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

        order.push_back(p[idx].pid);
        timeline.push_back(time);

        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        p[idx].done = true;
        completed++;
    }

    timeline.push_back(time);

    //gantt chart table 
    cout << "\nGantt Chart:\n\n";

    for (int i = 0; i < n; i++) cout << "--------";
    cout << "-\n";

    for (string x : order) {
        cout << "| " << x << " ";
    }
    cout << "|\n";

    for (int i = 0; i < n; i++) cout << "--------";
    cout << "-\n";

    for (int i = 0; i < timeline.size(); i++) {
        cout << timeline[i] << "   ";
    }

    cout << "\n";

    // this table after excution 
    float totalWT = 0, totalTAT = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "--------------------------------\n";

    for (auto &x : p) {
        cout << x.pid << "\t"
             << x.at << "\t"
             << x.bt << "\t"
             << x.ct << "\t"
             << x.tat << "\t"
             << x.wt << "\n";

        totalWT += x.wt;
        totalTAT += x.tat;
    }

    cout << "\nAverage WT: " << totalWT / n;
    cout << "\nAverage TAT: " << totalTAT / n << endl;

    return 0;
}