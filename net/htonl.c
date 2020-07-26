#include <stdio.h>
#include <arpa/inet.h>

int main(void) {

	int a = 0x12345678;
	printf("a=%#x\n", a);
	int b = htonl(a);
	printf("b=%#x\n", b);

	return 0;
}
