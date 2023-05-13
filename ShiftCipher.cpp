#include<iostream>
using namespace std;
string EncryptShift(string message){
    int key = rand()%26;
    cout<<key<<endl;
    string result = "";
    for(auto it:message){
        result+=char((int(it) - int('a')+key)%26 + int('a'));
    }
    return result;
}
string DecryptShift(string message, int key){
    string result = "";
        for(auto it:message){
            result+=char((int(it) - int('a')-key+26)%26 + int('a'));
        }
        return result;
}
void AnalyseShift(string message){
    for(int key = 0;key<26;key++){
        string result = "";
        for(auto it:message){
            result+=char((int(it) - int('a')-key+26)%26 + int('a'));
        }
        cout<<result<<endl;
    }
}
int main(){
    cout<<"Enter message : ";
    string s;
    cin>>s;
    
    
    string c = EncryptShift(s);
    cout<<"EncryptShift : "<<c<<endl;
    cout<<DecryptShift(c,11);
    cout<<"\n\n Decrypted messages \n\n";
    AnalyseShift(c);
    return 0;
}