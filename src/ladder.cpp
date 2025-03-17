#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << endl;
    cout << "Word1: " << word1 << endl;
    cout << "Word2: " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();
    
    if (abs(len1 - len2) > d) {
        return false;
    }
    
    int diff = 0;
    
    if (len1 == len2) {
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) {
                diff++;
                if (diff > d) {
                    return false;
                }
            }
        }
        return true;
    } else {
        if (len1 > len2) {
            return edit_distance_within(str2, str1, d);
        }
        
        for (int i = 0, j = 0; i < len1; i++, j++) {
            if (str1[i] != str2[j]) {
                if (diff >= d) {
                    return false;
                }
                diff++;
                i--; 
            }
        }
        diff += (len2 - len1) - (diff);
        return diff <= d;
    }
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // Check if start and end words are the same
    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words are the same!");
        return {};
    }
    
    // Queue
    queue<vector<string>> ladder_queue;
    
    // Initialize with starting word
    vector<string> initial_ladder = {begin_word};
    ladder_queue.push(initial_ladder);
    
    // Track visited words
    set<string> visited;
    visited.insert(begin_word);
    
    // BFS
    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = current_ladder.back();
        
        // Check if the last word is the end word
        if (last_word == end_word) {
            return current_ladder;
        }
        
        // Explore
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    return {};
}

// Load words from file
void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    
    if (!in) {
        in.clear(); 
        in.open("src/words.txt"); 
    }
    
    if (!in) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }
    
    string word;
    while (in >> word) {
        for (char& c : word) {
            c = tolower(c);
        }
        word_list.insert(word);
    }
    in.close();
}

// Print the word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    cout << "cat to dog: ";
    cout << (generate_word_ladder("cat", "dog", word_list).size() == 4 ? "passed" : "failed") << endl;
    
    cout << "marty to curls: ";
    cout << (generate_word_ladder("marty", "curls", word_list).size() == 6 ? "passed" : "failed") << endl;
    
    cout << "code to data: ";
    cout << (generate_word_ladder("code", "data", word_list).size() == 6 ? "passed" : "failed") << endl;
    
    cout << "work to play: ";
    cout << (generate_word_ladder("work", "play", word_list).size() == 6 ? "passed" : "failed") << endl;
    
    cout << "sleep to awake: ";
    cout << (generate_word_ladder("sleep", "awake", word_list).size() == 8 ? "passed" : "failed") << endl;
    
    cout << "car to cheat: ";
    cout << (generate_word_ladder("car", "cheat", word_list).size() == 4 ? "passed" : "failed") << endl;
}