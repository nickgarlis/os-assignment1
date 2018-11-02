#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int get_file (char *file_name);
void read_file (int file, int buff_size);
void close_file (int file);

int main (int argc, char *argv[]) {
    const short int start = atoi(argv[1]);
    const short int buff_size = atoi(argv[2]);

    const int file = get_file("data2.txt");
    
    read_file(file, buff_size);

    close_file(file);

    return 0;
}

int get_file (char *file_name) {
    int const status = open(file_name, O_RDONLY);
    if (status<0) {
        perror("Cannot open file");
        exit(1);
    }
    return status;
}

void read_file (int file, int buff_size) {
    char buffer[buff_size];
	
    memset(buffer, 0, buff_size);
    while (read(file, buffer, buff_size-1)){
        printf("%s\n", buffer);
        memset(buffer, 0, buff_size);
	}
}

void close_file (int file) {
    int const status = close(file);
    if (status<0) {
        perror("Cannot close file");
        exit(1);
    }
}