/*Write one single C /C++ program to simulate different scheduling algorithm in OS  (functions)- Pre-emptive  Algorithms

•	Shortest job remaining first
•	Priority (pre-emptive)
•	Round Robin 

Compare the algorithm and print which is having less waiting time.

Consider the ready queue of OS, the process are present and maintained with their arrival time and expected burst time for execution. Some processes have priority which is also given. Consider the required data to run different scheduling algorithms and analyse the result with respect to average waiting time and turnaround time.
*/

#include<iostream>
#include<cstdlib>
#include<queue>
#include<cstdio>
#define INT_MAX 9999999
using namespace std;
struct process{
int pid;
int bt;
int at;
int priority;
int st;
int ft;
float waitt;
float tat;
};
process p[5],p1[5],temp;
queue<int> q1;

void sjrffindwt(process pr[], int n, int wt[]){
int rt[n];
for(int i=0;i<n;i++)
rt[i]=pr[i].bt;
int comp=0,t=0,max=INT_MAX, shortest=0;
int ft;
bool flag=false;
while (comp!=n){
for(int i=0;i<n;i++){
if((pr[i].at<=t)&&(rt[i]<max)&&(rt[i]>0)){
max=rt[i];
shortest=i;
flag=true;
}}
if (flag==false){
t++;
continue;
}
rt[shortest]--;
max=rt[shortest];
if(max==0)
max=INT_MAX;
if(rt[shortest]==0){
comp++;
flag=false;
ft=t+1;
wt[shortest]=ft-pr[shortest].bt-pr[shortest].at;
if(wt[shortest]<0)
wt[shortest]=0;
} t++;
}}


void sjrffindtt(process pr[],int n, int wt[], int tt[]){
for(int i=0;i<n;i++){
tt[i]=pr[i].bt+wt[i];
}}


float sjrf(process pr[], int n){
int wt[n], tt[n], twt=0, ttt=0;
sjrffindwt(pr,n,wt);
sjrffindtt(pr,n,wt,tt);
cout<<"Process\t"<<"Burst Time\t"<<"Waiting time\t"<<"Turnaround time\t"<<endl;
for(int i=0;i<n;i++){
twt=twt+wt[i];
ttt=ttt+tt[i];
cout<<" "<<pr[i].pid<<"\t\t"<<pr[i].bt<<"\t\t"<<wt[i]<<"\t\t"<<tt[i]<<endl;
}
float w1=(float)twt/(float)n;
cout<<"\nSJRF Avg Waiting time: "<<w1<<endl;
cout<<"\nSJRF Avg Turnaround time: "<<(float)ttt/(float)n<<endl;
return w1;
}


// C++ Implementation of Preemptive Priority Scheduling
float prio(process pr[], int n){
    int x[n], wt[n], tt[n], ct[n];
    int i, j, smallest, count = 0, temp;
    double avg = 0, tt1 = 0, end;

    for (i = 0; i < n; i++)
        x[i] = pr[i].bt;


    pr[n].priority=10000;


    for (temp = 0; count != n; temp++)
    {
        smallest = n;
        for (i = 0; i < n; i++)
        {
            if (pr[i].at<= temp && pr[i].priority < pr[smallest].priority && pr[i].bt > 0)
                smallest = i;
        }
        pr[smallest].bt--;
        if (pr[smallest].bt == 0)
        {
            count++;
            end = temp + 1;
            ct[smallest] = end;
            wt[smallest] = end - pr[smallest].at - x[smallest];
            tt[smallest] = end - pr[smallest].at;
        }
    }
    cout << "Process"<< "\t  "<< "burst-time"<< "\t "<< "arrival-time"<< "\t "<< "waiting-time"
        << "\t"<< "turnaround-time"<< "\t "<< "completion-time"<< "\t"<< "Priority" << endl;
    for (i = 0; i < n; i++)
    {
        cout << "p" << i + 1 << "\t\t" << x[i] << "\t\t" << pr[i].at << "\t\t" << wt[i] << "\t\t" << tt[i] << "\t\t" << ct[i] << "\t\t" << pr[i].priority<< endl;
        avg = avg + wt[i];
        tt1 = tt1 + tt[i];
    }
    float w2=avg / n;
    cout << "\n\nPriority Average waiting time= " <<w2<<endl;
    cout << "Priority Average turnaround time= " << tt1 / n << endl;
}

int accept(int ch)
{
  int i,n;
 
  printf("Enter the Total Number of Process: ");
  scanf("%d",&n);
  
 if(n==0)
  {
    printf("Invalid");
    exit(1);
  }
  
  cout<<endl;
  
  for(i=1;i<=n;i++)
  {
    printf("Enter an Arrival Time of the Process P%d: ",i);
    scanf("%d",&p[i].at);
    p[i].pid=i;
  }

 cout<<endl;
  
  for(i=1;i<=n;i++)
  {
    printf("Enter a Burst Time of the Process P%d: ",i);
    scanf("%d",&p[i].bt);
  } 
 
  for(i=1;i<=n;i++)
   {
    p1[i]=p[i];
 }
  return n;
}

void ganttrr(int n)
{ 
  int i,ts,m,nextval,nextarr; 
 
  nextval=p1[1].at;
  i=1;
 
  cout<<"\nEnter the Time Slice or Quantum: ";
  cin>>ts;
 
  for(i=1;i<=n && p1[i].at<=nextval;i++)
   {
    q1.push(p1[i].pid);
 }
 
  while(!q1.empty()) 
  { 
    m=q1.front();
    q1.pop();
  
    if(p1[m].bt>=ts)
     {
      nextval=nextval+ts;
  } 
    else
     {
      nextval=nextval+p1[m].bt;
    }   
    if(p1[m].bt>=ts)
     {
      p1[m].bt=p1[m].bt-ts;
  } 
    else
     {
      p1[m].bt=0;
  }   
  
    while(i<=n&&p1[i].at<=nextval)
    {
      q1.push(p1[i].pid);
      i++;
    }
  
    if(p1[m].bt>0)
     {
      q1.push(m);
  }
    if(p1[m].bt<=0)
     {
      p[m].ft=nextval;
     }   
  }
}

void turnwait(int n)
{
  int i; 
 
  for(i=1;i<=n;i++)
  {
    p[i].tat=p[i].ft-p[i].at;
    p[i].waitt=p[i].tat-p[i].bt;
    p[0].tat=p[0].tat+p[i].tat;
    p[0].waitt=p[0].waitt+p[i].waitt;
  }   
 
  p[0].tat=p[0].tat/n;
  p[0].waitt=p[0].waitt/n;
}

float display(int n)
{
  int i;
  cout<<"\n===================TABLE==============================\n";
  printf("\nProcess\tAT\tBT\tFT\tTAT\t\tWT");
 
  for(i=1;i<=n;i++)
 {
  printf("\nP%d\t%d\t%d\t%d\t%f\t%f",p[i].pid,p[i].at,p[i].bt,p[i].ft,p[i].tat,p[i].waitt);
 }
  cout<<"\n=====================================================\n"; 
   float w3=p[0].waitt;
   printf("\nRR Average Waiting Time: %f\n",w3);
   printf("\nRR Average Turn Around Time: %f\n",p[0].tat);
   return w3;
}


int main(){
process pr[]={{1,15,0,3},{2,2,2,1},{3,5,4,4},{4,1,7,5},{5,7,3,2}};
int n=sizeof(pr)/sizeof(pr[0]);
 int i,ch,ts,j,x;
    float w1, w2, w3;
  p[0].tat=0;
  p[0].waitt=0;
 
  n=accept(ch);
  ganttrr(n);
  turnwait(n);
  w1=sjrf(pr,n);
 w2=prio(pr,n);
 w3=display(n);


if(w1<w2 && w1<w3){
    cout<<"SJRF has least waiting time.";
}
else if(w2<w3){
    cout<<"Priority algorithm has least waiting time.";
}

else{
    cout<<"RR algorithm has least waiting time.";
}
return 0;
}
