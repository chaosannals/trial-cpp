#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calculjit.h"

extern int yylineno;

struct ast* newast(int nodetype, struct ast* l, struct ast* r) {
    struct ast* a = malloc(sizeof(struct ast));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast* newnum(double d) {
    struct ast* a = malloc(sizeof(struct ast));

    if (!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'N';
    a->number = d;
    return (struct ast*)a;
}

double eval(struct ast* a) {
    double v;
    if (!a) {
        yyerror("internal error, null eval");
        return 0.0;
    }
    switch (a->nodetype) {
    case 'N': v = a->number; break;
    case 'M': v = -eval(a->l); break;
    case '+': v = eval(a->l) + eval(a->r); break;
    case '-': v = eval(a->l) - eval(a->r); break;
    case '*': v = eval(a->l) * eval(a->r); break;
    case '/': v = eval(a->l) / eval(a->r); break;
    default: printf("internal error: bad node $c\n", a->nodetype);
    }
    return v;
}

void treefree(struct ast* a) {
    switch (a->nodetype) {
    case '+':
    case '-':
    case '*':
    case '/':
        treefree(a->r);
        treefree(a->l);
        break;
    case 'N':
    case 'M':
        break;
    default:
        printf("internal error: free bad nod $c\n", a->nodetype);
    }
    free(a);
}

void yyerror(char* s, ...) {
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
