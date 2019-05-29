#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <regex>
#include <vector>

int main(){
std::string input, str, num, buf, conflict;
std::regex BEGINING("^(int |short |long )([A-Za-z]([A-Za-z]|[0-9]){0,8})(\[[0-9][0-9]+\])([=]\\{[-]?[0-9]+).*");
std::regex LIST("(,[-]?[0-9]+).*");
std::regex TAIL("\\}$");
std::smatch m;
std::vector<std::string> names;
std::ofstream fout;
std::ifstream fin;
fout.open("t_res.txt", std::ios_base::out);
fin.open("tests.txt");
if(!(fin.is_open() && fout.is_open())){
    std::cout<<"Erore of opening files";
    return 0;
}

int number, mul = 1, size;
clock_t TIME;
clock_t a,b;
while(std::getline(fin, input)){
    a = clock();
    bool x=std::regex_match(input,m,BEGINING);
    if(!x){
        fout<<"Incorrect.\n";
        input = "";
        continue;
    }
    num = m[4];
    str = m[1];
    buf += str;
    str = m[2];
    buf += str;
    str = m[4];
    buf += str;
    str = m[5];
    buf += str;
    str = m[2];
    input.erase(0, buf.size());
    num.pop_back();
    num.erase(0,1);
    mul = 1;
    number = 0;
    for(int i = num.size()-1; i>=0; i--)
    {
        number += mul*(num[i] - 48);
        mul *= 10;
    }
    for(int i = 1; i < number; i++)
    {
        x=std::regex_match(input,m,LIST);
        buf = m[1];
        input.erase(0,buf.size());
        if(!x)
            break;
    }
    if(!x){
        fout<<"Incorrect."<<std::endl;
        input = "";
        continue;
    }
    x=std::regex_match(input,m,TAIL);
    if(!x){
        fout<<"Incorrect.\n";
        input = "";
        continue;
    }

    conflict = "none";
    if(str == "int")
        conflict = "int";
    if(str == "short")
        conflict = "short";
    if(str == "long")
        conflict = "long";
    for(int i = names.size() - 1; i>=0; i--)
    {
        if(names[i] == str)
        {
            conflict = names[i];
            break;
        }
    }
    input = "";
    buf="";
    fout<<"Correct|Conflict: "<<conflict<<"\n";
    names.push_back(str);
    b = clock();
    TIME += b-a;
}
fout.close();
fin.close();
std::cout<<"TIME = "<<TIME<<std::endl;
return 0;
}
