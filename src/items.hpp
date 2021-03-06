#ifndef __ITEMS__HPP__
#define __ITEMS__HPP__

#include <vector>

namespace Item
{
    enum class Type
    {
        NONE = -1,
        MAGIC_AMULET,
        MAGIC_WAND,
        SWORD,
        JADE_WARRIORS_SWORD,
        PLUMED_HELMET,
        THROWING_KNIVES,
        HEALING_SALVE,
        ELFIN_BOOTS,
        CENSER_OF_FRAGRANT_INCENSE,
        JEWEL_OF_SUNSET_FIRE,
        KNIFE,
        DIAMOND,
        CHAINS,
        SHIELD,
        BOOK_OF_MYTHS_AND_LEGENDS,
        First = MAGIC_AMULET,
        Last = BOOK_OF_MYTHS_AND_LEGENDS
    };

    class Base
    {
    public:
        std::string Name;
        std::string Description;

        Item::Type Type = Item::Type::NONE;

        int Charge = -1;

        Base()
        {
        }

        Base(const char *name, const char *description, Item::Type type)
        {
            Name = name;
            Description = description;
            Type = type;
        }

        Base(const char *name, const char *description, Item::Type type, int charge)
        {
            Name = name;
            Description = description;
            Type = type;
            Charge = charge;
        }
    };

    // Item defaults
    auto MAGIC_AMULET = Item::Base("MAGIC AMULET", "MAGIC AMULET", Item::Type::MAGIC_AMULET);
    auto MAGIC_WAND = Item::Base("MAGIC WAND", "MAGIC WAND", Item::Type::MAGIC_WAND);
    auto SWORD = Item::Base("SWORD", "SWORD", Item::Type::SWORD);
    auto JADE_WARRIORS_SWORD = Item::Base("JADE WARRIOR's SWORD", "JADE WARRIOR's SWORD", Item::Type::JADE_WARRIORS_SWORD);
    auto PLUMED_HELMET = Item::Base("PLUMED HELMET", "PLUMED HELMET", Item::Type::PLUMED_HELMET);
    auto THROWING_KNIVES = Item::Base("THROWING KNIVES", "THROWING KNIVES", Item::Type::THROWING_KNIVES);
    auto HEALING_SALVE = Item::Base("HEALING SALVE", "HEALING SALVE", Item::Type::HEALING_SALVE);
    auto ELFIN_BOOTS = Item::Base("ELFIN BOOTS", "ELFIN BOOTS", Item::Type::ELFIN_BOOTS);
    auto CENSER_OF_FRAGRANT_INCENSE = Item::Base("CENSER OF FRAGRANT INCENSE", "CENSER OF FRAGRANT INCENSE", Item::Type::CENSER_OF_FRAGRANT_INCENSE);
    auto JEWEL_OF_SUNSET_FIRE = Item::Base("JEWEL OF SUNSET FIRE", "JEWEL OF SUNSET FIRE", Item::Type::JEWEL_OF_SUNSET_FIRE);
    auto KNIFE = Item::Base("KNIFE", "KNIFE", Item::Type::KNIFE);
    auto DIAMOND = Item::Base("DIAMOND", "DIAMOND", Item::Type::DIAMOND);
    auto CHAINS = Item::Base("CHAINS", "CHAINS", Item::Type::CHAINS);
    auto SHIELD = Item::Base("SHIELD", "SHIELD", Item::Type::SHIELD, 6);
    auto BOOK_OF_MYTHS_AND_LEGENDS = Item::Base("BOOK OF MYTHS AND LEGENDS", "BOOK OF MYTHS AND LEGENDS", Item::Type::BOOK_OF_MYTHS_AND_LEGENDS);

    std::vector<Item::Type> UniqueItems = {};

    bool IsUnique(Item::Type item)
    {
        auto unique = false;

        for (auto i = 0; i < Item::UniqueItems.size(); i++)
        {
            if (Item::UniqueItems[i] == item)
            {
                unique = true;

                break;
            }
        }

        return unique;
    }

    void REMOVE(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    items.erase(items.begin() + i);

                    break;
                }
            }
        }
    }

    void ADD(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            auto found = 0;

            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    found++;
                }
            }

            if (found == 0)
            {
                items.push_back(item);
            }
        }
        else
        {
            items.push_back(item);
        }
    }

    bool VERIFY(std::vector<Item::Base> &items, Item::Base item)
    {
        auto has = false;

        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    has = true;

                    break;
                }
            }
        }

        return has;
    }

    int FIND(std::vector<int> list, int item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i] == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int FIND_TYPE(std::vector<Item::Base> list, Item::Type item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int COUNT_TYPES(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = 0;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found++;
            }
        }

        return found;
    }

    int FIND_LEAST(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = -1;

        auto min = 255;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                if (list[i].Charge < min)
                {
                    found = i;

                    min = list[i].Charge;
                }
            }
        }

        return found;
    }

} // namespace Item
#endif
