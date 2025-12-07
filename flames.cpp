#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
void sleep_ms(int ms){ Sleep(ms); }
#else
#include <unistd.h>
void sleep_ms(int ms){ usleep(ms*1000); }
#endif

void typePrint(const char *s,int d){
    for(int i=0;s[i];i++){
        putchar(s[i]);
        fflush(stdout);
        sleep_ms(d);
    }
}

void cleanStr(char *s){
    int j=0;
    for(int i=0;s[i];i++){
        if(s[i]!=' ') s[j++]=tolower(s[i]);
    }
    s[j]='\0';
}

int countRemaining(char a[],char b[]){
    int used[200]={0}, count=0;
    for(int i=0;a[i];i++){
        int found=0;
        for(int j=0;b[j];j++){
            if(!used[j] && a[i]==b[j]){
                used[j]=1;
                found=1;
                break;
            }
        }
        if(!found) count++;
    }
    for(int j=0;b[j];j++){
        if(!used[j]) count++;
    }
    return count;
}

char* mapResult(char c){
    switch(c){
        case 'F': return "Friends";
        case 'L': return "Love";
        case 'A': return "Affection";
        case 'M': return "Marriage";
        case 'E': return "Enemies";
        case 'S': return "Siblings";
    }
    return "Unknown";
}

void flamesAnimation(int count){
    char flames[]="FLAMES";
    int len=6;

    printf("\nCalculating FLAMES");
    for(int i=0;i<5;i++){
        printf(".");
        fflush(stdout);
        sleep_ms(300);
    }
    printf("\n\n");

    while(len>1){
        int removeIndex=(count%len)-1;
        if(removeIndex<0) removeIndex=len-1;

        printf("Removing: %c\n", flames[removeIndex]);
        sleep_ms(400);

        for(int k=removeIndex;k<len-1;k++){
            flames[k]=flames[k+1];
        }
        len--;
    }

    printf("\nFinal Letter: %c\n", flames[0]);
    printf("Result: %s\n", mapResult(flames[0]));
}

int main(){
    char boy[200], girl[200];

    printf("Enter Boy Name: ");
    fgets(boy, sizeof(boy), stdin);
    boy[strcspn(boy,"\n")]=0;

    printf("Enter Girl Name: ");
    fgets(girl, sizeof(girl), stdin);
    girl[strcspn(girl,"\n")]=0;

    printf("\nProcessing: ");
    typePrint(boy, 30);
    printf(" & ");
    typePrint(girl, 30);
    printf("\n\n");

    cleanStr(boy);
    cleanStr(girl);

    int count = countRemaining(boy, girl);
    if(count==0) count=1;

    flamesAnimation(count);

    return 0;
}

