//
// Created by nieme on 2022-03-09.
//
// This is where the magic happens, this class will largely be the one responsible for the Spellchecking program itself

#ifndef ASSIGNMENT_3_SPELLCHECKER_H
#define ASSIGNMENT_3_SPELLCHECKER_H


#include <string>
#include <vector>
#include "Dictionary.h"
#include <iostream>

class SpellChecker {
public:
    std::vector<std::string> misspelled_words;
    Dictionary dict;
    std::string file_contents[100];

    // Main Driver
    void check_spelling_in_file(std::string file_name);

    // Helpers
    int count_words_in_line(std::string const& line);
    std::string sanitize_word(std::string word);
    void ltrim(std::string &s);
    void rtrim(std::string &s);
    void trim(std::string &s);

    void print_errors();
    void print_errors_to_file(std::string file_name);
};


#endif //ASSIGNMENT_3_SPELLCHECKER_H
