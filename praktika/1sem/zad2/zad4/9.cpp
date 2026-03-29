#include <iostream>
#include <random>

using namespace std;

int main() {
    int n;
    cout << "Введите число элементов массива: "; cin >> n;

    int *array = new int[n]; 
    cout << "Введите элементы массива\nОставьте пустую строку для случайного ввода\n";
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "#" << i+1 << ": ";
        srand(rand());
        string elem;
        getline(cin, elem);
        if (elem.empty()) {
            array[i] = rand() % 100 - 50;
        }
        else {
            array[i] = stoi(elem);
        }
    }
    cout << "Текущий массив:\n";
    for (int i = 0; i < n; i++) {
        cout << array [i] << "\t";
    }
    cout << endl << endl;

    // Алгоритм фон Неймана (сортировка слиянием)
    int groupSize = 1;
    while (groupSize < n) {
        for (int i = 0; i < n; i += 2 * groupSize) {
            int left = i;
            int mid = i + groupSize;
            int right = min(i + 2 * groupSize, n);
            
            if (mid >= n) break; // Если второй группы нет, пропускаем
            
            int *temp = new int[right - left];
            int j = left, k = mid, p = 0;
            
            // Сливаем две упорядоченные группы
            while (j < mid && k < right) {
                if (array[j] <= array[k]) {
                    temp[p++] = array[j++];
                }
                else {
                    temp[p++] = array[k++];
                }
            }
            while (j < mid) temp[p++] = array[j++];
            while (k < right) temp[p++] = array[k++];
            
            // Копируем обратно в исходный массив
            for (int idx = 0; idx < p; idx++) {
                array[left + idx] = temp[idx];
            }
            delete[] temp;
        }
        
        groupSize *= 2;
    }

    cout << "Преобразованный массив:\n";
    for (int i = 0; i < n; i++) {
        cout << array [i] << "\t";
    }
    
    delete[] array;
}