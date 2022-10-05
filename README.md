# Compute_Collatz
Compute collatz using shared memory. Collatz asks whether repeating two simple arithmetic operations will eventually transform every positive integer into 1.
// About: Forks processes and computes collatz algorithm using shared memory through mmap.
//        By creating a shared memory object with shm_open, ftruncate, and mmap you are able to
//        use the shared memory in a way that allows both the parent and the child process to access

//        shm_open: creates and opens a new, or opens an existing, POSIX shared memory object.
//        ftruncate: creates a block of space for the shared memory object to use
//        mmap: maps or unmaps files or devices into memory. It creates a new mapping in the virtual address space of the calling process.

// Compile Instructions: gcc -Wall fazio_collatz_sharedMem.c -o collatz
//                  Run: ./collatz <value>
