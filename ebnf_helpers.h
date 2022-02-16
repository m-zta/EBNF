#include <istream>

bool input_available(std::istream& input);
char peek(std::istream& input);
char lookahead(std::istream& input);
bool consume(std::istream& input, char expected);