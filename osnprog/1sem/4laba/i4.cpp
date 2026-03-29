#include <iostream>
using namespace std;

int main() {
    int n; cout << "размер матрицы N: "; cin >> n;

    int **matrix = new int*[n];
    for (int j = 0; j < n; j++) {
        matrix[j] = new int[n];
    }

    cout << "Матрица " << n << "x" << n << ":\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10 + 1;
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }

    long long product = 1; //  пр
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            product *= matrix[i][j];
        }
    }

    cout << "Прозиведение элементов матрицы: " << product << endl;
    for (int j = 0; j < n; j++) {     // осв памяти
        delete[] matrix[j];
    }
    delete[] matrix;
    return 0;
}