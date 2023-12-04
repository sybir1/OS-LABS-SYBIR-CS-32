#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int shared_memory_id;
void *shared_memory_ptr;

void signal_handler(int sig);

void attach_shared_memory(char *shared_memory_id_str);

void register_signal_handler();

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Використання: %s <ідентифікатор_спільної_пам'яті>\n", argv[0]);
        return 1;
    }

    attach_shared_memory(argv[1]);
    register_signal_handler();

    while (1) {
        pause();
    }

    shmdt(shared_memory_ptr);
    return 0;
}

void signal_handler(int sig) {
    printf("\nПрограма 2 (дитина): обробник сигналу викликаний сигналом: %d\n", sig);
    if (sig == SIGUSR1) {
        int sum = 0, i = 0, val;
        printf("Програма 2 (дитина): Читання даних із спільної пам'яті...\n");

        do {
            memcpy(&val, shared_memory_ptr + i * sizeof(int), sizeof(int));
            if (val == 0) break;
            sum += val;
            i++;
        } while (1);

        printf("Програма 2 (дитина): Розрахована сума: %d\n", sum);

        memcpy(shared_memory_ptr, &sum, sizeof(int));

        kill(getppid(), SIGUSR1);
        printf("Програма 2 (дитина): Сигнал надіслано батькові\n");
    }
}

void attach_shared_memory(char *shared_memory_id_str) {
    shared_memory_id = atoi(shared_memory_id_str);
    printf("\nПрограма 2 (дитина): Отримано ідентифікатор спільної пам'яті: %d\n", shared_memory_id);
    shared_memory_ptr = shmat(shared_memory_id, NULL, 0);

    if (shared_memory_ptr == (void *) -1) {
        perror("Програма 2 (дитина): shmat");
        exit(1);
    } else {
        printf("Програма 2 (дитина): Спільна пам'ять приєднана за адресою: %p\n", shared_memory_ptr);
    }
}

void register_signal_handler() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigaction(SIGUSR1, &sa, NULL);
}
