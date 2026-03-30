#include <bits/stdc++.h>
using namespace std;

// ---------------- FIFO ----------------
int FIFO(vector<int> ref, int frames) {
    queue<int> q;
    unordered_set<int> s;
    int faults = 0;

    cout << "=== FIFO ===\n";

    cout << "Page: ";
    for (int x : ref) cout << x << " ";
    cout << "\n";

    vector<vector<int>> table(frames, vector<int>(ref.size(), -1));
    vector<char> fault(ref.size(), '.');

    for (int i = 0; i < ref.size(); i++) {
        int page = ref[i];

        if (s.find(page) == s.end()) {
            faults++;
            fault[i] = 'F';

            if (q.size() == frames) {
                int old = q.front();
                q.pop();
                s.erase(old);
            }

            q.push(page);
            s.insert(page);
        }

        // snapshot frames
        vector<int> temp;
        queue<int> copy = q;
        while (!copy.empty()) {
            temp.push_back(copy.front());
            copy.pop();
        }

        for (int j = 0; j < frames; j++) {
            if (j < temp.size())
                table[j][i] = temp[j];
        }
    }

    for (int i = 0; i < frames; i++) {
        cout << "[" << i << "]: ";
        for (int j = 0; j < ref.size(); j++) {
            if (table[i][j] == -1) cout << "  ";
            else cout << table[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "Fault: ";
    for (char c : fault) cout << c << " ";
    cout << "\n";

    cout << "Total Page Faults: " << faults << "\n\n";
    return faults;
}

// ---------------- LRU ----------------
int LRU(vector<int> ref, int frames) {
    unordered_set<int> s;
    unordered_map<int, int> last;
    int faults = 0;

    cout << "=== LRU ===\n";

    for (int i = 0; i < ref.size(); i++) {
        int page = ref[i];

        if (s.find(page) == s.end()) {
            faults++;

            if (s.size() == frames) {
                int lru = -1, mn = INT_MAX;

                for (auto p : s) {
                    if (last[p] < mn) {
                        mn = last[p];
                        lru = p;
                    }
                }
                s.erase(lru);
            }

            s.insert(page);
        }

        last[page] = i;
    }

    cout << "Total Page Faults: " << faults << "\n\n";
    return faults;
}

// ---------------- OPTIMAL ----------------
int OPT(vector<int> ref, int frames) {
    unordered_set<int> s;
    int faults = 0;

    cout << "=== Optimal ===\n";

    for (int i = 0; i < ref.size(); i++) {
        int page = ref[i];

        if (s.find(page) == s.end()) {
            faults++;

            if (s.size() == frames) {
                int victim = -1, far = -1;

                for (auto p : s) {
                    int j;
                    for (j = i + 1; j < ref.size(); j++) {
                        if (ref[j] == p) break;
                    }

                    if (j > far) {
                        far = j;
                        victim = p;
                    }
                }

                s.erase(victim);
            }

            s.insert(page);
        }
    }

    cout << "Total Page Faults: " << faults << "\n";
    return faults;
}

// ---------------- MAIN ----------------
int main() {
    int n, frames;

    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> ref(n);

    cout << "Enter reference string:\n";
    for (int i = 0; i < n; i++) cin >> ref[i];

    cout << "Enter number of frames: ";
    cin >> frames;

    FIFO(ref, frames);
    LRU(ref, frames);
    OPT(ref, frames);

    cout << "Operating Systems — Lab Project\n";
    cout << "Undergraduate OS Course\n";

    return 0;
}