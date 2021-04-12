#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;


map<string,string> loaded_phonebook;

vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;
    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    } 
    return answer;
}

void init(void){
    printf(".______    __    __    ______   .__   __.  _______ .______     ______     ______    __  ___ \n");
    printf("|   _  \\  |  |  |  |  /  __  \\  |  \\ |  | |   ____||   _  \\   /  __  \\   /  __  \\  |  |/  / \n");
    printf("|  |_)  | |  |__|  | |  |  |  | |   \\|  | |  |__   |  |_)  | |  |  |  | |  |  |  | |  '  /  \n");
    printf("|   ___/  |   __   | |  |  |  | |  . `  | |   __|  |   _  <  |  |  |  | |  |  |  | |    <   \n");
    printf("|  |      |  |  |  | |  `--'  | |  |\\   | |  |____ |  |_)  | |  `--'  | |  `--'  | |  .  \\  \n");
    printf("| _|      |__|  |__|  \\______/  |__| \\__| |_______||______/   \\______/   \\______/  |__|\\__\\ \n");              
}

void menu(void){
    printf("What do you want to do?\n");
    printf("1. Insert the Phone number.\n");
    printf("2. Find the Phone number.\n");
    printf("3. Find the Person.\n");
    printf("4. Save and Exit!\n");
}

void API_LoadPhonebook(){  
    ifstream read_phonebook;
    read_phonebook.open("phonebook.csv");
    
    string line;
    vector<string> splited_line;
    

    // 파일이 열렸는 지 확인
    if(read_phonebook.is_open()){
        getline(read_phonebook,line); // header 없애기 위해
        while(getline(read_phonebook, line)){
            splited_line = split(line, ',');
            loaded_phonebook[splited_line[0]]=splited_line[1];
        }
    }

    return ;
}

void API_SavePhonebook(void){
    ofstream write_phonebook;
    write_phonebook.open("phonebook.csv");

    write_phonebook << "name" <<"," <<"number" << "\n";

    if(write_phonebook.is_open()){
        for (auto it = loaded_phonebook.begin(); it != loaded_phonebook.end(); it++)
        {
            write_phonebook << (*it).first << "," << (*it).second << "\n";
        }
    }

    return ;
}

int API_InsertPhoneNumber(string name, string number){
    loaded_phonebook[name] = number;
    return loaded_phonebook.size();
}

int InsertPhoneNumber(){ 
    string name;
    string number;
    printf("name: ");
    getline(cin, name);
    printf("number(ex,010xxxxxxxx): ");
    getline(cin, number);
    int ret = API_InsertPhoneNumber(name, number);
    return ret;
}

string API_FindPhoneNumber(string name){
    if(loaded_phonebook.count(name) == 0){
        string ERROR("No PhoneNumber of");
        ERROR = ERROR + name;
        return ERROR;
    }
    string number = loaded_phonebook[name];
    return number;
}

string FindPhoneNumber(){
    string name;
    printf("name: ");
    getline(cin,name);
    
    string number = API_FindPhoneNumber(name); //number or errormessage
    cout << number << "\n";
    return number;
}

string API_FindPerson(string number){ // 아마 map 두개로 사용하는 게 메모리는 많이 먹어도 빠르긴 할 듯
    for (auto it = loaded_phonebook.begin(); it != loaded_phonebook.end(); it++)
    {
        if ((*it).second == number) return (*it).first;        
    }

    string ERROR("No Person of");
    ERROR = ERROR + number;
    return ERROR;    
}

string FindPerson(){
    string number;
    printf("number: ");
    getline(cin,number);
    string name = API_FindPerson(number);
    cout << name << "\n";

    return name;
}

int main(int argc, char const *argv[])
{
    char menu_num;
    char while_exit = 0;
    init();
    API_LoadPhonebook();
    while (1)
    {
        menu();
        cin >> menu_num;
        cin.ignore();
        switch (menu_num)
        {
        case '1':
            InsertPhoneNumber();
            break;
        
        case '2':
            FindPhoneNumber();
            break;
        
        case '3':
            FindPerson();
            break;
        
        case '4':
            while_exit = 1;
            break;
        
        default:
            printf("[ERROR] Invalid Number\n");
            break;
        }

        if(while_exit) break;
    }
    API_SavePhonebook();
    return 0;
}
