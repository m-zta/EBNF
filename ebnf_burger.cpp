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
    if (!((consume(is, 'X') || consume(is, 'Y')) && is_cheese(is))) {
        return false;
    }
    
    while (consume(is, 'X') || consume(is, 'Y') || is_cheese(is));

    return true;
}

// Onions = 'O' 'O' 'O'
bool is_onions(std::istream& is) {
    unsigned int i {0};
    for (;consume(is, 'O'); ++i);
    return !(i % 3);
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

// manual test mode [1]
void manual_test(std::istream& is) {
    //this is manual test mode
    std::cout << "Enter string to check:\n";

    if(is_burger(std::cin)) {
        std::cout << "valid\n";
    } else {
        std::cout << "invalid\n";
    }
}

// auto test mode [2]
void auto_test(std::istream& is) {
    // initialize a testcontainer with examples
    std::vector<std::string> testcon {
        "BSOOO(XC)KB", // valid 1
        "BSOOO(XCYCCXC)KB", // valid
        "BSOOOOOO(XCYXY)MB", // valid
        "BSOOO(YC)MB", // valid
        "BSOOO(XCYXC)TB", // valid
        "BSOOOOOOOOO(YCXXCCX)KB", // valid 6
        "BSOO(XCKB ", // invalid 1
        "BSOO(XC)MB", // invalid
        "BSOOO(YXC)KB", // invalid
        "BSOOO(CYCC)MB", // invalid
        "BOOOOOOOO(XC)MB", // invalid
        "BOOO(XCXXXCC)TKB", // invalid
        "BOOOYCYYY)KB", // invalid
        "BBOOO(XC)TB", // invalid
        "BOOO(XCCCCY)KBBB" // invalid 9
    };

    // run auto test
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
    std::cout << "\nTOTAL RESULT:";
    std::cout << "\ntests passed: " << len - failed << '/' << len;
    std::cout << "\npercentage: " << rate << "%\n";
    std::cout << "-------------------\n\n";
}

int main() {
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

