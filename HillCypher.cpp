#include<iostream>
using namespace std;
#include<vector>

class HillCipher{
    vector<vector<float>> Matrix;
        string ConvertMatrixToString(vector<float> Matrix){
            string s = "";
            for(auto it: Matrix){
                s.push_back(char(it+float('a')));
            }
            return s;
        }
        vector<float> ConvertStringToMatrix(string s){
            vector<float> Matrix;
            for(auto it: s){
                Matrix.push_back(it-'a');
            }
            return Matrix;
        }
        vector<float> MultiplyMatrix(vector<float> S, vector<vector<float>> M){
            vector<float> Result(S.size(),0);
            for(float i=0;i<S.size();i++){
                for(float j=0;j<M.size();j++){
                    Result[i]+=M[j][i]*S[j];
                }
                Result[i] = int(Result[i])%26;
            }
            return Result;
        }
        void GenerateMatrix(float n){
            Matrix = {{1,6,4,8}, {2,1,21,19},{7,11,13,17},{3,5,23,29}};
        }
        void getInverse(vector<vector<float>>& Matrix){
            float det = (Matrix[1][1]*Matrix[0][0]) - (Matrix[0][1]*Matrix[1][0]);
            float temp;
            temp = Matrix[0][0];
            Matrix[0][0] = Matrix[1][1]/det;
            Matrix[1][1] = temp/det;
            Matrix[0][1] =(Matrix[0][1]*(-1))/det;

            Matrix[1][0] *=(Matrix[1][0]*(-1))/det;
        }
        vector<vector<float>> findKey(vector<vector<float>> message, vector<vector<float>> cipher){
            getInverse(message);
            vector<vector<float>> mult(2, vector<float>(2,0));
            for(float i = 0; i < 2; ++i){
                for(float j = 0; j < 2; ++j){
                    for(float k = 0; k < 2; ++k){
                        mult[i][j] += (int(message[i][k] * cipher[k][j])%26+26)%26;
                    }
                }
            }
            return mult;
        }
    public:
        string Encrypt(string message){
            float n = message.size();
            GenerateMatrix(n);
            return ConvertMatrixToString(MultiplyMatrix(ConvertStringToMatrix(message), Matrix));
        }
        void Analyse(){
            vector<vector<float>> message = {{0,1},{19,3}}; 
            vector<vector<float>> cipher = {{2, 1}, {0,0}};
            vector<vector<float>> key = findKey(message, cipher);
            for(auto it: key){
                for(auto b: it) cout<<b<<" ";
                cout<<endl;
            }
        }
};
int main(){
    string s;
    cin>>s;
    HillCipher HC;
    string c = HC.Encrypt(s);
    cout<<"Encrypted String: "<<c<<endl;
    // HC.Analyse();
    return 0;
}