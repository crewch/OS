#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <thread>

using namespace std;

class QS {
public:
    int* array_t;
    int size_t;
    int thread_t;
    QS** threads_t;

    QS(int* array, int size, QS** threads, int thread_id)
    {
        array_t = array;
        size_t = size;
        threads_t = threads;
        thread_t = thread_id;
        threads[thread_id] = this;
    }
    ~QS()
    {
        threads_t[thread_t] = NULL;
    }
};

void qsort(int* array, const unsigned int size)
{
    if (size <= 50) {
        for (unsigned int i = 1; i < size; i++) {
            int temp = array[i];
            unsigned int j = i;

            while (j > 0 && temp < array[j - 1]) {
                array[j] = array[j - 1];
                j--;
            }
            
            array[j] = temp;
        }
    } else {
        int pivot = array[size / 2];
        int* left = array;
        int* right = array + size - 1;

        while (true) {
            while ((left <= right) && (*left < pivot))
                left++;
            
            while ((left <= right) && (*right > pivot))
                right--;
            
            if (left > right)
                break;
            
            int temp = *left;
            *left = *right;
            left++;
            *right = temp;
            right--;
        }

        qsort(array, right - array + 1);
        qsort(left, array + size - left);
    }
}

void* qsort_thread(void* obj)
{
    qsort(((QS*)obj)->array_t, ((QS*)obj)->size_t);
    delete ((QS*)obj);
    return NULL;
}

int main(int argc, char** argv)
{
    int maxCountElements = 2000;
    int maxCountThreads = 12;

    printf("Введите кол-во элементов массива: ");
    scanf("%d", &maxCountElements);
    printf("Введите кол-во потоков: ");
    scanf("%d", &maxCountThreads);

    if (maxCountThreads < 1)
        maxCountThreads = 1;

    int* array = new int[maxCountElements];
    int len = maxCountElements / maxCountThreads;

    srand(clock());

    QS** threads = new QS*[maxCountThreads];
    
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double time_mil = (tv.tv_sec) * 1000. + (tv.tv_usec) / 1000.;




    for (int i = 0; i < maxCountElements; i++) {
        array[i] = rand() % 2000;
    }

    for (int i = 0, ai = 0; i < maxCountThreads; i++, ai += len) {
        threads[i] = NULL;
        pthread_t t;

        int size = len + (i == (maxCountThreads - 1) ? (maxCountElements % maxCountThreads) : 0);

        pthread_create(&t, 0, qsort_thread, new QS(&array[ai], size, threads, i));
    }

    int i = 0;
    while (i < maxCountThreads) {
        if (threads[i])
            continue;
        i++;
    }

    if (maxCountThreads > 1) {
        qsort(array, maxCountElements);
    }



    gettimeofday(&tv, NULL);
    double time_mil_ = (tv.tv_sec) * 1000. + (tv.tv_usec) / 1000.;
    cout << "\nSorted in " << (time_mil_ - time_mil) << " ms";

    int last = 0;
    for (int i = 0; i < maxCountElements; i++) {
        if (array[i] < last) {
            cout << "\n\nArray isn't Sorted";
            delete[] array;
            delete[] threads;
            return 0;
        }

        last = array[i];
    }

    cout << "\n\nArray Sorted\n";

    delete[] array;
    delete[] threads;

    return 0;
}