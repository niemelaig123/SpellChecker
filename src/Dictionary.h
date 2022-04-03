//
// Created by nieme on 2022-03-09.
//
// This class represents the BST itself, and as such is responsible for BST related actions, including loading, populating, searching, and balancing
// A lot of the AVL balancing methods are based on code found here: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

#ifndef ASSIGNMENT_3_DICTIONARY_H
#define ASSIGNMENT_3_DICTIONARY_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Dictionary.h"
#include "Word.h"

class Dictionary {
private:
    Word *m_root {nullptr};
public:
    Dictionary() = default;
    ~Dictionary() = default;

    // Methods
    Word *add_word(std::string word);
    bool search_for_word(std::string word_to_find);
    void show_dictionary(std::ostream& output, Word*& node, int indent);
    void fill_dictionary_from_file(std::string file_name);

    // Balancing functions
    Word *balance(Word *word);
    Word *left_left_rotate(Word *word);
    Word *left_right_rotate(Word *word);
    Word* right_right_rotate(Word *word);
    Word* right_left_rotate(Word *word);

    // Helpers
    int get_max(int num1, int num2);
    int get_difference(Word *word);
    int find_height(Word *word);


    void print_dictionary_to_file(std::string file_name);
    friend std::ostream& operator<<(std::ostream &output, Dictionary &dictionary);

protected:
    void print_dictionary_to_file(std::string file_name, Word *word, int indent);
    Word* add_word(std::string word, Word*& node);
    bool search_for_word(std::string word_to_find, Word *word);
};


#endif //ASSIGNMENT_3_DICTIONARY_H
