#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int open_file (const char *path, const int permissions);
void read_file (const int file_des, const size_t buff_size);
void close_file (const int file_des);
size_t int_to_size_t(const int val);

int main (int argc, char *argv[]) {
    const unsigned int start = atoi(argv[1]);
    const size_t buff_size = int_to_size_t(atoi(argv[2]));

    const int data_file = open_file("data2.txt", O_RDONLY);

    read_file(data_file, buff_size);

    close_file(data_file);

    return 0;
}

int open_file (const char *path, const int permissions) {
    int const file_des = open(path, permissions);
    if (file_des < 0) {
        perror("Cannot open file");
        exit(1);
    }
    return file_des;
}

void read_file (const int file_des, const size_t buff_size) {
    char buffer[buff_size];
    memset(buffer, 0, buff_size);
    ssize_t read_chars = read(file_des, buffer, buff_size-1);
    if (read_chars<0) {
        perror("Cannot read file");
        exit(1);
    }
    while (read_chars) {
        printf("%s\n", buffer);
        memset(buffer, 0, buff_size);
        read_chars = read(file_des, buffer, buff_size-1);
	}
}

void close_file (const int file) {
    int const status = close(file);
    if (status<0) {
        perror("Cannot close file");
        exit(1);
    }
}

size_t int_to_size_t (const int val) {
    return (val < 0) ? __SIZE_MAX__ : (size_t)((unsigned)val);
}