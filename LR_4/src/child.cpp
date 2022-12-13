#include "../includes/header.h"

int main(int argc, char** argv)
{
    int map_fd = shm_open(CommonFile, O_RDWR, mode);
    if (map_fd < 0) {
        _exit(EXIT_FAILURE);
    }
    
    struct stat statbuf;
    fstat(map_fd, &statbuf); // Эти функции возвращают информацию о файле в буфере. Вызов fstat() идентичен stat(), но опрашиваемый файл задаётся в виде файлового дескриптора fd.
    const size_t map_size = statbuf.st_size;
    
    char* memptr = (char*)mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, map_fd, 0);
    if (memptr == MAP_FAILED) {
        _exit(EXIT_FAILURE);
    }
    
    sem_t* semptr = sem_open(SemaphoreName, O_CREAT, mode, 1);
    if (semptr == SEM_FAILED) {
        _exit(EXIT_FAILURE);
    }

    /*
    Функция sem_wait() уменьшает (блокирует) семафор, на который указывает sem.
    Если значение семафор больше нуля, то выполняется уменьшение и функция сразу завершается.
    */

    if (sem_wait(semptr) != 0) {
        _exit(EXIT_FAILURE);
    }
    
    char* out = (char*)malloc(sizeof(char));
    size_t m_size = 0;
    string first;
    string second;

    FILE* filename = fopen(argv[1], "w");
    if (filename == NULL) {
        _exit(EXIT_FAILURE);
    }

    int flag = 0;
    
    for (int i = 0; i + 1 < map_size; ++i) {
        if (flag == 0) {
            first.push_back(memptr[i]);
        } else if (flag == 1) {
            second.push_back(memptr[i]);
        }
        
        if (memptr[i] == ' ' && flag == 0) {
            flag = 1;
        } else if ((memptr[i] == ' ' || memptr[i] == '\n') && flag == 1) {
            if (atof(second.c_str()) == 0) {
                cout << "ERROR!!!" << endl;
                break;
            }
            
            first = to_string(atof(first.c_str()) / atof(second.c_str()));
            second = "";
            
            if (memptr[i] == '\n') {
                fprintf(filename, "%s\n", first.c_str());
                flag = 0;
                first = "";
                second = "";
            }
        }
    }

    fclose(filename);
    out[m_size++] = '\0';
    ftruncate(map_fd, (off_t)m_size);
    memset(memptr, '\0', m_size);
    sprintf(memptr, "%s", out);
    free(out);
    close(map_fd);
    sem_post(semptr);
    sem_close(semptr);
    return 0;
}