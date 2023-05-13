#include<iostream>
#include<vector>
#include<cstdlib>
#include <time.h>
#include<map>
using namespace std;

class VigenereCiphere{
    vector<int> key;
    float Freq[26] = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 0.008, 0.040, 0.024, 0.067, 0.075, 0.019, 0.001, 0.060, 0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001};
    vector<string> divideCipher(string message, int k){
        vector<string> result(k, "");
        for(int i=0;i<message.length();i++){
            result[i%k].push_back(message[i]);
            
        }
        return result;
    }
    vector<float> calculateProbability(string message, int k){
        vector<string> v = divideCipher(message, k);
        vector<float> prob(k,0);
        for(int i=0;i<k;i++){
            float f[26] = {0};
            for(auto it: v[i]){
                f[int(it)-int('a')]++;
            }
            for(int j=0;j<26;j++){
                prob[i]+=f[j]*f[j];
            }
            prob[i]/=(v[i].length()*v[i].length());
        }
        return prob;
    }
    bool checkProbability(string message, int k){
        vector<float> p = calculateProbability(message, k);
        cout<<k<<endl;
        for(auto it: p){
            if((it>0.075) || (it<0.05))
                return false;
        }
        // if(k==message.size()/2)
            return true;
        // return false;
    }
    string getmessage(string cipher, int k){
        vector<string> v = divideCipher(cipher, k);
        vector<int> shift(k,0);
        for(int i=0;i<k;i++){
            float f[26] = {0};
            
            for(auto it: v[i]){
                f[int(it)-int('a')]+=1;
            }
            float highprob = 0;
            int highshift = -1;
            for(int p=0;p<26;p++){
                float prob = 0;
                for(int j=0;j<26;j++){
                    prob+=f[j]*Freq[(j+p)%26];
                }
                if(prob>highprob){
                    highprob = prob;
                    highshift = p;
                }
            }
            string r = "";
            for(auto it: v[i]){
                r.push_back(char(((it-'a')+highshift)%26 + int('a')));
            }
            v[i] = r;
        }
        string message = "";
        int i=0;
        while(i<v[0].size()){
            for(auto it: v){
                if(i<it.size())
                    message.push_back(it[i]);
                else 
                    break;
            }
            i++;
        }
        return message;
    }
    vector<int> getKey(int n){
        vector<int> k;
        for(int i=0;i<n;i++) k.push_back(rand()%26);
        return k;
    }
    public:
        string Encrypt(string message){
        string result = "";
        key = getKey(4);
        for(int i=0;i<message.size();i++) result+=(char((int(message[i])-int('a')+key[i%4])%26 + int('a')));
        return result;
        }
        string Analyse(string cipher){
            for(int i = 1;i<cipher.length();i++){
            // int i = 4;
                // return getmessage(cipher, 4);
                cout<<endl<<i<<" ";
                if(checkProbability(cipher, i)){
                    
                     return getmessage(cipher, i);
                }
            }
            return "NotFound";
        }
        string Decrypt(string message){
            string result = "";
            for(int i=0;i<message.size();i++){
                result.push_back(char((int(message[i])-'a'-key[i%key.size()]+26)%26)+int('a'));
            }
            return result;
        }

};

int main(){
    srand(time(0));
    cout<<"Enter message : ";
    string s;
    cin>>s;
    cout<<s.length();
    VigenereCiphere VC;
    string c3 = VC.Encrypt(s);
    cout<<"\n Decrypt : "<<VC.Decrypt(c3);
    cout<<"\nVigenere Cypher : "<<c3<<endl;
    cout<<"Analyse : "<<VC.Analyse(c3);
    return 0;
}