#include <iostream>
#include "../cnova.h"

int main() {
    auto interpreter = new cnova::CNovaInterpreter{"../script/word_counter.nova"};
    std::string sentence = "I thought what I'd do was I'd pretend I was one of those deaf-mutes.";
    interpreter->execute(sentence.data());
    auto dic = interpreter->getDictionaryResult(0);
    for (const auto& p : dic) {
        std::cout << p.first << ": " << p.second.data.int_data << std::endl;
    }

    return 0;
}