/*Consider the following snapshot of a system in which four resources A, B, C and D are available. The system currently contains 6 instances of A, 4 of resource B, 4 of resource C, 2 resources D after allocation.
    
a.	Write a C/ C++ code to do deadlock avoidance using banker’s algorithm:

•	Compute what each process might still request and fill this in under the column Need.
•	Is the system in a safe state? Why or why not?
•	 Is the system deadlocked? Why or why not?

b.	If   P0 request < 1 1 0 0> at t1, will the request grant? If so, find the Safe sequence.
*/

#include <iostream>
using namespace std;
void banker()
{
int n, m, i, j, k;
cout<<"Enter number of processes:";
cin>>n;
cout<<"Enter number of resources:";
cin>>m;
int alloc[n][m];
cout<<"Enter allocation matrix value\n";
for(int i=0;i<n;i++){
 for(int j=0;j<m;j++){
 cin>>alloc[i][j];
 }}
int max[n][m];
cout<<"Enter max matrix's value\n";
for(int i=0;i<n;i++){
 for(int j=0;j<m;j++){
 cin>>max[i][j];
 }}
 int avail[m];
cout<<"Enter available matrix value\n";
for (int i = 0; i < m; i++) {
cin>>avail[i];
 }
 int need[n][m];
int f[n], ans[n];

int ind = 0;
for (k = 0; k < n; k++) {
f[k] = 0;
}

for (i = 0; i < n; i++) {
for (j = 0; j < m; j++)
need[i][j] = max[i][j] - alloc[i][j];
}
cout<<"Upon computation, Need Column looks as follows:"<<endl;
cout<<"\tA\tB\tC\tD"<<endl;
cout<<"----------------------------------"<<endl;
for(i=0;i<n;i++){
cout<<"P"<<i<<"\t";
for(j=0;j<n;j++){
cout<<need[i][j]<<"\t";
}
cout<<endl;
}
int y = 0;
for (k = 0; k < 5; k++) {
    for (i = 0; i < n; i++) {
if (f[i] == 0) {
    int flag = 0;
 for (j = 0; j < m; j++) {
 if (need[i][j] > avail[j]){
 flag = 1;
 break;
}
 }
 if (flag == 0) {
     
ans[ind++] = i;
for (y = 0; y < m; y++)
avail[y] += alloc[i][y];
f[i] = 1;
}
 }
 }
}
int c=0;
int flag = 1;
for(int i = 0;i<n;i++)
{
if(f[i]==0)
{
 flag = 0;
 c++;
 cout << "\nThe given sequence is not safe. So, system is not in safe state.\n";
cout<<"Since there is no safe state for the system, the system is deadlocked.\n";
 break;
}
}
if(flag==1)
{
cout << "\nThe system is in safe state and following is the safe sequence\n" << endl;
for (i = 0; i < n - 1; i++)
cout << "P" << ans[i] << " ->";
cout << "P" << ans[n - 1] <<endl;
cout<<"\nSince safe sequence is available for the system, it can be concluded that the system does not get into a deadlock state.\n";
}
int request[4];
bool condition;
int temp;
label1:
cout<<"Do you want to pass a request?\n";
cout<<"Enter 1 if yes, else 0: \n";
cin>>temp;
if (temp==1)
condition=true;
else
condition=false;
if (condition)
{
    cout<<"Enter request:\n";
    for(i=0;i<m;i++){
        cin>>request[i];
    }
int pid,count;
cout<<"Enter process number:\n";
cin>>pid;
for(i=0;i<m;i++){
    if(request[i]<=need[pid][i]){
        count++;
        need[pid][i]=request[i];
    }
}
if(count==4){
for(k=0;k<n;k++)
f[k]=0;
y=0;
for(k=0;k<n+1;k++){
    for(i=0;i<n;i++){
        if(f[i]==0){
            int flag=0;
            for(j=0;j<m;j++){
                if(need[i][j]>avail[j]){
                    flag=1;
                    break;
                }
            }
            if(flag==0){
                ans[ind++]=i;
                for (y = 0; y < m; y++)
                 avail[y] += alloc[i][y];
                 f[i] = 1;

            }
        }
    }
}
c=0;
flag=1;
for(i=0;i<n;i++){
    if(f[i]==0){
        flag=0;
        cout<<"Sequence is not safe\n";
        c++;
        cout<<"Request cannot be generated and due to hold and wait, syste gets into deadlock.\n";
        break;
    }
    if(flag==1){
        cout << "\nThe system is in safe state and following is the safe sequence\n" << endl;
        for (i = 0; i < n - 1; i++)
        cout << "P" << ans[i] << " ->";
        cout << "P" << ans[n - 1] <<endl;
        cout<<"Request can be granted. Since there is atleast 1 safe sequence, system does not get into deadlock. \n";
    }
else{
    cout<<"The request cannot be granted for the process. The system goes into a deadlock state.";
}}
goto label1;
}
}}
int main(){
    banker();
return 0;
}
