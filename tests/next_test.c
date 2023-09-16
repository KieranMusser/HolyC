#define DBG

#include "../holyc.c"


char test[] = "printf(\"Hello, world\\n\");";

Context
disp_next(Context ctx) {
	TokenValue tvalue;
	TokenType ttype;
	Context ectx;

	ectx = next(ctx, &ttype, &tvalue);
	printf("end : %d type : %d\n",ectx.data - ctx.data, ttype);

	if (ttype >= 256) 
		printf("ttype : %s\n", dbg_TokenTypeName[ttype-256]);
	else
		printf("ttype char : %c\n", ttype);

	if (ttype == NAME || ttype == STRING) 
		pr_slice(tvalue.text); 
	printf("final %d %c\n", *ectx.data, *ectx.data);
	return ectx;
}

int main(int argc, char **argv) {
	TokenValue tvalue;
	TokenType ttype;
	Context ctx,ectx;
	ctx.data = test;
	ctx.index = 0;

	ttype = -1;

 /*
	ectx = next(ctx, &ttype, &tvalue);
	printf("end : %d type : %d\n",ectx.data - ctx.data, ttype);
	printf("ttype : %s\n", dbg_TokenTypeName[ttype]);

	pr_slice(tvalue.text);
*/
	printf("input %s\n", test);
	ctx = disp_next(ctx); /* NAME printf */
	ctx = disp_next(ctx); /* SYM ( */
	ctx = disp_next(ctx); /* STRING "Hello, world" */
	ctx = disp_next(ctx); /* SYM ) */
	ctx = disp_next(ctx); /* SYM ; */
	return 0;
}
