#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_ARGS 20
#define MAX_CMDS 20

typedef struct { char *args; } command;

int get_args(char *cmdline, char *args[]) {
  int i = 0;
	if ((args[0] = strtok(cmdline, "\n\t ")) == NULL)
    return 0;
 while ((args[++i] = strtok(NULL, "\n\t ")) != NULL) {
    if (i >= MAX_ARGS) {
      printf("Too many arguments!\n");
      exit(1);
    }
  }

  return i;
}


int get_cmds(char *cmdline, command *cmds[]) {
  int i = 0;
  char *token;

  token = strtok(cmdline, "\n\t|");
	while (token != NULL) {
    cmds[i] = calloc(1, sizeof(command));
    cmds[i++]->args = token;
    token = strtok(NULL, "\n\t|");
  }
  return i;
}


void cleanCommands(command *cmds[], int ncmds) {
  int i;
  for (i = 0; i < ncmds; i++) {
    free(cmds[i]);
  }
}


void execute_child(char *cmd, char *args[], int fd[]) {
  int pid;
  
  switch (pid = fork()) {
  case 0:
    
    dup2(fd[1], 1);
    close(fd[0]);
    execvp(cmd, args);
    printf("Execlp failed running ls\n");
    break;
  case -1:
    printf("Fork failed\n");
    exit(1);
    break;
  default:
    break;
  }
}

int execute(command *cmds[], int ncmds) {
  pid_t pid;
  int child_status, argsc = 0, i = 0, j, fd[2], in = 0, inputStream,
                    outputStream;
  char *outfilename;
  char *infilename;


  while (i < ncmds) {
    if (pipe(fd) == -1) {
      printf("bad pipe%i\n", i);
      exit(1);
    }

    int wflag = 0, rflag = 0, aflag = 0, pipeflag = 0;
    char *command, *args[MAX_ARGS];

    argsc = get_args(cmds[i]->args, args);
	command = args[0];

    if (!strcmp(command, "quit") || !strcmp(command, "exit")) {
      exit(-1);
    }

    for (j = 0; j < argsc; j++) {

      if (!strcmp(args[j], ">")) {
        wflag = 1;
        outfilename = args[j + 1];

        args[j] = NULL;
        args[j++] = NULL;
        if (i != ncmds - 1)
          pipeflag = 1;
      } else
      
      if (!strcmp(args[j], "<")) {
        rflag = 1;
        infilename = args[j + 1];

        args[j] = NULL;
        args[j++] = NULL;
      } else

       if (!strcmp(args[j], ">>")) {
        aflag = 1;
        outfilename = args[j + 1];
       
        args[j] = NULL;
        args[j++] = NULL;
        if (i != ncmds - 1)
          pipeflag = 1;
      }
    }


   switch (pid = fork()) {
    case 0:

      if (in != 0) {
        dup2(in, 0);
        close(in);
      }

      if (rflag) {
        if (!(inputStream = open(infilename, O_RDONLY, 0644))) {
          printf("Error opening file\n");
          exit(1);
        }
        dup2(inputStream, 0);
        close(inputStream);
      }

      if (wflag) {
        if (!(outputStream =
                  open(outfilename, O_CREAT | O_TRUNC | O_WRONLY, 0644))) {
          printf("Error opening file\n");
          exit(1);
        }
        if (pipeflag)
          execute_child(command, args, fd);
        dup2(outputStream, 1);
        close(outputStream);
      } else

      
      if (aflag) {
        if (!(outputStream =
                  open(outfilename, O_CREAT | O_APPEND | O_WRONLY, 0666))) {
          printf("Error opening file\n");
          exit(1);
        }
        if (pipeflag)
          execute_child(command, args, fd);
        dup2(outputStream, 1);
        close(outputStream);
      } else

      
      if (i < ncmds - 1) {
        dup2(fd[1], 1);
        close(fd[1]);
      } 
      execvp(command, args);  
      printf("Wooah !! I don't know what '%s' means\n", command);
      exit(1);
      break;
   
    case -1:
      printf("Fork failed\n");
      exit(1);
      break;
    default:
      break;
    }
    close(fd[1]);
    in = fd[0];
    i++;
  }

   close(fd[1]);
  close(fd[0]);

  while ((pid = wait(&child_status)) != -1) {}

  return 0;
}


int analyzeCmds(char *cmdline) {
  command *cmds[MAX_CMDS];

  int ncmds = get_cmds(cmdline, cmds);
	if (ncmds <= 0)
    return -1;

  execute(cmds, ncmds);

  cleanCommands(cmds, ncmds);
  return 0;
}

int main(int argc, char *argv[]) {
  char cmdline[BUFSIZ];

  for (;;) {
    printf("➜ ~ ");
    if (fgets(cmdline, BUFSIZ, stdin) == NULL) {
      perror("fgets failed");
      exit(1);
    }

    if(analyzeCmds(cmdline) != 0){
      printf("No Commands\n");
    };
  }

  return 0;
}