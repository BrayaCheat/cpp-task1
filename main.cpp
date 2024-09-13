#include <iostream>
#include "FileManager.h"

int main() {
    FileManager fm;

    // Create folders and files
    fm.createFolder("Root", "Folder1");
    fm.createFile("Root/Folder1", "File1.txt", 100);
    fm.createFolder("Root/Folder1", "SubFolder1");
    fm.createFile("Root/Folder1/SubFolder1", "File2.txt", 200);

    // Show content
    std::cout << "Disc Content:\n";
    fm.showDiscContent();

    // Rename file
    fm.renameItem("Root/Folder1", "File1.txt", "File1_renamed.txt");

    // Move file
    fm.moveItem("Root/Folder1/SubFolder1", "Root/Folder1", "File2.txt");

    // Search for files with mask
    std::cout << "\nSearch Results:\n";
    fm.searchByMask("Root/Folder1", "File");

    // Calculate size
    std::cout << "\nSize of Folder1: " << fm.navigateToFolder("Root/Folder1")->getSize() << " bytes\n";

    return 0;
}
