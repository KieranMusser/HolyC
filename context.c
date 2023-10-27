#include <stdlib.h>

Context context_new(char *code_data) {
	Context ctx;

	ctx.data = code_data;
//	ctx.index = 0;
//	ctx.lasttok = ERROR;

	ctx.funcs = NULL;
	ctx.num_funcs = 0;
	ctx.alloc_funcs = 0;

	ctx.symbols = syms_new();

	return ctx;
}
