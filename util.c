#include <string.h>

/* pearson */
int hash(Slice slice) {
	int i;
	int ret = 0;
	int C = 314;
	for (i=0; i<slice.len; ++i) {
		ret = (slice.start[i] * C + ret) % 1024;
	}	
	return ret;
}



Slice slicify(char *text) {
	Slice s;
	s.start = text;
	s.len = strlen(text);
	return s;
}


