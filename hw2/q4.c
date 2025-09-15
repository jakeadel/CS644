#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
	int eacces_res = open("./not_writable.txt", O_WRONLY);
	printf("EACCES ERR: %s\n", strerror(errno));

	int eexist_res = open("./dne.txt", O_RDONLY);
	printf("EEXIST ERR: %s\n", strerror(errno));

	int enoent_res = open("./not_writable.txt", O_EXCL | O_CREAT);
	printf("ENOENT ERR: %s\n", strerror(errno));
	
	return 0;
}
