# Лабораторная работа №5 по курсу "Операционные системы"

Студент группы: M80-207Б-21, Крючков Артемий Владимирович\
Контакты: artemkr2003@mail.ru\
Работа выполнена: 17.09.2022\
Преподаватель: Миронов Евгений Сергеевич

## Задание

![Screenshot_20221213_213135](https://user-images.githubusercontent.com/86799725/207416314-41f13758-cbb0-445c-ad58-7c0a04b53fe1.png)
![Screenshot_20221213_213458](https://user-images.githubusercontent.com/86799725/207416874-cc977619-c882-4dd2-895f-8fc3714b137b.png)
![Screenshot_20221213_213504](https://user-images.githubusercontent.com/86799725/207416898-cd88b476-b299-4209-92dd-98e952552997.png)
![Screenshot_20221213_213513](https://user-images.githubusercontent.com/86799725/207416904-5c494d03-4bbe-4f3a-8631-94aa0ddf4eca.png)

### Методы и алгоритмы решения

```c
#include <stdlib.h>

int fact(int x)
{
    int res = 1;
    for (int i = 2; i <= x; i++) {
        res *= i;
    }

    return res;
}

float power(float base, int exp) {
    float result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}

float E(int x)
{
    return power(1 + 1 / (float)x, x);
}

int GCF(int A, int B)
{
    while (B ^= A ^= B ^= A %= B);
    return abs(A);
}
```

```c
#include <stdlib.h>

int fact(int x)
{
    int res = 1;
    for (int i = 2; i <= x; i++) {
        res *= i;
    }

    return res;
}

float E(int x)
{
    float sum = 0;

    for (int i = 0; i <= x; i++) {
        sum += (1 / (float)fact(i));
    }
    
    return sum;
}

int GCF(int A, int B)
{
    A = abs(A);
    B = abs(B);
    int min_num = (A < B) ? A : B;

    for (int i = min_num; i > 0; i--) {
        if (A % i == 0 && B % i == 0) {
            return i;
        }
    }

    return 1;
}
```

```txt
[crewch@pc build]$ cmake -D LIB_PRINT_TYPE=XD ..
CMake Error at CMakeLists.txt:21 (message):
  Unexpected LIB_PRINT_TYPE: XD


-- Configuring incomplete, errors occurred!
See also "/home/crewch/git/OS/LR_5/build/CMakeFiles/CMakeOutput.log".
```

```txt
[crewch@pc build]$ cmake -D LIB_PRINT_TYPE=EXTENDED ..
-- Configuring done
-- Generating done
-- Build files have been written to: /home/crewch/git/OS/LR_5/build

[crewch@pc build]$ cmake --build .
[ 10%] Building C object CMakeFiles/lib1.dir/src/functions1.c.o
[ 20%] Linking C shared library liblib1.so
[ 20%] Built target lib1
[ 30%] Building C object CMakeFiles/lib2.dir/src/functions2.c.o
[ 40%] Linking C shared library liblib2.so
[ 40%] Built target lib2
[ 50%] Building C object CMakeFiles/test11.dir/src/test1.c.o
[ 60%] Linking C executable test11
[ 60%] Built target test11
[ 70%] Building C object CMakeFiles/test12.dir/src/test1.c.o
[ 80%] Linking C executable test12
[ 80%] Built target test12
[ 90%] Building C object CMakeFiles/test2.dir/src/test2.c.o
[100%] Linking C executable test2
[100%] Built target test2

[crewch@pc build]$ /home/crewch/git/OS/LR_5/build/test2 
2 1000
Operation system: Linux-5.15.81-1-MANJARO
E: 2.717049
0
2 18
Operation system: Linux-5.15.81-1-MANJARO
E: 2.718282
```

## Strace

```txt
[crewch@pc build]$ strace ./test11
execve("./test11", ["./test11"], 0x7ffce201f760 /* 70 vars */) = 0
brk(NULL)                               = 0x5588f5ef7000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffeb7f5d7e0) = -1 EINVAL (Недопустимый аргумент)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f0b53ced000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/glibc-hwcaps/x86-64-v3/liblib1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
newfstatat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/glibc-hwcaps/x86-64-v3", 0x7ffeb7f5ca10, 0) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/glibc-hwcaps/x86-64-v2/liblib1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
newfstatat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/glibc-hwcaps/x86-64-v2", 0x7ffeb7f5ca10, 0) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/tls/x86_64/x86_64/liblib1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
newfstatat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/tls/x86_64/x86_64", 0x7ffeb7f5ca10, 0) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/tls/x86_64/liblib1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
newfstatat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/tls/x86_64", 0x7ffeb7f5ca10, 0) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/tls/x86_64/liblib1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
newfstatat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/tls/x86_64", 0x7ffeb7f5ca10, 0) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/tls/liblib1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
newfstatat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/tls", 0x7ffeb7f5ca10, 0) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/x86_64/x86_64/liblib1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
newfstatat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/x86_64/x86_64", 0x7ffeb7f5ca10, 0) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/x86_64/liblib1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
newfstatat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/x86_64", 0x7ffeb7f5ca10, 0) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/x86_64/liblib1.so", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
newfstatat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/x86_64", 0x7ffeb7f5ca10, 0) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/liblib1.so", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=17832, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 16408, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f0b53ce8000
mmap(0x7f0b53ce9000, 4096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1000) = 0x7f0b53ce9000
mmap(0x7f0b53cea000, 4096, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7f0b53cea000
mmap(0x7f0b53ceb000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7f0b53ceb000
close(3)                                = 0
openat(AT_FDCWD, "/home/crewch/git/OS/LR_5/build/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (Нет такого файла или каталога)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=158163, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 158163, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f0b53cc1000
close(3)                                = 0
openat(AT_FDCWD, "/usr/lib/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P4\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=1953472, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 1994384, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f0b53ada000
mmap(0x7f0b53afc000, 1421312, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7f0b53afc000
mmap(0x7f0b53c57000, 356352, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x17d000) = 0x7f0b53c57000
mmap(0x7f0b53cae000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1d4000) = 0x7f0b53cae000
mmap(0x7f0b53cb4000, 52880, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f0b53cb4000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f0b53ad7000
arch_prctl(ARCH_SET_FS, 0x7f0b53ad7740) = 0
set_tid_address(0x7f0b53ad7a10)         = 31613
set_robust_list(0x7f0b53ad7a20, 24)     = 0
rseq(0x7f0b53ad8060, 0x20, 0, 0x53053053) = 0
mprotect(0x7f0b53cae000, 16384, PROT_READ) = 0
mprotect(0x7f0b53ceb000, 4096, PROT_READ) = 0
mprotect(0x5588f5e75000, 4096, PROT_READ) = 0
mprotect(0x7f0b53d20000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7f0b53cc1000, 158163)          = 0
newfstatat(0, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x2), ...}, AT_EMPTY_PATH) = 0
getrandom("\x95\xee\xd1\x28\x61\xce\x28\x95", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x5588f5ef7000
brk(0x5588f5f18000)                     = 0x5588f5f18000
read(0, 2 1000
"2 1000\n", 1024)               = 7
newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x2), ...}, AT_EMPTY_PATH) = 0
write(1, "Operation system: Linux-5.15.81-"..., 42Operation system: Linux-5.15.81-1-MANJARO
) = 42
write(1, "E: 2.717049\n", 12E: 2.717049
)           = 12
read(0, ^Cstrace: Process 31613 detached
 <detached ...>
```