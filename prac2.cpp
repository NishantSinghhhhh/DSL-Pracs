#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<list>
#include<string>

using namespace std;

const int TABLE_SIZE = 101;

struct Entry{
    string word;
    string meaning;
};

vector<list<Entry>> hashTable(TABLE_SIZE);

int hashFunction(string word){
    int hash = 0;

    for(char ch: word)
        hash = (hash * 31 + ch) % TABLE_SIZE;
    return hash;   
}

void insertWord(const string& word, const string& meaning){
    int idx = hashFunction(word);

    hashTable[idx].push_back({word, meaning});
}

void searchWord(const string& word) {
    int idx = hashFunction(word);
    int comparisons = 0;

    list<Entry>& bucket = hashTable[idx]; 
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        comparisons++;
        if (it->word == word) {
            cout << "Word: " << word << "\nMeaning: " << it->meaning
                 << "\nComparisons: " << comparisons << "\n";
            return;
        }
    }

    cout << "Word '" << word << "' not found in dictionary.\n";
}

int main(){
    insertWord("apple", "a sweet fruit");
    insertWord("book", "a set of pages");
    insertWord("car", "a vehicle");
    insertWord("data", "information in raw form");
    insertWord("pen", "an instrument for writing");

    // Hardcoded search queries
    vector<string> queries = {"apple", "pen", "laptop"};

    for (const string& query : queries) {
        cout << "\nSearching for: " << query << endl;
        searchWord(query);
    }

    return 0;
}