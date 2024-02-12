#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <sys/stat.h>
using namespace std;

long long int tokenSize, bufferSize, matrixWidth, matrixHeight, numberOfSequence, maxSequence, pointMax = 0;
vector<int> point = {}, pathMax = {};
vector<string> sequence = {};
vector<vector<string>> matrix;

string RemoveSpace(string str){
    int size = str.length();
    for(int i=0;i<=size;i++){
        for(int j=0;j<=i;j++){
            if(str[j] == ' '){
                str.erase(str.begin() + j);
            }
        }
    }
    return str;
}

void HitungPoin(vector<int> path){
    long long int i, points = 0;
    string str = "";

    // Mengubah path menjadi string
    for(i=0;i<path.size();i++){
        str.append(matrix[(path[i])/matrixWidth][(path[i])%matrixWidth]);
    }

    // Menambahkan poin untuk tiap sequence yang muncul
    for(i=0;i<sequence.size();i++){
        if(str.find(sequence[i]) != -1){
            points += point[i];
        }
    }

    // Mengganti nilai pointMax dan path jika nilai poin lebih besar dari poin sekarang
    if(points > pointMax){
        pointMax = points;
        pathMax = path;
    }
    
    // Untuk mendapatkan jawaban dengan banyak token minimal
    if(points == pointMax && path.size() < pathMax.size()){
        pointMax = points;
        pathMax = path;
    }
}

void iterate(vector<int> path){
    long long int mods,i;
    // Jika awal iterasi
    if(path.size() == 0){
        for(i=0;i<matrixWidth;i++){
            path = {};
            path.push_back(i);
            iterate(path);
        }
    } else if(path.size() == bufferSize){ // Jika Buffer sudah penuh
        HitungPoin(path);
    } else if(path.size() % 2){ // Jika gerakan sebelumnya horizontal
        mods = path.back() % matrixWidth;
        for(i=0;i<matrixHeight;i++){
            vector<int> newPath;
            if(find(path.begin(),path.end(),(matrixWidth*i) + mods) == path.end()){
                newPath = path;
                newPath.push_back((matrixWidth*i) + mods);
                iterate(newPath);
            }
        }
        HitungPoin(path);
    } else { // Jika gerakan sebelumnya vertikal
        mods = (path.back() / matrixWidth) * matrixWidth;
        for(i=mods;i<mods+matrixWidth;i++){
            vector<int> newPath;
            if(find(path.begin(),path.end(),i) == path.end()){
                newPath = path;
                newPath.push_back(i);
                iterate(newPath);
            }
        }
        HitungPoin(path);
    }
}

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
            // Variabel untuk menyimpan sebuah line dalam file
            string line;

            // Membaca ukuran buffer
            getline(file,line);
            bufferSize = stoi(line);

            // Membaca ukuran matrix
            getline(file,line);
            int temp = line.length();
            size_t found = line.find(" ");
            matrixWidth = stoi(line.substr(0,found));
            matrixHeight = stoi(line.substr(found+1,temp-found));

            // Membaca matrix
            for(long long int i=0;i<matrixHeight;i++){
                getline(file,line);
                vector<string> temps = {};
                for(long long int j=0;j<matrixWidth;j++){
                    temps.push_back(line.substr(3*j,2));
                }
                matrix.push_back(temps);
            }

            // Membaca Sekeuns
            getline(file,line);
            numberOfSequence = stoi(line);
            for(long long int i=0;i<numberOfSequence;i++){
                getline(file,line);
                sequence.push_back(RemoveSpace(line));
                getline(file,line);
                point.push_back(stoi(line));
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
        for(long long int i=0;i<tokenSize;i++){
            token[i] = userInput.substr(3*i,2);
        }

        cout << "Masukkan ukuran buffer : ";
        cin >> bufferSize;
        srand(time(0));

        cout << "Masukkan ukuran matrix(Lebar Panjang) : ";
        cin.ignore();
        getline(cin,userInput);
        int temp = userInput.length();
        size_t found = userInput.find(" ");
        matrixWidth = stoi(userInput.substr(0,found));
        matrixHeight = stoi(userInput.substr(found+1,temp-found));
        for(long long int i=0;i<matrixHeight;i++){
            vector<string> temps = {};
            for(long long int j=0;j<matrixWidth;j++){
                temps.push_back(token[rand() % tokenSize]);
            }
            matrix.push_back(temps);
        }

        cout << "Masukkan jumlah sekuens : ";
        cin >> numberOfSequence;

        cout << "Masukkan ukuran maksimal sekuens : ";
        cin >> maxSequence;
        for(long long int i=0;i<numberOfSequence;i++){
            string temps = "";
            long long int gacha = (rand() % (maxSequence - 2)) + 2;
            for(long long int j=0;j<gacha;j++){
                temps += token[rand() % tokenSize];
            }
            sequence.push_back(temps);
            point.push_back((rand() % 200) - 100);
        }

        cout << "Matriks permainan :\n";
        for(long long int i=0;i<matrixHeight;i++){
            for(long long int j=0;j<matrixWidth;j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Sekuens permainan :\n";
        for(long long int i=0;i<numberOfSequence;i++){
            for(long long int j=0;j<sequence[i].length();j++){
                cout << sequence[i][j];
                if(j%2){
                    cout << " ";
                }
            }
            cout << endl << point[i] << endl;
        }
    }

    // Memulai Bruteforce
    auto start = chrono::high_resolution_clock::now();
    iterate({});
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Output
    cout << "Reward : " << pointMax;
    cout << "\nPath : ";
    for(int i=0;i<pathMax.size();i++){
        cout << matrix[pathMax[i]/matrixWidth][pathMax[i]%matrixWidth] << " ";
    }
    cout << "\nCoordinate :\n";
    for(int i=0;i<pathMax.size();i++){
        cout << pathMax[i]%matrixWidth + 1 << ", " << pathMax[i]/matrixWidth + 1 << endl;
    }
    cout << "\nTime taken : " << duration.count() << " ms" << endl;

    cout << "Apakah ingin menyimpan solusi? (y/n)\n";
    cin >> userInput;
    while(userInput.length() != 1 || !(userInput[0] == 89 || userInput[0] == 121 || userInput[0] == 78 || userInput[0] == 110)){
        cout << "\nMasukkan tidak valid.\nApakah ingin menyimpan solusi? (y/n)\n";
        cin >> userInput;
    }

    if(userInput == "y" || userInput == "Y"){
        cout << "Masukkan nama file untuk disimpan : ";
        cin.ignore();
        getline(cin,userInput);
        userInput.insert(0,"../test/");

        ofstream outputFile(userInput);

        if (!outputFile.is_open()) {
            cerr << "Error opening file for writing!" << endl;
            return 1;
        }

        // Menuliskan data ke file external
        outputFile << "Reward : " << pointMax;
        outputFile << "\nPath : ";
        for(int i=0;i<pathMax.size();i++){
            outputFile << matrix[pathMax[i]/matrixWidth][pathMax[i]%matrixWidth] << " ";
        }
        outputFile << "\nCoordinate :\n";
        for(int i=0;i<pathMax.size();i++){
            outputFile << pathMax[i]%matrixWidth + 1 << ", " << pathMax[i]/matrixWidth + 1 << endl;
        }
        outputFile << "\nTime taken : " << duration.count() << " ms" << endl;

        outputFile.close();

        cout << "File telah berhasil disimpan!" << endl;
    } else {
        cout << "Terima kasih telah menggunakan program ini!\n";
    }

    return 0;
}