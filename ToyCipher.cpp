#include<bits/stdc++.h>
using namespace std;
class ToyCipher{
    int SBox[16] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7};
    int Permutation[16] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
    vector<int> MasterKey;
    void GenerateMasterKey(){
        while(MasterKey.size()<20){
            srand(time(0));
            int a = rand();
            while(a!=0 && MasterKey.size()<20){
                MasterKey.push_back(a%2);
                a/=2;
            }
        }
    }
    string encrypt16Bit(string s){
        string result = "";
        GenerateMasterKey();
        int arr[16];
        int k=0;
        //convert string into hexadecimal
        for(int j=0;j<2;j++){
            int m = int(s[j]);
            while(k<(j+1)*8){
                arr[k++] = m%2;
                m/=2;
            }
        }
        for(int round=0;round<4;round++){
            
            // key mixing
            for(int j=0;j<16;j++) arr[j]=arr[j]^MasterKey[j+round];
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
        for(int j=0;j<16;j+=8){
            int m = 0;
            for(int p = j+7;p>=j;p--) m = m*2 + arr[p]; 
            result.push_back(char(m));
        }
        return result;
    }
    
    string decrypt16Bit(string s){
        string result = "";
        int invSBox[16];
        int invPermutation[16];
        for(int i=0;i<16;i++){
            invSBox[SBox[i]] = i;
            invPermutation[Permutation[i]-1] = i; 
        }
        int arr[16];
        int k=0;
        //convert string into hexadecimal
        for(int j=0;j<2;j++){
            int m = int(s[j]);
            if(m<0)
                m+=256;
            while(k<(j+1)*8){
                arr[k++] = m%2;
                m/=2;
            }
        }
        for(int round=3;round>=0;round--){
        
        // key mixing
            if(round!=3){
                int copyarr[16];
                for(int j=0;j<16;j++) copyarr[j] = arr[j];
                for(int j=0;j<16;j++) arr[j] = copyarr[invPermutation[j]];
            } //key mixing in last round
            else{
                for(int j=0;j<16;j++) arr[j]=arr[j]^MasterKey[j+4];
            }
            //SBOX
            for(int j=0;j<16;j+=4){
                int t = 0;
                for(int k=j+3;k>=j;k--){
                    t = t*2 + arr[k];
                }
                
                t = invSBox[t];
                for(int k=j;k<j+4;k++){
                    arr[k] = t%2;
                    t = t/2;
                }
            }
            for(int j=0;j<16;j++) arr[j]=arr[j]^MasterKey[j+round];
        }
        for(int j=0;j<16;j+=8){
            int m = 0;
            for(int p = j+7;p>=j;p--) m = m*2 + arr[p]; 
            result.push_back(char(m));
        }

        return result;
    }
    public:
    string Encrypt(string s){
        string result = "";
        for(int i=0;i<s.length();i+=2){
            string b = "";
            b+=s[i];
            if(i==s.length()-1){  //odd length string
                result+=b;//to store additional character's encyption so that it can be used while decrypting
            }
            else{
                b+=s[i+1];
                b = encrypt16Bit(b);
                result+=b;
            }
        }
        return result;
    }
    string Decrypt(string s){
        string result = "";
        for(int i=0;i<s.length();i+=2){
            string b = "";
            b+=s[i];
            if(i==s.length()-1){  //odd length string
                result+=b;
            }
            else{
                b+=s[i+1];
                b = decrypt16Bit(b);
                result+=b;
            }
        }
        return result;
    }
};
int main(){
    ToyCipher T;
    ifstream infile("test.txt");
    ofstream outfile("encrypted.txt");
    if(infile){
        string s="";
        while(getline(infile, s)){
            string result = T.Encrypt(s);
            outfile << result;
            if(!infile.eof()) {
                outfile << endl;
            }
        }
        
    }
    else{
        cout<<"file not found";
    }
    infile.close();
    outfile.close();

    // Decryption

    ifstream in2file("encrypted.txt");
    ofstream out2file("decrypted.txt");
    if(in2file){
        string s="";
        while(getline(in2file, s)){
            string result = T.Decrypt(s);
            out2file << result;
            if(!in2file.eof()) {
                out2file << endl;
            }
        }
    }
    else{
        cout<<"file not found";
    }
    in2file.close();
    out2file.close();

    return 0;
}