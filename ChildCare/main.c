#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

#define ADULTS 5
#define CHILDREN 16

sem_t sem_child_number;

pthread_mutex_t mutex_adult;
pthread_mutex_t mutex_print;

volatile int adults = 0;
volatile int children = 0;

void show_chidren(int n_children) {
    char child[7][11];
    strcpy(child[0], "   _?_    ");
    strcpy(child[1], " _/. .\\_  ");
    strcpy(child[2], "(.\\_o_/.) ");
    strcpy(child[3], "(.`,.`'.')");
    strcpy(child[4], " ('.`,'`,)");
    strcpy(child[5], "  ('.`,'`)");
    strcpy(child[6], "   `--'\"` ");

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < n_children; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                printf("%c", child[i][k]);
            }
            printf(" ");
        }
        printf("\n");
    }
}

void show_adult() {
    char adult[9][17];
    strcpy(adult[0], "   ////^\\\\\\\\    ");
    strcpy(adult[1], "   | ^   ^ |    ");
    strcpy(adult[2], "  @ (o) (o) @   ");
    strcpy(adult[3], "   |   >   |    ");
    strcpy(adult[4], "   |  \\_/  |    ");
    strcpy(adult[5], "    \\_____/     ");
    strcpy(adult[6], "  ____|  |____  ");
    strcpy(adult[7], " /    \\__/    \\ ");
    strcpy(adult[8], "/              \\");

    for (int i = 0; i < 9; i++)
    {
        for (int k = 0; k < 16; k++)
        {
            printf("%c", adult[i][k]);
        }
        printf("\n");
    }
}

void show_childcare() {
    pthread_mutex_lock(&mutex_print);

    int aux = children;

    system("clear");
    printf("/------------- CRECHE DO PAPAI -------------/\n");
    while (aux > 0) {
        show_adult();
        if (aux > 3) 
            show_chidren(3);
        else
            show_chidren(aux);
        aux -= 3;
    }
    printf("/-------------------------------------------/\n\n\n");
    sleep(1);
    pthread_mutex_unlock(&mutex_print);
}

void *p_thread_adult(void *v) {
    adults++;
    show_childcare();
    sem_post(&sem_child_number);
    children++;
    show_childcare();
    sem_post(&sem_child_number);
    children++;
    show_childcare();
    sem_post(&sem_child_number);
    children++;
    show_childcare();

    pthread_mutex_lock(&mutex_adult);

    sleep(1);
    sem_wait(&sem_child_number);
    children--;
    show_childcare();


    sleep(1);
    sem_wait(&sem_child_number);
    children--;
    show_childcare();


    sleep(1);
    sem_wait(&sem_child_number);
    children--;
    show_childcare();

    pthread_mutex_unlock(&mutex_adult);
    adults--;
    show_childcare();
}

int main() {
    pthread_t thr_adults[ADULTS];

    sem_init(&sem_child_number, 0, 0);

    pthread_mutex_init(&mutex_adult, NULL);

    for (int i = 0; i < ADULTS; i++) {
        pthread_create(&thr_adults[i], NULL, p_thread_adult, NULL);
    }

    for (int i = 0; i < ADULTS; i++) {
        pthread_join(thr_adults[i], NULL);
    }

    pthread_mutex_destroy(&mutex_adult);

    return 0;
}