# KMP Algoritması C++ Implementasyonu

Bu repo, Knuth-Morris-Pratt (KMP) string arama algoritmasının C++ için entegrasyonunu içerir. KMP algoritması, bir metin içerisinde belirli bir örüntünün (pattern) oluşumlarını verimli bir şekilde bulmak için kullanılır.

## Algoritmanın Çalışma Prensibi

Knuth-Morris-Pratt (KMP) algoritması, string arama problemlerinde verimliliği artırmak için tasarlanmış bir algoritmadır. Algoritma, iki temel aşamadan oluşur: LPS (Longest Proper Prefix which is also Suffix) dizisinin hesaplanması ve arama aşaması.

### 1. LPS Dizisinin Hesaplanması
LPS dizisi, bir örüntünün (pattern) her bir alt ön ekinin (prefix) aynı zamanda bir son ek (suffix) olduğu durumdaki en uzun uzunluğu temsil eder. Bu dizinin hesaplanması, algoritmanın verimliliğini sağlayan temel adımdır. LPS dizisi şu şekilde hesaplanır:

- Örüntüdeki her bir karakter için, o karaktere kadar olan alt string'in en uzun uygun ön eki (proper prefix) ile aynı zamanda bir son ek (suffix) olup olmadığı kontrol edilir.
- Eğer bir eşleşme bulunursa, bu uzunluk LPS dizisine eklenir. Aksi takdirde, değer sıfır olarak atanır.

Örneğin, `pattern = "ABABC"` için LPS dizisi şu şekilde hesaplanır:
- `lps[0]` (A için): 0 (Ön ek yok)
- `lps[1]` (AB için): 0 (A != B)
- `lps[2]` (ABA için): 1 (Baştaki "A", sondaki "A" ile eşleşir)
- `lps[3]` (ABAB için): 2 (Baştaki "AB", sondaki "AB" ile eşleşir)
- `lps[4]` (ABABC için): 0 (Baştaki "A" sondaki "C" ile eşleşmez)

Bu dizinin hesaplanması, örüntüdeki karakterlerin yalnızca bir kez işlenmesiyle `O(m)` zaman karmaşıklığında gerçekleştirilir.

### 2. Arama Aşaması
Arama aşamasında, metin (text) ve örüntü (pattern) karakter karakter karşılaştırılır. Bu aşamada LPS dizisi, uyuşmazlık durumunda örüntünün ne kadar kaydırılacağını belirlemek için kullanılır. Bu sayede, metin üzerinde geri gitmeye gerek kalmaz ve gereksiz karşılaştırmalar önlenir.

Arama işlemi şu şekilde gerçekleştirilir:
- Metin ve örüntü karakterleri sırayla karşılaştırılır.
- Eğer bir uyuşmazlık meydana gelirse, LPS dizisi kullanılarak örüntü kaydırılır. Kaydırma işlemi, örüntünün önceki eşleşen kısmına dayanarak yapılır.
- Eğer örüntünün sonuna kadar eşleşme sağlanırsa (`j == m`, burada `m` örüntü uzunluğudur), örüntünün metin içindeki başlangıç indeksi kaydedilir.
- Aynı örüntünün metin içinde birden fazla kez bulunabilmesi için, eşleşme bulunduktan sonra `j` (örüntü indeksi) `lps[j-1]` değerine ayarlanarak aramaya devam edilir.

Bu aşama, metindeki her karakterin yalnızca bir kez işlenmesiyle `O(n)` zaman karmaşıklığında gerçekleştirilir. Burada `n`, metnin uzunluğunu ifade eder.

### Genel Verimlilik
KMP algoritması, hem LPS dizisinin hesaplanması hem de arama aşamasında lineer zaman karmaşıklığına sahiptir (`O(n + m)`). Bu özellik, algoritmayı büyük metinlerde ve uzun örüntülerde oldukça verimli bir hale getirir. Ayrıca, LPS dizisinin saklanması için yalnızca `O(m)` ek alan gereklidir.

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

## Diğer Kelime Arama Algoritmaları ile Karşılaştırma

Knuth-Morris-Pratt (KMP) algoritması, diğer kelime arama algoritmalarıyla karşılaştırıldığında belirli avantajlara ve dezavantajlara sahiptir. Bu bölümde, KMP algoritmasının Boyer-Moore ve Naive algoritmaları ile karşılaştırması yapılmıştır.

### Avantajları

1. **Lineer Zaman Karmaşıklığı:**
   * KMP algoritması, hem LPS dizisinin hesaplanması hem de arama aşamasında `O(n + m)` zaman karmaşıklığına sahiptir. Bu, özellikle uzun metinlerde ve örüntülerde büyük bir avantaj sağlar.

2. **Geri Gitme Gereksinimi Yok:**
   * KMP algoritması, metin üzerinde geri gitmeden çalışır. Bu, özellikle büyük veri kümelerinde performansı artırır.

3. **Örüntüye Bağımsız Performans:**
   * KMP algoritmasının performansı, örüntüdeki karakterlerin dağılımından etkilenmez. Bu, örüntünün yapısına bağlı olarak performansın değiştiği Boyer-Moore gibi algoritmalara kıyasla bir avantajdır.

### Dezavantajları

1. **Ek Alan Gereksinimi:**
   * KMP algoritması, LPS dizisini saklamak için `O(m)` ek alan gerektirir. Bu, özellikle çok büyük örüntülerde bir dezavantaj olabilir.

2. **Pratikte Daha Yavaş:**
   * Boyer-Moore algoritması, pratikte genellikle KMP'den daha hızlıdır çünkü metin üzerinde daha az karşılaştırma yapar.

3. **Basitlik:**
   * Naive algoritma, küçük metinler ve örüntüler için daha basit ve kolay uygulanabilir bir çözüm sunar. KMP'nin daha karmaşık bir yapıya sahip olması, uygulama ve hata ayıklama sürecini zorlaştırabilir.

### Boyer-Moore Algoritması ile Karşılaştırma

- **Avantaj:** Boyer-Moore algoritması, metni sağdan sola tarayarak ve "bad character" ile "good suffix" kurallarını kullanarak genellikle daha az karşılaştırma yapar.
- **Dezavantaj:** Boyer-Moore algoritması, örüntüdeki karakterlerin metinle uyuşmadığı durumlarda performans kaybı yaşayabilir.

### Naive Algoritma ile Karşılaştırma

- **Avantaj:** Naive algoritma, uygulaması son derece basit bir algoritmadır ve küçük veri kümelerinde yeterince etkilidir.
- **Dezavantaj:** Naive algoritma, en kötü durumda `O(n * m)` zaman karmaşıklığına sahiptir ve büyük veri kümelerinde verimsizdir.

KMP algoritması, özellikle büyük veri kümelerinde ve örüntülerin sıkça tekrarlandığı durumlarda etkili bir çözüm sunar. Ancak, uygulama bağlamına göre diğer algoritmalar da tercih edilebilir.

## Zaman ve Alan Karmaşıklığı

KMP algoritmasının zaman ve alan karmaşıklığı şu şekildedir:

### Zaman Karmaşıklığı

1. **LPS Dizisinin Hesaplanması:**
   * LPS dizisi, örüntüdeki her karakterin yalnızca bir kez işlenmesiyle `O(m)` zaman karmaşıklığında hesaplanır.

2. **Arama Aşaması:**
   * Metindeki her karakterin yalnızca bir kez işlenmesiyle `O(n)` zaman karmaşıklığında gerçekleştirilir.

Toplam zaman karmaşıklığı: `O(n + m)`
   * `n`: Metnin uzunluğu
   * `m`: Örüntünün uzunluğu

### Alan Karmaşıklığı

1. **LPS Dizisi:**
   * Örüntünün uzunluğuna bağlı olarak `O(m)` ek alan gerektirir.

Genel alan karmaşıklığı: `O(m)`

## Kaynakça

https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
