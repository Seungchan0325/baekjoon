#include <stdio.h>

int TransToTime(char dial);

int TransToTime(char dial)
{
    int times = 2;
    if (dial >= 'A' && dial <= 'C') {
        times += 1;
    } else if (dial >= 'D' && dial <= 'F') {
        times += 2;
    } else if (dial >= 'G' && dial <= 'I') {
        times += 3;
    } else if (dial >= 'J' && dial <= 'L') {
        times += 4;
    } else if (dial >= 'M' && dial <= 'O') {
        times += 5;
    } else if (dial >= 'P' && dial <= 'S') {
        times += 6;
    } else if (dial >= 'T' && dial <= 'V') {
        times += 7;
    } else if (dial >= 'W' && dial <= 'Z') {
        times += 8;
    } else {
        times += 8;
    }

    return times;
}

int main(int argc, char *argv[])
{
    char input_str[16];
    int i, sum = 0;

    scanf("%s", input_str);

    for (i = 0; input_str[i] != '\0'; ++i) {
        sum += TransToTime(input_str[i]);    
    }

    printf("%d\n", sum);
    return 0;
}