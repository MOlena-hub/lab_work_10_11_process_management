#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Помилка при створенні процесу
        perror("Fork failed");
        return 1;
    } 

    if (pid == 0) {
        // Це код ДОЧІРНЬОГО процесу
        printf("[CHILD]: Мій PID: %d. Завершую роботу з кодом 7...\n", getpid());
        exit(7); 
    } else {
        // Це код БАТЬКІВСЬКОГО процесу
        int status;
        printf("[PARENT]: Чекаю на завершення дочірнього процесу (PID: %d)...\n", pid);

        // Очікуємо на завершення конкретного процесу
        wait(&status);

        // Перевіряємо, чи процес завершився нормально
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("[PARENT]: Дочірній процес завершився. Код повернення: %d\n", exit_code);
        } else {
            printf("[PARENT]: Процес завершився аномально.\n");
        }
    }

    return 0;
}
