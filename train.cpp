#include <iostream>
#include <istream>
#include "ebnf_helpers.cpp"

// project completed

// train = '[' ( open | compositions ) ')'
// open = loco cars
// loco = '*' | '*' loco
// cars = '-' | '(' cars ')'
// compositions = composition { compositions }
// composition = '<' open loco '>'

// forward declaration:
bool train(std::istream& is);
bool open(std::istream& is);
bool loco(std::istream& is);
bool cars(std::istream& is);
bool compositions(std::istream& is);
bool composition(std::istream& is);

bool composition(std::istream& is) {
    // immediately exit if first character is not '<'
    if(!consume(is, '<')) return false;

    if(!open(is) || !loco(is)) return false;

    if(!consume(is, '>')) return false;

    return true;
}

bool compositions(std::istream& is) {
    if(!composition(is)) return false;
    if(lookahead(is) == '<') return compositions(is);
    return true;
}

bool cars(std::istream& is) {
    if(lookahead(is) == '-') {
        return consume(is, '-');
    } else if(lookahead(is) == '(') {
        return consume(is, '(')
            && cars(is) && consume(is,')');
    }
    return false;
}

bool loco(std::istream& is) {
    if(!consume(is, '*')) return false;
    if(lookahead(is) == '*') return loco(is);
    return true;
}

bool open(std::istream& is) {
    return loco(is) && cars(is);
}

bool train(std::istream& is) {
    // exit with false if first char is not '['
    if(!(consume(is, '['))) return false;

    // var represents the middle part of train
    bool var {false};
    if(lookahead(is) == '*') {
        var = open(is);
    } else if(lookahead(is) == '<') {
        var = compositions(is);
    } else {
        return false;
    }
    
    // exit with false if first char is not ']'
    if(!(consume(is, ']'))) return false;

    return var;
}

int main() {
    if(train(std::cin)) {
        std::cout << "valid!\n";
    } else std::cout << "invalid!\n";

    return 0;
}

// train = '[' ( open | compositions ) ')'
// open = loco cars
// loco = '*' | '*' loco
// cars = '-' | '(' cars ')'
// compositions = composition { compositions }
// composition = '<' open loco '>'

// project completed