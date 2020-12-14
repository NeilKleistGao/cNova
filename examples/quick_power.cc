#include <iostream>
#include "../cnova.h"

int main() {
    auto interpreter = new cnova::CNovaInterpreter{"../script/quick_power.nova"};
    interpreter->execute<cnova::nova_int, cnova::nova_int, cnova::nova_int>(2, 10, 9);
//    std::cout << "result: " << interpreter->getFloatResult(0) << std::endl;
    return 0;
}