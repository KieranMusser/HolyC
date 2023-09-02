#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


typedef enum raw_TokenType {
	NAME,NUM,STRING,TYPE,IF,WHILE
} TokenType;

typedef enum raw_DataType {
	U0,U8,I8,U16,I16,U32,I32,U64,I64,F64
} DataType;

typedef struct raw_Slice {
	char *start;
	int len;
} Slice;

typedef union raw_TokenValue {
	Slice text;
	DataType type;
	int number;
} TokenValue;

typedef struct raw_Context {
	char *data;
	int index;
	TokenType lasttok;
} Context;

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
	while (isspace(*ctx.data)
		++ctx.data;
	return ctx;
}


int
match_type() {
	return 0;

}	

Context
match_var_set(Context ctx) {

}

void
asm_new_var(DataType type, Slice name); /* Take name + datatype and add instr to alloc */

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


/* Uncomplete func, handles string */
Context
next_sym(Context ctx, TokenType *ttype, TokenValue *tval) {
	switch(*ctx.data) {
	case '"':
		return next_str(ctx,ttype,tval);
	default:
		*ttype = *ctx.data;
	}
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
		//next_name(ctx);
		printf("ALP\n");
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

void
match_print_str(Context ctx) {
	
}

/*
Handle:
type var [= expr];
Output: ?
*/
void
match_var_dec(Context ctx, TokenValue type) {
	TokenValue varname, tvalue;
	TokenType tok;
	//assert(next(ctx, &varname, NULL) == NAME);
	//asm_new_var(type.type, varname.text);
	ctx = next(ctx,&tok,&tvalue);
	if (tok == '=') {
		match_var_set(ctx);
	}
}

Context
match_statement(Context ctx) {
	TokenType tok;
	Slice tslice;	
	TokenValue tvalue;
	Context tctx;

	tctx = next(ctx,&tok,&tvalue);

	switch(tok) {
	case TYPE:
		match_var_dec(ctx, tvalue);
		break;
	case STRING:
		match_print_str(ctx);
		break;
	case NAME:
		break;
	case IF:
		break;
	case WHILE:
		break;
	default:
		printf("unhandled token type %d\n",tok);
	}
	return ctx;
}

Context
match_function(Context ctx) {
  	int type;

	type = match_type();
   



	return ctx;
}

Context
match_global(Context ctx) {
	if (match_function(ctx).data == ctx.data) {
		match_statement(ctx);
	}	
}




