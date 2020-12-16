#include <iostream>
#include "../cnova.h"

int main() {
    auto interpreter = new cnova::CNovaInterpreter{"../script/calc.nova"};
    interpreter->execute();
    std::cout << "result: " << interpreter->getIntResult(0) << std::endl;

    return 0;
}