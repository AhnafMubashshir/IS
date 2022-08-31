#include<bits/stdc++.h>
using namespace std;

int main()
{
    string eStr, dStr;

    cout<<"Text to Encode: ";
    getline(cin,eStr);
    cout<<endl;

    map<char, char> strCntMap;
    map<char, char> strMap;

    int len= eStr.size();

    for(int i=0; i<len; i++){
        if(strCntMap[eStr[i]]==0){
            strCntMap[eStr[i]]++;
            if(eStr[i]==' ') strMap[eStr[i]]= ' ';
            else if(eStr[i]>='a' && eStr[i]<'x') strMap[eStr[i]]= eStr[i]+3;
            else if(eStr[i]>='A' && eStr[i]<'X') strMap[eStr[i]]= eStr[i]+3;
            else{
                strMap[eStr[i]]= eStr[i]-23;
            }
        }
    }
    strCntMap.clear();

    cout<<"Encoder Table: "<<endl;
    for(int i=0; i<len; i++){
        if(strCntMap[eStr[i]]==0 && eStr[i]!=' '){
            strCntMap[eStr[i]]++;
            cout<<eStr[i]<<" "<<strMap[eStr[i]]<<endl;
        }
    }
    cout<<endl;

    cout<<"Encoded Text: ";
    for(int i=0; i<len; i++){
        dStr+= strMap[eStr[i]];
    }

    cout<<dStr<<endl;



//    Decoder

    cout<<endl<<"Decoded text: ";
    for(int i=0; i<len; i++){
        for(auto itr= strMap.begin(); itr!= strMap.end(); itr++){
            if(itr->second == dStr[i]){
                cout<<itr->first;
                break;
            }
        }
    }
    cout<<endl;
}
