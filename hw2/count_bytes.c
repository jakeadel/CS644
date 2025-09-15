#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// L1 Cache line size is 64 bytes
// read can transfer at most 0x7ffff000
// or 2,147,479,552 bytes, approx 2^31
#define CHUNK_SIZE 1000000

int main(int argc, char *argv[]) {
	if (argc < 2) {
		puts("Please provide filename argument");
		return -1;
	}
	char *file = argv[1];

	int fd = open(file, O_RDONLY);
	if (fd == -1) {
		printf("%s\n", strerror(errno));
	}

	int total_bytes = 0;
	int total_whitespace = 0;
	char buf[CHUNK_SIZE];
	for (;;) {
		int bytes = read(fd, buf, CHUNK_SIZE);
		if (bytes == -1) {
			printf("%s\n", strerror(errno));
			break;
		}
		else if (bytes == 0) {
			break;
		}
		total_bytes += bytes;
		int whitespace = 0;
		for (size_t i = 0; i < bytes; i++) {
			char c = buf[i];
			if (c == ' ' || c == '\n' || c == '\t') {
				whitespace++;
			}
		}
		total_whitespace += whitespace;
	}

	printf("Total number of bytes read: %i\n", total_bytes);
	printf("Number of whitespace characters: %i\n", total_whitespace);

	return 0;
}
