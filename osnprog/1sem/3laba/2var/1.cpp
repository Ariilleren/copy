#include <iostream>
#include <ctime> 
using namespace std;

int main(){
    int n,m;
    cout << "введите n и m: " << endl;
    cin >> n;
    cin >> m;
    
    int mat[n][m];
    srand(time(0));

    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            mat[i][j] = rand()%101-50;
            cout << mat[i][j] << "  ";
        }
        cout << endl;
    }
    int otr = 0;
    int pol = 0;
    int nol = 0;
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            if (mat[i][j] < 0) 
            {
                otr+=1;
            }
            else if (mat[i][j] > 0)
            {
                pol +=1;
            }
            else {
                nol+=1;
            }
        }
    }
    cout << otr << "\n" << pol << "\n" << nol;
    return 0;
}