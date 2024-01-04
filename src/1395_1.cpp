#include <iostream>

using namespace std;

using uint32 = unsigned int;

const int bit_num = 32;

int N, M;
uint32 switches[3126] = { 0, };

void print_bits(uint32 bits) {
    for(int i=bit_num-1; i>=0; i--) {
        printf("%d ", (bits & (1 << i)) ? 1 : 0);
    }
    printf("\n\n");
}

inline int popcount(uint32 bits) {
    return __builtin_popcount(bits);
}

uint32 make_mask(int l, int r) {
    uint32 mask = 0;
    for(int i=31-r; i<=31-l; i++) {
        mask |= 1<<i;
    }

    //print_bits(mask);

    return mask;
}

void BitsFlip(int l, int r) {
    int l_index = l / bit_num;
    int l_shift = l % bit_num;

    int r_index = r / bit_num;
    int r_shift = r % bit_num;

    for(int i=l_index+1; i<=r_index-1; i++) {
        switches[i] = ~switches[i];
    }

    if(l_index == r_index) {
        uint32 mask = make_mask(l_shift, r_shift);
        uint32 bits = ~switches[l_index] & mask;
        bits |= switches[l_index] & ~mask;
        switches[l_index] = bits;
        return;
    }

    uint32 mask = make_mask(l_shift, bit_num-1);
    uint32 bits = ~switches[l_index] & mask;
    bits |= switches[l_index] & ~mask;
    switches[l_index] = bits;

    mask = make_mask(0, r_shift);
    bits = ~switches[r_index] & mask;
    bits |= switches[r_index] & ~mask;
    switches[r_index] = bits;
}

int BitsCnt(int l, int r) {
    int ret = 0;

    int l_index = l / bit_num;
    int l_shift = l % bit_num;

    int r_index = r / bit_num;
    int r_shift = r % bit_num;

    for(int i=l_index+1; i<=r_index-1; i++) {
        ret += popcount(switches[i]);
    }

    if(l_index == r_index) {
        uint32 mask = make_mask(l_shift, r_shift);
        uint32 bits = switches[l_index] & mask;
        ret += popcount(bits);
        return ret;
    }
    
    uint32 mask = make_mask(l_shift, bit_num-1);
    uint32 l_bits = switches[l_index] & mask;
    ret += popcount(l_bits);

    mask = make_mask(0, r_shift);
    uint32 r_bits = switches[r_index] & mask;
    ret += popcount(r_bits);

    return ret;
}

int main() {
    scanf("%d %d", &N, &M);
    int o, s, t;
    for(int i=0; i<M; i++) {
        scanf("%d %d %d", &o, &s, &t);
        s--; t--;

        if(o == 0) {
            BitsFlip(s, t);
        } else if(o == 1) {
            int result = BitsCnt(s, t);
            printf("%d\n", result);
        }
    }
}