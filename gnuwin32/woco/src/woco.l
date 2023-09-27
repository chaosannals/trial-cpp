%option noyywrap
%{
    #include "lex.h"
    int chars = 0;
    int words = 0;
    int lines = 0;

    int totchars = 0;
    int totwords = 0;
    int totlines = 0;
%}

%%

[^ \t\n\r\f\v]+ { words++; chars += strlen(yytext); }
\n { chars++; lines++; }
. { chars++; }

%%
