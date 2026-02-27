#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

struct ZOO {
    char* name = nullptr;
    char* nick = nullptr;
    char* diet_type = nullptr;
    float diet_weight = 0;
    int age = 0;
    
    ~ZOO () {
        delete[] name;
        delete[] nick;
        delete[] diet_type;
    }
};


constexpr int zoo_size = 80;
constexpr int buffer_size = 512;

struct Solution {
    FILE* file;
    ZOO* pmi_pad;
    Solution() {
        file = fopen("13. ZOO.txt", "r");
            /* 
        pmi_pad = new ZOO[zoo_size];
        
        char buffer[buffer_size];
        while (fgets(buffer, buffer_size, file)) {
            // printf(const char *const Format, ...)
        }
        */
        
    }
    ~Solution(){
        fclose(file);
        delete[] pmi_pad;
    }
};

int main () {
    Solution();
}