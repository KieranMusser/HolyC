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
char DataTypeNames[][4] = {
	"U0","U8","I8","U16","I16","U32","I32","U64","I64","F64"
};

typedef struct raw_Slice {
	char *start;
	int len;
} Slice;

typedef union raw_TokenValue {
	Slice text;
	int number;
} TokenValue;

typedef enum {
	SYM_SLICE,
	SYM_INT
} SYM_TYPE;

typedef union raw_Value {
	Slice slice;
	int num;
} Value;

typedef struct raw_FuncArg {
	char *keyword;
	DataType type;
	int has_default;
	SYM_TYPE dv_type;
	TokenValue default_value;
} FuncArg;

typedef struct raw_FuncSig {
	char *name;
	DataType return_type;
	int num_args;
	FuncArg *args;
} FuncSig;


typedef struct raw_Symbol {
	unsigned int hash;
	SYM_TYPE type;
	Value v;
} Symbol;

typedef struct raw_SymbolTable {
	Symbol *start;
	int len;
	int alloc;
} SymbolTable;


typedef struct raw_Context {
	char *data;
//	int index;
//	TokenType lasttok;

	FuncSig *funcs;
	int num_funcs;
	int alloc_funcs;

	SymbolTable symbols;
} Context;

