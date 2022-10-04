// Name: Vincent Fazio
// Class: CSC 4210
// Date: 2/19/21
// About: Forks processes and computes collatz algorithm using shared memory through mmap.
//        By creating a shared memory object with shm_open, ftruncate, and mmap you are able to
//        use the shared memory in a way that allows both the parent and the child process to access

//        shm_open: creates and opens a new, or opens an existing, POSIX shared memory object.
//        ftruncate: creates a block of space for the shared memory object to use
//        mmap: maps or unmaps files or devices into memory. It creates a new mapping in the virtual address space of the calling process.

// Compile Instructions: gcc -Wall fazio_collatz_sharedMem.c -o collatz
//                  Run: ./collatz <value>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <sys/mman.h>

int main(int argc, char**argv)
{
/*The size (in bytes) of shared memory object */
const int SIZE = 4096;

/*Name of the shared memory object */
const char *name = "Shared_Mem";

/*Input from command line arguments*/ 
int n = atoi(argv[1]);

/*Shared memory file descriptor */
int shm_fd;

/*Char Pointer to shared memory obect */
char *ptr;

/*Create the shared memory object */
shm_fd = shm_open(name, O_CREAT | O_RDWR,0666);

/*Configure the size of the shared memory object */ 
ftruncate(shm_fd, SIZE);

/*Memory map the shared memory object */
ptr = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

/*Error handling*/
if (argc == 1) {
    perror("No argument provided. Format: ./collatz <value>\n");
    exit(1);
    }

/*Error handling */
if (n <= 0) {
    perror("Number was non-positive. Enter a positive integer.\n");
    exit(1);
}

/*Forking of parent and child process*/
pid_t pid = fork();

if (pid < 0)
    {
        fprintf(stderr, "Fork not successful.\n");
        return 1;
    }
    /* Parent process*/
    else if (pid > 0) {
        //waiting for child process to write to the shared memory
        wait(0);
        //open/use shared memory in rdonly mode
        shm_fd = shm_open(name, O_RDONLY, 0666);
        //Print out the ending output of char* ptr - should always be 1
        printf("Output from parent: %s\n",(char *)ptr);
        //Unlink the shared memory object
        shm_unlink(name);
    }
    else{
        /* Write to the shared memory object */ 
        
        while(n!=1){ 
            if(n % 2 == 0) {
                n = n/2;
                //Writing the modified int value into shared memory - sprintf writes the msg into the ptr buffer.
                sprintf(ptr,"%i", n);
                printf("%i ", n);     
            }
            else {
                n = 3*n+1;
                //Writing the modified int value into shared memory - sprintf writes the msg into the ptr buffer.
                sprintf(ptr,"%i", n);
                printf("%i ", n);                    
            }
        }       
    }
return 0;
}
