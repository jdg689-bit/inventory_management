// InventoryManagement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// This program aims to provide CRUD functionality within a .txt file
// Installation of sqlite was far too confusing for now

#include <iostream>
#include <fstream>
#include <string>

void addItem(std::fstream& myFile, std::string item) { // stream objects are non-copyable, pass by ref
    // Add the name of an item to a txt file

    // Open file
    myFile.open("inventory.txt", std::ios::app); // append mode

    if (myFile.is_open()) {
        // Write to file
        myFile << item << '\n';

        // Close file
        myFile.close();

        std::cout << "Successfully added " << item << " to file\n";

    }
    else {
        std::cout << "Error opening file\n";
    }
}

void readFile(std::fstream& myFile) {
    myFile.open("inventory.txt", std::ios::in); // read mode

    if (myFile.is_open()) {
        std::cout << '\n' << '\n' << "#########################" << '\n'; // Create some space before printing

        std::string line{};
        while (std::getline(myFile, line)) { // line by line copies myFile to line
            std::cout << line << std::endl;
        }
        std::cout << "#########################" << '\n' << '\n';
        myFile.close();
    }
    else {
        std::cout << "Error opening file\n";
    }
}

bool inFile(std::fstream& file, std::string query) {
    // open file
    file.open("inventory.txt", std::ios::in); // read mode

    bool isFound{ false };

    if (file.is_open()) {
        std::string line{};
        while (std::getline(file, line)) { // copy file line by line into line string
            // compare line string with query string
            if (line == query) {
                isFound = true;
                break;
            }
        }

        file.close();
    }

    return isFound;
}

void deleteItem(std::fstream& file, std::string lineToRemove) {
    // Files are sequential, no direct way to remove single line without rewriting

    // Create temp file
    std::fstream tempFile{};

    // Copy all other lines to temp file
    tempFile.open("temp.txt", std::ios::out);
    file.open("inventory.txt", std::ios::in);

    if (!tempFile.is_open() || !file.is_open()) {
        std::cout << "Error opening files.\n";
        return;
    }

    std::string line{};

    while (std::getline(file, line)) {
        if (line != lineToRemove) {
            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();

    // Delete original file
    std::remove("inventory.txt");

    // Rename temp file
    if (std::rename("temp.txt", "inventory.txt") != 0) {
        std::cout << "Error renaming temp file.\n";
    }

    std::cout << "Successfully removed " << lineToRemove << " from list.\n";
}


int main()
{
    std::cout << "Welcome to your new inventory management system.\n";

    do
    {
        std::cout << "Press 1 to add an entry.\n";
        std::cout << "Press 2 to delete an entry.\n";
        std::cout << "Press 3 to view current inventory.\n";
        std::cout << "Press 4 to terminate the program.\n";

        int selection{};

        std::cin >> selection;

        // Create file stream and string to store item
        std::fstream myFile{};
        std::string item{};

        if (selection == 1) { // Add item
            std::cout << "Enter item to add: ";
            std::getline(std::cin >> std::ws, item); // Item may contain ws (eg "red onions")
            addItem(myFile, item);
        }
        else if (selection == 2) { // Delete item
            std::cout << "Enter item to remove: ";
            std::getline(std::cin >> std::ws, item);
            deleteItem(myFile, item);
        }
        else if (selection == 3) {
            readFile(myFile);
        }
        else if (selection == 4) {
            break;
        }

    } while (true);

    std::cout << "Your session has been terminated.\n";

    return 0;
}
