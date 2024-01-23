#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> //includes file flags

int main(int argc, char *argv[]){
    int inFile;
    int outFile;
    char buffer[1024]; //array of 1024 chars, arbitrary size
    ssize_t bytesRead;// type read() returns
    if (argc != 1 && argc != 3){
        exit(EXIT_FAILURE);
    }

    if (argc == 1){ //no arguments
        inFile = 0;
        outFile = 1;

        //read() returns number of bytesRead
        while ((bytesRead = read(inFile, buffer, 1024))>0){ //reads up to 1024 at a time
            if (write(outFile, buffer, bytesRead)!=bytesRead){
                perror("write");
                inFile = close(inFile);
                outFile = close(outFile);
                exit(EXIT_FAILURE);
            }
        }
        if (bytesRead < 0){
            perror("read");
            exit(EXIT_FAILURE);
        }

            exit(EXIT_SUCCESS);

        
    } else { //two arguments
        int inFile = open(argv[1], O_RDONLY); 
        if (inFile < 0){
            perror(argv[1]);
            exit(EXIT_FAILURE);
        }

        int outFile = open(argv[2], O_WRONLY);
        if (outFile < 0){
            perror(argv[2]);
            exit(EXIT_FAILURE);
        }

        while ((bytesRead = read(inFile, buffer, 1024))>0){
            if (write(outFile, buffer, bytesRead)!=bytesRead){
                perror(argv[2]);
                exit(EXIT_FAILURE);
            }
        }
        if (bytesRead < 0){
            perror(argv[1]);
            exit(EXIT_FAILURE);
        }


        inFile = close(inFile);
        outFile = close(outFile);
        exit(EXIT_SUCCESS);

    }
    
}

