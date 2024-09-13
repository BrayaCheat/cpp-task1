#ifndef FOLDER_H
#define FOLDER_H

#include "FileSystemItem.h"

class Folder : public FileSystemItem {
public:
    Folder(const std::string& name) : FileSystemItem(name) {}

    void addItem(std::shared_ptr<FileSystemItem> item) {
        items.push_back(item);
    }

    void removeItem(const std::string& name) {
        items.erase(std::remove_if(items.begin(), items.end(),
            [&name](const std::shared_ptr<FileSystemItem>& item) {
                return item->getName() == name;
            }), items.end());
    }

    std::shared_ptr<FileSystemItem> findItem(const std::string& name) const {
        for (const auto& item : items) {
            if (item->getName() == name) {
                return item;
            }
        }
        return nullptr;
    }

    void showContent(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << name << " (Folder)" << std::endl;
        for (const auto& item : items) {
            item->showContent(indent + 2);
        }
    }

    size_t getSize() const override {
        size_t totalSize = 0;
        for (const auto& item : items) {
            totalSize += item->getSize();
        }
        return totalSize;
    }

private:
    std::vector<std::shared_ptr<FileSystemItem>> items;
};

#endif // FOLDER_H
