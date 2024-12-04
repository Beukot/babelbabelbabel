#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <typeinfo>
#include <cstddef>
#include <windows.h>

template <typename T>
void populate_arr(T *arr, std::size_t len)
{
    for (int i = 0; i < len; i++)
    {
        if (typeid(T) == typeid(float) || typeid(T) == typeid(double))
        {
            arr[i] = static_cast<T>(rand() ) / static_cast<T> (1000 / 1.23);
        } else {
            arr[i] = static_cast<T>(rand() % 1000);
        }
    }
}

template <typename T>
void bubblesort_forfor(T *arr, std::size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (arr[i] < arr[j])
            {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

template <typename T>
void bubblesort_forfor_pointer(T *arr, std::size_t len) {
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len; j++) {
            if (arr[i] < arr[j]) {
                T temp = *(arr + i);
                *(arr + i) = *(arr + j);
                *(arr + j) = temp;
            }
        }
    }
}

template <typename T>
void bubblesort_while_true(T *arr, std::size_t len) {
    std::size_t i = 0;
    bool swapped = true;

    while (swapped) {
        swapped = false;
        i = 0;

        while (i < len) {
            if (arr[i] > arr[i + 1]) {
                T temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }

            i++;
        }
    }
}

template <typename T>
void bubblesort_while_true_pointer(T *arr, std::size_t len) {
    std::size_t i = 0;
    bool swapped = true;

    while (swapped) {
        swapped = false;
        i = 0;

        while (i < len) {
            if (arr[i] > arr[i + 1]) {
                T temp = *(arr + i);
                *(arr + i) = *(arr + i + 1);
                *(arr + i + 1) = temp;
                swapped = true;
            }

            i++;
        }
    }
}

template <typename T>
void bubblesort_while_for_short(T *arr, std::size_t len) {
    std::size_t i = 0;

    while (i < len) {
        for (std::size_t j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }

        i++;
    }
}

template <typename T>
void bubblesort_while_for_short_pointer(T *arr, std::size_t len) {
    std::size_t i = 0;

    while (i < len) {
        for (std::size_t j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                T temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }

        i++;
    }
}

template <typename T>
void check_if_sorted(T *arr, std::size_t len) {
    bool sorted = true;

    for (int i = 0; i < len - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            sorted = false;
        }
    }

    if (!sorted) {
        std::cout << "Uwaga! Tablica z " << len << " elementami nie posortowała się!" << std::endl;
    }
}

template <typename T>
void measure_sort_time(T, std::size_t len, void (*sort_func)(T*, std::size_t), int times)
{
    std::cout << typeid(T).name() << "\t";

    for (int i = 0; i < times; i++) {
        T arr[len];
        T* arr_ptr = arr;

        populate_arr(arr_ptr, len);

        auto start = std::chrono::high_resolution_clock::now();

        sort_func(arr_ptr, len);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        check_if_sorted(arr_ptr, len);

        std::cout << duration.count() << "\t";
        len *= 10;
    }

    std::cout << std::endl;
}

int main() {
    SetConsoleOutputCP( 65001 );

    srand (time(NULL));

    std::size_t len = 10;
    int times = 5;

    std::cout << "bubblesort for for" << std::endl;

    std::cout << "\t";
    for (int i = 0; i < times; i++) {
        std::cout << pow(len, i + 1) << "\t";
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_forfor, times);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_forfor, times);
    measure_sort_time(1.11, len, &bubblesort_forfor, times);

    std::cout << "bubblesort for for ze wskaźnikiem" << std::endl;

    std::cout << "\t";
    for (int i = 0; i < times; i++) {
        std::cout << pow(len, i + 1) << "\t";
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_forfor_pointer, times);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_forfor_pointer, times);
    measure_sort_time(1.11, len, &bubblesort_forfor_pointer, times);

    std::cout << "bubblesort while" << std::endl;

    std::cout << "\t";
    for (int i = 0; i < times; i++) {
        std::cout << pow(len, i + 1) << "\t";
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_while_true, times);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_while_true, times);
    measure_sort_time(1.11, len, &bubblesort_while_true, times);

    std::cout << "bubblesort while ze wskaźnikiem" << std::endl;

    std::cout << "\t";
    for (int i = 0; i < times; i++) {
        std::cout << pow(len, i + 1) << "\t";
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_while_true_pointer, times);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_while_true_pointer, times);
    measure_sort_time(1.11, len, &bubblesort_while_true_pointer, times);

    std::cout << "bubblesort while for skrócone" << std::endl;

    std::cout << "\t";
    for (int i = 0; i < times; i++) {
        std::cout << pow(len, i + 1) << "\t";
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_while_for_short, times);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_while_for_short, times);
    measure_sort_time(1.11, len, &bubblesort_while_for_short, times);

    std::cout << "bubblesort while for skrócone ze wskaźnikiem" << std::endl;

    std::cout << "\t";
    for (int i = 0; i < times; i++) {
        std::cout << pow(len, i + 1) << "\t";
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_while_for_short_pointer, times);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_while_for_short_pointer, times);
    measure_sort_time(1.11, len, &bubblesort_while_for_short_pointer, times);
}