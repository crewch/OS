#include "../includes/header.h"

int main(void)
{
    char *filename;
    size_t len = 0;

    cout << "Name of file: ";
    
    if (getline(&filename, &len, stdin) == -1) {
        _exit(EXIT_FAILURE);
    }
    
    size_t map_size = 0;
    char *in = (char *)malloc(sizeof(char));
    char c;
    
    while ((c = getchar()) != EOF) {
        in[map_size] = c;
        in = (char *)realloc(in, (++map_size + 1) * sizeof(char));
    }
    
    in[map_size++] = '\0';

    int fd = shm_open(CommonFile, O_RDWR | O_CREAT, mode);
    if (fd == -1) {
        _exit(EXIT_FAILURE);
    }

    ftruncate(fd, (off_t)map_size); // Функции truncate и ftruncate устанавливают длину обычного файла с именем path или файловым дескриптором fd в length байт.
    char* memptr = (char*) mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // создает новое сопоставление в виртуальном адресном пространстве вызывающего процесса.
    if (memptr == MAP_FAILED) {
        _exit(EXIT_FAILURE);
    }
    
    sprintf(memptr, "%s", in);
    free(in);
    
    switch (auto pid = fork())
    {
    case -1:
        return 0;
    case 0:
        munmap(memptr, map_size);
        close(fd);
        execl("child", "child", filename, NULL);
    }
}