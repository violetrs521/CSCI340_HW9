#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
    //gets the argument from the command line
    char *cmd = argv[1];
    printf("Here is what you have entered: %s \n", cmd);

    char *mem = (char *) calloc(100, sizeof(char));
    int *offset = calloc(1, sizeof(int));
    

    int file = open(cmd, O_RDONLY | O_CREAT);
    
    //gets the signature
    int sig = read(file, mem, 4);
    printf("Signature %s \n", mem);
    lseek(file, 4, SEEK_CUR);

    //gets the number of entries in the offset array and allocates an array of the size
    int off = read(file, offset, 4);
    printf("Offset number of entries %d \n", *offset);
    int *offset_array = calloc(*offset, sizeof(int));

    lseek(file, 8, SEEK_CUR);

    //attempting to loop through the offset array and store the values
    for(int i = 0; i < *offset; i++){
        
        int offset = read(file, offset_array + i, 4);
        printf("This is the offset number %d: %d \n", i, offset_array[i]);
        lseek(file, i*4+8, SEEK_CUR);
        char *readinn = calloc(*offset_array + i, sizeof(int)); 
        char readin = read(file, readinn, *offset_array +i);

        printf("Here is a mess: %s\n", readinn);
    }

    //lseek(file, *offset ,SEEK_CUR);
    // int *offset_for_line = calloc(1, sizeof(int));
    // int offsetline = read(file, offset_for_line, 4);
    // printf("This is the offset number for the line: %d \n", *offset_for_line);
    // lseek(file, *offset + 4, SEEK_CUR);

   


    free(mem);
    free(offset);
   // free(offset_for_line);
    //free(readinn);
    close(file);
}