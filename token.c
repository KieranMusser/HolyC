/*
 * Pulls a useful token out of a string
 * see next(...) and peek(...);
 */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


void
pr_slice(Slice sl) {
	printf("%.*s\n",sl.len,sl.start);
}


/*
 * Match uses other match_x() plus next/peek()
 * -> asm_x()
 * -next/peek parses text
 * -match parses tokens
 * -asm outputs assembly
 */



Context
skip_space(Context ctx) {
	while (isspace(*ctx.data))
		++ctx.data;
	return ctx;
}


/*
 * Get next "string"
 */
Context
next_str(Context ctx, TokenType *tokout, TokenValue *out) {
	printf("PSTR\n");
	if (tokout)
		*tokout = STRING;
	++ctx.data;
	if (out)
		(out)->text.start = ctx.data;
	while (*ctx.data && *ctx.data != '"') {
		++ctx.data;
		if (*ctx.data == '\\')
			++ctx.data;
	}
	++ctx.data; /* advance beyond final quote */
	if (out)
		out->text.len = ctx.data - out->text.start;
	return ctx;
}	

Context
next_name(Context ctx, TokenType *toktype, TokenValue *tokval) {
	TokenValue ret_tokval;
	ctx = skip_space(ctx);
	assert((isalpha(*ctx.data) || *ctx.data == '_') && "Not valid name");
	ret_tokval.text.start = ctx.data;
	while (isalnum(*ctx.data) || *ctx.data == '_')
		++ctx.data;

	if (toktype == NULL && tokval == NULL)
		return ctx;

	ret_tokval.text.len = ctx.data - ret_tokval.text.start;
	if (ret_tokval.text.len == 2 && strncmp("if",ret_tokval.text.start,ret_tokval.text.len) == 0) {
		if (toktype)
			*toktype = IF;
	} else {
		if (toktype)
			*toktype = NAME;
	}
	if (tokval)
		*tokval = ret_tokval;
	return ctx;
}


/* Uncomplete func, handles string and len 1 syms */
Context
next_sym(Context ctx, TokenType *ttype, TokenValue *tval) {
	switch(*ctx.data) {
	case '"':
		return next_str(ctx,ttype,tval);
	default:
		if (ttype)
			*ttype = *ctx.data;
	}
	++ctx.data;
	return ctx;
}
Context
next_number(Context ctx, TokenType *ttype, TokenValue *tval) {
	int ret;
	ret = 0;
	while (isdigit(*ctx.data)) {
		ret *= 10;
		ret += *ctx.data - '0';
		++ctx.data;
	}
	if (ttype)
		*ttype = NUM;
	if (tval)
		tval->number = ret;

	return ctx;
}
/*
 * Handles 
 * - symbol (incomplete)
 * - 
 *
 * all next* functions that take ptrs can be given NULL safely
 */
Context
next(Context ctx, TokenType *tokout, TokenValue *out) {
	int i;
	
	i = 0;
	while (*ctx.data == ' ' || *ctx.data == '\n')
		++ctx.data;

	if (isdigit(*ctx.data)) {
		printf("DIG\n");
		return next_number(ctx, tokout, out);
	} else if (isalpha(*ctx.data)) {
		printf("TXT\n");
		return next_name(ctx, tokout, out);
	} else {
		printf("SYM\n");
		return next_sym(ctx, tokout, out);
	}
	assert(0 && "Unhandled token");
}

/*
 * Get type of upcoming token
 */
TokenType
peek(Context ctx) {
	TokenType toktype;
	/* extract type of token, throw all else out */
	next(ctx, &toktype, NULL); 
	return toktype;
}

