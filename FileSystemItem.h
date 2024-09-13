#ifndef FILESYSTEMITEM_H
#define FILESYSTEMITEM_H

#include <string>
#include <vector>
#include <memory>

class FileSystemItem {
public:
    FileSystemItem(const std::string& name) : name(name) {}
    virtual ~FileSystemItem() = default;

    std::string getName() const { return name; }
    virtual void showContent(int indent = 0) const = 0;
    virtual size_t getSize() const = 0;

protected:
    std::string name;
};

#endif // FILESYSTEMITEM_H
