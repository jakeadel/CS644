#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>



int main(int argc, char *argv[]) {
	if (argc < 2) {
		puts("Please provide filepath argument");
		return -1;
	}
	char* file = argv[1];

	int fd = open(file, O_APPEND | O_CREAT | O_WRONLY);

	if (fd == -1) {
		printf("Unable to open file: %s\n", strerror(errno));
	} 

	// Write to a file forever
	char* buf = "_";
	size_t buf_size = 1;
	for (;;) {
		write(fd, buf, buf_size);		
		sleep(1);
	}

	return 0;
}
