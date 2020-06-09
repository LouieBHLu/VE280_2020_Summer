#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

struct apple
{
    string name;
    double price;
    double weight;
} Apple;

int main(int argc, char const *argv[])
{
    string filename = argv[1];
    //string filename = "price_list.txt";
    ifstream iFile;
    iFile.open(filename);
    string line;
    int kinds = 0;
    while(getline(iFile, line)){
        kinds++;
    }
    iFile.close();
    apple Apple[kinds];
    kinds = 0;
    iFile.open(filename);
    while(getline(iFile, line)){
        int order = 0;
        string total_price;
        string total_weight;
        while(line[order] != ' '){
            Apple[kinds].name = Apple[kinds].name + line[order];
            order++;
        }
        order++;
        while(line[order] != ' '){
            total_price = total_price +line[order];
            order++;
        }
        Apple[kinds].price = atof(total_price.c_str());
        order++;
        while(line[order]){
            total_weight = total_weight +line[order];
            order++;
        }
        Apple[kinds].weight = atof(total_weight.c_str());
        kinds++;
    }
    iFile.close();

    for(int i = 0; i < kinds - 1; i++) {
        for(int j = 0; j < kinds - 1 - i; j++) {
            double average_1 = Apple[j].price/Apple[j].weight; 
            double average_2 = Apple[j+1].price/Apple[j+1].weight;
            if(average_1 > average_2) {
                // switch two price
                double temp_price = Apple[j+1].price;
                Apple[j+1].price = Apple[j].price;
                Apple[j].price = temp_price;
                //switch two weight
                double temp_weight = Apple[j+1].weight;
                Apple[j+1].weight = Apple[j].weight;
                Apple[j].weight = temp_weight;
                //switch two names
                string temp_name = Apple[j+1].name;
                Apple[j+1].name = Apple[j].name;
                Apple[j].name = temp_name;
            }
        }
    }
    cout << Apple[0].name;
    cout << fixed << setprecision(2) << " " << Apple[0].price << " " << Apple[0].weight << endl;
    return 0;
}
