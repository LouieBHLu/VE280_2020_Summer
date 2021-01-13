#include "dlist.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class LRUCache{
private:
    int mem_size; // size of memory
    int *memory;
    struct block{
        int address; // its address in memory
        int data;
    };

    Dlist<block> cache;
    int cur_cache_size; // current length of `cache`
    int max_cache_size; // maximum length of `cache`

    static bool compare(const block *a, const block *b){
        if(a->address == b->address) return true;
        else return false;
    }
    // EFFECTS: returns true if two blocks have the same address

public:
    LRUCache(int cache_size, int memory_size){
        cur_cache_size = 0;
        max_cache_size = cache_size;
        mem_size = memory_size;
        memory = new int[mem_size];
        for(int i = 0; i < mem_size; i++) memory[i] = 0;
    } // constructor
    // Initialize `cur_cache_size`, `max_cache_size`, `memory`
    // Initialize all elements in `memory` to 0

    ~LRUCache(){
        delete[] memory;
        cache.~Dlist();
    } // destructor

    int read(int address){
        if(address >= 0 && address < mem_size){
            block* ref = new block;
            ref->address = address;
            block* itr = cache.remove(compare,ref);
            if(itr){
                delete ref;
                cache.insertFront(itr);
                return itr->data;
            } 
            else{
                if(cur_cache_size == max_cache_size){
                    block* last = cache.removeBack();
                    memory[last->address] = last->data;
                    delete last;
                    ref->data = memory[address];
                    cache.insertFront(ref);
                    return ref->data;
                }
                else if(cur_cache_size < max_cache_size){
                    cur_cache_size++;
                    ref->data = memory[address];
                    cache.insertFront(ref);
                    return ref->data;
                }
            }
            
        }
        else{
            cout << "ERROR: Address out of bound" << endl;
            return -1;
        }
        return 0;
    }
    // EFFECTS: returns data corresponding to address,
    // 0 <= address < mem_size;
    // if address is out of bound, throws an exception
    //
    // if hit,
    // removes this block and insert it to the front;
    // returns `data`;
    // if miss,
    // if `cur_cache_size` equals to `max_cache_size`,
    // removes the last (least recently used) block
    // in the `cache`;
    // writes data in the last block
    // to the corresponding address in `memory`;
    // if `cur_cache_size` < `max_cache_size`,
    // increment `cur_cache_size` by 1;
    // reads `data` of `address` from `memory`,
    // inserts the block with `address` and `data`
    // to the front of `cache`;
    // returns `data`

    void write(int address, int data){
        if(address >= 0 && address < mem_size){
            //memory[address] = data;
            block* ref = new block;
            ref->address = address;
            block* itr = cache.remove(compare,ref);
            if(itr){
                delete ref;
                itr->data = data;
                cache.insertFront(itr);
            }
            else{
                if(cur_cache_size == max_cache_size){
                    block* last = cache.removeBack();
                    memory[last->address] = last->data;
                    delete last;
                    ref->data = data;
                    cache.insertFront(ref);
                    //memory[address] = data;
                }
                else if(cur_cache_size < max_cache_size){
                    cur_cache_size++;
                    ref->data = data;
                    cache.insertFront(ref);
                }
            }
        }
        else{
            cout << "ERROR: Address out of bound" << endl;
            return;
        }

    }
    // EFFECTS: writes data to address, 0 <= address < mem_size
    // if address is out of bound, throws an exception
    //
    // if hit,
    // removes this block from list,
    // writes `data` to this block,
    // and inserts this block to the front;
    // if miss,
    // if `cur_cache_size` equals to `max_cache_size`,
    // removes the last (least recently used) block
    // in the `cache`;
    // writes data in the last block
    // to the corresponding address in `memory`;
    // if `cur_cache_size` < `max_cache_size`,
    // increment `cur_cache_size` by 1;
    // inserts the block with `address` and `data`
    // to the front of `cache`

    void printCache(){
        Dlist<block> temp(this->cache);
        for(int i = 0; i < cur_cache_size; i++){
            block* pointer = temp.removeFront();
            cout << pointer->address << " " << pointer->data << endl;
            delete pointer;
        }
        // for(int i = 0; i < cur_cache_size; i++){
        //     block* pointer = cache.removeFront();
        //     cout << pointer->address << " " << pointer->data << endl;
        //     cache.insertFront(pointer);
        // }
    }
    // EFFECTS: prints the cache in given format

    void printMem(){
        for(int i = 0; i < mem_size - 1; i++){
            cout << memory[i] << " ";
        }
        cout << memory[mem_size - 1] << endl;
    }
    // EFFECTS: prints the memory in given format
};

int main(int argc, char const *argv[]){
    string line;
    int cache_size, memo_size = 0;
    cin >> cache_size;
    cin >> memo_size;
    getchar();
    LRUCache lru(cache_size,memo_size);
    
    while(1){
        getline(cin,line);
        string command;
        int num_arg = 1;
        int i = 0;
        if(line.size() == 0) continue;
        while(line[i]){
            if(line[i] == ' ') num_arg++;
            i++;
        }
        i = 0;
        while(line[i] != ' ' && line[i]){
            command += line[i];
            i++;
        }
        if(line[i]) i++;
        
        if(command == "READ"){
            string read_address;
            if(num_arg == 1){
                cout << "ERROR: Not enough operands" << endl;
                continue;
            }
            if(num_arg > 2){
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            //read the address
            while(line[i]){
                read_address += line[i];
                i++;
            }
            int address_read = atoi(read_address.c_str());
            double num = lru.read(address_read);
            if(num != -1) cout << num << endl;
        }
        else if(command == "WRITE"){
            string write_address;
            string write_data;
            if(num_arg < 3){
                cout << "ERROR: Not enough operands" << endl;
                continue;
            }
            if(num_arg > 3){
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            //read the address
            while(line[i] != ' '){
                write_address += line[i];
                i++;
            }
            i++;
            //read the data
            while(line[i]){
                write_data += line[i];
                i++;
            }
            int address_write = atoi(write_address.c_str());
            int data_write = atoi(write_data.c_str());
            lru.write(address_write,data_write);
        }
        else if(command == "PRINTCACHE"){
            if(num_arg > 1){
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            lru.printCache();
        }
        else if(command == "PRINTMEM"){
            if(num_arg > 1){
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            lru.printMem();
        }
        else if(command == "EXIT"){
            if(num_arg > 1){
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            break;
        }
        else{
            cout << "ERROR: Unknown instruction" << endl;
            continue;
        }
    }
    return 0;
}
