#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n1; cout << "количество строк первого массива: "; cin >> n1;
    int m1; cout << "количество столбцов первого массива: "; cin >> n1;
    
    int n2; cout << "количество строк второго массива: "; cin >> n2;
    int m2; cout << "количество столбцов второго массива: "; cin >> n2;

    int **mas1 = new int* [n1]; // 1 массив
    for (int j = 0; j < n1; j++) {
        mas1[j] = new int [m1];
    }

    int **mas2 = new int* [n2];     // 2 массив
    for (int j = 0; j < n2; j++) {
        mas2[j] = new int [m2];
    }

    cout << "первый массив:\n";
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            mas1[i][j] = rand() % 100 - 50;
            cout << mas1[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "второй массив:\n";
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            mas2[i][j] = rand() % 100 - 50;
            cout << mas2[i][j] << "\t";
        }
        cout << endl;
    }

    for (int i = 0; i < n1; i++) {     // сорт 1 по возр
        for (int j = 0; j < m1; j++) {
            for (int i2 = 0; i2 < n1; i2++) {
                for (int j2 = 0; j2 < m1; j2++) {
                    if (mas1[i][j] < mas1[i2][j2]) {
                        int temp = mas1[i][j];
                        mas1[i][j] = mas1[i2][j2];
                        mas1[i2][j2] = temp;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n2; i++) { // сорт 2 по уб кв мод
        for (int j = 0; j < m2; j++) {
            for (int i2 = 0; i2 < n2; i2++) {
                for (int j2 = 0; j2 < m2; j2++) {
                    int mod1 = abs(mas2[i][j]);
                    int mod2 = abs(mas2[i2][j2]);
                    if (mod1 * mod1 > mod2 * mod2) {
                        int temp = mas2[i][j];
                        mas2[i][j] = mas2[i2][j2];
                        mas2[i2][j2] = temp;
                    }
                }
            }
        }
    }

    cout << "первый массив после сортировки:\n";
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            cout << mas1[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "второй массив после сортировки:\n";
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            cout << mas2[i][j] << "\t";
        }
        cout << endl;
    }

    for (int j = 0; j < n1; j++) { // Осв памяти
        delete[] mas1[j];
    }
    delete[] mas1;
    for (int j = 0; j < n2; j++) {
        delete[] mas2[j];
    }
    delete[] mas2;
    return 0;
}