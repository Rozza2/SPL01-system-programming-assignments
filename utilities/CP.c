#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int cp_main(int argc, char* argv[]) {
    if (argc < 2) {
        const char* msg = ": missing file operand\n";
        if (write(2, argv[0], strlen(argv[0])) < 0 ||
            write(2, msg, strlen(msg)) < 0) {
            perror("stderr write failure");
            exit(-2);
        }
        exit(-1);
    }

    if (argc < 3) {
        const char* msg1 = ": missing destination file operand after '";
        const char* msg2 = "'\n";
        if (write(2, argv[0], strlen(argv[0])) < 0 ||
            write(2, msg1, strlen(msg1)) < 0 ||
            write(2, argv[1], strlen(argv[1])) < 0 ||
            write(2, msg2, strlen(msg2)) < 0) {
            perror("stderr write failure");
            exit(-2);
        }
        exit(-1);
    }

    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        const char* part1 = ": cannot stat '";
        const char* part2 = "': No such file or directory\n";
        if (write(2, argv[0], strlen(argv[0])) < 0 ||
            write(2, part1, strlen(part1)) < 0 ||
            write(2, argv[1], strlen(argv[1])) < 0 ||
            write(2, part2, strlen(part2)) < 0) {
            perror("stderr write failure");
            exit(-2);
        }
        exit(-3);
    }

    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("failed to open destination");
        close(src_fd);
        exit(-3);
    }

    char buffer[100];
    ssize_t read_bytes;
    while ((read_bytes = read(src_fd, buffer, 100)) > 0) {
        if (write(dest_fd, buffer, read_bytes) < 0) {
            perror("failed to write to target file");
            close(src_fd);
            close(dest_fd);
            exit(-2);
        }
    }

    if (read_bytes < 0) {
        perror("failed to read from source");
        close(src_fd);
        close(dest_fd);
        exit(-4);
    }

    if (close(src_fd) < 0 || close(dest_fd) < 0) {
        perror("failed to close file descriptor");
        exit(-5);
    }

    return 0;
}
