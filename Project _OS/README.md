

```md id="readme_final1"
🖥️ CPU Scheduling Algorithms in C++ (Operating Systems Project)

This project demonstrates different **CPU Scheduling Algorithms** used in Operating Systems.  
It is implemented in **C++** for academic learning and simulation of process scheduling.

---

📌 Implemented Algorithms

✔ First Come First Serve (FCFS)  
✔ Shortest Job First (SJF - Non Preemptive)  
✔ Round Robin (RR - Preemptive)

---

📂 Project Structure

```

CPU-Scheduling-Algorithms/
│

├── fcfs.cpp

├── ShortestJobFirst.cpp

├── RoundRobin.cpp


├── Docs File


├── README.md

```

---

⚙️ Features

- Process input (Arrival Time, Burst Time)
- CPU Scheduling simulation
- Gantt Chart generation
- Completion Time (CT)
- Turnaround Time (TAT)
- Waiting Time (WT)
- Average WT and TAT calculation

---

📊 Formulas Used

- Turnaround Time (TAT) = Completion Time − Arrival Time  
- Waiting Time (WT) = Turnaround Time − Burst Time  

---

🔹 1. First Come First Serve (FCFS)

- Processes executed in order of arrival
- Simple scheduling method
- No preemption

---

🔹 2. Shortest Job First (SJF)

- Process with smallest Burst Time is executed first
- Reduces average waiting time
- Can cause starvation for long processes

---

🔹 3. Round Robin (RR)

- Each process gets fixed time quantum
- Preemptive scheduling algorithm
- Good for time-sharing systems
- Ensures fairness among processes

---

📥 Input Format

```

Number of Processes: n
Arrival Time (AT)
Burst Time (BT)

```id="input1"

For Round Robin:
```

Time Quantum (TQ)

````id="input2"

---

⚙️ How to Run (VS Code)

1. Open project in VS Code  
2. Open terminal (`Ctrl + ~`)  
3. Compile any file:

```bash id="run1"
g++ FCFS.cpp -o fcfs
````

4. Run program:

```bash id="run2"
./fcfs
```

(Repeat same for SJF and Round Robin)

---

📸 Output

Each algorithm produces:

* Gantt Chart
* Process Table
* Average Waiting Time
* Average Turnaround Time

---

🧠 Learning Outcome

* Understanding CPU Scheduling
* Process execution order
* Difference between FCFS, SJF, RR
* Performance comparison of algorithms

---

👨‍💻 Author
# 👨‍💻 Author

Md Munna Sardar  
Student, Department of Computer Science & Engineering  
Northern University of Business & Technology Khulna (NUBTK)

Student Project – Operating Systems Lab
C++ Programming Implementation

---

⭐ If you like this project

Give a ⭐ on GitHub and use it for learning or academic submission.

```


