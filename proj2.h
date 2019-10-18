#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Need for waiting in random time interval
#include <pthread.h>
// Librariese for work with semaphores and for share memory
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#include <sys/mman.h>



#ifndef _PROJ2_H
#define _PROJ2_H

#define NAME "proj2.out"

/*typedef struct  {
     int errorState;
         int A;
         int C;
         int AGT;
         int CGT;
         int AWT;
         int CWT;
  //      FILE *sOUT;
    } params_t;

void child(params_t Params);
void adult(params_t Params);

        sem_t *sem_mutex;                   // just mutex
        sem_t *sem_pa;                  //for that: If process adult generate, then will end after their descendant
        sem_t *sem_pc;                      //for that: If process child generate, then will end after their descendant
        sem_t *sem_gena;                    //Need for that the main process end, after adult process was generate
        sem_t *sem_genc;                    //Need for that the main prosceee end, after child process was generate
        sem_t *sem_inside;                  // Need for adult and child ends
        sem_t *sem_child_queue;                 //For child queue, while they enter
        sem_t *sem_child_adult_queue;           //For aduld queue, while they leaving
        sem_t *sem_wait_child;          //child have to wait, if before him child
        sem_t *sem_wait_adult;
        sem_t *sem_adult_queue;



/// FILE  for SHARED VARIABLES
unsigned int order_A_id,  // it's order number for adult
             c_A_id,       // coming adults - how many ???
             w_leave_A_id,// adult waiting for leave from center
             number_AC_id,  //  totally number  adult in center
             c_plus_A_id,   //  Total number of process
             w_number_in_C_id, // Child waiting to enter the center
             number_CC_id;    // totally number child in center
// POINTERS TO SHARED VARIABLES

unsigned int *order_A,  // it's order number for adult
             *c_A,       // coming adults - how many ???
             *w_leave_A,// adult waiting for leave from center
             *number_AC,  //  totally number  adult in center
             *c_plus_A,   //  Total number of process
             *w_number_in_C, // Child waiting to enter the center
             *number_CC;    // totally number child in center

*/
///FILE *sOUT;


#define CLEAN_CHILD do { sem_close(sem_mutex);\
                 sem_close(sem_pa);\
                 sem_close(sem_pc);\
                 sem_close(sem_gena);\
                 sem_close(sem_genc);\
                 sem_close(sem_inside);\
                 sem_close(sem_child_queue);\
                 sem_close(sem_child_adult_queue);\
                 sem_close(sem_wait_child);\
                 sem_close(sem_wait_adult);\
                 sem_close(sem_adult_queue);  } while (0)


#define CLOSE_SEM do {  sem_unlink(mutexName);\
                        sem_unlink(paName);\
                        sem_unlink(pcName);\
                        sem_unlink(genaName);\
                        sem_unlink(gencName);\
                        sem_unlink(insideName);\
                        sem_unlink(child_queueName);\
                        sem_unlink(wait_childName);\
                        sem_unlink(wait_adultName);\
                        sem_unlink(adult_queueName); } while (0)



void child(int Params);
//void child(params_t Params);
void adult(int Params);
void child(params_t Params);
void set_resources();

void clean_allocation();

//unsigned int ran_num(unsigned int max);
int check_args(int argc, char **argv);
 params_t  check_args(int argc, char *argv[]);

int check_args(int argc, char **argv);
int set_resources();
int clean_allocation();
void child(int num_child);
void adult(int num_adult);
#endif