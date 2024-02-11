#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef struct{
    vector<string> str;
    long long int point;
} SEQUENCE;

long long int tokenSize, bufferSize, matrixWidth, matrixHeight, numberOfSequence, maxSequence, i, j, k, ans = 0;

int main(){
    cout << "Selamat datang di \n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "______                     _      ______          _                  _ \n";
    cout << "| ___ \\                   | |     | ___ \\        | |                | |\n";
    cout << "| |_/ /_ __ ___  __ _  ___| |__   | |_/ / __ ___ | |_ ___   ___ ___ | |\n";
    cout << "| ___ \\ '__/ _ \\/ _` |/ __| '_ \\  |  __/ '__/ _ \\| __/ _ \\ / __/ _ \\| |\n";
    cout << "| |_/ / | |  __/ (_| | (__| | | | | |  | | | (_) | || (_) | (_| (_) | |\n";
    cout << "\\____/|_|  \\___|\\__,_|\\___|_| |_| \\_|  |_|  \\___/ \\__\\___/ \\___\\___/|_|\n\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "INPUT :\n1. txt\n2. Random\n";
    cout << "Silahkan pilih metode input : ";

    string userInput;
    cin >> userInput;
    while(userInput.length() != 1 || !(userInput[0] == 49 || userInput[0] == 50)){
        cout << "\nMasukkan tidak valid.\nSilahkan pilih metode input : ";
        cin >> userInput;
    }

    int input = stoi(userInput);

    if(input == 1){
        cout << "\nMetode input txt telah dipilih.\nMasukkan nama file txt yang ingin dipakai (pastikan sudah ada dalam folder test): ";
        string path;
        cin >> path;
        path.insert(0,"../test/");

        fstream file;

        file.open(path,ios::in);
        if (file.is_open()){
            string line;

            getline(file,line);
            bufferSize = stoi(line);
            cout << "Buffer Size : " << bufferSize << endl;

            getline(file,line);
            int temp = line.length();
            size_t found = line.find(" ");
            matrixWidth = stoi(line.substr(0,found));
            matrixHeight = stoi(line.substr(found+1,temp-found));
            cout << "Matrix Width : " << matrixWidth << endl;
            cout << "Matrix Height : " << matrixHeight << endl;

            string matrix[matrixHeight][matrixWidth];

            for(i=0;i<matrixHeight;i++){
                getline(file,line);
                for(j=0;j<matrixWidth;j++){
                    matrix[i][j] = line.substr(3*j,2);
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }

            getline(file,line);
            numberOfSequence = stoi(line);
            cout << "Number of sequence : " << numberOfSequence << endl;
            SEQUENCE seq[numberOfSequence];
            for(i=0;i<numberOfSequence;i++){
                getline(file,line);
                temp = line.length() + 1;
                temp /= 3;
                for(j=0;j<temp;j++){
                    string temps = line.substr(3*j,2);
                    seq[i].str.push_back(temps);
                    cout << seq[i].str[j] << endl;
                }
                getline(file,line);
                seq[i].point = stoi(line);
                cout << "point : " << seq[i].point << endl;
            }

            file.close();
        } else {
            cout << "\nFile txt tidak ditemukan pada folder test, pastikan penulisan sudah benar!\n";
        }
    } else {
        cout << "Masukkan jumlah token unik : ";
        cin >> tokenSize;
        string token[tokenSize];

        cout << "Masukkan token unik(dipisahkan dengan spasi): ";
        cin.ignore();
        getline(cin,userInput);
        for(i=0;i<tokenSize;i++){
            token[i] = userInput.substr(3*i,2);
        }

        cout << "Masukkan ukuran buffer : ";
        cin >> bufferSize;

        cout << "Masukkan ukuran matrix(Lebar Panjang) : ";
        cin.ignore();
        getline(cin,userInput);
        int temp = userInput.length();
        size_t found = userInput.find(" ");
        matrixWidth = stoi(userInput.substr(0,found));
        matrixHeight = stoi(userInput.substr(found+1,temp-found));

        cout << "Masukkan jumlah sekuens : ";
        cin >> numberOfSequence;

        cout << "Masukkan ukuran maksimal sekuens : ";
        cin >> maxSequence;
    }

    return 0;
}
