#include <iostream>
#include <string>
#include "ebnf_helpers.cpp"

// Krusty Krab Burger:
// Burger = Bun Salad (Onions)
//          '(' Patty Cheese {Patty | Cheese} ')'
//          Sauce Bun
// Salad = 'S'
// Onions = Onion {Onions}
// Onion = 'O'
// Patty = 'X' | 'Y'
// Cheese = 'C'
// Sauce = 'K' | 'M' | 'T'
// Bun = 'B'

bool is_sauce(std::istream& is) {
    return consume(is, 'K')
        || consume(is, 'M')
        || consume(is, 'T');
}

bool is_cheese(std::istream& is) {
    return consume(is, 'C');
}

bool is_patty(std::istream& is) {
    return consume(is, 'X') || consume(is, 'Y');
}

bool is_pc(std::istream& is) {
    return (is_patty(is) && is_cheese(is)
            && lookahead(is) != 'X' && lookahead(is) != 'Y')
        || is_pc(is);
}

bool is_onions(std::istream& is) {
    if(lookahead(is) != 'O') return true;
    return consume(is, 'O') && is_onions(is);
}

bool is_burger(std::istream& is) {
    char c {' '};
    return consume(is, 'B')
        && consume(is, 'S')
        && is_onions(is)
        && consume(is, '(')
        && is_pc(is)
        && (is >> c) && (c == ')')
        && is_sauce(is)
        && consume(is, 'B');
}

int main() {
    if(is_burger(std::cin)) {
        std::cout << "valid\n";
    } else {
        std::cout << "invalid\n";
    }
    return 0;
}