// University Application Manager
// header file
// Teammates: 1) Tarbi Pyakurel(w10172900)
//            2) Drishya Basyal (w10185871)
//            3) Sonam Sherpa (w10171501)

#ifndef UNIVERSITY_APP_MANAGER_H
#define UNIVERSITY_APP_MANAGER_H

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Applicant {
public:
    string name;
    int applicantID;
    double gpa;
    string major;
    string status;
    int height;
    Applicant* left;
    Applicant* right;

    Applicant(string n, int id, double g, string m, string s)
        : name(n), applicantID(id), gpa(g), major(m), status(s),
          height(1), left(nullptr), right(nullptr) {}
};

class UniversityAppManager {
private:
    Applicant* root;  // Root of the AVL tree holding all applications

    // AVL tree helper functions:
    int getHeight(Applicant* node);
    int getBalance(Applicant* node);
    Applicant* rotateRight(Applicant* y);
    Applicant* rotateLeft(Applicant* x);
    Applicant* insert(Applicant* node,
                      const string& name,
                      int id,
                      double gpa,
                      const string& major,
                      const string& status);
    Applicant* search(Applicant* node, int id);
    Applicant* deleteNode(Applicant* root, int id);
    Applicant* minValueNode(Applicant* node);
    void inOrder(Applicant* node);
    void freeTree(Applicant* node);

public:
    UniversityAppManager();   // Constructor: initializes empty manager
    ~UniversityAppManager();  // Destructor: frees all allocated memory

    // Inserts a new application into the AVL tree
    void insertApplication(const string& name,
                           int id,
                           double gpa,
                           const string& major,
                           const string& status);

    // Returns true if an application with given ID exists
    bool searchApplication(int id);

    // Updates the status field of an existing application
    void updateApplicationStatus(int id, const string& status);

    // Deletes an application by ID (if present) and rebalances the tree
    void deleteApplication(int id);

    // Displays full details of the application matching the given ID
    void displaySearchResult(int id);

    // Displays all applications in sorted order by ID
    void displayApplications();
};

#endif // UNIVERSITY_APP_MANAGER_H
