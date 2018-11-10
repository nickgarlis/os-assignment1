#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "next_i.h"

int open_file (const char *path, const int flag, const mode_t mode);
ssize_t read_file (const int data_file, char *buffer, const size_t buff_size);
ssize_t write_file (const int file_des, const char *buffer, const size_t buff_size); 
void close_file (const int file_des);
off_t set_offset (const int file_des, const off_t offset);
ssize_t dump_buffer (const char *buffer, const size_t buff_size);
void fill_and_dump (const size_t buff_size, off_t offset);
size_t int_to_size_t(const int val);

int data_file;
int letters_file;
int numbers_file;

int main (int argc, char *argv[]) {
    if (argc!=3) {
        fprintf(stderr, "Wrong input\n");
        exit(1);
    }

    const unsigned int offset = strtol(argv[1], NULL, 10);
    const size_t buff_size = int_to_size_t(strtol(argv[2], NULL, 10));
    
    data_file = open_file("data2.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    letters_file = open_file("exercise2_letters", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    numbers_file = open_file("exercise2_numbers", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

    fill_and_dump(buff_size, offset);

    close_file(data_file);
    close_file(numbers_file);
    close_file(letters_file);

    return 0;
}

int open_file (const char *path, const int flag, const mode_t mode) {
    int const file_des = open(path, flag, mode);
    if (file_des < 0) {
        perror("Cannot open file");
        printf("%s\n", path);
        exit(2);
    }
    return file_des;
}

ssize_t read_file (const int data_file, char *buffer, const size_t buff_size) {
    const ssize_t read_chars = read(data_file, buffer, buff_size);
    if (read_chars<0) {
        perror("Cannot read file");
        exit(4);
    }
    return read_chars;
}

ssize_t write_file (const int file_des, const char *buffer, const size_t buff_size) {
    ssize_t written_bytes = write(file_des, buffer, buff_size);
    if (written_bytes < 0 ) {
        perror("Cannot write file");
        exit(5);
    }
    return written_bytes;
}

void close_file (const int file) {
    int const status = close(file);
    if (status<0) {
        perror("Cannot close file");
        exit(6);
    }
}

off_t set_offset (const int file_des, off_t offset) {
    offset = lseek(file_des, offset, SEEK_SET);
    if (offset<0) {
		perror("Seek error");
        exit(3);
	}
    return offset;
}

ssize_t dump_buffer (const char *buffer, const size_t buff_size) {
    int file_des;
    if (isalpha(buffer[0])) {
        file_des = letters_file;
    } else if (isdigit(buffer[0])) {
        file_des = numbers_file;
    }

    return write_file (file_des, buffer, buff_size);
}

void fill_and_dump (const size_t buff_size, off_t offset) {
    char buffer[buff_size];
    int total_written_bytes = 0;

    for (unsigned int i=0; i<10; i++) {
        offset = set_offset(data_file, offset);
        memset(buffer, 0, buff_size);
        ssize_t read_chars = read_file(data_file, buffer, buff_size);
        dump_buffer(buffer, buff_size);
        offset = next_num (offset);
        total_written_bytes += read_chars;
    }

    printf("Bytes written: %d\n", total_written_bytes);
}

size_t int_to_size_t (const int val) {
    return (val < 0) ? __SIZE_MAX__ : (size_t)((unsigned)val);
}