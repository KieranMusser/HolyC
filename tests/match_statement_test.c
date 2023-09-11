#define DBG

#include "../holyc.c"


char test[] = "printf(\"Hello, world\\n\")";

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

	if (ttype == NAME) 
		pr_slice(tvalue.text); 

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
	ctx = disp_next(ctx);
	ctx = disp_next(ctx);
	ctx = disp_next(ctx);
	return 0;
}
