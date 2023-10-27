#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
 * func_new
 * - owns args
 * - copies name
 * - muts ctx
 *
 * Does not handle realloc fails (assert)
 */
int func_add(Context *ctx, Slice name, FuncArg *args, int num_args) {
	/* Grow Funcs array, no graceful error */
	assert(ctx->alloc_funcs >= ctx->num_funcs);
	if (ctx->num_funcs == ctx->alloc_funcs) {
		ctx->alloc_funcs *= 2;
		ctx->funcs = realloc(ctx->funcs, sizeof(ctx->funcs)*ctx-alloc_funcs);
		assert(ctx->funcs != NULL);
	}
	ctx->funcs[ctx->num_funs].name = malloc(name.len * sizeof(*name.start));
	strncpy(ctx->funcs[ctx->num_funs].name, name.start, name.len);

	ctx->funcs[ctx->num_funs].args = args;
	ctx->funcs[ctx->num_funs].num_args = num_args;
	return 0;
}


