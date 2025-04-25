// University Application Manager
// main file
// Teammates: 1) Tarbi Pyakurel (w10172900)
//           2) Drishya Basyal  (w10185871)
//           3) Sonam Sherpa     (w10171501)

#include "UniversityAppManager.h"  // Include the class definition
#include <iostream>                 // For input/output operations
using namespace std;

// Displays the user menu and handles all user interactions
void menu() {
    // Create a manager object to perform all operations
    UniversityAppManager manager;

    // Variables to store user input for various operations
    int choice, id;
    string name, major, status;
    double gpa;

    // Loop until the user chooses to exit (option 6)
    while (true) {
        // Display menu options
        cout << "\n University Application Manager\n";
        cout << "1. Insert Application\n";
        cout << "2. Search Application\n";
        cout << "3. Update Application\n";
        cout << "4. Delete Application\n";
        cout << "5. Display Applications (Sorted)\n";
        cout << "6. Exit\n";
        cout << "   Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Insert a new application
                cout << "Enter Name: ";
                cin.ignore();  // Consume leftover newline
                getline(cin, name);
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter GPA: ";
                cin >> gpa;
                cout << "Enter Major: ";
                cin.ignore();
                getline(cin, major);
                cout << "Enter Status: ";
                getline(cin, status);
                manager.insertApplication(name, id, gpa, major, status);
                break;

            case 2:
                // Search for an application by ID and display if found
                cout << "Enter Applicant Id to search: ";
                cin >> id;
                if (manager.searchApplication(id)) {
                    cout << "Application found\n";
                    manager.displaySearchResult(id);  // Show details
                } else {
                    cout << "Application not found\n";
                }
                break;

            case 3:
                // Update the status of an existing application
                cout << "Enter Applicant Id: ";
                cin >> id;
                cout << "Enter new status (e.g., pending, rejected, accepted): ";
                cin.ignore();
                getline(cin, status);
                manager.updateApplicationStatus(id, status);
                break;

            case 4:
                // Delete an application by ID
                cout << "Enter Applicant Id to delete: ";
                cin >> id;
                manager.deleteApplication(id);
                break;

            case 5:
                // Display all applications in sorted order
                manager.displayApplications();
                break;

            case 6:
                // Exit the program
                return;

            default:
                // Handle invalid menu choices
                cout << "Invalid Choice.\n";
        }
    }
}

// Entry point of the program
int main() {
    menu();  // Launch the menu-driven interface
    return 0;
}
