#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <string>
#include "ebnf_helpers.cpp"

// project completed

// PLZ = '(' B ')' '-' number
// B = G { G }
// G = 'A' | 'K' | 'W' | 'Z'
// number = digit { digit }
// digit = '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

bool digit(std::istream& is) {
    char ch {lookahead(is)};
    
    if ('0' <= ch && ch <= '9') {
        return consume(is, ch);
    } else {
        return false;
    }
}

bool number(std::istream& is) {
    for (unsigned int i {0}; i < 4; ++i) {
        if (!digit(is)) return false;
    }

    if (lookahead(is)) {
        return false;
    }

    return true;
}

bool G(std::istream& is) {
    return consume(is, 'A') || consume(is, 'K')
        || consume(is, 'W') || consume(is, 'Z');
}

bool find(const char& c) {
    switch(c) {
        case 'A':
        case 'K':
        case 'W':
        case 'Z': return true;
        default: return false;
    }

    return false;
}

bool B(std::istream& is) {
    if (!G(is)) return false;
    while (find(lookahead(is))) {
        if (!G(is)) return false;
    }
    
    return true;
}

bool is_plz(std::istream& is) {
    return consume(is, '(') && B(is) && consume(is, ')')
        && consume(is, '-') && number(is);
}

void manual_test(std::istream& is) {
    //this is manual test mode
    std::cout << "Enter string to check:\n";

    if(is_plz(std::cin)) {
        std::cout << "valid\n";
    } else {
        std::cout << "invalid\n";
    }
}

void auto_test(std::istream& is) {
    // initialize a container with examples
    std::vector<std::string> testcon {
        "(WZAK)-1323", // valid
        "(KAZWA)-2342", // valid
        "(KW)-2621", // valid
        "(A)-9284", // valid
        "(ZKZK)-0000", // valid
        "(WZ)-1294", // valid
        "ZKWK)-1349", // invalid
        "(AAKWKZ-7242", // invalid
        "(CWK)-2138", // invalid
        "(KWKAR9-2913", // invalid
        "(ZKWA)--1983", // invalid
        "(AKWA)-139284", // invlaid
        "(WKAW)-53", // invalid
        "(KWAWWKAZZWA)-13K9" // invalid
    };

    // run auto test
    std::cout << "\nAUTOTEST RUN:\n";
    unsigned int failed {0};
    unsigned long len {testcon.size()};

    for (unsigned int i {0}; i < len; ++i) {
        std::string str {testcon.at(i)};
        std::istringstream is {str};
        bool val {i < 6};
        bool res {is_plz(is)};

        std::cout << '\n' << i + 1 << ". input: " << str << std::endl;
        std::cout << "expected output: " << (val ? "valid" : "invalid") << std::endl;
        std::cout << "actual output: " << (res ? "valid" : "invalid") << std::endl;
        if (i < 6 == res) {
            std::cout << "PASSED" << std::endl;
        } else {
            std::cout << "--NOT PASSED" << std::endl;
            ++failed;
        }
    }

    // print the percentage of correct outputs
    unsigned long rate {(len - failed) * 100 / len};
    std::cout << "\nTOTAL RESULT:";
    std::cout << "\ntests passed: " << len - failed << '/' << len;
    std::cout << "\npercentage: " << rate << "%\n";
    std::cout << "-------------------\n\n";
}

int main() {
    // std::string s{};
    // std::getline(std::cin, s);
    // std::istringstream iss {s};

    // if (plz(iss)) {
    //     std::cout << "valid!\n";
    // } else {
    //     std::cout << "invalid!\n";
    // }
    // return 0;

    std::cout << "Choose mode:\n";
    std::cout << "[1] - manual test" << std::endl;
    std::cout << "[2] - auto test" << std::endl;
    std::cout << "chosen mode: ";
    unsigned int mode {0};
    std::cin >> mode;

    if (mode == 1) {
        manual_test(std::cin);
    } else if (mode == 2) {
        auto_test(std::cin);
    }

    return 0;
}

// project completed