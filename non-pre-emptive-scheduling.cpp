/*Write one single C /C++ program to simulate different scheduling algorithm in OS  (functions)
•	First come first serve
•	Shortest job first
•	Priority
	Non pre-emptive

Compare the algorithm and print which is having less waiting time.
Consider the ready queue of OS, the processes are present and maintained with their arrival time and expected burst time for execution. Some processes have priority which is also given. Consider the required data to run different scheduling algorithms and analyse the result with respect to average waiting time and turnaround time.
*/

#include <iostream> 
#include <limits.h> 
#include <algorithm> 
#include <vector>
using namespace std; 
struct process_info{
int pid;
int at;
int bt;
int ct;
int tt;
int wt;
int priority;
};
bool sortbyat(process_info p1, process_info p2) { 
    return (p1.at < p2.at);
}
bool sortbybt(const process_info &p1, const process_info &p2) { 
    return p1.bt < p2.bt;
}
bool sortbyPriority(const process_info &p1, const process_info &p2) { 
    return p1.priority < p2.priority;
}

vector<int> burst(200);
void Firstcomefirstserve(vector<process_info> &process) { 
    int n = process.size();
    sort(process.begin(),process.end(),sortbyat); 
    process[0].ct = process[0].bt+process[0].at;
    process[0].tt = process[0].ct - process[0].at; 
    process[0].wt = 0;
    for (int i = 1; i < n; i++) {
    process[i].ct = process[i - 1].ct + process[i].bt; 
    process[i].tt = process[i].ct - process[i].at; 
    process[i].wt = process[i].tt - process[i].bt;
    }
}

void Shortestjobfirst(vector<process_info> &process, int n) { 
    sort(process.begin(), process.end(), sortbybt); 
    int current_t = 0;
    int i = 0; 
    while (i < n) {
    int next = -1;
    int short_t = INT_MAX; 
    for (int j = 0; j < n; j++) {
    if (process[j].at <= current_t && process[j].bt < short_t && process[j].bt > 0) {
    next= j;
    short_t= process[j].bt;
    }
    }
    if (next== -1) { 
    current_t++; 
    continue;
    }
    process[next].bt--; 
    current_t++;
    if (process[next].bt == 0) { 
    i++;
    process[next].ct = current_t; 
    process[next].tt = process[next].ct -process[next].at;
    }
    }
    for(int i=0;i<n;i++){
    process[i].wt=process[i].tt-burst[process[i].pid-1];
    }
    sort(process.begin(), process.end(), sortbyat);
}

void Priority(vector<process_info> &process) { 
    int n = process.size();
    sort(process.begin(),process.end(),sortbyPriority); 
    process[0].ct = process[0].bt; 
    process[0].wt = 0;
    for (int i = 1; i < n; i++) {
    process[i].ct = process[i - 1].ct+ process[i].bt; 
    process[i].tt= process[i].ct;
    process[i].wt = process[i].tt- process[i].bt;
    }
}

int main() {
int n,tt1=0,wt1=0,wt2=0,wt3=0; 
float avg1,avg2,avg3,avg4;
cout<<"Since non-pre emptive, Arrival time is 0 by default."<<endl;
cout << "Enter total number of processes: "; 
cin >> n;
vector<process_info> process(n); 
for (int i = 0; i < n; i++) {
cout << "Enter burst time and priority for process " << i + 1 << ": "; 
process[i].pid=i+1;
cin >> process[i].bt>>process[i].priority; 
burst[i]=process[i].bt;
}

Firstcomefirstserve(process);
cout << "Non-preemptiveFCFS\nProcessID\tAT\tBT\tCT\tTT\tWT" << "\n"; 
for (int i = 0; i < n; i++) { 
    tt1+=process[i].tt; 
    wt1+=process[i].wt;
    cout << process[i].pid<< "\t\t" <<process[i].at << "\t" << process[i].bt<< "\t"
    << process[i].ct<< "\t" << process[i].tt<< "\t" << process[i].wt<< "\n";
}

cout<<"\n";
avg1=(float)tt1/n; 
avg2=(float)wt1/n;

cout<<"Average Waiting Time of FCFS algorithm is: "<<avg2<<"time units"<<"\n"<<endl; 
cout<<"Average Turn Around Time of FCFS algorithm is : "<<avg1<<" time units\n"<<endl; 

Shortestjobfirst(process, n);
tt1=0;
cout << "\nNon-preemptive SJF\nProcessID\tAT\tBT\tCT\tTT\tWT" << "\n\n"; 
for (int i = 0; i < n; i++) { 
    tt1+=process[i].tt;
    wt2+=process[i].wt;
    cout << process[i].pid << "\t\t" << process[i].at<< "\t" << burst[process[i].pid-1] << "\t" << process[i].ct<< "\t" << process[i].tt << "\t" << process[i].wt << "\n";
}
avg1=(float)tt1/n; avg3=(float)wt2/n;

cout<<"Average Waiting Time of SJF algorithm is: "<<avg3<<" time units"<<"\n"<<endl; 
cout<<"Average TurnAround Time of SJF algorithm is: "<<avg1<<" time units\n"<<endl; 

for(int i=0;i<n;i++){
    process[i].at=0; process[i].bt=burst[process[i].pid-1];
}
tt1=0;

Priority(process);
cout << "\nNon-preemptive priority\nProcessID\tAT\tBT\tPriority\tCT\tTT\tWT" << "\n\n"; 
for(int i = 0; i < n; i++) {
    tt1+=process[i].tt; 
    wt3+=process[i].wt;
    cout << process[i].pid<< "\t\t" <<process[i].at << "\t" << process[i].bt<< "\t"<<process[i].priority<< "\t\t" << process[i].ct<< "\t" << process[i].tt << "\t" << process[i].wt << "\n";
}
avg1=(float)tt1/n; 
avg4=(float)wt3/n;

cout<<"Average Waiting Time of priority algorithm is : "<<avg4<<" time units\n"<<endl; 
cout<<"Average TurnAround Time of priority algorithm is: "<<avg1<<" time units\n"<<endl; 

cout<<"RESULT:"<<endl;
if(avg2< avg3 && avg2<avg4){
cout<<"Non-preemptive FCFS Algorithm has the least waiting time."<<endl;
}

else if(avg3<avg4 && avg3 <avg2){
cout<<"Non-preemptive SJF Algorithm has the least waiting time."<<endl;
}
else{
cout<<"Non-preemptive Priority Algorithm has the least waiting time."<<endl;
}
return 0;
}
