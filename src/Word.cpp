//
// Created by nieme on 2022-03-09.
//

#include "Word.h"

bool Word::operator==(Word word) {
    return (this->m_data == word.m_data);
}

int Word::get_height() {
    if (this == nullptr) {
        return 0;
    }
    return this->height;
}

Word::Word(std::string word) {
    m_data = word;
    height = 1;
}
