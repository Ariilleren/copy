#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cout << "n: ";
    cin >> n;
    int m[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= j && i + j < n) {
                m[i][j] = 1;
            } else if (i <= j && i + j >= n - 1) {
                m[i][j] = 1;
            } else {
                m[i][j] = 0;
            }
        }
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}