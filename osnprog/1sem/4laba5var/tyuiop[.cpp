#include <iostream>
#include <random>
#include <time.h>
#include <cmath>

using namespace std;

int main(){
    time_t timer;
    srand(time(&timer));
    
    int n; cout << "количество элементов массива:\n"; cin >> n;

    cout << "массив:\n ";
    double *array = new double [n];
    for (int i = 0; i < n; i++){
        array[i] = rand() % 99 + 1;
        cout << array[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            array[i] = array[i] * array[i];
        } else {
            array[i] = fabs(array[i] * array[i] * array[i]);
        }
    }

    cout << "новый массив:\n ";
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << "\n" << endl;
    delete[] array;
    return 0;
}