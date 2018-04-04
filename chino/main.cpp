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
            //printf("next:%c\n",command[commc]);
            //ungetc(command[commc],src);
        }
        /*
        if((command[commc] != ' ') || (command[commc] != '\n') ){
            printf("unget:%c:\n",command[commc]);
            ungetc(command[commc],src);
            command[commc] = '\0';
        }
        */
        command[commc] = '\0';
        if(!strcmp(command,"print")){
            //ungetc(command[commc],src);
            Printer();
        }
        if(!strcmp(command,"let")){
            value_system();
        }
        /*
        if(!feof(src)){
            contflag = 0;
        }
        */
        command[0] = '\0';
        commc = 0;
    }
}
void value_system()
{
    int idx;
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
    num = ch - '0';
    ch = getc(src);
    while((ch >= '0') && (ch <= '9')){
        //printf("%d",num);
        num *= 10;
        num += ch - '0';
        ch = getc(src);
    }
    Value[idx] = num;
}

void Printer(void)
{
    char ch;
    int vindex;
    char first = TRUE;
    ch = getc(src);
    int loopcounter = 0;
    //printf("ap=%c:",ch);
    char stringflag = FALSE;
     while((ch == ' ') || (ch == '\t') || (ch == '\n')){
        ch = getc(src);
       // printf("skip = %c",ch);
    }
    if(ch == '\"'){
        stringflag = TRUE;
    }
    //ch = getc(src);
    //printf("askip=%c:",ch);
    //変数でないかつクォートが出るまで
    while(stringflag){
        /*
        while(ch == ' '){
            ch = getc(src);
        }
        */
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
        //printf("loop %d done.",loopcounter);
        loopcounter++;
        first = FALSE;
    }
    //ch = getc(src);
    if((ch >= 'A') && (ch <= 'Z')){
        vindex = ch - 'A';;
        printf("val = :%d:\n",Value[vindex]);
    }
    printf("\n");
}
