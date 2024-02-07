#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main(){
    string str = "896 6";
    size_t found = str.find(" ");
    cout << found;
}