#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory.h>

int main() {
    int nrCoins, sum;
    scanf("%d %d", &nrCoins, &sum);
    int *coins = malloc((nrCoins) * sizeof(int));
    for (int i = 0; i < nrCoins; i++) {
        scanf("%d", &coins[i]);
    }

    int *max = malloc((sum + 1) * sizeof(int));

    for (int i = 0; i < sum+1; i++) {
        max[i] = INT_MAX;
    }

    max[0] = 0;

    for (int i = 0; i < nrCoins; i++) {
        for (int j = coins[i]; j <= sum; j++) {
            if (max[j-coins[i]] + 1 < max[j]) {
                max[j] = max[j-coins[i]] + 1;
            }
        }
    }

    printf("%d\n", max[sum]);
    return 0;
}
