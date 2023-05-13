#include<iostream>
#include <time.h>
using namespace std;
class Affine{
    int Z26star[11] = {3,5,7,9,11,15,17,19,21,23,25};
    pair<int,int> key;
    public:
    string Encrypt(string message){
        int Z26star[11] = {3,5,7,9,11,15,17,19,21,23,25};
        int randindex = rand()%11;
        int a = Z26star[randindex];
        int b = rand()%26;
        key = {a,b};
        string c = "";
        for(auto it:message){
            int p = int(it)-int('a');
            p = p*a + b;
            p%=26;
            c += char(p+int('a'));
        }
        return c;
    }
    void Analyse(string message, string p){
        for(int i = 0;i<11;i++){
            int a = Z26star[i];
            for(int b= 0;b<26;b++){
                string result = "";
                for(auto it: message){
                    int p = int(it)-int('a');
                    p = (p - b +26)*a;
                    p = p%26;
                    result+=char(p+int('a'));
                }
                if(result==p) cout<<"----------";
                cout<<result<<endl;
            }
        }
    }
    string Decrypt(string cipher){
        int a=-1;
        for(auto it: Z26star) {
            if(it*key.first%26 == 1){
                a = it;
                break;
            }
        }
        if(a==-1)
            cout<<"error";
        string result = "";
        for(auto it: cipher){
            int p = int(it)-'a';
            p = (p-key.second+26)*a;
            p=p%26;
            result.push_back(char(p+int('a')));
        }
        return result;
    }
};
int main(){
    srand(time(0));
    cout<<"Enter message : \n";
    string s;
    cin>>s;
    Affine A;
    string c2 = A.Encrypt(s);
    cout<<"AffineCypher :  "<<c2<<endl;
    cout<<endl<<"Decrypt : "<<A.Decrypt(c2)<<endl;
    cout<<endl<<"AnalyseAffine"<<endl;
    A.Analyse(c2, s);
    return 0;
}