#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

long long int bufferSize,matrixWidth,matrixHeight,numberOfSequence;

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
        cout << "\nMetode input txt telah dipilih.\nMasukkan nama file yang ingin dipakai(tanpa .txt): ";
        string path;
        cin >> path;
        path.append(".txt");
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

            file.close();
        } else {
            cout << "\nFile txt tidak ditemukan pada folder test, pastikan penulisan sudah benar!\n";
        }
    } else {
        cout << "random";
    }

    return 0;
}
