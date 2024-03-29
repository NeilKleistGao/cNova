#include <iostream>
#include <cnova.h>
#include <ROOT_PATH.h>

static const std::string rootPath(ROOT_PATH);
int main() {
    auto interpreter = new cnova::CNovaInterpreter{rootPath + "/data/script/rotate_matrix.nova"};
    interpreter->execute(3.1415926535 / 4);
    auto mtr = interpreter->getArrayResult(0);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << mtr[i * 2 + j].data.float_data << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
