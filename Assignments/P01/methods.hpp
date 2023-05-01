#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "person.hpp"

using namespace std;

// Defining the Linked list
struct LLNode {
    Person data;
    struct LLNode* next;
};

// Insert method for linked list
void insert_in_LinkedList(LLNode** root, Person individual) {
    LLNode* new_node = new LLNode();
    new_node->data = individual;
    new_node->next = NULL;
    if (*root == NULL) {
        *root = new_node;
    }
    else {
        LLNode* last_node = *root;
        while (last_node->next != NULL) {
            last_node = last_node->next;
        }
        last_node->next = new_node;
    }
}

// Search method for linked list
LLNode* search_in_LL(LLNode* node, string search_key) {
    int comp = 0;
    if (node == NULL) {
        return node;
    }
    while (node != NULL) {
        comp++;
        if (get_lower(node->data.first_name).find(search_key) != string::npos ||
            get_lower(node->data.last_name).find(search_key) != string::npos ||
            get_lower(node->data.email).find(search_key) != string::npos ||
            get_lower(node->data.address).find(search_key) != string::npos ||
            get_lower(node->data.city).find(search_key) != string::npos ||
            get_lower(node->data.state).find(search_key) != string::npos ||
            get_lower(node->data.car).find(search_key) != string::npos ||
            get_lower(node->data.favorite_movie).find(search_key) != string::npos ||
            get_lower(node->data.pet).find(search_key) != string::npos ||
            get_lower(node->data.job_title).find(search_key) != string::npos ||
            get_lower(node->data.phone_number).find(search_key) != string::npos) {
            cout << "Compared " << comp << " Nodes." << endl;
            return node;
        }
        node = node->next;
    }
    cout << "Compared " << comp << " Nodes." << endl;
    return node;
}

LLNode* search_in_LL(LLNode* node, int search_key) {
    int comp = 0;
    if (node == NULL) {
        return node;
    }
    while (node != NULL) {
        comp++;
        if (node->data.id == search_key) {
            cout << "Compared " << comp << " Nodes." << endl;
            return node;
        }
        node = node->next;
    }
    cout << "Compared " << comp << " Nodes." << endl;
    return node;
}

LLNode* search_in_LL(LLNode* node, double latitude, double longitude) {
    int comp = 0;
    if (node == NULL) {
        return node;
    }
    while (node != NULL) {
        comp++;
        if (node->data.latitude == latitude && node->data.longitude == longitude) {
            cout << "Compared " << comp << " Nodes." << endl;
            return node;
        }
        node = node->next;
    }
    cout << "Compared " << comp << " Nodes." << endl;
    return node;
}


// Defining Binary serach tree
struct BST {
    string key;
    Person individual;
    BST* left;
    BST* right;
};

// Insert a new individual into the tree based on string keys like name & address
void insert(BST*& root, Person individual, string key) {
    if (root == NULL) {
        root = new BST;
        root->key = key;
        root->individual = individual;
        root->left = NULL;
        root->right = NULL;
    }
    else {
        if (key < root->key) {
            insert(root->left, individual, key);
        }
        else {
            insert(root->right, individual, key);
        }
    }
}

// Insert a new individual into the tree based on int keys like ID
void insert(BST*& root, Person individual, int key) {
    if (root == NULL) {
        root = new BST;
        root->key = to_string(key);
        root->individual = individual;
        root->left = NULL;
        root->right = NULL;
    }
    else {
        if (key < stoi(root->key)) {
            insert(root->left, individual, key);
        }
        else {
            insert(root->right, individual, key);
        }
    }
}

// Insert a new person into the tree based on double keys like GPS
void insert(BST*& root, Person individual, double key) {
    if (root == NULL) {
        root = new BST;
        root->key = to_string(key);
        root->individual = individual;
        root->left = NULL;
        root->right = NULL;
    }
    else {
        if (individual.latitude + individual.longitude < stod(root->key)) {
            insert(root->left, individual, key);
        }
        else {
            insert(root->right, individual, key);
        }
    }
}

// Search for a person in the tree based in int keys such as ID
BST* search(BST* root, int search_key) {
    static int visits = 0;
    visits++;
    if (root == NULL || root->individual.id == search_key) {
        cout << endl;
        cout << "Visited " << visits << " nodes in BST." << endl;
        return root;

    }
    else if (search_key < root->individual.id) {
        return search(root->left, search_key);
    }
    else {
        return search(root->right, search_key);
    }
}

// Search for a person in the tree based on string keys like Name & address
BST* search(BST* root, string search_key) {
    static int visits = 0;
    visits++;
    if (root == NULL || root->key.find(search_key) != string::npos) {
        cout << "Visited " << visits << " nodes in BST." << endl;
        return root;

    }
    else if (search_key < root->key) {
        return search(root->left, search_key);
    }
    else {
        return search(root->right, search_key);
    }
}

// Search for a person in the tree based on double keys like gps
BST* search(BST* root, double latitude, double longitude) {
    static int visits = 0;
    visits++;
    if (root == NULL || root->individual.latitude + root->individual.longitude ==
        (latitude + longitude)) {
        cout << "Visited " << visits << " nodes in BST." << endl;
        return root;

    }
    else if ((latitude + longitude) <
        (root->individual.latitude + root->individual.longitude)) {
        return search(root->left, latitude, longitude);
    }
    else {
        return search(root->right, latitude, longitude);
    }
}
