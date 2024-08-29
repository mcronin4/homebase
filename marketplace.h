#ifndef MARKETPLACE_H
#define MARKETPLACE_H

#include <string>
#include <vector>

enum class ItemCategory {
    ELECTRONICS,
    BOOKS,
    FURNITURE,
    CLOTHING,
    OTHER
};

struct ItemInfo {
    std::string name;
    ItemCategory category;
    std::string description;
    std::string contactInfo;
    std::string imageUrl;
};


class SecondHandMarket {
public:
    void addItem (const std::string& name, ItemCategory category, const std::string& description, const std::string& contactInfo, const std::string& imageUrl);
    std::vector<ItemInfo> getAllItems() const;

private:
    std::vector<ItemInfo> items;

};

#endif // MARKETPLACE_H
