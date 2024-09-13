#ifndef FILE_H
#define FILE_H

#include "FileSystemItem.h"

class File : public FileSystemItem {
public:
    File(const std::string& name, size_t size) : FileSystemItem(name), size(size) {}

    void showContent(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << name << " (File, " << size << " bytes)" << std::endl;
    }

    size_t getSize() const override {
        return size;
    }

private:
    size_t size;
};

#endif // FILE_H
