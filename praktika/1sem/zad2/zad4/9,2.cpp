#include <iostream>
#include <random>
using namespace std;

int main() {
    int n;
    cout << "число элементов массива: "; cin >> n;

    int *array = new int[n]; 
    cout << "элементы массива\nпустая строка для случайного ввода\n";
    cin.ignore();
    srand(time(0));

    for (int i = 0; i < n; i++) {
        cout << "#" << i+1 << ": ";
        string elem;
        getline(cin, elem);
        if (elem.empty()) {
            array[i] = rand() % 100 - 50;
            cout << array[i] <<endl;
        }
        else {
            array[i] = stoi(elem);
        }
    }
    cout << "массив:\n";
    for (int i = 0; i < n; i++) {
        cout << array [i] << "\t";
    }
    cout << endl << endl;

    int groupSize = 1;
    while (groupSize < n) {
        for (int i = 0; i < n; i += 2 * groupSize) {
            int left = i;
            int mid = i + groupSize;
            int right = min(i + 2 * groupSize, n);
            
            if (mid >= n) break; // если 2 гр нет
            
            int *temp = new int[right - left];
            int j = left, k = mid, p = 0;
            
            // сливаем 2 гр
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
            
            // копируем в исх
            for (int idx = 0; idx < p; idx++) {
                array[left + idx] = temp[idx];
            }
            delete[] temp;
        }
        
        groupSize *= 2;
    }

    cout << "новый массив:\n";
    for (int i = 0; i < n; i++) {
        cout << array [i] << "\t";
    }
    
    delete[] array;
}