# CPU Scheduling Algorithms Implementation (C Language)

This repository contains a C program that simulates various **CPU Scheduling Algorithms**. It includes input validation to handle errors and generates a **Gantt Chart** for a visual representation of process execution.



---

## 🚀 Features

The program implements the following scheduling techniques:

1.  **FCFS (First-Come, First-Served):** Processes are executed in the order they arrive.
2.  **SJF (Shortest Job First):** A non-preemptive algorithm that selects the process with the smallest burst time.
3.  **SRJF (Shortest Remaining Job First):** The preemptive version of SJF where the process with the smallest remaining time is executed first.

---

## 📊 Key Metrics Calculated

For every algorithm, the program provides:
* **Arrival Time (AT)**
* **Burst Time (BT)**
* **Waiting Time (WT)**
* **Turnaround Time (TAT)**
* **Average Waiting & Turnaround Times**
* **Visual Gantt Chart** (with start and finish times)



---

## 🛠️ How to Run

### 1. Prerequisites
Make sure you have a C compiler (like `gcc`) installed on your system.

### 2. Compilation
Open your terminal/command prompt and run:
```bash
gcc main.c -o scheduler

### 3. Execution
Run the compiled file:

```bash

./scheduler

### 4. Sample Execution Output

CPU Scheduling Algorithms
1.FCFS
2.SJF
3.SRJF
Enter choice: 1

Process 1 Arrival Time: 0
Process 1 CPU Burst Time: 4
...

Gantt Chart:
|  P1   |  P2   |  P3   |
0      4      9      12

Average Waiting Time = 2.50
Average Turnaround Time = 6.50
