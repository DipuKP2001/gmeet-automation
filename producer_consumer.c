#include <stdio.h>

#include <unistd.h>

#include <semaphore.h>

#include <pthread.h>



int x=0;

sem_t mutex,full,empty;

int wait(int n){

    return --n;

}



int signal(int n){

    return ++n;

}





void *producer(){

    while(1){

        if(x<10){

            sem_wait(&mutex);

            sem_post(&full);

            sem_wait(&empty);

            printf("Producer produces %d item\n",++x);

            sem_post(&mutex);

            sleep(1);

        }else{

            printf("Buffer is full!!\n");

            sleep(5);

        }

    }   

}



void *consumer(){

    while(1){

        if(x>0){

            sem_wait(&mutex);

            sem_post(&empty);

            sem_wait(&full);

            printf("Consumer consumes %d item\n",x--);

            sem_post(&mutex);

            sleep(3);

        }else{

            printf("Buffer is empty!!\n");

            sleep(1);

        }

    }

}



int main(){



    sem_init(&mutex,0,1);

    sem_init(&full,0,0);

    sem_init(&empty,0,10);



    pthread_t producer_thread,consumer_thread;

    pthread_create(&producer_thread,NULL,&producer,NULL);

    pthread_create(&consumer_thread,NULL,&consumer,NULL);

    pthread_join(producer_thread,NULL);

    pthread_join(consumer_thread,NULL);    

    return 0;



}