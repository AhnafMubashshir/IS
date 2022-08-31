#include<iostream>
#include<string>
#include<map>
using namespace std;

string add_round_key[16][16];
string Text[4][4];
string w[50][4];


string S_Box[16][16]=
{
    "63", "7C", "77", "7B", "F2", "6B", "6F", "C5", "30", "01", "67", "2B", "FE", "D7", "AB", "76",
    "CA", "82", "C9", "7D", "FA", "59", "47", "F0", "AD", "D4", "A2", "AF", "9C", "A4", "72", "C0",
    "B7", "FD", "93", "26", "36", "3F", "F7", "CC", "34", "A5", "E5", "F1", "71", "D8", "31", "15",
    "04", "C7", "23", "C3", "18", "96", "05", "9A", "07", "12", "80", "E2", "EB", "27", "B2", "75",
    "09", "83", "2C", "1A", "1B", "6E", "5A", "A0", "52", "3B", "D6", "B3", "29", "E3", "2F", "84",
    "53", "D1", "00", "ED", "20", "FC", "B1", "5B", "6A", "CB", "BE", "39", "4A", "4C", "58", "CF",
    "D0", "EF",	"AA", "FB",	"43", "4D",	"33", "85",	"45", "F9",	"02", "7F",	"50", "3C",	"9F", "A8",
    "51", "A3",	"40", "8F",	"92", "9D",	"38", "F5",	"BC", "B6", "DA", "21", "10", "FF", "F3", "D2",
    "CD", "0C", "13", "EC", "5F", "97", "44", "17", "C4", "A7", "7E", "3D", "64", "5D", "19", "73",
    "60", "81", "4F", "DC", "22", "2A", "90", "88", "46", "EE", "B8", "14", "DE", "5E", "0B", "DB",
    "E0", "32", "3A", "0A", "49", "06", "24", "5C", "C2", "D3", "AC", "62", "91", "95", "E4", "79",
    "E7", "C8", "37", "6D", "8D", "D5", "4E", "A9", "6C", "56",	"F4", "EA", "65", "7A", "AE", "08",
    "BA", "78", "25", "2E", "1C", "A6", "B4", "C6", "E8", "DD", "74", "1F", "4B", "BD", "8B", "8A",
    "70", "3E", "B5", "66", "48", "03", "F6", "0E", "61", "35", "57", "B9", "86", "C1", "1D", "9E",
    "E1", "F8", "98", "11", "69", "D9", "8E", "94", "9B", "1E", "87", "E9", "CE", "55", "28", "DF",
    "8C", "A1", "89", "0D", "BF", "E6", "42", "68", "41", "99", "2D", "0F", "B0", "54", "BB", "16"

};


//Map for binary value to hexadecimal storing
map <string, string> btoh=
{
    {"0000", "0"},
    {"0001", "1"},
    {"0010", "2"},
    {"0011", "3"},
    {"0100", "4"},
    {"0101", "5"},
    {"0110", "6"},
    {"0111", "7"},
    {"1000", "8"},
    {"1001", "9"},
    {"1010", "A"},
    {"1011", "B"},
    {"1100", "C"},
    {"1101", "D"},
    {"1110", "E"},
    {"1111", "F"}
};



//X-OR operation
string x_or(string str1, string str2)
{
    string xor_bin= "";

    for(int i=0; i<str1.length(); i++){
        if( (str1[i]=='0' && str2[i]=='0') || (str1[i]=='1' && str2[i]=='1') ) xor_bin+= "0";
        else xor_bin+= "1";
    }

    return xor_bin;
}



int HexToDec(string str)
{
    int len = str.length();

    int base = 1;

    int dec_val = 0;


    for (int i = len - 1; i >= 0; i--) {
        if (str[i] >= '0' && str[i] <= '9') {
            dec_val += (int(str[i]) - 48) * base;

            base = base * 16;
        }


        else if (str[i] >= 'A' && str[i] <= 'F') {
            dec_val += (int(str[i]) - 55) * base;


            base = base * 16;
        }
    }
    return dec_val;
}



//converting decimal to hexadecimal
string DecToHex(int n)
{
    string hex= "";

    while(n!=0){
        int temp;
        char ch;
        string temp_str;

        temp= n%16;

        if(temp<10){
            ch= (char) temp+48;
            temp_str= ch;
        }
        else{
            ch= (char) temp+55;
            temp_str= ch;
        }

        hex= temp_str+ hex;

        n/=16;
    }

    return hex;
}
//converting text to hexadecimal
string TextToHex(string str)
{
    string hex= "";
    for(int i=0; i< str.length(); i++){
        int temp= (int) str[i];

        hex+= DecToHex(temp);
    }

    return hex;
}


//Hexadecimal to Binary
string HexToBin(string str)
{
    string bin;

//    For padding 0
//    while(str.length()%4!=0){
//        str= "0" + str;
//    }

    int i= str.length()-1;

    while(i>-1){
        if (str[i]=='0') bin= "0000" +bin;
        else if (str[i]=='1') bin= "0001" +bin;
        else if(str[i]=='2') bin= "0010" +bin;
        else if(str[i]=='3') bin= "0011" +bin;
        else if(str[i]=='4') bin= "0100" +bin;
        else if(str[i]=='5') bin= "0101" +bin;
        else if(str[i]=='6') bin= "0110" +bin;
        else if(str[i]=='7') bin= "0111" +bin;
        else if(str[i]=='8') bin= "1000" +bin;
        else if(str[i]=='9') bin= "1001" +bin;
        else if(str[i]=='A' || str[i]=='a') bin= "1010" +bin;
        else if(str[i]=='B' || str[i]=='b') bin= "1011" +bin;
        else if(str[i]=='C' || str[i]=='c') bin= "1100" +bin;
        else if(str[i]=='D' || str[i]=='d') bin= "1101" +bin;
        else if(str[i]=='E' || str[i]=='e') bin= "1110" +bin;
        else if(str[i]=='F' || str[i]=='f') bin= "1111" +bin;

        i--;
    }

    return bin;
}


//Binary to Hexadecimal
string BinToHex(string str)
{
    string hex= "";
    int opt= 0;

    while(1){
        hex+= btoh[ str.substr(opt, 4)];
        opt+=4;
        if(opt==str.length()) break;
    }

    return hex;
}



//Round key construction
void construct_RoundKey(string str)
{
    string hex_str= TextToHex(str);


//    word seperation
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=(i*8)+j*2; k<(i*8)+(j*2)+2; k++){
                w[i][j]+=hex_str[k];
            }
        }
    }

    for(int i=0, k=0; i<4; i++){
        for(int j=0; j<4; j++, k++){
            add_round_key[0][k]= w[i][j];
        }
    }


    for(int m=3, round_number=1; round_number<11 ; m+=4, round_number++){

        string round_cnst;

        if(round_number==1) round_cnst= "01";
        else if(round_number==2) round_cnst= "02";
        else if(round_number==3) round_cnst= "04";
        else if(round_number==4) round_cnst= "08";
        else if(round_number==5) round_cnst= "10";
        else if(round_number==6) round_cnst= "20";
        else if(round_number==7) round_cnst= "40";
        else if(round_number==8) round_cnst= "80";
        else if(round_number==9) round_cnst= "1B";
        else if(round_number==10) round_cnst= "36";

//        G function
        string G[4];
        G[0]= w[m][0];
        G[1]= w[m][1];
        G[2]= w[m][2];
        G[3]= w[m][3];



//        left circular shift
        string l_shift;
        l_shift= G[0];

        for(int i=0; i<4; i++) G[i]= G[i+1];
        G[3]=l_shift;



//        Substitution bytes
        string sub_bytes;

        for(int i=0; i<4; i++){
            string row_col= G[i];

            if(row_col[0]>='0' && row_col[0]<='9'){
                if(row_col[1]>='0' && row_col[1]<='9') G[i]= S_Box[ row_col[0]-48 ][ row_col[1]-48 ];
                else G[i]= S_Box[ row_col[0]-48 ][ row_col[1]-55 ];
            }
            else{
                if(row_col[1]>='0' && row_col[1]<='9') G[i]= S_Box[ row_col[0]-55 ][ row_col[1]-48 ];
                else G[i]= S_Box[ row_col[0]-55 ][ row_col[1]-55 ];
            }
        }





//        X-ORing constant

        G[0]= BinToHex( x_or( HexToBin(G[0]), HexToBin(round_cnst) ) );



//        Constructing Round Key
        w[m+1][0]= BinToHex( x_or( HexToBin(G[0]), HexToBin(w[m-3][0]) ) );
        w[m+1][1]= BinToHex( x_or( HexToBin(G[1]), HexToBin(w[m-3][1]) ) );
        w[m+1][2]= BinToHex( x_or( HexToBin(G[2]), HexToBin(w[m-3][2]) ) );
        w[m+1][3]= BinToHex( x_or( HexToBin(G[3]), HexToBin(w[m-3][3]) ) );


        for(int i=m+2; i<m+5; i++){
            for(int j=0; j<4; j++){
                w[i][j]= BinToHex( x_or( HexToBin(w[i-1][j]), HexToBin(w[i-4][j]) ) );
            }
        }

        for(int i=m+1, k=0; i<m+5; i++){
            for(int j=0; j<4; j++, k++){
                add_round_key[round_number][k]= w[i][j];
            }
        }
    }
}



void TtoH(string str)
{
    string txt= TextToHex(str);

    for(int i=0, j=0; i<txt.length(); i+=2, j++){
        Text[j%4][j/4]+= txt[i];
        Text[j%4][j/4]+= txt[i+1];
    }
}


//Add round key operation
void AddRoundKey(int round)
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            Text[i][j]= BinToHex( x_or( HexToBin( Text[i][j] ), HexToBin( add_round_key[round][(j*4)+i] ) ) );
        }
    }
}


string two_rule(int i, int j)
{
    string temp= HexToBin(Text[i][j]);
    int choice=0;

    if(temp[0]=='1') choice=1;

    temp.erase(temp.begin()+0);

    temp+= "0";

    if(choice==1) temp= x_or( temp, HexToBin("1B") );

    temp= BinToHex(temp);


    return temp;
}


void MixColumn()
{
    string state_mat[4][4]=
    {
        "02", "03", "01", "01",
        "01", "02", "03", "01",
        "01", "01", "02", "03",
        "03", "01", "01", "02"
    };
    string temp_text_mat[4][4];



    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            string temp= "00";
            string temp1="00";

            for(int k=0; k<4; k++){
                if(state_mat[i][k]== "01") temp= BinToHex( x_or( HexToBin(temp), HexToBin(Text[k][j]) ) );
                else if(state_mat[i][k]== "02") {
                    temp= BinToHex( x_or( HexToBin(temp), HexToBin( two_rule(k, j) ) ) );
                }
                else{
                    temp1=two_rule(k, j);

                    temp1= BinToHex( x_or( HexToBin(temp1), HexToBin(Text[k][j]) ) );
                    temp= BinToHex( x_or( HexToBin(temp), HexToBin(temp1) ) );

                }
            }

            temp_text_mat[i][j]= temp;
        }
    }


//    copying cypher text in main text
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            Text[i][j]= temp_text_mat[i][j];
        }
    }
}


void ShiftRows()
{
    for(int i=1; i<4; i++){
        if(i==1){
            string l_shift;
            l_shift= Text[i][0];

            for(int j=0; j<3; j++) Text[i][j]= Text[i][j+1];
            Text[i][3]=l_shift;
        }
        else if(i==2){
            string l_shift;

            l_shift=Text[i][0];
            Text[i][0]=Text[i][2];
            Text[i][2]= l_shift;

            l_shift=Text[i][1];
            Text[i][1]=Text[i][3];
            Text[i][3]= l_shift;

        }
        else{
            string r_shift;
            r_shift= Text[i][3];

            for(int j=3; j>0; j--) Text[i][j]= Text[i][j-1];
            Text[i][0]=r_shift;
        }
    }
}


void SubBytes()
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            string row_col= Text[i][j];

            if(row_col[0]>='0' && row_col[0]<='9'){
                if(row_col[1]>='0' && row_col[1]<='9') Text[i][j]= S_Box[ row_col[0]-48 ][ row_col[1]-48 ];
                else Text[i][j]= S_Box[ row_col[0]-48 ][ row_col[1]-55 ];
            }
            else{
                if(row_col[1]>='0' && row_col[1]<='9') Text[i][j]= S_Box[ row_col[0]-55 ][ row_col[1]-48 ];
                else Text[i][j]= S_Box[ row_col[0]-55 ][ row_col[1]-55 ];
            }
        }
    }
}



void encryption()
{
    AddRoundKey(0);

    for(int i=1; i<10; i++){
        SubBytes();
        ShiftRows();
        MixColumn();
        AddRoundKey(i);
    }

    SubBytes();
    ShiftRows();
    AddRoundKey(10);
}

int main()
{
    string text, key;

    freopen("Input.txt", "r", stdin);

    getline(cin, text);
    getline(cin, key);

    fclose(stdin);

    construct_RoundKey(key);
    TtoH(text);



    //    Plain Text
    cout<<"Plain Text (In Hexadecimal Format): ";
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cout<<Text[i][j]<<" ";
        }
    }
    cout<<endl<<endl;



    encryption();


//    cyphered text
    cout<<"Cyphered Text (In Hexadecimal Format): ";
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cout<<Text[i][j]<<" ";
        }
    }
    cout<<endl;
}
