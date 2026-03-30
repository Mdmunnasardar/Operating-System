#include <iostream>
#include <vector>
using namespace std;

struct Process {
    string id;
    int at, bt, ct, tat, wt;
    bool finished;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input
    for (int i = 0; i < n; i++) {
        p[i].id = "P" + to_string(i + 1);
        cout << "AT for " << p[i].id << ": ";
        cin >> p[i].at;
        cout << "BT for " << p[i].id << ": ";
        cin >> p[i].bt;
        p[i].finished = false;
    }

    int time = 0, doneCount = 0;

    // Execution
    while (doneCount < n) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].finished) {
                if (selected == -1 || p[i].bt < p[selected].bt) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            time++;
            continue;
        }

        time += p[selected].bt;

        p[selected].ct = time;
        p[selected].tat = p[selected].ct - p[selected].at;
        p[selected].wt = p[selected].tat - p[selected].bt;

        p[selected].finished = true;
        doneCount++;
    }

    // Output
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    float sumWT = 0, sumTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        sumWT += p[i].wt;
        sumTAT += p[i].tat;
    }

    cout << "\nAverage WT: " << sumWT / n;
    cout << "\nAverage TAT: " << sumTAT / n;

    return 0;
}