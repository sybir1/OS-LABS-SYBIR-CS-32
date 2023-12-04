#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

void acquire_semaphore(int sem_id) {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = SEM_UNDO;
    if (semop(sem_id, &op, 1) == -1) {
        perror("acquire_semaphore failed");
        exit(EXIT_FAILURE);
    }
}

void release_semaphore(int sem_id) {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = SEM_UNDO;
    if (semop(sem_id, &op, 1) == -1) {
        perror("release_semaphore failed");
        exit(EXIT_FAILURE);
    }
}

int shm_id;
void *shm_ptr;
int sem_id;

void signal_handler(int sig) {
    printf("Клієнт: Обробник сигналу отримав сигнал %d\n", sig);
    if (sig == SIGUSR1) {
        int sum = 0, i = 0, val;

        printf("Клієнт: Блокування семафору перед читанням даних...\n");
        acquire_semaphore(sem_id);

        do {
            memcpy(&val, (int *)shm_ptr + i, sizeof(int));
            if (val == 0) break;
            sum += val;
            i++;
        } while (1);

        memcpy(shm_ptr, &sum, sizeof(int));

        printf("Клієнт: Звільнення семафору після читання...\n");
        release_semaphore(sem_id);
        printf("Клієнт: Відправка сигналу назад на сервер...\n");
        kill(getppid(), SIGUSR1);
    }
}

void connect_shared_memory_and_semaphore(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Використання: %s <shm_id> <sem_id>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Клієнт: Підключення до спільної пам'яті...\n");
    shm_id = atoi(argv[1]);
    sem_id = atoi(argv[2]);

    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Клієнт: Підключення до семафору...\n");
    signal(SIGUSR1, signal_handler);
}

void run_client() {
    while (1) {
        pause();
    }
}

int main(int argc, char *argv[]) {
    connect_shared_memory_and_semaphore(argc, argv);
    run_client();
    shmdt(shm_ptr);
    return 0;
}
