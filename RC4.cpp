#include<iostream>
#include<vector>
using namespace std;
class RC4{
    vector<int> GenerateKey(string k, int m){
        // KSA
        vector<int> IVvector;
        for(auto it: k){
            IVvector.push_back(int(it));
        }
        int n = IVvector.size();
        vector<int> s;
        for(int i=0;i<256;i++){
            s.push_back(i);
        }
        int j=0;
        for(int i=0;i<256;i++){
            j = (j+s[i]+IVvector[i%n])%256;
            int temp = s[i];
            s[i] = s[j];
            s[j] = temp;
        }
        // PRGA
        int i = 0;
        j = 0;
        vector<int> z;
        while(z.size()<m){
            i = (i+1)%256;
            j = (j+s[i])%256;
            int temp = s[i];
            s[i] = s[j];
            s[j] = temp;
            z.push_back(s[(s[i]+s[j])%256]);
        }
        return z;
    }
    public:
    string Encrypt(string message, string IV){
        vector<int> Key = GenerateKey(IV, message.size());
        // cout<<Key<<endl;
        string Cipher = "";
        vector<int> messageArray;
        for(int i=0;i<message.size();i++){
            Cipher.push_back(char(int(message[i])^Key[i]));
        }
        return Cipher;
    }
    string Decrypt(string Cipher, string IV){
        vector<int> Key = GenerateKey(IV, Cipher.size());
        // cout<<Key<<endl;
        string Message = "";
        vector<int> CipherArray;
        for(int i=0;i<Cipher.size();i++){
            Message.push_back(char(int(Cipher[i])^Key[i]));
        }
        return Message;
    }
};
int main(){
    RC4 RC;
    string message = "todayismonday";
    cout<<"Message : "<<message<<endl;
    string cipher = RC.Encrypt(message, "10101");
    cout<<"cipher : "<<cipher<<endl;
    cout<<"After Decrypting : "<<RC.Decrypt(cipher, "10101");
}