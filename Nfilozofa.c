#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define MAX 100

int broj_ruku[MAX], broj_stapica, filozof;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void uzmi_stapice(int broj){ 
   
   pthread_mutex_lock(&mutex);
   while(broj > broj_stapica) 
      pthread_cond_wait(&cond,&mutex); 
      int i = 0;
    for(i = 0; i < broj; ++i){
        sleep(1);
        printf("Filozof uzima svoj %d. stapic\n", i +1);
    }
   broj_stapica -= broj;
   pthread_mutex_unlock(&mutex); 
} 


void vrati_stapice(int broj){ 
   pthread_mutex_lock(&mutex); 
    broj_stapica += broj;
   pthread_cond_broadcast(&cond);
   pthread_mutex_unlock(&mutex); 
}  

void *Filozof(int *x){


        sleep(5);
        printf("%d. filozof pokusava uzet stapice\n", *x);

        int j = *x;
        uzmi_stapice(broj_ruku[j]);
        

        int i = 0;
        for(i = 0; i < 5; ++i){
            
            sleep(1);
            printf("%d. filozof jede\n", *x);
            printf("*\t*.\t*\n");
        }

        vrati_stapice(broj_ruku[j]);
        printf("%d. filozof misli\n", *x);

}

void prekid(void){

    printf("Filozofi napustaju stol, naglo uoci prekida\n");
    printf("Stol je prazan\n");
    exit(1);

}

int main(void){

    sigset(SIGINT, prekid);

    FILE *f;
    if((f = fopen("filozofi.txt", "r")) == NULL){
        printf("Problem u ucitavanju datoteke, izlazim\n");
        exit(0);
    }
    broj_stapica = 0;

    printf("Prosao\n");
    int j = 0;
    int n= 0;
    fscanf(f,"%d %d", &broj_stapica, &filozof);
   
    printf("Prosao\n");
    n = filozof;
    j = 0;
    while(n){
        fscanf(f, "%d", &broj_ruku[j]);
        ++j;
        --n;
    }

    pthread_t threadID[filozof];

    int i = 0;
    while (i < filozof){
        printf("Dolazi %d. filozof za stol\n", i + 1);
        pthread_create(threadID + i, NULL, Filozof, &i);
        ++i;
        sleep(1);

    }

    i = 0;
    while(i < filozof){

        printf("%d. filozof napusta stol\n", i + 1);
        pthread_join(threadID[i], NULL);
        ++i;
        sleep(2);

    }

    printf("Stol je prazan\n");
    return 0;
}
