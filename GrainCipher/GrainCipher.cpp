#include<bits/stdc++.h>
using namespace std;

class GrainCipher{
    vector<bool> ArrN = vector<bool>(80, 1);
    vector<bool> ArrL = vector<bool>(80);
    vector<bool> Key;
    int NFSR(){
        return ArrN[62] ^ ArrN[60] ^ ArrN[52] ^ ArrN[45] ^ ArrN[37] ^ ArrN[33] ^ ArrN[28] ^ ArrN[21] ^ ArrN[14] ^ ArrN[9] ^ ArrN[0] ^
            (ArrN[63] & ArrN[60]) ^ (ArrN[37] & ArrN[33]) ^ (ArrN[15] & ArrN[9]) ^
            (ArrN[60] & ArrN[52] & ArrN[45]) ^ (ArrN[33] & ArrN[28] & ArrN[21]) ^
            (ArrN[63] & ArrN[45] & ArrN[28] & ArrN[9]) ^ (ArrN[60] & ArrN[52] & ArrN[37] & ArrN[33]) ^
            (ArrN[63] & ArrN[60] & ArrN[21] & ArrN[15]) ^ (ArrN[63] & ArrN[60] & ArrN[52] & ArrN[45] & ArrN[37]) ^
            (ArrN[33] & ArrN[28] & ArrN[21] & ArrN[15] & ArrN[9]) ^ (ArrN[52] & ArrN[45] & ArrN[37] & ArrN[33] & ArrN[28] & ArrN[21]) ;   
    }
    void InsertinNFSR(int k){
        for(int i=0;i<79;i++) ArrN[i] =  ArrN[i+1];
        ArrN[79] = k;
    }
    void updateLFSR(){
        int k = ArrL[62] ^ ArrL[51] ^ ArrL[38] ^ ArrL[23] ^ ArrL[13] ^ ArrL[0]; 
        for(int i=0;i<79;i++) ArrL[i] =  ArrL[i+1];
        ArrL[79] = k;
    }
    void updateNFSR(){
        InsertinNFSR(ArrL[0]^NFSR());
        updateLFSR();
    }
    
    int genKey(){
        int A[] = {1, 2, 4, 10, 31, 43, 56};
        int p =0;
        updateNFSR();
        
        for(auto it: A){
            p = p^ArrN[it];
        }
        p = p^HFunction(3,25, 46, 64, 63);
    }
    
    int HFunction(int a, int b, int c, int d, int e){
        return b^e^(a&d)^(c&d)^(d&e)^(a&b&c)^(a&c&d)^(a&c&e)^(b&c&e)^(c&d&e);
    }
    public: 
        void SetIV(vector<int> IV){
            for(int i=0;i<80;i++){
                if(i<64)
                    ArrN[i] = IV[i];
                ArrL[i] = Key[i];
            }
        }
        
        void GenerateKey(){
            srand(time(0));
            int a = rand();
            while(Key.size()<80){
                Key.push_back(a%2);
                a = a/2;
                if(a==0)
                    a = rand();
            }
        }
        string EncryptDecrypt(string s){
            // createNFSR(IV);
            string result="";
            // cout<<s<<endl;
            for(auto it: s){
                int a = int(it);
                if(a<0)
                    a+=256;
                bool arr[8];
                // cout<<a<<" ";
                for(int i=0;i<8;i++){
                    arr[i] = a%2;
                    arr[i]=arr[i]^genKey();
                    a/=2;
                }
                a = 0; 
                for(int i = 7;i>=0;i--){
                    a=a*2 + arr[i];
                }
                // cout<<a<<" ";
                result+=char(a);
            }
            return result;
            // cout<<result<<endl;
        }
        
};
int main(){
    GrainCipher G;
    G.GenerateKey();
    vector<int> IV;
    int a = rand();
    while(IV.size()<64){
        IV.push_back(a%2);
        a/=2;
        if(a==0)
            a = rand();
    }
    // string p = G.EncryptDecrypt("ABC", IV);
    // cout<<p<<endl;
    // cout<<G.EncryptDecrypt(p, IV);
    ifstream infile("test.txt");
    ofstream outfile("GrainEncrypted.txt");
    if(infile){
        G.SetIV(IV);
        string s="";
        while(getline(infile, s)){
            string result = G.EncryptDecrypt(s);
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

    ifstream in2file("GrainEncrypted.txt");
    ofstream out2file("GrainDecrypted.txt");
    if(in2file){
        G.SetIV(IV);
        string s="";
        while(getline(in2file, s)){
            string result = G.EncryptDecrypt(s);
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