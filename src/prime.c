#include <stdbool.h>
#include <math.h>

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }

    if (num < 4)
        return true;

    int s = floor(sqrt((double)num));

    if ((num % 2) == 0) { return 0; }
    for (int i = 3; i <= s; i += 2) {
        if ((num % i) == 0) {
            return 0;
        }
    }

    return true;
}

int next_prime(int num) {
    num++;
    while (!is_prime(num)) {
        num++;
    }
    return num;
}
