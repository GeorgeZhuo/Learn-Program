#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pl0.h"

#define SOURCE_FILE_NAME "first.pl0"

int main()
{
    init();
    fPointer = fopen(SOURCE_FILE_NAME, "r");    //Open file with readonly mode
    print_source_file(fPointer);
    fseek(fPointer, 0, SEEK_SET);   //Go to head of file

    printf("Begin lexical analysis\n");
    lexical_analysis();
    fclose(fPointer);

    parsing_analysis(0);
    /*

    */
    return 0;
}

int print_source_file()
{
    char c;
    while((c = fgetc(fPointer)) != EOF) {
        putc(c, stdout);
    }
}

int init()
{
    int i = 0;
    
    /* Initial eTypeMap */
    for (i = 0; i < 256; i++) {
        eTypeMap[i] = UNDEFINED;
    }
    for (i = 'a'; i <= 'z'; i++) {
      eTypeMap[i] = LOWERC;
    }
    for (i = 'A'; i <= 'Z'; i++) {
      eTypeMap[i] = UPPERC;
    }
    for (i = '0'; i <= '9'; i++) {
      eTypeMap[i] = DIGITC;
    }
    eTypeMap[255] = ENDOFFILE;
    eTypeMap[' '] = eTypeMap[9] = eTypeMap[10] = eTypeMap['\r'] = SEPERATER;
    eTypeMap['_'] = UNDERLINE;
    eTypeMap[':'] = COLON;
    eTypeMap['+'] = PLUS;
    eTypeMap['-'] = MINUS;
    eTypeMap['*'] = TIMES;
    eTypeMap['/'] = SLASH;
    eTypeMap['#'] = NEQL;
    eTypeMap['<'] = LSS;
    eTypeMap['>'] = GRTR;
    eTypeMap['('] = LPAREN;
    eTypeMap[')'] = RPAREN;
    eTypeMap[','] = COMMA;
    eTypeMap[';'] = SEMICOLON;
    eTypeMap['.'] = PERIOD;
    eTypeMap['='] = CONSTDEF;
    eTypeMap['{'] = BEGINSYM;
    eTypeMap['}'] = ENDSYM;
    /* End eTypeMap initial */

    /* Initial remainWordMap for match remainWord */
    strcpy(remainWordMap[0].szWord, "begin");
    strcpy(remainWordMap[1].szWord, "call");
    strcpy(remainWordMap[2].szWord, "const");
    strcpy(remainWordMap[3].szWord, "do");
    strcpy(remainWordMap[4].szWord, "end");
    strcpy(remainWordMap[5].szWord, "if");
    strcpy(remainWordMap[6].szWord, "odd");
    strcpy(remainWordMap[7].szWord, "procedure");
    strcpy(remainWordMap[8].szWord, "read");
    strcpy(remainWordMap[9].szWord, "then");
    strcpy(remainWordMap[10].szWord, "var");
    strcpy(remainWordMap[11].szWord, "while");
    strcpy(remainWordMap[12].szWord, "write");
    strcpy(remainWordMap[13].szWord, "else");

    remainWordMap[0].eType = BEGINSYM;
    remainWordMap[1].eType = CALLSYM;
    remainWordMap[2].eType = CONSTSYM;
    remainWordMap[3].eType = DOSYM;
    remainWordMap[4].eType = ENDSYM;
    remainWordMap[5].eType = IFSYM;
    remainWordMap[6].eType = ODDSYM;
    remainWordMap[7].eType = PROCSYM;
    remainWordMap[8].eType = READSYM;
    remainWordMap[9].eType = THENSYM;
    remainWordMap[10].eType = VARSYM;
    remainWordMap[11].eType = WHILESYM;
    remainWordMap[12].eType = WRITESYM;
    remainWordMap[13].eType = ELSESYM;
    /* End Initial remainWord */

    /* Initial symStringMap for Print eType */
    strcpy(symStringMap[BEGINSYM], "BEGIN");
    strcpy(symStringMap[CALLSYM], "CALL");
    strcpy(symStringMap[CONSTSYM], "CONST");
    strcpy(symStringMap[DOSYM], "DO");
    strcpy(symStringMap[ENDSYM], "END");
    strcpy(symStringMap[IFSYM], "IF");
    strcpy(symStringMap[ODDSYM], "ODD");
    strcpy(symStringMap[PROCSYM], "PROCEDURE");
    strcpy(symStringMap[READSYM], "READ");
    strcpy(symStringMap[THENSYM], "THEN");
    strcpy(symStringMap[VARSYM], "VAR");
    strcpy(symStringMap[WHILESYM], "WHILE");
    strcpy(symStringMap[WRITESYM], "WRITE");
    strcpy(symStringMap[UNDEFINED], "UNDEFINED");
    strcpy(symStringMap[IDENTIFY], "IDENTIFY");
    strcpy(symStringMap[INTEGER], "INTEGER");
    strcpy(symStringMap[FLOATNUM], "FLOAT");
    strcpy(symStringMap[PLUS], "PLUS");
    strcpy(symStringMap[MINUS], "MINUS");
    strcpy(symStringMap[TIMES], "TIMES");
    strcpy(symStringMap[SLASH], "SLASH");
    strcpy(symStringMap[EQL], "EQL");
    strcpy(symStringMap[NEQL], "NEQL");
    strcpy(symStringMap[LSS], "LSS");
    strcpy(symStringMap[LSSEQL], "LSSEQL");
    strcpy(symStringMap[GRTR], "GRTR");
    strcpy(symStringMap[GRTREQL], "GRTREQL");
    strcpy(symStringMap[LPAREN], "LPAREN");
    strcpy(symStringMap[RPAREN], "RPAREN");
    strcpy(symStringMap[COMMA], "COMMA");
    strcpy(symStringMap[SEMICOLON], "SEMICOLON");
    strcpy(symStringMap[PERIOD], "PERIOD");
    strcpy(symStringMap[BECOMES], "BECOMES");
    strcpy(symStringMap[CONSTDEF], "CONSTDEF");
    strcpy(symStringMap[ELSESYM], "ELSE");
    /* End Initial symStringMap */

    return 0;
}
