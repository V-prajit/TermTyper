#include <iostream>
#include <vector>
#include "getFile.h"
#include <chrono>

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
    
    std::cout << "Press Enter to Start..." << std::endl;
    std::cin.ignore();

    auto start_time = std::chrono::high_resolution_clock::now();

    std::string inputText;
    std::getline(std::cin, inputText);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;


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
    
    std::cout << "Success! The strings match. And you typed it in " << elapsed_time.count() << "seconds." << std::endl;

    return 0;
}


