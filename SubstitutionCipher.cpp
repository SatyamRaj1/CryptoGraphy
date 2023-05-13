#include<iostream>
#include<vector>
#include<set>
#include <time.h>
using namespace std;
class SubstitutionCipher{
    vector<int> key;
    vector<int> GenerateKey(){
        vector<int> key;
        set<int> st;
        while(key.size()<26){
            int p = rand()%26;
            if(st.find(p)==st.end()){
                st.insert(p);
                key.push_back(p);
            }
        }
        return key;
    }
    public:
    string Encrypt(string message){
        key = GenerateKey();
        string result = "";
        for(auto it: message){
            int p = int(it)-int('a');
            p = key[p];
            result+=char(p+int('a'));
        }
        return result;
    }
    string Decrypt(string Cypher){
        string result = "";
        vector<int> reverseKey(26,0);
        for(int i=0;i<26;i++){
            reverseKey[key[i]] = i;
        }
        for(auto it: Cypher){
            result.push_back(char(reverseKey[int(it)-'a']+int('a')));
        }
        return result;
    }
};
int main(){
    SubstitutionCipher SC;
    srand(time(0));
    cout<<"Enter message : ";
    string s;
    cin>>s;
    string c5 = SC.Encrypt(s);
    cout<<"Substitution Cypher : "<<c5<<endl;
    cout<<"Decrypt :"<<SC.Decrypt(c5);
    return 0;
}