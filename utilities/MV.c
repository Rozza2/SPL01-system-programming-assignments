#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        char* msg = ": missing file operand\n";
        if ((write(2, argv[0], strlen(argv[0])) < 0) || (write(2, msg, strlen(msg)) < 0)) {
            perror("write error");
            exit(1);
        }
        exit(1);
    } else if (argc == 2) {
        char* msg1 = ": missing destination file operand after '";
        if ((write(2, argv[0], strlen(argv[0])) < 0) ||
            (write(2, msg1, strlen(msg1)) < 0) ||
            (write(2, argv[1], strlen(argv[1])) < 0) ||
            (write(2, "'\n", 2) < 0)) {
            perror("write error");
            exit(1);
        }
        exit(1);
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) {
        char* m1 = ": cannot stat '";
        char* m2 = "': No such file or directory\n";
        if ((write(2, argv[0], strlen(argv[0])) < 0) ||
            (write(2, m1, strlen(m1)) < 0) ||
            (write(2, argv[1], strlen(argv[1])) < 0) ||
            (write(2, m2, strlen(m2)) < 0)) {
            perror("write error");
            exit(2);
        }
        exit(2);
    }

    if (rename(argv[1], argv[2]) == 0) {
        return 0;
    }

    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0) {
        perror("open error");
        exit(2);
    }

    char buffer[100];
    int n;
    do {
        n = read(fd1, buffer, 100);
        if (n < 0) {
            perror("read error");
            exit(3);
        }
        if (n > 0) {
            if (write(fd2, buffer, n) < 0) {
                perror("write error");
                exit(4);
            }
        }
    } while (n > 0);

    if (close(fd1) < 0) {
        perror("close error");
        exit(5);
    }
    if (close(fd2) < 0) {
        perror("close error");
        exit(5);
    }

    if (unlink(argv[1]) < 0) {
        perror("unlink error");
        exit(6);
    }

    return 0;
}
