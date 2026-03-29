#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    int n, m;
    cout << "n: " << endl;
    cin >> n;
    cout << "m: " << endl;
    cin >> m;
    cout << endl;

    srand(time(0));
    int a[n][m];
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            a[i][j] = rand()%101-50;
            cout << a[i][j]<< "    ";
        }   
        cout << endl;
    }
    cout << endl;

    int ch[m] = {0};
    for (int j = 0; j<m; j++){
        for (int i = 0; i<n; i++){
            if ((a[i][j]%2 != 0) && (a[i][j]< 0)){
                ch[j] += abs(a[i][j]);
            }
        }   
    }

    for (int i = 0; i<m; i++){
        cout << ch[i] << " ";
    }

    for (int i = 0; i<m-1; i++){
        for (int j = 0; j< m - i -1; j++){
            if (ch[j] > ch[j +1]){
                swap(ch[j], ch[j+1]);
                for (int k = 0; k<n; k++){
                    swap (a[k][j], a[k][j+1]);
                }
            }
        }   
        cout << endl;
    }
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            cout << a[i][j]<< "    ";
        }   
        cout << endl;
    }
    cout << endl;

    return 0;
}
