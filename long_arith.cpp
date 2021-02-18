#include <iostream>
#include <string>

using namespace std;



char* ResultOperation(string& line1, string& line2, char& operation){
    string l1 = line1;
    string l2 = line1;
    char res;
    switch (operation) {
    case '+':
        res = 'vd';
        break;
    case '-':
        res = 'vd';
        break;
    case '*':
        res = 'vd';
        break;
    case '/':
        res = 'vd';
        break;
    case '^':
        res = 'vd';
        break;
    case '<':
        res = 'vd';
        break;
    case '>':
        res = 'vd';
        break;
    case '=':
        res = 'vd';
        break;
    default:
        cout << "Error";
        break;
    }
    return &res;
}

int main() {
    string line1;
    string line2;
    char *result = nullptr;
    char operation;

     while (true) {
        cin >> line1;
        cin >> line2;
        cin >> operation;
        result = ResultOperation(line1, line2, operation);
        cout << result;
    }
    return 0;
}