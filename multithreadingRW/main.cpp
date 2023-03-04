#include "header.h"



// Initialize mutex lock
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//Initialize Variable Conditions for R/W phase
pthread_cond_t readPhase = PTHREAD_COND_INITIALIZER;
pthread_cond_t writePhase =PTHREAD_COND_INITIALIZER;

int waitReader, res;
uint64_t gSharedValue;

#define NUM_Writers 5
#define NUM_Readers 5
#define NUM_Writes 5
#define NUM_Reads 5




int main()
{

    pthread_t r[NUM_Readers], w[NUM_Writers];

    uint32_t readID[NUM_Readers], writeID[NUM_Writers];

    //Generate Reading threads
    for (int i = 0; i < NUM_Readers; ++i) {
        readID[i] = i+1;
        pthread_create(&r[i], NULL, &mainReader, &readID[i]);
    }

    //Generate Writing threads
    for (int i = 0; i < NUM_Writers; ++i) {
        writeID[i] = i+1;
        pthread_create(&w[i], NULL, &mainWriter, &writeID[i]);
    }


    //Wait until readers threads to finish
    for (int i = 0; i < NUM_Readers; ++i) {
        pthread_join(r[i], NULL);
    }

    //Wait until writers threads to finish
    for (int i = 0; i < NUM_Writers; ++i) {
        pthread_join(w[i], NULL);
    }

    return 0;
}







void *mainReader(void *arg)
{
    int id = *((int *)arg);
    int currReader = 0;

    for(int i = 0; i < NUM_Reads; i++) {
        // Wait so that reads and writes do not all happen at once
        usleep(1000 * (random() % NUM_Writers + NUM_Readers));

        // Enter critical section
        pthread_mutex_lock(&lock);
        waitReader++;
        while (res == -1)
            pthread_cond_wait(&readPhase, &lock);
        currReader = ++res;
        waitReader--;
        pthread_mutex_unlock(&lock);

        //Read Data
        fprintf(stdout, "[r%d] Reading  %-3lu [readers: %2d]\n", id, gSharedValue, currReader);


        // Exit critical section
        pthread_mutex_lock(&lock);
        res--;
        if (res == 0)
            pthread_cond_signal(&writePhase);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *mainWriter(void *arg)
{
    int id = *((int *)arg);
    int currReader = 0;

    for(int i = 0; i < NUM_Writes; i++) {
        // Wait so that reads and writes do not all happen at once
        usleep(1000 * (random() % NUM_Writers + NUM_Readers));

        // Enter critical section
        pthread_mutex_lock(&lock);
        while (res != 0)
            pthread_cond_wait(&writePhase, &lock);
        res = -1;
        currReader = res;
        pthread_mutex_unlock(&lock);

        //Write Data
        fprintf(stdout, "[w%d] Writing  %-2lu* [readers: %2d]\n", id, ++gSharedValue, currReader);


        // Exit critical section
        pthread_mutex_lock(&lock);
        res = 0;
        if (waitReader > 0)
            pthread_cond_broadcast(&readPhase);
        else
            pthread_cond_signal(&writePhase);
        pthread_mutex_unlock(&lock);
    }
    return NULL;

}

