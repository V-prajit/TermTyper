#include <iostream>
#include <vector>
#include "getFile.h"
#include <chrono>
#include <ncurses.h>
#include <csignal>
#include <cstdlib>

void signalHandler(int signum) {
    endwin(); 
    std::cout << "\nProgram terminated by user.\n";
    exit(signum);
}

int main(void) {

    signal(SIGINT, signalHandler);

    while (true) {
        // ncurses config
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);
        start_color();

        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);

        std::string displayText;
        try {
            auto words = get_word_list(); // Generate a new set of random words
            for (const auto& word : words) {
                displayText.append(word + " ");
            }
            if (!displayText.empty()) {
                displayText.pop_back(); // Remove the trailing space
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }

        clear();
        mvprintw(0, 0, "Here are the words you need to type. Have fun!");
        mvprintw(2, 0, "%s", displayText.c_str());
        mvprintw(4, 0, "Start typing below:");
        refresh();

        auto start_time = std::chrono::high_resolution_clock::now();
        std::string userInput;

        size_t inputPos = 0;
        int ch;

        while (inputPos < displayText.size()) {
            ch = getch();

            if (ch == '\n') {
                break;
            }

            if (ch == KEY_BACKSPACE || ch == 127) {
                if (!userInput.empty()) {
                    userInput.pop_back();
                    inputPos--;
                }
            } else if (isprint(ch)) {
                userInput.push_back(static_cast<char>(ch));
                inputPos++;
            }

            clear();
            mvprintw(0, 0, "Here are the words you need to type. Have fun!");
            mvprintw(2, 0, "%s", displayText.c_str());
            mvprintw(4, 0, "Start typing below:");

            for (size_t i = 0; i < displayText.size(); ++i) {
                if (i < userInput.size()) {
                    if (userInput[i] == displayText[i]) {
                        attron(COLOR_PAIR(1)); // Correct input
                    } else {
                        attron(COLOR_PAIR(2)); // Incorrect input
                    }
                    mvprintw(6, i, "%c", userInput[i]);
                    attroff(COLOR_PAIR(1));
                    attroff(COLOR_PAIR(2));
                } else {
                    attron(COLOR_PAIR(3)); // Default text color
                    mvprintw(6, i, "%c", displayText[i]);
                    attroff(COLOR_PAIR(3));
                }
            }
            refresh();
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;

        double time_in_minutes = elapsed_time.count() / 60.0;
        size_t word_count = std::count(displayText.begin(), displayText.end(), ' ') + 1;
        double wpm = word_count / time_in_minutes;

        if (userInput == displayText) {
            mvprintw(8, 0, "Success! You typed at a speed of %d words per minute (WPM).", static_cast<int>(wpm));
            mvprintw(10, 0, "Press any key to start a new test, or Ctrl+C to exit.");
        } else {
            mvprintw(8, 0, "The strings do not match. Better luck next time!");
            mvprintw(10, 0, "Press any key to start a new test, or Ctrl+C to exit.");
        }

        refresh();
        getch();
        clear();
        endwin();
    }

    return 0;
}
