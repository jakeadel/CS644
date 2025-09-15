#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define CHUNK_SIZE 10

int main(int argc, char *argv[]) {
	if (argc < 2) {
		puts("Please provide filepath argument");
		return -1;
	}
	char* file = argv[1];

	int fd = open(file, O_RDONLY);

	if (fd == -1) {
		printf("Unable to open file: %s\n", strerror(errno));
	} 

	// Read from a file forever
	// Every second, read from the previous
	// final location
	// keep track of index and use lseek
	// Read max CHUNK_SIZE bytes/s
	int none_count = 0;

	for (;;) {
		char buf[CHUNK_SIZE];
		// lseek not necessary?
		size_t count = read(fd, buf, CHUNK_SIZE);
		// If the count is 0, it still fills buf with the last CHUNK_SIZE bytes
		// Why is buf keeping its data?
		// Prints with the H continually when we run out of bytes to read
		// But in the read man pages, it says no bytes are read if at eof
		if (count == 0) none_count++;
		if (none_count > 5) return -1;
		printf("Bytes read: [%i] - %s\n", count, buf);
		buf[7] = 'H';
		sleep(1);
	}

	return 0;
}
