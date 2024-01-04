#include <stdio.h>

long long sigma_n(long long param_n) { //sum(n), n까지의 합을 반환하는 함수
    return (param_n*(param_n+1))/2;
}

long long convertStepToDistance(int param_step) { //이동횟수가 주어졌을 때 최대 이동거리를 반환하는 함수
    long long distance = 0;

    if(param_step <= 2) {return param_step;}

    if(param_step%2==0) {
        distance = sigma_n(param_step/2)*2;
    } else {
        distance = sigma_n((param_step-1)/2)*2+((param_step-1)/2)+1;
    }

    return distance;
}

int main() {
    long long input_x=0, input_y=0;
    long long distance=0;
    long long count_move=1, count_input=0;
    long long index=0;

    count_input=0;
    scanf("%lld", &count_input);

    for(index=0; index<count_input; index++) {
        input_x=0, input_y=0, count_move=1;
        scanf("%lld %lld", &input_x, &input_y);

        distance = input_y-input_x;

        //최대 이동거리가 x지점과 y지점 사이의 거리보다 큰 값을 만족하는 n값을 찾는다.
        while(distance > convertStepToDistance(count_move)) {
            count_move++;
        }

        printf("%d\n", count_move);
    }

    return 0;
}