#include <unistd.h> 
#include <string.h>   
#include <stdio.h>    
#include <stdlib.h>   


int echo_main(int argc, char* argv[]) {

    for (int idx = 1; idx < argc; ++idx) {
        ssize_t bytes_written = write(STDOUT_FILENO, argv[idx], strlen(argv[idx]));
        if (bytes_written < 0) {
            perror("Failed to write argument");
            exit(-1);
        }

        
        if (idx < argc - 1) {
            if (write(STDOUT_FILENO, " ", 1) < 0) {
                perror("Failed to write space");
                exit(-1);
            }
        }
    }
    if (write(STDOUT_FILENO, "\n", 1) < 0) {
        perror("Failed to write newline");
        exit(-1);
    }

    return 0;
}
