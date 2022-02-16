#include <iostream>
#include <cassert>
#include "ebnf_helpers.h"

// PRE:  valid input stream input
// POST: returns true if further input is available 
//       otherwise false
bool input_available(std::istream& input) {
    input.peek(); // in case end of input has not yet been seen
    return input.good();
}

// PRE:  valid input stream input
// POST: the next character at the stream is returned (but not consumed)
//       if no input is available, 0 is returned
char peek(std::istream& input) {
    if(input_available(input)) {
        return input.peek();
    }
    else return 0;
}

// POST: leading whitespace characters are extracted
//       from input, and the first non-whitespace character is returned (but not consumed)
//       if an error or end of stream occurs, 0 is returned
char lookahead(std::istream& input) {
    input >> std::ws;         // skip whitespaces
    return peek(input);
}

// think about implementing a lookahead-function for strings of size n
// with the std::istream method: .read(pointer_to_array, size_of_array)

// PRE:  Valid input stream input, expected > 0
// POST: If ch matches the next lookahead then it is consumed and true is returned
//       otherwise no character is consumed and false is returned
bool consume(std::istream& input, char expected) {
    assert(expected > 0);
    if(lookahead(input) == expected) {
        input.get();
        assert(input.good());
        return true;
    }
    return false;
}
