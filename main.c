#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

pid_t caffeinate_pid = -1;

void start_caffeinate() {
  caffeinate_pid = fork();

  if (caffeinate_pid == -1) {
    perror("fork failed");
    exit(1);
  }

  if (caffeinate_pid == 0) {
    // Child process: run caffeinate
    execlp("caffeinate", "caffeinate", "-d", NULL);
    perror("execlp failed");
    exit(1);
  }

  printf("[INFO] caffeinate started with PID %d\n", caffeinate_pid);
}

void stop_caffeinate() {
  if (caffeinate_pid > 0) {
    kill(caffeinate_pid, SIGTERM); // or SIGKILL
    printf("[INFO] caffeinate stopped\n");
  }
}

int main() {

  start_caffeinate();
  int i = 1;
  while (i < 11) {
    printf("ROUND %d\n", i);
    system("say exercise");
    sleep(39);
    if (i == 10) {
      system("say complete");
      break;
    }
    system("say rest");
    sleep(19);
    i++;
  }
  stop_caffeinate();
}
