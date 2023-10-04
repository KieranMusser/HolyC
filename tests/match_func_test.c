#define DBG 
#include "../holyc.c"



char test_code[] = "U0 print(U8 *string, U64 test, U64 other, U64 hm = 817) {}\nprint(\"Hello, world\",test=1337,420,);\n";

int main(int argc, char **argv) {
	TokenValue tvalue;
	TokenType ttype;
	Context ctx,ectx;
	FuncSig fsig;
	int *args, num_args, i;

	ctx = context_new(test_code);

	ttype = 0;
	
	ctx = match_function(ctx, &fsig);
	ctx.funcs = &fsig;
	ctx.num_funcs = 1;
	printf("ARGS PTR %d\n",fsig.args);
	for (i=0; i<fsig.num_args; ++i) {
		printf("Arg %d\n", fsig.args[i].keyword);
		printf("Default? %d\n", fsig.args[i].has_default);
	}
	
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
