   File access mode
       Unlike the other values that can be specified in flags, the access
       mode values O_RDONLY, O_WRONLY, and O_RDWR do not specify individual
       bits.  Rather, they define the low order two bits of flags, and are
       defined respectively as 0, 1, and 2.  In other words, the combination
       O_RDONLY | O_WRONLY is a logical error, and certainly does not have
       the same meaning as O_RDWR.

## File operations Examples:

1. write1.c - A program that uses write system call with proper ERROR Handling.

2. read1.c - A program that uses read system call with proper ERROR Handling.

3. open1.c - A program that reads a "abc" file content and writes in to stadard output.
	open1.c = $ cat abc
	open1.c != $ cat 123

4. copy_system.c  - A program that uses low-level system calls to copy one file to another.
	$ TIMEFORMAT=”” time copy_system
	11.32sec ; 99%cpu

5. copy_block.c  -  An improved version of system.c that copies blocks of data between the files.
	$ TIMEFORMAT=”” time copy_block
	0.02sec ; 50%cpu

6. copy_stdio.c  -  A program uses library calls to further improve the speed of the above programs by buffering
the file input and output.
	$ TIMEFORMAT=”” time copy_stdio
	0.03 sec; 59% cpu

7. lseek.c - A program that uses lseek system call.

8. stat.c - A Program that shows file information. 
	stat.c = ls -l


## Lab Assignments: Basic File Operations: (open(), read(), write(), close())
1.	Write a C program that makes a copy of a file using standard I/O and system calls.  Explain the Difference between System Call and Standard Library.
2.	Write a system programming your own version of getchar() standard C Library?
3.	Write a system programming your own version of cat command?
4.	Write a system programming your own version of echo command \?
5.	Write a system programming your own version of cp command?
6.	Write a system programming your own version of head & tail command?
7.	Write a system programming your own version of wc command?
8.	Write a system programming your own version of du & touch command?
