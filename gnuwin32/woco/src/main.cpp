#include <iostream>
#include "lex.h"

extern "C" int yylex();
extern "C" void yyrestart(FILE * input_file);

extern "C" int chars;
extern "C" int words;
extern "C" int lines;

extern "C" int totchars;
extern "C" int totwords;
extern "C" int totlines;

int main(int argc, char** argv) {
    std::cout << "start count." << std::endl;

    if (argc < 2) {
        yylex();
        printf("%8d%8d%8d\n", lines, words, chars);
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        std::cout << "open: " << argv[i] << std::endl;

        FILE* f = fopen(argv[i], "r");
        if (!f) {
            perror(argv[i]);
            return 1;
        }
        yyrestart(f);
        yylex();
        fclose(f);

        std::cout << "lines: " << lines << std::endl;
        printf("%8d%8d%8d %s\n", lines, words, chars, argv[i]);
        totchars += chars;
        chars = 0;
        totwords += words;
        words = 0;
        totlines += lines;
        lines = 0;
    }

    if (argc > 1) {
        printf("%8d%8d%8d total\n", totlines, totwords, totchars);
    }

    return 0;
}
