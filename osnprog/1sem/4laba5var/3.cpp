#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n; cout << "Введите количество строк массива: "; cin >> n;
    int m; cout << "Введите количество столбцов массива: "; cin >> m;

    double **mas = new double* [n];
    for (int j = 0; j < n; j++) {
        mas[j] = new double [m];
    }

    cout << "Массив:\n";
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mas[i][j] = (rand() % 200 - 100) / 10.0;
            cout << mas[i][j] << "\t";
        }
        cout << endl;
    }
//1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //эл который нужно переместить 
            for (int i2 = i; i2 < n; i2++) {
                for (int j2 = (i2 == i ? j + 1 : 0); j2 < m; j2++) {
                    if (fabs(mas[i][j]) > 1 && fabs(mas[i2][j2]) <= 1) {
                        // Меняем местами
                        double temp = mas[i][j];
                        mas[i][j] = mas[i2][j2];
                        mas[i2][j2] = temp;
                    }
                }
            }
        }
    }

    //2 часть
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fabs(mas[i][j]) > 1) {
                for (int i2 = i; i2 < n; i2++) {
                    for (int j2 = (i2 == i ? j + 1 : 0); j2 < m; j2++) {
                        if (fabs(mas[i2][j2]) > 1 && fabs(mas[i][j]) < fabs(mas[i2][j2])) {
                            double temp = mas[i][j];
                            mas[i][j] = mas[i2][j2];
                            mas[i2][j2] = temp;
                        }
                    }
                }
            }
        }
    }

    cout << "Полученный массив:\n" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << mas[i][j] << "\t";
        }
        cout << endl;
    }

    for (int j = 0; j < n; j++) {
        delete[] mas[j];
    }
    delete[] mas;

    return 0;
}