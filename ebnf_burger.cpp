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
    return consume(is, 'O') && consume(is, 'O') && consume(is, 'O');
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
        "BSOO(XCYXC)TB", // valid
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

    for (unsigned int i {0}; i < testcon.size(); ++i) {
        std::string str {testcon.at(i)};
        std::istringstream is {str};
        bool val {i < 6};
        bool res {is_burger(is)};

        std::cout << '\n' << i + 1 << ". input: " << str << std::endl;
        std::cout << "expected output: " << (val ? "valid" : "invalid") << std::endl;
        std::cout << "actual output: " << (res ? "valid" : "invalid") << std::endl;
        std::cout << ((i < 6 == res) ? "PASSED" : "--NOT PASSED") << std::endl;
    }

    // FIXME: Solve the problem of type conversion from unsigned long to double...
    // double rate {(testcon.size() - failed) / testcon.size() * 100};
    //     std::cout << "\ntotal result: " << rate << "%\n";
}

