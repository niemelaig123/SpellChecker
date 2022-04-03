//
// Created by nieme on 2022-03-09.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "SpellChecker.h"

void SpellChecker::check_spelling_in_file(std::string file_name) {
    std::ifstream file_reader(file_name);
    std::string line;
    try {
        while (file_reader) {
            // Get file contents, line by line
            getline(file_reader, line);
            std::stringstream line_in(line);
            int i = 0;
            // break line apart into array of individual strings for evaluation
            while (line_in.good() && i <  count_words_in_line(line)) {
                line_in >> this->file_contents[i];
                file_contents[i] = sanitize_word(file_contents[i]);
                i++;
            }
            int count = i;
            for (i = 0; i < count; i++) {
                // if
                if (!this->dict.search_for_word(file_contents[i])) {
                    misspelled_words.push_back(file_contents[i]);
                }
            }
        }
    } catch (std::ifstream::failure& e) {
        std::cerr << "Error while reading in file for spellchecking";
    } catch (...) {
        std::cerr << "General Error while checking spelling in file";
    }

}

// Src for this function: https://stackoverflow.com/questions/3672234/c-function-to-count-all-the-words-in-a-string
int SpellChecker::count_words_in_line(std::string const& line) {
    std::stringstream line_stream(line);
    return std::distance(std::istream_iterator<std::string>(line_stream), std::istream_iterator<std::string>());
}

// ================================================= Spellchecker outputs
void SpellChecker::print_errors() {
    std::cout << "Misspelled Words" << std::endl;
    for (int i = 0; i < this->misspelled_words.size(); i++) {
        std::cout << misspelled_words.at(i) << std::endl;
    }
}

void SpellChecker::print_errors_to_file(std::string file_name) {
    std::ofstream file_writer(file_name);
    try {
        for (int i = 0; i < this->misspelled_words.size(); i++) {
            file_writer << misspelled_words.at(i) << std::endl;
        }
    } catch (std::ifstream::failure& e) {
        std::cerr << "Error writing misspelled words to file";
    } catch (...) {
        std::cerr << "A general error has occurred trying to write misspelled words to file.";
    }

}

// ======================================== Input Sanitation ========================================
// Function built out with some help from Src: https://stackoverflow.com/questions/34723981/replacing-by-empty-character
std::string SpellChecker::sanitize_word(std::string word) {
    for (int i = 0; i < word.size(); i++) {
        // Convert string to lowercase
        if (!islower(word[i])) {
            word[i] = tolower(word[i]);
        }
        // Check for symbols, remove symbol and move every other char down
        if (!std::isalpha(word[i])) {
            word[i] = ' ';
        }
    }
    // Trim whitespace
    trim(word);
    return word;
}

// Trimming whitespaces from ends of string. Src: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
void SpellChecker::ltrim(std::string &s) {
    // use iterators to go over string
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        // 'callback' (phrase in JS, I guess its called a Lambda in c++) to find empty spaces
        return !std::isspace(ch);
    }));
}

void SpellChecker::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// One summing function that calls both trimming functions
void SpellChecker::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


