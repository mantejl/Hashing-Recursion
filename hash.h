#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash
{
    HASH_INDEX_T rValues[5]{983132572, 1468777056, 552714139, 984953261, 261934300};
    MyStringHash(bool debug = true)
    {
        if (false == debug)
        {
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string &k) const
    {
        // Add your code here
        unsigned long int total = 0;
        unsigned long int user = 0;
        unsigned long int intialVar, placeholder, checker;
        unsigned long int size = k.size();
        unsigned long int holder = 4;
        const int firstSize = k.size();
        unsigned long int words[5];
        std::string strTemp = k;

        if (size > 6)
        {
            long endResult = 0;
            unsigned long int tempSize = (size * -1) + 30;
            unsigned long int i = tempSize;
            while (i > 0)
            {
                strTemp = '!' + strTemp;
                --i;
            }
            std::cout << strTemp << std::endl;
            unsigned int placer = 0;
            while (placer < 5)
            {
                placeholder = 1;
                unsigned long int j = ((6 * placer * placeholder) * 1) + user;
                do
                {
                    switch (strTemp[j])
                    {
                    case '!':
                        intialVar = 0;
                        break;
                    }
                    if (strTemp[j] != '!')
                    {
                        intialVar = letterDigitToNumber(strTemp[j]);
                    }
                    total = (total * 36);
                    total += intialVar;
                    j = j + 1;

                } while (j < 6 * (placer + 1) * placeholder + user);
                words[placer] = total;
                total = 0;
                ++placer;
            }
            unsigned int tmp = 0;
            unsigned long long tmpValue;
            while (tmp < 5)
            {
                tmpValue = ((words[tmp]) * (rValues[tmp]));
                endResult += tmpValue;
                ++tmp;
            }
            return endResult;
        }

        switch (firstSize)
        {
        case 6:
            unsigned long long int i = 0;
            do
            {
                intialVar = letterDigitToNumber(k[i]);
                total = (total * 36) + intialVar;
                ++checker;
                ++i;
            } while (i <= 5);
            total *= rValues[holder];
            return total;
        }

        if (size < 6)
        {
            unsigned long int empty = 1 + user;
            unsigned int i = 0;
            do
            {
                strTemp += '!';
                ++i;
            } while (i < empty);
            unsigned long long checks = 0;
            while (checks < 6)
            {
                if (strTemp[checks] == '!')
                {
                    break;
                }
                if (strTemp[checks] != '!')
                {
                    intialVar = letterDigitToNumber(k[checks]);
                }
                total = ((total * 36)) + intialVar + user;
                checks = checks + 1;
            }
            checks = 1;
            total *= rValues[4];
            int tester = total * placeholder;
            return total;
        }
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        char changeLetter = tolower(letter);
        if (changeLetter >= '0')
        {
            if (changeLetter <= '9')
            {
                return changeLetter - '0' + 26;
            }
        }
        if (changeLetter <= 'z')
        {
            if (changeLetter >= 'a')
            {
                return changeLetter - 'a';
            }
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed); // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for (int i{0}; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif