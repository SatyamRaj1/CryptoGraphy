
#include<iostream>
#include <time.h>
using namespace std;
string EncryptPermutation(string message){
    int n = message.length();
    for(int i=0;i<n;i++){
        int ind = i+rand()%(n-i);
        char temp = message[ind];
        message[ind] = message[i];
        message[i] = temp;
    }
    return message;
}
int main(){
    srand(time(0));
    cout<<"Enter message : ";
    string s;
    cin>>s;
    string c4 = EncryptPermutation(s);
    cout<<"Permutation Cypher : "<<c4<<endl;
    return 0;
}