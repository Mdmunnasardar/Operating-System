#include <iostream>
#include <algorithm>
using namespace std;

class process {
public:
    int pid;
    int AT;
    int BT;
    int WT;
    int CT;  // Completion Time
    int TAT; // Turnaround Time
};

bool compareByAT(process a, process b) {
    return a.AT < b.AT;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    process p[n];
    
    // Input process details
    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time and Burst Time for Process P" << i+1 << ": ";
        cin >> p[i].AT >> p[i].BT;
    }
    
    // Sort processes by arrival time
    sort(p, p + n, compareByAT);
    
    // Calculate completion time, turnaround time, and waiting time
    int currentTime = 0;
    float avgWT = 0, avgTAT = 0;
    
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "----------------------------------------\n";
    
    for(int i = 0; i < n; i++) {
        if(currentTime < p[i].AT) {
            currentTime = p[i].AT;
        }
        
        p[i].CT = currentTime + p[i].BT;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
        
        currentTime = p[i].CT;
        
        avgWT += p[i].WT;
        avgTAT += p[i].TAT;
        
        cout << "P" << p[i].pid << "\t" << p[i].AT << "\t" << p[i].BT << "\t" 
             << p[i].CT << "\t" << p[i].TAT << "\t" << p[i].WT << endl;
    }
    
    avgWT /= n;
    avgTAT /= n;
    
    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;
    
    return 0;
}