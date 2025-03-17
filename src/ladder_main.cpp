#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    string start_word, end_word;

    verify_word_ladder();
    
    while (true) {
        cout << "\nEnter the starting word (or 'quit' to exit): ";
        cin >> start_word;
        
        // Convert to lowercase
        for (char& c : start_word) {
            c = tolower(c);
        }
        
        if (start_word == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }
        
        cout << "Enter the ending word: ";
        cin >> end_word;
        
        for (char& c : end_word) {
            c = tolower(c);
        }
        
        // Check if start and end words are the same
        if (start_word == end_word) {
            error(start_word, end_word, "Start and end words are the same!");
            continue;
        }
        vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
        print_word_ladder(ladder);
    }
    
    return 0;
}