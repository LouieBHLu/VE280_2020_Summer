#include "binaryTree.h"
#include "huffmanTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
const int CHAR_NUM = 28;
const string null_string = "";

void frequency(char letter, int freq[]){
    switch (letter)
    {
    case 'a':
        freq[2]++;
        break;
    case 'b':
        freq[3]++;
        break;
    case 'c':
        freq[4]++;
        break;
    case 'd':
        freq[5]++;
        break;
    case 'e':
        freq[6]++;
        break;
    case 'f':
        freq[7]++;
        break;
    case 'g':
        freq[8]++;
        break;
    case 'h':
        freq[9]++;
        break;
    case 'i':
        freq[10]++;
        break;
    case 'j':
        freq[11]++;
        break;
    case 'k':
        freq[12]++;
        break;
    case 'l':
        freq[13]++;
        break;
    case 'm':
        freq[14]++;
        break;
    case 'n':
        freq[15]++;
        break;
    case 'o':
        freq[16]++;
        break;
    case 'p':
        freq[17]++;
        break;
    case 'q':
        freq[18]++;
        break;
    case 'r':
        freq[19]++;
        break;
    case 's':
        freq[20]++;
        break;
    case 't':
        freq[21]++;
        break;
    case 'u':
        freq[22]++;
        break;
    case 'v':
        freq[23]++;
        break;
    case 'w':
        freq[24]++;
        break;
    case 'x':
        freq[25]++;
        break;
    case 'y':
        freq[26]++;
        break;
    case 'z':
        freq[27]++;
        break;
    case ' ':
        freq[1]++;
        break;
    }
}

void two_smallest(int &min1, int &min2, int &pos1, int &pos2, Node *letters[], int &count){
    if(count < 3) return;
    for(int i = 2; i < count; i++){
        if(min1 != min2){
            if(letters[i]->getnum() < min1){
                min2 = min1;
                min1 = letters[i]->getnum();
                pos2 = pos1;
                pos1 = i;
            }
            else if(letters[i]->getnum() < min2){
                min2 = letters[i]->getnum();
                pos2 = i;
            }
            else if(letters[i]->getnum() == min1){
                string new_string = letters[i]->getstr();
                string old_string = letters[pos1]->getstr();
                if(new_string[0] < old_string[0]) pos1 = i;
            }
            else if(letters[i]->getnum() == min2){
                string new_string = letters[i]->getstr();
                string old_string = letters[pos2]->getstr();
                if(new_string[0] < old_string[0]) pos2 = i;
            }
        }
        else{
            if(letters[i]->getnum() < min1){
                min2 = min1;
                min1 = letters[i]->getnum();
                pos2 = pos1;
                pos1 = i;
            }
            else if(letters[i]->getnum() > min1) continue;
            else{
                string new_string = letters[i]->getstr();
                string old_string_1 = letters[pos1]->getstr();
                string old_string_2 = letters[pos2]->getstr();
                if(new_string[0] < old_string_1[0]){
                    if(old_string_1[0] < old_string_2[0]){
                        pos2 = pos1;
                        pos1 = i;
                    }
                    else{
                        pos1 = i;
                    }
                }
                else if(new_string[0] < old_string_2[0]){
                    if(old_string_2[0] < old_string_1[0]){
                        pos1 = i;
                    }
                    else{
                        pos2 = pos1;
                        pos1 = i;
                    }
                }
            }
        }
    }
    if(min1 == min2){
        string string_1 = letters[pos1]->getstr();
        string string_2 = letters[pos2]->getstr();
        if(string_2[0] < string_1[0]){
            int temp = pos1;
            pos1 = pos2;
            pos2 = temp;
        }
    }    
}

void remove_two(Node *letters[], int &pos1, int &pos2, int &count){
    int min_pos = min(pos1,pos2);
    int max_pos = max(pos1,pos2);
    for(int i = max_pos; i < count-1; i++){
        letters[i] = letters[i+1];
    }
    letters[count-1] = nullptr;
    count--;
    for(int i = min_pos; i < count-1; i++){
        letters[i] = letters[i+1];
    }
    letters[count-1] = nullptr;
    count--;
}

int main(int argc, char *argv[]) {
    //open an array to calculate the frequency of each character
    string letter[CHAR_NUM] = {"\n"," ","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    int freq[CHAR_NUM];
    //read the input arguments
    string filename;
    if(argc == 3) filename = argv[2];
    else if(argc == 2) filename = argv[1];
    //initialize frequency
    for(int i = 0; i < CHAR_NUM; i++) freq[i] = 0;
    //read the file and calculate the frequency
    string line;
    ifstream ifile;
    ifile.open(filename);
    while(getline(ifile,line)){
        for(int i = 0; i < line.size(); i++){
            frequency(line[i],freq);
        }
        freq[0]++;
    }
    //count the number of existing characters
    int count = 0;
    for(int i = 0; i < CHAR_NUM; i++){
        if(freq[i] > 0) count++;
    }
    ifile.close();
    //build a node for each character and add it to an array
    int stable_count = count+1;
    Node **letters = new Node *[stable_count];
    int allo_num = 0;
    for(int i = 0; i < CHAR_NUM; i++){
        if(freq[i] > 0){
            letters[allo_num] = new Node(letter[i],freq[i]);
            allo_num++;
        } 
    }
    //merge until there is only one root node
    while(count > 1){
        int pos1, pos2, min1, min2;
        if(letters[0]->getnum() > letters[1]->getnum()){
            min2 = letters[0]->getnum();
            pos2 = 0;
            min1 = letters[1]->getnum();
            pos1 = 1;
        }
        else if(letters[0]->getnum() < letters[1]->getnum()){
            min2 = letters[1]->getnum();
            pos2 = 1;
            min1 = letters[0]->getnum();
            pos1 = 0;
        }
        else{
            string string_1 = letters[0]->getstr();
            string string_2 = letters[1]->getstr();
            if(string_1[0] < string_2[0]){
                min2 = letters[1]->getnum();
                pos2 = 1;
                min1 = letters[0]->getnum();
                pos1 = 0;
            }
            else{
                min2 = letters[0]->getnum();
                pos2 = 0;
                min1 = letters[1]->getnum();
                pos1 = 1;
            }
        }
        //find the position of two node with the least freq
        two_smallest(min1,min2,pos1,pos2,letters,count);
        //merge into one node
        Node merge_node(null_string,0);
        letters[count] = merge_node.mergeNodes(letters[pos2],letters[pos1]);
        count++;
        //remove two smallest nodes
        remove_two(letters,pos1,pos2,count);
    }
    //construct a HuffmanTree with root node
    HuffmanTree tree(letters[0]);
    //output
    if(argc == 3) tree.printTree();
    else{
        ifile.open(filename);
        while(getline(ifile,line)){
            for(int i = 0; i < line.size(); i++){
                string each_char;
                each_char += line[i];
                cout << tree.findPath(each_char) << " ";
            }
            cout << tree.findPath("\n") << " ";
        }
        ifile.close();
    }
    delete[] letters;
    return 0;
}