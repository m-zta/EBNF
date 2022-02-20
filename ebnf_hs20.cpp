#include <iostream>
#include <istream>
#include <sstream>
#include "ebnf_helpers.cpp"

// project completed

// Each of the following functions implements a check of the 
// EBNF production rule given in the preceding comment.
// A function returns true if at the given instream a pattern
// according to the EBNF rule is present, otherwise it returns false.
// Functions expecting a single character only consume matching 
// characters.

//   Night = Princess On Stack On Peas.
//   Stack = Mattress (Frogs | Stack) Mattress.
//   Peas = Pea {Pea} On Ground.
//   Frogs = Frog Frog {Frog Frog}.
//   Princess = 'X'.
//   On = '/'.
//   Mattress = 'M'.
//   Frog = 'F'.
//   Pea = 'P'.
//   Ground = 'G'.

// Ground = 'G'.
bool Ground(std::istream& is) {
    return consume(is, 'G');
}

// Pea = 'P'.
bool Pea(std::istream& is) {
    return consume(is, 'P');
}

// Frog = 'F'.
bool Frog(std::istream& is) {
    return consume(is, 'F');
}

// Mattress = 'M'.
bool Mattress(std::istream& is) {
    return consume(is, 'M');
}

// On = '/'.
bool On(std::istream& is) {
    return consume(is, '/');
}

// Princess = 'X'.
bool Princess(std::istream& is) {
    return consume(is, 'X');
}

// Frogs = Frog Frog {Frog Frog};
bool Frogs(std::istream& is) {
    if (!(Frog(is) && Frog(is))) return false;
    while (lookahead(is) == 'F') {
        if (!(Frog(is) && Frog(is))) return false;
    }
    return true;
}

// Stack = Mattress ( Frogs | Stack ) Mattress.
bool Stack(std::istream& is) {
    if (!Mattress(is)) return false;
    if (lookahead(is) == 'F') {
        if (!Frogs(is)) return false;
    } else if (lookahead(is) == 'M') {
        if (!Stack(is)) return false;
    } else {
        return false;
    }
    if (!Mattress(is)) return false;
    return true;
}

// Peas = Pea { Pea } On Ground.
bool Peas(std::istream& is) {
    if (!Pea(is)) return false;
    while (lookahead(is) == 'P') {
        if (!Pea(is)) return false;
    }
    if (!(On(is) && Ground(is))) return false;
    return true;
}

// Night = Princess On Pile On Peas.
bool Night(std::istream& is) {
    return Princess(is) & On(is) & Stack(is) & On(is) & Peas(is);
}

int main() {
    std::string s{};
    std::getline(std::cin, s);
    std::istringstream iss {s};

    if (Night(iss)) {
        std::cout << "valid!\n";
    } else {
        std::cout << "invalid!\n";
    }
    return 0;
}

// project completed