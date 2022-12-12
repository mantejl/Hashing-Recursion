#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>


typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        int total, intialVar;
        int size = k.size();
        std::string strTemp = k;
        unsigned long long w[5];

        if(size == 6){
            for(size_t i = 0; i < 6; i++){
                intialVar = letterDigitToNumber(k[i]);
                total = (total*36) + intialVar;
            }
            total = total * rValues[4];
            return total;

        }else if(size < 6){
            size_t blank_size = 1;
            for(size_t i = 0; i < blank_size; i++){
                strTemp = strTemp+'!'; 
            }
            for(size_t i = 0; i < 6; i++){
                if(strTemp[i] != '!'){
                    intialVar = letterDigitToNumber(k[i]);
                }else{
                    break;
                }
                total = (total*36) + intialVar;
            }
            total = total * rValues[4];
            return total;
        }else{
            unsigned long long final_total = 0;
            size_t blank_size = 30 - size;
            for(size_t i = 0; i < blank_size; i++){
                strTemp = '!' + strTemp ; 
            }
            std::cout<<strTemp<<std::endl;
            for(size_t i = 0; i < 5; i++){
                 for(size_t j = 6*i; j < 6*(i+1); j++){
                    if(strTemp[j] != '!'){
                        intialVar = letterDigitToNumber(strTemp[j]);
                    }else{
                        intialVar = 0;
                    }
                    total = (total*36) + intialVar;
                }
                w[i] = total;
                total = 0;
            }
            for(size_t i = 0; i < 5; i++){
                final_total = final_total + ((w[i])*(rValues[i]));
            }
            return final_total;
        }
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it 
        char adj_letter = tolower(letter);
        if (adj_letter >= 'a' && adj_letter <= 'z'){
            return adj_letter = adj_letter - 'a';
        }else if(adj_letter >= '0' && adj_letter <= '9'){
            return adj_letter - '0' + 26;
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif