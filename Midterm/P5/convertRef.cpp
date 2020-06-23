#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;

struct name
{
    string surname;
    string firstname;
};

int main(int argc, char const *argv[])
{
    ifstream ifile;
    ifile.open("biblio.txt");
    string line;
    int i = 0;
    int name_num = 0;
    name Name[100];
    string title;
    string year;
    string conference;
   getline(ifile,line);
        while(line[i] != ';'){
            while(line[i] != ','){
                Name[name_num].surname = Name[name_num].surname + line[i];
                i++;
            }
            i+=2;
            while(line[i] != ' '){
                Name[name_num].firstname = Name[name_num].firstname + line[i];
                i++;
            }
            name_num++;
            i+=5;   
        }

        i++;
        while(line[i] != '('){
            title = title + line[i];
            i++;
        }
        i++;
        while(line[i] != ')'){
            year = year + line[i];
            i++;
        }
        i+=3;
        while(!line[i]){
            conference = conference + line[i];
        }


    
    return 0;
}
