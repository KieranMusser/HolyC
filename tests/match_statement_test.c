#include "../holyc.c"


char test[] = "printf(\"Hello, world\\n\")";

int main(int argc, char **argv) {
	TokenValue tvalue;
	TokenType ttype;
	Context ctx,ectx;
	ctx.data = test;
	ctx.index = 0;

	ttype = 0;
	
	ectx = next(ctx, &ttype, &tvalue);
	printf("end : %d type : %d\n",ectx.data - ctx.data, ttype);
	pr_slice(tvalue.text);

}
