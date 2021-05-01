#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_STUDENTS 20
#define N_STUDENTS 25

// officer = 0 é 'not here', = 1 é 'waiting' e = 2 é 'in the room'

volatile int students = 0; // quantos tem dentro
volatile int officer_state = 0; // 0, 1 ou 2

pthread_mutex_t sem_mutex; 

sem_t sem_turn; // não pode entrar
sem_t sem_clear; // vaza
sem_t sem_lie_in; // pode entrar


p_thread_officer(void *v) {
    pthread_mutex_lock(&sem_mutex);
    // Verifica se tem estudantes
    if (students > 0 && students < MAX_STUDENTS) {
    // Se tiver mais de um e menos de MAX_STUDENTS vai ficar esperando
        officer_state = 1;
        pthread_mutex_unlock(&sem_mutex);
        printf("Policial esperando...\n");
        sem_wait(&sem_lie_in);
    }

    else if (students >= MAX_STUDENTS) {
    // Se não tiver olha e vai embora
        officer_state = 2;
        // breakup();
        printf("Policial entrou no rolê e está esperando todos saírem.\n");
        sem_wait(&sem_turn);
        pthread_mutex_unlock(&sem_mutex);
        sem_wait(&sem_clear);
        printf("Agora podem entrar.\n");
        sem_post(&sem_turn);
    }

    else {
    // Se houver mais de MAX_STUDENTS entra e manda todo mundo embora
        // search ();
        printf("Policial fiscalizando...\n");
        sleep(1);
    }

    printf("Policial foi embora.\n");
    officer_state = 0;
    pthread_mutex_unlock(&sem_mutex);
}

p_thread_students(void *v) {
    pthread_mutex_lock(&sem_mutex);

    // Verifica se policial esta presente
    if (officer_state == 2){
        pthread_mutex_unlock(&sem_mutex);
        //  Testar começar festa e depois do guarda chegar, colocar mais pessoas e ver as pessoas bloqueadas
        printf("Estudantes não podem entrar. Polícia na área!\n");
        sem_wait(&sem_turn); 
        sem_post(&sem_turn);
        pthread_mutex_lock(&sem_mutex);
    }

    // Se estiver vai embora
    students += 1;
    printf("1 estudante entrou. Tem %d no rolê.\n", students);


    if (students == MAX_STUDENTS && officer_state == 1)
    {
        printf("A polícia está chegando!\n");
        sem_post(&sem_lie_in);
    }
    // and pass mutex to the officer
    else {
        pthread_mutex_unlock(&sem_mutex);
    }

    // Se não entra
    // party(); 
    sleep(1);

    pthread_mutex_lock(&sem_mutex);
    printf("1 estudante foi embora. Tem %d no rolê.\n", students);
    students -= 1;

    if (students == 0 && officer_state == 1)
    {
        sem_post(&sem_lie_in); // and pass mutex to the officer
    }
    else if (students == 0 && officer_state == 2){
        sem_post(&sem_clear); // and pass mutex to the officer
    }
    else {
        pthread_mutex_unlock(&sem_mutex);
    }
    
}

int main() {
    pthread_t thr_students[N_STUDENTS], thr_officer;

    // sem_init(&sem_mutex, 0, 1);
    sem_init(&sem_turn, 0, 1);
    sem_init(&sem_clear, 0, 0);
    sem_init(&sem_lie_in, 0, 0);

    for (int i = 0; i < N_STUDENTS; i++) {
        pthread_create(&thr_students[i], NULL, p_thread_students, NULL);
    }

    pthread_mutex_init(&sem_mutex, NULL);
    pthread_create(&thr_officer, NULL, p_thread_officer, NULL);

    for (int i = 0; i < N_STUDENTS; i++) 
        pthread_join(thr_students[i], NULL);

    pthread_mutex_destroy(&sem_mutex);

    return 0;
}