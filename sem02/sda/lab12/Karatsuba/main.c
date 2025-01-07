#include <stdio.h>

#define MAX(x,y) (x) > (y) ? (x) : (y)

int digitCount(int x) {
    int k = 0;
    while (x != 0) {
        k++;
        x /= 10;
    }
    return k;
}

void split(int x, int m, int* x0, int* x1) {
    int a = 0;
    for (int i = 0; i < m; i++) {
        a *= 10;
        a += x % 10;
        x = x/10;
    }

    int b = 0;
    while (x != 0) {
        b *= 10;
        b += x % 10;
        x = x/10;
    }

    int c = 0;
    while (b != 0) {
        c *= 10;
        c += b % 10;
        b = b/10;
    }

    int d = 0;
    while (a != 0) {
        d *= 10;
        d += a % 10;
        a = a/10;
    }

    *x0 = d;
    *x1 = c;


}

int pow10(int p) {
    int x = 1;
    for (int i = 0; i < p; i++) {
        x *= 10;
    }
    return x;
}

int Karatsuba(int x, int y) {
    if (x < 10 || y < 10) {
        return x * y;
    }
    int m = MAX(digitCount(x), digitCount(y)) / 2;

    int x0,x1;
    split(x,m,&x0,&x1);
    int y0,y1;
    split(y,m,&y0,&y1);

    int z0 = Karatsuba(x0,y0);
    int z2 = Karatsuba(x1,y1);
    int z1 = Karatsuba(x1+x0, y1+y0) - z2 - z0;
    return z2 * pow10(2*m) + z1*pow10(m) + z0;
}

int main() {
    printf("Hello, World!\n");
    int x = 12345;
    int y = 95699;
    printf("%d\n", Karatsuba(x,y));
    return 0;
}
