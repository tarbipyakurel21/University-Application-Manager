// University Application Manager
// cpp file
// Teammates: 1) Tarbi Pyakurel (w10172900)
//           2) Drishya Basyal  (w10185871)
//           3) Sonam Sherpa     (w10171501)

#include "UniversityAppManager.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Constructor: initialize an empty AVL tree (root is nullptr)
UniversityAppManager::UniversityAppManager()
    : root(nullptr) {}

// Destructor: recursively free all nodes to avoid memory leaks
UniversityAppManager::~UniversityAppManager() {
    freeTree(root);
}

// Helper: get height of a node, 0 if null
int UniversityAppManager::getHeight(Applicant* node) {
    return node ? node->height : 0;
}

// Helper: compute balance factor = height(left) - height(right)
int UniversityAppManager::getBalance(Applicant* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Rotate subtree right around y (LL case)
Applicant* UniversityAppManager::rotateRight(Applicant* y) {
    Applicant* x = y->left;       // x becomes new root of this subtree
    Applicant* T2 = x->right;     // T2 is x's right subtree

    x->right = y;                 // perform rotation
    y->left = T2;

    // Update heights after rotation
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;  // return new subtree root
}

// Rotate subtree left around x (RR case)
Applicant* UniversityAppManager::rotateLeft(Applicant* x) {
    Applicant* y = x->right;      // y becomes new root of this subtree
    Applicant* T2 = y->left;      // T2 is y's left subtree

    y->left = x;                  // perform rotation
    x->right = T2;

    // Update heights after rotation
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;  // return new subtree root
}

// Recursive insertion into AVL tree with rebalancing
Applicant* UniversityAppManager::insert(Applicant* node,
                                        const string& name,
                                        int id,
                                        double gpa,
                                        const string& major,
                                        const string& status) {
    // 1) Standard BST insert
    if (!node)
        return new Applicant(name, id, gpa, major, status);

    if (id < node->applicantID)
        node->left = insert(node->left, name, id, gpa, major, status);
    else if (id > node->applicantID)
        node->right = insert(node->right, name, id, gpa, major, status);
    else
        return node;  // duplicate IDs not inserted

    // 2) Update height of this ancestor node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3) Check balance factor and choose rotation if unbalanced
    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && id < node->left->applicantID)
        return rotateRight(node);
    // RR Case
    if (balance < -1 && id > node->right->applicantID)
        return rotateLeft(node);
    // LR Case
    if (balance > 1 && id > node->left->applicantID) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // RL Case
    if (balance < -1 && id < node->right->applicantID) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Return unchanged node pointer
    return node;
}

// Recursive search in BST: returns pointer or nullptr
Applicant* UniversityAppManager::search(Applicant* node, int id) {
    if (!node || node->applicantID == id)
        return node;
    if (id < node->applicantID)
        return search(node->left, id);
    return search(node->right, id);
}

// Find node with minimum ID (leftmost leaf) for deletion
Applicant* UniversityAppManager::minValueNode(Applicant* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// Recursive deletion from AVL tree with rebalancing
Applicant* UniversityAppManager::deleteNode(Applicant* root, int id) {
    // 1) BST deletion
    if (!root)
        return root;

    if (id < root->applicantID)
        root->left = deleteNode(root->left, id);
    else if (id > root->applicantID)
        root->right = deleteNode(root->right, id);
    else {
        // Node with one or no child
        if (!root->left || !root->right) {
            Applicant* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        // Node with two children: get inorder successor
        Applicant* temp = minValueNode(root->right);
        // Copy successor’s data to this node
        root->name        = temp->name;
        root->applicantID = temp->applicantID;
        root->gpa         = temp->gpa;
        root->major       = temp->major;
        root->status      = temp->status;
        // Delete the successor
        root->right = deleteNode(root->right, temp->applicantID);
    }

    // 2) Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3) Rebalance if necessary
    int balance = getBalance(root);
    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// In-order traversal: prints applications sorted by ID
void UniversityAppManager::inOrder(Applicant* node) {
    if (!node) return;
    inOrder(node->left);
    cout << "ID: " << node->applicantID
         << ", Name: " << node->name
         << ", GPA: " << node->gpa
         << ", Major: " << node->major
         << ", Status: " << node->status << endl;
    inOrder(node->right);
}

// Recursively free all nodes to clean up memory
void UniversityAppManager::freeTree(Applicant* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

// Public wrapper: insert a new application
void UniversityAppManager::insertApplication(const string& name,
                                             int id,
                                             double gpa,
                                             const string& major,
                                             const string& status) {
    root = insert(root, name, id, gpa, major, status);
}

// Public wrapper: check if application exists
bool UniversityAppManager::searchApplication(int id) {
    return search(root, id) != nullptr;
}

// Public: update status if application exists
void UniversityAppManager::updateApplicationStatus(int id,
                                                   const string& status) {
    Applicant* applicant = search(root, id);
    if (applicant) {
        applicant->status = status;
        cout << "Application status updated!\n";
    } else {
        cout << "Applicant not found.\n";
    }
}

// Public: delete an application by ID
void UniversityAppManager::deleteApplication(int id) {
    root = deleteNode(root, id);
    cout << "Applicant with ID " << id << " deleted if existed.\n";
}

// Public: display all applications sorted by ID
void UniversityAppManager::displayApplications() {
    cout << "Displaying Applications in Sorted Order:\n";
    inOrder(root);
}

// Public: display detailed info for a single application by ID
void UniversityAppManager::displaySearchResult(int id) {
    Applicant* node = search(root, id);
    if (node) {
        cout << "--- Applicant Details ---\n"
             << "ID:     " << node->applicantID << "\n"
             << "Name:   " << node->name        << "\n"
             << "GPA:    " << node->gpa         << "\n"
             << "Major:  " << node->major       << "\n"
             << "Status: " << node->status      << "\n";
    } else {
        cout << "Applicant with ID " << id << " not found.\n";
    }
}
