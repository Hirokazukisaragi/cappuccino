#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "immcode.h"
#include <boost/compute/source.hpp>
#include <boost/compute/source.hpp>
#define MAX_SRC_LEN 65553
void endgine(void);
void Printer(void);
void expr(int idx,int lval,char ch);
int calVal(int idx,char ch);
void addval(int idx,int lval);
void subval(int idx,int lval);
void mulval(int idx,int lval);
void divval(int idx,int lval);
void value_system(void);
static int Value[26];
static FILE *src;
static char command[80];
int main(int argc, char **argv) {
    static int pc = 0;
    static char direct_mode = 0;
    static char *source;
    
    source = (char *)malloc(MAX_SRC_LEN);
    if(argc==1){
        direct_mode = 1;
        src = stdin;
    }else{
    src = fopen(argv[1],"r");
    }
    srand(time(NULL));
    endgine();
    return 0;
}
void endgine(void)
{
    char contflag = 1;
    char commc = 0;
    while(feof(src) == 0){
        command[commc] = getc(src);
        if(feof(src)){
            break;
        }
        while((command[commc] != ' ') && (command[commc] != '\t') && (command[commc] != '\n') && (command[commc] != '\0') ){
            commc++;
            command[commc] = getc(src);
            if(feof(src)){
                break;
            }
            //ungetc(command[commc],src);
        }
        
        command[commc] = '\0';
        if(!strcmp(command,"print")){
            //ungetc(command[commc],src);
            Printer();
        }
        if(!strcmp(command,"let")){
            value_system();
        }
        command[0] = '\0';
        commc = 0;
    }
}
void value_system()
{
    int idx;
    int lindx;
    int lval,rval;
    int num;
    char ch;
    idx = getc(src);
    ch = idx;
    //変数インデックス以外なら
    while((idx < 'A') && (idx > 'Z')){
    printf("skip whitespace\n");
        idx = getc(src);
    }
    
    ch = idx;
    idx = idx - 'A';
    ch = getc(src);
    while((ch == ' ') || (ch == '\t')) {
        ch = getc(src);
    }
    if(ch == '='){
        ch = getc(src);
    }else{
        printf("syntax error!\n");
    }
    
    //ch = getc(src);
    while((ch == ' ')){
        ch = getc(src);
    }
    if((ch >= '0') && (ch <= '9')){
        lval = calVal(idx,ch);
    }else if((ch >= 'A') && (ch <= 'Z')){
        lindx = ch - 'A';
        lval = Value[lindx];
    }
    expr(idx,lval,ch);

}

void Printer(void)
{
    char ch;
    int vindex;
    char first = TRUE;
    ch = getc(src);
    char stringflag = FALSE;
     while((ch == ' ') || (ch == '\t') || (ch == '\n')){
        ch = getc(src);
    }
    if(ch == '\"'){
        stringflag = TRUE;
    }
    //変数でないかつクォートが出るまで
    while(stringflag){
        if((ch == '\"')){
            if(first){
                ch = getc(src);
                first = FALSE;
                continue;
            }
            stringflag = FALSE;
            break;
        }
        if((ch == '\n') || (ch == '\0')){
            printf("FATAL ERORR!:%c:\n",ch);
            break;
        }
        printf("%c",ch);

        ch = getc(src);
        first = FALSE;
    };
    if((ch >= 'A') && (ch <= 'Z')){
        vindex = ch - 'A';
        printf("%d",Value[vindex]);
    }
    printf("\n");
}
int calVal(int idx, char ch){
    int num;
    num = ch - '0';
    ch = getc(src);
    while((ch >= '0') && (ch <= '9')){
        //printf("%d",num);
        num *= 10;
        num += ch - '0';
        ch = getc(src);
    }
    ungetc(ch,src);
    Value[idx] = num;
    return num; 
}
void addval(int idx,int lval){
    char ch = getc(src);
    int rval;
    int num;
    while((ch == ' ') || (ch == '\n')){
        ch =getc(src);
    }
    if((ch >= '0') && (ch <= '9')){
    num = ch - '0';
    ch = getc(src);
    }
    //ch = getc(src);
    while((ch >= '0') && (ch <= '9')){
        num *= 10;
        num += ch - '0';
        ch = getc(src);
    }
    if((ch >= 'A') && (ch <= 'Z')){
        rval = ch - 'A';
        num = Value[rval];

    printf("rval=:%d\n",num);
    }
    Value[idx] = lval + num;
}
void subval(int idx,int lval){
    char ch = getc(src);
    int rval;
    int num;
    while((ch == ' ') || (ch == '\n')){
        ch =getc(src);
    }
    if((ch >= '0') && (ch <= '9')){
    num = ch - '0';
    ch = getc(src);
    }
    //ch = getc(src);
    while((ch >= '0') && (ch <= '9')){
        num *= 10;
        num += ch - '0';
        ch = getc(src);
    }
    if((ch >= 'A') && (ch <= 'Z')){
        rval = ch - 'A';
        num = Value[rval];

    }
    Value[idx] = lval - num;
}
void mulval(int idx,int lval){
    char ch = getc(src);
    int rval;
    int num;
    while((ch == ' ') || (ch == '\n')){
        ch =getc(src);
    }
    if((ch >= '0') && (ch <= '9')){
    num = ch - '0';
    ch = getc(src);
    }
    //ch = getc(src);
    while((ch >= '0') && (ch <= '9')){
        num *= 10;
        num += ch - '0';
        ch = getc(src);
    }
    if((ch >= 'A') && (ch <= 'Z')){
        rval = ch - 'A';
        num = Value[rval];

    printf("rval=:%d\n",num);
    }
    Value[idx] = lval * num;
}
void divval(int idx,int lval){
    char ch = getc(src);
    int rval;
    int num;
    while((ch == ' ') || (ch == '\n')){
        ch =getc(src);
    }
    if((ch >= '0') && (ch <= '9')){
    num = ch - '0';
    ch = getc(src);
    }
    //ch = getc(src);
    while((ch >= '0') && (ch <= '9')){
        num *= 10;
        num += ch - '0';
        ch = getc(src);
    }
    if((ch >= 'A') && (ch <= 'Z')){
        rval = ch - 'A';
        num = Value[rval];

    }
    Value[idx] = lval / num;
}
void expr(int idx,int lval,char ch){
        ch = getc(src);
    
    while((ch == ' ') && (ch != '+') && (ch != '-') && (ch != '*') && (ch != '/')){
        ch = getc(src);
    }
    

       switch(ch){
        case '+':
            addval(idx,lval);
            break;
        case '-':
            subval(idx,lval);
            break;
        case '*':
            mulval(idx,lval);
            break;
        case '/':
            divval(idx,lval);
            break;
    }
}
