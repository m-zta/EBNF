#include <iostream>
#include <istream>
#include <string>
#include <sstream>
#include "ebnf_helpers.cpp"

// this task is a crap to implement...
// Here's why:
// It's a similar problem as with the fs19-task. The function is_B(...)
// causes trouble. The task is equivalent to check whether after the
// first "c" there's a series of "ab" in the stream. However, we only
// want to extract the next "a" if there's a "b" right behind it. Again
// we come to the problem that our lookahead-function can only access
// the very next character and not what is behind it.
// Solution postponed...

// S := "b" "a" A "a" | "b" "a" B       = "ba" ( A "a" | B )
// A := "a" | "d" A "d"                 = "a" | "d" A "d"
// B := B "a" "b" | "c"                 = "c" | B "ab"
// cab cababab c cababababab

// valid examples:
// b a a a
// b a c a b a b
// invalid examples:
// b a d d d a d d d

// B := B "a" "b" | "c"     = "c" | B "ab"      = "c" { "ab" }
bool is_B(std::istream& is) {
    // return consume(is, 'c') // Attention!: The base case must be checked first, else infinite recursion
    //     || is_B(is) && consume(is, 'a') && consume(is, 'b');

    if(!consume(is, 'c')) {
        return false;
    }
    return true;
}

// A := "a" | "d" A "d"                 = "a" | "d" A "d"
bool is_A(std::istream& is) {
    // return consume(is, 'a')
    //     || consume(is, 'd') && is_A(is) && consume(is, 'c');
    
    if(consume(is, 'a')) {
        return true;
    } else if(consume(is, 'd')) {
        return is_A(is) && consume(is, 'd');
    } else return false;
}

// S := "b" "a" A "a" | "b" "a" B   = "ba" ( A "a" | B )
bool is_S(std::istream& is) {
    if(!(consume(is, 'b') && consume(is, 'a'))) return false;

    // return is_A(is) && consume(is, 'a')
    //     || is_B(is);

    if(lookahead(is) == 'a' || lookahead(is) == 'd') {
        return is_A(is) && consume(is, 'a');
    } else if(lookahead(is) == 'c') {
        return is_B(is);
    } else return false;
    
}

int main() {
    if(is_S(std::cin)) {
        std::cout << "valid\n";
    } else {
        std::cout << "invalid\n";
    }
    return 0;
}

// S := "b" "a" A "a" | "b" "a" B       = "ba" ( A "a" | B )
// A := "a" | "d" A "d"                 = "a" | "d" A "d"
// B := B "a" "b" | "c"                 = "c" | B "ab"