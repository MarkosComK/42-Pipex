<h1 align="center">
	📖 Pipex
</h1>

![pipex](https://github.com/user-attachments/assets/df89053b-44ad-4ba2-b8c7-b883ee7a9dbc)

<p align="center">
	<b><i>Development repo for 42cursus Pipex project</i></b><br>
	For further information about 42cursus and its projects, please refer to <a href="https://github.com/MarkosComK/42-Common-Core-Guide"><b>42-Common-Core-Guide repo</b></a>.
</p>


<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#-index">Index</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-testing">Testing</a>
</h3>

---
<br>
<div align="center">
	<img src="https://github.com/MarkosComK/42-Libft/assets/67120870/10a2a298-340e-4a67-96bd-d97716a60526">
</div>

## This is a project in daily use. If you want to see the project that i have been evaluated in 42school click in releases at the right side!

## 🗣️ About

> Pipex is a project that re-creates in C the way two commands are piped together via `|` in the shell

<br>

<p align="center">
	<b><i>Reproduction of shell pipes</i></b><br>
</p>


# The beginning

To understand how to re-create the pipe used in shell we must understand the usage of those functions

- fork( )
- pipe( )
- dup2( )
- execve( )


i will give you a small starting point of each of them them at the very end of this file you find resources not just for those functions but for the whole project.

#

## The fork( ) function

Understanding fork( )

The fork( ) function in C is a system call that <strong>creates a new process</strong>, which is a copy of the current process. This new process is called a child process, and the original process is the parent process.

### How it works

When fork() is called, two things happen:

    A new process is created: The operating system creates a copy of the parent process, including its memory space, open files, and other resources.
    Return value: The fork() function returns a value to both the parent and child processes:

    - In the parent process, fork() returns the process ID (PID) of the child process.
    - In the child process, fork() returns 0.   

Here is an example.

```C
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        return (1);
    } 
    else if (pid == 0)
    {
        // Child process
        printf("I am the child process\n");
    } 
    else
    {
        // Parent process
        printf("I am the parent process\n");
    }

    return  
 0;
}
```
<p>Don not forget to test every example so you can understand what is going on</p>

## Understanding the pipe ( ) function

The pipe() function in C is a system call used for inter-process communication (IPC). It creates a unidirectional communication channel between two processes. Data written to one end of the pipe can be read from the other end. That mean you can create a connection between those two processes using pipe(here is where the magic happens).

### How it works

    Creation:
        pipe() takes an array of two integers as input.
        It creates a pipe and stores file descriptors for the read and write ends of the pipe in the first and second elements of the array respectively.
        Returns 0 on success, -1 on failure.

    Reading and Writing:
        The process that holds the write end can write data to the pipe using write().
        The process that holds the read end can read data from the pipe using read().
        The pipe has a limited buffer size. If a process writes more data than the buffer can hold, the write operation blocks until space is available.
        If a process tries to read from an empty pipe, the read operation blocks until data is available.

Heres a example code. If you do not understand yet, dont worry. The next snippet will make more sense, but yet, test this one.

```C
#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    char buffer[1024];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) { // Child process
        close(pipefd[0]); // Close the read end
        write(pipefd[1], "Hello from child\n", 14);
        close(pipefd[1]);
    } else { // Parent process
        close(pipefd[1]); // Close the write end
        read(pipefd[0], buffer, 1024);
        printf("Parent received: %s", buffer);
        close(pipefd[0]);
    }

    return 0;
}
```

````
# ./pipex infile cmd1 cmd2 outfile
pipe()
 |
 |-- fork()
      |
      |-- child // cmd1
      :     |--dup2()
      :     |--close end[0]
      :     |--execve(cmd1)
      :
      |-- parent // cmd2
            |--dup2()
            |--close end[1]
            |--execve(cmd2)
 
# pipe() sends the output of the first execve() as input to the second execve()
# fork() runs two processes (i.e. two commands) in one single program
# dup2() swaps our files with stdin and stdout
 ````
## Setting the pipe

````
void    pipex(int f1, int f2)
{
    int end[2];    pipe(end);
}

# pipe() takes an array of two int, and links them together
# what is done in end[0] is visible to end[1], and vice versa
# pipe() assigns an fd to each end
# Fds are file descriptors
# since files can be read and written to, by getting an fd each, the two ends can communicate
# end[1] will write to the its own fd, and end[0] will read end[1]’s fd and write to its own

````
## Forking the processes

````
void    pipex(int f1, int f2)
{
    int   end[2];
    pid_t parent;    pipe(end);
    parent = fork();
    if (parent < 0)
         return (perror("Fork: "));
    if (!parent) // if fork() returns 0, we are in the child process
        child_process(f1, cmd1);
    else
        parent_process(f2, cmd2);
}

# fork() splits the process in two sub-processes -> parallel, simultaneous, happen at the same time
# it returns 0 for the child process, a non-zero for the parent process, -1 in case of error
````
end[1] is the child process, end[0] the parent process; the child writes, the parent reads  
Since for something to be read, it must be written first, so cmd1 will be executed by the child, and cmd2 by the parent.  

## FDs
pipex is run like this ./pipex infile cmd1 cmd2 outfile  
FDs 0, 1 and 2 are by default assigned to stdin, stdout and stderr  
`infile`, `outfile`, the pipe, the `stdin` and `stdout` are all FDs  
On linux, you can check your fds currently open with the command ls -la /proc/$$/fd  

Our fd table right now looks like this:
````
                           -----------------    
                 0         |     stdin     |  
                           -----------------    
                 1         |     stdout    |    
                           -----------------    
                 2         |     stderr    |  
                           -----------------
                 3         |     infile    |  // open()
                           -----------------
                 4         |     outfile   |  // open()
                           -----------------
                 5         |     end[0]    | 
                           -----------------
                 6         |     end[1]    |  
                           -----------------
````
## Swapping fds with dup2()

For the child process, we want infile to be our stdin (as input), and end[1] to be our stdout (we write to end[1] the output of cmd1)  
In the parent process, we want end[0] to be our stdin (end[0] reads from end[1] the output of cmd1), and outfile to be our stdout (we write to it the output of cmd2)  
Visually,
````
// each cmd needs a stdin (input) and returns an output (to stdout)
   
    infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2            
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2           
                     |                       |
            cmd1   |---------------------------|  end[0]
           output                             reads end[1]
         is written                          and sends cmd1
          to end[1]                          output to cmd2
       (end[1] becomes                      (end[0] becomes 
        cmd1 stdout)                           cmd2 stdin)

````
We swap fds to stdin/stdout with dup2()  
From the MAN, 
````
int dup2(int fd1, int fd2) : it will close fd2 and duplicate the value of fd2 to fd1
else said, it will redirect fd1 to fd2
````
In pseudo code:
````
# child_process(f1, cmd1); // add protection if dup2() < 0
// dup2 close stdin, f1 becomes the new stdin
dup2(f1, STDIN_FILENO); // we want f1 to be execve() input
dup2(end[1], STDOUT_FILENO); // we want end[1] to be execve() stdout
close(end[0]) # --> always close the end of the pipe you don't use,
                    as long as the pipe is open, the other end will 
                    be waiting for some kind of input and will not
                    be able to finish its process
close(f1)
// execve function for each possible path (see below)
exit(EXIT_FAILURE);
````
Parent process in pseudo code will be similar  
It needs a `waitpid()` at the very beginning to wait for the child to finish her process  
````
# parent_process(f2, cmd2);
int status;
waitpid(-1, &status, 0);
dup2(f2, ...); // f2 is the stdout
dup2(end[0], ...); // end[0] is the stdin
close(end[1])
close(f2);
// execve function for each possible path (see below)
exit(EXIT_FAILURE);
````
## Executing with execve()

From the MAN,
````
int execve(const char *path, char *const argv[], char *envp[]);

# path: the path to our command
# type `which ls` and `which wc` in your terminal
# you'll see the exact path to the commands' binaries

# argv[]: the args the command needs, for ex. `ls -la`
# you can use your ft_split to obtain a char **
# like this { "ls", "-la", NULL }
# it must be null terminated

# envp: environmental variable -> retrieved from main (see below)
# in envp the line PATH contains all possible paths to the commands' binaries
# type env in the terminal to have a look
# split on : to retrieve all possible PATHs 

int main(int ac, char **ag, char **envp)
{
     int f1;
     int f2;
     f1 = open(ag[1], O_RDONLY);
     f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
     if (f1 < 0 || f2 < 0)
          return (-1);
     pipex(f1, f2, ag, envp);
     return (0);
}
````
`execve()` will try every possible path to the cmd until it finds the good one  
If the command does not exist, `execve()` will do nothing and return -1;  
else, it will execute the cmd and delete all ongoing processes (so no leaks)  

In pseudo code,
````
// parsing (somewhere in your code) char *PATH_from_envp;
char **mypaths;
char **mycmdargs; // retrieve the line PATH from envp

PATH_from_envp = ft_substr(envp ....);
mypaths = ft_split(PATH_from_envp, ":");
mycmdargs = ft_split(ag[2], " ");// in your child or parent process
int  i;
char *cmd;

i = -1;
while (mypaths[++i])
{
    cmd = ft_join(mypaths[i], ag[2]); // protect your ft_join
    execve(cmd, mycmdargs, envp); // if execve succeeds, it exits
    // perror("Error"); <- add perror to debug
    free(cmd) // if execve fails, we free and we try a new path
}
return (EXIT_FAILURE);
````
## Creating a pipe with two child processes

````
void    pipex(int f1, int f2, char *cmd1, char *cmd 2)
{
    int   end[2];
    int   status;
    pid_t child1;
    pid_t child2;    pipe(end);
    child1 = fork();
    if (child1 < 0)
         return (perror("Fork: "));
    if (child1 == 0)
        child_one(f1, cmd1);
    child2 = fork();
    if (child2 < 0)
         return (perror("Fork: "));
    if (child2 == 0)
        child_two(f2, cmd2);
    close(end[0]);         // this is the parent
    close(end[1]);         // doing nothing
    waitpid(child1, &status, 0);  // supervising the children
    waitpid(child2, &status, 0);  // while they finish their tasks
}
````
## Using access()

If the command that does not exist, execve() will execute nothing without error messages  
You need to check if the command exists before its execution with `access()`, else send an error `pipex: weirdcmd: weirdcmd not found`  

## Debugging

[0] When splitting the env, print out the result of split. Add a `/` at the end for the path to work correctly.

[1] If the program gets stuck without executing anything, most probably the pipe ends are not closed correctly.
Until one end is open, the other will be waiting for input and its process will not finish.

[2] Place `perror("Error")` in your code, especially right after fork() or execve() , to see what is going on in the pipe.
Inside the pipe, everything we do will go to one of its ends.
`printf` for ex. won’t print to the terminal, it will print to your outfile (because we swapped the stdout)
`perror("Error")` will work because it prints to stderr.

[3] Handle file rights when `open()`ing them.
Return error if the file cannot be opened, read or written. 
Check how the shell treats infile and outfile when they do not exist, are not readable, writable etc. (chmod is your best friend).


# Great Resources for Pipex

[42-Gitbook](https://42-cursus.gitbook.io/guide)

[Libft functions](https://www.asidesigned.com/project-libft.html) 

[Learn C](https://www.learn-c.org/)

[Makefile tutor](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)

[C-Programming-Language-2nd-Edition (PDF)](https://github.com/MarkosComK/42-Libft/files/14312769/C-Programming-Language-2nd-Edition.pdf)

For detailed information, refer to the [subject of the project](https://github.com/MarkosComK/42-Libft/files/14319130/00-libft-en.pdf)