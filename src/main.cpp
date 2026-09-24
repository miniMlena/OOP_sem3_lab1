#include "array_ops.h"
#include <iostream>
#include <limits>

bool read_int(int& value) {
    if (std::cin >> value) {
        char next = std::cin.peek();
        if (next == '.' || next == ',') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

int main() {
    int* array = nullptr;
    std::size_t size = 0;
    int choice = -1;

    std::cout << "\nChoose operation:\n";
    std::cout << "1. Create array\n";
    std::cout << "2. Print array\n";
    std::cout << "3. Resize array\n";
    std::cout << "4. Insert value to array\n";
    std::cout << "5. Remove element from array\n";
    std::cout << "6. Find k-th minimal element in array\n";
    std::cout << "0. Exit\n";
    
    while (true) {
        std::cout << "Your choice: ";
        
        if (!read_int(choice)) {
            std::cout << "Input error! Please enter an integer.\n";
            continue;
        }
        
        switch (choice) {
            case 1: {
                int s = 0;
                std::cout << "size: ";
                if (!read_int(s)) {
                    std::cout << "Invalid input! Please enter an integer.\n";
                    break;
                }
                if (s < 0) {
                    std::cout<<"Size must be not less than 0.\n";
                    break;
                }
                array_delete(array);
                size = static_cast<std::size_t>(s);
                array = array_create(size);
                std::cout << "Array of size " << size << " created.\n";
                break;
            }
            case 2: {
                if (!array) {
                    std::cout << "Create array first!\n";
                    break;
                }
                std::cout << "Current array:\n";
                array_print(array, size);
                break;
            }
            case 3: {
                if (!array) {
                    std::cout << "Create array first!\n";
                    break;
                }
                int new_s = 0;
                std::cout << "new_size: ";
                if (!read_int(new_s)) {
                    std::cout << "Invalid input! Please enter an integer.\n";
                    break;
                }
                if (new_s < 0) {
                    std::cout<<"Size must be not less than 0.\n";
                    break;
                }
                std::size_t new_size = static_cast<std::size_t>(new_s);
                array = array_resize(array, size, new_size);
                size = new_size;
                std::cout << "Array resized to " << new_size << ".\n";
                break;
            }
            case 4: {
                if (!array) {
                    std::cout << "Create array first!\n";
                    break;
                }
                int p = 0;
                std::cout << "position: ";
                if (!read_int(p)) {
                    std::cout << "Invalid input! Please enter an integer.\n";
                    break;
                }
                if (p < 0) {
                    std::cout << "Position must be not less than 0.\n";
                    break;
                }
                std::size_t pos = static_cast<std::size_t>(p);
                if (pos > size) {
                    std::cout << "Position out of range.\n";
                    break;
                }
                int val = 0;
                std::cout << "value: ";
                if (!read_int(val)) {
                    std::cout << "Invalid input! Please enter an integer.\n";
                    break;
                }
                array = array_insert(array, size, pos, val);
                std::cout << "Value " << val << " inserted to array in position "<< pos <<".\n";
                break;
            }
            case 5: {
                if (!array) {
                    std::cout << "Create array first!\n";
                    break;
                }
                int p = 0;
                std::cout << "position: ";
                if (!read_int(p)) {
                    std::cout << "Invalid input! Please enter an integer.\n";
                    break;
                }
                if (p < 0) {
                    std::cout << "Position must be not less than 0.\n";
                    break;
                }
                std::size_t pos = static_cast<std::size_t>(p);
                if (pos >= size) {
                    std::cout << "Position out of range.\n";
                    break;
                }
                array = array_remove(array, size, pos);
                std::cout << "Element on position " << pos << " removed from array.\n";
                break;
            }
            case 6: {
                if (!array) {
                    std::cout << "Create array first!\n";
                    break;
                }
                int int_k = 0;
                std::cout << "k: ";
                if (!read_int(int_k)) {
                    std::cout << "Invalid input! Please enter an integer.\n";
                    break;
                }
                if (int_k < 1) {
                    std::cout << "Number must be not less than 1.\n";
                    break;
                }
                std::size_t k = static_cast<std::size_t>(int_k);
                if (k > size) {
                    std::cout << "k out of range.\n";
                    break;
                }
                int res = array_kth_smallest(array, size, k);
                std::cout << k << "-th smallest element is " << res << ".\n";
                break;
            }
            case 0: {
                array_delete(array);
                std::cout << "Exit.\n";
                return 0;
            }
            default:
                std::cout << "Invalid option!\n";
        }
    }
    return 0;
}