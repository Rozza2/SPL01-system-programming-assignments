#include <unistd.h>
#include <stdlib.h>	
#include <string.h>	
#include <stdio.h>	



int pwd_main() {
    
//     if (argc > 1) {
// 		const char* error = "problem in calling pwd can't add arguments Usage: ./pwd \n";
// 		if ( write(2, error, strlen(error)) < 0) {
// 			perror("Error in writing to error file");
// 			exit(-2);
// 		}	
// 		exit(-1);
// 	}
	
	char* x = getcwd(NULL, 0);
	
	if (x == NULL) {
		const char* error = "Error in calling getcwd function \n";
		
        if ( write(2, error, strlen(error)) < 0) {
            perror("Error in writing to error file");
            exit(-2);
        }
        exit(-3);
	}


	if ((write(1, x, strlen(x)) < 0) || (write(1, "\n", 1) < 0)) {
		perror("Error in writing to output file");
		exit(-2);
	}

	free(x);
	return 0;
}
