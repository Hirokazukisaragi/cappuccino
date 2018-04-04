#ifndef __GENCODE__
#define __GENCODE__
typedef struct{
    short int incode;
    char *rawcode;
}KEYTBL;
/*
KEYTBL STable{
    {IF_CODE,"if"},
    {PRINT_CODE,"print"},
    {GOTO_CODE,"goto"},
    {WHILE_CODE,"while"},
    {END_CODE,"end"},
    {THEN_CODE,"then"},
};
*/
#define TRUE 1
#define FALSE 0
#endif
