#include "../holyc.c"


char test_code[] = "print(\"Hello, world\",test=1,420,);\n";

int main(int argc, char **argv) {
	TokenValue tvalue;
	TokenType ttype;
	Context ctx,ectx;
	ctx.data = test_code;
	ctx.index = 0;

	int *args, num_args, i;

	ttype = 0;
	
	ectx = match_call(ctx, &args, &num_args);
	printf("matched %d\n", num_args);
	for (i=0; i<num_args; ++i) {
		printf("%d : %d\n", i, args[i]);
	}
	/*
	printf("end : %d type : %d\n",ectx.data - ctx.data, ttype);
	pr_slice(tvalue.text);
	*/
	return 0;

}
