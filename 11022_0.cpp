#include <iostream>
int main() {
    int test_case;
    scanf("%d", &test_case);
    for (int i = 1; i <= test_case; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("Case #%d: %d + %d = %d\n", i, x, y, x + y);
    }
}