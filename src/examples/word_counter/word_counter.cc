#include <iostream>
#include <cnova.h>
#include <ROOT_PATH.h>

static const std::string rootPath(ROOT_PATH);
int main() {
    auto interpreter = new cnova::CNovaInterpreter{rootPath + "/data/script/word_counter.nova"};
    std::string sentence = "I thought what I'd do was I'd pretend I was one of those deaf-mutes.";
    interpreter->execute(sentence.data());
    auto dic = interpreter->getDictionaryResult(0);
    for (const auto& p : dic) {
        std::cout << p.first << ": " << p.second.data.int_data << std::endl;
    }

    return 0;
}