#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

int main(){
    int n, m;
    cout << "введите n,m: ";
    cin >> n;
    cin >> m;
    int mat[n][m];

    srand(time(0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j<m; j++){
            mat[i][j] = rand()%101-10;
            cout << mat[i][j] << "   ";
        } 
        cout << endl;
    }
    cout << endl;
    vector<int> arr;
    for (int j = 0; j<m; j++){
        int sch = 0;
        for (int i = 0; i < n; i++){
            if (mat[i][j]>0){
                sch += 1;    
            }
        } 
        if (sch == n){
            int pr = 1;
            for (int i = 0; i<n; i++){
                pr*= mat[i][j];
            }
            arr.push_back(pr);
        }
        else {
            arr.push_back(0);
        }
    }
    int min = 100000000000000000000;
    for (int i = 0; i< arr.size(); i++){
        cout << arr[i] << "    ";
        if (arr[i]>0){
            if (min > arr[i]){
                min = arr[i];
            }
        }
    }

    cout << endl<<  min;
    return 0;
}