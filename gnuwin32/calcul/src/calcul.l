%option noyywrap nodefault yylineno

%{
    /* 不引入 stdlib.h 不会报错，atof 居然只给出错误的返回结果，C 果然是弱类型的。 */
    #include <stdlib.h>
    #include "calcul.h"
    #include "calcul.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"*" |
"/" |
"(" |
")" { return yytext[0]; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }

\n { return EOL; }
"//".* 
[ \t] 
\\\n { printf("c> "); }
. { yyerror("Mystery charactre %c\n", *yytext); }

%%