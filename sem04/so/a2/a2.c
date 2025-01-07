#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdbool.h>
#include "a2_helper.h"

#define T7_COUNT 5
#define T2_COUNT 48
#define T5_COUNT 6

int th2_count = 0;
int th2_so_far = 0;
bool done = false;
pthread_mutex_t th2_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t th2_cond = PTHREAD_COND_INITIALIZER;
sem_t sem2_total;
sem_t sem2_barrier;

void* thread2(void *arg) {
    int id = *((int*)arg);

    sem_wait(&sem2_total);
    info(BEGIN, 2, id);
    pthread_mutex_lock(&th2_mutex);
    th2_count++;
    th2_so_far++;
    pthread_mutex_unlock(&th2_mutex);

    if (!done && id == 15) {
        sem_wait(&sem2_barrier);
        pthread_mutex_lock(&th2_mutex);
        done = true;
        pthread_cond_wait(&th2_cond, &th2_mutex);
        pthread_mutex_unlock(&th2_mutex);

        pthread_mutex_lock(&th2_mutex);
        th2_count--;
        pthread_mutex_unlock(&th2_mutex);

        info(END, 2, id);
        sem_post(&sem2_total);
        sem_post(&sem2_barrier);
    } else {
        if (!done && th2_so_far >= 45) {
            sem_wait(&sem2_barrier);
            pthread_mutex_lock(&th2_mutex);
            done = true;
            pthread_mutex_unlock(&th2_mutex);
        }
        if (th2_so_far == 48) {
            sem_post(&sem2_barrier);
        }

        if (th2_count == 4) {
            pthread_mutex_lock(&th2_mutex);
            pthread_cond_broadcast(&th2_cond);
            pthread_mutex_unlock(&th2_mutex);
        }

        sem_wait(&sem2_barrier);
        sem_post(&sem2_barrier);

        pthread_mutex_lock(&th2_mutex);
        th2_count--;
        pthread_mutex_unlock(&th2_mutex);

        info(END, 2, id);
        sem_post(&sem2_total);
    }
    pthread_exit(NULL);
}


sem_t sem7_3, sem7_4;
void* thread7(void* arg) {
    int id = *((int*)arg);

    switch(id) {
        case 3: {
            sem_wait(&sem7_3);
            info(BEGIN, 7, id);
            info(END, 7, id);
            sem_post(&sem7_4);
            break;
        }
        case 4: {
            info(BEGIN, 7, id);
            sem_post(&sem7_3);
            sem_wait(&sem7_4);   
            info(END, 7, id);
            break;
        }
        case 5: {
            sem_t* sem5_5 = sem_open("sem5_5", O_CREAT, 0644, 0);
            sem_t* sem5_3 = sem_open("sem5_3", O_CREAT, 0644, 0);
            sem_wait(sem5_5);
            info(BEGIN, 7, id);
            info(END, 7, id);
            sem_post(sem5_3);
            break;
        }
        default: {
            info(BEGIN, 7, id);
            info(END, 7, id);
            break;
        }   
    }   
    pthread_exit(NULL); 
}

void *thread5(void *arg) {
    int id = *((int*)arg);

    switch (id) {
        case 5: {
            sem_t* sem5_5 = sem_open("sem5_5", O_CREAT, 0644, 0);
            info(BEGIN, 5, id);
            info(END, 5, id);
            sem_post(sem5_5);
            break;
        }
        case 3: {
            sem_t* sem5_3 = sem_open("sem5_3", O_CREAT, 0644, 0);
            sem_wait(sem5_3);
            info(BEGIN,5,id);
            info(END,5,id);
            break;
        }
        default: {
            info(BEGIN, 5, id);
            info(END, 5, id);
            break;
        }
    }

    pthread_exit(NULL);
}

int main(){
    init();

    info(BEGIN, 1, 0);
    
    int pid2 = fork();
    if (pid2 == 0) {
        info(BEGIN, 2, 0);

        sem_init(&sem2_total, 0, 4);
        sem_init(&sem2_barrier,0,1);

        pthread_t threads2[T2_COUNT];
        int ids2[T2_COUNT];
        for (int i = 0; i < T2_COUNT; i++) {
            ids2[i] = i + 1;
            pthread_create(&threads2[i], NULL, thread2, &ids2[i]);
        }

        for (int i = 0; i < T2_COUNT; i++) {
            pthread_join(threads2[i], NULL);
        }

        sem_destroy(&sem2_total);

        info(END, 2, 0);
        exit(0);
    } else {
        int pid4 = fork();
        if (pid4 == 0) {
            info(BEGIN, 4, 0);
            info(END, 4, 0);
            exit(0);
        } else {
            int pid7 = fork();
            if (pid7 == 0) {
                info(BEGIN, 7, 0);

                sem_init(&sem7_3, 0, 0);
                sem_init(&sem7_4, 0, 0);

                pthread_t threads7[T7_COUNT];
                int ids7[T7_COUNT];
                for (int i = 0; i < T7_COUNT; i++) {
                    ids7[i] = i + 1;
                    pthread_create(&threads7[i], NULL, thread7, &ids7[i]);
                }

                for (int i = 0; i < T7_COUNT; i++) {
                    pthread_join(threads7[i], NULL);
                }

                sem_destroy(&sem7_3);
                sem_destroy(&sem7_4);

                info(END, 7, 0);
                exit(0);
            } else {
                int pid3 = fork();
                if (pid3 == 0) {
                    info(BEGIN, 3, 0);

                    int pid5 = fork();
                    if (pid5 == 0) {
                        info(BEGIN, 5, 0);



                        pthread_t threads5[T5_COUNT];
                        int ids5[T5_COUNT];
                        for (int i = 0; i < T5_COUNT; i++) {
                            ids5[i] = i + 1;
                            pthread_create(&threads5[i], NULL, thread5, &ids5[i]);
                        }

                        for (int i = 0; i < T5_COUNT; i++) {
                            pthread_join(threads5[i], NULL);
                        }

                        info(END, 5, 0);
                        exit(0);
                    } else {
                        int pid6 = fork();
                        if (pid6 == 0) {
                            info(BEGIN, 6, 0);

                            int pid8 = fork();
                            if (pid8 == 0) {
                                info(BEGIN, 8, 0);
                                info(END, 8, 0);
                                exit(0);
                            } else {
                                waitpid(pid8, NULL, 0);
                                info(END, 6, 0);
                                exit(0);
                            }
                        } else {
                            waitpid(pid6, NULL, 0);
                            waitpid(pid5, NULL, 0);
                            info(END, 3, 0);
                            exit(0);
                        }
                    }
                } else {
                    waitpid(pid3, NULL, 0);
                    waitpid(pid2, NULL, 0);
                    waitpid(pid4, NULL, 0);
                    waitpid(pid7, NULL, 0);
                    info(END, 1, 0);
                }
            }
        }
    }

    return 0;
}
