#include <iostream>
#include <cnova.h>
#include <ROOT_PATH.h>

static const std::string rootPath(ROOT_PATH);

int main() {
    auto interpreter = new cnova::CNovaInterpreter{rootPath + "/data/script/quick_power.nova"};
    interpreter->execute<cnova::nova_int, cnova::nova_int, cnova::nova_int>(2, 10, 9);
    std::cout << "result: " << interpreter->getIntResult(0) << std::endl;
    std::cout << "length of result: " << interpreter->getIntResult(1) << std::endl;

    return 0;
}