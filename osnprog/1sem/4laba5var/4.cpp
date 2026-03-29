#include <iostream>
using namespace std;

int main() {
    int n; cout << "Введите размерность матрицы: "; cin >> n;
    int **mat = new int*[n];
    for (int j = 0; j < n; j++) {
        mat[j] = new int[n];
    }

    cout << "Матрица:\n";
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = rand() % 100;
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }

    int maxSum = -1000;

    //выше гл
    for (int k = 0; k < n; k++) {
        int sum = 0;
        for (int i = 0, j = k; i < n && j < n; i++, j++) {
            sum += mat[i][j];
        }
        if (sum > maxSum) {
            maxSum = sum;
        }
    }

    //ниже гл
    for (int k = 1; k < n; k++) {
        int sum = 0;
        for (int i = k, j = 0; i < n && j < n; i++, j++) {
            sum += mat[i][j];
        }
        if (sum > maxSum) {
            maxSum = sum;
        }
    }

    cout << "Максимум среди сумм диагоналей: " << maxSum << endl;

    for (int j = 0; j < n; j++) {
        delete[] mat[j];
    }
    delete[] mat;
    return 0;
}