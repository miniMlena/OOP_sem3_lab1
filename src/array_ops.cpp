#include "array_ops.h"
#include <iostream>

int* array_create(std::size_t size) {
    if (size == 0) {
        return nullptr;
    }
    int* data = new int[size]{};
    return data;
}

void array_delete(int*& arr) {
    if (arr == nullptr) {
        return;
    }
    delete[] arr;
    arr = nullptr;
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size) { // по-хорошему здесь бы & size
    if (arr == nullptr) {
        return nullptr;
    }
    int* new_arr = array_create(new_size);
    std::size_t amount_to_copy = (new_size > size) ? size : new_size;
    for (std::size_t i = 0; i < amount_to_copy; i++) {
        new_arr[i] = arr[i];
    }

    delete[] arr;
    return new_arr;
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value) {
    if (!arr) {
        return nullptr;
    }

    int* new_arr = array_create(size + 1);
    for (std::size_t i = 0; i < pos; i++) {
        new_arr[i] = arr[i];
    }
    new_arr[pos] = value;
    for (std::size_t i = pos + 1; i < size + 1; i++) {
        new_arr[i] = arr[i - 1];
    }

    delete[] arr;
    size += 1;
    return new_arr;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos) {
    if (arr == nullptr) {
        return nullptr;
    }

    int* new_arr = array_create(size - 1);
    
    for (std::size_t i = 0; i < pos; i++) {
        new_arr[i] = arr[i];
    }
    for (std::size_t i = pos; i < size - 1; i++) {
        new_arr[i] = arr[i + 1];
    }

    delete[] arr;
    size -= 1;
    return new_arr;
}

void array_print(const int* arr, std::size_t size) {
    if (arr == nullptr) {
        std::cout << "Array is null!\n";
        return;
    }
    for (std::size_t i = 0; i < size; i++) {
        std::cout << arr[i] << "\t";
    }
    std::cout << "\n";
}

void array_quick_sort(int* arr, int low, int high) {
    if (arr == nullptr || low >= high) {
        return;
    }

    int pivot = arr[low + (high - low) / 2];
    int l = low;
    int r = high;
    while (l <= r) {
        while (l <= high && arr[l] < pivot) {
            l++;
        }
        while (r >= low && arr[r] > pivot) {
            r--;
        }
        if (l <= r) {
            int temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }
    }
    array_quick_sort(arr, low, r);
    array_quick_sort(arr, l, high);
}

int array_kth_smallest(int* arr, std::size_t size, std::size_t k) { //можно ли optional int?
    if (arr == nullptr) {
        std::cout << "Array is null!\n";
        return -1;
    }

    int* new_arr = array_create(size);
    for (std::size_t i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }
    array_quick_sort(new_arr, 0, static_cast<int>(size) - 1);
    int res = new_arr[k - 1];
    delete[] new_arr;
    return res;
}