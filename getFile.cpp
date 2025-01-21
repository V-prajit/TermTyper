#include "getFile.h"

std::vector<std::string> get_word_list(void){
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    std::vector<std::string> wordsList(10);
    std::string word;

    std::ifstream ifs ("random-words.txt", std::ifstream::in);
    if (!ifs.is_open()){
        throw std::runtime_error("Error: could not open the file.");
    }

    for(int i = 0; i < 10; ++i){
        int fileLineNumber = dist(rng);

        while (fileLineNumber > 0){
            if (std::getline(ifs, word)){
                --fileLineNumber;
            } else {
                ifs.clear();
                ifs.seekg(0, std::ios::beg);
            }
        }

        wordsList[i] = word;
    }

    return wordsList;
}
