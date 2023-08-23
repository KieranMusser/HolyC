
typedef enum raw_Token {
	NAME,LITERAL,TYPE,IF,WHILE
} Token;

typedef enum raw_DataType {
    Void,Char,Int
} DataType;

typedef struct raw_Slice {
    char *start;
    int len;
} Slice;

typedef struct raw_Context {
	char *data;
	int index;
	Token lasttok;
} Context;

Token next(Slice *out);
void peek();

int match_type();
void match_statement();
void match_function();

void match_statement() {
	token tok;
	Slice tslice;	

	tok = next();

	if (tok == TYPE) { /* variable decl */
		assert(next(&tslice) == String);
		tok = next();
		if (tok == '=') {
		
		}

		
	}
}

void match_function() {
   int type;

   type = match_type();
   




}

void check_global() {
	token t = next();
	if (!match_function()) {
		match_statement();
	}	
}









