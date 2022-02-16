#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <sstream>
#include "ebnf_helpers.h"

// project completed

// polynomial = monomial {op monomial}
// op = "+" | "-"
// monomial = number ["x^" number]
// number = digit {digit}
// digit = "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "0"

// digit = "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
bool digit(std::istream& is) {
    // if(!input_available(is)) return false;
    // return consume(is, '1') || consume(is, '2') || consume(is, '3')
    //     || consume(is, '4') || consume(is, '5') || consume(is, '6')
    //     || consume(is, '7') || consume(is, '8') || consume(is, '9')
    //     || consume(is, '0');

    char ch {lookahead(is)};
    if('0' <= ch && ch <= '9') {
        return consume(is, ch);
    } else {
        return false;
    }
}

// number = digit {"0" | digit}
bool number(std::istream& is) {
    is >> std::skipws;
    if(!digit(is)) return false;
    while(48 <= lookahead(is) && lookahead(is) <= 57) {
        if(!digit(is)) return false;
    }
    return true;
}

// op = "+" | "-"
bool op(std::istream& is) {
    return consume(is, '+') || consume(is, '-');
}

// monomial = number ["x^" number]
bool monomial(std::istream& is) {
    if(!number(is)) return false;
    if(lookahead(is) == 'x') {
        if(!consume(is, 'x') || !consume(is, '^') || !number(is)) return false;
    }
    return true;
}

// polynomial = monomial {op monomial}
bool polynomial(std::istream& is) {
    if(!monomial(is)) return false;
    while(lookahead(is) == '+' || lookahead(is) == '-') {
        if(!op(is) || !monomial(is)) return false;
    }
    return true;
}

bool test_digit(std::istream& is) {
    bool var {digit(is)};
    (var) ? std::cout << "is a digit.\n" : std::cout << "is NOT a digit...\n";
    return var;
}

bool test_number(std::istream& is) {
    bool var {number(is)};
    (var) ? std::cout << "is a number.\n" : std::cout << "is NOT a number...\n";
    return var;
}

bool test_monomial(std::istream& is) {
    bool var {monomial(is)};
    (var) ? std::cout << "is a monomial.\n" : std::cout << "is NOT a monomial...\n";
    return var;
}

bool test_polynomial(std::istream& is) {
    bool var {polynomial(is)};
    (var) ? std::cout << "is a polynomial.\n" : std::cout << "is NOT a polynomial...\n";
    return var;
}

void auto_test() {
    std::cout << std::endl;
    // valid examples:
    std::vector<std::string> val {"3", "8x^1", "5x^8 - 2x^7 + 3", "4 + 8x^2 - 3", "9x^24 - 2 + 42"};
    // invalid examples:
    std::vector<std::string> inval {"3 + ", "6x", "8x^1 - ", "+ 3x^3 - 2x^9", "4x^22 - 7x^ + 3"};

    // test all the valid inputs
    for(unsigned int i {0}; i < val.size(); ++i) {
        std::istringstream iss {val.at(i)};
        std::cout << i + 1 <<  ". input: " << val.at(i) << "\nexpected output: valid!\nactual output: ";
        if(polynomial(iss)) {
            std::cout << "valid!\n\n";
        } else {
            std::cout << "invalid!\n\n";
        }
    }

    // test all the invalid inputs
    for(unsigned int i {0}; i < inval.size(); ++i) {
        std::istringstream iss {inval.at(i)};
        std::cout << i + 6 << ". input: " << inval.at(i) << "\nexpected output: invalid!\nactual output: ";
        if(polynomial(iss)) {
            std::cout << "valid!\n\n";
        } else {
            std::cout << "invalid!\n\n";
        }
    }
}

int main() {
    // intersting phenomenon: (might be wrong)
    // if implemented directly with a std::cin inputstream, a bug occurs which
    // demands inputs as long as a non-valid input is given, which is not what I want.
    // if implemented with getline() and a std::istringstream (passing the input-stream
    // via a string-stream) it works perfectly well...
    
    std::string s {};
    std::getline(std::cin, s);
    std::istringstream iss {s};
    
    char mode {' '}; 
    iss >> mode;

    switch(mode) {
        case '0': auto_test(); break;
        case '1': test_digit(iss); break;
        case '2': test_number(iss); break;
        case '3': test_monomial(iss); break;
        case '4': test_polynomial(iss); break;
        default:
            std::cout << "Please enter a valid test mode.\n";
            break;
    }
}

// polynomial = monomial {op monomial}
// op = "+" | "-"
// monomial = number ["x^" number]
// number = digit {"0" | digit}
// digit = "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

// project completed