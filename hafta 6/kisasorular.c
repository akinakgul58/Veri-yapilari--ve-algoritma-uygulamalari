/*
1) 25 değeri eklenirse hangi düğümün altına yerleşir?

30'un sol çocuğu olur. Yol: 25 < 40 → sola, 25 > 20 → sağa (30'a), 25 < 30 → sola.
Orada NULL olduğu için yeni düğüm buraya eklenir.

2) Inorder fonksiyonunda printf() ilk satıra taşınırsa hangi dolaşma elde edilir?

Preorder (kök → sol → sağ) dolaşma elde edilir,
çünkü düğüm önce yazdırılır, sonra sol ve sağ alt ağaçlara geçilir. 
Bu ağaç için çıktı: 40 20 10 30 60 50 70. (Inorder’da ise sıralı çıktı alınır: 10 20 30 40 50 60 70.)

3) findMin() içinde left yerine right takip edilirse hangi değer bulunur?

Ağaçtaki en büyük değer bulunur. Yol 40 → 60 → 70 olur ve 70'in sağ çocuğu NULL olduğu için 70 döner.
 Fonksiyon fiilen findMax() haline gelir.
*/