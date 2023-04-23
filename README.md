###Simple Shell

This project is in collaboration of Glamour Maphanga and Hoja Tesema 

This is a project for Holberton School's curriculum, where we were asked to implement a simple UNIX command interpreter.

###Background

The original Unix operating system was designed and implemented by Ken Thompson and Dennis Ritchie at Bell Labs in 1969. Ken Thompson also wrote the first version of the UNIX shell. He also invented the B programming language, which was the direct predecessor to the C programming language. Ken Thompson is a renowned computer scientist, who has made significant contributions to the field of computer science, including the development of the first compiler, the first operating system with virtual memory, and the creation of the Go programming language.

A shell is a program that allows users to interact with the operating system by providing a command-line interface. When a user types a command in a shell, the shell interprets the command and executes it.

A process is a running instance of a program. A pid (process ID) is a unique identifier for a process, and a ppid (parent process ID) is the identifier for the process that started it. The environment of a process includes all the variables and their values that are defined for that process.

A function is a block of code that performs a specific task, while a system call is a request to the operating system kernel to perform a specific operation.

###Requirements

Allowed editors: vi, vim, emacs
All files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
All files should end with a new line
A README.md file, at the root of the folder of the project is mandatory
Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
Your shell should not have any memory leaks
No more than 5 functions per file
All your header files should be include guarded
Use system calls only when you need to (why?)

##List of allowed functions and system calls

access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getpid (man 2 getpid)
getline (man 3 getline)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)

##Compilation
Your shell will be compiled this way:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

##To start the shell in interactive mode, run:

./hsh
This will display a prompt and wait for the user to type a command. The prompt is
