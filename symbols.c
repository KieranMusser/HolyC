#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


SymbolTable syms_new() {
	SymbolTable tbl;
	tbl.len = 0;
	tbl.alloc = 1;
	tbl.start = malloc(sizeof(*tbl.start) * tbl.alloc);
	return tbl;
}

void syms_grow(SymbolTable *tbl) {
	assert(tbl->alloc != 0 && "Use after free"); 
	if (tbl->len < tbl->alloc) {
		return;
	} 
	tbl->alloc = tbl->alloc * 2;
	tbl->start = realloc(tbl->start, sizeof(*(tbl->start)) * tbl->alloc);
	assert(tbl->start != NULL && "Realloc fail");
}

void syms_add(SymbolTable *tbl, Symbol sym) {
	syms_grow(tbl);
	tbl->start[tbl->len] = sym;
	++tbl->len;
}

void syms_free(SymbolTable *tbl) {
	tbl->alloc = 0;
	tbl->len = 0;
	free(tbl->start);
	tbl->start = NULL;
}


#ifdef DBG
void syms_print(SymbolTable tbl) {
	int i;
	for (i=0; i<tbl.len; ++i) {
		printf(
			"%d %d %d\n",
			tbl.start[i].hash, 
			tbl.start[i].type,
			tbl.start[i].v.num
		);
	}
}


int syms_main() {
	SymbolTable tbl;
	Symbol s;
	tbl = syms_new();
	s.hash = 123;
	s.v.num = 321;
	syms_add(&tbl, s);
	syms_add(&tbl, s);
	syms_print(tbl);
	return 0;
}




#endif




