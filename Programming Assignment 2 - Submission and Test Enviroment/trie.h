#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); 
    // Do not change this line.
    void wildcardSearchHelper(typename Trie<T>::TrieNode* node, std::string currentKey, const std::string &wildcardKey, std::vector<T*> &results);
  bool wildcardMatch(const std::string &pattern, const std::string &key);
   void deleteTrieNode(TrieNode* node);
  void insertHelper(TrieNode* node, const string& key, size_t index);
  void findAll(TrieNode* node, std::string prefix, std::vector<T*>& results);
  
};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
      deleteTrieNode(root);
}
template <class T>
void Trie<T>::deleteTrieNode(TrieNode* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < TrieNode::ALPHABET_SIZE; i++) {
        deleteTrieNode(node->children[i]);
    }
if(node->data!=NULL){
    delete node->data;}
    if(node!=NULL){
    delete node;}
}

template <class T>
Trie<T>& Trie<T>::insert(const std::string& username) {
  insertHelper(root, username, 0);
        return *this;}
    template <class T>    

void Trie<T>::insertHelper(TrieNode* node, const string& key, size_t index) {
    if (index == key.size()) {
        node->isEndOfKey = true;
        node->data = new T(key);  
        return;
    }
    char c = key[index];
    if (node->children[static_cast<unsigned char>(c)] == NULL) {
        node->children[static_cast<unsigned char>(c)] = new TrieNode(c);
    }
    insertHelper(node->children[static_cast<unsigned char>(c)], key, index + 1);
}
template <class T>
T* Trie<T>::search(std::string username) {
    TrieNode* node = root;
    for (size_t i = 0; i < username.size(); ++i) {
        char c = username[i];
        if (node->children[static_cast<unsigned char>(c)] == NULL) {
            return NULL;
        }
        node = node->children[static_cast<unsigned char>(c)];
    }
    return node->isEndOfKey ? node->data : NULL;
}

template <class T>
void Trie<T>::remove(std::string username) {
    TrieNode* node = root;
    std::vector<TrieNode*> nodes;
    for (size_t i = 0; i < username.size(); ++i) {
        char c = username[i];
        if (node->children[static_cast<unsigned char>(c)] == NULL) {
            return;
        }
        nodes.push_back(node);
        node = node->children[static_cast<unsigned char>(c)];
    }
    if (node->isEndOfKey) {
        node->isEndOfKey = false;
       delete node->data;  
            node->data = NULL;
        }
        
    }

template <class T>
void Trie<T>::findStartingWith(std::string prefix, std::vector<T*>& results) {
    TrieNode* node = root;
    for (std::size_t i = 0; i < prefix.size(); ++i) {
        char c = prefix[i];
        if (node->children[static_cast<unsigned char>(c)] == NULL) {
            
            return;  
        }
        node = node->children[static_cast<unsigned char>(c)];
    }
    
    findAll(node, prefix, results);
}

template <class T>
void Trie<T>::findAll(TrieNode* node, std::string prefix, std::vector<T*>& results) {
    if (node == NULL) {
        return;
    }
    if (node->isEndOfKey) {
        
        results.push_back(node->data);  
    }
    for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
        if (node->children[i] != NULL) {
            char nextChar = static_cast<char>(i);
            findAll(node->children[i], prefix + nextChar, results);
        }
    }}
    
template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
    wildcardSearchHelper(root, "", wildcardKey, results);
}
template <class T>
void Trie<T>::wildcardSearchHelper(typename Trie<T>::TrieNode* node, std::string currentKey, const std::string &wildcardKey, std::vector<T*> &results)  {
    if (node == NULL) {
        return;
    }
    if (node->isEndOfKey) {
        if (wildcardMatch(wildcardKey, currentKey)) {
            results.push_back(node->data);
        }
    }
    for (int i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
        if (node->children[i] != NULL) {
            char nextChar = static_cast<char>(i);
            wildcardSearchHelper(node->children[i], currentKey + nextChar, wildcardKey, results);
        }
    }
}
template<class T>
bool Trie<T>::wildcardMatch(const std::string &pattern, const std::string &key)  {
    int m = key.size();
    int n = pattern.size();

    
    
vector<vector<bool> > table(m + 1, vector<bool>(n + 1, false));
   
    table[0][0] = true;

   
    for (int j = 1; j <= n; j++) {
        if (pattern[j - 1] == '*') {
            table[0][j] = table[0][j - 1];
        }
    }

    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            
            if (pattern[j - 1] == '*') {
                table[i][j] = table[i][j - 1] || table[i - 1][j];
            }
           
            else if (pattern[j - 1] == '?' || key[i - 1] == pattern[j - 1]) {
                table[i][j] = table[i - 1][j - 1];
            }
           
            else {
                table[i][j] = false;
            }
        }
    }

    return table[m][n];
}




/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (size_t i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}



