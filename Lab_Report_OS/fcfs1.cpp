#include <iostream>
#include <vector>
using namespace std;

struct Process {
    string id;
    int at, bt, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input takes from user 
    for (int i = 0; i < n; i++) {
        p[i].id = "P" + to_string(i + 1);
        cout << "AT for " << p[i].id << ": ";
        cin >> p[i].at;
        cout << "BT for " << p[i].id << ": ";
        cin >> p[i].bt;
    }

    // Manual sorting (by arrival time)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                swap(p[i], p[j]);
            }
        }
    }

    int currentTime = 0;

    // Execution start
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at)
            currentTime = p[i].at;

        currentTime += p[i].bt;

        p[i].ct = currentTime;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    // Output showing
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