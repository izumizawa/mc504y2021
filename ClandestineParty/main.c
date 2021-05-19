#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

#define MAX_STUDENTS 20
#define N_STUDENTS 25

volatile int students = 0; 
volatile int officer_state = 0; // officer_state = 0 is 'not here', = 1 is 'waiting' and = 2 is 'in the room'
volatile int dance_position = 0;

pthread_mutex_t sem_mutex; 
pthread_mutex_t sem_print;

sem_t sem_turn; // não pode entrar na festa
sem_t sem_clear; // todos precisam ir embora
sem_t sem_lie_in; // podem entrar

void show_student(int n_students, int dance_position) {
    char dancer[10][3][5];
    strcpy(dancer[0][0], "  o  ");
    strcpy(dancer[0][1], " /|\\ ");
    strcpy(dancer[0][2], " / \\ ");
    strcpy(dancer[1][0], "\\ o /");
    strcpy(dancer[1][1], "  |    ");
    strcpy(dancer[1][2], " / \\ ");
    strcpy(dancer[2][0], " _ o ");
    strcpy(dancer[2][1], "  /\\ ");
    strcpy(dancer[2][2], " | \\ ");
    strcpy(dancer[3][0], "     ");
    strcpy(dancer[3][1], " __\\o");
    strcpy(dancer[3][2], "/)  |");
    strcpy(dancer[4][0], "__|  ");
    strcpy(dancer[4][1], "  \\o ");
    strcpy(dancer[4][2], "  ( \\");
    strcpy(dancer[5][0], " \\ / ");
    strcpy(dancer[5][1], "  |  ");
    strcpy(dancer[5][2], " /o\\ ");
    strcpy(dancer[6][0], "   |__");
    strcpy(dancer[6][1], " o/  ");
    strcpy(dancer[6][2], "/ )  ");
    strcpy(dancer[7][0], "     ");
    strcpy(dancer[7][1], "o/__ ");
    strcpy(dancer[7][2], "|  (\\");
    strcpy(dancer[8][0], " o _ ");
    strcpy(dancer[8][1], " /\\  ");
    strcpy(dancer[8][2], " / | ");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n_students; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                printf("%c", dancer[dance_position][i][k]);
            }
            printf(" ");
        }
        printf("\n");
    }
}

void show_officer() {
    if (officer_state == 0)
        return;

    char officer[3][11][15];
    strcpy(officer[0][0], "          ,    ");
    strcpy(officer[0][1], "     _.-\"` `'-.");
    strcpy(officer[0][2], "     '._ __{}_(");
    strcpy(officer[0][3], "       |'--.__\\");
    strcpy(officer[0][4], "      (   ^_\\^ ");
    strcpy(officer[0][5], "       |   3 | ");
    strcpy(officer[0][6], "       )\\___/  ");
    strcpy(officer[0][7], "   .--'`:._]   ");
    strcpy(officer[0][8], "  /  \\      '-.");
    strcpy(officer[0][9], "Aguardando uma ");
    strcpy(officer[0][10], "  baguncinha! ");

    strcpy(officer[1][0], "          ,    ");
    strcpy(officer[1][1], " __  _.-\"` `'-.");
    strcpy(officer[1][2], "/||\\'._ __{}_( ");
    strcpy(officer[1][3], "||||  |'--.__\\ ");
    strcpy(officer[1][4], "|  L.(   ^_\\^  ");
    strcpy(officer[1][5], "\\ .-' |   O |  ");
    strcpy(officer[1][6], "| |   )\\___/  ");
    strcpy(officer[1][7], "|  \\-'`:._]   ");
    strcpy(officer[1][8], "\\__/;      '-.");
    strcpy(officer[1][9], "A festa acabou!");
    strcpy(officer[1][10], "Todos pra fora!");

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            for (int k = 0; k < 15; k++)
            {
                printf("%c", officer[officer_state-1][i][k]);
            }
        }
        printf("\n");
    }

}

void show_gate() {
    printf("\n/----/----/----/----/----/        /----/----/----/----/----/\n\n");
}

void show_party() {
    /*
    |-----------------------------------------------------------------------|
    |    o   \ o /  _ o         __|    \ /     |__        o _  \ o /   o    |
    |   /|\    |     /\   ___\o   \o    |    o/    o/__   /\     |    /|\   |
    |   / \   / \   | \  /)  |    ( \  /o\  / )    |  (\  / |   / \   / \   |
    |-----------------------------------------------------------------------|
    */
    pthread_mutex_lock(&sem_print);
    int n_students = students;

    system("clear");
    if (officer_state == 2)
        show_gate();
    show_officer();
    if (officer_state <= 1)
        show_gate();

    while (n_students > 0) {
        if (n_students > 10)
            show_student(10, dance_position);
        else
            show_student(n_students, dance_position);
        n_students -= 10;
    }

    dance_position += 1;
    dance_position = dance_position%9;
    sleep(1);
    pthread_mutex_unlock(&sem_print);
}

void *p_thread_officer(void *v) {
    pthread_mutex_lock(&sem_mutex);

    if (students > 0 && students < MAX_STUDENTS) {
        officer_state = 1;
        show_party();
        pthread_mutex_unlock(&sem_mutex);
        sem_wait(&sem_lie_in);
    }
    if (students >= MAX_STUDENTS) {
        officer_state = 2;
        show_party();
        sem_wait(&sem_turn);
        pthread_mutex_unlock(&sem_mutex);
        sem_wait(&sem_clear);
        sem_post(&sem_turn);
    }
    else {
        officer_state = 2;
        show_party();
        sleep(1);
    }

    officer_state = 0;
    show_party();
    pthread_mutex_unlock(&sem_mutex);
}

void *p_thread_students(void *v) {
    pthread_mutex_lock(&sem_mutex);

    if (officer_state == 2){
        show_party();
        pthread_mutex_unlock(&sem_mutex);
        sem_wait(&sem_turn); 
        sem_post(&sem_turn);
        pthread_mutex_lock(&sem_mutex);
    }

    students += 1;
    show_party();

    if (students == MAX_STUDENTS && officer_state == 1)
    {
        sem_post(&sem_lie_in);
    }
    else {
        pthread_mutex_unlock(&sem_mutex);
    }

    sleep(1);

    pthread_mutex_lock(&sem_mutex);
    students -= 1;
    show_party();

    if (students == 0 && officer_state == 1)
    {
        sem_post(&sem_lie_in);
    }
    else if (students == 0 && officer_state == 2){
        sem_post(&sem_clear);
    }
    else {
        pthread_mutex_unlock(&sem_mutex);
    }
    
}

int main() {
    pthread_t thr_students[N_STUDENTS], thr_officer;

    sem_init(&sem_turn, 0, 1);
    sem_init(&sem_clear, 0, 0);
    sem_init(&sem_lie_in, 0, 0);
    pthread_mutex_init(&sem_print, NULL);
    // pthread_mutex_init(&sem_mutex, NULL);
    // pthread_create(&thr_officer, NULL, p_thread_officer, NULL);

    pthread_mutex_init(&sem_mutex, NULL);
    for (int i = 0; i < N_STUDENTS; i++) {
        pthread_create(&thr_students[i], NULL, p_thread_students, NULL);
        if (i == 15) {
            pthread_create(&thr_officer, NULL, p_thread_officer, NULL);
        }
    }

    // pthread_mutex_init(&sem_mutex, NULL);
    // pthread_create(&thr_officer, NULL, p_thread_officer, NULL);

    for (int i = 0; i < N_STUDENTS; i++) 
        pthread_join(thr_students[i], NULL);

    pthread_mutex_destroy(&sem_mutex);

    return 0;
}