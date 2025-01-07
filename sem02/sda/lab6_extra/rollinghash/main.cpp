#include <iostream>
#include "rollingHash.h"
#include <string>
#include <fstream>


using namespace std;
int main() {
    string text;
    string pattern;
    int cand = 0;
    ifstream fin("../date.in", ios::in);
    fin >> text;
    while (fin >> pattern) {
        int pHash = hashingFunction(pattern.length(),pattern);
        string window = text.substr(0, 3);
        int wHash = hashingFunction(window.length(), window);
        if (pHash == wHash) cand++;
        cout << pHash << " " << wHash << endl;

        for (int i = 1; i < text.length() - pattern.length(); i++) {
            wHash = rollHash(pattern.length(), text.substr(i, pattern.length()), wHash);
            if (wHash == pHash)
                cand++;
            cout << pHash <<" " << wHash << endl;

        }
    }

    cout << cand << endl;
    return 0;
}
