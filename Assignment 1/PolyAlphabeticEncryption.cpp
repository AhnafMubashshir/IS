#include<bits/stdc++.h>
using namespace std;

int main()
{
    string eStr, uniquee, dStr, str;

    cout<<"Text to Encrypt: ";
    getline(cin, eStr);
    cout<<endl;

    map<char, map<int, char>> strMap;
    map<char, int> strCntMap;

    int len= eStr.size();

    int maxx=0;
    for(int i=0; i<len; i++){
        if(strCntMap[eStr[i]]==0) uniquee+=eStr[i];
        strCntMap[eStr[i]]++;
        if(strCntMap[eStr[i]]>maxx) maxx= strCntMap[eStr[i]];
    }
    int unLen= uniquee.size();
    sort(uniquee.begin(), uniquee.end());

    for(int i=0; i<unLen; i++){
        for(int j=0; j<maxx; j++){
            if(uniquee[i]==' ') strMap[uniquee[i]][j]= ' ';
            else if(uniquee[i] + j + 3>='a' && uniquee[i] + j + 3<='z') strMap[uniquee[i]][j]= uniquee[i] + j + 3;
            else if(uniquee[i] + j + 3>='A' && uniquee[i] + j + 3<='Z') strMap[uniquee[i]][j]= uniquee[i] + j + 3;
            else strMap[uniquee[i]][j]= uniquee[i] + j - 23;
        }
    }

    cout<<"Encryption Table: "<<endl;
    for(int i=0; i<unLen; i++){
        if(uniquee[i]==' ') continue;

        cout<<uniquee[i]<<": ";
        for(int j=0; j<maxx; j++){
            cout<<strMap[uniquee[i]][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;


    cout<<"Encrypted Text: ";
    for(int i=0; i<len; i++){

        int col= i%maxx;

        dStr+= strMap[eStr[i]][col];
    }

    cout<<dStr<<endl<<endl;



//    Decoder

    cout<<"Decrypted Text: ";

    bool flag;

    for(int i=0; i<len; i++){
        flag=false;
        for (auto outer = strMap.begin(); outer != strMap.end(); outer++) {
            auto inner_map = outer->second;
            for (auto inner_iterator = inner_map.begin(); inner_iterator != inner_map.end(); inner_iterator++) {

                int col= i%maxx;

                if(inner_iterator->first == col && inner_iterator->second == dStr[i]){
                    str+=outer->first;
                    flag=true;
                }
            }
            if(flag) break;
        }
    }
    cout<<str<<endl;
}
