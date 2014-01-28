#include<defs.h>
#include "../sys/fs.h"
#ifndef _STDIO_H
#define _STDIO_H

struct dir_struct; 
struct dirent; 

int printf(const char *format, ...);
//int scanf(const char *format, ...);
int scanf(char *format, ...);
int shell_scanf(char *format, ...);
void waitpid(uint16_t task_id);
void wait();
uint16_t getpid();
void sleep(uint16_t sec);
uint16_t fork();
void * malloc(uint64_t);
int open(const char *);
struct dir_struct * opendir(const char *);
struct dirent * readdir(struct dir_struct *);
int closedir(struct dir_struct *);
int close(int);
int read(int,void *,uint64_t);
void execvpe(const char *, int, char **);
//void execvpe(const char *);
void ls();
void ps();
void  ulimit(uint64_t size);
void cd(const char * dir_name); 


#endif
