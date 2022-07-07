#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define CYLINDERS 10000 // defining the cylinders
#define REQUESTS 1000 // defining the requests

int FCFS(int disk[], int head);
int SCAN(int disk[], int head);
int CSCAN(int disk[], int head);

// First Come First Serve (FCFS)
int FCFS(int disk[], int head) {
    int movement = 0;
    int current = disk[head];

    for (int i = head; i < REQUESTS; i++) {
        movement += abs(disk[i] - current);
        current = disk[i];
    }

    for (int i = 0; i < head; i++) {
        movement += abs(disk[i] - current);
        current = disk[i];
    }

    // returns the value of the head movement within the FCFS algorithm
    return movement;
}

// SCAN Algorithm 
int SCAN(int disk[], int head) {
    int movement = 0; 
    int position = 0;
    int curr_ptr = head;
    bool toZero = true;
    bool fromZero = true;

    while (true) {
        // current represents the minimum distance  in the current head pointer on the disk
        int current = CYLINDERS;

        // Takes in all of elements and checks from head to zero
        if (toZero) {
            for (int i = 0; i < REQUESTS; i++) {
                if (disk[curr_ptr] > disk[i] && current >= abs(disk[curr_ptr] - disk[i])) {
                    current = abs(disk[curr_ptr] - disk[i]);
                    position = i;
                }
            }

            // checks for the position
            if (curr_ptr == position) {
                movement += disk[curr_ptr];
                curr_ptr = head;
                toZero = false;
            } else {
                movement += abs(disk[curr_ptr] - disk[position]);
                curr_ptr = position;
            }
        }
        
        else {
            for (int i = 0; i < REQUESTS; i++) {
                if (disk[curr_ptr] < disk[i] && current >= abs(disk[curr_ptr] - disk[i])) {
                    current = abs(disk[curr_ptr] - disk[i]);
                    position = i;
                }
            }

            if (curr_ptr == position) {
                return movement;
            } 
            else if (fromZero) {
                movement += disk[position];
                curr_ptr = position; 
                fromZero = false;
            } 
            else {
                movement += abs(disk[curr_ptr] - disk[position]);
                curr_ptr = position;
            }

        }
    }
}

// C-SCAN Algorithm
int CSCAN(int disk[], int head) {
    int movement = 0;
    int position = 0;
    int curr_ptr = head;
    bool toMax = true;
    bool fromMax = true;

    while (true) {
        // current represents minimum distance from the current head pointer on the disk
        int current = CYLINDERS;

        // C-SCAN goes towards to the highest element in the disk first
        if (toMax) {
            for(int i = 0; i < REQUESTS; i++) {
                if (disk[head] < disk[i] && disk[curr_ptr] < disk[i]  && current >= abs(disk[curr_ptr] - disk[i])){
                    current = abs(disk[curr_ptr] - disk[i]);
                    position = i;
                }
            }

            // checks for the position
            if (curr_ptr == position) {
                movement += abs(disk[curr_ptr] - CYLINDERS-1);
                curr_ptr = head; 
                toMax = false;
            } 
            else {
                movement += abs(disk[curr_ptr] - disk[position]);
                curr_ptr = position; 
            }

        } 

        else {
            if (fromMax) {
                movement += CYLINDERS-1;
                for (int i = 0;i < REQUESTS;i++) {
                    if (current >= abs(0 - disk[i]) && disk[i] < disk[head]){
                        current = abs(0 - disk[i]);
                        position = i; 
                    }
                }
                movement += disk[position]; 
                curr_ptr = position;
                fromMax = false;
            } 

            else {
                for(int i = 0;i < REQUESTS;i++) {
                    if (disk[curr_ptr] < disk[i] && disk[head] > disk[i] && current >= abs(disk[curr_ptr] - disk[i])){
                        current = abs(disk[curr_ptr] - disk[i]);
                        position = i;
                    }
                }

                if (curr_ptr == position) {
                    return movement;
                } 
                else {
                    movement += abs(disk[curr_ptr] - disk[position]);
                    curr_ptr = position;
                }
            }
        }
    }
}

// main class
int main(int argc, char *argv[]) {

    // argument handling
    if (argc < 2) {
        printf("Too few parameters, please add a starting position.\n");
        return -1;
    } 
    else if (argc > 2) {
        printf("Too many parameters, please add a starting position.\n");
    }

    // Array of disk requests and initializing starting head position
    int disk[REQUESTS];
    int head = atoi(argv[1]);

    // Parameter not matched, if not, O < head < 999, then output the message
    if (head < 0 || head > 999) { 
        printf("Incorrect parameter, starting position should be 0-999 \n");
        return -1; 
    }
    
    srand(time(NULL)); 
    for(int i = 0; i< REQUESTS;i++) { 
        disk[i] = rand() % CYLINDERS; // Disk has cylinders from 0-9999
    }

    // Output of the code
    printf("--Disk Algorithm: Head Movement--");
    printf("\n  FCFS: %d", FCFS(disk, head));
    printf("\n  SCAN: %d", SCAN(disk, head));
    printf("\n  CSCAN: %d\n", CSCAN(disk, head));
    return 0;
}