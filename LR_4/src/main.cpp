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

    /*
    shm_open создает и открывает новый (или открывает уже существующий)
    объект разделяемой памяти POSIX. Объект разделяемой памяти
    POSIX - это обработчик, используемый несвязанными процессами для исполнения mmap(2)
    на одну область разделяемой памяти. Функция shm_unlink выполняет обратную операцию,
    удаляя объект, предварительно созданный с помощью shm_open.
    Операция shm_open аналогична open(2). name определяет собственно создаваемый объект
    разделяемой памяти для создания или открытия. Для использования в портируемых программах
    name должно иметь в начале косую черту (/) и больше не содержать их внутри имени.
    */
    int fd = shm_open(CommonFile, O_RDWR | O_CREAT, mode);
    if (fd == -1) {
        _exit(EXIT_FAILURE);
    }

    sem_t* semptr = sem_open(SemaphoreName, O_CREAT, mode, 1); // 1 - начальное значение для семафора
    if (semptr == SEM_FAILED) {
        _exit(EXIT_FAILURE);
    }

    ftruncate(fd, (off_t)map_size); // Функции truncate и ftruncate устанавливают длину обычного файла с именем path или файловым дескриптором fd в length байт.
    // Это тип данных, определенный в разделе sys/types.h заголовочный файл (основного типа unsigned long) и используется для измерения смещения файла в байтах от начала файла.
    char* memptr = (char*) mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // создает новое сопоставление в виртуальном адресном пространстве вызывающего процесса.
    if (memptr == MAP_FAILED) {
        _exit(EXIT_FAILURE);
    }
    
    sprintf(memptr, "%s", in);
    free(in);
    
    int val;
    if (sem_getvalue(semptr, &val) != 0) { // sem_getvalue(sem_t *sem, int *sval); омещает текущее значение семафора, заданного в sem, в виде целого, на которое указывает sval.
        _exit(EXIT_FAILURE);
    }

    /*
    Функция sem_post() увеличивает (разблокирует) семафор, на который указывает sem.
    Если значение семафора после этого становится больше нуля, то другой процесс или нить
    заблокированная в вызове sem_wait(3), проснётся и заблокирует семафор.
    */
    while (val++ < 1) {
        sem_post(semptr);
    }

    switch (auto pid = fork())
    {
    case -1:
        return 0;
    case 0:
        munmap(memptr, map_size);
        close(fd);
        sem_close(semptr);
        execl("child", "child", filename, NULL);
    }

    while (true) {
        if (sem_getvalue(semptr, &val) != 0) {
            _exit(EXIT_FAILURE);
        }

        if (val == 0) {
            /*
            Функция sem_wait() уменьшает (блокирует) семафор, на который указывает sem.
            Если значение семафор больше нуля, то выполняется уменьшение и функция сразу завершается.
            */
            if (sem_wait(semptr) == -1) {
                _exit(EXIT_FAILURE);
            }
            return 0;
        }
    }
}