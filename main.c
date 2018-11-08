#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sighandler(int signo)
{
  if (signo == SIGINT)
  {
    printf("Found a SIGNIT. Gonna close now.\n");
    exit(0);
  }

  if (signo == SIGUSR1)
  {
    printf("My parent is: %d\n", getppid());
  }
}

int main()
{
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);

  while(1)
  {
    printf("My id is: %d\n", getpid());
    sleep(1);
  }

  return 0;
}
