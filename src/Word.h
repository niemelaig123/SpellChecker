//
// Created by nieme on 2022-03-09.
//
// This is the representation of every node in the BST, as they correspond to words from the dictionary

#ifndef ASSIGNMENT_3_WORD_H
#define ASSIGNMENT_3_WORD_H

#include <string>

class Word {
private:

public:
    std::string m_data;
    Word *m_left {nullptr};
    Word *m_right {nullptr};
    int height;

    Word() = default;
    Word(std::string word);
    ~Word() = default;

    // getters
    int get_height();

    // for comparison
    bool operator==(Word word);
};


#endif //ASSIGNMENT_3_WORD_H
