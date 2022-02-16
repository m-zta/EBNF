#include <iostream>
#include <istream>
#include <sstream>
#include "ebnf_helpers.cpp"

// project completed

// PLZ = '(' B ')' '-' number
// B = G { G }
// number = digit { digit }
// digit = '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

bool digit(std::istream& is) {
    char ch {lookahead(is)};
    if('0' <= ch && ch <= '9') {
        return consume(is, ch);
    } else {
        return false;
    }
}

bool number(std::istream& is) {
    for(unsigned int i {0}; i < 4; ++i) {
        if(!digit(is)) return false;
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
    if(!G(is)) return false;
    while(find(lookahead(is))) {
        if(!G(is)) return false;
    }
    return true;
}

bool plz(std::istream& is) {
    return consume(is, '(') && B(is) && consume(is, ')')
        && consume(is, '-') && number(is);
}

int main() {
    std::string s{};
    std::getline(std::cin, s);
    std::istringstream iss {s};

    if(plz(iss)) {
        std::cout << "valid!\n";
    } else {
        std::cout << "invalid!\n";
    }
    return 0;
}

// project completed