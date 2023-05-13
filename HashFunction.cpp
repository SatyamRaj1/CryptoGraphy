#include<bits/stdc++.h>
using namespace std;
class ToyCipher{
    int SBox[16] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7};
    int Permutation[16] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
    public:
    vector<int> Encrypt16Bit(vector<int> arr, vector<int> MasterKey){
        for(int round=0;round<4;round++){
            // key mixing
            for(int j=0;j<16;j++) arr[j]=arr[j]^MasterKey[(j+round)%16];
            //Substitution
            for(int j=0;j<16;j+=4){
                int t = 0;
                for(int k=j+3;k>=j;k--){
                    t = t*2 + arr[k];
                }
                t = SBox[t];
                for(int k=j;k<j+4;k++){
                    arr[k] = t%2;
                    t = t/2;
                }
            }
            //Permutation
            if(round!=3){
                int copyarr[16];
                for(int j=0;j<16;j++) copyarr[j] = arr[j];
                for(int j=0;j<16;j++) arr[j] = copyarr[Permutation[j]-1];
            } //key mixing in last round
            else{
                for(int j=0;j<16;j++) arr[j]=arr[j]^MasterKey[j+4];
            }
        }
        return arr;
    }
    
};
class HashFunction{
    vector<int> convertStringToArray(string s){
        vector<int> arr;
        for(auto c: s){
            int k = 7;
            int n = int(c);
            vector<int> current(8,0);
            
            while(n>0){
                current[k] = n%2;
                n/=2;
            }
            arr.insert(arr.end(), current.begin(), current.end());
        }
        return arr;
    }
    ToyCipher T;
    vector<int> IVvector = vector<int>(16,0);
    public:
    string Encrypt(string message){
        int i = 0;
        vector<int> Y = convertStringToArray(message);
        vector<int> Mi = IVvector;
        bool firstiter = 0;
        int paddingZeros = 0;
        while(i<Y.size()){
            vector<int> Yi(16, 0);
            Yi[0] = firstiter;
            firstiter = 1;
            int j = 1;
            for(int k = i;k<i+15;k++){
                if(k>=Y.size()){
                    paddingZeros = 15-j;
                    break;
                }
                Yi[j++] = Y[k]; 
            }
            Mi = CompressionFucntion(Mi, Yi);
            i+=19;
        }
        vector<int> Yi(16,0);
        Yi[0] = 1;
        int j = 15;
        while(paddingZeros!=0){
            Yi[j--] = paddingZeros%2;
            paddingZeros/=2;
        }
        Mi = CompressionFucntion(Mi, Yi);
        string result = "";
        int  p = 0;
        j = 15;
        while(j>=0){
            p = p*2 + Mi[j--];
            if(j==7 || j<0){
                result+=char(p);
                p=0;
            }
        }
        for(int i = 0;i<16;i++){
            cout<<Mi[i]<<" ";
        }
        return result;

    }
    vector<int> CompressionFucntion(vector<int> Mi, vector<int> Yi){
        Mi = T.Encrypt16Bit(Mi, Yi);
        for(int k = 0;k<16;k++) Mi[k] = Mi[k]^Yi[k];
        return Mi;
    }
};

int main(){
    HashFunction H;
    ifstream infile("test.txt");
    string message = "";
    if(infile){
        string s="";
        while(getline(infile, s)){
            message += s;
        } 
    }
    else{
        cout<<"file not found";
    }
    infile.close();
    string result;
    result = H.Encrypt(message);
    ofstream outfile("encrypted.txt");
    outfile << result;
    outfile.close();
    return 0;
}