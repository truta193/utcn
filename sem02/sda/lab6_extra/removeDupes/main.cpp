#include <iostream>
#include <fstream>
#include <vector>

#define NRMODULO 101
#define EMPTY -1
#define DELETED -2

using namespace std;

int hashFunction(int key) {
    return key % NRMODULO;
}

int probeFunction(int key, int attempt) {
    return ((key & NRMODULO) + attempt) % NRMODULO;
}

int main() {
    ifstream fin("../date.in", ios::in);
    int nrElem;
    fin >> nrElem;
    vector<int> arr;
    int i = 0;
    for (i = 0; i < nrElem; i++) {
        int n;
        fin >> n;
        arr.push_back(n);
    }

    int hash[i];
    for (int j = 0; j < i; j++) {
        hash[j] = EMPTY;
    }

    for (int j =  0; j < i; j++) {
        int idx = hashFunction(arr[j]);
        bool dupe = false;
        for (int k = 0; k < i; k++) {
            if (hash[probeFunction(idx, k)] == arr[j]) {
                //hash[probeFunction(idx, k)] = DELETED;
                dupe = true;
                break;
            }
        }
        if (!dupe) {
            for (int k = 0; k < i; k++) {
                if (hash[probeFunction(idx, k)] == EMPTY || hash[probeFunction(idx, k)] == DELETED) {
                    hash[probeFunction(idx, k)] = arr[j];
                    break;
                }
            }
        }

    }

    for (int j = 0; j < i; j++) {
        if ((hash[j] != EMPTY) || (hash[j] != DELETED)){
            cout << hash[j] << endl;
        }
    }



    return 0;
}
