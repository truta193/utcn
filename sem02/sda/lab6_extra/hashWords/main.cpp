#include <iostream>
#include <cstring>

typedef struct HashNode {
    char *word;
    HashNode *next;
} HashNodeT;

int hashCode(char *word) {
    int sum = 0;
    int count = 0;
    while (*word != '\0') {
        sum += *word;
        count++;
        word++;
    }
    return sum / count;
}

int hashFunc(int code, int modulo) {
    return code % modulo;
}

int main() {
    HashNodeT **hash = nullptr;
    hash = (HashNodeT**)malloc(sizeof(HashNodeT*)*10);
    int n = 10;
    int m = 7;
    memset(hash, 0, 10*sizeof(HashNodeT*));
    for (int i = 0; i < n; i++) {
        char buf[100] = {0};
        scanf("%s", buf);
        int idx = hashFunc(hashCode(buf), m);

        HashNodeT *node = (HashNodeT*) malloc(sizeof(HashNodeT));
        node->word = strdup(buf);
        //If node is empty
        if (hash[idx] == nullptr) {
            hash[idx] = node;
            continue;
        }

        //If there's only 1 node
        if (hash[idx] != nullptr && hash[idx]->next == nullptr) {
            hash[idx]->next = node;
            continue;
        }

        //If we have to insert it, find last node
        HashNodeT *cursor = hash[idx];
        while (cursor->next != nullptr) cursor = cursor->next;
        cursor->next = node;


    }

    for (int i = 0; i < 10; i++) {
        HashNodeT* current = hash[i];
        while(current != nullptr) {
            printf("%s\n", current->word);
            current = current->next;
        }
    }

    return 0;
}
