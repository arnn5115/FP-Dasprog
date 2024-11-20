#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int cPow(int base, int exponent){
    if (exponent == 0) return 1;
    return (exponent < 2) ? base : base * cPow(base-1, exponent);
}

void generateQuestion(int nDigitA, int nDigitB){
    srand(time(NULL));
    int ans;
    int a = rand() % cPow(10, nDigitA)+1;
    int b = rand() % cPow(10, nDigitB)+1;
    printf("%d x %d =", a, b);
    scanf("%d", &ans);
    if (ans == a*b) printf("Benar");
    else printf("Salah");
    return;
}

clock_t startTimer() {
    return clock();
}

void diffSelector(int diff){
    switch (diff) {
    case 1:
        generateQuestion(1, 1);
        break;
    case 2:
        generateQuestion(2, 1);
        break;
    case 3:
        generateQuestion(2, 2);
        break;
    case 4:
        generateQuestion(3, 2);
        break;
    case 5:
        generateQuestion(3, 3);
        break;
    default:
        // Error Handling
        break;
    }
}

int main(){
    char str1[10];
    printf("Pilih Tingkat Kesulitan :");
    printf("easy \n");
    printf("medium \n");
    printf("hard \n");
    printf("insane \n");
    printf("impossible");
    

    scanf("%9s", &str1);
    if (!strcmp(str1,"easy"))
    {
        diffSelector(1);
    }else if (!strcmp(str1, "medium"))
    {
        diffSelector(2);
    }else if (!strcmp(str1, "hard"))
    {
        diffSelector(3);
    }else if (!strcmp(str1, "insane"))
    {
        diffSelector(4);
    }else if (!strcmp(str1, "impossible"))
    {
        diffSelector(5);
    }
    return 0;
}