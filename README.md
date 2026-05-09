# 🐚 Minishell — Kendi Shell'ini Yaz

<div align="center">

![42 School](https://img.shields.io/badge/School-42-black?style=for-the-badge&logo=42)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Minishell](https://img.shields.io/badge/Project-minishell-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**Bash'e benzer, gerçek bir Unix shell'i sıfırdan C dilinde yazan proje**

*Lexer, parser, AST, expansion, heredoc, sinyal yönetimi ve bonus olarak wildcard, subshell, mantıksal operatörler.*

[Kurulum](#-kurulum) • [Kullanım](#-kullanım) • [Özellikler](#-desteklenen-özellikler) • [Mimari](#-mimari) • [Bonus](#-bonus-kısmı)

</div>

---

## 🎯 Projenin Amacı

<img align="right" alt="Shell Animation" width="280" src="https://media.giphy.com/media/3oKIPnAiaMCws8nOsE/giphy.gif">

Bu proje, gerçek bir Unix shell'inin **tüm temel bileşenlerini** sıfırdan uygulamayı amaçlar. Bash'in kullandığı mekanizmaların — tokenizer, parser, AST yürütücüsü, değişken genişletme, yönlendirmeler ve sinyal yönetimi — çalışma prensiplerini derinlemesine öğretir.

### 🎓 **Ana Öğrenme Hedefleri**

#### 📝 **Lexer (Tokenizer)**
- Ham komut satırını anlamlı token'lara ayırma
- Tek/çift tırnak içindeki özel karakterleri doğru işleme
- Operatörleri (`|`, `<<`, `>>`, `<>`, `&&`, `||`) ve kelimeleri ayırt etme
- Bonus: `(`, `)`, `&`, `<<<`, `||`, `&&` desteği

#### 🌳 **Parser ve AST**
- Token dizisini özyinelemeli iniş (recursive descent) ile parse etme
- `NODE_CMD`, `NODE_PIPE`, `NODE_SEQ` node tiplerinden oluşan AST inşa etme
- Syntax hata tespiti ve anlamlı hata mesajları üretme
- Bonus: `NODE_AND`, `NODE_OR`, `NODE_SUBSHELL`, `NODE_BG` node tipleri

#### 🔀 **Expansion (Genişletme)**
- `$VAR` ve `$?` değişken genişletme
- Tek tırnak içinde genişletme yapılmaması, çift tırnak içinde yapılması
- `~` (tilde) genişletme (HOME dizinine çözümleme)
- Bonus: `*` wildcard ile glob pattern eşleştirme

#### 🔗 **Execution (Yürütme)**
- Pipeline (`|`) ile birden fazla process oluşturma ve `pipe()` / `dup2()` yönetimi
- Builtin'leri parent process'te çalıştırma, dışsal komutları fork/execve ile çalıştırma
- `>`, `<`, `>>`, `<<` (heredoc), `<>` (read-write) yönlendirmeleri uygulama
- PATH üzerinden komut arama ve çalıştırma

#### 📦 **Builtins**
| Builtin | Davranış |
|---------|----------|
| `echo [-n]` | Argümanları yazar; `-n` ile newline bastırılır |
| `cd [path]` | Dizin değiştirir; `-` ile OLDPWD'ye döner |
| `pwd` | Mevcut dizini yazar |
| `export [key[=val]]` | Değişkeni ortama ekler/günceller |
| `unset [key]` | Değişkeni ortamdan kaldırır |
| `env` | Tüm ortam değişkenlerini listeler |
| `exit [n]` | Shell'i `n` koduyla kapatır |

#### 📡 **Sinyal Yönetimi**
- `SIGINT` (Ctrl+C): Prompt'u yeniler, heredoc'u sonlandırır
- `SIGQUIT` (Ctrl+\): Her zaman yok sayılır
- `SIGINT` child process'lerde varsayılan davranışa döndürülür
- `g_sig` global değişkeni ile sinyal durumu thread-safe aktarımı

#### 🧹 **Bellek Yönetimi**
- `ft_gc_malloc` singleton garbage collector ile tüm tahsislerin takibi
- `ft_gc_destroy()` ile tek çağrıda tüm bellek serbest bırakma
- FD GC (`t_fd_node` linked list) ile açık dosya tanımlayıcılarının takibi

---

## ✨ Desteklenen Özellikler

<div align="center">

![Pipes](https://img.shields.io/badge/Pipes-Supported-brightgreen?style=for-the-badge)
![Heredoc](https://img.shields.io/badge/Heredoc-Supported-blue?style=for-the-badge)
![Expansion](https://img.shields.io/badge/Expansion-Supported-orange?style=for-the-badge)

</div>

### 📋 **Mandatory Özellikler**

| Özellik | Örnek | Açıklama |
|---------|-------|----------|
| **Pipe** | `ls \| grep c` | N komutlu pipeline |
| **Yönlendirme** | `cat < f`, `echo hi > out` | `<`, `>`, `>>`, `<>` |
| **Heredoc** | `cat << EOF` | Delimiter'e kadar okuma |
| **Değişken** | `echo $HOME $?` | `$VAR`, `$?` genişletme |
| **Tilde** | `cd ~` | HOME'a genişletme |
| **Tırnak** | `echo "a $b" 'c $d'` | Çift/tek tırnak |
| **Sıralı** | `echo a ; echo b` | `;` ile komut sıralaması |
| **Builtins** | `export`, `cd`, `exit`… | 7 adet builtin |
| **Sinyaller** | Ctrl+C, Ctrl+\ | Prompt/heredoc modları |
| **SHLVL** | — | Shell seviyesi otomatik artar |

### 🎁 **Bonus Özellikler**

| Özellik | Örnek | Açıklama |
|---------|-------|----------|
| **Mantıksal AND** | `make && ./prog` | Sol başarılıysa sağı çalıştır |
| **Mantıksal OR** | `cmd \|\| echo fail` | Sol başarısızsa sağı çalıştır |
| **Subshell** | `(cd /tmp && pwd)` | Parantez içi alt shell |
| **Wildcard** | `ls *.c`, `rm *.o` | Glob pattern eşleştirme |
| **Herestring** | `cat <<< "merhaba"` | String'i STDIN'e besle |
| **FD Yönlendirme** | `2>err`, `1>out` | Dosya tanımlayıcı yönlendirme |
| **Append Export** | `export X+=suffix` | Değişkene değer ekleme |
| **Arka Plan** | `sleep 5 &` | Arka plan process |
| **Çok Satır** | `echo hello \|` | Eksik pipe'da devam istemi |

---

## 📁 Dosya Yapısı

```
minishell/
│
├── 📄 Makefile
├── 📚 libft/                        # Garbage collector dahil özel C kütüphanesi
│   ├── ft_gc.c / ft_gc_singleton.c  # Global GC
│   ├── ft_split.c, ft_strjoin.c …   # String yardımcıları
│   └── libft.h
│
├── 🗂️ include_mandatory/
│   ├── types.h                      # t_shell, t_ast, t_redir, t_pl…
│   ├── minishell.h
│   └── builtins/ env/ exec/ expand/ lexer/ parser/ signals/
│
├── 🗂️ include_bonus/
│   ├── types_bonus.h                # NODE_AND, NODE_OR, NODE_SUBSHELL, NODE_BG, R_HERESTR…
│   ├── minishell_bonus.h
│   └── builtins_bonus/ env_bonus/ exec_bonus/ expand_bonus/
│      lexer_bonus/ parser_bonus/ signals_bonus/
│
├── 🧩 src_mandatory/
│   ├── main.c
│   ├── builtins/    echo.c cd.c pwd.c export.c unset.c env.c exit.c exit_utils.c builtins.c
│   ├── env/         env_get.c env_set.c env_init.c env_unset.c env_export_print.c env_export_sort.c shlvl.c
│   ├── exec/        exec.c exec_cmd.c exec_path.c fd.c find_in_path.c
│   │                heredoc.c heredoc_run.c pipeline.c redir_apply.c redir_ops.c wait.c
│   ├── expand/      expander.c expand_handle.c expand_run.c expand_parse_utils.c expand_utils.c apply_expansion.c
│   ├── lexer/       tokenize.c tok_word.c tok_op.c tok_buf.c tok_vec.c tok_str.c parse_utils.c
│   ├── parser/      ast.c ast_cmd.c ast_cmd_utils.c ast_helpers.c ast_nodes.c
│   │                ast_parse_line.c ast_primary.c ast_redir.c ast_utils.c argv_free.c
│   ├── shell/       sh_init.c sh_loop.c sh_handle_line.c sh_read.c sh_continuation.c sh_destroy.c
│   └── signals/     sig_setup.c sig_handlers.c
│
└── 🎁 src_bonus/
    ├── main_bonus.c
    ├── builtins_bonus/   (mandatory ile aynı mantık)
    ├── env_bonus/        (aynı)
    ├── exec_bonus/       exec_bonus.c exec_cmd_bonus.c exec_path_bonus.c
    │                     subshell_bonus.c pipeline_bonus.c …
    ├── expand_bonus/     expander_bonus.c wildcard_bonus.c wildcard_utils_bonus.c …
    ├── lexer_bonus/      tokenize_bonus.c (&&, ||, (, ), <<<, & desteği)
    ├── parser_bonus/     ast_bonus.c ast_parse_line_bonus.c ast_primary_bonus.c
    │                     ast_helpers_bonus.c …
    └── shell_bonus/      sh_loop_bonus.c sh_handle_line_bonus.c sh_input_bonus.c
                          sh_continuation_bonus.c sh_read_bonus.c …
```

### 📊 **Dosya Açıklamaları**

| Dosya / Dizin | Sorumluluk |
|---------------|------------|
| `libft/ft_gc.c` | Singleton GC — `ft_gc_malloc`, `ft_gc_destroy` |
| `types.h` | Tüm struct ve enum tanımları (`t_shell`, `t_ast`, `t_redir`, `t_pl`, `t_sig_state`…) |
| `lexer/tokenize.c` | Ham satırı token dizisine dönüştürür |
| `parser/ast_parse_line.c` | Token dizisini AST'ye dönüştürür (top-level) |
| `expand/expander.c` | `$VAR`, `$?`, `~` genişletmesini uygular |
| `exec/exec_cmd.c` | Builtin/external ayrımı yapar, fork/execve yönetir |
| `exec/pipeline.c` | N-aşamalı pipeline kurar, pipe FD'lerini yönetir |
| `exec/heredoc.c` | Heredoc giriş döngüsü, pipe'a yazar |
| `shell/sh_loop.c` | Ana REPL döngüsü |
| `signals/sig_setup.c` | `g_sig` global durumu, `sigaction` kurulumu |
| `expand_bonus/wildcard_bonus.c` | `*` glob eşleştirme ve dizin tarama |
| `exec_bonus/subshell_bonus.c` | `(…)` subshell fork/wait |
| `parser_bonus/ast_bonus.c` | `&&`, `\|\|`, `&` operatörleri için AST |

---

## 🚀 Kurulum

### 📋 **Ön Gereksinimler**

![GCC](https://img.shields.io/badge/GCC%20%2F%20Clang-Required-red?style=flat-square)
![Make](https://img.shields.io/badge/Make-Required-blue?style=flat-square)
![Readline](https://img.shields.io/badge/libreadline-Required-green?style=flat-square)

- **Derleyici**: `cc` (gcc veya clang)
- **Unix-like OS**: Linux veya macOS
- **libreadline**: Ubuntu'da `sudo apt install libreadline-dev`, macOS'ta `brew install readline`

### 📥 **Klonlama ve Derleme**

```bash
# Repoyu klonla
git clone https://github.com/skarayil/minishell.git
cd minishell

# Mandatory versiyonu derle
make

# Bonus versiyonu derle
make bonus

# Temizlik
make clean      # Object dosyaları
make fclean     # Object + executable
make re         # Yeniden derle
```

### 📦 **Çıktı Dosyaları**

```bash
minishell        # Mandatory executable
minishell_bonus  # Bonus executable
```

---

## 💻 Kullanım

### 🖥️ **Shell'i Başlatma**

```bash
./minishell
# veya bonus:
./minishell_bonus
```

Karşılama promptu: `minishell$ `

### 📝 **Temel Örnekler**

#### 🟢 **Komut Çalıştırma**

```bash
minishell$ ls -la
minishell$ /bin/echo "merhaba dünya"
minishell$ pwd
```

#### 🟡 **Pipe**

```bash
minishell$ ls | grep ".c" | wc -l
minishell$ cat /etc/passwd | grep root | cut -d: -f1
```

#### 🟠 **Yönlendirme**

```bash
# Input / output
minishell$ cat < dosya.txt > cikti.txt

# Append
minishell$ echo "satır" >> log.txt

# Read-write
minishell$ cat <> dosya.txt

# Heredoc
minishell$ cat << EOF
> Merhaba
> Dünya
> EOF
```

#### 🔵 **Değişken Genişletme**

```bash
minishell$ echo $HOME
minishell$ echo $?
minishell$ export ISIM="Sude"
minishell$ echo "Merhaba $ISIM"
minishell$ echo 'Bu genişlemez: $HOME'
```

#### 🟣 **Builtins**

```bash
minishell$ cd /tmp
minishell$ cd -              # OLDPWD'ye dön
minishell$ export FOO=bar
minishell$ export FOO+=_baz  # bonus: FOO=bar_baz
minishell$ unset FOO
minishell$ env | grep PATH
minishell$ exit 42
```

#### 🔴 **Bonus: Mantıksal Operatörler ve Subshell**

```bash
# AND / OR zincirleme
minishell$ make && ./minishell_bonus
minishell$ false || echo "başarısız"
minishell$ true && echo "başardı" || echo "başarısız"

# Subshell — alt ortamı etkiler, üstü etkilemez
minishell$ (cd /tmp && ls)
minishell$ (export TEMP=123) && echo $TEMP  # Boş — subshell yalıtılmış

# Wildcard
minishell$ ls *.c
minishell$ echo src_bonus/**/*_bonus.c
minishell$ rm *.o

# Herestring
minishell$ cat <<< "tek satır girdi"
minishell$ wc -w <<< "beş kelime sayılacak"
```

---

## 🏗️ Mimari

### 🔄 **Komut İşlem Akışı**

```
Kullanıcı Girdisi (readline)
         │
         ▼
   ┌─────────────┐
   │   Lexer     │  Ham satır → Token dizisi
   │  tokenize() │  ["ls", "-l", "|", "grep", ".c"]
   └──────┬──────┘
          │
          ▼
   ┌─────────────┐
   │   Parser    │  Token dizisi → AST
   │ parse_line()│
   └──────┬──────┘
          │
          ▼
   ┌─────────────────────────────────────┐
   │              AST                    │
   │          NODE_PIPE                  │
   │         /         \                 │
   │    NODE_CMD     NODE_CMD            │
   │    [ls,-l]     [grep,.c]            │
   └──────┬──────────────────────────────┘
          │
          ▼
   ┌─────────────┐
   │  Heredoc    │  Heredoc'ları önceden işler
   │ pre_process │  (heredoc_fd'leri doldurur)
   └──────┬──────┘
          │
          ▼
   ┌─────────────┐
   │  Expansion  │  $VAR, $?, ~, wildcard
   │ expand_list │  Yürütme sırasında uygulanır
   └──────┬──────┘
          │
          ▼
   ┌─────────────┐
   │  Execution  │  AST'yi yürütür
   │  exec_ast() │  fork/pipe/dup2/execve
   └─────────────┘
```

### 🌳 **AST Node Tipleri**

| Tip | Mandatory | Bonus | Açıklama |
|-----|-----------|-------|----------|
| `NODE_CMD` | ✅ | ✅ | Tek komut (argv + redirs) |
| `NODE_PIPE` | ✅ | ✅ | `a \| b` |
| `NODE_SEQ` | ✅ | ✅ | `a ; b` |
| `NODE_AND` | — | ✅ | `a && b` |
| `NODE_OR` | — | ✅ | `a \|\| b` |
| `NODE_SUBSHELL` | — | ✅ | `(a)` |
| `NODE_BG` | — | ✅ | `a &` |

### 🔒 **Yönlendirme Tipleri**

| Sabit | Sembol | Açıklama |
|-------|--------|----------|
| `R_IN` | `<` | Input yönlendirme |
| `R_OUT` | `>` | Output yönlendirme (truncate) |
| `R_APP` | `>>` | Output yönlendirme (append) |
| `R_HEREDOC` | `<<` | Heredoc |
| `R_INOUT` | `<>` | Okuma-yazma |
| `R_HERESTR` | `<<<` | Herestring (bonus) |

### 🧹 **Bellek Yönetimi**

```c
/* Her malloc ft_gc üzerinden geçer */
void *ft_gc_malloc(size_t size);   /* GC listesine ekler */
void  ft_gc_destroy(void);         /* Hepsini serbest bırakır */

/* FD GC: açık dosya tanımlayıcılarını takip eder */
void ms_gc_add_fd(t_shell *sh, int fd, const char *tmp_file);
void ms_gc_close_all(t_shell *sh);  /* Tüm FD'leri kapatır */
```

### 📡 **Sinyal Makinesi**

```
g_sig.mode = SM_PROMPT   →  SIGINT: yeni satır yaz, rl_replace_line("")
g_sig.mode = SM_HEREDOC  →  SIGINT: ^C yaz, STDIN'i kapat (heredoc sonlanır)
Child process            →  SIGINT/SIGQUIT: SIG_DFL (varsayılan davranış)
Komut yürütme sırasında  →  SIGINT/SIGQUIT: SIG_IGN (parent yok sayar)
```

---

## 🧪 Test Senaryoları

### ✅ **Temel Fonksiyonalite**

```bash
# Tek komut
echo hello world
ls -la /tmp

# Pipe zinciri
ls | sort | uniq | head -5
cat /etc/hosts | grep localhost | wc -l

# Heredoc
cat << LIMIT
satır1
satır2
LIMIT

# Değişken
export X=42
echo $X $?
unset X
echo $X   # Boş

# Çıkış kodu
false; echo $?   # 1
true; echo $?    # 0
```

### 🎁 **Bonus Testleri**

```bash
# Mantıksal zincir
true && echo "evet" || echo "hayır"   # evet
false && echo "evet" || echo "hayır"  # hayır

# Subshell yalıtımı
cd /tmp
(cd / && pwd)   # /
pwd             # /tmp  — parent değişmedi

# Wildcard
ls *.c
ls src_mandatory/**/*.c  # Yalnızca geçerli desende

# Herestring
wc -c <<< "merhaba"   # 8

# FD yönlendirme
./hatalı_program 2>/dev/null
echo "cikti" 1>dosya.txt

# Arka plan (temel)
sleep 2 &

# Çok satırlı pipe girişi (bonus)
echo hello |
> grep hello
```

### ⚠️ **Hata Durumu Testleri**

```bash
# Sözdizimi hataları
echo |          # syntax error near unexpected token `newline'
| echo          # syntax error
echo > > file   # syntax error
() echo         # syntax error near unexpected token `)'

# Komut bulunamadı
yokkomut        # minishell: yokkomut: command not found

# İzin hatası
chmod 000 dosya && cat dosya   # Permission denied

# Çıkış kodu
exit 256        # 0 (256 % 256)
exit abc        # numeric argument required
exit 1 2        # too many arguments
```

### 🔍 **Valgrind ile Bellek Kontrolü**

```bash
# Bellek sızıntısı
valgrind --leak-check=full --show-leak-kinds=all ./minishell

# Readline'ın kendi sızıntılarını bastır
valgrind --leak-check=full \
         --suppressions=readline.supp \
         ./minishell
```

---

## 📊 Mandatory vs Bonus Karşılaştırması

| Bileşen | Mandatory | Bonus |
|---------|-----------|-------|
| **Token tipleri** | `\|`, `<`, `>`, `>>`, `<<`, `<>`, `;` | + `&&`, `\|\|`, `(`, `)`, `&`, `<<<` |
| **AST node'ları** | `PIPE`, `CMD`, `SEQ` | + `AND`, `OR`, `SUBSHELL`, `BG` |
| **Expansion** | `$VAR`, `$?`, `~` | + `*` wildcard, `QUOTE_MARKER` mekanizması |
| **Yönlendirmeler** | `<`, `>`, `>>`, `<<`, `<>` | + `<<<`, FD numaralı yönlendirme |
| **Execution** | pipeline, seq | + subshell, AND/OR kısa devre, background |
| **Shell döngüsü** | trailing pipe continuation | + `is_incomplete` token analizi |
| **Heredoc** | expand / no-expand (tırnaklı delimiter) | aynı + herestring |

---

## 🏆 Proje Başarıları

<div align="center">

![Score](https://img.shields.io/badge/Score-125%2F100-gold?style=for-the-badge)
![Tests](https://img.shields.io/badge/Tests-All%20Passed-success?style=for-the-badge)
![Norminette](https://img.shields.io/badge/Norminette-OK-brightgreen?style=for-the-badge)
![Bonus](https://img.shields.io/badge/Bonus-Completed-orange?style=for-the-badge)

### 📊 **Proje İstatistikleri**

| Metrik | Mandatory | Bonus |
|--------|-----------|-------|
| **Kaynak Dosya** | 55+ | 65+ |
| **Toplam Fonksiyon** | 120+ | 150+ |
| **AST Node Tipi** | 3 | 7 |
| **Yönlendirme Tipi** | 5 | 6 |
| **Builtin Sayısı** | 7 | 7 |
| **Bellek Sızıntısı** | ✅ GC Temiz | ✅ GC Temiz |
| **Readline Entegrasyonu** | ✅ | ✅ |

</div>

---

## 📚 Teknik Notlar

### ⚠️ **Dikkat Edilmesi Gerekenler**

#### 🔒 **Heredoc Güvenliği**
- Delimiter tırnak içinde gelirse (`<< 'EOF'`) genişletme devre dışı bırakılır (`heredoc_expand = 0`)
- Heredoc FD'leri `t_fd_node` listesinde tutulur; komut tamamlanınca `ms_gc_close_all` ile kapatılır

#### 🌿 **Tilde Genişletme**
- Yalnızca kelimenin başında ve tek başına ya da `/` öncesinde geçerlidir (`~/docs` → `/home/user/docs`)
- Tırnak içinde `~` genişlemez

#### 🧵 **Sinyal — `g_sig` Global Değişkeni**
- Standart, `volatile sig_atomic_t` tipinde tek global değişken kullanılır
- `SA_RESTART` flag'i readline'ın `EINTR` ile bozulmamasını sağlar

#### 📋 **`export` Çıktı Formatı**
- `declare -x` ön ekiyle sıralı alfabetik çıktı
- Değer NULL ise (`export VAR`) `=` işareti olmadan yazdırılır
- Non-ASCII byte içeren değerler `$'...'` formatında octal escape ile yazdırılır

#### 🔁 **Garbage Collector Tasarımı**
- `ft_gc_singleton` pattern ile tek process kapsamında global GC durumu tutulur
- Her `fork()` sonrası child `ft_gc_destroy()` çağırmadan önce kendi işini tamamlar; böylece parent GC durumu bozulmaz

### 💡 **Best Practices**

1. Tüm sistem çağrılarının dönüş değerini kontrol et (`fork`, `pipe`, `dup2`, `open`)
2. Her child process çıkmadan önce `ms_gc_close_all` + `ft_gc_destroy` çağır
3. Parser'da sözdizimi hataları için `NULL` döndür, yürütme başlatma
4. Expansion yalnızca yürütme aşamasında (AST üzerinde) uygula; parse sırasında değil
5. Builtin'leri hiçbir zaman fork içinde çalıştırma (pipeline dışında)

---

<div align="center">

### 🎯 **Kazanılan Temel Beceriler**

![Lexing](https://img.shields.io/badge/Lexing-blue?style=flat-square)
![Parsing](https://img.shields.io/badge/Parsing-green?style=flat-square)
![AST](https://img.shields.io/badge/AST-orange?style=flat-square)
![Process Management](https://img.shields.io/badge/Process%20Management-red?style=flat-square)
![Signal Handling](https://img.shields.io/badge/Signal%20Handling-purple?style=flat-square)
![Memory Management](https://img.shields.io/badge/Memory%20Management-teal?style=flat-square)

---

**🐚 "Minishell, bir shell'i çalıştırmanın arkasındaki tüm sihrin aslında iyi tasarlanmış bileşenlerden ibaret olduğunu öğretir."**

*Bu proje; lexer, parser, process yönetimi ve sinyal işleme konularında sağlam bir sistem programlama temeli oluşturur.*

---

### 👩‍💻 Created by Sude Naz Karayıldırım

[![42 Profile](https://img.shields.io/badge/42%20Profile-skarayil-black?style=flat-square&logo=42&logoColor=white)](https://profile.intra.42.fr/users/skarayil)
[![GitHub](https://img.shields.io/badge/GitHub-skarayil-181717?style=flat-square&logo=github&logoColor=white)](https://github.com/skarayil)

**⭐ Eğer bu proje işinize yaradıysa, repo'ya star vermeyi unutmayın!**

</div>
