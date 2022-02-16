#include <iostream>
#include <istream>
#include <string>
#include <sstream>
#include "ebnf_helpers.cpp"

// this task is a crap to implement...
// Here's why:
// The function is_B(...) causes trouble. Because of the fact that the function is
// equivalent to check whether a series of "ab" is ahead in the stream. After the
// first "b" "c" we do only want to extract further "b"s if there's a "c" right
// behind it. The problem is, that our lookahead-function does only look ahead on
// the very next character, not on the character behind it. Since at this stage of
// my c++-knowledge there's no way to gain any information about the character
// behind the next character, this task has become impossible to finish for me, so
// I'm gonna have to postpone this to some other day...


// S = A "b" | "a" B    
// A = "a" | "a" A
// B = "b" "c" | B "b"  = { "b" "c" } "b"
// bcb bcbcbcbcbcb

bool is_B(std::istream& is) {
    // immediately exit if first characte is not 'b'
    // if(!(consume(is, 'b') && consume(is, 'c') && lookahead(is) != 'b')) return false;
    // return is_B
}

bool is_A(std::istream& is) {
    return consume(is, 'a') && lookahead(is) != 'a'
        || is_A(is);
}

bool is_S(std::istream& is) {
    // immediately exit if first character is not 'a'
    if(lookahead(is) != 'a') return false;

    // initialize count variable
    unsigned int count {0};

    // read in and count every 'a' there's in the stream
    while(consume(is, 'a')) {
        ++count;
    }

    // if there's more than 1 'a' then only A is possible
    if(count == 1) {
        return is_B(is);
    } else {
        return is_A(is);
    }
    return false;
}

int main() {
    std::string s {};
    std::getline(std::cin, s);
    std::istringstream iss {s};

    if(is_S(iss)) {
        std::cout << "valid!\n";
    } else {
        std::cout << "invalid!\n";
    }
    return 0;
}