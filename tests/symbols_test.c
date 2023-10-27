#define DBG
#include "../types.h"
#include "../symbols.c"
#include "../util.c"

int main(int argc, char **argv) {
	char test[] = "12345";
	char test1[] = "1";
	char test2[] = "2";
	char test3[] = "3";
	syms_main();
	printf("%d\n", hash(slicify(test)));
	printf("%d\n", hash(slicify(test1)));
	printf("%d\n", hash(slicify(test2)));
	printf("%d\n", hash(slicify(test3)));
	return 0;
}
