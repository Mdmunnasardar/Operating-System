#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    string pid;
    int at, bt, rt, ct, tat, wt;
};

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Time Quantum: ";
    cin >> tq;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].pid = "P" + to_string(i + 1);
        cin >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
    }

    queue<int> q;
    vector<int> gantt, timeLine;

    int time = 0, i = 0, completed = 0;

    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return p[a].at < p[b].at;
    });

    q.push(idx[0]);
    time = p[idx[0]].at;
    i = 1;

    while (!q.empty()) {
        int id = q.front();
        q.pop();

        gantt.push_back(id);
        timeLine.push_back(time);

        int exec = min(tq, p[id].rt);
        time += exec;
        p[id].rt -= exec;

        while (i < n && p[idx[i]].at <= time) {
            q.push(idx[i]);
            i++;
        }

        if (p[id].rt > 0) {
            q.push(id);
        } else {
            p[id].ct = time;
            completed++;
        }
    }

    timeLine.push_back(time);

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    cout << "\nGantt Chart:\n";
    cout << "-------------------------------------------------\n";

    for (int id : gantt)
        cout << "| " << p[id].pid << " ";

    cout << "|\n-------------------------------------------------\n";

    for (int t : timeLine)
        cout << t << "    ";

    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for (auto &x : p) {
        cout << x.pid << "\t" << x.at << "\t" << x.bt << "\t"
             << x.ct << "\t" << x.tat << "\t" << x.wt << "\n";
    }

    return 0;
}