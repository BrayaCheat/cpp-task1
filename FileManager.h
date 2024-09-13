#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Folder.h"
#include <string>
#include <memory>
#include <algorithm>

class FileManager {
public:
    FileManager() : root(std::make_shared<Folder>("Root")) {}

    std::shared_ptr<Folder> getRoot() const { return root; }

    void showDiscContent() const {
        root->showContent();
    }

    void createFile(const std::string& path, const std::string& name, size_t size) {
        auto folder = navigateToFolder(path);
        if (folder) {
            folder->addItem(std::make_shared<File>(name, size));
        }
    }

    void createFolder(const std::string& path, const std::string& name) {
        auto folder = navigateToFolder(path);
        if (folder) {
            folder->addItem(std::make_shared<Folder>(name));
        }
    }

    void deleteItem(const std::string& path, const std::string& name) {
        auto folder = navigateToFolder(path);
        if (folder) {
            folder->removeItem(name);
        }
    }

    void renameItem(const std::string& path, const std::string& oldName, const std::string& newName) {
        auto item = navigateToItem(path, oldName);
        if (item) {
            item->name = newName;
        }
    }

    void copyItem(const std::string& srcPath, const std::string& destPath, const std::string& name) {
        auto item = navigateToItem(srcPath, name);
        if (item) {
            auto destFolder = navigateToFolder(destPath);
            if (destFolder) {
                destFolder->addItem(item);
            }
        }
    }

    void moveItem(const std::string& srcPath, const std::string& destPath, const std::string& name) {
        auto item = navigateToItem(srcPath, name);
        if (item) {
            auto destFolder = navigateToFolder(destPath);
            if (destFolder) {
                auto srcFolder = navigateToFolder(srcPath);
                if (srcFolder) {
                    srcFolder->removeItem(name);
                    destFolder->addItem(item);
                }
            }
        }
    }

    void searchByMask(const std::string& path, const std::string& mask) const {
        auto folder = navigateToFolder(path);
        if (folder) {
            searchByMaskInFolder(folder, mask);
        }
    }

private:
    std::shared_ptr<Folder> root;

    std::shared_ptr<Folder> navigateToFolder(const std::string& path) const {
        auto folder = root;
        // Assume path is just folder names separated by "/"
        size_t start = 0;
        size_t end = path.find('/');
        while (end != std::string::npos) {
            std::string folderName = path.substr(start, end - start);
            folder = std::dynamic_pointer_cast<Folder>(folder->findItem(folderName));
            if (!folder) return nullptr;
            start = end + 1;
            end = path.find('/', start);
        }
        return folder;
    }

    std::shared_ptr<FileSystemItem> navigateToItem(const std::string& path, const std::string& name) const {
        auto folder = navigateToFolder(path);
        if (folder) {
            return folder->findItem(name);
        }
        return nullptr;
    }

    void searchByMaskInFolder(const std::shared_ptr<Folder>& folder, const std::string& mask) const {
        for (const auto& item : folder->items) {
            if (item->getName().find(mask) != std::string::npos) {
                item->showContent();
            }
            if (auto subFolder = std::dynamic_pointer_cast<Folder>(item)) {
                searchByMaskInFolder(subFolder, mask);
            }
        }
    }
};

#endif // FILEMANAGER_H
