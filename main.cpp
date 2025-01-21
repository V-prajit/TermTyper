#include <iostream>
#include <vector>
#include "getFile.h"



int main(void) {
    std::cout << "Here are the words that you have to type. Have fun!" << std::endl << std::endl;
    std::string displayText;

    try{
        auto words = get_word_list();
        for (const auto& word : words){
            displayText.append(word + " ");
        }  
        if (!displayText.empty()){
            displayText.pop_back();
        }
        std::cout << displayText<< std::endl;
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
        return -1;
    }
    
    std::string inputText;
    std::getline(std::cin, inputText);

    auto displayit = displayText.begin();
    auto inputit = inputText.begin();

    while (displayit != displayText.end() && inputit != inputText.end()){
        if (*displayit != *inputit){
            throw std::runtime_error("The strings do not match.");
        }
        ++displayit;
        ++inputit;
    }

    if (displayit != displayText.end() || inputit != inputText.end()) {
        throw std::runtime_error("The strings do not match in length.");
    }
    
    std::cout << "Success! The strings match." << std::endl;

    return 0;
}

