/*Write a C Program using threads to Implement Page Replacement Algorithm (FIFO, Optimal, and LRU) and determine their number of page fault. Each thread runs a separate algorithm and main thread prints the page faults of each algorithm.
Input: 
Enter data (length of page reference sequence, page reference sequence and no of frames)
Example
Consider the following page reference string:
1, 2, 3, 4, 2, 1, 4,2,5, 6, 2, 1, 6,5, 2, 3, 7, 5, 4,2, 6, 3, 2, 1, 2, 3, 6,4,2,5.
How many page faults would occur for the following replacement algorithms, assuming three frames? Remember that all frames are initially empty, so your first unique pages will cost one fault each.
• LRU replacement
• FIFO replacement
• Optimal replacement
*/


#include <stdio.h>
#include <pthread.h>
#define MAX_LENGTH 1000
#define MAX_FRAMES 10

int page_seq[MAX_LENGTH];
int num_frames;

void *fifo(void *arg) {
    int i, j, k, page_faults = 0;
    int frames[MAX_FRAMES];

    for (i = 0; i < num_frames; i++)
        frames[i] = -1;
    
    int frame_index = 0;
    for (i = 0; i < MAX_LENGTH; i++) {
        int page = page_seq[i];
        int found = 0;
        
        for (j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }    }
        
        if (!found) {
            frames[frame_index] = page;
            frame_index = (frame_index + 1) % num_frames;
            page_faults++;
        }    }
    
    printf("FIFO page faults: %d\n", page_faults);
    pthread_exit(NULL);
}

void *optimal(void *arg) {
    int i, j, k, page_faults = 0;
    int frames[MAX_FRAMES];
    
    for (i = 0; i < num_frames; i++)
        frames[i] = -1;
    
    for (i = 0; i < MAX_LENGTH; i++) {
        int page = page_seq[i];
        int found = 0;
        
        for (j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }        }
        
        if (!found) {
            int replace_page = -1;
            int max_distance = -1;
            
            for (j = 0; j < num_frames; j++) {
                int distance = 0;
                for (k = i + 1; k < MAX_LENGTH; k++) {
                    if (frames[j] == page_seq[k]) {
                        distance = k - i;
                        break;
                    }      }
                
                if (distance == 0) {
                    replace_page = j;
                    break;
                }
                
                if (distance > max_distance) {
                    max_distance = distance;
                    replace_page = j;
                }     }
            
            frames[replace_page] = page;
            page_faults++;
        }   }
    
    printf("Optimal page faults: %d\n", page_faults);
    pthread_exit(NULL);
}

void *lru(void *arg) {
    int i, j, k, page_faults = 0;
    int frames[MAX_FRAMES];
    int time[MAX_FRAMES];
    
    for (i = 0; i < num_frames; i++) {
        frames[i] = -1;
        time[i] = -1;
    }
    
    for (i = 0; i < MAX_LENGTH; i++) {
        int page = page_seq[i];
        int found = 0;
        
        for (j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                time[j] = i;
                break;
            }     }
        
        if (!found) {
            int oldest_time = i;
            int replace_page = -1;
            
            for (j = 0; j < num_frames; j++) {
                if (time[j] < oldest_time) {
                    oldest_time = time[j];
                    replace_page = j;
                }     }
            
            frames[replace_page] = page;
            time[replace_page] = i;
            page_faults++;
        }   }
    
    printf("LRU page faults: %d\n", page_faults);
    pthread_exit(NULL);
}

int main() {
    int i;
    pthread_t threads[3];
    printf("Enter the length of the page reference sequence: ");
    int length;
    scanf("%d", &length);
    printf("Enter the page reference sequence: ");
    for (i = 0; i < length; i++)
        scanf("%d", &page_seq[i]);
    
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);
    
    pthread_create(&threads[0], NULL, fifo, NULL);
    pthread_create(&threads[1], NULL, optimal, NULL);
    pthread_create(&threads[2], NULL, lru, NULL);
    
    for (i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);    
    return 0;
}
