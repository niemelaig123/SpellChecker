#include <iostream>
#include "Dictionary.h"
#include "SpellChecker.h"

using namespace std;

int main(int argc, char** argv) {
    SpellChecker spellchecker;

    // Filling the dictionary tree
    if (argc > 1) {
        spellchecker.dict.fill_dictionary_from_file(argv[1]);
    } else {
        spellchecker.dict.fill_dictionary_from_file("../tests/dictionary.txt");
    }

    // Selecting file to read input from
    if (argc > 2) {
        spellchecker.check_spelling_in_file(argv[2]);
    } else {
        spellchecker.check_spelling_in_file("../tests/test.txt");
    }

    // Print errors to console
    spellchecker.print_errors();

    // Printing errors to file
    if (argc > 3) {
        spellchecker.print_errors_to_file(argv[3]);
    } else {
        spellchecker.print_errors_to_file("../output/misspelledtest.txt");
    }

    // Printing dictionary to file
    if (argc > 4) {
        spellchecker.dict.print_dictionary_to_file(argv[4]);
    } else {
        spellchecker.dict.print_dictionary_to_file("../output/dictionaryTree.txt");
    }

    return 0;
}