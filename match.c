#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>



/*
 * Match uses other match_x() plus next/peek()
 * -> asm_x()
 * -next/peek parses text
 * -match parses tokens
 * -asm outputs assembly
 */


Context
match_type(Context ctx, DataType *out_type) {
	TokenType ttype;
	TokenValue tval;
	int i;
	ctx = next(ctx, &ttype, &tval);
	assert(ttype == NAME);
	for (i=0; i<sizeof(DataTypeNames) / sizeof(*DataTypeNames); ++i) {
		if (strncmp(DataTypeNames[i], tval.text.start, tval.text.len) == 0) {
			*out_type = i;
			goto _match_type_ptr;
		}
	}
	*out_type = -1;
_match_type_ptr:
	i = peek(ctx);
	printf("M_TYPE NEXT %d %s %c \n",i,dbg_TokenTypeName[i-256],i);
	printf("next val %s\n",ctx.data);
	if (peek(ctx) == '*') {
		*out_type +=  1000;
		ctx = next(ctx,NULL,NULL);
	}
	return ctx;

}	

Context
match_expr(Context ctx, int *out) {
	TokenValue tval;
	TokenType ttype;
	


}

/* Take name + datatype and add instr to alloc */
void
asm_new_var(DataType type, Slice name) {

}

/*
 * Handles string alone on line
 */

void
match_print_str(Context ctx) {
	
}

/*
Handle:
	return ctx;
type var [= expr];
Output: ?
*/
Context
match_var_dec(Context ctx) {
	TokenValue varname, tvalue;
	TokenType tok;
	//assert(next(ctx, &varname, NULL) == NAME);
	//asm_new_var(type.type, varname.text);
	ctx = next(ctx,&tok,&tvalue);
	if (tok == '=') {
		match_var_set(ctx);
	}
	return ctx;
}
int extract_value(TokenValue tval, TokenType ttype) {
	switch(ttype) {
	case NUM:
		return tval.number;
	case STRING:
		return 0xC0FF;
	}
	return 420;
}



/*
 * Parses function calls
 * name(a,b=c,)
 * 
 */
Context
match_call(Context ctx, int ** out_args, int * out_num_args) {
	Context tmpctx;
	TokenType ttype, tmptype;
	TokenValue tv_func, tval;
	int num_args, i;
	int *args; /* Note: this could fail if sizeof int != sizeof void* */
	FuncSig fsig;
	fsig.name = NULL;

	ctx = next(ctx, &ttype, &tv_func);
	printf("M_CALL %d %c\n",ttype, ttype);
	assert(ttype == NAME && "Invalid function name");

	ctx = next(ctx, &ttype, NULL);
	assert(ttype == '(' && "Invalid token");


	/* not strictly needed */
	assert(out_args != NULL && "INVALID OUT ARGS");
	assert(out_num_args != NULL && "INVALID OUT N ARGS");


	/* Count number of arguments being passed */
	num_args = 0;
	tmpctx = ctx;
	while(1) {
		printf("cur %s\n", tmpctx.data);
		tmpctx = next(tmpctx, &ttype, NULL);
		assert(ttype != '\0' && "EOF before finish call");
	
		switch(ttype) {
		case ')':
			goto _done_counting; 
		case ',':
			++num_args;
			break;
		}
	}
_done_counting:


	/* Check against sigs */
	for (i=0; i<ctx.num_funcs; ++i) {
		if (strncmp(ctx.funcs[i].name, tv_func.text.start, tv_func.text.len) == 0) {
			fsig = ctx.funcs[i];
			break;
		}
	}

	/* fsig.name init to NULL, every real sig has name */
	assert(fsig.name != NULL);

	printf("num args %d\n", num_args);
	++num_args; /* num_arg counts ',' so it'll always be 0-1 short */
	args = malloc(sizeof(*args) * num_args);

	for (i=0; i<num_args; ++i) {
		ctx = next(ctx, &ttype, &tval);
		printf("ttype first %d %c\n",ttype, ttype);

		/* Default args */
		if (ttype == ',' || ttype == ')') {
			assert(fsig.args[i].has_default);
			args[i] = fsig.args[i].default_value;
			continue;
		/* Keyword argument */
		} else if (peek(ctx) == '=') {
			assert(ttype == NAME);
			args[i] = tval.text.start[0] * 100 + i;
			ctx = next(ctx, NULL, NULL); /* Consume = */
			ctx = next(ctx, &ttype, &tval); /* Temp consume */
			args[i] = extract_value(tval, ttype);
			
			/* Check against function signature */
		/* Regular argument */
		} else {
			/* Doesn't check against func sig */
			switch(ttype) {
			case NUM:
				args[i] = tval.number;
				break;
			case STRING:
				/* Store string */
				args[i] = 0xC0FF; /* String addr  */
				break;
			}
		}
		/* Consume comma - not reached for default arg */
		ctx = next(ctx, &ttype, NULL);
		printf("ttype %d %c\n", ttype, ttype);
		assert(ttype == ',' || ttype == ')' && "Bad arguments");
	}
	if (out_args)
		*out_args = args;
	if (out_num_args)
		*out_num_args = num_args;
	return ctx;
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
		match_var_dec(ctx);
		break;
	case STRING:
		match_print_str(ctx);
		break;
	/* Should handle type / var decl? */
	case NAME: 
		/*match_call(ctx);*/
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
match_body(Context ctx) {
	TokenType ttype;
	ctx = next(ctx, &ttype, NULL);
	assert(ttype == '{');
	while (ttype != '}')
		ctx = next(ctx, &ttype, NULL);
	return ctx;
}	

/* match function def */
Context
match_function(Context ctx, FuncSig *fsig) {
	TokenType ttype;
	TokenValue tval;
	Slice name;
	FuncArg arg;
	Context tmpctx;
	int num_args;
	

	/* currently this function is not NULL safe */
	assert(fsig != NULL);

	/* type */
	ctx = match_type(ctx, &(fsig->return_type));

	/* name */
	ctx = next(ctx, &ttype, &tval);
	assert(ttype == NAME);
	name = tval.text;
	fsig->name = malloc(sizeof(*(fsig->name)) * name.len);
	strncpy(fsig->name, name.start, name.len);
	/* (trash variable name) */
	
	ctx = next(ctx, &ttype, &tval);
	assert(ttype == '(');

	fsig->num_args = 0;
	fsig->args = NULL;
	if (peek(ctx) == ')') {
		ctx = next(ctx,NULL,NULL);
		return match_body(ctx);
	}
	tmpctx = ctx;
	while (peek(tmpctx) != ')') {
		tmpctx = next(tmpctx, &ttype, NULL);
		while (ttype != ',' && ttype != ')' && ttype != 0) {
			tmpctx = next(tmpctx, &ttype, NULL);
		}
		++num_args;
	}
	fsig->args = malloc(sizeof(*(fsig->args)) * num_args);
	while (peek(ctx) != ')') {
		printf("LEFT %s\n", ctx.data);
		ctx = match_type(ctx, &arg.type);
	
		ctx = next(ctx, &ttype, &tval);
		printf("TTYPE %d %c %s\n", ttype, ttype, dbg_TokenTypeName[ttype-256]);
		assert(ttype == NAME);
		name = tval.text;
		
		arg.keyword = malloc(sizeof(*(fsig->name)) * name.len);
		strncpy(arg.keyword, name.start, name.len);
		arg.keyword[name.len-1] = 0;
		
		if (peek(ctx) == '=') {
			/* handle default args */

			/* consume = */
			ctx = next(ctx, NULL, NULL);
			ctx = next(ctx, &ttype, &tval);
			arg.has_default = 1;
			arg.default_value = extract_value(tval, ttype);
		}
		ctx = next(ctx, &ttype, NULL);
		fsig->args[fsig->num_args] = arg;
		++(fsig->num_args);
		assert(fsig->num_args <= num_args);
		if (ttype == ')')
			break;
		
	}
	return match_body(ctx);
}

Context
match_global(Context ctx) {
	/* will always crash */
	if (match_function(ctx, NULL).data == ctx.data) {
		match_statement(ctx);
	}	
}




