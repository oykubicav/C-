#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.

    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    void deleteTree(TreeNode* node);
    typename BST<T>::TreeNode* insert(TreeNode* node, const string key, const T& value);
    typename BST<T>::TreeNode* remove(TreeNode* node, std::string key);
    bool search(TreeNode* node, std::string key) const;
    typename BST<T>::TreeNode* minValueNode(TreeNode* node);
    void tree2vector(TreeNode* node, vector<TreeNode>& result);
    
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {
     deleteTree(root);

    }
    template <class T>
typename BST<T>::TreeNode* BST<T>::remove(TreeNode* node, std::string key) {
    if (node == NULL) {
        return node;
    }
    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if (node->left == NULL) {
            TreeNode* temp = node->right;
             if(node!=NULL){
            delete node;
            node=NULL;}
            return temp;
        } else if (node->right == NULL) {
            TreeNode* temp = node->left;
            if(node!=NULL){
            delete node;}
            return temp;
        }
        TreeNode* temp = minValueNode(node->right);
        node->key = temp->key;
        node->data = temp->data;  // Copy the data from temp
        node->right = remove(node->right, temp->key);
    }
    return node;}
template <class T>
typename BST<T>::TreeNode* BST<T>::minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
template <class T>
bool BST<T>::search(TreeNode* node, std::string key) const {
    if (node == NULL) {
        return false;
    }
    if (key < node->key) {
        return search(node->left, key);
    } else if (key > node->key) {
        return search(node->right, key);
    } else {
        return true;
    }
}
template <class T>
void BST<T>::deleteTree(TreeNode* node) {
    if (node != NULL) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        node = NULL;  // Set the pointer to NULL after deletion
    }
}
    // Insert function for BST.    
    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
          root = insert(root, key, value);
    return *this;
    
    }
    template <class T>
typename BST<T>::TreeNode* BST<T>::insert(TreeNode* node, const string key, const T& value) {
    if (node == NULL) {
        return new TreeNode(key, value);
    }
    if (key < node->key) {
        node->left = insert(node->left, key, value);
    } else if (key > node->key) {
        node->right = insert(node->right, key, value);
    }
    return node;
}
    // Search function for BST.
    template <class T>
    bool BST<T>::search(std::string value) const {
       return search(root, value);
    }
    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        root = remove(root, key);
    }
    
    // A helper function for converting a BST into vector.
    
    template <class T>
void BST<T>::tree2vector(TreeNode* node, vector<TreeNode>& result) {
    if (node != NULL) {
        tree2vector(node->left, result);
        result.push_back(*node); // Shallow copy
        tree2vector(node->right, result);
    }
}

template <class T>
vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
    vector<TreeNode> result;
    tree2vector(root, result);
    return result;
}
    


template <class T>
BST<T>* BST<T>::merge(BST<T>* bst) {
    if (this->isEmpty() && bst->isEmpty()) {
        return NULL;
    }

    // Convert both trees into sorted vectors
    std::vector<TreeNode> vec1 = this->tree2vector(this->getRoot());
    std::vector<TreeNode> vec2 = bst->tree2vector(bst->getRoot());

    // Define iterator types
    typedef typename std::vector<TreeNode>::iterator VecIter;

    // Merge the two sorted vectors into one
    std::vector<TreeNode> merged;
    VecIter it1 = vec1.begin();
    VecIter it2 = vec2.begin();
    while (it1 != vec1.end() && it2 != vec2.end()) {
        if (it1->key < it2->key) {
            merged.push_back(*it1);
            ++it1;
        } else {
            merged.push_back(*it2);
            ++it2;
        }
    }
    while (it1 != vec1.end()) {
        merged.push_back(*it1);
        ++it1;
    }
    while (it2 != vec2.end()) {
        merged.push_back(*it2);
        ++it2;
    }

    // Convert the merged vector into a new BST
    BST<T>* mergedTree = new BST<T>();
    for (VecIter it = merged.begin(); it != merged.end(); ++it) {
        mergedTree->insert(it->key, it->data);
    }

    return mergedTree;
}


// Comparison function for TreeNode pointers

        
    // Intersect two BST's and return new BST.
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
    BST<T>* result = new BST<T>();
    vector<TreeNode> nodes = tree2vector(root);
    for (size_t i = 0; i < nodes.size(); i++) {
       if (bst->search(nodes[i].key)) {
            // Create a copy of the data in the node
            string key = nodes[i].key;
            T data = nodes[i].data;  // Make sure this creates a deep copy of the data
            // Insert the copy into the result tree
            result->insert(key, data);
        }
    }
    return result;}
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print() {
        print(root, "", true, false);
    
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
        if (node != NULL) {
            cout << node->key << endl;
            print(node->left, indent, false, true);
            print(node->right, indent, true, false);
        }
    
    }


