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

int ShankAlgo(int g, int n, int x){
    int m = sqrt(n);
    m++;
    unordered_set<int> St;
    unordered_map<int, int> mp;
    for(int j = 0;j<m;j++){
        int gmj = calculatePower(g, m*j, n);
        St.insert(gmj);
        mp[gmj] = j;
    }
    for(int i = 0; i<m;i++){
        int p = calculatePower(g, i, n);
        int col = (x*Inverse(p, n))%n;
        if(St.find(col)!=St.end())
            return (m*mp[col] + i)%n;
    }
    return -1;
}
///////////////////////////////////////////////////////////////////// 

int main(){
    srand(time(0));
    int x, g, n;
    // x = 9451;
    // g = 5;
    // n = 10007;
    cout<<"Enter Number to find it's log : ";
    cin>>x;
    cout<<"Enter g ( generator) : ";
    cin>>g;
    cout<<"Enter mod (p) : ";
    cin>>n;
    
    
    cout<<"Value of x from Shanks's Algoithm : "<<ShankAlgo(g, n, x);
    // to find logx -- base g log 9451 = 6057
    
    return 0;
}

