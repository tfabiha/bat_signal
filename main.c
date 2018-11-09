#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static void sighandler(int signo)
{
  if (signo == SIGINT)
  {
    printf("Found a SIGNIT. Gonna close now.");

    int fd = open("errors.txt", O_CREAT | O_EXCL | O_WRONLY, 0777);
    //printf("%d\n", fd);
    //printf("%d: %s\n", errno, strerror(errno));

    if (fd < 0)
    {
      fd = open("errors.txt", O_WRONLY | O_APPEND);
    }

    //lseek(fd, 0, SEEK_END);

    char str[25] = "Sigint found in %d\n";
    sprintf(&str, "%d", getpid());
    int yes = write(fd, &str, 15);
    close(fd);
    //printf("%d", yes);
    //printf("%d: %s\n", errno, strerror(errno));

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
