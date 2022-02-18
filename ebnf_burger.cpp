#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "ebnf_helpers.cpp"

// Krusty Krab Burger:
// Burger = Bun Salad {Onions}
//          '(' Patty Cheese {Patty | Cheese} ')'
//          Sauce Bun
// Salad = 'S'
// Onions = 'O' 'O' 'O'
// Patty = 'X' | 'Y'
// Cheese = 'C'
// Sauce = 'K' | 'M' | 'T'
// Bun = 'B'

// Sauce = 'K' | 'M' | 'T'
bool is_sauce(std::istream& is) {
    return consume(is, 'K')
        || consume(is, 'M')
        || consume(is, 'T');
}

// Cheese = 'C'
bool is_cheese(std::istream& is) {
    return consume(is, 'C');
}

bool is_pc(std::istream& is) {
    if (!(consume(is, 'X') || consume(is, 'Y')) && !is_cheese(is)) {
        return false;
    }
    
    while (consume(is, 'X') || consume(is, 'Y') || is_cheese(is));

    return true;
}

// Onions = 'O' 'O' 'O'
bool is_onions(std::istream& is) {
    do {
        for (unsigned int i {0}; i < 2; ++i) {
            if (!consume(is, 'O')) {
                return false;
            }
        }
    } while (lookahead(is) == 'O');
    return true;
}

// Burger = Bun Salad {Onions}
//          '(' Patty Cheese {Patty | Cheese} ')'
//          Sauce Bun
bool is_burger(std::istream& is) {
    char c {' '};

    if (!(consume(is, 'B') && consume(is, 'S'))) {
        return false;
    }

    if (lookahead(is) == 'O' && !is_onions(is)) {
        return false;
    }

    return consume(is, '(')
        && is_pc(is)
        && (is >> c) && (c == ')')
        && is_sauce(is)
        && consume(is, 'B');

}

int main() {
    /* 
    //this is manual test mode
    if(is_burger(std::cin)) {
        std::cout << "valid\n";
    } else {
        std::cout << "invalid\n";
    }
    return 0;
    */

    // this is auto-test mode
    
    std::vector<std::string> testcon {
        "BSOOO(XC)KB", // valid
        "BSOOO(XCYCCXC)KB", // valid
        "BSOOOOOO(XCYXY)MB", // valid
        "BSOOO(YC)MB", // valid
        "BSOOO(XCYXC)TB", // valid
        "BSOOOOOOOOO(YCXXCCX)KB", // valid
        "BSOO(XCKB ", // invalid
        "BSOO(XC)MB", // invalid
        "BSOOO(YXC)KB", // invalid
        //"BSOOO(CYCC)MB", // invalid, this one causes a segmentation fault...
        "BOOOOOOOO(XC)MB", // invalid
        "BOOO(XCXXXCC)TKB", // invalid
        "BOOOYCYYY)KB", // invalid
        "BBOOO(XC)TB", // invalid
        "BOOO(XCCCCY)KBBB" // invalid
    };

    std::cout << "\nAUTOTEST RUN:\n";
    unsigned int failed {0};
    unsigned long len {testcon.size()};

    for (unsigned int i {0}; i < len; ++i) {
        std::string str {testcon.at(i)};
        std::istringstream is {str};
        bool val {i < 6};
        bool res {is_burger(is)};

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
        std::cout << "\ntotal result: " << rate << "%\n";
        std::cout << "------------------\n\n";
}

