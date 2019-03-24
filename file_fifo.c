// C program to implement one side of FIFO 
// This side writes first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd; 
  
    // FIFO file path 
    char * myfifo = "/tmp/myfifo"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>, <permission>) 
    //mkfifo(myfifo, 0666); 
  
    char arr1[20];
	const int MAX_BUF = 20;
	int bytesread = 0;
	
     while (1) 
    { 
		// Open FIFO for Read only 
        fd = open(myfifo, O_RDONLY);
        // Read from FIFO 
	if((bytesread = read( fd, arr1, MAX_BUF - 1)) > 0)
	{
		arr1[bytesread] = '\0';
		printf("Received: %s", arr1);
	}	
       // read(fd, arr1, sizeof(arr1));   
        // Print the read message 
        //printf("%s", arr1); 
        close(fd); 
    } 
    return 0; 
} 
