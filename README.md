# KMP Algoritması C++ Implementasyonu

Bu repo, Knuth-Morris-Pratt (KMP) string arama algoritmasının C++ için entegrasyonunu içerir. KMP algoritması, bir metin içerisinde belirli bir örüntünün (pattern) oluşumlarını verimli bir şekilde bulmak için kullanılır.

## Algoritmanın Çalışma Prensibi

KMP algoritması iki ana bölümden oluşur:

1.  **LPS (Longest Proper Prefix which is also Suffix) Dizisinin Hesaplanması:**
    *   Bu adımda, aranacak örüntü (pattern) analiz edilir.
    *   Örüntünün her bir alt ön eki (prefix) için, o alt ön ekin en uzun uygun ön ekinin (proper prefix - string'in kendisi hariç ön ek) aynı zamanda bir son ek (suffix) olduğu durumdaki uzunluk hesaplanır ve bir `lps` dizisinde saklanır.
    *   Örneğin, `pattern = "ABABC"` için `lps` dizisi `[0, 0, 1, 2, 0]` olur.
        *   `lps[0]` (A için): 0
        *   `lps[1]` (AB için): 0 (A != B)
        *   `lps[2]` (ABA için): 1 (Baştaki "A", sondaki "A" ile eşleşir)
        *   `lps[3]` (ABAB için): 2 (Baştaki "AB", sondaki "AB" ile eşleşir)
        *   `lps[4]` (ABABC için): 0 (Baştaki "A" sondaki "C" ile eşleşmez, "AB" sondaki "BC" ile eşleşmez vb.)
    *   Bu `lps` dizisi, arama sırasında uyuşmazlık olduğunda örüntünün ne kadar kaydırılacağını belirlemek için kullanılır, böylece gereksiz karşılaştırmalar önlenir.

2.  **Arama Aşaması:**
    *   Metin (text) ve örüntü (pattern) karakter karakter karşılaştırılır.
    *   Bir uyuşmazlık durumunda, `lps` dizisi kullanılarak örüntü akıllıca kaydırılır. Metin üzerinde geri gitmeye gerek kalmaz.
    *   Eğer örüntünün sonuna kadar (yani `j == m`, `m` örüntü uzunluğu) eşleşme sağlanırsa, örüntünün metin içindeki başlangıç indeksi bulunur.
    *   Aynı örüntünün metin içinde birden fazla kez bulunabilmesi için, bulunduktan sonra `j` (örüntü indeksi) `lps[j-1]` değerine ayarlanarak aramaya devam edilir.

## Dosya İçeriği

*   `kmp.cpp`: KMP algoritmasının C++ implementasyonunu ve `main` fonksiyonu içinde kullanıcıdan alınan girdilerle test senaryolarını içerir.

## Fonksiyonlar

*   `vector<int> LPSArray(const std::string& pattern)`:
    *   Verilen `pattern` için LPS dizisini hesaplar ve döndürür.
*   `void KMPSearch(const string& text, const string& pattern)`:
    *   Verilen `text` içinde `pattern`'i arar.
    *   Örüntünün bulunduğu tüm başlangıç indekslerini standart çıktıya yazdırır.
    *   Eğer örüntü bulunamazsa, uygun bir mesaj yazdırır.

## Nasıl Kullanılır?

1.  **Derleme:**
    Bir C++ derleyicisi (örneğin clang++) kullanarak `kmp.cpp` dosyasını derleyin.

2.  **Çalıştırma:**
    Derlenen programı çalıştırın.
    
    Terminal ekranında program, `main` fonksiyonunda kullanıcının girdiği metin ve aranacak örüntü doğrultusunda sonuçları konsola yazdıracaktır.

## Örnek Test Senaryoları

1.  Metin: "ABABDABACDABABCABAB", Örüntü: "ABABC"
    *   Beklenen Çıktı: Örüntü 10. indekste bulundu.
2.  Metin: "AAAAABAAABA", Örüntü: "AAAA"
    *   Beklenen Çıktı: Örüntü 0. indekste bulundu. Örüntü 1. indekste bulundu. Örüntü 6. indekste bulundu.
3.  Metin: "THIS IS A TEST TEXT", Örüntü: "TEST"
    *   Beklenen Çıktı: Örüntü 10. indekste bulundu.
4.  Metin: "ABCDE", Örüntü: "FGH"
    *   Beklenen Çıktı: Örüntü metin içinde bulunamadı.

## Zaman ve Alan Karmaşıklığı

*   **Zaman Karmaşıklığı:** `O(n + m)`
    *   `n`: Metnin uzunluğu
    *   `m`: Örüntünün uzunluğu
    *   LPS dizisi oluşturma `O(m)` sürer.
    *   Arama aşaması `O(n)` sürer.

*   **Alan Karmaşıklığı:** `O(m)`
    *   LPS dizisini saklamak için ek alan gerekir.

Bu implementasyon, KMP algoritmasının temel prensiplerini ve C++'da nasıl kullanılabileceğini göstermektedir. String arama problemlerinde verimli bir çözüm sunar.
