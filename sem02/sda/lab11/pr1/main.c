#include <stdio.h>
#include <stdlib.h>

int main() {
    int nrCoins, sum;
    scanf("%d %d", &nrCoins, &sum);
    int *coins = malloc((nrCoins) * sizeof(int));
    for (int i = 0; i < nrCoins; i++) {
        scanf("%d", &coins[i]);
    }
    int *max = malloc((sum + 1) * sizeof(int));
    max[0] = 1;

    for (int i = 0; i < nrCoins; i++) {
        for (int j = coins[i]; j < sum+1; j++) {
            max[j] += max[j - coins[i]];
        }
    }

    printf("%d\n", max[sum]);
    return 0;
}
