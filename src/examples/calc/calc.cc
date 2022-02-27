#include <iostream>
#include <cnova.h>
#include <ROOT_PATH.h>

static const std::string rootPath(ROOT_PATH);

int main() {
    auto interpreter = new cnova::CNovaInterpreter{rootPath+"/data/script/calc.nova"};
    interpreter->execute();
    std::cout << "result: " << interpreter->getIntResult(0) << std::endl;

    return 0;
}