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
	(out)->text.start = ctx.data;
	while (*ctx.data && *ctx.data != '"') {
		++ctx.data;
		if (*ctx.data == '\\')
			++ctx.data;
	}
	if (out)
		out->text.len = ctx.data - out->text.start;
	return ctx;
}	

Context
next_name(Context ctx, TokenType *toktype, TokenValue *tokval) {
	ctx = skip_space(ctx);
	assert((isalpha(*ctx.data) || *ctx.data == '_') && "Not valid name");
	tokval->text.start = ctx.data;
	while (isalnum(*ctx.data) || *ctx.data == '_')
		++ctx.data;
	tokval->text.len = ctx.data - tokval->text.start;
	if (tokval->text.len == 2 && strncmp("if",tokval->text.start,tokval->text.len) == 0) {
		*toktype = IF;
	} else {
		*toktype = NAME;
	}

	return ctx;
}


/* Uncomplete func, handles string and len 1 syms */
Context
next_sym(Context ctx, TokenType *ttype, TokenValue *tval) {
	switch(*ctx.data) {
	case '"':
		return next_str(ctx,ttype,tval);
	default:
		*ttype = *ctx.data;
	}
	++ctx.data;
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
	while (*(ctx.data) == ' ') ++ctx.data;
	if (isdigit(*ctx.data)) {
		printf("DIG\n");
	} else if (isalpha(*ctx.data)) {
		printf("TXT\n");
		return next_name(ctx, tokout, out);
	} else {
		printf("SYM\n");
		return next_sym(ctx, tokout, out);
	}
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

