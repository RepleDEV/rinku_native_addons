#ifndef COMMON_H_
#define COMMON_H_

#include <string>

class Common {
    public:
        static std::string charToString(char* arr, int size) { 
            int i;
            std::string res = ""; 
            for (i = 0; i < size; i++) { 
                res = res + arr[i]; 
            } 
            return res; 
        } 
};

#endif
