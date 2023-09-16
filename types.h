/* Split NUM into INT and FLOAT? */
typedef enum raw_TokenType {
	ERROR=256,NAME,NUM,STRING,TYPE,IF,WHILE
} TokenType;

#ifdef DBG
 char dbg_TokenTypeName[][7] = {"ERROR","NAME","NUM","STRING","TYPE","IF","WHILE"};
#endif /* DBG */

/* 
 * Avoid relying on "these" for holding all types? 
 * Switch to struct { int type; int indirection; } ?
 */

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

typedef struct raw_FuncArg {
	int has_default;
	char *keyword;
	DataType type;
	int default_value;
} FuncArg;

typedef struct raw_FuncSig {
	char *name;
	int num_args;
	FuncArg *args;
} FuncSig;

typedef struct raw_Context {
	char *data;
	int index;
	TokenType lasttok;
	FuncSig *funcs;
	int num_funcs;
} Context;

