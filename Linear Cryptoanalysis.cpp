#include<bits/stdc++.h>
using namespace std;
class ToyCipher{
    public:
    vector<int> MasterKey;
    
    int u4 = 0;
    int SBox[16] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 };
    int Permutation[16] = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };
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
            u4 = 0;
            //Permutation
            if(round!=3){
                int copyarr[16];
                for(int j=0;j<16;j++) copyarr[j] = arr[j];
                for(int j=0;j<16;j++) arr[j] = copyarr[Permutation[j]-1];
            } //key mixing in last round
            else{
                for(int j=0;j<16;j++){
                arr[j]=arr[j]^MasterKey[j+4];
                u4 += MasterKey[j+4];
                u4*=2; 
                }
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
    string Encrypt(string s){
        string result = "";
        for(int i=0;i<s.length();i+=2){
            string b = "";
            b+=s[i];
            if(i==s.length()-1){  //odd length string
                result+=b;//to store additional character's encyption so that it can be used while decrypting
                result+=" ";
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
    unordered_map<string, string> MessageCipherPair;
    int pairsize = 10000;
    while(MessageCipherPair.size()!=pairsize){
        string s="";
        int r = rand()%65536;
        s +=char(r%256);
        r/=256;
        s+=char(r%256);
        MessageCipherPair[s] = T.Encrypt((s));
    }
    int minerror = INT_MAX;
    int bestguess = -1;
    int bestcount = 0;
    for(int i = 0;i<256;i++){
        int  p = i;
        int guess[16];
        for(int k = 0;k<16;k++){
            if(k<4 || (k>7 && k<12))
                guess[k] = 0;
            else{
                guess[k] = p%2;
                p/=2;
            }
        }
        // calculate count;
        int count = 0;
        for(auto it: MessageCipherPair){
            int m1 = int(it.first[0]), m2 = int(it.first[1]);
            int c1 = int(it.second[0]), c2 = int(it.second[1]);
            int cipherarr[16];
            int messagearr[16];
            for(int j=0;j<16;j++){
                if(j<8){
                    cipherarr[j] = c1%2;
                    c1/=2;
                    messagearr[j] = m1%2;
                    m1/=2;
                }
                else{
                    cipherarr[j] = c2%2;
                    c2/=2;
                    messagearr[j] = m2%2;
                    m2/=2;
                }
                cipherarr[j] = cipherarr[j] ^ guess[j];
            }
            int invSBox[16];
            for(int j=0;j<16;j++){
                invSBox[T.SBox[j]] = j;
            }
            int arru4[16];
            for(int j=0;j<16;j+=4){
                int t = 0;
                for(int k=j+3;k>=j;k--){
                    t = t*2 + cipherarr[k];
                }
                
                t = invSBox[t];
                for(int k=j;k<j+4;k++){
                    arru4[k] = t%2;
                    t = t/2;
                }
            }
            if(!(messagearr[4]^messagearr[6]^messagearr[7]^arru4[5]^arru4[7]^arru4[13]^arru4[15]))
                count++;
        }
        int lowlim = (15*pairsize)/32;
        int highlim = (17*pairsize)/32;
        int error = min(abs(lowlim-count), abs(highlim-count));
        if(error<minerror){
            bestguess = i;
            minerror = error;
            bestcount=  count;
        }
    }
    cout<<bestguess<<"\n"<<bestcount<<"\n"<<minerror<<endl;
    cout<<T.u4<<endl;
    int k = T.u4;
    int u4array[16] = {0};
    int p = 15;
    while(k!=0 || p>-1){
        u4array[p--] = k%2;
        k/=2;
    }
    for(auto it: u4array) cout<<it<<" ";
    cout<<endl;
    int guessed[16] = {0};
    for(int k = 4;k<8;k++){
        int temp = guessed[k];
        guessed[k] = guessed[k+8];
        guessed[k+8] = temp;
    }
    for(int k = 0;k<16;k++){
        if((k>=4 && k<8) || (k>11))
            guessed[k] = 0;
        else{
            guessed[k] = bestguess%2;
            bestguess/=2;
        }
    }
    for(auto it: guessed) cout<<it<<" ";
    cout<<endl;
    for(auto it: T.MasterKey) cout<<it<<" ";

    return 0;
}