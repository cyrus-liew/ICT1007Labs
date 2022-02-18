#include <pthread.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

#define BUFFER_SIZE 5

//Globals
bool run = true;
int counter = 0, in = 0, out = 0;
int buffer[BUFFER_SIZE];

pthread_mutex_t mutex;

int randomNum(){
    return rand() % 999 + 1;
}

int randSlp(){
    return rand() % 3 + 1;
}

void *pro_func(void *id){
    long pid = (long) id + 1;
    while(true){

        if(!run){
            pthread_exit(NULL);
        }

        sleep(randSlp());   
        
        pthread_mutex_lock(&mutex);
        if(counter != BUFFER_SIZE){
            buffer[in] = randomNum();
            printf("Producer%ld inserted item %d\n", pid, buffer[in]);
            in = (in + 1) % BUFFER_SIZE;
            counter++;
            //printf("%d\n", counter); 
        }
        pthread_mutex_unlock(&mutex);
    }    
}

void *con_func(void *id){
    int consume;
    long cid = (long) id + 1;
    while(true){

        if(!run){
            pthread_exit(NULL);
        }

        sleep(randSlp());

        pthread_mutex_lock(&mutex);
        if(in > 0){
            consume = buffer[in - 1];
            printf("Consumer%ld removed item\t\t %d\n", cid, buffer[in - 1]);
            in--;
            //out = (out + 1) % BUFFER_SIZE;
            counter--;
            //printf("%d\n", counter);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char *argv[]){

    srand(time(0));
    long i;
    int x, pro_id, con_id;
    long thread_arg, conv;
    long int arr[2];
    char *p;

    if(argc != 4){
        printf("Enter 3 arguments.\n");

        return 0;
    }
    else{
        for(i = 1; i <= 3; i++){
            errno = 0;
            conv =  strtol(argv[i], &p, 10);
            if(errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN){
                printf("Enter three integers.\n");

                return 0;
            }
            else{
                arr[i - 1] = conv;
            }
            
        }
    }

    int sleeptimer= arr[0];
    int no_pro = arr[1];
    int no_con = arr[2];

    printf("Number of arguments = %d\n" , argc - 1);
    printf("Main Process sleep time = %d\n", sleeptimer);
    printf("Number of producer(s) = %d\n", no_pro);
    printf("Number of consumer(s) = %d\n", no_con);

    pthread_t pro_threads[no_pro];
    pthread_t con_threads[no_con];

    for(i = 0; i < no_pro; i++){
        pro_id = pthread_create(&pro_threads[i], NULL, &pro_func, (void *)i);
        if(pro_id == 0){
            printf("Producer%ld thread created successfully\n", i+1);
        }
    }
    
    for(i = 0; i < no_con; i++){
        con_id = pthread_create(&con_threads[i], NULL, &con_func, (void *)i);
        if(con_id == 0){
            printf("Consumer%ld thread created successfully\n", i+1);
        }
    }

    sleep(sleeptimer);
    run = false;

    for(x = 0; x < no_pro; x++){
        pthread_join(pro_threads[x], NULL);
    }
    for(x = 0; x < no_con; x++){
        pthread_join(con_threads[x], NULL);
    }  

    printf("Sleep time elapsed. Producers and Consumers terminated\n");
    printf("Number of remaining items on buffer = %d\n" , counter);

    pthread_exit(NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}