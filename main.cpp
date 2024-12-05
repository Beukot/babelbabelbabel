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
#include <algorithm>

template <typename T>
void populate_arr(T *arr, std::size_t len)
{
    int firstElement = len;

    for (int i = 0; i < len; i++)
    {
        if (typeid(T) == typeid(float))
        {
            arr[i] = static_cast<T>(sqrt(len - i));
        } else {
            arr[i] = static_cast<T>(len - i);
        }

        firstElement--;
    }
}

template <typename T>
void populate_vector(std::vector<T>& arr, std::size_t len)
{
    int firstElement = len;

    for (int i = 0; i < len; i++)
    {
        if (typeid(T) == typeid(float))
        {
            arr.push_back(static_cast<T>(sqrt(len - i)));
        } else {
            arr.push_back(static_cast<T>(len - i));
        }

        firstElement--;
    }
}

template <typename T>
void bubblesort_while_for_short(T *arr, std::size_t len) {
    for (std::size_t i = 0; i < len; i++) {
        for (std::size_t j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

template <typename T>
void bubblesort_while_for_short_pointer(T *arr, std::size_t len) {
    for (std::size_t i = 0; i < len; i++) {
        T* el1 = arr;
        T* el2 = el1 + 1;

        for (std::size_t j = 0; j < len - 1 - i; j++) {
            if (*el1 > *el2) {
                T temp = *(el1);
                *(el1) = *(el2);
                *(el2) = temp;
            }

            el1++;
            el2++;
        }
    }
}

template <typename T>
void bubblesort_while_for_short_vector(T &arr, std::size_t len) {
    for (std::size_t i = 0; i < len; i++) {
        for (std::size_t j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <typename T>
void bubblesort_stdsort(T* arr, std::size_t len) {
    std::sort(arr, arr + len);
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
void check_if_sorted_vector(T& arr, std::size_t len) {
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
void measure_sort_time(T, std::size_t len, void (*sort_func)(T*, std::size_t), int times, int step)
{
    std::cout << typeid(T).name() << "\t";

    for (int i = 0; i < times; i++) {
        T arr[len];
        T* arr_ptr = arr;

        populate_arr(arr_ptr, len);
        // for (int j = 0; j < len; j++) {
        //     std::cout << arr[j] << "\t";
        // }
        // std::cout << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

        sort_func(arr_ptr, len);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        check_if_sorted(arr_ptr, len);

        std::cout << duration.count() << "ms\t";
        // for (int j = 0; j < len; j++) {
        //     std::cout << arr[j] << "\t";
        // }
        // std::cout << std::endl;

        len += step;
    }

    std::cout << std::endl;
}

template <typename T>
void measure_sort_time_vector(T, std::size_t len, void (*sort_func)(std::vector<T>&, std::size_t), int times, int step)
{
    std::cout << typeid(T).name() << "\t";

    for (int i = 0; i < times; i++) {
        std::vector<T> arr;

        populate_vector(arr, len);

        auto start = std::chrono::high_resolution_clock::now();

        sort_func(arr, len);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        check_if_sorted_vector(arr, len);

        std::cout << duration.count() << "ms\t";
        len += step;
    }

    std::cout << std::endl;
}

int main() {
    SetConsoleOutputCP( 65001 );

    srand (time(NULL));

    std::size_t len = 1000;
    int times = 4;
    int step = 1000;

    std::cout << "\nbubblesort for for skrócone" << std::endl;

    std::cout << "\t";
    for (int i = 1; i <= times; i++) {
        std::cout << step * i << "\t";
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_while_for_short, times, step);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_while_for_short, times, step);

    std::cout << "\nbubblesort for for skrócone ze wskaźnikiem" << std::endl;

    std::cout << "\t";
    for (int i = 1; i <= times; i++) {
        std::cout << step * i << "\t";
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_while_for_short_pointer, times, step);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_while_for_short_pointer, times, step);

    std::cout << "\nbubblesort for for skrócone z wektorem i std::swap" << std::endl;

    std::cout << "\t";
    for (int i = 1; i <= times; i++) {
        std::cout << step * i << "\t";
    }
    std::cout << std::endl;

    measure_sort_time_vector(1, len, &bubblesort_while_for_short_vector, times, step);
    measure_sort_time_vector(static_cast<float>(1.1), len, &bubblesort_while_for_short_vector, times, step);

    std::cout << "\nstd::sort" << std::endl;

    std::cout << "\t";
    for (int i = 1; i <= times; i++) {
        std::cout << step * i << "\t";
    }
    std::cout << std::endl;

    measure_sort_time(1, len, &bubblesort_stdsort, times, step);
    measure_sort_time(static_cast<float>(1.1), len, &bubblesort_stdsort, times, step);
}