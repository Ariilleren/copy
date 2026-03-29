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
        //cout << groupSize;
        for (int i = 0; i < n; i += 2 * groupSize) {
            int left = i; //cout << left; //начало 1 гр
            int mid = i + groupSize; //cout << groupSize; //нач 2
            int right = min(i + 2 * groupSize, n); //cout << right; //конец 2 <=n
            
            if (mid >= n) break; // если 2 гр нет
            
            int *temp = new int[right - left];
            int j = left;//текущий эл 1г 
            int k = mid; //тэ 2г
            int p = 0; //позиция в темпе
            //cout << j << k << p << endl;
            
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