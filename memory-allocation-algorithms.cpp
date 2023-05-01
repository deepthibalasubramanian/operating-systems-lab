/*1.	Write a C/C++ program for dynamic memory allocation algorithm. Consider six memory partitions of size 200 KB, 400 KB, 600 KB, 500 KB, 300 KB and 250 KB. These partitions need to be allocated to four processes of sizes 357 KB, 210 KB, 468 KB and 491 KB in that order. Calculate the external fragmentation caused if any.
      Perform the allocation of processes using-
1.	First Fit Algorithm
2.	Best Fit Algorithm
3.	Worst Fit Algorithm
*/

#include<iostream>
using namespace std;
struct memory_block {
    int id; 
    int size;
    bool allocated; //flag to check if the block is allocated or not
};
void init_memory_blocks(memory_block memory_blocks[], int num_blocks) {
    int sizes[] = {200, 400, 600, 500, 300, 250};
    for(int i=0; i<num_blocks; i++) {
        memory_blocks[i].id = i+1;
        memory_blocks[i].size = sizes[i];
        memory_blocks[i].allocated = false;
    }
}
//First Fit algorithm
void first_fit(memory_block memory_blocks[], int num_blocks, int process_sizes[], int num_processes) {
    cout<<"First Fit Allocation:"<<endl;
    for(int i=0; i<num_processes; i++) {
        int j;
        for(j=0; j<num_blocks; j++) {
            if(memory_blocks[j].size >= process_sizes[i] && !memory_blocks[j].allocated) {
                memory_blocks[j].allocated = true;
                cout<<"Process "<<i+1<<" of size "<<process_sizes[i]<<" KB is allocated in memory block "<<memory_blocks[j].id<<" of size "<<memory_blocks[j].size<<" KB"<<endl;
                break;
            } }
        if(j == num_blocks) {
            cout<<"Process "<<i+1<<" of size "<<process_sizes[i]<<" KB can't be allocated due to insufficient memory"<<endl;
        } }
    cout<<endl;
}
//Best Fit algorithm
void best_fit(memory_block memory_blocks[], int num_blocks, int process_sizes[], int num_processes) {
    cout<<"Best Fit Allocation:"<<endl;
    for(int i=0; i<num_processes; i++) {
        int best_block = -1;
        for(int j=0; j<num_blocks; j++) {
            if(memory_blocks[j].size >= process_sizes[i] && !memory_blocks[j].allocated) {
                if(best_block == -1 || memory_blocks[j].size < memory_blocks[best_block].size) {
                    best_block = j;
                } } }
        if(best_block == -1) {
            cout<<"Process "<<i+1<<" of size "<<process_sizes[i]<<" KB can't be allocated due to insufficient memory"<<endl;
        }
        else {
            memory_blocks[best_block].allocated = true;
            cout<<"Process "<<i+1<<" of size "<<process_sizes[i]<<" KB is allocated in memory block "<<memory_blocks[best_block].id<<" of size "<<memory_blocks[best_block].size<<" KB"<<endl;
        } }
    cout<<endl;
}
//Worst Fit algorithm
void worst_fit(memory_block memory_blocks[], int num_blocks, int process_sizes[], int num_processes) {
    cout<<"Worst Fit Allocation:"<<endl;
    for(int i=0; i<num_processes; i++) {
        int worst_block = -1;
        for(int j=0; j<num_blocks; j++) {
            if(memory_blocks[j].size >= process_sizes[i] && !memory_blocks[j].allocated) {
                if(worst_block == -1 || memory_blocks[j].size > memory_blocks[worst_block].size) {
                    worst_block = j;
                } } }
        if(worst_block == -1) {
            cout<<"Process "<<i+1<<" of size "<<process_sizes[i]<<" KB can't be allocated due to insufficient memory"<<endl;
}
else {
memory_blocks[worst_block].allocated = true;
cout<<"Process "<<i+1<<" of size "<<process_sizes[i]<<" KB is allocated in memory block "<<memory_blocks[worst_block].id<<" of size "<<memory_blocks[worst_block].size<<" KB"<<endl;
}}
cout<<endl;
}
//Calculate external fragmentation
void calc_external_fragmentation(memory_block memory_blocks[], int num_blocks) {
int total_free_memory = 0;
int largest_free_block = 0;
for(int i=0; i<num_blocks; i++) {
if(!memory_blocks[i].allocated) {
total_free_memory += memory_blocks[i].size;
if(memory_blocks[i].size > largest_free_block) {
largest_free_block = memory_blocks[i].size;
}}}
cout<<"Total free memory: "<<total_free_memory<<" KB"<<endl;
cout<<"Largest free block: "<<largest_free_block<<" KB"<<endl;
cout<<"External fragmentation: "<<total_free_memory - largest_free_block<<" KB\n"<<endl;
cout<<"-----------------------------------------------------------------------------"<<endl;
}

int main() {
const int num_blocks = 6;
memory_block memory_blocks[num_blocks];
init_memory_blocks(memory_blocks, num_blocks);
const int num_processes = 4;
int process_sizes[num_processes] = {357, 210, 468, 491};
first_fit(memory_blocks, num_blocks, process_sizes, num_processes);
calc_external_fragmentation(memory_blocks, num_blocks);
init_memory_blocks(memory_blocks, num_blocks);
best_fit(memory_blocks, num_blocks, process_sizes, num_processes);
calc_external_fragmentation(memory_blocks, num_blocks);
init_memory_blocks(memory_blocks, num_blocks);
worst_fit(memory_blocks, num_blocks, process_sizes, num_processes);
calc_external_fragmentation(memory_blocks, num_blocks);
return 0;
}
