#include <iostream>
#include<unordered_set>
#include<unordered_map>
using namespace std;

int calculatePower(int a, int n, int mod){
    int res = 1;
    a = a%mod;
    while(n>0){
        if(n & 1)
            res = (res*a)%mod;
        n = n>>1;
        a = (a*a)%mod;
    }
    return res; 
}

int Inverse(int A, int N){
    int n0 = N;
    int y = 0, x = 1;
 
    if (N == 1)
        return 0;
 
    while (A > 1) {
        int q = A / N;
        int t = N;
        N = A % N, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += n0;
    return x;
}

#define MatSize 3
void getCofactor(vector<vector<int> > A, vector<vector<int> >& temp, int p, int q,
                 int n){
    int N = MatSize;
    int i = 0, j = 0;
 
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];
 
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
int determinant(vector<vector<int> > A, int n){
    int N = MatSize;
    int D = 0; 
    if (n == 1)
        return A[0][0];
 
    vector<vector<int> > temp(N, vector<int>(N)); 
 
    int sign = 1; 
    for (int f = 0; f < n; f++) {
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return D;
}
 
// Function to get adjoint of A[N][N] in adj[N][N].
vector<vector<int> > adjoint(vector<vector<int> > A){
    int N = MatSize;
    vector<vector<int> > adj(N, vector<int>(N));
    
    
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            getCofactor(A, temp, i, j, N);
            
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
    }
    
    return adj;
}
 


vector<vector<int> > InverseMatrix(vector<vector<int> > A, int mod){
    int N = MatSize;
    vector<vector<int> > inverse(N, vector<int>(N));
    int det = determinant(A, N);
    if (det == 0) {
        return vector<vector<int> >();
    }
 
    vector<vector<int> > adj = adjoint(A);
    int de = Inverse(det, mod);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            inverse[i][j] = (((adj[i][j] * de)%mod) + mod)%mod;
        }
    }
 
    return inverse;
}


vector<int > MatrixMultiplication(vector<vector<int> >  mat1, vector<int >  mat2, int mod){
    int R1 = mat1.size(), R2 = mat2.size(), C1 = mat1[0].size();
    vector<int>  result(R1);
    for (int i = 0; i < R1; i++) {
        result[i] = 0;
        for (int j = 0; j < C1; j++) {
                result[i] += mat1[i][j] * mat2[j];
                result[i] = (result[i]%mod + mod)%mod;
        }
    }
    return result;
}


vector<int> checkLucky(int n){
    vector<int> Exp(MatSize+1, 0);
    while(n!=1){
        if(n%2==0){
            Exp[0]++;
            n/=2;
        }
        else if(n%3==0){
            Exp[1]++;
            n/=3;
        }
        else if(n%5==0){
            Exp[2]++;
            n/=5;
        }
        else if(n%7==0){
            Exp[3]++;
            n/=7;
        }
        else{
            return vector<int>();
        }
    }
    return Exp;
}



vector<int > ComputeSmallPrimes(int g, int n){
    S:
    // vector<vector<int> > Matrix;
    // vector<int > Y;
    // while(Matrix.size()<4){

    //     int r1 = rand();
    //     int n1 = calculatePower(g, r1, n);
    //     vector<int> m1 = checkLucky(n1);
    //     if(m1.size()>1){
    //         m1[2] = m1[3];
    //         m1.pop_back();
    //         Matrix.push_back(m1);
    //         Y.push_back(r1);
            
    //     }
    // }
    vector<vector<int> > Matrix = {{1, 1, 1}, {1, 3, 0}, {0, 3, 1}};
    vector<int> Y = {4063, 5136, 9865};
    vector<vector<int> > InvMatrix = InverseMatrix(Matrix, n-1);
    if(InvMatrix.size()<1)
        goto S;
    
    return MatrixMultiplication(InvMatrix, Y, n-1);
}
int IndexCalculas(int g, int n, int x){
    vector<int > PrimeLogs = ComputeSmallPrimes(g, n);
    //assuming g = 5
    PrimeLogs.push_back(1);
    PrimeLogs[3] = PrimeLogs[2];
    PrimeLogs[2] = 1;
    while(1){
        int s = rand();
        int gamma = (x*calculatePower(g, s, n))%n;
        // cout<<endl;
        // cout<<"gamma "<<gamma<<endl;
        vector<int> smallPrimeConv = checkLucky(gamma);
        
        if(smallPrimeConv.size()<2){
            continue;
        }
        
        int pmod = n-1;
        int result=0;
        for(int i = 0;i<5;i++){
            result+=smallPrimeConv[i]*PrimeLogs[i];
            result = result%pmod;
        }
        
        return ((result-s)%pmod+pmod)%pmod;
    }
    return 0;
}

int main(){
    srand(time(0));

    // needed to calculate all small log as code gets keeps on calculating non invertible matrix
    int x = 9451;
    int g = 5;
    int n = 10007;
    cout<<"Answer from Index Calculas : "<<IndexCalculas(g, n, x);
    return 0;
    }