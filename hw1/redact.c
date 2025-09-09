#include <stdio.h>
#include <ctype.h>

void print_redact(const char *str) {
	while (++str && *str != '\0') {
		if (isdigit(*str)) {
			printf("X");
		}
		else {
			printf("%c", *str);
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		puts("Please provide a string to be redacted");
		return -1;
	}
	const char *str = argv[1];
	print_redact(str);
	return 0;
}
