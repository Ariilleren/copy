#include <iostream>
#include <random>

using namespace std;

int main() {
    int n;
    cout << "число элементов: "; cin >> n;

    int *array = new int[n]; 
    cout << "элементы массива (буква для случайного):\n";
    
    for (int i = 0; i < n; i++) {
        cout << "#" << i+1 << ": ";
        int elem;
        if (cin >> elem) {
            array[i] = elem;
        }
        else {
            array[i] = rand() % 100 - 50;
            cout << "случайное значение: " << array[i] << endl;
        }
    }
    cout << "Текущий массив:\n";
    for (int i = 0; i < n; i++) {
        cout << array [i] << " ";
    }
    cout << endl << endl;

    int size = 1;
    while (size < n) {
        int left = 0;
        while (left < n) {
            int mid = left + size - 1;
            if (mid >= n - 1) break;
            
            int right = min(left + 2 * size - 1, n - 1);
            
            int n1 = mid - left + 1;
            int n2 = right - mid;
            
            int* leftArray = new int[n1];
            int* rightArray = new int[n2];
            
            for (int i = 0; i < n1; i++) {
                leftArray[i] = array[left + i];
            }
            for (int j = 0; j < n2; j++) {
                rightArray[j] = array[mid + 1 + j];
            }
            
            int i = 0, j = 0, k = left;
            while (i < n1 && j < n2) {
                if (leftArray[i] <= rightArray[j]) {
                    array[k] = leftArray[i];
                    i++;
                }
                else {
                    array[k] = rightArray[j];
                    j++;
                }
                k++;
            }
            
            while (i < n1) {
                array[k] = leftArray[i];
                i++;
                k++;
            }
            
            while (j < n2) {
                array[k] = rightArray[j];
                j++;
                k++;
            }
            
            delete[] leftArray;
            delete[] rightArray;
            
            left += 2 * size;
        }
        size *= 2;
    }

    cout << "Преобразованный массив:\n";
    for (int i = 0; i < n; i++) {
        cout << array [i] << " ";
    }
    
    delete[] array;
}