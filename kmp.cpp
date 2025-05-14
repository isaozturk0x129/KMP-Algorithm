#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

vector<int> LPSArray(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int length = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void KMPSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) {
        cout << "Örüntü boş olamaz." << endl;
        return;
    }
    if (n == 0) {
        cout << "Metin boş olamaz." << endl;
        return;
    }
    if (m > n) {
        cout << "Örüntü metinden daha uzun olamaz." << endl;
        return;
    }

    vector<int> lps = LPSArray(pattern);
    vector<int> foundIndices;

    int i = 0;
    int j = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            foundIndices.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    if (!foundIndices.empty()) {
        for (int index : foundIndices) {
            cout << "Örüntü " << index << ". indekste bulundu." << endl;
        }
    } else {
        cout << "Örüntü metin içinde bulunamadı." << endl;
    }
}

int main() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    string userinput;
    string userpattern;
    cout << "Ana Metni Giriniz: ";
    getline(cin, userinput);
    cout << userinput << endl;
    cout << "Aranacak Örüntüyü Giriniz: ";
    getline(cin, userpattern);
    cout << userpattern << endl;
    cout << endl;
    KMPSearch(userinput, userpattern);

    return 0;
}