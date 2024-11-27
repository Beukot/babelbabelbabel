#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdlib>
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
void bubblesort(T *arr, std::size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < len; j++)
        {
            if (arr[i] > arr[j])
            {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}

template <typename T>
void measure_time(T, size_t len, void (*func)(T*, std::size_t), int times, int* results)
{
    for (int i = 0; i < times; i++) {
        T arr[len];
        T* arr_ptr = arr;

        populate_arr(arr, len);

        std::cout << "Zaczynam mierzyć czas dla " <<  len << " elementów..." << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        bubblesort(arr_ptr, len);

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Czas zmierzony!\n" << std::endl;
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        results[i] = duration.count();
        len *= 10;
    }
}

int main() {
    SetConsoleOutputCP( 65001 );

    srand (time(NULL));

    size_t len = 10;
    int times = 5;
    int types = 3;

    int results[times];
    int* ptr_results = results;

    int final_results[types][times];

    measure_time(1, len, &bubblesort, times, ptr_results);
    for (int i = 0; i < times; i++) {
        final_results[0][i] = results[i];
    }
    measure_time(static_cast<float>(1.1), len, &bubblesort, times, ptr_results);
    for (int i = 0; i < times; i++) {
        final_results[1][i] = results[i];
    }
    measure_time(1.11, len, &bubblesort, times, ptr_results);
    for (int i = 0; i < times; i++) {
        final_results[2][i] = results[i];
    }

    for (int i = 0; i < types; i++) {
        switch (i) {
            case 0:
                std::cout << "int\t";
                break;
            case 1:
                std::cout << "float\t";
                break;
            case 2:
                std::cout << "double\t";
                break;
            default:
                std::cout << "unknown\t";
                break;
        }

        for (int j = 0; j < times; j++) {
            std::cout << final_results[i][j] << "\t";
        }

        std::cout << std::endl;
    }
}