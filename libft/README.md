# Libft Directory

## 1. Bu Klasör Ne İşe Yarar?
C standart kütüphanesindeki bazı fonksiyonların (strlen, split, strdup vb.) tarafımızca yeniden yazılmış halidir (+42 projelerinin olmazsa olmazı). Ayrıca **Garbage Collector** (`ft_gc_*`) implementasyonunu da burada barındırıyorsa, bellek yönetiminin kalbidir.

## 2. Minishell Akışında Hangi Aşamada Çalışır?
Projenin HER yerinde. String işleyen, bellek ayıran her satırda buradaki fonksiyonlar kullanılır.

## 3. Kritik Fonksiyonlar
Minishell için değiştirilmiş veya eklenmiş olabilecek kritik fonksiyonlar:

- **ft_split**: PATH değişkenini bölmek için.
- **ft_strdup / ft_substr**: Token'ları kopyalamak için.
- **ft_strncmp**: Komutları karşılaştırmak için (`if (ft_strncmp(cmd, "echo", 5) == 0)`).
- **ft_gc_malloc**: Bellek sızıntısını önlemek için tüm malloc'ları takip eden versiyon.
