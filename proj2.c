#include "proj2.h"


sem_t
    *sem_adult,
    *sem_child,
    *sem_mutex,
    *sem_all_leave,
    *sem_wait_child,
    *sem_wait_adult;

FILE *out;





int counter, A, C, AGT, CGT, AWT, CWT;
int *orderA, *orderB, *orderC, *orderD, *orderE, *orderF, *orderG;



int orderGID, orderFID, orderEID, orderDID, orderCID, orderBID, orderAID;






void adult(int num_adult)
{
  sem_wait(sem_mutex);
        fprintf(out,"%d\t: A %d\t: started\n", ++(*orderC), num_adult);
    sem_post(sem_mutex);

    sem_wait(sem_mutex);
        fprintf(out,"%d\t: A %d\t: enter\n", ++(*orderC), num_adult);
        (*orderE)--;
        (*orderA)++;
        if (*orderD)
        {
            int n = (3 < (*orderD)) ? 3 : (*orderD); 
            for (int i = 0; i < n; i++)
            {
                sem_post(sem_child);
            }
            (*orderD) -= n;
            (*orderB) += n;

            sem_post(sem_mutex);

            for (int i = 0; i < n; i++)
            {               
                sem_wait(sem_wait_child);
            }

            sem_wait(sem_mutex);
        }
    sem_post(sem_mutex);


    
    if (AWT)
    {
        usleep((random() % AWT) * 1000);
    }

    sem_wait(sem_mutex);
        fprintf(out,"%d\t: A %d\t: trying to leave\n", ++(*orderC), num_adult);

        if (*orderB <= ((*orderA) - 1) * 3)
        {
            (*orderA)--;
            fprintf(out,"%d\t: A %d\t: leave\n", ++(*orderC), num_adult);
            sem_post(sem_mutex);
        }
        else
        {
            fprintf(out,"%d\t: A %d\t: waiting:\t%d: %d\n", ++(*orderC), num_adult, *orderA, *orderB);
            (*orderF)++;
            sem_post(sem_mutex);
            sem_wait(sem_adult); 
            sem_wait(sem_mutex);
            fprintf(out,"%d\t: A %d\t: leave\n", ++(*orderC), num_adult);
            sem_post(sem_mutex);
            sem_post(sem_wait_adult); 
        }

        sem_wait(sem_mutex);
            if ((*orderE) == 0) 
            {
                for (int i = 0; i < C; i++)
                {
                    sem_post(sem_child);
                }
            }

            sem_post(sem_mutex);

        sem_wait(sem_mutex);
        (*orderG)++;
        if (*orderG == A + C )
        {
            sem_post(sem_all_leave);
        }

    sem_post(sem_mutex);

    sem_wait(sem_all_leave);
    sem_post(sem_all_leave);

    sem_wait(sem_mutex);
        fprintf(out,"%d\t: A %d\t: finished\n", ++(*orderC), num_adult);
    sem_post(sem_mutex);
}




void child(int num_child)
{
    sem_wait(sem_mutex);
        fprintf(out,"%d\t: C %d\t: started\n", ++(*orderC), num_child);

        if ((*orderB) < (3 * (*orderA)))
        {
            (*orderB)++;
            fprintf(out,"%d\t: C %d\t: enter\n", ++(*orderC), num_child);
            sem_post(sem_mutex);
        }
        else
        {
            (*orderD)++;
            if(*orderE) 
            {
                fprintf(out,"%d\t: C %d\t: waiting:\t%d: %d\n", ++(*orderC), num_child, *orderA, *orderB);
            }
            sem_post(sem_mutex);
            if (A)
            {
                sem_wait(sem_child); 
            }
            sem_wait(sem_mutex);
                sem_post(sem_wait_child);
                fprintf(out,"%d\t: C %d\t: enter\n", ++(*orderC), num_child);
            sem_post(sem_mutex);
        }


    if (CWT) 
    {
        usleep((random() % AWT) * 1000);
    }

    sem_wait(sem_mutex);
        fprintf(out,"%d\t: C %d\t: trying to leave\n", ++(*orderC), num_child);
        fprintf(out,"%d\t: C %d\t: leave\n", ++(*orderC), num_child);
        (*orderB)--;

        if ((*orderB <= ((*orderA) - 1) * 3) && (*orderF)) 
        {
            (*orderF)--;
            (*orderA)--;
                sem_post(sem_adult);
                sem_post(sem_mutex);
                sem_wait(sem_wait_adult);
                sem_wait(sem_mutex);
        }

        if ((++(*orderG)) == A + C)
        {
            sem_post(sem_all_leave);
        }
    sem_post(sem_mutex);

    sem_wait(sem_all_leave);
    sem_post(sem_all_leave);

    sem_wait(sem_mutex);
        fprintf(out,"%d\t: C %d\t: finished\n", ++(*orderC), num_child);
    sem_post(sem_mutex);
}








int check_args(int argc, char **argv)
{
               
    /*
    if(argc != 7)
    {
       // Params.errorState = E_BADPARAMS;
       // return Params;
       return -1;
    }
    long check;
    char *ptrError;
    // Argument  0 < A < MAX_UINT
    check = strtol(argv[1], &ptrError, 10);
        if (!(check > 0 || check < UINT_MAX))
    {


            return -1;
        }

    A = (int) check;
    if(!(A > 0 && *ptrError == '\0'))
         {
            return -1;
         }

         // Arguments  0 < C < UINT_MAX
    check= strtol(argv[2], &ptrError, 10);
     if (!(check > 0 || check < UINT_MAX))
    {
       return -1;
    }
    C = (int) check;
        if(!(C > 0 && *ptrError == '\0'))
        {
            return -1;
        }


    // Arguments  0 <= AGT < 5001

        check = strtol(argv[3], &ptrError, 10);
            if(!(check > 0 || check < UINT_MAX))
            {
                return -1;
            }
        AGT = (int) check;
            if(!(AGT <= 5001  && *ptrError == '0'))
            {
                return -1;
            }
        check = strtol(argv[4], &ptrError, 10);
            if(!(check > 0 || check < UINT_MAX))
            {
               return -1;
            }
        CGT = (int) check;
            if(!(CGT <= 5001 && *ptrError == '\0'))
            {

                return -1;
            }

        check = strtol(argv[5], &ptrError, 10);
            if (!(check > 0 || check < UINT_MAX))
            {
                return -1;
            }
        AWT = (int) check;
         if(AWT >= 5001 && *ptrError == '\0')
         {
             return -1;
         }




        check = strtol(argv[6], &ptrError, 10);
           if (!(check > 0 || check < UINT_MAX))
            {
                return -1;
            }

        CWT = (int) check;
            if(CWT >= 5001 && *ptrError == '\0')
            {
                return -1;
            }
    return 0;
}*/
    
    if (argc != 7)      
    {
        
        return -1;
    }

    for (int i = 1; i < 7; i++) 
    {
        for (unsigned j = 0; j < strlen(argv[i]); j++)
        {
            if (!isdigit(argv[i][j]))
            {
                return -1;
            }
        }
        switch (i)
        {
            case 1: A = atoi(argv[i]); break;
            case 2: C = atoi(argv[i]); break;
            case 4: CGT = atoi(argv[i]); break;
            case 3: AGT = atoi(argv[i]); break;
            case 5: AWT = atoi(argv[i]); break;
            case 6: CWT = atoi(argv[i]); break;
        }
    }

    
    if(!(AGT >= 0 && AGT < 5001) || !(CGT >= 0 && CGT < 5001) || !(AWT >= 0 && AWT < 5001) || !(CWT >= 0 && CWT < 5001) || A < 0 || C < 0)
    {
        return -1;
    }

    return 0;
}







int set_resources()
{
    /// shared variables
    if ((orderAID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }
    if ((orderBID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderDID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderEID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderAID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderFID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderGID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderA = (int *) shmat(orderAID, NULL, 0)) == NULL)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderB = (int *) shmat(orderBID, NULL, 0)) == NULL)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderC = (int *) shmat(orderDID, NULL, 0)) == NULL)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderD = (int *) shmat(orderEID, NULL, 0)) == NULL)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if ((orderE = (int *) shmat(orderAID, NULL, 0)) == NULL)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }
    if ((orderF = (int *) shmat(orderFID, NULL, 0)) == NULL)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }
    if ((orderG = (int *) shmat(orderGID, NULL, 0)) == NULL)
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }
    

        (*orderD) = 0;
        (*orderC) = 0;
        (*orderA) = 0;
        (*orderB) = 0;
        (*orderF) = 0;
        (*orderG) = 0;

   

   sem_mutex = sem_open("/xabduk001", O_CREAT | O_EXCL, 0666, 1);


   sem_adult = sem_open("/xabduk002", O_CREAT | O_EXCL, 0666, 0);


   sem_child = sem_open("/xabduk003", O_CREAT | O_EXCL, 0666, 0);

   sem_all_leave = sem_open("/xabduk004", O_CREAT | O_EXCL, 0666, 0);
  

    sem_wait_child = sem_open("/xabduk005", O_CREAT | O_EXCL, 0666, 0);
    

    sem_wait_adult = sem_open("/xabduk006", O_CREAT | O_EXCL, 0666, 0);

        if(sem_mutex == SEM_FAILED || sem_adult == SEM_FAILED || sem_child == SEM_FAILED || sem_all_leave == SEM_FAILED || sem_wait_child == SEM_FAILED || sem_wait_adult == SEM_FAILED)
    {
        fprintf(stderr, "ERROR!\n");
        return -1;
    }
        



    out = fopen("NAME", "w");
    if (!out)
    {
        fprintf(stderr, "ERROR: could not open out.\n");
        return 2;
    }
    (*orderE) = A;
    counter = 0;

    return 0;
}





int clean_allocation()
{
  
   
      if (sem_close(sem_mutex))
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }
    if (sem_close(sem_child))
    {
        fprintf(stderr, "\n");
        return -1;
    }
    if (sem_close(sem_all_leave))
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }
    if (sem_close(sem_adult))
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }
    if (sem_close(sem_wait_child))
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }

    if (sem_close(sem_wait_adult))
    {
        fprintf(stderr, "ERROR\n");
        return -1;
    }


    sem_unlink("/xabduk001");
    sem_unlink("/xabduk002");
    sem_unlink("/xabduk003");
    sem_unlink("/xabduk004");
    sem_unlink("/xabduk005");
    sem_unlink("/xabduk006");
    

    shmctl( orderEID, IPC_RMID, NULL);
    shmctl( orderAID, IPC_RMID, NULL);
    shmctl( orderDID, IPC_RMID, NULL);
    shmctl( orderBID, IPC_RMID, NULL);
    shmctl( orderAID, IPC_RMID, NULL);
    shmctl( orderFID, IPC_RMID, NULL);
    shmctl( orderGID, IPC_RMID, NULL);

    return 0;
        
 }  












int main(int argc, char **argv)
{
    
    srandom(time(0)); 

    
    if(check_args(argc, argv) == -1)
    {
        printf("Error: Wrong number of parameters\n");
        return 1;
    }

   
    if (set_resources() != 0)
    {
        return 2;
    }
   setbuf(stderr, NULL);
    setbuf(stdout, NULL);
    setbuf(out, NULL);

    pid_t process_child = fork();

    if (process_child == 0) 
    {
        for (int i = 0; i < C; i++) 
        {
            if (CGT)
            {
                usleep((random() % CGT) * 1000);
            }

            pid_t process_ID = fork();
            int num_child = i + 1;
            
            
            if (process_ID == 0)
            {
                child(num_child);
                exit(0);
            }
            else if (process_ID < 0)
            {
                fprintf(stderr, "ERROR: Could not create process child.\n");
                return 2;
            }
        }

       
        for (int i = 0; i < C; i++)
        {
            wait(NULL);

        exit(0); 
        }
    }
    else if (process_child < 0)
    {
        fprintf(stderr, "ERROR: Could not create process.\n");
        return 2;
    }

    pid_t adult_Pid = fork();

    if (adult_Pid == 0) 
    {

        for (int i = 0; i < A; i++) 
        {
            if (AGT) 
            {
                usleep((random() % AGT) * 1000);
            }

            pid_t process_adult_Pid = fork();
            int num_adult = i + 1; 
            
            
            if (process_adult_Pid == 0)
            {
                adult(num_adult);
                exit(0);
            }
            else if (process_adult_Pid < 0)
            {
                fprintf(stderr, "ERROR: Could not create process adult.\n");
                return 2;
            }
        }
        
        for (int i = 0; i < A; i++)
        {
            wait(NULL);

            exit(0); 
        }
    }
    else if (process_child < 0)
    {
        fprintf(stderr, "ERROR: Could not create process.\n");
        return 2;
    }

// main process //

    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }
        clean_allocation();
        fclose(out);
    

return 0;
}