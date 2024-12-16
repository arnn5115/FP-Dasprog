#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>

// define the text format escape sequences
#define SIGMA "\e[1;97;103m"
#define BENAR "\e[1;97;102m"
#define SALAH "\e[1;97;101m"
#define BOLD  "\e[1;97m"
#define RESET "\e[0m" 

clock_t startTimer() {
    return clock();
}

int pangkat(int base, int exponent){
    if (exponent == 0) return 1;
    return (exponent < 2) ? base : base * pangkat(base, exponent-1);
}

void loading(){
    char spinner[] = {'|', '/', '-', '\\'};
    int loading = 100000; //in µs
    
    printf("  __  __       _ _   _       _ _           _   _               _____  _         \n");
    printf(" |  \\/  |     | | | (_)     | (_)         | | (_)             |  __ \\(_)        \n");
    printf(" | \\  / |_   _| | |_ _ _ __ | |_  ___ __ _| |_ _  ___  _ __   | |__) |_ ________\n");
    printf(" | |\\/| | | | | | __| | '_ \\| | |/ __/ _` | __| |/ _ \\| '_ \\  |  _  /| |_  /_  /\n");
    printf(" | |  | | |_| | | |_| | |_) | | | (_| (_| | |_| | (_) | | | | | | \\ \\| |/ / / / \n");
    printf(" |_|  |_|\\__,_|_|\\__|_| .__/|_|_|\\___\\__,_|\\__|_|\\___/|_| |_| |_|  \\_\\_/___/___|\n");
    printf("                      | |                                                        \n");
    printf("                      |_|                                                        \n");

    printf("Loading(  ");
    for (int i = 0; i < 20; i++) {
        printf("\b\b%c)", spinner[i % 4]);
        fflush(stdout);
        usleep(loading);   // Tunggu selama 0,1 detik
    }
    printf("\b\b\b Complete.");
}

int generateQuestion(int nDigitA, int nDigitB, double timer){
    srand(time(NULL));
    int ans;
    char sAns[100];
    int benar;
    int i = 0;
    int a = rand() % pangkat(10, nDigitA)+1;
    int b = rand() % pangkat(10, nDigitB)+1;
    printf("Sisa Waktu: %s%.0lf%s detik\n", BOLD, timer, RESET);
    printf("%s%d x %d = ", BOLD, a, b);
    
    fflush(stdout);
    fflush(stdin);
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
    printf("%s\nJawaban kamu ", RESET);
    if (ans == a*b) {
        printf("%sBENAR%s", BENAR, RESET);
        benar = 1;
    }
    else {
        printf("%sSALAH%s", SALAH, RESET);
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
    loading(); // comment if debugging
    
    char inputStr[10];
    int score = 0;
    
    printf("\n--------------------------------------\n");
    printf("Tingkat Rizz :\n");
    printf("--------------------------------------\n");
    printf("   1 - Big L\n");
    printf("   2 - Beta\n");
    printf("   3 - Normal\n");
    printf("   4 - Alpha\n");
    printf("   5 - %sSigma%s\n", SIGMA, RESET);
    printf("--------------------------------------\n");
    printf("   0 - Keluar\n");
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











