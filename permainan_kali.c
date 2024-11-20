#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>

clock_t startTimer() {
    return clock();
}
int cPow(int base, int exponent){
    if (exponent == 0) return 1;
    return (exponent < 2) ? base : base * cPow(base, exponent-1);
}

void loading(){
    char spinner[] = {'|', '/', '-', '\\'};
    int loading = 100000;
    
    printf("  __  __       _ _   _       _ _           _   _               _____  _         \n");
    printf(" |  \\/  |     | | | (_)     | (_)         | | (_)             |  __ \\(_)        \n");
    printf(" | \\  / |_   _| | |_ _ _ __ | |_  ___ __ _| |_ _  ___  _ __   | |__) |_ ________\n");
    printf(" | |\\/| | | | | | __| | '_ \\| | |/ __/ _` | __| |/ _ \\| '_ \\  |  _  /| |_  /_  /\n");
    printf(" | |  | | |_| | | |_| | |_) | | | (_| (_| | |_| | (_) | | | | | | \\ \\| |/ / / / \n");
    printf(" |_|  |_|\\__,_|_|\\__|_| .__/|_|_|\\___\\__,_|\\__|_|\\___/|_| |_| |_|  \\_\\_/___/___|\n");
    printf("                      | |                                                        \n");
    printf("                      |_|                                                        \n");

    printf("Loading... ");
    for (int i = 0; i < 20; i++) {
        printf("\b%c", spinner[i % 4]);
        fflush(stdout);
        usleep(loading);   // Tunggu selama 0,1 detik
    }
}

int generateQuestion(int nDigitA, int nDigitB, double timer){
    srand(time(NULL));
    int ans;
    char sAns[100];
    int benar;
    int i = 0;
    int a = rand() % cPow(10, nDigitA)+1;
    int b = rand() % cPow(10, nDigitB)+1;
    printf("Sisa Waktu: %.0lf detik", timer);
    printf("\n%d x %d = ", a, b);
    
    fflush(stdout);
    clock_t start = startTimer();
    while (((double)(clock() - start)) / CLOCKS_PER_SEC < timer){
        // int remainingTime = timer - (int)(((double)(clock() - start)) / CLOCKS_PER_SEC);
        // printf("\rYou have %d seconds to input your answer:  ", remainingTime);
        // fflush(stdout);
        
        if (_kbhit()){
            char ch = _getch();
            if (ch == '\r'){
                sAns[i] = '\0';
                break;
            }
            if ((ch == '\b') && (i > 0)){ // i > 0 ga berfungsi
                i--;
                printf("\b \b");
                continue;
            }
            if (i < sizeof(sAns)-1){
                sAns[i++] = ch;
                printf("%c", ch);
            }
        }
    }

    sAns[i] = '\0';
    ans = atoi(sAns);
    printf("\nJawaban kamu %d ",ans);
    if (ans == a*b) {
        printf("(BENAR)");
        benar = 1;
    }
    else {
        printf("(SALAH)");
        benar = 0;
    }
    printf("!\n");
    return benar;
}

int diffSelector(int diff){
    int questionScore = 0;    
    switch (diff) {
    case 1:
        if(generateQuestion(1, 1, 5.0)){
            questionScore = 1;
        }
        break;
    case 2:
        if(generateQuestion(2, 1, 10.0)){
            questionScore = 2;
        }
        break;
    case 3:
        if(generateQuestion(2, 2, 30.0)){
            questionScore = 3;
        }
        break;
    case 4:
        if(generateQuestion(3, 2, 30.0)){
            questionScore = 4;
        }
        break;
    case 5:
        if(generateQuestion(3, 3, 60.0)){
            questionScore = 5;
        }
        break;
    default:
        // Error Handling
        break;
    }
    return questionScore;
}

int main(){    
    // loading(); // comment if debugging
    
    char inputStr[10];
    int score = 0;
    
    printf("--------------------------------------\n");
    printf("\nTingkat Kesulitan :\n");
    printf("--------------------------------------\n");
    printf("   1 - Easy\n");
    printf("   2 - Medium\n");
    printf("   3 - Hard\n");
    printf("   4 - Insane\n");
    printf("   5 - Impossible\n");
    printf("   0 - Quit\n");
    printf("--------------------------------------\n");
    while(1) {
        printf("Pilih Tingkat Kesulitan : ");   
        scanf("%9s", inputStr);

        for(int i=0; inputStr[i] != '\0'; i++){
            inputStr[i]= tolower(inputStr[i]);
        }

        if(!strcmp(inputStr, "quit") || !strcmp(inputStr,"0")){
            break;
        }
        printf("--------------------------------------\n");

        if (!strcmp(inputStr, "easy") || !strcmp(inputStr,"1")){
            score += diffSelector(1);
        }
        else if (!strcmp(inputStr, "medium") || !strcmp(inputStr,"2")){
            score += diffSelector(2);
        }
        else if (!strcmp(inputStr, "hard") || !strcmp(inputStr,"3")){
            score += diffSelector(3);
        }
        else if (!strcmp(inputStr, "insane") || !strcmp(inputStr,"4")){
            score += diffSelector(4);
        }
        else if (!strcmp(inputStr, "impossible") || !strcmp(inputStr,"5")){
            score += diffSelector(5);
        }
        printf("--------------------------------------\n");
        fflush(stdin);
    }
    printf("--------------------------------------\n");
    printf("Terimakasih telah bermain\n");
    printf("Score akhir kamu adalah %d\n", score);
    printf("---------- Program Berhenti ----------\n");
    
    return 0;
}











