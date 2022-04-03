//
// Created by nieme on 2022-03-09.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Dictionary.h"

// ============================== Main Dictionary Drivers ==================================
// ------------------------------ Insertion ------------------------------------------------
Word* Dictionary::add_word(std::string word) {
    return add_word(word, m_root);
}

// Recursive insertion called from entry
Word* Dictionary::add_word(std::string word, Word *&node) {
    // Checking to see if new root is needed
    if (node == nullptr) {
        node = new Word();

        // If not an empty string
        if (word.size() > 0) {
            if (word[word.size()-1] == '\r') {
                // trying to erase carriage returns to improve word comparison
                word.erase(word.size()-1);
            }
        }

        node->m_data = word;
        node->m_left = nullptr;
        node->m_right = nullptr;
        return node;
    } else if (word < node->m_data) {
        node->m_left = add_word(word, node->m_left);
        node = balance(node);
    } else if (word > node->m_data) {
        node->m_right = add_word(word, node->m_right);
        node = balance(node);
    }
    return node;
}

// --------------------------- In-Search-in' --------------------------------------
bool Dictionary::search_for_word(std::string word_to_find) {
    return search_for_word(word_to_find, m_root);
}

bool Dictionary::search_for_word(std::string word_to_find, Word *word) {
    // If null, its not in the dictionary so its misspelled
    if (word == nullptr) {
        return false;
    }
    // Convert string to lowercase
    for (int i = 0; i < word_to_find.size(); i++) {
        if (!islower(word_to_find[i])) {
            word_to_find[i] = tolower(word_to_find[i]);
        }
    }

    if (word->m_data == word_to_find) {
        return true;
    }
    bool is_left = search_for_word(word_to_find, word->m_left);
    if (is_left) {
        return true;
    }
    bool is_right = search_for_word(word_to_find, word->m_right);
    return is_right;
}

void Dictionary::show_dictionary(std::ostream &output, Word *&node, int indent) {
    if (node != nullptr) {
        show_dictionary(output, node->m_right, indent + 4);
        output << std::setw(indent) << node->m_data << std::endl;
        show_dictionary(output, node->m_left, indent + 4);
    }
}

// Functions for displaying the output of the BST
void Dictionary::fill_dictionary_from_file(std::string file_name) {
    std::ifstream file_reader(file_name);
    std::string word;
    try {
        while (file_reader) {
            getline(file_reader, word);
            add_word(word);
        }
    } catch (std::ifstream::failure& e) {
        std::cerr << "Error reading dictionary from file";
    } catch (...) {
        std::cerr << "A general error has occurred while trying to read dictionary from file";
    }

}

std::ostream &operator<<(std::ostream &output, Dictionary &dictionary) {
    dictionary.show_dictionary(output, dictionary.m_root, 0);
}

// ============================ Balancers =========================================
Word *Dictionary::balance(Word *word) {
    int balance_factor = get_difference(word);
    if (balance_factor > 1) {
        if (get_difference(word->m_left) > 0) {
            word = left_left_rotate(word);
        } else {
            word = left_right_rotate(word);
        }
    }
    else if (balance_factor < -1) {
        if (get_difference(word->m_right) > 0) {
            word = right_left_rotate(word);
        } else {
            word = right_right_rotate(word);
        }
    }
    return word;
}

// Helper for finding the max height between two nodes
int Dictionary::get_max(int num1, int num2) {
    // Return the higher value
    return (num1 > num2) ? num1 : num2;
}

int Dictionary::get_difference(Word *word) {
    return (find_height(word->m_left) - find_height(word->m_right));
}

int Dictionary::find_height(Word *word) {
    int height = 0;
    if (word != nullptr) {
        int left_height = find_height(word->m_left);
        int right_height = find_height(word->m_right);
        height = get_max(left_height, right_height) + 1;
    }
    return height;
}

// ============================== Rotations ===================================
Word *Dictionary::left_left_rotate(Word *word) {
    Word *node = word->m_left;
    word->m_left = node->m_right;
    node->m_right = word;
    //std::cout << "Left Left Rotation" << std::endl;

    return node;
}

Word *Dictionary::left_right_rotate(Word *word) {
    Word *node = word->m_left;
    word->m_left = right_right_rotate(node);
    //std::cout << "Left Right Rotation" << std::endl;

    return left_left_rotate(word);
}

Word *Dictionary::right_right_rotate(Word *word) {
    Word *node = word->m_right;
    word->m_right = node->m_left;
    node->m_left = word;
    //std::cout << "Right Right Rotation" << std::endl;

    return node;
}

Word *Dictionary::right_left_rotate(Word *word) {
    Word *node = word->m_right;
    word->m_right = left_left_rotate(node);
    //std::cout << "Right Left Rotation" << std::endl;

    return right_right_rotate(word);
}

// ==================================== printing functions ====================================
void Dictionary::print_dictionary_to_file(std::string file_name) {
    print_dictionary_to_file(file_name, m_root, 0);
}

void Dictionary::print_dictionary_to_file(std::string file_name, Word *word, int indent) {
    std::ofstream file_writer(file_name, std::ios_base::app);
    if (word != nullptr) {
        print_dictionary_to_file(file_name, word->m_right, indent + 8);
        file_writer << std::setw(indent) << word->m_data << std::endl;
        print_dictionary_to_file(file_name, word->m_left, indent + 8);
    }
}