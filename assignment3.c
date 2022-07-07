#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define THREADS 10 // defining the threads

// declaring the mutex lock and initializing
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// alter struct where it alternates each farmer and bridge
struct alter {
    int c; // the count
    char* b; // bridges
};

void *runner(void *alt);

// main class
int main() {

    // declaring the north and south threads
    pthread_t north[THREADS], south[THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // intializing the lock
    pthread_mutex_init(&lock, NULL);

    // 2 alters declared
    struct alter alt[2]; 
    alt[0].c = 0;
    alt[0].b = "North Tunbridge";
    alt[1].c = 0;
    alt[1].b = "South Tunbridge";

    // creating the threads 
    for(int i = 0; i < THREADS;i++) {
        pthread_create(&north[i], &attr, runner, (void *)&alt[0]);
        pthread_create(&south[i], &attr, runner, (void *)&alt[1]);
    }

    // joining the threads
    for (int i = 0; i < THREADS;i++) {
        pthread_join(north[i], NULL);
        pthread_join(south[i], NULL);
    }

    // lock is destroyed
    pthread_mutex_destroy(&lock); 
}

void *runner(void *alt) {
    // locks the thread, 
    // Note: comment this to not use the lock
    pthread_mutex_lock(&lock);
    
    // crosses the bridge
    struct alter *args = alt;
    args -> c++;
    printf("%s #%d farmer can cross the bridge \n", args -> b, args -> c);

    // random time
    srand(time(NULL));
    printf("%s #%d is traveling on the bridge...\n", args -> b, args -> c);

    // waits for between 0 to 3 seconds
    sleep(rand() % 3);
    printf("%s #%d farmer has left the bridge \n\n", args -> b, args -> c);

    // unlocks the thread
    // Note: comment this to not use the lock
    pthread_mutex_unlock(&lock);

    // exits the thread
    pthread_exit(0);
}