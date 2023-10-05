#ifndef CALCULJIT_H

struct ast {
    int nodetype;
    double number;
    int offset;
    struct ast* l;
    struct ast* r;
};

struct ast* newast(int nodetype, struct ast* l, struct ast* r);
struct ast* newnum(double d);
double eval(struct ast*);
void treefree(struct ast*);
void yyerror(char* s, ...);

#endif
