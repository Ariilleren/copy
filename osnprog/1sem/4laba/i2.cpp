#include <iostream>
#include <time.h>
using namespace std;

int main(){
    time_t timer;
    srand(time(&timer));
    int n; cout << "количество элементов массива:\n"; cin >> n;

    cout << "массив:\n{ ";
    int *array = new int [n];
    for (int i = 0; i < n; i++){
        array[i] = rand() % 100 - 50;
        cout << array[i] << " ";
    }
    cout << "}\n" << endl;

    for (int i = 0; i < n; i++) {     //отр - модули
        if (array[i] < 0) {
            array[i] = -array[i];
        }
    }

    for (int i = 0; i < n / 2; i++) { // изм порядок
        int temp = array[i];
        array[i] = array[n - 1 - i];
        array[n - 1 - i] = temp;
    }

    cout << "новый массив:\n{ ";
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << "}" << endl;

    delete[] array;
    return 0;
}