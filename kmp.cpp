#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

// LPS (Longest Prefix Suffix) dizisini oluşturur
vector<int> LPSArray(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0); // LPS dizisi başlangıçta sıfırlarla doldurulur
    int length = 0; // Önceki en uzun prefix-suffix uzunluğu
    int i = 1;

    // LPS dizisini oluşturmak için döngü
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

// KMP (Knuth-Morris-Pratt) algoritması ile örüntü arama
void KMPSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    // Özel durumlar için kontroller
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

    // LPS dizisini oluştur
    vector<int> lps = LPSArray(pattern);
    vector<int> foundIndices; // Bulunan örüntü indekslerini saklar

    int i = 0; // Metin için indeks
    int j = 0; // Örüntü için indeks

    // Metin içinde örüntüyü arama döngüsü
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) { // Örüntü bulunduğunda
            foundIndices.push_back(i - j); // Bulunan indeks kaydedilir
            j = lps[j - 1]; // Örüntüdeki bir sonraki eşleşme için ilerle
        } else if (i < n && pattern[j] != text[i]) { // Eşleşme başarısız olduğunda
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    // Bulunan indeksleri yazdır
    if (!foundIndices.empty()) {
        for (int index : foundIndices) {
            cout << "Örüntü " << index << ". indekste bulundu." << endl;
        }
    } else {
        cout << "Örüntü metin içinde bulunamadı." << endl;
    }
}

int main() {
    // Konsolu temizle (platforma bağlı olarak)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    string userinput; // Kullanıcıdan alınacak metin
    string userpattern; // Kullanıcıdan alınacak örüntü

    // Kullanıcıdan metin ve örüntü girişi al
    cout << "Ana Metni Giriniz: ";
    getline(cin, userinput);
    cout << userinput << endl;
    cout << "Aranacak Örüntüyü Giriniz: ";
    getline(cin, userpattern);
    cout << userpattern << endl;
    cout << endl;

    // KMP algoritmasını çağır
    KMPSearch(userinput, userpattern);

    return 0;
}
