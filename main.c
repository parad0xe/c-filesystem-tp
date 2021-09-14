#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

const char* COLOR_DEFAULT = "\e[00m";
const char* COLOR_RED = "\e[31m";
const char* COLOR_GREEN = "\e[32m";
const char* COLOR_YELLOW = "\e[33m";
const char* COLOR_BLUE = "\e[34m";

int get_file_size(char* path) {
	struct stat sb;
	if (stat(path, &sb) == -1) {
		echo("$vFailed$v to get file size of $v\n", COLOR_RED, COLOR_DEFAULT, path);
        return -1;
    }

    return sb.st_size;
}

int get_file_content(char* path, char* read_buffer, int size) {
    int fd;
    if((fd = open(path, O_RDONLY, 0444)) == -1) {
    	echo("$vFailed$v to open file $v\n", COLOR_RED, COLOR_DEFAULT, path);
		return -1;
    }

    int read_size = read(fd, read_buffer, size);
    if(read_size == -1) {
    	echo("$vFailed$v to read file $v\n", COLOR_RED, COLOR_DEFAULT, path);
		return -1;
    }

    read_buffer[size] = '\0';
    close(fd);

    return read_size;
}

int put_file_content(char* path, char* write_buffer, int buffer_size) {
	int fd;
    if((fd = open(path, O_WRONLY | O_CREAT, 0644)) == -1) {
    	echo("$vFailed$v to open file $v\n", COLOR_RED, COLOR_DEFAULT, path);
		return -1;
    }

    write(fd, write_buffer, buffer_size);
    close(fd);
    return 0;
}

int main(int argc, char** argv) {
	if(argc != 2) {
		echo("\n\t$vUsage: ./main <file_path>\n\n", COLOR_RED);
		return 1;
	}

	char* err_data = "J'ai tout compris au C.\n";

	int buffer_size;
	if((buffer_size = get_file_size(argv[1])) == -1) {
		put_file_content("0.txt", err_data, len(err_data));
		return 1;
	}

	char buffer[buffer_size + 1];
	int read_size = get_file_content(argv[1], buffer, buffer_size);
	if(read_size == -1 || read_size == 0) {
		put_file_content("0.txt", err_data, len(err_data));
		return 1;
	}

	char** lines = explode(buffer, buffer_size, '\n');

	for (int i = 0; *(lines + i); i++)
	{
		char* str_i = to_string(i + 1);
		char* filename = format("$v.txt", str_i);
		echo("$vFile($v$v$v): $vsuccessfully edited !\n", COLOR_DEFAULT, COLOR_BLUE, filename, COLOR_DEFAULT, COLOR_GREEN);
		put_file_content(filename, *(lines + i), len(*(lines + i)));
		free(filename);
		free(str_i);
	}

	free_explode(lines);

	return 0;
}