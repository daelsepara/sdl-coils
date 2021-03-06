#ifndef __STORY__HPP__
#define __STORY__HPP__

#include <vector>

#include "constants.hpp"
#include "controls.hpp"
#include "codewords.hpp"
#include "items.hpp"
#include "skills.hpp"
#include "character.hpp"

namespace Choice
{
    enum class Type
    {
        NORMAL = 0, // No requirements
        ITEMS,
        GET_ITEMS,
        SKILL,
        CODEWORD,
        MONEY,
        LIFE,
        ANY_ITEM,
        ANY_SKILL,
        SKILL_ITEM,
        SKILL_ANY,
        SKILL_ALL,
        FIRE_WEAPON,
        LOSE_ITEMS,
        LOSE_MONEY,
        LOSE_ALL,
        LOSE_SKILLS,
        GET_CODEWORD,
        LOSE_CODEWORD,
        GAIN_MONEY,
        GIVE,
        BRIBE,
        TAKE,
        PAY_WITH,
        SELL,
        BARTER
    };

    class Base
    {
    public:
        const char *Text = NULL;

        Choice::Type Type = Choice::Type::NORMAL;

        Skill::Type Skill = Skill::Type::NONE;

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        std::vector<Codeword::Type> Codewords = std::vector<Codeword::Type>();

        int Value = 0;

        int Destination = -1;

        Base(const char *text, int destination)
        {
            Text = text;
            Destination = destination;
        }

        Base(const char *text, int destination, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL_ITEM;
            Items = items;
            Skill = skill;
        }

        Base(const char *text, int destination, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::ITEMS;
            Items = items;
        }

        Base(const char *text, int destination, Skill::Type skill)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL;
            Skill = skill;
        }

        Base(const char *text, int destination, std::vector<Codeword::Type> codewords)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::CODEWORD;
            Codewords = codewords;
        }

        Base(const char *text, int destination, Choice::Type type, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type)
        {
            Text = text;
            Destination = destination;
            Type = type;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Skill = skill;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Codeword::Type> codewords)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Codewords = codewords;
        }
    };
} // namespace Choice

namespace Story
{
    enum class Type
    {
        NORMAL = 0,
        GOOD,
        HERO_DEATH,
        MARTYR_DEATH,
        DOOM
    };

    enum class Controls
    {
        NONE = 0,
        STANDARD,
        SHOP,
        BUY_AND_SELL,
        SELL,
        TRADE,
        BARTER,
        BARTER_AND_SHOP
    };

    class Base
    {
    public:
        int ID = 0;

        const char *Text = NULL;

        const char *Title = NULL;

        const char *Bye = NULL;

        const char *Image = NULL;

        Story::Controls Controls = Story::Controls::NONE;

        std::vector<Choice::Base> Choices = std::vector<Choice::Base>();

        std::vector<std::pair<Item::Base, int>> Shop = std::vector<std::pair<Item::Base, int>>();
        std::vector<std::pair<Item::Base, int>> Sell = std::vector<std::pair<Item::Base, int>>();

        std::pair<Item::Base, Item::Base> Trade;
        std::vector<std::pair<Item::Base, std::vector<Item::Base>>> Barter = std::vector<std::pair<Item::Base, std::vector<Item::Base>>>();

        // Player selects items to take up to a certain limit
        std::vector<Item::Base> Take = std::vector<Item::Base>();

        // Player selects items to lose
        std::vector<Item::Base> ToLose = std::vector<Item::Base>();

        int Limit = 0;

        int LimitSkills = 0;

        Story::Type Type = Story::Type::NORMAL;

        // Handle background events
        virtual int Background(Character::Base &player) { return -1; };

        // Handle events before story branches
        virtual void Event(Character::Base &player){};

        // Jump to next section
        virtual int Continue(Character::Base &player) { return -1; };

        Base()
        {
        }

        Base(int id)
        {
            ID = id;
        }

        Base(int id, const char *text, Story::Type type)
        {
            ID = id;
            Text = text;
            type = type;
        }

        Base(const char *text, Story::Type type)
        {
            Text = text;
            type = type;
        }
    };

    std::vector<Button> StandardControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/exit.png", idx + 4, idx + 5, compact ? idx + 5 : 1, idx + 5, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ShopControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> SellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/selling.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BuyAndSellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/selling.png", idx + 5, idx + 7, compact ? idx + 6 : 1, idx + 6, startx + 6 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 7, "icons/exit.png", idx + 6, idx + 7, compact ? idx + 7 : 1, idx + 7, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> TradeControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::TRADE));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BarterControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/exhange.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::BARTER));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BarterAndShopControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/exchange.png", idx + 5, idx + 7, compact ? idx + 6 : 1, idx + 6, startx + 6 * gridsize, buttony, Control::Type::BARTER));
        controls.push_back(Button(idx + 7, "icons/exit.png", idx + 6, idx + 7, compact ? idx + 7 : 1, idx + 7, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ExitControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/exit.png", compact ? idx : idx - 1, idx, compact ? idx : idx - 1, idx, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }
} // namespace Story

class NotImplemented : public Story::Base
{
public:
    NotImplemented()
    {
        ID = -1;

        Title = "Not implemented yet";

        Controls = Story::Controls::NONE;
    }
};

auto notImplemented = NotImplemented();

auto Stories = std::vector<Story::Base *>();

void *findStory(int id)
{
    Story::Base *story = &notImplemented;

    if (Stories.size() > 0)
    {
        for (auto i = 0; i < Stories.size(); i++)
        {
            if (((Story::Base *)Stories[i])->ID == id)
            {
                story = (Story::Base *)Stories[i];

                break;
            }
        }
    }

    return story;
}

class Prologue : public Story::Base
{
public:
    Prologue()
    {
        ID = 0;

        Image = "images/coils-of-hate-cover.png";

        Title = "The Coils of Hate: Prologue";

        Text = "You are down on your luck, but you will not swallow your pride and look for a job. Every day a throng of hopefuls gathers outside the rich palazzi of the riverfront. Others seek to join a trader's caravan as a guide or guard. Those turned away drift at last to the seaweed-stinking waterfront to become rowers in the fleet and begin a life no better than slavery.\n\nIn your heart you know that your destiny, the destiny of a Judain, is greater than this. Not for nothing have you toiled to learn your skills. Now you are without peer among your people. One thing only you lack: a sense of pupose, a quest to show the world your greatness and put your skills to the test.\n\nThe city of Godorno is a stinking cess-pit. The Judain are not wanted here. Your people are rich but the pale ones of Godorno covet those riches. \"Usurers, thieves,\" they cry as your people walk the streets going about their daily business.\n\nThe Overlord stokes the fire of discontent. When those who speak out against his cruel reign disappear, never to be seen again, he blames the Judain. When people starve because he sells the harvest to the westerners for jewels and silks, his minions say it is the Judain who profit from his peoples' wretchedness. Now the people hate you and all your kind. Soon it will not be safe to walk the streets. The caravan lines are swelled by tall proud Judain slaves with their glittering black eyes, backs bent under casks of spices and bolts of silk.\n\nIn the past two centuries Godorno has become a byword for decadence, luxury and idle pleasure. Everywhere you look you see the insignia of the winged lion, once the proud standard of the city's legions. Now it stands as the very symbol of corruption and evil.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 1; }
};

class Story001 : public Story::Base
{
public:
    Story001()
    {
        ID = 1;

        Image = "images/vr-logo.png";

        Text = "Walk the streets you must, for there is no food and nothing to be gained from idling here in the hovel you call home. You push the rotten front door open gently. There is a wet cracking noise and it splinters, coming off its hinges. You jump past into Copper Street as it falls into the street and breaks. It is beyond repair.\n\nEven before you turn the corner of the narrow mired street a prowling thief, a sewer rat escaped from the fleet, is going into your home. Let him. You are carrying everything you own. He will find nothing but tick-ridden blankets and a leaking earthenware pot or two.\n\nAs you turn your back on the grey stone shacks of Copper Street a youth, gangling and pasty-faced, spits in your eye and calls out \"Judain scum.\" The boy is beneath notice. He sneers with his nose in the air, like the rich folk of the riverfront, but his sailcloth breeches are out at the knees. His father is probably a tanner or a tinker or some such.\n\nYour time in Godorno has taught you to ignore such insults.";

        Choices.clear();
        Choices.push_back(Choice::Base("You cannot stand this treatment any longer: round on him", 33));
        Choices.push_back(Choice::Base("Walk on, humbly wiping the spittle from your cheek", 48));

        Controls = Story::Controls::STANDARD;
    }
};

class Story002 : public Story::Base
{
public:
    Story002()
    {
        ID = 2;

        Image = "images/filler1.png";

        Text = "You run on, leaving your pursuers fifty yards or so behind, though looking back you see the youth running ahead of them. You hurtle into the square and attempt to lose yourself in a gathering throng. A large walled flowerbed encircles a rare sight. It is a greenbark treeh eighty feet tall. The smooth bark is striped lime green and grey-green and the heart-shaped leaves are golden yellow. There is a shrine here to the tree spirit with a few offerings of potash and wine.\n\nNext to the shrine is the town crier dressed in the traditional black and gold tabard. He unfurls a scroll and begins to declaim to the gathered crowd. He is flanked by a bodyguard of the Overlord's men armoured in black leather. You push forward to hear better.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 254; }
};

class Story003 : public Story::Base
{
public:
    Story003()
    {
        ID = 3;

        Text = "As nightfall approaches and a thunderstorm brews, you leave the road to find shelter in a copse of trees. But you are destined to sleep under better than a canopy of leaves -- hidden among the trees is a dilapidated cottage by a well. The dwelling's solid, green-tiled roof alone will mean you'll not get wet tonight.\n\nThe well is an even more welcome sight; you have fled Godorno ill-prepared and have travelled most of the day without a single drink. Drawing water from the well, you drink deeply.\n\nOn entering the rude shelter, you find it is empty but largely clean, with no signs of recent habitation by men or animals. Making yourself as comfortable as you can on the hard-packed earth floor you settle down to sleep.\n\nWhen you awake in the morning, however, you feel strangely feverish. The trials of your journey might have been too much for you and perhaps you have sunstroke. Or did you dehydrate too much, and that refreshing drink come too late? There again, perhaps the water from the well is tainted, though to you it was as sweet as honeyed wine upon thetongue.\n\nSuch thoughts plague your mind as you sink deeper into delirium, restlessly tossing and turning on the cottage's floor. A kind of madness possesses you, and you are sure that several times you run out into the copse in search of food, grasping at and eating anything that seems remotely edible. How many days must you be gripped by the coils of madness that threaten to destroy your mind and body?\n\nYou LOSE 2 Life Points.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }

    int Continue(Character::Base &player) { return 15; }
};

class Story004 : public Story::Base
{
public:
    Story004()
    {
        ID = 4;

        Image = "images/avenue-of-skulls.png";

        Text = "The road leading up to Greenbank Plaza has been renamed the Avenue of Skulls. At regular intervals posts have been erected from which iron cages swing. Inside the cages are executed Judain. Hundreds have been slain. The smell of rank corruption has drawn clouds of flies. Nearby you hear the clang of a bell and a dolorous voice calling, \"Bring out your dead. Bring out your dead.\"\n\nThe plague has struck Godorno like a ravaging scourge. No respecter of a man's station, it has carried off nobleman and beggar alike. The streets have not been swept for what must have been weeks.  Refuse is piling up in drifts in the wind. There is a blank look of despair on the faces of the people you pass and even the guards seem too preoccupied to notice a Judain. The sun is drawing the humours from the city like the fumes from a witch's kettle by the time you turn the corner into Copper Street.\n\nYou return to the hovel which you used to call home. You can use it as a base to see if you can contact some of your fellow Judain and learn what has taken place in the city. The old door has been broken up and used for firewood. There is nobody and nothing in the hovel -- but did you hear voices from beneath the trap door that leads to the hidden cellar?";

        Choices.clear();
        Choices.push_back(Choice::Base("Fling the trap door open", 61));
        Choices.push_back(Choice::Base("Knock first", 46));

        Controls = Story::Controls::STANDARD;
    }
};

class Story005 : public Story::Base
{
public:
    std::string PreText = "";

    bool SURVIVED = true;

    Story005()
    {
        ID = 5;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Hate shrieks -- a cry of insensate fury as it sees you charging back to slice at it with your enchanted blade. In a welter of carnage, you and your monstrous foe lock in mortal combat. The green-tinted metal of your blade chops deep into Hate's soft purulent flesh, while its tentacles slap into you with stunning force. Those baleful green eyes gleam with a new emotion now - not hatred and unreasoning violence, but the liquid gleam of fear. Hate knows that it is going to die today.\n\nBut it sells its life dearly.\n\n";

        auto DAMAGE = -9;

        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            DAMAGE = -6;

            PreText += "[CHARMS] Your magic gives you some protection. ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        SURVIVED = true;

        if (player.Life <= 0)
        {
            SURVIVED = false;

            player.Life = 1;
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (SURVIVED)
        {
            return 416;
        }
        else
        {
            return 17;
        }
    }
};

class Story006 : public Story::Base
{
public:
    Story006()
    {
        ID = 6;

        Text = "You spend much of the day poring over your battle plans with the heads of the resistance. Not only other Judain have rallied to your cause. Now you have many people who have equally good cause to fightthe Overlord -- those whose families have been starved by his harsh taxes or abused by his brutish soldiers.\n\nSome time after noon, as you are explaining the tactics for the final pitched battle to decide the fate of the city, a little street urchin brings news that Lucie's house has collapsed. She is feared dead.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go to see if you can do anything", 210));
        Choices.push_back(Choice::Base("Carry on making your plans for the battle", 195));

        Controls = Story::Controls::STANDARD;
    }
};

class Story007 : public Story::Base
{
public:
    Story007()
    {
        ID = 7;

        Text = "On your way to meet Lucie the next day, you notice bushels of red flowers bobbing on the surface of the Circle Canal and wander over to the edge to look. On closer inspection they look like pieces of meat. An uneasy feeling steals over you as you realize they are human hearts, hundreds of them, bobbing on the surface, waiting for the carrion crows. These cannot be the hearts of the slaughtered Judain, for your people hang in iron cages and their chests are still intact.\n\nWhen you arrive at the Garden of Statues, Lucie is there, looking as pretty as ever. She pretends not to have seen you and walks down the deserted street towards a dog-handler who has a gigantic deerhound straining at a leash. Perhaps Lucie doesn't want to give you away, in which case she is being very streetwise. You can stay hidden here but the dog seems to have picked up your scent and barks excitedly. What is it that makes bloodhounds bark so? Is the dog already imagining sinking his teeth into soft manflesh?\n\nLucie may have some plan.";

        Choices.clear();
        Choices.push_back(Choice::Base("Wait to see what she does", 27));
        Choices.push_back(Choice::Base("Break cover and walk out into the street", 39));

        Controls = Story::Controls::STANDARD;
    }
};

class Story008 : public Story::Base
{
public:
    Story008()
    {
        ID = 8;

        Text = "The brigands strip you of everything useful and ride off down the trade road, leaving you nothing. There is much mirth at your plight and a certain amount of cursing that you are so poor. \"This one's gear will hardly pay for the horseshoe metal we wasted in the chase,\" grumbles one of them.\n\nYou have LOST ALL your MONEY and POSSESSIONS.\n\nIt is obvious these men will forget about you as soon as you are out of sight, just another victim on the road. At least they haven't harmed you.\n\nYou are more fortunate later, however. Your journey to Bagoe on the Palayal river is charmed. You find food dropped in a sack by the side of the path and are treated to a beer at an inn. At Bagoe you are welcomed aboard a barge and the bargees promise to hide you when you near Godorno. They say you will easily be able to slip ashore, unseen, in the dead of night.\n\nThey are as good as their word and one fine dawn you find yourself back in Godorno, with the wharfs and warehouses behind you and the city befqre you. The revetments of the buildings lend the city an unmistakable air of patrician hauteur. This is the hub of the civilized world.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ALL(player);
    }

    int Continue(Character::Base &player) { return 300; }
};

class Story009 : public Story::Base
{
public:
    Story009()
    {
        ID = 9;

        Text = "The centre of this corridor has a series of holes covered by metal grilles down its length. The stench of human decay rises from each of them. These are the oubliettes: holes which prisoners who have lost the power to entertain under torment are thrown down. They are forgotten there and left to rot.\n\nThis whole place fills you with horror at man's inhumanity to his fellow man. Your heart flutters at the thought of the plight of the Judain who are locked away here. You only hope they are not down the oubliettes.\n\nThere is a loud slurping noise from another corridor. A waft of sweet cloying scent like roses and honeysuckle bathes you. Is that the monster Hate advancing to claim you and draw you in to the orgy of despair? How are you going to face up to Hate in all its majestic horror? You are just one poor Judain, about to go the way of so many of your kind. A heavy squelching and rubbing, like chafing rubber, announces that Hate is about to turn the corner before you. You decide better of facing Hate alone and flee down a side corridor.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 72; }
};

class Story010 : public Story::Base
{
public:
    Story010()
    {
        ID = 10;

        Text = "You speak the word of power and throw your handswide in a dramatic gesture that releases the power of the planes beyond. There is a whoof and a cloud of thick green fog fills the room. There are no windows and the door is shut behind you. There is no escape. The occult fog is killing the snakes but it is also causing you to retch with nausea and you fall onto the serpents which writhe beneath you and sink their envenomed fangs into your soft flesh. The poison of the garter snake is virulent indeed and you are soon dead. There is no one left to save the Judain now.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story011 : public Story::Base
{
public:
    Story011()
    {
        ID = 11;

        Text = "The black plume sways as the Jade Warrior swivels its head to observe you closely, brandishing its sword as it does so. By chance you have chosen to attack the leader. It clicks and whirrs ominously as it advances to do battle. Its SWORD has a halo which glows more strongly than the others. You manoeuvre behind the Jade Warrior and throw yourself against its sword arm, wrenching the BLADE from its armoured grasp.\n\nThere seems to be a mind inside the SWORD itself, prompting you to issue orders to the Jade Warriors. \"Obey me!\" you cry out.\n\nTo your relief and amazement they line up before you and stand to attention. The warrior from whom you robbed the sword picks up another from behind an awning. The warriors are ready to do your bidding. They whirr and click as they follow you dutifully to the edge of the precincts of the burial chambers, and there they grind to a halt. There is nothing you can do to move them further. Although you cannot command the Jade Warriors to go forth and attack Hate, you tell them that they must attack Hate if it should loop its coils into the burial chambers of the Megiddo dynasty. You leave all doors and traps wide open in the hope that Hate will blunder in and get carved up.\n\nSure enough, when you return the next day the place shows the signs of an epic battle. Great gouts of translucent flesh hang from lintel and corners. There is a fine green powder in the air, like pulverized glass. The Jade Warriors have been ground to dust by Hate but, judging by the quantity of purple ichor smeared over the walls, they must have given the monster acute indigestion.\n\nYou OBTAINED a JADE WARRIOR's SWORD. You gained the codeword HECATOMB.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::JADE_WARRIORS_SWORD});

        Character::GET_CODEWORDS(player, {Codeword::Type::HECATOMB});

        Take = {Item::PLUMED_HELMET};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 174; }
};

class Story012 : public Story::Base
{
public:
    Story012()
    {
        ID = 12;

        Image = "images/melmelo.png";

        Text = "Melmelo has his major-domo, a tall, stooping man with a wooden leg, show you into his snug. Doubtless this man lost his leg doing a job for Melmelo and has been rewarded by the sinecure of becoming the guildmaster's senior servant. The snug is a comfortable little wood-panelled room lined with bookcases and trophies picked up from the villas of the nobility. It is one of the smallest rooms in what must be one of the grandest villas in the city. Melmelo is very rich.\n\nHe is a small shrewd-looking man, missing his left little finger and just beginning to lose his greying hair. He is dressed simply and you are reasonably sure he is not armed. You can hear the major-domo working in the garden; the stub of his wooden leg thumps on the flagstones of the garden path. He is too far away to help Melmelo should you attack him. Melmelo looks quite relaxed. He doesn't seem either prepared for or worried about trouble.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take advantage of Melmelo's apparent helplessness and kill him", 258));
        Choices.push_back(Choice::Base("Ask him if he can think of a way of vanquishing Hate", 78));

        Controls = Story::Controls::STANDARD;
    }
};

class Story013 : public Story::Base
{
public:
    Story013()
    {
        ID = 13;

        Text = "\"You'll burn in hell for this, Judain scum, for all eternity. You'll join me here in the swamp of Hate. You'll rue the day you wouldn't offer a helping hand to an old soldier...\"\n\nHe breaks off and moans in despair. His flesh is mottled horribly and a gaping wound on his neck seems to have the pus of Hate oozing into it rather than his own fluids leaking out. You could never describe the horror of seeing these lost souls in their degradation. All you can do is try to keep hold of your sanity. You close your ears to the sounds of torment and walk on.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 9; }
};

class Story014 : public Story::Base
{
public:
    std::string PreText = "";

    Story014()
    {
        ID = 14;

        Image = "images/filler1.png";

        Choices.clear();
        Choices.push_back(Choice::Base("Go back down the road you travelled from Godorno", 85));
        Choices.push_back(Choice::Base("Cut across country towards the Palayal river", 155));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You leave the road and head into the rich farmlands that lead towards the valley of Burg and the great forest beyond. These green hills and dales with their farmsteads, mills and vineyards are the breadbasket of the decadent city of Godorno.\n\nSoon after dawn the next day you pass a Judain shrine -- white marble arches hung with creepers, set up on a hillside. Inside the shrine, which hasn't been visited for some time, you find the holy book of teachings, The Songs of Suleiman, which tells of the Judain's flight from captivity and their search for the Promised Land. It is full of the most marvellous stories of heroism in the face of stark adversity. The stories of your noble people lift up your heart and give you the strength to dare to be a hero and strive to be the saviour of the Judain. The understanding you gain here in this shrine means you will never nurture hate in your heart.\n\nYou linger at the shrine and go on reading until the failing light tires your eyes. When you awaken in the morning you begin reading again, and the cycle of waking, reading and sleeping continues until you have absorbed every word of the holy book. Time for you has passed quickly, but after you have finished the book you realize that you have been at the shrine for more than a week, your body sustained only by the knowledge you have learned.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYour mind is made up. You will go back to Godorno to try to save your people. Turning your back on the bucolic dales and farmsteads is easy when you travel with a light heart. You will live to be a hero or perish in the attempt. Nothing can shake your resolve.\n\nYou gained the codeword SATORI.";

            Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});
        }

        Text = PreText.c_str();
    }
};

class Story015 : public Story::Base
{
public:
    std::string PreText = "";

    Story015()
    {
        ID = 15;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "After several days -- or could it be weeks? -- your ravaged body throws off the disease. You are greatly weakened, but the desire to leave this wretched hovel motivates your limbs into motion and you stagger back to the road.";

        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            PreText += "\n\nYour [AGILITY] skill is LOST.";

            Character::LOSE_SKILLS(player, {Skill::Type::AGILITY});
        }

        PreText += "\n\nThrowing caution to the wind you continue alone on the road until you see a cloud of smoke or dust on the road ahead.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            return 22;
        }
        else
        {
            return 35;
        }
    }
};

class Story016 : public Story::Base
{
public:
    Story016()
    {
        ID = 16;

        Text = "You turn tail and flee from the Jade Warriors, but on your way out you fall foul of a trap that stabs your thigh with a broken-off spear shaft.\n\nYou LOSE 1 Life Point.";

        Bye = "You pull the shaft out. The blood wells forth ominously; you are lucky it didn't sever an artery. You hobble back to your bolt-hole on Bumble Row and lie down to recuperate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 20; }
};

class Story017 : public Story::Base
{
public:
    Story017()
    {
        ID = 17;

        Text = "At the last, you seem to hear a high-pitched uncanny whispering coming from Hate's black maw. As it shudders in its death throes and you sink into the oblivion of death, you imagine that you hear its words: \"To the last I grapple with thee, Judain. From hell's heart I stab at thee. For Hate's sake I spit my last breath at thee!\"\n\nIt pulls you close to its rancid maw as the two of you die. But you have died a true hero's death, bringing salvation to the city of your birth. In days to come, when Godorno is rebuilt, a statue will be erected to honour your memory. You have triumphed.";

        Type = Story::Type::HERO_DEATH;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.Life = 0;
    }
};

class Story018 : public Story::Base
{
public:
    Story018()
    {
        ID = 18;

        Text = "The spell works for you here, even in the bright sunlight, and you slink back down the road unseen. The brigands, coarse looking hard-bitten men and women, linger to steal everything they can pillage from the farmsteads on either side of the road. They start to set fire to the farmsteads in an orgy of looting so you retrace your steps towards the city of Godorno, content for fate to steer you back towards less immediate but greater danger.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story019 : public Story::Base
{
public:
    Story019()
    {
        ID = 19;

        Text = "In the morning, you reach under your pack for your SWORD only to find the scabbard empty. Your trusty blade is nowhere to be seen. The other Judain are all out somewhere, probably foraging for supplies. But who has stolen the SWORD on which you depend?\n\nYou will have to go out without it for you promised to meet Lucie to see if she has any news for you, down by the Garden of Statues. It is most odd that someone has stolen your SWORD. You had thought you were among friends here. It is an easily recognizable SWORD, anyone using it cannot hide the fact they are a thief. There is nothing you can do about it now, so you set out to meet Lucie.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 7; }
};

class Story020 : public Story::Base
{
public:
    Story020()
    {
        ID = 20;

        Text = "You resolve to enter the prison fortress of Grond. Once there, you can free the captured Judain and other political prisoners detained to await the mercy of the Overlord's torturers. But you cannot succeed at such an ambitious mission alone, and you are unwilling to put your fellow Judain at further risk. They are brave enough, but to get inside the prison you will need the help of an expert rogue.";

        Choices.clear();
        Choices.push_back(Choice::Base("Pay a visit to your mulatto friend, Mameluke, who has been useful to you in the past", 303));
        Choices.push_back(Choice::Base("Call on the little gamine Lucie", 293));

        Controls = Story::Controls::STANDARD;
    }
};

class Story021 : public Story::Base
{
public:
    std::string PreText = "";

    Story021()
    {
        ID = 21;

        Image = "images/filler2.png";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your ploy works. The lasso catches Tormil's leg and with the help of some bystanders you are able to drag him free.\n\n\"Why do we help him?\" asks one of the men as he releases the rope. \"The Overlord's men treat us like cattle!\"\n\n\"True, he has earned our hatred,\" you say. \"But now, see, he deserves our pity.\" \n\nTormil weeps over the body of his daughter, past saving in the body of the monster. You creep away while he mourns.";

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::VENEFIX);
        }
        else
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});

            PreText += "\n\nYou gained the codeword SATORI.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story022 : public Story::Base
{
public:
    Story022()
    {
        ID = 22;

        Text = "You realize that the cloud of dust is thrown up from the hoofs of horses being ridden fast. You take cover in the bushes beside the road - a prudent move which conceals you from the brigands who soon go thundering past. Obviously the trouble in Godorno has led to lawlessness in the surrounding countryside. If you venture further you have a good chance of simply being slaughtered for the clothes on your back. On the other hand, if you return to the city you might at least sell your life dearly in the Judain cause.";

        Choices.clear();
        Choices.push_back(Choice::Base("Strike out into the depths of the forest", 14));
        Choices.push_back(Choice::Base("Risk returning to the gates of Godorno", 188));

        Controls = Story::Controls::STANDARD;
    }
};

class Story023 : public Story::Base
{
public:
    Story023()
    {
        ID = 23;

        Text = "The wind whistles, causing the miserable wailing of the gargoyles to roll around you as the air streams through the holes in their faces. This is going to be a very dangerous climb.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 50, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            Choices.push_back(Choice::Base("Otherwise", 203));
        }
    }

    int Continue(Character::Base &player) { return 50; }
};

class Story024 : public Story::Base
{
public:
    Story024()
    {
        ID = 24;

        Text = "You step gingerly onto the carpet and the gold and silver filigree threads seem to bunch and tighten beneath the balls of your feet. The Overlord stops breathing for a moment and you copy him. Then he rolls over and the stertorous noise starts again. In his sleep his hand caresses the girl's flank, but she doesn't wake. You take another step and then struggle to make another, but the wires have snared around your ankle. The slender metal thread is cutting into your skin like a cheesewire. Cursing, you bend to free yourself. It should be easy enough to get free before the wire cuts through your leg.\n\nYour sixth sense alerts you to a louring presence somewhere above, a presence that broods, heavy with hate. You dart a look upwards at the canopy of the Overlord's bed.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 62; }
};

class Story025 : public Story::Base
{
public:
    Story025()
    {
        ID = 25;

        Text = "The guard squeezes your hand fiercely and tries to heave himself out of Hate's soft embrace. You are drawn towards the purple flesh as the guard, driven to feats of great strength by terror, pulls on you for all he is worth. His face is as purple as Hate as he exerts a great effort and you are dragged into the translucent flesh of the monster. You have joined the orgy of despair and the poor guard who dragged you in cannot escape. He is exhausted. You must lie together, like eggs in a basket, as Hate goes on devouring lost souls. There is no one left to save the Judain now. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story026 : public Story::Base
{
public:
    Story026()
    {
        ID = 26;

        Text = "You were a fool to return to the Inn of the Inner Temple. Skakshi's friends seize you when you go to the latrines. Your last sight is of the knife protruding from your heart as you die face down in the puddles of urine mingling with your own blood. You have failed to save the city from Hate.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story027 : public Story::Base
{
public:
    Story027()
    {
        ID = 27;

        Text = "Lucie gives a sweetmeat to the dog which wolfs it down and then starts to nuzzle the pocket of her dress for more. The dog-handler leers at the pretty young girl.\n\nYou walk out into the street and the dog notices you right away, giving vent to the sighting cry -- a series of short urgent barks which sound like \"Look there, look there, look there.\" The dog-handler sees you and slips the dog off the leash and runs towards you, drawing his SWORD. Lucie sticks out her leg and trips him. He goes sprawling flat on his face in the muddy gutter, his SWORD clattering towards you across the cobbles. The dog stops still with its tail down.";

        Choices.clear();
        Choices.push_back(Choice::Base("Make a dash for the SWORD", 124));
        Choices.push_back(Choice::Base("Go to Lucie's help without delay", 75));

        Controls = Story::Controls::STANDARD;
    }
};

class Story028 : public Story::Base
{
public:
    Story028()
    {
        ID = 28;

        Text = "Your senses have been honed razor-keen by your many escapades on the hazy edge of the law. When a thief treads lightly on the steps leading down to your cellar hideout, you are instantly awake and on your feet. A figure stands in the shadows. Snatching up your SWORD, you call for the intruder to stay where he is. His response is to turn and bolt away. You chase him up to the street, but he is already out of sight. Your only impression was of a small build and very quick reflexes. You must be on the look-out for such a person.\n\nYou go back to your lair and spend the rest of the night undisturbed.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 7; }
};

class Story029 : public Story::Base
{
public:
    Story029()
    {
        ID = 29;

        Text = "After a perilous exploration to find the best way up, you mount the tower. Your fingers clutch into the cracks between the massive stone blocks, and you use the ivy to help you climb. Your gasps of breath are drowned by the whistle and roar of the wind as it claws at the jutting masonry so far from the ground.\n\nAt last, a hundred feet up, you reach a set of steps winding round the outside of the tower. There is no balustrade and the steps are no more than a foot wide, winding in a spiral up the outside of the tower. There is nothing at all to hold on to.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to walk up the steps", 50));
        Choices.push_back(Choice::Base("Crawl up the steps", 23));
        Choices.push_back(Choice::Base("Give up and leave the tower", 172));

        Controls = Story::Controls::STANDARD;
    }
};

class Story030 : public Story::Base
{
public:
    Story030()
    {
        ID = 30;

        Image = "images/concubine.png";

        Text = "The Overlord lies beside his concubine, the silk sheets disturbed by his restless tossing and turning. The back of the girl is towards you and her fair pale skin is disfigured by what look like vile purple birthmarks that are weeping a clear yellowish fluid and puckered at the edges. She seems to be sleeping the sleep of the damned. He is breathing stertorously and twitching occasionally, while she is as still as death. The smell of putrefaction is here just as it pervades and penetrates the whole city.\n\nThe richness of the wall-hangings, furniture and pictures, ransacked and taxed from the old nobility, have been placed and hung without taste.\n\nThe Overlord lies there at your mercy. Will you avenge the terrible suffering of your fellow Judain, or carry off the concubine so that you can question her and find out what is happening to the city and its Overlord?";

        Choices.clear();
        Choices.push_back(Choice::Base("Get to the bed", 40));
        Choices.push_back(Choice::Base("You would rather accept discretion as the better part of valour and make a run for it", 161));

        Controls = Story::Controls::STANDARD;
    }
};

class Story031 : public Story::Base
{
public:
    Story031()
    {
        ID = 31;

        Text = "You cling to the axles of a slaver's cart in the mews of Slave Market Plaza and let yourself fall, unnoticed, to the cobbles as it turns a corner. Next you pick your way through a maze of old alleyways, built soon after this part of the city was razed to the ground in the Great Fire of two thousand years ago. You are soon looking at the doors of the Inn of the Inner Temple.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 63; }
};

class Story032 : public Story::Base
{
public:
    Story032()
    {
        ID = 32;

        Text = "You have made the right choice. Skakshi cannot get past your guard as your BLADE cuts through the air. He is becoming increasingly desperate. \"Impossible...\" he gasps, face twisted into a look of fury. \"You must be cheating -- using some Judain sorcery to aid you!\"\n\nYou are about to step up the tempo of your attack when he throws down the club and tries to make a run for the door.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cut him down", 36));
        Choices.push_back(Choice::Base("Let him escape", 43));

        Controls = Story::Controls::STANDARD;
    }
};

class Story033 : public Story::Base
{
public:
    Story033()
    {
        ID = 33;

        Image = "images/filler1.png";

        Text = "You spin on your heel. The fierce look of anger on your face makes the boy step back in fear, but he is used to treating your kind with scorn. He recovers himself.\n\n\"Judain scum, your kind aren't wanted here.\"\n\nHe pulls a tanner's knife from his pocket. It is long, sharp and menacing.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SWORDPLAY] Break the law of Godorno by unsheathing your sword here in the street", 56, Skill::Type::SWORDPLAY));
        Choices.push_back(Choice::Base("Use [UNARMED COMBAT]", 92, Skill::Type::UNARMED_COMBAT));
        Choices.push_back(Choice::Base("Rely on [STREETWISE]", 99, Skill::Type::STREETWISE));
        Choices.push_back(Choice::Base("[CHARMS] There is no time to cast a spell, but you have an AMULET", 112, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("You had better run", 130));

        Controls = Story::Controls::STANDARD;
    }
};

class Story034 : public Story::Base
{
public:
    std::string PreText = "";

    Story034()
    {
        ID = 34;

        Choices.clear();
        Choices.push_back(Choice::Base("Return to Bumble Row and ponder what to do next", 6));
        Choices.push_back(Choice::Base("Return to Grond to free more of the guards and prisoners", 311));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "";

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::VENEFIX);
        }
        else
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});

            PreText = "You gained the codeword SATORI.\n\n";
        }

        PreText += "As soon as they are outside the gates of Grond, the freed guards flee. They are leaving the city taking only what they can grab as they run. This is the most sensible option and a very tempting one for you.";

        Text = PreText.c_str();
    }
};

class Story035 : public Story::Base
{
public:
    Story035()
    {
        ID = 35;

        Text = "The cloud of dust is coming closer and when it is no more than a quarter of a mile away you begin to make out the figures of several horsemen. They are moving at a fast trot, faster than merchants or most other travellers. They could be brigands.";

        Choices.clear();
        Choices.push_back(Choice::Base("Flee back towards the city of Godorno, hoping to elude them until nightfall", 44));
        Choices.push_back(Choice::Base("Stand your ground, greet them, and offer to throw in your lot with them", 64));

        Controls = Story::Controls::STANDARD;
    }
};

class Story036 : public Story::Base
{
public:
    std::string PreText = "";

    Story036()
    {
        ID = 36;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::IMPASSE});

        PreText = "You gained the codeword IMPASSE.\n\nYou cut Skakshi down in a welter of blood, wipe your BLADE on a barcloth, and replace it in its scabbard before looking round you once more.\n\nAll is quiet in the Inn of the Inner Temple. No one will meet your eye. They stare at Skakshi's corpse, shocked at the sudden violence you have done to one of their comrades. You don't expect any trouble from them after that demonstration. Nor will you make many friends here. You feel Skakshi's pockets, quickly finding a concealed flap in which you discover a set of THROWING KNIVES.\n\nYou look up from the body. One man gives you a narrow glare and spits on the floor. You won't make any friends here so you decide to go back to your lair on Bumble Row.\n\nIn your heart you know that you did not have to kill Skakshi. Perhaps you are beginning to succumb to the general hysteria and hatred that seems to be infetting most others in the city?";

        Take = {Item::THROWING_KNIVES};

        Limit = 1;

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::SATORI);
        }
        else
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::VENEFIX});

            PreText += "\n\nYou gained the codeword VENFIX.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 214; }
};

class Story037 : public Story::Base
{
public:
    Story037()
    {
        ID = 37;

        Image = "images/filler2.png";

        Text = "You know from expenence that the dust cloud is raised by a group of riders riding at a canter. They will overtake you within half an hour.";

        Choices.clear();
        Choices.push_back(Choice::Base("Hide in one of the farms until they pass", 69));
        Choices.push_back(Choice::Base("Choose a place to ambush them in case they are the Overlord's men", 82));

        Controls = Story::Controls::STANDARD;
    }
};

class Story038 : public Story::Base
{
public:
    Story038()
    {
        ID = 38;

        Text = "People turn to stare as you run past and then take up the hue and cry as they are engulfed by the mob that pursues you. You run on, your lungs beginning to hurt. They are not closing but you don't know how much longer you can keep going like this. Every time you see a likely place to hide there seems to be someone else there. You turn a corner and run on in the direction of the main gate where the trade road enters the city. Behind you can hear the sound of hoofs on the cobbles. A squadron of the Overlord's cavalry is giving chase. Ahead there is a drinking house, outside is a HORSE tethered to a post.";

        Choices.clear();
        Choices.push_back(Choice::Base("Steal the HORSE", 237));
        Choices.push_back(Choice::Base("Hide in the drinking house", 255));

        Controls = Story::Controls::STANDARD;
    }
};

class Story039 : public Story::Base
{
public:
    Story039()
    {
        ID = 39;

        Text = "You are not scared of a mere dog. You walk out from hiding nonchalantly enough but the dog is at you in a trice.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::SWORD}))
        {
            return 68;
        }
        else
        {
            return 57;
        }
    }
};

class Story040 : public Story::Base
{
public:
    Story040()
    {
        ID = 40;

        Text = "As you pad quietly towards the Overlord;s bed the candles flicker in a gust of wind. Far off you can hear the baying of his hunting dogs in their kennels. Farther off still the wind carries the moans and screams of the unfortunates in Grond.\n\nThe Overlord's bed is set on a rich ruby-red carpet with intricate patterns of gold and silver thread woven into it. There are signs and sigils, perhaps magical wards.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            Choices.push_back(Choice::Base("Walk quietly across the carpet to the concubine's side", 24));
            Choices.push_back(Choice::Base("Jump straight onto the bed so your feet don't touch the carpet", 98));
        }
    }

    int Continue(Character::Base &player) { return 135; }
};

class Story041 : public Story::Base
{
public:
    Story041()
    {
        ID = 41;

        Text = "You pass a troubled night in your lair and wake listening to the chittering of the rats that flourish as the city becomes a slum. You feel better for the rest and wake refreshed.\n\nYou RECOVER 2 Life Points.\n\nYou wash in cold water and plan what to do on this grey morning. There is only one course of action left to you. You will have to attack Hate itself and vanquish it utterly if you are to save your people.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 2);
    }

    int Continue(Character::Base &player) { return 272; }
};

class Story042 : public Story::Base
{
public:
    Story042()
    {
        ID = 42;

        Text = "There is a whoof as a thick cloud of smoke explodes around you. You grope your way through the smoke towards the Jade Warriors. One of them looms towards you, the light gleaming dully now off its facets and its sword is working mechanically. You recoil in fright but it lumbers past you making elaborate passes in the air, as if engaged in a display of an ancient style of swordplay. The others are also lurching about at random. The smoke seems to have scrambled their senses. Each is cutting and thrusting at the air around it but they seem oblivious of you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE) && !Character::VERIFY_ITEMS(player, {Item::Type::BOOK_OF_MYTHS_AND_LEGENDS}))
        {
            return 133;
        }
        else
        {
            return 119;
        }
    }
};

class Story043 : public Story::Base
{
public:
    Story043()
    {
        ID = 43;

        Text = "Skakshi slams the door as he goes and the other drinkers follow without so much as a glance in your direction. They do not dare to share the drinking hall of the Inn of the Inner Temple with you. You have made no friends here and you won't get a meeting with Melmelo now. He will hear everything that has happened here and he is not an easy man to find and get to talk to.\n\nThe landlord stoops to pick up the spiked club which still has congealed blood sticking to it from the last time it was used and puts it back behind the bar.\n\nYou gained the codeword COOL.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::COOL});
    }

    int Continue(Character::Base &player) { return 214; }
};

class Story044 : public Story::Base
{
public:
    Story044()
    {
        ID = 44;

        Image = "images/filler3.png";

        Text = "Your steady run keeps you out of their clutches but you are already in sight of the city of Godorno once more. They seem intent on chasing you back as far as the city walls. Perhaps they mean to sneak into the city to rob the cityfolk, but they will not find it easy to pass through the city gates.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        Choices.push_back(Choice::Base("Change your mind about fleeing and offer to throw your lot in with them", 64));

        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            Choices.push_back(Choice::Base("Keep running and hide in the city once more", 188));
        }
        else
        {
            if (Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
            {
                Choices.push_back(Choice::Base("(ELFIN BOOTS) Keep running and hide in the city once more", 188, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            }
            else
            {
                Choices.push_back(Choice::Base("Keep running and hide in the city once more", 76));
            }
        }
    }
};

class Story045 : public Story::Base
{
public:
    Story045()
    {
        ID = 45;

        Text = "You also manage to free two hundred of the grateful guards who cannot believe their luck. They wipe themselves off along the walls. Most of them look as if they are in shock. They shouldn't give you too much trouble. You are more likely to face trouble from the Judain you have set free. They can see their tormenters among them and they want to take their revenge. \"Now die, dogs, die slowly and in pain!\" they cry. \"Let us see how you like to be put to the torture. Kill them! Heat the irons and warm their vitals.\" The Judain are near hysterical and they begin to slaughter the guards out of hand, while others try to drag some of them back to the torture chambers. The guards are petrified.\n\nWill you stop the slaughter by killing one of your fellow Judain? In the heat of the moment there is no time for finesse, and your people are behaving no better than savage beasts who have lost all control.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stop the slaughter", 269));
        Choices.push_back(Choice::Base("Let your people take their natural revenge", 348));

        Controls = Story::Controls::STANDARD;
    }
};

class Story046 : public Story::Base
{
public:
    Story046()
    {
        ID = 46;

        Image = "images/caiaphas.png";

        Text = "You tap on the door, then kneel and place your ear to the planking to hear what goes on beneath. You can hear men whispering. They must fear you are one of the Overlord's men. You call out quietly your name, and that you are Judain. At last you persuade them to open the trap door. Down in the cellar are three families hiding from the Overlord's butchers. There is a big man whom you recognize as Caiaphas, the rabbi at the synagogue before it was torn down. He carries a rusty old spear which he casts aside as soon as he sees you.\n\n\"Caiaphas, old friend,\" you say in greeting. \"What has come to pass here? Why do all our people cower below ground like rats?\"\n\nCaiaphas looks sombre and one of the women starts to cry as he tells the story in a rumbling basso voice which would be most impressive were he not cowering in a damp cellar.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 71; }
};

class Story047 : public Story::Base
{
public:
    Story047()
    {
        ID = 47;

        Image = "images/filler2.png";

        Text = "You never retire for the night without first casting a charm to watch over you while you sleep, keeping you safe from thieves and nocturnal predators. In the small hours, a high ringing chime resounds through your dreams, bringing you instantly awake. You look around. You can see nothing in the darkness. Eventually the feeling of danger passes and you drift off back to sleep.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 330; }
};

class Story048 : public Story::Base
{
public:
    Story048()
    {
        ID = 48;

        Text = "The youth is not content to leave it there. He means to draw blood. He closes stealthily and is about to stab you. His shadow falls across you before the blow is struck.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [STREETWISE]", 99, Skill::Type::STREETWISE));
        Choices.push_back(Choice::Base("Use [UNARMED COMBAT]", 92, Skill::Type::UNARMED_COMBAT));
        Choices.push_back(Choice::Base("There is no time to draw a SWORD or use SORCERY: you must run for it", 130));

        Controls = Story::Controls::STANDARD;
    }
};

class Story049 : public Story::Base
{
public:
    Story049()
    {
        ID = 49;

        Text = "You find the librarian outside the building, staring at a glimmering pile of ashes. As you go closer, you see that someone has piled up the books of the library and torched them. The librarian falls to his knees, overcome with distress. \"They burned my books!\" he groans, tears running into his beard. \n\n\"Who did? And why?\" you ask.\n\n\"The Overlord's men. They said that knowledge was the enemy oflaw and order. They claimed that lies had been written in the books by Judain authors. Oh, such a waste...!\"\n\nThere is no chance now of finding more about Hate from the writings of ancient scholars; you may not visit the library again should you be given the option. You wonder if the Overlord has truly gone mad.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story050 : public Story::Base
{
public:
    Story050()
    {
        ID = 50;

        Text = "Walking is better than crawling. On a difficult climb you should keep three holds, using your hands and feet, on what you are climbing at all times. If you do this you will succeed in all but the most difficult of climbs. The wind is whipping around you, however, and the baleful wails of the gargoyles seem destined to make you falter and tumble to your death.\n\nIt is slow going and you have to force yourself not to look down, but step by step you edge around to the corner. But what if there is something round there waiting to attack you?";

        Choices.clear();
        Choices.push_back(Choice::Base("Decide you cannot manage the tower and return to the ground", 172));
        Choices.push_back(Choice::Base("Press on", 304));

        Controls = Story::Controls::STANDARD;
    }
};

class Story051 : public Story::Base
{
public:
    Story051()
    {
        ID = 51;

        Text = "Tarkamandor tells you he has decided to quit the city. \"Matters have gone too far,\" he says. \"Each day I fear the guards will come to drag me off to Grond.\"\n\n\"Why should you fear?\" you say with a trace of bitterness. \"You are not Judain.\"\n\nHe gives a snort of ironic laughter. \"Do you think that what has been going on is a simple matter of persecution? It goes deeper than that. The Overlord started his attacks on your people to distract attention from his disastrous policies, reasoning that once the populace had a scapegoat to blame they would be easier to control.\"\n\n\"That strategy has worked well, them\"\n\n\"Now it is out of control! Hate is rife in the city. It extends its influence like a cancer. Today it is you Judain who are marched off to the prison. Tomorrow it may he the aged, or the infirm, or those who dare to speak out against the Overlord. That's why I'm leaving.\" He takes a few more steps, the wheels of his cart sloshing through the rut of mire in the middle of the street, then pauses and looks back. \"As long as I'm going, I suppose I ought to sell some of my stock. Are you interested?\"\n\nHe has a HEALING SALVE which can be used once at any time except when in combat; it will RESTORE ALL LOST Life Points. Another item on the cart is a pair of ELFIN BOOTS which grant their wearer one use of the AGILITY skill and MUST THEN BE DISCARDED. Tarkamandor also offers you a CENSER OF FRAGRANT INCENSE which he swears is blessed by the temple, a SWORD, a set of THROWING KNIVES, and a MAGIC WAND.";

        Bye = "Bidding Tarkamandor farewell, you set off to the meeting.";

        Choices.clear();

        Controls = Story::Controls::SHOP;
    }

    void Event(Character::Base &player)
    {
        Shop = {{Item::HEALING_SALVE, 80}, {Item::ELFIN_BOOTS, 100}, {Item::CENSER_OF_FRAGRANT_INCENSE, 100}, {Item::SWORD, 10}, {Item::THROWING_KNIVES, 15}, {Item::MAGIC_WAND, 60}};
    }

    int Continue(Character::Base &player) { return 94; }
};

class Story052 : public Story::Base
{
public:
    std::string PreText = "";

    Story052()
    {
        ID = 52;

        Text = "You advance quickly on Skakshi, getting in close to match your SWORD against his club. As you lunge forward, the haft of the club catches you a painful blow on the shoulder and you feel the spikes tear your jerkin and bite into the flesh beneath.\n\nYou LOSE 3 Life Points.";

        Bye = "You send the pommel of your SWORD crashing into Skakshi's jaw with stunning force. He gives a surprised grunt as his knees fold under him. Before he can rise and continue the battle, you have the point of your SWORD at his throat. \"Take me to Melmelo,\" you say to him as you get your breath back.\n\nHe looks at your SWORD uneasily as he slowly gets to his feet. \"I'll take you,\" he says sullenly.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -3);
    }

    int Continue(Character::Base &player) { return 181; }
};

class Story053 : public Story::Base
{
public:
    Story053()
    {
        ID = 53;

        Text = "You walk quickly along towards the main gate, hiding your face from strangers. After a time you realize you are being followed by a gang of young street urchins. You turn off the main thoroughfare and duck and dive down back alleys but these orphans seem to know this quarter of the city by heart. They must have explored every inch in their quest to stay alive.\n\nDeciding to ignore them you return to the main street and toward the twin arches of the main gates. As you approach the campanile, its bell sounds a steady doleful ringing. There is a creak as the gate guards push the heavy gate back. There is no way out here for anyone. You will have to try to slip out of the city another way.\n\nThe walls are high and well patrolled.";

        Choices.clear();
        Choices.push_back(Choice::Base("Explore the river quay to see if you may escape upriver by stowing away on a barge", 70));
        Choices.push_back(Choice::Base("Try to bribe the guards", 398));

        Controls = Story::Controls::STANDARD;
    }
};

class Story054 : public Story::Base
{
public:
    Story054()
    {
        ID = 54;

        Text = "You back away out of Hate's reach to recover your breath. The monster strains at the links binding it, but cannot break them. If you have a MAGICAL SALVE with which to heal your wounds, now is the time to use it.";

        Choices.clear();
        Choices.push_back(Choice::Base("Return to the fray", 5));
        Choices.push_back(Choice::Base("Use the JEWEL OF SUNSET FIRE", 349, {Item::JEWEL_OF_SUNSET_FIRE}));

        Controls = Story::Controls::STANDARD;
    }
};

class Story055 : public Story::Base
{
public:
    Story055()
    {
        ID = 55;

        Text = "You walk on, unconcerned, until you see the people ahead of you leaving their work in the fields and returning hurriedly to their farmhouses. Looking back down the road you see the dust cloud is caused by a large group of horsemen clad in the Overlord's livery of purple and black. They have seen you and are calling to you to stop.";

        Choices.clear();
        Choices.push_back(Choice::Base("Do as they say", 101));
        Choices.push_back(Choice::Base("Hide in one of the farmhouses", 125));

        Controls = Story::Controls::STANDARD;
    }
};

class Story056 : public Story::Base
{
public:
    Story056()
    {
        ID = 56;

        Text = "Your sword rasps from its sheath. The youth starts to retreat, throwing his knife away and yelling at the top of his voice: \"Help, murder! A Judain tried to kill me! Help me!\"\n\nBefore you can sheathe your SWORD the shutters in the houses overlooking the street are flung open and the cry is taken up. A group of cobblers come advancing on you wielding their little hammers. Pots and pans rain down on your head from the windows above. A steaming hot sago pudding lands on your head and oozes down underneath your jerkin as you jump nimbly aside to avoid the contents of a chamber pot. You have no choice but to flee before the mob overwhelms you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 225; }
};

class Story057 : public Story::Base
{
public:
    Story057()
    {
        ID = 57;

        Text = "The dog buries its jaws in your calf and clamps hard like a blacksmith's vice. The pain is terrible and if you struggle the dog may take a chunk out of your leg. There is no time to think of a way out, the blood is soaking your boots. You are calling out your surrender to the dog-handler when he inserts a sharp dagger into your spine and you know no more. Who would have thought a hero such as you could be caught by a dog? There is no one left to save the Judain now.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story058 : public Story::Base
{
public:
    Story058()
    {
        ID = 58;

        Text = "You duck and the blade buries itself in the wooden panel behind you, making a sound like a woodpecker as it vibrates there. You follow up quickly, as Skakshi bends to pull a knife from his other boot. You are too quick for him and wrestle him to the ground before he can pull the knife.\n\n\"I will do what you want, Judain sc--\" He chokes back the insult. \"What is it you want of me?\"\n\n\"Take me to Melmelo's hideout; take me to the guildmaster of thieves. I have a proposition to put to him, for his ears only.\"\n\n\"I can do that easily enough. Follow me.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 181; }
};

class Story059 : public Story::Base
{
public:
    Story059()
    {
        ID = 59;

        Text = "You are thoroughly versed in the criminal haunts and goings-on of the city. You make your way along twisting alleys until you stand before an ornamental villa with a hot bubbling fountain in front of it. The grandeur of the house is at odds with the ramshackle district in which it is located. This is the home of Melmelo, head of what is jocularly known as the Thieves' Guild -- a loose alliance of crooks and shady merchants who between them have most crime in the city sewn up.\n\nYou pause before knocking at the door. You have always resisted getting drawn into Melmelo's organization, and he has let it be known that he is not pleased by your disdain for his activities. On the other hand, he is a man who adheres to his own code of honour. You cannot imagine him stooping so low as handing you to the authorities for a reward.";

        Choices.clear();
        Choices.push_back(Choice::Base("Knock at the door", 12));
        Choices.push_back(Choice::Base("Retrace your steps, abandoning your plan to consult Melmelo", 214));

        Controls = Story::Controls::STANDARD;
    }
};

class Story060 : public Story::Base
{
public:
    Story060()
    {
        ID = 60;

        Text = "You sprint for it, little caring that you will crush the poor snakes you tread on. They writhe underfoot and hiss balefully. You are half-way across the room when you slip as one of the serpents rolls under the ball of your foot. You fall face down in a sea of serpentine coils and the envenomed fangs of the snakes are soon piercing your soft flesh and injecting the deadly venom. The poison of the garter snake is virulent indeed and you are soon dead. There is no one left to save the Judain now.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story061 : public Story::Base
{
public:
    std::string PreText = "";

    Story061()
    {
        ID = 61;

        Text = "You fling up the door and jump down into the cellar to find yourself surrounded by several men, one of whomjabs you with a rusty old spear before you can regain your balance.\n\nYou LOSE 3 Life Points.";

        Bye = "Wait! A fellow Judain!\" realizes one of them. You recognize the tall imposing figure of Caiaphas, rabbi at the synagogue before it was torn down by the mob.\n\n\"I am,\" you reply with a nod. \"As, I see, are all of you.\"\n\nThere are three Judain families hiding down here from the Overlord's butchers. The rusty old spear is thrown aside as they welcome you with open arms.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -3);
    }

    int Continue(Character::Base &player) { return 71; }
};

class Story062 : public Story::Base
{
public:
    Story062()
    {
        ID = 62;

        Text = "Your sixth sense has not failed you. Your instinct for danger leads you to look up into the canopy of the Overlord's four-poster bed, even as the filigree begins to tighten painfully around your ankle. Above you, what looks like a black blanket floats eerily down from beneath the canopy to engulf you.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            Choices.push_back(Choice::Base("[SWORDPLAY] Use a SWORD", 84, Skill::Type::SWORDPLAY));
            Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 118, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            Choices.push_back(Choice::Base("Cry for help", 109));
        }
    }

    int Continue(Character::Base &player) { return 118; }
};

class Story063 : public Story::Base
{
public:
    Story063()
    {
        ID = 63;

        Text = "The Inn of the Inner Temple has fake columns along its front and amusing and irreverent cartoons of many gods and goddesses painted above its lintel. Inside it is no more than a low seedy hall divided into cubicles. The drinkers all have their backs to you. There is a board near the door to which several notices have been stuck. Some are reward posters, offering money in return for help arresting some of the inn's regulars. They have been defaced and scrawled on. One of the posters offers a reward of ten gleenars for any Judain, dead or alive. You tear it down as you walk past, dropping the crumpled paper into the spittoon beside the bar.\n\nMost of those drinking in the cubicles would happily kill you for even a miserable sum like ten gleenars.";

        Choices.clear();
        Choices.push_back(Choice::Base("Talk to the people in the nearest cubicle", 197));
        Choices.push_back(Choice::Base("Leave the inn", 214));

        Controls = Story::Controls::STANDARD;
    }
};

class Story064 : public Story::Base
{
public:
    Story064()
    {
        ID = 64;

        Text = "The brigands accept you into their band and though the life is hard you flourish. Within the year you lead your own band, preying on the rich and overlooking the psychopathic excesses of your men. You are a successful brigand leader, but the Judain perish in Godorno.\n\nThe next time you see the city, it has sunk into the sea leaving only the tops of the fortresses and towers piercing the waves to show where the city that was once the jewel of the east now lies.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story065 : public Story::Base
{
public:
    Story065()
    {
        ID = 65;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            return 335;
        }
        else
        {
            return 91;
        }
    }
};

class Story066 : public Story::Base
{
public:
    Story066()
    {
        ID = 66;

        Text = "You summon up all your concentration and cast the puissant spell as the Jade Warriors lurch menacingly towards you. They are mere cyphers. There is no will within them to conquer. In vain you struggle to tamper with the circuits that set them in motion but it is quite beyond you. You are powerless as the Jade Warriors surround you and their razor-sharp swords slice into your vitals. You are slain and there is no one left to save the poor doomed Judain. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story067 : public Story::Base
{
public:
    Story067()
    {
        ID = 67;

        Text = "\"There's a price on your head, Skakshi, my friend. Melmelo wants you dead and he's hired Hammer, the assassin, to take care of you.\"\n\n\"It isn't true!\" he scoffs. \"Why should Melmelo want me dead?\"\n\n\"He is afraid. He fears you seek to supplant him as guildmaster of thieves. He has grown fat and worried on the juicy sinecures of the guild.\"\n\n\"I'm going to find Melmelo and have it out with him once and for all,\" Skakshi snarls at this. He stalks out of the inn. In his high dudgeon he fails to notice you follow him, slinking stealthily through the shadows. Shadowing men is something you have done many times before -- there isn't an urchin of the streets who could lose you in the byways and catacombs of Godorno.\n\nSoon you are following Skakshi up the steps towards Melmelo's town stronghold. He walks past an ornamental steam bath that bubbles away in the garden. Melmelo's villa is built on the site of a thermal spring.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 356; }
};

class Story068 : public Story::Base
{
public:
    Story068()
    {
        ID = 68;

        Text = "A dog, however, is no match for a man with a SWORD -- all you have to do is prod it with the weapon and it goes yelping back to its master with its tail between its legs.\n\nYou look around for Lucie. She is heading towards the Old Quarter, probably to the Silver Eel tavern which is one of her haunts. You know it as a dubious drinking-house whose customers have a dangerous reputation.";

        Choices.clear();
        Choices.push_back(Choice::Base("Follow Lucie", 261));
        Choices.push_back(Choice::Base("Return to Bumble Row for the time being and seek her out this afternoon", 371));

        Controls = Story::Controls::STANDARD;
    }
};

class Story069 : public Story::Base
{
public:
    Story069()
    {
        ID = 69;

        Text = "You leave the road and walk across melon beds past a farmhouse safely out of sight of the riders, where a young woman greets you and offers you mash beer, while her father looks on warily. You accept their hospitality. They seem simple honest people. They ask who you are and where you come from. \"You are Judain, are you not? Tell me why are the Judain so proud? And are you all as rich as they say?\"\n\n\"We are proud because we are the chosen ones,\" you explain. \"We have remained together, never marrying outside our kind through the difficulties of our troubled history. I wish we were all rich, but I, I must confess, am almost beggared.\"\n\n\"Why did you leave the road?\" asks the girl.\n\n\"The riders. They carry word to Bagoe that we Judain are outcast. They will put a price upon our heads.\"\n\n\"We will hide you and smuggle you past the town by the back paths.\"\n\nAlthough you are dogged by the Overlord's riders for more than a week, the farmers are as good as their word. They keep you well fed, allowing you to build up your strength for the day you must flee.\n\nYou RECOVER 3 Life Points.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 3);
    }

    int Continue(Character::Base &player) { return 142; }
};

class Story070 : public Story::Base
{
public:
    Story070()
    {
        ID = 70;

        Text = "You creep along side streets, hiding your face from strangers, as you head towards the riverfront. You are plagued by midges but that is the least of your troubles. You can hear shrieks and the cries of hysterical mobs behind you as they rampage back and forth across the city. Making your way carefully to the quay you can see a row of three river barges, two laden with goods and one which has just finished unloading.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            return 120;
        }
        else
        {
            return 134;
        }
    }
};

class Story071 : public Story::Base
{
public:
    Story071()
    {
        ID = 71;

        Text = "Caiaphas's story of what has been the fate of their many friends is chilling. As soon as you fled the city, the Overlord's guards -- along with foreign mercenaries who marched out of beyond -- started to round up all the Judain they could find. The executions have been carried out all day every day since then. A few, like you, escaped from the city; several thousand have gone to ground; but most of your folk have already perished. You vow then and there to avenge your fellow Judain.\n\n\"It is worse even than I have said,\" continues Caiaphas. \"Some have reported seeing a loathsome monster dragging its bulk through the streets at night. None knows where it comes from, but by daybreak there are always fewer people in the city.\"\n\n\"What is it?\" you ask, aghast.\n\n\"Hate itself. The embodiment of cruelty. It has been awakened and given living form by the Overlord's excesses. Now it stalks the streets beyond even his power to control, and it will not rest until our city has become a desolate ruin.\"\n\nYou hear his words with horror.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 181; }
};

class Story072 : public Story::Base
{
public:
    Story072()
    {
        ID = 72;

        Image = "images/mameluke.png";

        Text = "The cloying smell of crushed roses and honeysuckle makes your senses swim again. The reek of Hate is all about you. You hear a deep voice, cursing bitterly, and the grunts and gasps of a strong man trying to lift a heavy boulder. The noises are coming from just around the next corner. You can't resist seeing who it is.\n\nThe strong form of a mulatto beckons you imploringly. He is stuck fast in the coils of Hate. Its gelid form has oozed around his body. He is covered from knees to armpits and will soon succumb. As you get closer you recognize him as your friend Mameluke. You must do something to save him.";

        Choices.clear();
        Choices.push_back(Choice::Base("Attack Hate with a SWORD", 83, Choice::Type::ANY_ITEM, {Item::SWORD}));
        Choices.push_back(Choice::Base("Pummel Hate with punches and kicks", 93));
        Choices.push_back(Choice::Base("[SPELLS] Use a spell of Rulership", 122, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast a spell of Miasma", 136, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast a spell of Thunderflash", 167, Skill::Type::SPELLS));

        Controls = Story::Controls::STANDARD;
    }
};

class Story073 : public Story::Base
{
public:
    Story073()
    {
        ID = 73;

        Text = "There is a great crash which echoes around the room and seems to shake the whole tower, followed by an explosion of spurting red flame which bathes the black spider in its punishing light. You feel giddy as the tower rocks, and the spider recoils before gathering itself to leap once more. It is badly hurt, but not yet incapacitated, though you have gained time to cast another spell. You cannot cast the same spell twice in a row.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Miasma", 79));
        Choices.push_back(Choice::Base("Cast Images to give yourself more time", 208));

        Controls = Story::Controls::STANDARD;
    }
};

class Story074 : public Story::Base
{
public:
    std::string PreText = "";

    Story074()
    {
        ID = 74;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The middle platform is a trap. The wood gives way as you land and you fall through, impaling yourself on metal spikes which stick into the soles of your feet.\n\nYou LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        if (player.Life > 0)
        {
            PreText += "\n\nYou extricate yourself and balance on the outside of the box. The pain is excruciating and it affects your ability to balance but you can't go back now. The heads of the garter snakes are starting to mesmerize you as they sway, as if silently willing you to fall among them. You nerve yourself to go on, you will never give up, and leap for the next rope.\n\nYou grab the rope and swing above the snakes, looking down to see their jaws opening wide and venom dribbling from the jaws. You can only hope they do not spit venom like some of the hooded cobras you have heard about that live in the fens around Bagoe. You swing slowly across the room to alight on the last box, which stays firm beneath your feet and from whe!e you can jump down and open the door beyond.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 180; }
};

class Story075 : public Story::Base
{
public:
    Story075()
    {
        ID = 75;

        Image = "images/filler3.png";

        Text = "Lucie didn't need your help, she is already half-way to the dubious sanctuary of the Silver Eel tavern. You have lost the chance of picking up another SWORD. The dog-handler has retrieved it and he pulls his dog roughly behind him as he sets out home again.";

        Choices.clear();
        Choices.push_back(Choice::Base("Follow Lucie to the Silver Eel right now", 261));
        Choices.push_back(Choice::Base("Bide your time and seek her out later today", 371));

        Controls = Story::Controls::STANDARD;
    }
};

class Story076 : public Story::Base
{
public:
    Story076()
    {
        ID = 76;

        Text = "You can't flee for ever. They are slowly running you down, urging their mounts to greater efforts with the cracks of bullhide whips. At last you are forced to stand your ground, fighting for breath. You are so exhausted you can hardly collect your wits.\n\n\"This one's a Judain!\" one of the brigands shouts.\"Didn't old Samfgash say there was a price on 'em in Godorno? Let's take the Judain to the main gate and claim the blood money.\"\n\nThe brigand leader agrees it would be sensible to turn you in for money as you have led them so close to the city in the chase. You try to escape but they will collect their money for your dead body just as they would if they turned you in alive. They cut you down like a hunted doe.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story077 : public Story::Base
{
public:
    Story077()
    {
        ID = 77;

        Image = "images/hate-attacks.png";

        Text = "Hate has been grievously wounded fighting the Jade Warrior tomb guards of the Megiddo dynasty burial vaults. It cannot tear itself free from the chains and caltrops which bind and gall it.\n\nHate thrashes wildly and a tidal wave erupts from the canal, smashing against the Bargello keep, but it is the monster's death throes. Just as the sun sinks beneath the horizon the JEWEL glows white hot and the ruby light becomes a coruscating fan of many coloured motes that disintegrate the soft purple flesh. The monster falls and makes its own grave as the catacombs open up beneath its bulk to welcome it to its final rest. The sun sets and the city is quiet.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 416; }
};

class Story078 : public Story::Base
{
public:
    Story078()
    {
        ID = 78;

        Text = "\"I have been giving that matter much thought. It's not good for business with Hate disrupting the life of the city.\" Melmelo had the larceny side of business in the city nicely sewn up until the monster emerged from the catacombs. \"I can only think of one thing which might be the key to the city's salvation.\"\n\n\"What is that?\" you ask, avidly.\n\n\"The JEWEL OF SUNSET FIRE.\"\n\n\"Where is this JEWEL?\"\n\nMelmelo seems certain that it lies at the top of the Tower of the Sentinel at the east end of Fortuny Street. \"I have coveted it all my life. It is said to give wondrous powers to its wielder. But though many of us have tried to scale the tower -- both within, using stealth and cunning, and without, clinging like flies to the stones -- none of us survived.\"\n\n\"I will survive,\" you say determinedly. You can be reasonably sure Melmelo is telling you the truth for he wants to see Hate vanquished as much as any man does. He is already on top of the pile, here in Godorno.\n\nYou gained the codeword SUNSET.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::SUNSET});
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story079 : public Story::Base
{
public:
    Story079()
    {
        ID = 79;

        Text = "With a dramatic gesture and a clap of your hands you bring forth a cloud of noxious vapours that fills the top room of the Tower of the Sentinel, obscuring the JEWEL from view. The gigantic spider falters momentarily then leaps towards you, seemingly unaffected by the poison gas. You haven't time to cast another spell.";

        Choices.clear();
        Choices.push_back(Choice::Base("Run for it back down the stairs", 146));
        Choices.push_back(Choice::Base("Make a dash for the JEWEL OF SUNSET FIRE", 164));

        Controls = Story::Controls::STANDARD;
    }
};

class Story080 : public Story::Base
{
public:
    Story080()
    {
        ID = 80;

        Text = "Conjuring a magical silver shield from thin air is the work of only a moment and you scoop a writhing interlocked mass of snakes aside, slowly and painstakingly clearing the way across the floor. The serpents hiss balefully, as if outraged to have been disturbed so unceremoniously. As soon as you sweep them aside, so they wriggle back towards you and it is a miracle that you reach the door at the other side of the room without being bitten.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 180; }
};

class Story081 : public Story::Base
{
public:
    Story081()
    {
        ID = 81;

        Text = "\"But, Caiaphas, did no one fight back? Did all our people just surrender themselves to be led away meekly to the slaughter, like sheep? We must fight?\"\n\nCaiaphas, a tall man with a black beard and rumbling basso voice replies. \"You are a fine one to criticize us! Where were you? We could not fight. We have no swords nor heavy suits of mail to protect us. There are too few of us.\"\n\n\"Surely there is someone among us who will strike back, someone prepared to stand up to the evil of the accursed Overlord?\"\n\nCaiaphas has not heard of any such resistance group, though he can get messages through to the large number of Judain who are in hiding throughout the city.\n\n\"Who is our leader now?\" you ask. \"Are the elders all dead or gone?\"\n\nAnnas, a small man with a quavering, flute-like voice tells you, \"They were taken together, as they met in the synagogue to discuss the Overlord's edict.\"\n\n\"And did all the folk of the city just stand by?\"\n\n\"Yes, they did, or denounced us to the guards.\"\n\nThere are sounds from the street above. An iron-tyred cart is being pulled past the smashed door to the hovel. You wait for it to pass before lowering your voice to say, \"How safe are we down here?\"\n\n\"As safe as anywhere,\" is Caiaphas's opinion.\n\n\"But do you plan to stay here for the rest of your lives?\" He just shrugs helplessly. \"What do you do for food?\" you go on.\n\nWe have enough food and water for another two weeks,\" puts in Annas.\n\n\"And what then?\" Again they shrug. \"We must do something. Organize ourselves. Band together for our own protection.\"\n\n\"It would accomplish nothing,\" Caiaphas replies despondently.";

        Choices.clear();
        Choices.push_back(Choice::Base("Immediately organize a resistance movement among the Judain", 111));
        Choices.push_back(Choice::Base("Remain in hiding in the cellar while formulating a plan", 121));

        Controls = Story::Controls::STANDARD;
    }
};

class Story082 : public Story::Base
{
public:
    Story082()
    {
        ID = 82;

        Text = "You choose a place where the road winds beneath copses of trees and wait. The horsemen are wearing the purple and black livery of the Overlord of Godorno and it seems they are tracking you. To attack them would be dangerous, there are too many of them you reluctantly decide, so you let them pass and double back making haste to put distance between yourself and your pursuers before they realize they have been thrown off the scent.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story083 : public Story::Base
{
public:
    Story083()
    {
        ID = 83;

        Text = "You hack wildly at the purple flesh of Hate to free Mameluke, who strains against the suffocating flesh. Your SWORD rips dark maroon welts in the flesh of Hate which puckers and drools a pale pink viscous mucus. After three minutes of wild work with the SWORD your arms are aching, but Mameluke is able to pull himself free with one last effort. Pausing to wipe some of the pink mucus off your face, you clasp the Tartar's hand and tell him you are taking him home for a bath. Hate's coil is twitching and still bleeding the pink mucus. Your skin crawls where the sticky secretions landed on your bare face.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 185; }
};

class Story084 : public Story::Base
{
public:
    Story084()
    {
        ID = 84;

        Text = "The underside of the monster is lined with wicked barbs oozing amber fluid. They must be poisoned.";

        Choices.clear();
        Choices.push_back(Choice::Base("Couch beneath your upheld sword so that the monster impales itself on your BLADE", 127));
        Choices.push_back(Choice::Base("Hack at it as it descends to envelop you", 145));

        Controls = Story::Controls::STANDARD;
    }
};

class Story085 : public Story::Base
{
public:
    Story085()
    {
        ID = 85;

        Text = "Your journey back to the city takes no longer than your outward trek. By midday of the third day you are before the battlemented towers and guarded walls of the great city. Carrion crows wheel in great flocks above the city and the wind carries the dismal cries of the poor unfortunates being tortured in the prison fortress of Grond to your unwilling ears. You approach the gates with trepidation.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 188; }
};

class Story086 : public Story::Base
{
public:
    Story086()
    {
        ID = 86;

        Image = "images/silver-eel-tavern.png";

        Text = "The inside of the Silver Eel is much as you expected. Sawdust covers curdled puddles of vomit or blood on the creaking floor. There are rough trestles for seats, a few with initials carved deep into the dark old wood -- it is amazing that most of these lowlifes even know how to write their initials. The thick green bottle-glass in the lanterns gives the whole of the interior a strange unreal look. A dozen pairs of eyes swivel, assessing you at a glance before returning to drinks or companions.\n\nThe tall blond man has walked to the bar and ordered firewater for himself and lemon bitters for Lucie. He is dressed in a suit of the most outlandish leather and mail armour you have ever seen. It is a patchwork quilt of jagged bosses and scales, which altogether make a very striking and rather chilling outfit to look upon.\n\nThe landlord, an ex-captain at the duelling school with scars and the tip of an ear missing as testament to the many fights he has been in with unruly customers, is quick to serve this towering figure of a young man. Lucie is quite at ease with him as if she knows him well.\n\nThe tall blond man darts a glance at you and looks quizzical. He is very pale of skin and his cheekbones are dusted with freckles. Lucie puts her arm around his waist and whispers something. He replies and you hear the word 'Judain', after which he hawks a gobbet of phlegm into the sawdust. He puts his hand on Lucie's bottom but she smacks it away and takes her drink to a table in a nook at the back of the tavern, followed by the tall stranger. There is a group of four men drinking small beer who could be either artisans or thieves. Two women wearing lace and silks and not much of either laugh scurrilously in the alcove beyond, and a single dark figure lurks at the far end of the bar smoking a pipe.";

        Choices.clear();
        Choices.push_back(Choice::Base("Order a drink from the bar", 113));
        Choices.push_back(Choice::Base("Ask the gang of four where you can find Melmelo the master thief", 132));
        Choices.push_back(Choice::Base("Join Lucie and the tall stranger", 227));

        Controls = Story::Controls::STANDARD;
    }
};

class Story087 : public Story::Base
{
public:
    Story087()
    {
        ID = 87;

        Text = "You tried to leap too far. You fall with a thump among the writhing garter snakes. The snakes intertwine around your legs and arms, their forked tongues questing for bare flesh. They sink their venomed fangs into your flesh and your body is soon hot with poison. Unconsciousness comes as a blessed release. You are just another would-be thief. There is no one left alive to save the Judain now.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story088 : public Story::Base
{
public:
    Story088()
    {
        ID = 88;

        Text = "It might have been better to disappear in a puff of smoke first. A young Judain turning suddenly, by the use of magic, into an aged bent old crone fools no one. The guard close in around you and cut you down while the townsfolk howl with glee. There is no one left to save the Judain now.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story089 : public Story::Base
{
public:
    Story089()
    {
        ID = 89;

        Text = "You draw Hate's attention by waving your arms as you retreat to the back 1of the plaza. Two tentacles sweep towards you, but you evade them by ducking into the pillared portico of a church. As the tentacles snake around on either side of the pillar, feeling for you, you slip the chains around the slimy purple flesh and lock them into place.\n\nHate gives a roar of rage as you stand safely back to survey your handiwork. You have tethered Hate to the portico of the church. If only the chains hold, you may be able to destroy your enemy once and for all.\n\nYou gained the codeword GORDIAN.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use the JADE WARRIOR's SWORD", 230, {Item::JADE_WARRIORS_SWORD}));
        Choices.push_back(Choice::Base("Use the JEWEL OF SUNSET FIRE", 349, {Item::JEWEL_OF_SUNSET_FIRE}));
        Choices.push_back(Choice::Base("You have neither of those items", 187));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::GORDIAN});
    }
};

class Story090 : public Story::Base
{
public:
    Story090()
    {
        ID = 90;

        Text = "You pass a restful night. As the sun slants in through the broken cellar roof, you get ready to set out for your rendezvous with Lucie.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 7; }
};

class Story091 : public Story::Base
{
public:
    Story091()
    {
        ID = 91;

        Text = "By dint of desperate effort, you succeed in freeing yourself from the body of Hate. Mameluke has by now been completely engulfed. Mourning the loss of your brave Tartar friend, you return to your hideout on Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 159; }
};

class Story092 : public Story::Base
{
public:
    Story092()
    {
        ID = 92;

        Image = "images/filler3.png";

        Text = "Your stiffened fingers lash out as fast as a striking cobra, jabbing into the cluster of nerves at the base of his palm. His fingers immediately go limp and he drops the KNIFE without even feeling any pain. You snatch it up from the cobblestones before he can take stock of what has happened.\n\nA moment later, he gives a sob of frustrated rage and launches a kick at your midriff. You easily catch his foot and draw it up, pulling him off-balance as you step closer to look him straight in the eye.\n\n\"I wonder if you're also the sort who kicks dogs?\" you say softly, but with a hard look in your eye.\n\n\"Beware, if so. You'll find that we Judain are like wolfhounds. We bite back.\"\n\nSo saying, you give his leg a twist so that he is thrown over onto his back in the street. Pocketing his KNIFE so that it cannot be used against another of your people, you saunter off in the direction of Greenbark Plaza.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::KNIFE});
    }

    int Continue(Character::Base &player) { return 201; }
};

class Story093 : public Story::Base
{
public:
    Story093()
    {
        ID = 93;

        Text = "Your blow is so forceful that your arm sinks into the soft purple flesh of Hate up to the elbow. When you try to withdraw it to strike again the flesh ripples and shudders, pulling you in. Try as you might you can't get free.";

        Choices.clear();
        Choices.push_back(Choice::Base("Brace yourself with your foot against the monster's purple flesh", 151));
        Choices.push_back(Choice::Base("Keep trying to free yourself without touching Hate with any other part of you", 65));

        Controls = Story::Controls::STANDARD;
    }
};

class Story094 : public Story::Base
{
public:
    Story094()
    {
        ID = 94;

        Text = "The heads of each cell have risked coming together at the granary warehouse behind the old army stables on Slipshod Row. There are some two hundred people here, waiting for you to address them. Now that they are standing up to the Overlord, they are regaining their self respect. They report the number of their people dragged off to the Grond by the Overlord's guards is much diminished. Resistance fighters have assassinated over thirty key figures in the bureaucracy. If they continue to act with such success the Overlord will soon have to meet your demands.\n\n\"There is bound to be a backlash,\" you caution. \"Beware of anyone who is not of our people. They are jealous of us. At the end of this meeting, I am going to give you all new assignments and new safe houses in which to lie low. If we keep moving like this the Overlord\"s men can never find us all, even if they catch one of us for torture.\"\n\nYour people are cheered to find you have thought about the situation and they look to you increasingly for leadership.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story095 : public Story::Base
{
public:
    Story095()
    {
        ID = 95;

        Text = "Tormil's sword seems to stick fast in the body of the purple mass. The weapon is pulled from his grasp and then the whole bloated purple mass rolls over, crushing Tormil beneath it. His flattened body is already being absorbed. Terror draws bile into your throat and you cannot help giving a small cry of horror. Averting your face, you leave the grisly scene behind. You are ashamed to think you could have led any foe into such a trap, even a cur like Tormil.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::SATORI);
        }
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story096 : public Story::Base
{
public:
    Story096()
    {
        ID = 96;

        Text = "Bafflement is a powerful spell to use against a single dire opponent. But even if you succeeded in confusing one of the Jade Warriors, the others would still cut you down.\n\nAs it is they have no mind as we understand it. They are automata, immune to your spell. The Jade Warriors whirr and click menacingly as they advance to surround you with swords aloft. There is no time to cast another spell: Their sharp blades lance your vitals and rob you of life. The burial vaults of the Megiddo dynasty remain inviolate. Your last thought is that, now you are slain, there is no one who can save the Judain and Hate will conquer all.\n\nVanity of vanities...";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story097 : public Story::Base
{
public:
    Story097()
    {
        ID = 97;

        Text = "You cast a Bafflement spell on Tormil, hoping to be able to lead him away from the grisly scene of his daughter's living entombment. The spell works and Tormil seems to forget everything but his daughter. He tries to embrace her and stares nonplussed at the cloying purple flesh which will not let him go. There is nothing you can do to save him as he is drawn into the body of Hate. He is already another lost soul.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story098 : public Story::Base
{
public:
    Story098()
    {
        ID = 98;

        Text = "It is a difficult leap but you just make it, launching yourself high in the air from a short run up. You land beside the girl and the bodies on the bed rock as the bedsprings bounce. The Overlord twitches again but does not awaken, while the girl lies inert, her back still towards you. You carry the concubine off for questioning.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 231; }
};

class Story099 : public Story::Base
{
public:
    Story099()
    {
        ID = 99;

        Text = "Your confident look unnerves him. He expected fear or anger but you treat him as if he were a harmless stranger asking the way. You guess from the red dye which stains his wrists that he is a tanner's son. Judging by the state of his clothing his father is poor, probably in debt to a Judain, else why would the youth show such malice towards you? You decide to bluff him.\n\n\"Be careful, young one,\" you say, \"you know what happens if we Judain withdraw a loan - debtors' prison or debt slavery if you can't pay up. You have a strong resemblance to one of my clients, a tanner down on his luck. Your father, perhaps?\"\n\nYou are lucky, your hunch was right. His father must be in debt. The youth won't risk harming you in case of losing the roof over his head. He slinks away.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 201; }
};

class Story100 : public Story::Base
{
public:
    Story100()
    {
        ID = 100;

        Text = "Decide what to do next.";

        Choices.clear();
        Choices.push_back(Choice::Base("Seek out Melmelo, the master of the Guild of Thieves", 153));
        Choices.push_back(Choice::Base("Visit the library to look for more information about Hate", 110));
        Choices.push_back(Choice::Base("Organize the defence of the city", 174));
        Choices.push_back(Choice::Base("Go to confront Hate itself", 272));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SUNSET}))
        {
            Choices[0].Destination = 117;
        }
        else if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::IMPASSE}))
        {
            Choices[0].Destination = 26;
        }
        else if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::COOL}))
        {
            Choices[0].Destination = 334;
        }
        else
        {
            Choices[0].Destination = 153;
        }

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::CODEX}))
        {
            Choices[1].Destination = 49;
        }
        else
        {
            Choices[1].Destination = 110;
        }
    }
};

class Story101 : public Story::Base
{
public:
    Story101()
    {
        ID = 101;

        Text = "\"Your money or your life,\" comes the age-old cry from the leader. The horsemen are brigands, disguised as the Overlord's men!";

        Choices.clear();
        Choices.push_back(Choice::Base("Surrender everything you have to them", 8));
        Choices.push_back(Choice::Base("Ask to join their merry band and live the next chapter of your life as a brigand", 64));

        Controls = Story::Controls::STANDARD;
    }
};

class Story102 : public Story::Base
{
public:
    Story102()
    {
        ID = 102;

        Text = "You speak the word of power and disappear, but the Jade Warriors must be sensing you by some other means than sight. Skulking in the shadows will not avail you here. They lurch menacingly towards you. You have no time to cast a spell and are powerless as the Jade Warriors surround you and slice into your vitals with their razor-sharp swords. You are slain. There is no one left now to save the Judain. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story103 : public Story::Base
{
public:
    Story103()
    {
        ID = 103;

        Text = "You try to duck the tentacle but it crashes down, smashing you like an avalanche crushing you into the midst of a mound of rubble that was once the Bargello, the strongest building in the city. The monster carries all before it. Soon you are all partners in the eternal orgy of despair. The city crumbles and is lost for ever beneath the waves. Hate has completed its work.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story104 : public Story::Base
{
public:
    Story104()
    {
        ID = 104;

        Text = "You conjure a cloud of smoke which engulfs you and all those nearby. The crowd and the soldiers fall back. The smoke makes them cough and their eyes smart, but it doesn't affect you. You then cast a spell of Disguise and those who can still see pay no attention to a bent old woman coughing and rubbing her eyes, who staggers out of the smoke and shuffies away from the plaza. Still looking like an old woman you run nimbly away from the plaza, ducking under a milk cart as you feel the spell start to wear off. Then, looking like yourself again, you go on. You hide your face from strangers as far as possible but the people of Godorno are mad for the blood of the Judain and you soon attract suspicion once more.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 38; }
};

class Story105 : public Story::Base
{
public:
    Story105()
    {
        ID = 105;

        Text = "It looks like there is no back exit from this building, but you recall seeing a trap door in the alley running behind it. Dragging the frightened Ruth behind you, you descend to the cellar. Sure enough, there is a ramp for delivery of wine barrels. You make your escape, emerging in the alley at the back of the house while the soldiers are bursting in the front way.\n\nRuth cannot thank you enough. \"My baby will be born, thanks to you,\" she sobs as you lead her back to Copper Street.\n\n\"I hope to save many others,\" you tell her. \"All our people, in fact.\" Once she is safe with Caiaphas, you return to your own bolthole.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 414; }
};

class Story106 : public Story::Base
{
public:
    std::string PreText = "";

    Story106()
    {
        ID = 106;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The Overlord's men are tipped off by a mysterious informer. You are ambushed on your way to the meeting and have to fight to get away. As you run, a crossbow quarrel buries itself in your shoulder.\n\n";

        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            PreText += "[CHARMS] Your magic gives you some protection. ";
        }
        else
        {
            Character::GAIN_LIFE(player, -3);

            PreText += "You LOSE 3 Life Points.";
        }

        if (player.Life > 0)
        {
            PreText += "\n\nYou return to Copper Street to hear the terrible news. Many other Judain were also captured and are now swinging dead in gibbets beside the Avenue of Skulls. \"There is no trust in the hell-pit this city has become,\" groans Caiaphas, himself bleeding from a deep gash across his forehead. He barely escaped from the meeting alive.\n\n\"From now on, secrecy shall be our watchword,\" you agree. You find yourself a hideout on Medallion Street. Only a few hand-picked comrades know where to find you. You are determined not to let the Overlord's men set another trap for you.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 414; }
};

class Story107 : public Story::Base
{
public:
    Story107()
    {
        ID = 107;

        Image = "images/ruby-light.png";

        Text = "The jewel sparkles in the rays of the setting sun and then kindles into a blinding aura. There is a flaring sound and a beam of ruby light strikes Hate between the eyes like a mace blow. The monster squirms and writhes, desperate to free itself from the chains that have bitten deep and scored its soft purple flesh, but it cannot yet break free. With a last great spasm it starts to rip the chains away from their anchorage in the plaza and prepares to fall upon the parapet and smash you and the Bargello into the water.\n\nThe chains are pulling apart. A link snaps with a sound like a pot of Greek fire exploding and plumes of water turn to steam in the ruby beam. The sun is about to slip from the heavens and dusk is upon you. If Hate is not destroyed before nightfall you have no hope.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            return 401;
        }
        else if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::HECATOMB}))
        {
            return 77;
        }
        else
        {
            return 364;
        }
    }
};

class Story108 : public Story::Base
{
public:
    Story108()
    {
        ID = 108;

        Text = "You duck too late. In your last moment you see the dagger arcing through the air, its blade glinting in the light of the lanterns as it flies unerringly towards your neck. You fall to the floor, impaled, andSkakshi gloats.\n\n\"What a shame I can't claim the extra reward forbringing in a live Judain for the torture,\" he chucklesto himself, satisfied his standing amongst his villainous peers is all the higher for having despatched you with contemptuous ease. There is no one left to save the Judain now. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story109 : public Story::Base
{
public:
    Story109()
    {
        ID = 109;

        Text = "Disturbed by your noise, the Overlord yawns, rubs sleep out of his eyes and looks about him. As he sees you his eyes widen with fear and.he reaches furtively beneath his pillow. He pulls out a small blowpipe and puffs out a tiny dart which bites into your neck like a hornet sting. It is tipped with curare, a very painful death. There is no one left now to save the Judain. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story110 : public Story::Base
{
public:
    Story110()
    {
        ID = 110;

        Text = "You slip into the great yellowstone library of Brunelesci unseen and take down what is a recent invention: the combined dictionary and bestiary. Crouching beneath a reading bench you are soon immersed in the cursive script. \"Hate, hatred, detestation, abhorrence, abomination, malignity,\" and there are quotes from Senecio, one of the great playwrights of the age. \"Do all men kill the thing they do not love? Hates any man the thing he would not kill?\" and \"The monster that turneth man against his daughter and mother against her firstborn son, servitor of Death and handmaid to Destruction, maker of wars and inspiration of man's blackest deeds.\"\n\nAccording to the scholar who compiled the lexicon and bestiary, \"Hate always shows its true face and so may be bested.\" Unfortunately he does not write how to overcome the monster. There is much written here, it is almost as if he was obsessed, \"In concert with Fear the most terrible of the Trinity of the Dark, Hate feeds on the bodies and souls of those who have given themselves up to the monster's embrace in despair, depravity and degradation.\"\n\nYou are still staring in fascination at the illuminated pages of the manuscript when the door opens and a soft-footed scholar librarian comes into the book-lined room. You have read enough and will learn nothing more here, so you creep out and return to Bumble Row, none the wiser but a little more oppressed of spirit.\n\nYou gained the codeword CODEX.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::CODEX});
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story111 : public Story::Base
{
public:
    Story111()
    {
        ID = 111;

        Text = "Caiaphas's wife, Ruth, asks, \"Will we have to share our food with this stranger? There is precious little to go round as it is, without our having to feed every down-at-heel ragamuffin who stumbles across our hideout.\"\"Be quiet, woman. We will feed all of our kind.\"\n\nRuth used to be a generous mild-mannered woman who wouldn't hurt a flea. Adversity has certainly hardened her. \"Well spoken, Caiaphas,\" you say. \"Ruth, did you not know this miserable hovel is my home?\"\n\n\"Haven't you heard? We Judain cannot own property. We cannot even walk the streets. We haven't moved from this miserable place for days.\"\n\n\"What, none of you?\" You look to Caiaphas in surprise. \"Has no one ventured out for food or information?\"\n\nCaiaphas shakes his head and looks at the ground.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask him how they pass messages", 131));
        Choices.push_back(Choice::Base("Quit the safety of the cellar to seek out more information and contacts to help the Judain cause", 141));

        Controls = Story::Controls::STANDARD;
    }
};

class Story112 : public Story::Base
{
public:
    Story112()
    {
        ID = 112;

        Text = "Rubbing the green emerald amulet ostentatiously you chant an incantation. A green glow suffuses your face evilly as the amulet lights up magically from within. The youth blenches, he makes a sign invoking the protection of one of the gods of Godorno, Hecasta the patroness of enchanters, and backs away.\n\n\"Judain witch. A plague take you and the pox turn you to dust,\" he mutters.\n\nIf that was his best effort at a curse, you have nothing to fear. He daren't challenge someone as powerful as you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 201; }
};

class Story113 : public Story::Base
{
public:
    Story113()
    {
        ID = 113;

        Text = "The landlord is ignoring you, cleaning glasses that already sparkle in the sombre red light. The pipesmoker gives you a glance, then turns away. You can hear two women gossiping about the fate of some of their Judain acquaintances. \"It wouldn't do to call them friends in these times -- well, would it, darling?\"\n\nAt the far end of the tavern the tall stranger is staring morosely at his drink, while Lucie watches him fondly.";

        Choices.clear();
        Choices.push_back(Choice::Base("Tolerate the landlord's rudeness", 158));
        Choices.push_back(Choice::Base("Force him to serve you", 169));

        Controls = Story::Controls::STANDARD;
    }
};

class Story114 : public Story::Base
{
public:
    Story114()
    {
        ID = 114;

        Text = "Seeking out some of your unsavoury underworld contacts, you manage to get an offer of 900 gleenars for the DIAMOND. You know it is worth much more than that. So does the fence, who says, \"You're lucky I deal with you at all these days. You know the trouble I could get into for talking to a Judain?\"\n\n\"Not as much trouble as if that Judain told the Overlord's men about you handling the Overlord's own DIAMOND,\" you say with an ingenuous smile.\n\nHe curses under his breath, but finally agrees to pay you 1,000 gleenars for the DIAMOND.\n\nOn your way back to join the others, you pass a narrow shop. You recognize it as the shop of Tarkamandor the Sage, where you have occasionally bought interesting items m the past. A lamp is burning in the window. You creep up and peek through the shutters. Tarkamandor is alone, polishing a carved ebony staff at his work bench.";

        Choices.clear();
        Choices.push_back(Choice::Base("Knock at the door", 318));
        Choices.push_back(Choice::Base("Get back to Caiaphas and the others", 190));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 1000);

        Character::LOSE_ITEMS(player, {Item::Type::DIAMOND});
    }
};

class Story115 : public Story::Base
{
public:
    Story115()
    {
        ID = 115;

        Text = "You jump for the rope and clasp it tight, swinging out above the living carpet of serpents. You swing over one of the box platforms and towards another. The serpents' heads sway in time with you, their jaws wide to reveal dripping black venom.";

        Choices.clear();
        Choices.push_back(Choice::Base("Let the rope go and jump to the far platform", 87));
        Choices.push_back(Choice::Base("Content yourself with alighting on the middle platform beneath where the rope hangs from the ceiling", 74));

        Controls = Story::Controls::STANDARD;
    }
};

class Story116 : public Story::Base
{
public:
    Story116()
    {
        ID = 116;

        Text = "The late afternoon sun slants over the close-packed rooftops and through the open doorway of the hovel where you are hiding. You have an inspiration. Lifting your amulet, you tilt it so that the gem reflects the sunbeam out onto the wall on the opposite side of the street. The guards are standing waiting for the dogs to be brought, but one of them catches the flicker of reflected light out of the corner of his eye. He spins, looking along the street away from where you're hiding, and yells, \"Hey! I saw something dart down that alley over there. Come on, lads!\"\n\nWhile they race off chasing sunbeams, you help Ruth to the safety of the Copper Street hideaway. Then you slink back to your own bolthole.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 414; }
};

class Story117 : public Story::Base
{
public:
    Story117()
    {
        ID = 117;

        Text = "You find Melmelo packing his belongings into a cart which is watched closely by his burly bodyguards. He himself carries a heavy treasure chest and loads it onto the cart.\n\n\"Leaving town, Melmelo?\" you ask. He nods. \"Take my advice, Judain. Get out while the going is good.\"\n\nYou give a puff of bitter laughter. \"You call this good? My people are the victims of a slaughter!\"\n\n\"It'll get far worse than this,\" says Melmelo. \"I'm off to Mazarkhand before the Overlord sets his sights on my wealth. Don't try to seek me out again, Judain. You'll find my friends remaining in the city will cover my tracks.\"\n\nAgreeing not to come here again, you walk away. It is tempting to think you might leave the city yourself, but your people need you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story118 : public Story::Base
{
public:
    Story118()
    {
        ID = 118;

        Text = "Rising quickly onto tiptoe you slip the noose snare from your ankle and somersault backwards. The black blanket, like a vampire's cloak, falls to the floor with a heavy thump. You have escaped the first of the defences of the Overlord's bedchamber. The black monster flops about feebly then falls still.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay here to see what new trick or trap will test you next", 139));
        Choices.push_back(Choice::Base("Retreat back into the catacombs", 161));

        Controls = Story::Controls::STANDARD;
    }
};

class Story119 : public Story::Base
{
public:
    Story119()
    {
        ID = 119;

        Text = "From your knowledge of mythology you remember that the Jade Warriors were set to guard the tombs of the Megiddo dynasty. Legend has it that one of the swords is the key to controlling the warriors. If you can get that sword you may be able to command them to do your bidding, perhaps even lead against the Overlord or the monster itself.";

        Choices.clear();
        Choices.push_back(Choice::Base("Look as closely as you can at the flashing haloed blades", 157));
        Choices.push_back(Choice::Base("Attempt to grab the nearest one from the grip of the Jade Warrior which hefts it", 170));

        Controls = Story::Controls::STANDARD;
    }
};

class Story120 : public Story::Base
{
public:
    Story120()
    {
        ID = 120;

        Image = "images/quay.png";

        Text = "You are no expert on the ways of bargees, who are looked down upon by real seamen. You do know, however, that the tide is due to rise strongly this evening and that the bargees like to do the hard work of poling their barges upstream on a rising tide at dusk when it is no longer unbearably hot.\n\nThere are three barges at the quay. The first is a big barge which is little more than a wide raft. It has a huge pile of lime for cargo. The second has just been unloaded, an ordinary grain barge; you can see rats scavenging the dropped grains of corn. The third is a smaller barge with a shallow draught which is loaded with barrels under a tarpaulin. These shallower barges are used on the small tributary, the Palayal river, which descends from the great forest to the north. This looks the most likely barge to leave on the tide.";

        Choices.clear();
        Choices.push_back(Choice::Base("Hide under the tarpaulin on the small barge", 183));
        Choices.push_back(Choice::Base("Hide in the lime on the raft barge", 152));
        Choices.push_back(Choice::Base("Join the rats on the grain barge", 166));

        Controls = Story::Controls::STANDARD;
    }
};

class Story121 : public Story::Base
{
public:
    std::string PreText = "";

    Story121()
    {
        ID = 121;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You grow steadily weaker on the meagre diet of scraps.\n\nYou LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        if (player.Life > 0)
        {
            PreText += "\n\nSince it is too dangerous to risk lighting a fire, some of the others suggest catching rats and salting strips of their flesh to eat when the rations run out. The thought is as revolting to you as it is to Caiaphas the rabbi.\n\n\"Is it our destiny to spend our last days like ravening beasts?\" he asks. \"No! We are the Chosen People -- let us go forth and die gloriously against the Overlord's men.\"\n\nHe snatches up his spear and climbs the steps to the trap door, but then you call out something that stops him in his tracks, and he and the other Judain all turn to look at you in a new light.\n\n\"Die gloriously?\" you say. \"Why do that, when we can win?\"\n\nFor the first time in days, there is a look of hope in their eyes. They wait to hear your plan. You must not let them down.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 131; }
};

class Story122 : public Story::Base
{
public:
    Story122()
    {
        ID = 122;

        Text = "The casting of the Rulership spell was most inadvisable. You are attacking the mind of a being that has already overcome and subdued those minds and bodies of millions before you. Do you think they were all feeble-minded dolts eager to share Hate's embrace? Hate's mind is like a god's, incomprehensible and unfathomably powerful. With a great cry of joy you throw wide your arms and plunge into the hot purple softness of Hate, to join the eternal orgy of despair. There is no one left to save the Judain now. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story123 : public Story::Base
{
public:
    Story123()
    {
        ID = 123;

        Image = "images/filler2.png";

        Text = "You steal up behind one of the Jade Warriors and throw yourself against its sword arm, wrenching the blade from its grasp.\n\n\"Obey me, Jade Warriors of the Megiddo dynasty!\" you cry on impulse.\n\nTheir only response is to whirr and swivel towards you and advance with swords aloft. There seems no escape from their deadly flashing blades, and you cry out in agony as your stolen sword is dashed from your grip and you are cut to the bone.\n\nYou LOSE 4 Life Points.";

        Bye = "You flee from the tomb chamber.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -4);
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story124 : public Story::Base
{
public:
    Story124()
    {
        ID = 124;

        Text = "You dart across the street and snatch up the SWORD before the dog-handler can stop you. The dog starts to run forward, but you prod it with the point of the SWORD and it goes skulking back to its master with its tail between its legs.\n\nYou look round for Lucie. She is heading towards the Old Quarter, probably to the Silver Eel tavern which is one of her haunts. You know it as a dubious drinking-house whose customers have a dangerous reputation.";

        Choices.clear();
        Choices.push_back(Choice::Base("Follow Lucie now", 261));
        Choices.push_back(Choice::Base("Return to Bumble Row for the time being and seek her out this afternoon", 371));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::SWORD});
    }
};

class Story125 : public Story::Base
{
public:
    Story125()
    {
        ID = 125;

        Text = "You reach the safety of one of the buildings just as the horsemen reach the first farmstead and begin torching it. There are nearly thirty of them, cruel looking men and well armed -- clearly they are brigands who have donned the uniforms of the Overlord's men.\n\nThe peasants have fled to the hills; those who were too slow to make off with their most treasured possessions have to plead for their lives.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Rely on your magic and make yourself invisible", 18, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Throw in your lot with them, hoping they will let you join their band", 64));

        Controls = Story::Controls::STANDARD;
    }
};

class Story126 : public Story::Base
{
public:
    Story126()
    {
        ID = 126;

        Text = "You grab Ruth by the shoulder and pull her into the cess-pit at the back of the empty house. The smell is revolting, and you nearly throw up when you have to push your face down into the rancid ordure. The guards conduct a search of the vicinity and one of them pokes his head through the open doorway, but it does not occur to him that anyone could bring themselves to take cover where you have done. Indeed, the very art of concealment is to hide where your enemy does not think to look!\n\nWhen they have gone, you help Ruth out into the street. \"We look like two escaped lunatics,\" she wails, wiping the greasy muck off her face.\n\n\"It's nothing that a few pails of water won't cure,\" you assure her. \"I can't say we'd be as easy to set right after a spell in the prison.\" Bidding her good-day, you return to your hideout.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 414; }
};

class Story127 : public Story::Base
{
public:
    Story127()
    {
        ID = 127;

        Text = "Bracing yourself, you crouch with both hands holding your sword aloft. The monster wraps itself around the sword point, constricts and pierces itself. There is no blood but with one mighty rip you cleave the thing in twain. It flops on the floor, twitching slightly, then falls still. Only sorcery can create a beast without any lifeblood in it.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay here to see what new trick or trap will test you next", 139));
        Choices.push_back(Choice::Base("Retreat back into the catacombs", 161));

        Controls = Story::Controls::STANDARD;
    }
};

class Story128 : public Story::Base
{
public:
    Story128()
    {
        ID = 128;

        Text = "You have no difficulty, even in these troubled times, finding a foreign merchant who will give you 600 gleenars for the diamond. You know it is worth much more than that, but the merchant shows you the gold in a sack. \"Others could promise more,\" he points out, \"but you might wait for ever to get your hands on the gold. I offer an immediate exchange.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Accept the deal (GET 600 dinars)", 190, Choice::Type::GAIN_MONEY, 600));
        Choices.push_back(Choice::Base("Refuse the deal", 190));

        Controls = Story::Controls::STANDARD;
    }
};

class Story129 : public Story::Base
{
public:
    Story129()
    {
        ID = 129;

        Text = "The gold plume sways as the Jade Warrior swivels its head to observe you closely, brandishing its sword as it does so. It clicks and whirrs ominously as it advances to do battle. You steal up behind the Jade Warrior and throw yourself against its sword arm, wrenching the blade from its grasp.\n\nThe other warriors close in around you and though you defend yourself ably with the Jade Warrior's sword you are no match for three magical bodyguards of the Megiddo dynasty vaults. You are slain and there is no one left who can save the Judain. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story130 : public Story::Base
{
public:
    std::string PreText = "";

    Story130()
    {
        ID = 130;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The youth is quick and he moves to stab you in the back as you flee.";

        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            PreText += "\n\n[AGILITY] You are faster and soon leave him behind.";
        }
        else if (Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
        {
            PreText += "\n\n[ELFIN BOOTS: AGILITY] You are faster and soon leave him behind.";

            Character::LOSE_ITEMS(player, {Item::Type::ELFIN_BOOTS});
        }
        else
        {
            PreText += "\n\nYou feel a sharp cold pain as the blade bites into sinew and muscle and rasps against your shoulder blade.\n\nYou LOSE 1 Life Point as blood stains your clothes dark red.";

            Character::GAIN_LIFE(player, -1);

            if (player.Life > 0)
            {
                PreText += "\n\nYou are lucky it was not a killing blow. This guttersnipe is good with his knife. \"I thought you Judain had black blood,\" he sneers as he lets you go.";
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 201; }
};

class Story131 : public Story::Base
{
public:
    Story131()
    {
        ID = 131;

        Text = "The Judain have long had a system for moving gold around the city unseen. They now carry messages in the same way, using dives and back streets, safe houses, and, sometimes, even the catacombs. You can contact all the Judain through them, but their morale is low. So many of their kith and kin have been carried off to Grond.\n\n\"Do not despair. Are we not a proud people?\" you say. \"We have many advantages. First, the Overlord fears us, or why else would he turn his guards against us? Second, we know the secret ways bentath the city and we can already, pass messages without fear of interception. Third, we have a leader now: me.\" Caiaphas protests, \"But what can we do? We are not armed. Each of us has already lost a loved one, swinging in an iron cage. We will all stiffer the same fate if we come out of hiding.\"\n\n\"Then we will stay hidden, strike only at night, always in a different part of the city. Let us strike fear into the hearts of the good burghers of Godorno. Let no one say the Judain are cowards.\"\n\n\"And we have money, stashed in the vaults under the warehouses in The Crescent Canal Avenue.\" \n\n\"How much?\"\n\n\"A talent. The weight of a man in gold.\" This is unlooked-for good news. The cunning Judain can do much with their money. Men can be bought as easily in the godforsaken city of Godorno as anywhere.";

        Choices.clear();
        Choices.push_back(Choice::Base("Suggest holding a meeting in one of the old warehouses on Crescent Avenue", 106));
        Choices.push_back(Choice::Base("Give the word to stay hidden but organize into cells of five people each with a different target", 175));

        Controls = Story::Controls::STANDARD;
    }
};

class Story132 : public Story::Base
{
public:
    Story132()
    {
        ID = 132;

        Text = "\"You want to ask Skakshi,\" says one of the four men.\n\n\"Where is he to be found?\"\n\nThey laugh mockingly at this. \"In the Inn of the Inner Temple, of course -- when he's not out jewelling, that is!\"\n\nYou will get no more out of them.";

        Choices.clear();
        Choices.push_back(Choice::Base("Order a drink from the bar", 113));
        Choices.push_back(Choice::Base("Join Lucie and the tall stranger", 227));
        Choices.push_back(Choice::Base("Leave", 199));

        Controls = Story::Controls::STANDARD;
    }
};

class Story133 : public Story::Base
{
public:
    Story133()
    {
        ID = 133;

        Text = "Each of the Jade Warriors has a vivid plume of feathers adorning his helmet. One is azure, another black, the third is viridian and the fourth old gold. You decide to try to take one of their SWORDs, but which one will you take?";

        Choices.clear();
        Choices.push_back(Choice::Base("Take that of the of the azure-plumed warrior", 182));
        Choices.push_back(Choice::Base("... the viridian warrior", 123));
        Choices.push_back(Choice::Base("... the black-plumed warrior", 11));
        Choices.push_back(Choice::Base("... the warrior decked in old gold", 129));

        Controls = Story::Controls::STANDARD;
    }
};

class Story134 : public Story::Base
{
public:
    Story134()
    {
        ID = 134;

        Text = "Which barge will you stow away on? The first is a big barge which is little more than a wide raft. It has a huge pile of lime for cargo.\n\nThe second has just been unloaded; it is an ordinary grain barge, and you can see rats scavenging the dropped grains of corn.\n\nThe third is a smaller barge with a shallow draught. It is loaded with barrels under a tarpaulin.";

        Choices.clear();
        Choices.push_back(Choice::Base("Choose the first barge", 152));
        Choices.push_back(Choice::Base("Board the second barge", 166));
        Choices.push_back(Choice::Base("Board the third barge", 183));

        Controls = Story::Controls::STANDARD;
    }
};

class Story135 : public Story::Base
{
public:
    std::string PreText = "";

    Story135()
    {
        ID = 135;

        Image = "images/filler1.png";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You grasp the AMULET but it burns you. You must be in mortal peril for the stone to burn so fiercely. As it is your hand is scorched.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        Choices.clear();

        if (player.Life > 0)
        {
            PreText += "\n\nThe odour of your own charred flesh is added to the pervading stench of corruption and decay that has settled over the city like a shroud. You have dropped the PENDANT and it is smouldering on the carpet, melting the filigree. It is too hot to pick up.";

            Character::LOSE_ITEMS(player, {Item::Type::MAGIC_AMULET});

            if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
            {
                Choices.push_back(Choice::Base("Jump onto the bed without stepping on the carpet", 98));
            }
            else if (Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
            {
                Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS to Jump onto the bed", 98, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            }
            else
            {
                Choices.push_back(Choice::Base("Jump onto the bed without stepping on the carpet", 140));
            }

            Choices.push_back(Choice::Base("Look about to find where the danger lurks", 140));
        }

        Text = PreText.c_str();
    }
};

class Story136 : public Story::Base
{
public:
    Story136()
    {
        ID = 136;

        Text = "With a word of power and a clap of your hands you bring forth a great fog of noxious gas. Mameluke succumbs immediately; when the fog clears you can see he has sunk completely under the purple shimmering translucent surface of the monster. Hate doesn't seem to have suffered any ill effects from the spell, though its body convulses as it throws out a purple coil to envelop you. You turn tail and flee back to Bumble Row as quickly as you can, mourning the loss of a brave dear friend.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 159; }
};

class Story137 : public Story::Base
{
public:
    Story137()
    {
        ID = 137;

        Text = "Hate sends another barrage of baneful magic against you, but you walk forth without fear. The sky above turns from indigo to the deep grey of night. The monster looms ahead of you like a great crag in the darkness of the street. You begin to recite to yourself: \"Yea, though I walk in the valley of the shadow of death, I will fear no evil...\"\n\nA tentacle lashes out with the force of a steel cable, only to recoil in a hissing. Hate gives vent to a bellow of pain. It cannot abide to touch you, for your soul carries none of the taint on which it thrives.\n\nYou advance until you are right in front of the monster. Its maw gapes like a great cavern from which the fetid gusts of its breath waft dreadfully.";

        Choices.clear();
        Choices.push_back(Choice::Base("Step into Hate's maw", 400));
        Choices.push_back(Choice::Base("Look around for a weapon to use against it", 295));

        Controls = Story::Controls::STANDARD;
    }
};

class Story138 : public Story::Base
{
public:
    Story138()
    {
        ID = 138;

        Text = "The KNIVES are perfect for the job. You send them end over end in quick succession into the bloated gasbag of a body which is punctured. Black ichor sprays all over the room and the spider hunches up against the ceiling to die. The KNIVES from are now out of reach high in the dead spider's web.\n\nYou step up to the frame and hold the JEWEL aloft in both hands. The room is suffused with a glow of power. At last you have a weapon with which to combat Hate. Now all you have to do is bring it safely down from the tower.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::THROWING_KNIVES});
    }

    int Continue(Character::Base &player) { return 308; }
};

class Story139 : public Story::Base
{
public:
    Story139()
    {
        ID = 139;

        Text = "It is no trick or trap which faces you now but the tramping feet of the Overlord's personal bodyguard which alert you to danger. It sounds as if a troop of twenty men or so is approaching down one of the corridors. You can hear barked orders, they know there is an intruder.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stand your ground", 350));
        Choices.push_back(Choice::Base("Retreat into the catacombs", 161));

        Controls = Story::Controls::STANDARD;
    }
};

class Story140 : public Story::Base
{
public:
    Story140()
    {
        ID = 140;

        Text = "The leap was further than you thought. As you take off, after a short run up, your foot slips and you sprawl forward onto the carpet. The silver and gold filigree springs out of the weave and binds itself around your limbs, tightening and cutting into your flesh. You are held fast.\n\nAbove you black shape detaches itself from the underside of the canopy of the Overlord's four-poster bed and settles heavily over you. Its skin sports rows of barbed spines that inject a poison into your bloodstream. Try as you might, you can't break free. The poison turns your blood to cloying syrup and your heart stops beating. You have died with revenge for the Judain almost within your grasp. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story141 : public Story::Base
{
public:
    Story141()
    {
        ID = 141;

        Image = "images/madman.png";

        Text = "It is not hard to make contact with others of your kind. The Judain are well known for their sharpness and cunning. Word has been passed round among the Judain that all is not well with the other inhabitants of the city. Hundreds of people have mysteriously disappeared without trace. Something or somebody is carrying off the people of Godorno as they sleep.\n\nThere is a rumble outside as a town house crashes to the ground, killing its occupants. The very foundations of Godorno are rotten to the core.\n\nA madman totters down the street shouting in a hoarse croak, \"We have brought it all upon ourselves. Too much evil, bad living, we are miserable sinners suffering the retribution of divine punishment...\" He totters on, lapsing into a babble as he is pelted with mud by women washing clothes in a water butt.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 212; }
};

class Story142 : public Story::Base
{
public:
    Story142()
    {
        ID = 142;

        Text = "On your way past Bagoe you pass a series of shrines to various deities and demigods, including one sacred to the Judain. The farmer and his daughter say goodbye to you here, leaving a large watermelon and advice as to how to find the road ahead. Then they are gone. You may never meet such kind and gentle people again.\n\nThe shrine is a circle within a circle of white marble arches hung with creeper, set up on a hillside. Inside the shrine, which hasn't been visited for some time, you find the holy book of teachings, The Songs of Suleiman, which tells of the Judain's flight from captivity and their search for the Promised Land. It is full of the most marvellous stories of heroism in the face of stark adversity. The stories of your great people lift up your heart and give you the strength to dare to be a hero and the saviour of your people. You decide to return to the god-forsaken city of Godorno. The understanding you gain here in this shrine means you will never nurture hatred in your heart.\n\nYou gained the codeword SATORI.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story143 : public Story::Base
{
public:
    std::string PreText = "";

    Story143()
    {
        ID = 143;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "There are four guards, tall heavy-looking men with cold hard eyes. Each has a sword in his right hand and a dirk with a spike for catching blows in the left. You launch yourself into them with a ferocious cry which makes them hesitate. You cannon into the nearest, jabbing him hard in the midriff, and he doubles up in pain. Then another of the guards recovers his wits and lashes out at you. You have to fight your way past them.\n\n";

        auto DAMAGE = -3;
        auto USE_SHIELD = true;

        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::SWORDPLAY, Skill::Type::UNARMED_COMBAT, Skill::Type::AGILITY}))
        {
            DAMAGE = -1;

            if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
            {
                PreText += "[SWORDPLAY] ";
            }

            if (Character::VERIFY_SKILL(player, Skill::Type::UNARMED_COMBAT))
            {
                PreText += "[UNARMED COMBAT] ";

                USE_SHIELD = false;
            }

            if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
            {
                PreText += "[AGILITY] ";

                USE_SHIELD = false;
            }
        }
        else if (Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
        {
            DAMAGE = -1;

            PreText += "[ELFIN BOOTS: AGILITY] ";

            Character::LOSE_ITEMS(player, {Item::Type::ELFIN_BOOTS});
        }

        Character::GAIN_LIFE(player, DAMAGE);

        if (USE_SHIELD && Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY) && Character::VERIFY_ITEMS(player, {Item::Type::SHIELD}))
        {
            Character::DAMAGE(player, Skill::Type::SWORDPLAY, Item::Type::SHIELD, DAMAGE);

            PreText += "Your SHIELD absorbs " + std::to_string(-DAMAGE) + " Damage.";
        }
        else
        {
            PreText += "You LOST " + std::to_string(-DAMAGE) + " Life Point(s).";
        }

        if (player.Life > 0)
        {
            PreText += "\n\nDeciding that you cannot fight them all, you lead the guards off along the street. They cannot keep up with you in their heavy armour and you soon lose them. Doubling back, you meet up with Ruth and escort her back to Copper Street. She promises to tell Caiaphas you have saved her life. You bid her good-bye and return to your hideout.";

            if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
            {
                Character::REMOVE_CODEWORD(player, Codeword::Type::VENEFIX);
            }
            else
            {
                Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});

                PreText += "\n\nYou gained the codeword SATORI.";
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 414; }
};

class Story144 : public Story::Base
{
public:
    Story144()
    {
        ID = 144;

        Text = "Standing beneath the Tower of the Sentinel, which looms three hundred feet above you against the glowering dusk sky, you feel very small and alone. If the greatest thieves of Godorno have tried to climb this tower and failed, what hope is there for this poor Judain?\n\nAt the top of the Sentinel's tower, the JEWEL OF SUNSET FIRE shines like a shooting star. The JEWEL OF SUNSET FIRE is a so-called eye of power that can vanquish evil. The sheer-sided tower is of chequered grey and red mosaic tiles, overlain with the black grime of centuries. It has stood on this spot since before the coming of the corsairs who ravaged the Old Empire. It was the lighthouse for Godorno before the sea level dropped in the great cataclysm. Looking up at the gaunt forbidding tower as it juts against the grey sky you are reminded of the frontispiece of a book you saw once -- The Tale of Nuth, Prince of Thieves -- which tells of the vain attempt to steal the JEWEL by the greatest thief of the Old Empire.\n\nThe black gate is reached under a trellis which is woven thickly with purple kiss-flowers, that smell unpleasantly like honeysuckle. To your surprise it opens at your touch and you walk into the atrium where small trees are growing in tubs. There is a curving marble staircase that leads up into the tower itself and you begin your long and dangerous climb.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 29; }
};

class Story145 : public Story::Base
{
public:
    Story145()
    {
        ID = 145;

        Text = "You flourish your SWORD and swipe at the black monster. It wraps itself around the blade and starts to entwine itself around your arm.";

        Choices.clear();
        Choices.push_back(Choice::Base("Throw down the SWORD", 163));
        Choices.push_back(Choice::Base("Try to prize your arm free without relinquishing your beloved WEAPON", 178));

        Controls = Story::Controls::STANDARD;
    }
};

class Story146 : public Story::Base
{
public:
    Story146()
    {
        ID = 146;

        Text = "Somehow you survive the outside staircase and the other perils of the tower and live to see another day. You are the first to survive the Tower of the Sentinel in a very long time. Disconsolately you return to Bumble Row to hatch another plot. You cannot return to the Tower of the Sentinel as you dare not face that hideous spider agam.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story147 : public Story::Base
{
public:
    Story147()
    {
        ID = 147;

        Text = "You cleave the great tentacle in two, missing Lucie as though by a miracle. You have done it. Leaping to the top of the parapet of the Bargello, you grab the Jewel of Sunset Fire from inside your jerkin and climb up into the last rays of daylight. As you do so you see the world's most terrifying sight. Rising slowly out of the hole that was once the old quarter of the city is the head of Hate itself. Two baleful green eyes twice the height of a man glare at you as the slow bulk of Hate starts to ooze towards the parapet. The eyes are ringed by the faces of the most depraved lost souls, all beckoning you to join them. They still live on, crushed side by side and looking out to see what Hate sees. They have quite lost their minds.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::GORDIAN}))
        {
            return 107;
        }
        else
        {
            return 375;
        }
    }
};

class Story148 : public Story::Base
{
public:
    Story148()
    {
        ID = 148;

        Text = "What a noble deed you have just done. They let Mameluke go and grasp you instead. They have no regard for the Judain and beat you to a pulp in the street, where they leave you to die. You will perish here and there is no one left to save the Judain.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story149 : public Story::Base
{
public:
    Story149()
    {
        ID = 149;

        Text = "With a clap of your hands you cast a Thunderflash spell. There is a blinding light and a whipcrack, then the smell of seared flesh. The living carpet is a writhing, boiling sea of serpentine coils. You have certainly distracted the snakes. You run in boldly. The living carpet writhes beneath the soles of your feet and there is a baleful hissing.\n\nOne of the snakes sinks its fangs into the soft flesh of your calf but you make it to the other side and slam the door shut behind you. The venom of the garter snake is virulent indeed and your blood burns while you fight for breath.\n\nYou LOSE 4 Life Points.";

        Bye = "You find yourself looking up another spiral staircase. Once outside the door the snake coils loosen and it glides to the floor and out of sight.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -4);
    }

    int Continue(Character::Base &player) { return 180; }
};

class Story150 : public Story::Base
{
public:
    Story150()
    {
        ID = 150;

        Image = "images/giant-spider.png";

        Text = "The ceiling o( the room is clear crystal. The dome of crystal that tops the tower is supported by huge iron struts from a black boss directly above the jewel. You look up as you start to cross the floor to the casket, just as a flash of lightning illuminates everything in stark outline. The angled struts are in fact the legs of a giant spider whose eyes seem to follow your every move as you inch slowly beneath the arches of its legs.\n\nThe keening of the gargoyles reaches a new frenzied high and the crystal that protects you from the tower-spinning spider explodes into shards and dust. The wind falls away, the keening drops to a low moan and now you hear for the first time the wheezing susurratioins of the spider's breath. You can see its thorax opening and closing like a bellows.";

        Choices.clear();
        Choices.push_back(Choice::Base("Dash beneath it to seize the JEWEL and CASKET", 164));
        Choices.push_back(Choice::Base("Attack it from the doorway", 186));

        Controls = Story::Controls::STANDARD;
    }
};

class Story151 : public Story::Base
{
public:
    Story151()
    {
        ID = 151;

        Text = "As soon as you place your heel against the soft flesh of Hate it disappears from sight and the flesh turns to liquid, engulfing you up to the waist.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            return 91;
        }
        else
        {
            return 335;
        }
    }
};

class Story152 : public Story::Base
{
public:
    Story152()
    {
        ID = 152;

        Text = "There is nowhere to hide but inside the lime. There is lime dust everywhere, and wherever you go you leave a trail of chalky footsteps. You try to rub the footsteps away and burrow into the lime, leaving a small hole next to your nose to breathe through. As you lie there in the lime you daren't move in case someone sees you. But what if a small part of you is uncovered? Your dark clothes will be spotted against the white lime.\n\nYour uncomfortable wait is ended when someone pokes a boathook into your side. The bargees clear the lime away from your head under the eyes of a group of the Overlord's soldiers.\n\n\"It's a Judain,\" says one of the soldiers. Their captain orders them to knock you out and throw you in the river. Stuck inside the heavy mound of lime you are helpless as they cosh you over the head. You are food for the fishes.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story153 : public Story::Base
{
public:
    Story153()
    {
        ID = 153;

        Text = "Caiaphas looks very long-faced at your question. \"If it's the keys to the secret ways beneath the city you want then talk to Melmelo, the Master Thief. But beware. Nameless horrors lurk in the ever-nighted labyrinths... things best left undisturbed.\"\n\nThe only way you know of contacting Melmelo is by asking a thief. The only place you can be sure to find a thief when you want one is The Inner Temple, an inn in the middle of the oldest part of the city.\n\nThe streets are being patrolled by the Overlord's men.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::STREETWISE))
        {
            Choices.push_back(Choice::Base("Risk the streets", 307));
            Choices.push_back(Choice::Base("Try to stow away inside a slaver's cart and pass unseen", 31));
        }
    }

    int Continue(Character::Base &player) { return 59; }
};

class Story154 : public Story::Base
{
public:
    Story154()
    {
        ID = 154;

        Text = "With a word of power you unleash the Baffiement spell. It has no discernible effect on the monster but one of the guards goes glassy-eyed and his head lolls back into the pillow of Hate's body, to be submerged for ever in the orgy of despair. The monster convulses suddenly, throwing a coil out towards you. You decide it is time to flee back to your hidey-hole on Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 159; }
};

class Story155 : public Story::Base
{
public:
    Story155()
    {
        ID = 155;

        Text = "Your journey to Bagoe on the Palayal river is charmed. You find food dropped in a sack by the side of the path and are treated to a beer at an inn. At Bagoe you are welcomed aboard a barge and the bargees promise to hide you when you near Godorno. They say you will easily be able to slip ashore, unseen in the dead of night.\n\nThey are as good as their word and one fine dawn you find yourself back in Godorno, with the wharfs and warehouses behind you and the city before you. The revetments of the buildings lend the city an unmistakable air of patrician hauteur. This is the hub of the civilized world.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 300; }
};

class Story156 : public Story::Base
{
public:
    Story156()
    {
        ID = 156;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            return 47;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            return 28;
        }
        else
        {
            return 19;
        }
    }
};

class Story157 : public Story::Base
{
public:
    Story157()
    {
        ID = 157;

        Image = "images/filler1.png";

        Text = "One of the swords has a halo which shines brighter than the others. You steal up behind the Jade Warrior and throw yourself against its sword arm, wrenching the BLADE from its grasp.\n\n\"Obey me, Jade Warriors,\" you cry out on impulse. To your relief and amazement they line up before you and stand to attention. The warrior from whom you took the sword picks up another from behind an awning. The warriors are ready to do your bidding. They whirr and click as they follow you dutifully to the edge of the precincts of the burial chambers, and there they grind to a halt. There is nothing you can do to move them further. Although you cannot command the Jade Warriors to go forth and attack Hate, you tell them that they must attack Hate if it should loop its coils into the burial chambers of the Megiddo dynasty. You leave all doors and traps wide open in the hope that Hate will blunder in and get carved up.\n\nSure enough, when you return the next day the place shows the signs of an epic battle. Great gouts of translucent flesh hang from lintel and corners. There is a fine green powder in the air, like pulverized glass. The Jade Warriors have been ground to dust by Hate but, judging by the quantity of purple ichor smeared over the walls, they must have given the monster acute indigestion.\n\nYou OBTAINED a JADE WARRIOR's SWORD. You gained the codeword HECATOMB.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::JADE_WARRIORS_SWORD});

        Character::GET_CODEWORDS(player, {Codeword::Type::HECATOMB});

        Take = {Item::PLUMED_HELMET};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story158 : public Story::Base
{
public:
    Story158()
    {
        ID = 158;

        Text = "As a Judain in Godorno you have become used to being treated with disdain. You didn't want to drink anyway. The two women favour you with glances dripping with disdain, as if you were something someone had scraped off the heels of their boots. Try as you can to keep calm, this kind of prejudice is really upsetting. They are street sluts, no better, perhaps worse than slaves, yet here they are treating you like a worm. Still if you are to be tolerant then you must apply that understanding to members of their ancient profession just as you would wish them to extend it to all Judain.\n\nDetermined to find out what Lucie is up to you walk over to the couple, who are watching you intently. Lucie smiles as she did when you met her in the Garden of Statues.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 227; }
};

class Story159 : public Story::Base
{
public:
    Story159()
    {
        ID = 159;

        Text = "You have the word passed round to all the cells to lie low. Until further orders your people will cease their campaign of terror against the Overlord's men. A pity -- they had almost won control of the streets. They are dying, though: day by day, Hate takes off more of your fellow Judain to the orgy of eternal despair, where they are joined by hundreds more of the Overlord's men and thousands of the ordinary folk of the city. You will have to vanquish Hate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 6; }
};

class Story160 : public Story::Base
{
public:
    Story160()
    {
        ID = 160;

        Text = "You must decide your next bold stroke to free the city from the grip of hatred and unreason.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SUNSET}))
        {
            return 337;
        }
        else
        {
            return 100;
        }
    }
};

class Story161 : public Story::Base
{
public:
    Story161()
    {
        ID = 161;

        Text = "You slink back into the catacombs, dousing your lantern so you will not be discovered. You are soon under the stables. It is cold and damp down here, but there is a strong breeze, almost a gale. The air should be still here under the city, like the nighted airs of the pyramids of the ancients. Hate has undermined it so much that part of the catacombs have come to light, you guess. That means the monsters that have lurked here since the city was built will be wandering out onto the streets to add to the woes of the poor cityfolk. Since the storm drains prove to be blocked, you enter the burial crypts of the Megiddo dynasty.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 365; }
};

class Story162 : public Story::Base
{
public:
    Story162()
    {
        ID = 162;

        Text = "At the top of the last set of eight steps is a landing. The inside wall is covered by a tapestry and there is a single arrow slit in the outside wall. As you walk beside the tapestry gazing for a moment at its depiction of the labours of Coronus, the floor spins and you are shot backward through the tapestry into another room.\n\nYou are standing on a wooden platform. There are four other platforms in the room, the furthest in front of the only door. There is nothing to show how you came through the wall behind you and no way of return.\n\nThe floor of the room is submerged under a living carpet of orange and black garter snakes. It is too far to jump to the nearest platform above the snakes, but there is a rope hanging from the ceiling half-way between you and it.";

        Choices.clear();
        Choices.push_back(Choice::Base("Jump for the rope and hope to swing onto the next platform", 115));
        Choices.push_back(Choice::Base("Make a dash for it through the mass of snakes", 60));
        Choices.push_back(Choice::Base("Use [CHARMS]", 168, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Silver Shield to push the snakes aside", 80, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Thunderflash to stun them", 149, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Miasma to poison them", 10, Skill::Type::SPELLS));

        Controls = Story::Controls::STANDARD;
    }
};

class Story163 : public Story::Base
{
public:
    Story163()
    {
        ID = 163;

        Text = "You throw down the SWORD just in time as the monster tries to lap its black wings over you. The Overlord begins to wake up and the monster floats up again to attack you. You decide discretion is the better part of valour and retreat, leaving the concubine to her fate. By the look of her she will be one of Hate's many guests before the night is out.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 161; }
};

class Story164 : public Story::Base
{
public:
    Story164()
    {
        ID = 164;

        Text = "As you make a dash for the jewel the spider drops to flatten you. Its heavy bloated black sack of an abdo- men engulfs you and you are borne to the floor, where you begin to suffocate. Terror lends you the strength of seven men but even as you try to fight your way clear so the spider's venom does its deadly work. The likeness of you at the top of the stairs did indeed tell the story of your grisly and hopeless fate. The JEWEL OF SUNSET FIRE cannot so easily be stolen from the tower. There is no one left to save the Judain now. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story165 : public Story::Base
{
public:
    Story165()
    {
        ID = 165;

        Text = "The Thunderflash spell was the right choice for such circumstances. The bang makes the walls of the prison reverberate with echoes. There is a flare of spurting red fire which sears and burns the cloying purple softness of the monster, which convulses and expels some of the guards. The purple flesh is cauterized and it recedes, allowing a few more of the guards to break free as the coil twitches and recoils. Those still caught implore their comrades to stay and free them but not one of those you have freed waits to help a friend. They bolt for it, but then they are either terrified or in shock.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 34; }
};

class Story166 : public Story::Base
{
public:
    Story166()
    {
        ID = 166;

        Text = "To your dismay, the rats, instead of fleeing, set up an angry chittering as if protesting at your trespass. They are sleek with grain and their yellow teeth look needle sharp. Some are more than a foot long and evil looking. A bargee hears them and rouses a couple of his mates. They start to amble in your direction.";

        Choices.clear();
        Choices.push_back(Choice::Base("Hide in the barge laden with lime", 152));
        Choices.push_back(Choice::Base("Hide under the tarpaulin on the smallest of the barges", 183));

        Controls = Story::Controls::STANDARD;
    }
};

class Story167 : public Story::Base
{
public:
    Story167()
    {
        ID = 167;

        Text = "The casting of a Thunderflash spell makes the walls of the neighbouring houses reverberate with echoes. There is a flare of spurting red fire which sears and bums the cloying purple softness of the monster. It convulses and expels Mameluke, who rolls onto the floor, then struggling to his feet, wiping the strands of gelid purple slime from his body with the backs of his hands.\n\nHe thanks you and would embrace you as a friend, but you step back, anxious to avoid contamination by the putrescent slime of Hate.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take him back with you to your hidey-hole on Bumble Row", 177));
        Choices.push_back(Choice::Base("Lose him in the byways of the city", 239));

        Controls = Story::Controls::STANDARD;
    }
};

class Story168 : public Story::Base
{
public:
    Story168()
    {
        ID = 168;

        Text = "You start to swing your AMULET like a pendulum and begin to hum softly. The heads of the snakes sway gently in time, like wheat in the summer breeze. Still humming the charm, you step onto the living carpet which writhes beneath your sole, while baleful hisses warn you not to linger. Garter snakes coil around your thighs but they are nestling there and do not bury their venom-tipped fangs in your soft flesh.\n\nYou step trancelike across the living carpet of snakes and through the far door, where you face another spiral staircase. Once outside the door the snake coils loosen and they glide to the floor out of sight.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 180; }
};

class Story169 : public Story::Base
{
public:
    Story169()
    {
        ID = 169;

        Text = "How will you make the landlord pay attention to you?";

        Choices.clear();
        Choices.push_back(Choice::Base("[UNARMED COMBAT] Hurdle the bar and brawl with him", 179, Skill::Type::UNARMED_COMBAT));
        Choices.push_back(Choice::Base("Try-bribing him to tell you about Lucie and her foreign friend (3 gleenars)", 189, Choice::Type::MONEY, 3));
        Choices.push_back(Choice::Base("[SPELLS] Use magic", 219, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Approach Lucie and her ominous friend", 227));
        Choices.push_back(Choice::Base("Leave the tavern", 199));

        Controls = Story::Controls::STANDARD;
    }
};

class Story170 : public Story::Base
{
public:
    Story170()
    {
        ID = 170;

        Text = "You steal up behind one of the Jade Warriors and throw yourself against its sword arm, wrenching the blade from its jade grasp.\n\n\"Obey me, Jade Warriors of the Megiddo dynasty!\" you cry on impulse.\n\nTheir only response is to swivel towards you and advance with swords aloft. There seems no escape from their deadly flashing blades, and you cry out in agony as your stolen sword is dashed from yo ur grip and you are cut to the bone.\n\nYou LOSE 4 Life Points.";

        Bye = "You flee from the tomb chamber.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -4);
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story171 : public Story::Base
{
public:
    Story171()
    {
        ID = 171;

        Text = "The return journey takes no longer than the outward trek and you are soon faced with the battlemented towers and guarded walls of Godorno, city of the Forsaken. Carrion crows, habitually solitary scavengers, wheel in great flocks above the city and the wind carries the dismal cries of the unfortunates being tortured in the prison fortress of Grond to your unwilling ears.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stow away aboard a barge on the Palayal river and re-enter the city that way", 155));
        Choices.push_back(Choice::Base("Present yourself at the gate and bluff your way through", 188));

        Controls = Story::Controls::STANDARD;
    }
};

class Story172 : public Story::Base
{
public:
    Story172()
    {
        ID = 172;

        Text = "At least this way you live to fight another day. You reach the bottom of the tower again safely and as you walk back out onto the path to the street the great bronze doors swing shut with a sound like the knell of doom. You try the gates but they are sealed shut. You needn't worry -- Melmelo, the guildmaster of thieves, probably just wanted to get his own hands on the jewel. He can go to the trouble of finding it for himself. You slink back to Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story173 : public Story::Base
{
public:
    Story173()
    {
        ID = 173;

        Text = "With a word of power and a clap of your hands you bring forth a great cloud of noxious vapours, the Miasma. Several of the guards succumb immediately, sinking beneath the glassy purple surface for the last time. The spell doesn't seem to have affected the monster but it convulses suddenly, throwing a dripping purple coil out at you. You decide it is time to flee back to your lair on Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 159; }
};

class Story174 : public Story::Base
{
public:
    Story174()
    {
        ID = 174;

        Text = "Exploiting the rekindled morale of the Judain resistance and the other townsfolk who are rallying to your banner, you make your plans for the defence of the city. If you construct barricades in certain sectors of the city you can challenge the Overlord's authority. If his men cannot capture the barricades all will know that the writing is on the wall; it will only be a matter of time before you are storming the palace.\n\nThe barricade is composed of flagstones and carts, doors stripped from nearby deserted houses, and even pews from the nearest temple. The carts have been laden with mud. Even an elephant could not break through. The blockage is ten feet high and in places a parapet has been built on the defender's side from which potshots can be taken at the Overlord's city guards as they advance. You have archers in the windows and on the roofs of the houses on either side of the barricade. Morale is high; the stories of your exploits have placed you high in the esteem of your people.\n\nBut you have not chosen the sites for your barricades well. The Overlord's guards are quick to exploit your mistake. They pour a rain of crossbow quarrels from the roof into the brave defenders, slaughtering many, before charging the barricade. The ensuing battle is a slaughter. The guards have roused themselves to one last great effort to reclaim the streets of the city and they are putting the brave defenders to the sword. You decide discretion is the better part of valour and retreat to Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 41; }
};

class Story175 : public Story::Base
{
public:
    Story175()
    {
        ID = 175;

        Text = "You muse on the good fortune of finding your fellows so well provided for. \"A talent, more than I could have hoped for in my wildest dreams. With a talent of gold we can buy all the help we need.\"\n\n\"Ah, but taking gold from Judain is a capital offence, punishable by impalement.\"\n\n\"Even talking to a Judain is a capital offence, unless you are interrogating one.\"\n\n\"Are we not the Judain? Have we not the merchant's silver tongue? We have never wanted for those to do our bidding in the past.\"\n\n\"In the past the people were not in the grip of fear. Where once they thought of lining their pockets they now count themselves lucky if they can line their stomachs and stay out of trouble.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 190; }
};

class Story176 : public Story::Base
{
public:
    std::string PreText = "";

    Story176()
    {
        ID = 176;

        Bye = "You conduct a quick search of the upper rooms and leave as soon as you have the DIAMOND.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You must silence the soldier quickly, before his cries bring the neighbours. But even as you race up the stairs towards him, your thoughts are awhirl with the mystery of what went wrong. There was no fault in your magic. However, the plan relied on everyone in the house being asleep at the instant you cast the charm. Evidently this one soldier was awake guarding the DIAMOND, so the charm failed to affect him. You can well imagine his fright and confusion when he heard you moving around downstairs and then discovered that everyone else in the house was in a deathly deep sleep from which he could not rouse them.\n\nThe first sweep of his sword is clumsy. You dodge in under his guard anxious to end the fight as quickly as possible. You have fought much tougher opponents in your time.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
        {
            DAMAGE = 0;

            PreText += "[SWORDPLAY] You SUFFER NO LOSS of Life Points.";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::UNARMED_COMBAT))
        {
            DAMAGE = -1;

            PreText += "[UNARMED COMBAT] ";
        }

        if (DAMAGE < 0)
        {
            Character::GAIN_LIFE(player, DAMAGE);

            PreText += "You LOST " + std::to_string(-DAMAGE) + " Life Point(s).";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 358; }
};

class Story177 : public Story::Base
{
public:
    Story177()
    {
        ID = 177;

        Text = "Mameluke is glad to accompany you back to your little hidey-hole on Bumble Row. \"I see the toymakers and panderers have shut up shop some time since,\" he remarks. \"It used to be such a gay place, Bumble Row.\"\n\n\"Nothing but a dive for dogs like us in these cursed times,\" you say wryly.\n\n\"Don't be hard on yourself! You saved my life. How can I repay you?\"\n\n\"Forget it. I am happy just to see you free and breathing.\"\n\n\"I will help you in any way I can,\" he tells you. \"Remember, you just have to call on me and I'll be there.\"\n\n\"Thanks, Mameluke. It's good to have at least one true friend when all around are turning to hatred. For a start you can help me plan what to do next.\"\n\n\"I suppose we could flee the city?\"\n\n\"No. My place is here. I want to save my people -- not just my people; all the citizens.\"\n\n\"And you are the one to save all, a youngster like you?\" he asks with affectionate mockery.\n\n\"Who else is there?\" You explain to Mameluke how you have organized the Judain resistance and Mameluke is amazed at what you have done. The word from the palace is that the Overlord's soldiers are deserting in droves rather than patrol the city streets, which they have come to see as a fate worse than death. So your tactics are working.\n\n\"But it's not the Overlord who is our real enemy; it's the monster, Hate.\"\n\nHe gives you a frightened look. \"But what can we do against Hate itself?\"\n\n\"We need to find out everything we can about it. I will contact those with an ear inside the palace. Perhaps the Overlord has entered into some God-forsaken compact with the monster.\"\n\nYou wish Mameluke farewell and ponder how you can confront your inimical foe.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 6; }
};

class Story178 : public Story::Base
{
public:
    Story178()
    {
        ID = 178;

        Text = "The underside of the black monster is lined with barbed thorns which inject poison into your bloodstream. Try as you might, you can't break free. The poison turns your blood to cloying syrup and your heart stops beating. You have died when revenge for the Judain was almost within your grasp. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story179 : public Story::Base
{
public:
    Story179()
    {
        ID = 179;

        Image = "images/tough-guy.png";

        Text = "He is a tough-looking burly man and obviously used to dealing with rowdies like yourself. He snatches up a bottle ready to smash it against your skull. He had not reckoned with your skill at [UNARMED COMBAT], however. You wrestle with him, throwing him against the bar repeatedly and then seizing his right arm and twisting it up behind his back. Your skill and speed are too much for his brute strength -- and your mental attitude has been hardened by adversity as you have watched the rape of your people.\n\nHe is in pain now and submits, becoming totally still. You make him pour you a drink of ale and ask him about Lucie and her friend.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 209; }
};

class Story180 : public Story::Base
{
public:
    Story180()
    {
        ID = 180;

        Text = "Various cabbalistic signs like ancient cave paintings have been daubed on the outside of the topmost door in terracotta and charcoal. If your hopes are not disappointed the JEWEL OF SUNSET FIRE lies inside this topmost room.\n\nAt the top of the staircase is a series of frescoes showing the tower and depicting the grisly fates that befall those who rashly try to climb it. To your absolute horror and consternation the final fresco is a picture of you, squashed fiat beneath a gigantic bloated black spider. Above the spider you can see the orb shining brightly in its frame.\n\nYou walk on up a narrower spiral of stairs that lines the outer wall and at last pause before the final door. Gingerly you push it open, wincing at the creak of its rusty hinges. There is a brooding presence of evil here. Your heart hammers in your chest as you step forward.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 150; }
};

class Story181 : public Story::Base
{
public:
    Story181()
    {
        ID = 181;

        Text = "You think to relieve Skakshi of any weapons lest he attempt to double-cross you. Although he protests he has no more, a quick frisk of his clothing reveals a set of THROWING KNIVES. You look grimly at him, but he gives a weak smile, and says: \"I like to keep something up my sleeve for contingencies -- you'd do the same.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::THROWING_KNIVES};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 291; }
};

class Story182 : public Story::Base
{
public:
    Story182()
    {
        ID = 182;

        Text = "You steal up behind one of the Jade Warriors and throw yourself against its sword arm, wrenching the blade from its armoured grasp.\n\n\"Obey me, Jade Warriors of the Megiddo dynasty!\" you cry on impulse, but their only response is to advance on you with swords aloft. There seems no escape from their deadly flashing blades, and you cry out in agony as your stolen sword is dashed from your grip and you are cut to the bone.\n\nYou LOSE 4 Life Points.";

        Bye = "You flee from the tomb chamber.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -4);
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story183 : public Story::Base
{
public:
    Story183()
    {
        ID = 183;

        Text = "An hour before dusk the members of the crew return from whichever wine cellar they have been squandering their money in and prepare to cast off. They look over their cargo briefly but do not notice you huddled under a pile of ropes. They sing as they pole the barge, a sombre song with a pounding beat about how a man may toil his whole life away and at the end have nothing to show for it but the clothes he will die in.\n\nYou guess from the movements of the barge it has turned up the Palayal river. You are being borne towards the Great Forest. You guess they are making for the town of Bagoe twenty miles upriver. You lie still, listening to the lapping of water at the bows and feeling the rhythmic surge as the crew drives the barge on, poling in time. After three hours of dirges the crew tie up for the rest of the night against the deserted riverbank. While they snore you leap from barge to shore and walk inland to the Bagoe road.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 222; }
};

class Story184 : public Story::Base
{
public:
    std::string PreText = "";

    Story184()
    {
        ID = 184;

        Bye = "The reek of camphor and honeysuckle makes your head reel. Staggering under Hate's onslaught, you look up to see the largest of its tentacles smashing down towards you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You fight a pitched battle (ace to face with Hate, your blade hacking great quivering chunks out of its loathsome warty mass. The people of the city peer timidly from the cracked facades of their houses, astonished to see such bravery from a single lone Judain. Hate screams and lashes out at you, raining rubble down on your head in its frenzy to stop the punishing blows you are inflicting.\n\n";

        auto DAMAGE = -8;

        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            DAMAGE = -5;

            PreText += "[CHARMS] Blind luck protects you. ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::GORDIAN}))
        {
            return 54;
        }
        else
        {
            return 103;
        }
    }
};

class Story185 : public Story::Base
{
public:
    Story185()
    {
        ID = 185;

        Text = "You are turning the corner into Hanging Gardens -- once one of the wonders of the world, now a tumbledown jungle of rubble and festooned plants rioting over the houses -- when your face starts to itch unpleasantly. You are only half-way to Mameluke's garret and the broad-shouldered black man is striding on ahead, confidently. The pink mucus of Hate is infesting you. Mameluke looks at you with concern as your eyes become vacant and you are assailed by numbing dreams in which you walk open-armed into the embrace of Hate, to join in the orgy of despair. Mameluke is tugging at your arm and pulling you along the road towards Chink Street where his poor garret perches atop a building like a landlocked lighthouse. The cry of the city guard nearby urges Mameluke to greater efforts as the doleful dirge of 'Bring out your dead, bring out your dead,' tolls mournfully from the nearby Courtyard of Idle Fancies.";

        Choices.clear();
        Choices.push_back(Choice::Base("Send Mameluke on alone", 211));
        Choices.push_back(Choice::Base("Try to keep up with him as the guards approach", 221));

        Controls = Story::Controls::STANDARD;
    }
};

class Story186 : public Story::Base
{
public:
    Story186()
    {
        ID = 186;

        Text = "How will you attack the giant spider that lurks so menacingly above? The fresco outside the door warned you only too clearly of your fate should you falter or fail.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Conjure a gas cloud", 79, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Conjure a flash of stunning force", 73, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Conjure multiple illusory images to confuse your foe", 208, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Throw a set of THROWNING KNIVES", 138, {Item::THROWING_KNIVES}));
        Choices.push_back(Choice::Base("Throw the JADE WARRIOR's SWORD", 234, {Item::JADE_WARRIORS_SWORD}));
        Choices.push_back(Choice::Base("Make a dash into the room, beneath the gigantic spider, and make a grab for the JEWEL", 164));

        Controls = Story::Controls::STANDARD;
    }
};

class Story187 : public Story::Base
{
public:
    Story187()
    {
        ID = 187;

        Text = "You are forced to confront Hate without a weapon or strategy. You have only your own qualities as a hero to help you in this battle.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            return 137;
        }
        else
        {
            return 295;
        }
    }
};

class Story188 : public Story::Base
{
public:
    Story188()
    {
        ID = 188;

        Text = "The gate is manned by grim-looking sentries in the uniform of the Overlord's city watch. There are four of them, sitting two and two on benches set into the wall of the gatehouse that spans the road between the two gates. The outer gate opens outward into the countryside and the inner gate opens inwards into the city. Each man has a sword and a crossbow, though their bows look a little rusty with lack of use. They are slovenly soldiers, doubtless very corrupt.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Go invisible", 207, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Control their minds with magic", 218, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[STREETWISE] Bluff your way through", 229, Skill::Type::STREETWISE));
        Choices.push_back(Choice::Base("Try bribing them", 191));

        Controls = Story::Controls::STANDARD;
    }
};

class Story189 : public Story::Base
{
public:
    Story189()
    {
        ID = 189;

        Text = "Placing a money pouch on the bar, you ask, \"Tell me about Lucie. Does she frequent the Silver Eel often? And who is her companion?\"\n\nThe landlord pockets the money pouch after first weighing it carefully in his hand. He glances nervously at the gang of four and says, \"Yes, she haunts this place often. She's never alone. I see some of them again and again but she has a lot of friends, does little Lucie. She's an ornery girl that one. Knows her own mind and no mistake. Forever taking up with the most disreputable mountebanks and desperadoes. Always twists 'em round her little finger, mind.\"\n\n\"And what about her friend?\"\n\n\"That's Tyutchev, a foreigner. See how pale he is? Doesn't it make you feel ill just to look a.t him? He usually comes in with his doxy, Cassandra -- or is it he is her pretty boy? She's a terrible proud and beautiful woman, wearing gear like a Fury from the Abyss. At any rate, they had a terrible fight in here last week. I never saw a woman wield a sword with such skill and venom. It glowed cold blue, and where it struck the bar I found crystals of ice.\"\n\n\"Who won the fight?\" you ask, incredulous.\n\n\"They were both bleeding badly. It was a terrible battle. But they went out together. I do declare I've never had the misfortune to serve two less pleasant and outright perilous characters.\"\n\n\"What do they all want with Lucie?\" you wonder aloud.\n\nHe cracks a rancid-toothed smile. \"What does any man want with Lucie?\"\n\nYou thank the landlord for his information and, leaving the alepot on the bar, walk over to the couple, who are watching you intently. Lucie smiles as she did when you met her in the street.\n\nYou LOST 3 gleenars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, -3);
    }

    int Continue(Character::Base &player) { return 227; }
};

class Story190 : public Story::Base
{
public:
    Story190()
    {
        ID = 190;

        Image = "images/filler3.png";

        Text = "Your allies suggest various places for you to make a hideout and you choose a damp cellar on Medallion Street -- it seems the best option. You are on your way there when there is a commotion ahead of you. Seeing a group of city guards approaching, you duck into the ruin of an abandoned building. To your dismay, they stop in the street outside and you hear one of them say, \"A Judain went in here, I think. Fetch the dogs -- they'll soon sniff the wretch out!\"\n\nThere is a frightened whimper in the darkness behind you. You whirl to see Caiaphas\"s wife, Ruth -- the one who was reluctant to share the food with you. You remember hearing from Caiaphas that she is with child. She is hidden, trembling, behind a pillar at the back of the hall. You know that the guards will not return to barracks until they have caught their quota of Judain.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::ROGUERY, Skill::Type::CHARMS, Skill::Type::STREETWISE}))
        {
            Choices.push_back(Choice::Base("Use [ROGUERY]", 126, Skill::Type::ROGUERY));
            Choices.push_back(Choice::Base("[CHARMS] Use magic", 116, Skill::Type::CHARMS));
            Choices.push_back(Choice::Base("Make use of [STREETWISE] here", 105, Skill::Type::STREETWISE));
        }
        else
        {
            Choices.push_back(Choice::Base("Dash out into the street and fight the guards to buy Ruth time to escape", 143));
            Choices.push_back(Choice::Base("Push her out into the street to save yourself -- surely they will not harm a pregnant woman", 240));
        }
    }
};

class Story191 : public Story::Base
{
public:
    Story191()
    {
        ID = 191;

        Text = "As you step through the outer gate one of the ill-favoured guards closes the inner one against you with a loud thud, while another pushes shut the outer gate, to trap you, not minding the protestations of an old woman coming into the city to sell eggs, who is now barred. If they realize you are Judain they could turn you in. There is little doubt that they would, these men are more known for their greed than their scruples.\n\nThere is a placard on the inside gate proclaiming that the reward for turning in a Judain has been increased to thirty gleenars. You guess the Judain are encouraged to try to bribe their way to freedom and so the pogrom is making the Overlord rich as the prisoners are tricked out of their worldly wealth yet still left to rot in Grond.\n\nThe reward, however, is more money than the gold you carry on you, which is all you have.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            return 232;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::CUNNING))
        {
            return 250;
        }
        else
        {
            return 260;
        }
    }
};

class Story192 : public Story::Base
{
public:
    Story192()
    {
        ID = 192;

        Text = "You hack wildly at the cloying purple flesh of Hate, opening up great gashes in its side which pour out vile yellow pus. As fast as you cut so the tentacle twitches, spasms and convulses, sucking the wretched guards into its soft embrace. You are not making any progress, you are just burying the guards deeper in the morass of despair.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try using the flat of your SWORD instead", 370));
        Choices.push_back(Choice::Base("Try to torch the purple flesh of Hate", 228));
        Choices.push_back(Choice::Base("Ask some of the trapped guards what to do", 215));
        Choices.push_back(Choice::Base("[SPELLS] Conjure a poisonous fog", 173, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Conjure a blast of energy", 165, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast a spell of Baffiement", 154, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast a spell of Rulership", 122, Skill::Type::SPELLS));

        Controls = Story::Controls::STANDARD;
    }
};

class Story193 : public Story::Base
{
public:
    Story193()
    {
        ID = 193;

        Text = "If you escape, the guards will slaughter Mameluke. He calls out for you to run and save yourself. \"It's not worth losing your life over me. You have much to do. I could almost imagine you were a Tartar, such is your courage.\"\n\nMameluke hasn't lost his loquacity even in the moment of his downfall.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            return 244;
        }
        else if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::CUNNING, Skill::Type::STREETWISE}))
        {
            return 264;
        }
        else
        {
            return 278;
        }
    }
};

class Story194 : public Story::Base
{
public:
    Story194()
    {
        ID = 194;

        Text = "The lepers would follow you to the ends of the earth. As the pinnacles and battlements of Grond come into view they murmur unhappily but still shuffie hopefully along in your wake. They tell you they have been chained to the walls of their sanatorium from the time they contracted the disease. It is hard to imagine what fierce spark of life drives these people on, but there they are shuffiing in your wake. Two are travelling on tea trays with wheels attached, shifting lumps of iron forwards and backwards, to make their makeshift carts move over the rough cobbles. It is enough to break your heart to look at, but then you have seen much, much worse.\n\nTurning into Last Rites Street you are faced by the looming vastness of Grond. The grey stone matches the pallid skin of your pathetic band. The guard shut and barricade the gates against your motley crew before you can demand the release of the prisoners.";

        Choices.clear();
        Choices.push_back(Choice::Base("Offer some of the Judain's gold to the captain of the guard, in exchange for access to the prison fortress", 206));
        Choices.push_back(Choice::Base("[SPELLS] Try ensorcelling your way in", 268, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Threaten to infect the guards with the slow rotting death of leprosy to see if that will loosen the gates", 259));

        Controls = Story::Controls::STANDARD;
    }
};

class Story195 : public Story::Base
{
public:
    Story195()
    {
        ID = 195;

        Text = "The apprehension in your people is almost palpable as they face their sternest test by far -- pitched battle with the Overlord's guard. You buoy their spirits by promising them a fine banquet in the Overlord's palace by nightfall. Your enthusiasm is infectious and they are ready to follow you now. You decide to accompany one of the detachments led by your fellow Judain, who have no military training but enjoy the respect of their people. You go with Caiaphas to the barricade facing the Grand Canal.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 353; }
};

class Story196 : public Story::Base
{
public:
    Story196()
    {
        ID = 196;

        Text = "Lucie's eyes sparkle with malice. \"This is the Judain who slew your captain, Overlord. This guilty wretch deserves to die.\"\n\n\"And die the poor wretch will, undoubtedly, after interrogation.\" Lucie's smile of triumph is dripping with hatred. Something must have happened to her mind, else why would she lie and betray you. She is not the same girl you met standing in the rain near the Palazzo del Megiddo. She isn't behaving as she would with the riff-raff she usually disports herself with. Hate has got to her, just as it is taking over the minds of all the wretches of Godorno.\n\nNone the less you are fated to die in the prison fortress of Grond. By tomorrow your body will be hanging in an iron cage outside the Overlord's palace as a warning to the Judain to give up their futile struggle. There is no one left to save them now. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story197 : public Story::Base
{
public:
    Story197()
    {
        ID = 197;

        Text = "You recognize some of those present as senior members of the Thieves' Guild, grown rich on the juicy pickings of the latterday well-to-do of Godorno. They are well dressed, urbane looking men.\n\n\"Skakshi, I see you lurking there. I have a proposition to put to Melmelo -- just the thing for Godorno's master thief.\" You know Skakshi likes to think of himself as the master thief of Godorno. He is no friend to Melmelo the Guildmaster.\n\n\"I can take you to Melmelo for the price I would be given if I turned you over to the city guard: ten gleenars. Do you have ten gleenars, Judain scum?\"\n\nThere are chuckles from the other customers at Skakshi's insolence.";

        Choices.clear();
        Choices.push_back(Choice::Base("Teach him a lesson in how to talk to his betters", 281));
        Choices.push_back(Choice::Base("Agree to this bargain (10 gleenars)", 291, Choice::Type::LOSE_MONEY, 10));
        Choices.push_back(Choice::Base("Tell Skakshi you will never pay his blood money", 43));

        Controls = Story::Controls::STANDARD;
    }
};

class Story198 : public Story::Base
{
public:
    Story198()
    {
        ID = 198;

        Text = "Tyutchev has led you into a trap. As a net is dropped from an archway above, entangling you, Tyutchev spins on his heel and slices yout head from your shoulders with a single blow of his sword. You took one chance too many. No one is left to save your people now.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story199 : public Story::Base
{
public:
    Story199()
    {
        ID = 199;

        Image = "images/filler3.png";

        Text = "As you hurry away from the inn, you remember you have to attend the meeting of the heads of the resistance cells. As you make your way quickly through the desolate streets, you pass an old man pushing a cart filled with curios. He is Tarkamandor, a collector and trader who deals in enchanted items.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stop to talk to him", 51));
        Choices.push_back(Choice::Base("Press on to the meeting without delay", 94));

        Controls = Story::Controls::STANDARD;
    }
};

class Story200 : public Story::Base
{
public:
    Story200()
    {
        ID = 200;

        Text = "You take your usual care in the alleys and backways of the old city but this time your sixth sense has failed you. An assassin has you in the sights of his crossbow. A poisoned bolt catches you in the shoulder, spinning you round so that you fall in an ungainly heap on the cobblestones. Someone had marked you out, for what reason, you will never know. There is no one left to save the Judain now. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story201 : public Story::Base
{
public:
    Story201()
    {
        ID = 201;

        Text = "This street winds down towards the riverfront and the centre of the city. It is crossed by large avenues lined with tall straight cedars that lead up to the citadel. You hear the ringing of the town crier's bell. At the end of the street is Greenbark Plaza. Here a large walled flowerbed encircles a rare sight. It is a greenbark tree, eighty feet tall. The smooth bark is striped lime green and grey-green and the heart-shaped leaves are golden yellow. There is a shrine here to the tree spirit with a few offerings of potash and wine.\n\nNext to the shrine is the town crier dressed in his traditional black and gold tabard. He unfurls a scroll and begins to declaim to the gathered crowd. He is flanked by a bodyguard of the Overlord's men armoured in black leather. You push forward to hear better.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 254; }
};

class Story202 : public Story::Base
{
public:
    Story202()
    {
        ID = 202;

        Text = "Being among friends has its advantages. An old moneylender, Sekritt the Blind, has just such a PENDANT as you might use as a MAGICAL AMULET. It was pawned to him by an itinerant sorcerer many years ago. You are lucky. He was about to sell it to a young sorceress who had decided to risk trying to escape from the city down the catacombs -- an unwise move if ever there was one.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::HAS_SKILL(player, Skill::Type::CHARMS))
        {
            if (!Character::VERIFY_ITEMS(player, {Item::Type::MAGIC_AMULET}))
            {
                Character::GET_ITEMS(player, {Item::MAGIC_AMULET});
            }
        }
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story203 : public Story::Base
{
public:
    Story203()
    {
        ID = 203;

        Text = "As you go to step on a piece of mosaic majolica, your foot feels no resistance. You have stepped off the side of the tower and with a dreadful heave of the stomach you realize you are falling two hundred feet to be smashed on the rocks of what was once the entrance to Old Godorno harbour. Who will save your people now? Not you, a shattered body at the base of the Tower of the Sentinel.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story204 : public Story::Base
{
public:
    Story204()
    {
        ID = 204;

        Text = "You quickly ignite the incense, and smoke billows forth from the censer. The Jade Warriors are soon swathed in the roiling white clouds, and you grope your way through the smoke towards them. One of the warriors looms towards you, the light gleaming dully now off its facets and its sword is working mechanically. You recoil in fright but it lumbers past making elaborate passes in the air, as if engaged in a display of an ancient style of swordplay. The others are also lurching about at random. The smoke seems to have scrambled their senses. Each is cutting and thrusting at the air around it but they seem oblivious of you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE) && !Character::VERIFY_ITEMS(player, {Item::Type::BOOK_OF_MYTHS_AND_LEGENDS}))
        {
            return 133;
        }
        else
        {
            return 119;
        }
    }
};

class Story205 : public Story::Base
{
public:
    Story205()
    {
        ID = 205;

        Text = "You pole the boat as fast as you can to the nearest bank. Behind you there is a splash and a snort as an ugly but harmless sea cow breaks the surface of the water. You are exhausted from your attempt at flight, however, and step from the boat to rest at the edge of the murky canal, sitting on the road and basking in the midday sun.\n\nSoon you have the uneasy feeling of being watched.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 374; }
};

class Story206 : public Story::Base
{
public:
    std::string PreText = "";

    Story206()
    {
        ID = 206;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "How much gold are you offering me?\" From his tone of voice you can tell the guard does not believe you.\n\n\"The weight of a man's forearm in real red gold. You'll be rich beyond your wildest dreams.\"\n\nHe snorts. \"There is not so much wealth in the whole city, outside the Overlord's palace!\"\n\n\"The Overlord has indeed sucked the city dry in his greed. But what of the usurers, the bankers? They have kept their stash of gold safe underground in these troubled times.\"\n\nHe fixes you with a suspicious glare. \"Bring me the gold and I'll hand over the keys. I'll not be responsible for the mayhem which follows. I won't be your scapegoat, Judain.\"\n\n\"If you are wise,\" you tell him, \"you'll quit the city at the first opportunity, never to return.\"\n\nYou need 500 gleenars to cover the bribe you have offered him.";

        Choices.clear();

        if (player.Money < 500)
        {
            PreText += "\n\nYou must find the money somewhere else. It is unlikely that the other Judain would willingly part with most of the resistance fund for such a risky venture.";

            Choices.push_back(Choice::Base("Try selling some of your possessions", 235));
            Choices.push_back(Choice::Base("[SPELLS] Use magic to make them accept any specious argument you come up with", 288, Skill::Type::SPELLS));
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 415; }
};

class Story207 : public Story::Base
{
public:
    Story207()
    {
        ID = 207;

        Text = "Your spell of Invisibility works as neatly as it always does. You congratulate yourself and make a mental note you could earn good money as a teacher of spellcasting at a sorcerer's academy. You walk to the gate unseen, just in front of an old woman who has come to the city to sell eggs. As you step through the outer gate one of the guards closes the inner one against you, while another pushes shut the outer gate, not minding the protestations of the old woman, who is now trapped beside you.\n\n\"My wife could do with a dozen eggs for pancakes,\" he says to her. \"Haven't you heard about the Overlord's new tax, old woman? The egg tax!\"\n\n\"Leave my eggs alone. It was all I could do to glean enough grains of wheat to feed my poor little chicks. You wouldn't take an old woman's livelihood would you? Not an old woman who's never done you any harm, nor wouldn't want to?\"\n\nThe guards decide to have a little fun at the woman's expense. Their captain is lounging bored on a seat beside the wall. Your invisibility will wear off soon.";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast Miasma", 362));
        Choices.push_back(Choice::Base("Cast Visceral Pang", 372));
        Choices.push_back(Choice::Base("Cast Rulership", 382));

        Controls = Story::Controls::STANDARD;
    }
};

class Story208 : public Story::Base
{
public:
    Story208()
    {
        ID = 208;

        Text = "The gigantic spider rocks back and forth, seemingly transfixed by the apparitions of you which have appeared on either hand. You have indeed won more time. It seems the spider cannot make a choice between three absolutely identical targets. It is not clever enough to begin a process of elimination.";

        Choices.clear();
        Choices.push_back(Choice::Base("Attack it with an energy spell", 290));
        Choices.push_back(Choice::Base("Create a cloud of poisonous smoke", 79));

        Controls = Story::Controls::STANDARD;
    }
};

class Story209 : public Story::Base
{
public:
    Story209()
    {
        ID = 209;

        Image = "images/couple.png";

        Text = "\"I need some information. Perhaps you can help me?\" You wait for the landlord's reply, knowing that if you can get him to say yes he will probably end up telling you what you want to know.\n\n\"Maybe I can,\" he concedes gruffly.\n\n\"Tell me about Lucie. Does she frequent the Silver Eel often? And who is her companion?\"\n\n\"She might, then again she might not. What's it to you?\"\n\n\"If she's the girl I think she is, she has come into an inheritance. I'm trying to find out whether she is in fact the girl in question. I am sure she will be very appreciative of any help you can give.\"\n\nHis eyes light up with the thought of a reward. \"Yes, she haunts this place often. She's never alone. I see some of them again and again -- but she has a lot of friends, does little Lucie. She's an ornery girl that one. Knows her own mind and no mistake. Forever taking up with the most disreputable mountebanks and desperadoes. Always twists 'em round her little finger, mind.\"\n\n\"And what about her friend?\"\n\n\"That's Tyutchev, a foreigner. See how pale he is? Doesn't it make you feel ill just to look at him? He usually comes in with his doxy, Cassandra -- or is it he is her pretty boy? She's a terrible proud and beautiful woman, wearing gear like a Fury from the Abyss. At any rate, they had a terrible fight in here last week. I never saw a woman wield a sword with such skill and venom. It glowed cold blue, and where it struck the bar I found crystals of ice.\"\n\n\"Who won the fight?\" you ask, incredulous.\n\n\"They were both bleeding badly. It was a terrible battle. But they went out together. I do declare I've never had the misfortune to serve two less pleasant and outright perilous characters.\"\n\n\"What do they all want with Lucie?\" you wonder aloud.\n\nHe cracks a rancid-toothed smile. \"What does any man want with Lucie?\"\n\nYou thank the landlord for his information and, leaving the alepot on the bar, walk over to the couple, who are watching you intently. Lucie smiles as she did when you met her in the street.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 227; }
};

class Story210 : public Story::Base
{
public:
    Story210()
    {
        ID = 210;

        Text = "You reach the scene of the disaster by late afternoon. There is no sign of Lucie. The shack where she was hiding has been levelled to the ground. A great pit has opened up beneath it and looking down into it you smell the galling purulent stench of corruption that comes from the coils of Hate.\n\nIs Lucie now just another lost soul, forced to live a half-life of torment within the corrupt flesh of Hate itself? You can't ask anyone if they have seen her, for they would not tell you if they had, out of fear of the Overlord's men.";

        Choices.clear();
        Choices.push_back(Choice::Base("Attempt to search for her down the hole", 360));
        Choices.push_back(Choice::Base("Abandon her to her grisly fate", 252));

        Controls = Story::Controls::STANDARD;
    }
};

class Story211 : public Story::Base
{
public:
    Story211()
    {
        ID = 211;

        Text = "Mameluke doesn't realize how sick you are. His cheerfulness is wearing until he goes on ahead to light the fire and warm his rooms up for you. As soon as his broad back bobs out of sight round the corner you sink, exhausted, to the cobbled ground. The city watchmen are clip-clopping over the cobbles towards you on horseback.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            return 244;
        }
        else if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::CUNNING, Skill::Type::STREETWISE}))
        {
            return 264;
        }
        else
        {
            return 278;
        }
    }
};

class Story212 : public Story::Base
{
public:
    Story212()
    {
        ID = 212;

        Image = "images/filler1.png";

        Text = "As you walk warily along Last Rites Street you see a captain of the guard, whom you remember is called Tormil, agreeing to help a citizen flee the city in return for most of his worldly weath. Only a rat like Tormil would take advantage of people's helplessness so callously. You stand in front of him and revile him for taking advantage of the oppressed.\n\n\"If I were not due to take over my guard duties at the palace I would slay you on the instant, Judain scum. But I swear I will bring you before the Overlord in chains.\" With that he sets out for the palace.\n\nHis victim waits nearby until Tormil has rounded a corner and is safely out of sight, before plucking up courage to talk to you.\n\n\"As it is some time before Tormil can fulfil his pledge to help me leave, might I return your kindness?\" he asks.\n\nHe barely gives you time to nod your acceptance before continuing in his nasal tones: \"I am, or was until recently, a jeweller's assistant in Mire Street. Alas my own honesty has put me out of a job, and left me in fear of my life. I must leave the city.\n\n\"Yet perhaps I may be revenged on my employer, and you may strike a blow for the Judain against the Overlord. A DIAMOND owned by a Judain shopkeeper I once knew, is now at my master's shop being fashioned into a mighty sceptre for the Overlord. Finding out my connection with the previous owner, however, my master went to call the Overlord's guards so that I might be taken away and thrown into Grond to languish there with my Judain friend. It is clear_ to see my master favours not the Judain, nor those who would be their friends.\n\n\"I beg you to reacquire the DIAMOND, if not for my friend, then for the Judain cause. Here is the address.\"\n\nHe gives clear directions to the jeweller's shop in Mire Street before making his farewells. He parts company saying, \"Not all are against the Judain. Goodbye.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Turn your mind to acquiring the DIAMOND to order to finance the resistance effort", 241));
        Choices.push_back(Choice::Base("Search for a hideout", 190));

        Controls = Story::Controls::STANDARD;
    }
};

class Story213 : public Story::Base
{
public:
    Story213()
    {
        ID = 213;

        Text = "Your search for another AMULET is interrupted by the venomed blade of Skakshi the master thief. He has crept up on you unseen and unheard as only a master rogue can. He turns the knife in your vitals and you die at his hands. If only you hadn't lost your charm AMULET it might have warned you of the danger. There is no one left to save the Judain now. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story214 : public Story::Base
{
public:
    Story214()
    {
        ID = 214;

        Text = "It is time to spy out the lay of the land. Only by prowling around the streets yourself will you know what is really happening. As you pass towards the foreigners' quarter you are greeted silently by many of your people from their look-out and alarm posts. They melt away at the first sign of soldiers, so you are far from safe on the streets.\n\nTurning a corner you come upon a most distressing sight. A virulent throbbing mass of purple slime presses up through a fissure into the sewers of the city. On a pile of rubble, many figures are caught in the sticky slime like flies on a piece of honey-smeared paper.\n\nYou recognize one of the faces staring out mutely, barely submerged under a violet sheen of skin. It is the daughter of Torrriil, the captain of the palace guard who has sworn to deliver you to the Overlord in chains. Tormil's own daughter has fallen into the embrace of Hate. She is just another lost soul now. You decide to show her to Tormil; then you can ask him to join you in the resistance or try to trick him into joining his daughter, enmeshed in the coils of Hate.\n\nYou find Tormil on his journey home from the sword practice halls. You call to him from a dark alleyway and he stops and peers at you. \"Come with me, Captain Tormil. I have something to show you.\"\n\n\"What do you want with me?\"\n\n\"I have found your missing daughter. I want nothing but to bring you to her.\"\n\n\"Lead on. I will follow -- at a distance. No tricks.\" He follows you warily to the fallen wall. You scramble to the top of the pile of rubble and point. He stands beside you and gazes into the dull glassy eyes of his daughter, who tries to reach out a hand towards him, but cannot.\n\nTormil breaks into tears, then flourishing his sword, he runs down the rubble slope to hack at the bloated form of Hate.";

        Choices.clear();
        Choices.push_back(Choice::Base("Let him die: glad to see him meet his doom in Hate's coils", 95));
        Choices.push_back(Choice::Base("Try to save him", 265));

        Controls = Story::Controls::STANDARD;
    }
};

class Story215 : public Story::Base
{
public:
    Story215()
    {
        ID = 215;

        Text = "The guards crane their heads towards you, desperate for you to save them. They goggle at you comically, as if they have never seen a person free to walk about on the earth before.\n\n\"Here, grab my hand,\" implores one of the guards, who is standing in Hate up to his knees. He tries to smile at you but it is the smile of a traitor.";

        Choices.clear();
        Choices.push_back(Choice::Base("Grab his proferred hand and drag him out", 25));
        Choices.push_back(Choice::Base("Ignore him and pass on down the line", 13));

        Controls = Story::Controls::STANDARD;
    }
};

class Story216 : public Story::Base
{
public:
    Story216()
    {
        ID = 216;

        Text = "The water of the pool is cloudy and you cannot be sure how deep it is. Touching it cautiously reveals it is cold but not deathly cold and to the taste it is as pure as spring water.";

        Choices.clear();
        Choices.push_back(Choice::Base("Step in", 245));
        Choices.push_back(Choice::Base("Skirt round to the side of the pool", 203));

        Controls = Story::Controls::STANDARD;
    }
};

class Story217 : public Story::Base
{
public:
    Story217()
    {
        ID = 217;

        Text = "Hardly daring even to breathe, you insert a bent pin into the lock and twist it with consummate precision. No surgeon ever operated so carefully upon a patient, no swain ever gave such loving entreaties to his paramour, no artist ever wielded his brush with such fine skill, as you work now upon that tiny lock.\n\nYour diligence is rewarded; the lock abandons its duties with a soft tut. The lid of the coffer yields to your eager touch, and you allow yourself a smile as you lift out the gemstone you came for. Placing it in your mouth for safekeeping -- the sweetest lozenge you ever saw -- you skulk back noiselessly across the room and descend the stairs to emerge moments later into the night air.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 358; }
};

class Story218 : public Story::Base
{
public:
    Story218()
    {
        ID = 218;

        Text = "Touching your wand, you speak a cantrip which confuses the guards' minds so that they see you as a long-lost friend. They slap you on the back, offer you beer and wish you well in the city. The old woman, who sells eggs in the city, follows you through the city gate. She is mumbling to herself through toothless gums. She obviously can't afford a set of false teeth, which are a recent invention in Godorno and one of the wonders of modern medicine.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 380; }
};

class Story219 : public Story::Base
{
public:
    Story219()
    {
        ID = 219;

        Text = "The potent spell of Visceral Pang should suffice to bring the landlord to his knees and force him to do your bidding. You mouth the arcane words and twirl your fingers in the patterns that bring magic to life. The spell catches and the landlord's face grows pale, then very flushed. He makes a rush for the latrines but the pain pulls him up short and he doubles over in agony.\n\n\"You will serve a Judain, my good man, and be quick about it,\" you say, looking around to gauge the reaction of the other drinkers.\n\nThe two women are looking at you in a new light. The pipesmoker is tapping out his pipe. Lucie looks shocked. The eyes of the tall stranger transfix you with a piercing stare. The gang of four are all fingering hidden weapons and checking their escape routes.\n\n\"A pot of your finest ale, landlord,\" you say, letting the spell go. The landlord straightens slowly, holding his stomach, and reaches for an alepot.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask him about Lucie and the tall stranger", 236));
        Choices.push_back(Choice::Base("Ask if he knows who or what is carrying off the good burghers of Godorno and leaving their hearts bobbing in the Crescent Canal", 246));

        Controls = Story::Controls::STANDARD;
    }
};

class Story220 : public Story::Base
{
public:
    Story220()
    {
        ID = 220;

        Text = "You throw yourself down on your bed in the row of crooked houses down Bumble Row and try to sleep. A taint in the air stops your slumber and there is a sound like wet kippers being thrown onto a marble slab. It is getting louder. You roll off your bed in time to see a purple veil close over the door. Hate has sealed you in. Its skin starts to swell into a great blister which slowly expands until it covers the whole room. You are caught up in the coils of Hate and have joined the eternal orgy of despair. You cannot even save yourself now, much less your oppressed people.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story221 : public Story::Base
{
public:
    Story221()
    {
        ID = 221;

        Text = "Mameluke comes back for you when he sees you are struggling to keep up. You rest one arm over his shoulder and stagger on, supported by his strong frame. The Overlord's guard trot round the corner ahead and you pull up, scanning their faces for signs of pity. There are none.\n\n\"Get out of our way,\" says Mameluke. \"I'm taking this poor citizen home -- got mistaken for a Judain and given a pretty savage beating. Known to me for years, I'll vouch for...\"\n\n\"Get away from the wretched Judain.\"\n\nThe captain of the guard means to take you in for questioning.";

        Choices.clear();
        Choices.push_back(Choice::Base("Give yourself up and try to save Mameluke", 148));
        Choices.push_back(Choice::Base("Try to escape", 193));

        Controls = Story::Controls::STANDARD;
    }
};

class Story222 : public Story::Base
{
public:
    Story222()
    {
        ID = 222;

        Text = "You make good progress along the rutted road by the light of the moon. Most goods are carried to Bagoe by river so there are no brigands on this road. As the sun rises you pass farms growing fruit and olives, vines and tomatoes and the great purple hubloe fruit which is so popular in Godorno. Every now and then the sweep of the Palayal river comes into view where road and river run side by side. You press on, hoping to reach Bagoe before the bargees from Godorno.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 247; }
};

class Story223 : public Story::Base
{
public:
    Story223()
    {
        ID = 223;

        Text = "You draw your sword with a flourish and advance steadily on Skakshi. The landlord throws him a spiked club with which to defend himself. You can see by the way he hefts it he knows how to use it to pulp brains. Your sword gives you the advantage over his rude weapon but you have never trained against a man wielding a spiked club.\n\nHow will you fight this battle?";

        Choices.clear();
        Choices.push_back(Choice::Base("Move in close so that the smooth edge of the club shaft will fall on you if you are hit", 52));
        Choices.push_back(Choice::Base("Keep your distance and use looping cutting blows rather than fierce lunges", 32));

        Controls = Story::Controls::STANDARD;
    }
};

class Story224 : public Story::Base
{
public:
    std::string PreText = "";

    Story224()
    {
        ID = 224;

        Choices.clear();
        Choices.push_back(Choice::Base("Use the JADE WARRIOR's SWORD", 230, {Item::JADE_WARRIORS_SWORD}));
        Choices.push_back(Choice::Base("Use the JEWEL OF SUNSET FIRE", 349, {Item::JEWEL_OF_SUNSET_FIRE}));
        Choices.push_back(Choice::Base("You have neither of those items", 187));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You lure the monster to attack, then clamp the shackles of your chains around its tentacles. As you do, another tentacle swipes away the cornice of a building above and you are struck by a shower of falling masonry.\n\n";

        auto DAMAGE = -3;

        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            DAMAGE = -1;

            PreText += "[AGILITY] You dodge aside from the brunt of the rubble. ";
        }
        else if (Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
        {
            DAMAGE = -1;

            PreText += "[ELFIN BOOTS: AGILITY] You dodge aside from the brunt of the rubble. ";

            Character::LOSE_ITEMS(player, {Item::Type::ELFIN_BOOTS});
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nYou survey your handiwork. You have tethered Hate to the columns of the cathedral. If only the chains hold, you may be able to destroy it once and for all.\n\nYou gained the codeword GORDIAN.";

            Character::GET_CODEWORDS(player, {Codeword::Type::GORDIAN});
        }

        Text = PreText.c_str();
    }
};

class Story225 : public Story::Base
{
public:
    Story225()
    {
        ID = 225;

        Image = "images/mob.png";

        Text = "This street winds down towards the riverfront and the centre of the city. It is crossed by large avenues that lead up to the citadel, lined with tall straight cedars. You hear the ringing of the town crier's bell. At the end of the street is Greenbark Plaza. The mob is still chasing you, growing hysterical in its desire for your blood. If you are caught you will surely be stoned to death.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            Choices.push_back(Choice::Base("Run on into Greenbark Plaza", 2));
            Choices.push_back(Choice::Base("Duck down one of the smaller side streets", 385));
        }
    }

    int Continue(Character::Base &player) { return 369; }
};

class Story226 : public Story::Base
{
public:
    Story226()
    {
        ID = 226;

        Text = "You know a little bit about horses and can ride tolerably well. Looking at the horse you see it is flinching from its own shadow. Taking its bridle you turn it till it is facing into the sun so it can no longer see its shadow. Mounting safely, you give the horse free rein: it surges into a gallop and you hang on grimly. Luckily for you the road to the main gate is straight. Within a few minutes you can see the wooden arches of the double gate ahead. People jump aside at the last moment from the path of your frothing mount.\n\nThe horse is still galloping wildly as you approach the gate and the gate guards tumble out of their guardhouse to stop you. One tries to grab the bridle but misses and falls over. Another is winding his crossbow. As you gallop past he lets fly and the bolt catches you in the side.\n\nYou LOSE 3 Life Points.";

        Bye = "You hang on grimly as the twang of crossbows echoes from behind. Bolts zip past your ears. The horse gallops on, leaving pursuit behind. The towers and minarets of Godo mo are lost to view by the time the horse runs itself out. You dismount and carry on up the trade road on foot.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -3);
    }

    int Continue(Character::Base &player) { return 302; }
};

class Story227 : public Story::Base
{
public:
    Story227()
    {
        ID = 227;

        Text = "Tyutchev looks at you insolently. His direct stare makes you feel very uncomfortable. He has challenged many a poor fellow with a look like this, and most of them didn't live to tell the tale. Now he says, \"So a Judain comes ready for the slaughter! It's hardly worth the bother of collecting the ten gleenars' reward, but then there is the pleasure of killing you.\"\n\nHe speaks as though you were a slimebeast that had crawled out from under a stone. He draws his sword, a great one-and-a-half-hander, which he wields with negligent ease and power, as if it were a toothpick. It thrums through the air as he prepares to slaughter you. With a surprisingly quick movement for so large a man he manages to put himself between you and the only door. It doesn't look as if the latrine here backs onto the outside world so there is no escape that way. Perhaps that is why so many thieves drink here -- they are never bothered by the city guard. You have no choice but to fight.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 297; }
};

class Story228 : public Story::Base
{
public:
    Story228()
    {
        ID = 228;

        Text = "You pour oil from your lantern onto the soft cloying purple flesh of Hate but it will not kindle. Hate is inflammable. The bloated purple mass heaves as it breathes and you can make out the tracks of the lost ones' tears, deep inside the translucent body. You will have to try something else.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask some of the trapped guards what to do", 215));
        Choices.push_back(Choice::Base("Use a SWORD", 192, {Item::SWORD}));
        Choices.push_back(Choice::Base("[SPELLS] Cast Miasma", 173, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Thunderflash", 165, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Bafflement", 154, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Rulership", 122, Skill::Type::SPELLS));

        Controls = Story::Controls::STANDARD;
    }
};

class Story229 : public Story::Base
{
public:
    Story229()
    {
        ID = 229;

        Text = "\"What do you think of the disguise?\" you say before the gate guards can challenge you. \"Eh? What do you think? What do I look like?\"\n\nYou seem utterly confident and they all look at you and smile. \"Reckon you're a spitting image of a Judain, \" says one.\n\n\"Ain't I just? And I'm going to make a lot of friends among the Judain scum of the city and turn them over to the Overlord's men, for the reward. I reckon I'll make a fortune.\"\n\n\"You want to watch out. They're powerful deep people, the Judain. They stick together like like...\"\n\n\"Like rats and grain sacks!\" another puts in.\n\nYou and the old seller of eggs are allowed to proceed into the city. To your annoyance the old woman has the look of a tittle tattle. She mumbles constantly through toothless gums. \"I heard what you said in there. It ain't right. What have the Judain done to hurt you? Just raising their children as decent and honest as other folk, I'll warrant.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Tell the old woman that you really are Judain", 275));
        Choices.push_back(Choice::Base("Try to lose her in the streets and hope she does you no harm", 286));

        Controls = Story::Controls::STANDARD;
    }
};

class Story230 : public Story::Base
{
public:
    Story230()
    {
        ID = 230;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::HAS_SKILL(player, Skill::Type::SWORDPLAY) && Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            return 184;
        }
        else
        {
            return 396;
        }
    }
};

class Story231 : public Story::Base
{
public:
    Story231()
    {
        ID = 231;

        Text = "You gather the girl into your arms; she is as light as a feather pillow and quite limp. Her face is untouched by the blemishes which mar her body and she is quite beautiful, as you would expect of the Overlord's concubine.\n\nNow how are you going to get both her and yourself across the carpet without stepping on it?";

        Choices.clear();
        Choices.push_back(Choice::Base("Wrap her in the silk bedspread and drag her from the bed, after leaping clear", 319));
        Choices.push_back(Choice::Base("Carry her over your shoulderin a fireman's lift and walk quickly across the carpet", 285));

        Controls = Story::Controls::STANDARD;
    }
};

class Story232 : public Story::Base
{
public:
    Story232()
    {
        ID = 232;

        Text = "Picking the pocket of one of the guards while you hand him your gold with the other hand is child's play to someone of your accomplishments. You palm his gold to your other hand and let the coins drop one by one into his greedily outstretched palm.\n\n\"Where's my share?\" demands another of the gate guards, holding out his palm, while his other hand rests menacingly on the pommel of his rapier. You clap him on the back and empty his money pouch as you do so, also relieving him of a fine gold chain that hangs at his neck in the process. All four guards are soon happy with their own money newly shared out among them and at last you and the old seller of eggs are allowed to proceed into the city.\n\nYou OBTAINED 15 gleenars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, 15);
    }

    int Continue(Character::Base &player) { return 380; }
};

class Story233 : public Story::Base
{
public:
    Story233()
    {
        ID = 233;

        Image = "images/filler2.png";

        Text = "How will you lift the hearts of the men and women on the barricade? They are quailing before the presence of Hate. Some start to wail as they recognize loved ones sunk in the cloying purple embrace of the monster.";

        Choices.clear();
        Choices.push_back(Choice::Base("Tell them they have nothing to fear for they are of pure heart", 408));
        Choices.push_back(Choice::Base("Tell them that death on the barricade will lead to eternal salvation", 379));

        Controls = Story::Controls::STANDARD;
    }
};

class Story234 : public Story::Base
{
public:
    Story234()
    {
        ID = 234;

        Image = "images/tower.png";

        Text = "The SWORD leaves your hand like an arrow and buries itself into the bloated gasbag of a body, which is instantly ruptured. Black ichor sprays all over the room and the spider hunches up against the ceiling to die.\n\nThe JADE WARRIOR's SWORD is now out of reach high in the dead spider's web.\n\nYou step up to the frame and hold the JEWEL aloft in both hands. Now all you have to do is bring it safely down from the tower.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::JADE_WARRIORS_SWORD});
    }

    int Continue(Character::Base &player) { return 308; }
};

class Story235 : public Story::Base
{
public:
    Story235()
    {
        ID = 235;

        Text = "You find several buyers among the captains of the sailing ships moored along Tartars' Quay. Most are keen to return to their homelands before the wave of hatred and persecution engulfs them as it has your own people. No friends of the Overlord who has wrecked their livelihoods, they receive you warmly and consider your wares.\n\nAfter some deliberation, they announce the price they will pay for each item. You can sell any of the following, if you possess them: JADE WARRIOR's SWORD, JEWEL OF SUNSET FIRE, PLUMED HELMET, MAGIC WAND, MAGIC AMULET, HEALING SALVE, THROWING KNIVES.";

        Choices.clear();

        Controls = Story::Controls::SELL;
    }

    void Event(Character::Base &player)
    {
        Sell = {{Item::JADE_WARRIORS_SWORD, 500}, {Item::JEWEL_OF_SUNSET_FIRE, 1500}, {Item::PLUMED_HELMET, 50}, {Item::MAGIC_WAND, 100}, {Item::MAGIC_AMULET, 60}, {Item::HEALING_SALVE, 100}, {Item::THROWING_KNIVES, 40}};
    }

    int Continue(Character::Base &player)
    {
        if (player.Money > 499)
        {
            return 415;
        }
        else
        {
            return 6;
        }
    }
};

class Story236 : public Story::Base
{
public:
    Story236()
    {
        ID = 236;

        Image = "images/filler3.png";

        Text = "\"She's an ornery girl that one,\" he mutters after casting a look in her direction. \"Knows her own mind and no mistake. Forever taking up with the most disreputable mountebanks and desperadoes. Always twists 'em round her little finger, mind.\"\n\n\"And what about her friend?\"\n\n\"That's Tyutchev, a foreigner. See how pale he is? Doesn't it make you feel ill just to look at hjm? He usually comes in with his doxy, Cassandra -- or is it he is her pretty boy? She's a terrible proud and beautiful woman, wearing gear like a Fury from the Abyss. At any rate, they had a terrible fight in here last week. I never saw a woman wield a sword with such skill and venom. It glowed cold blue, and where it struck the bar I found crystals of ice.\"\n\n\"Who won the fight?\" you ask, although you would hardly expect the loser of a swordfight to be sitting drinking ale a week later.\n\n\"They were both bleeding badly. It was a terrible battle. But they went out together. I do declare I've never had the misfortune to serve two less pleasant and outright perilous characters.\"\n\n\"What do they all want with Lucie?\" you wonder aloud.\n\nHe cracks a rancid-toothed smile. \"What does any man want with Lucie?\"\n\nYou thank the landlord for his information and, leaving the alepot on the bar, walk over to the couple, who are watching you intently. Lucie smiles as she did when you met her in the street.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 227; }
};

class Story237 : public Story::Base
{
public:
    Story237()
    {
        ID = 237;

        Text = "The horse looks skittish. Its chestnut flanks are darkened by sweat and its eyes dart about nervously while it snorts and fidgets. It seems to be afraid of something.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::AGILITY, Skill::Type::WILDERNESS_LORE}) && Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
        {
            Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 271, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            Choices.push_back(Choice::Base("Otherwise", 289));
        }
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 271;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            return 226;
        }
        else
        {
            return 289;
        }
    }
};

class Story238 : public Story::Base
{
public:
    Story238()
    {
        ID = 238;

        Text = "You are soon trussed up, helpless, and frogmarched into the prison fortress of Grond to join hundreds more of your people. You will never see the light of day again. There is no one left to save your people now. They will all perish and be wiped from the face of the earth.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story239 : public Story::Base
{
public:
    Story239()
    {
        ID = 239;

        Text = "It is the work of just a few minutes to throw Mameluke off your trail in the old quarter of the city. You hear him calling: \"Where are you, Judain? Let us be friends. I will help you against the Overlord. Come back...\"\n\nHe screams suddenly and the gurgling sound is cut off, as though he were a pig being slaughtered. If you had taken him with you he would not now be dead -- but perhaps you should not blame yourself for the mindless ferocity of the Overlord's guards. No one in Godorno is safe these days.\n\nYou double back to your lair on Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 299; }
};

class Story240 : public Story::Base
{
public:
    Story240()
    {
        ID = 240;

        Text = "You grab Ruth and shove her roughly out into the street. The guards laugh as they take her. \"Tryin' to make a run for it, were you, darlin'?\" sneers one as he manhandles her.\n\nShe screams out that she is pregnant, but they only sneer, \"Two for the price of one.\" They drag her away and her distraught screaming is a torment you will never forget. It will trouble your conscience and wake you from your dreams till the day you die.\n\nYou return to your cellar hideout.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::SATORI);
        }
    }

    int Continue(Character::Base &player) { return 414; }
};

class Story241 : public Story::Base
{
public:
    Story241()
    {
        ID = 241;

        Text = "Returning to the cellar, you tell your cronies what you've learned while gathering rumours: \"The talk is of a certain jeweller on Mire Street. Recently he took delivery of a large DIAMOND, which the Overlord himself is paying to have worked into a sceptre. The DIAMOND in question was seized from a Judain shopkeeper when he was hauled off to Grond.\"\n\nAnnas blows out his cheeks. \"Stealing the Overlord's own DIAMOND, eh? You\"ve never been one to do things by halves, I'll say that.\"\n\n\"Still,\" adds Caiaphas, rubbing the long prow of his jaw, \"I'll admit we could use the money. Much of our operations rely on bribes -- and the traders from overseas demand high prices for weapons they're selling us these days.\"\n\nYou take a casual stroll down Mire Street to inspect the premises. The jeweller's house comprises an elegant shop with oak-framed bottle glass windows, above which live the jeweller and his family. Seeing a patrol of the city militia ahead, you dodge into cover down a side alley and wait for them to pass. You will return here tonight.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::ROGUERY, Skill::Type::CHARMS, Skill::Type::CUNNING}))
        {
            Choices.push_back(Choice::Base("Use [ROGUERY]", 306, Skill::Type::ROGUERY));
            Choices.push_back(Choice::Base("Use [CHARMS]", 327, Skill::Type::CHARMS));
            Choices.push_back(Choice::Base("Resort to [CHARMS]", 327, Skill::Type::CUNNING));
        }
        else
        {
            Choices.push_back(Choice::Base("Proceed with the attempt", 386));
            Choices.push_back(Choice::Base("Give up", 190));
        }
    }
};

class Story242 : public Story::Base
{
public:
    Story242()
    {
        ID = 242;

        Text = "It takes too long for you to concentrate your mind on the Rulership spell. You need to marshal every atom of your strength of will for this spell and your preparations are rudely and painfully interrupted by Skakshi's second stiletto dagger which buries its tip in your heart. You fall dead and there is no one left to save the wretched Judain from being wiped out for ever.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story243 : public Story::Base
{
public:
    Story243()
    {
        ID = 243;

        Text = "You seek out a foreign trader named Sardis, finally tracking him down in a tavern off Tartars' Quay. He always has a few odd trinkets to sell, brought from distant lands. When you explain your requirements, he gives a wink and pulls something from his pocket. It is an AMULET on a silver chain. You recognize the aura at once, and reach to inspect it.\n\nSardis closes his fingers around it and smiles. \"First, let us discuss the price,\" he says. \"I have braved many dangers to traverse the seas with my wares. First there were the pirates of Far Cathay, then the sirens in the Straits of Nullity. I hardly care even to remember the frightening mist phantoms that beset the ship as we lay becalmed off Hengist Head...\"\n\nYou sigh. \"Enough, Sardis. Spare me this tiresome routine. For once, will you break with the habit of a lifetime and just state the price!\"\n\n\"For this AMULET? A mere nine gleenars! And see, here I also have a fine SWORD of best Moorish steel, for which I ask only six gleenars.\"";

        Choices.clear();

        Controls = Story::Controls::SHOP;
    }

    void Event(Character::Base &player)
    {
        Shop = {{Item::MAGIC_AMULET, 9}, {Item::SWORD, 6}};
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story244 : public Story::Base
{
public:
    Story244()
    {
        ID = 244;

        Text = "This time you pick the charm oflnfernal Apparition, which causes you to resemble a nighted fiend from the pits ofhell. You walk stiff-legged down the street towards them, screaming in the tongue of the fierce cannibals of the Isles of the Gaels. The troops pass you in two streams on either side of the cobbled street, making the sign of protection of the one god tolerated in Godorno, though you notice one or two fingering charms sacred to their old gods, behind their backs. It is tempting to cause trouble by denouncing them as heretics but you haven't the energy. The guards walk slowly past and out of sight.\n\nSummoning all your strength you skulk through the shadows to the lighthouse garret, where Mameluke is warming some broth.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 316; }
};

class Story245 : public Story::Base
{
public:
    Story245()
    {
        ID = 245;

        Text = "To your relief the pool is only three feet deep and you step out wet but unharmed on the far side. The moaning of the gargoyles dies away and it is only now it has ceased you realize how oppressive the doleful sound was.";

        Choices.clear();
        Choices.push_back(Choice::Base("Explore the sides of this odd-shaped room, around the edges of the pool", 203));
        Choices.push_back(Choice::Base("Waste no time and open the door ahead of you", 162));

        Controls = Story::Controls::STANDARD;
    }
};

class Story246 : public Story::Base
{
public:
    Story246()
    {
        ID = 246;

        Text = "\"It's the old beast from the catacombs. The ancient wicked heart of the city, claiming the people for its own.\" He hands you the pot of ale, which smells strongly of malt, barley and honey.\n\n\"What is the old beast?\"\n\n\"Some say it is the spirit of the Harakadnezzar, the Great Tyrant. It is said that when robbers desecrated his tombs he became absorbed into the bones of the world, gaining strength in the dark places far from the light. Now he has come forth to avenge himself. Others say it is the many-limbed beast, Hate. It attacks the wicked and decadent, carrying people off who have hate in their hearts. One thing I do know, it isn't good for trade.\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::FOLKLORE, Skill::Type::CHARMS}) && !Character::VERIFY_ITEMS(player, {Item::Type::BOOK_OF_MYTHS_AND_LEGENDS}))
        {
            Choices.push_back(Choice::Base("Quaff the ale he has given you", 267));
            Choices.push_back(Choice::Base("Leave it untouched", 276));
        }
    }

    int Continue(Character::Base &player)
    {
        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE) && !Character::VERIFY_ITEMS(player, {Item::Type::BOOK_OF_MYTHS_AND_LEGENDS}))
        {
            return 287;
        }
        else
        {
            return 256;
        }
    }
};

class Story247 : public Story::Base
{
public:
    Story247()
    {
        ID = 247;

        Text = "You are still miies from Bagoe and your spirits are lifting as you find the farmers much more friendly than the cityfolk, though you dare not stop to chat. The workers in the fields wave solemn greetings as you pass. You wave back to one and notice he is looking from you back down the road. Turning back you see a cloud of dust or smoke. Perhaps one of the farmers is burning off some old tomato plants.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            return 37;
        }
        else
        {
            return 55;
        }
    }
};

class Story248 : public Story::Base
{
public:
    Story248()
    {
        ID = 248;

        Text = "Where will you enter the catacombs? There is a new fissure opened up in the sea wall at the old dock. There is also a way into the catacombs beneath the Overlord's stables.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go to the sea wall", 352));
        Choices.push_back(Choice::Base("Go to the Overlord's stables", 262));

        Controls = Story::Controls::STANDARD;
    }
};

class Story249 : public Story::Base
{
public:
    Story249()
    {
        ID = 249;

        Text = "How will you try to free the guards?";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to torch the purple flesh of Hate", 228));
        Choices.push_back(Choice::Base("Ask some of the trapped guards what to do", 215));
        Choices.push_back(Choice::Base("[SPELLS] Magic might do the trick: attack Hate using Miasma", 173, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Thunderflash", 165, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Bafflement", 154, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Rulership", 122, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Use a SWORD", 192, {Item::SWORD}));

        Controls = Story::Controls::STANDARD;
    }
};

class Story250 : public Story::Base
{
public:
    Story250()
    {
        ID = 250;

        Text = "The guards here on the city gate look bored. You find a piece of straw in the road and walk up chewing this like a milch cow. In your best country yokel accent you ask them if you can try your hand at their job to see if you would like to join the city guard. They are taken in by your country bumpkin act and one of them is only too glad to give up his place on the gate to you so that he can begin the evening's drinking early.\n\nYou stay with the guards at the gate and learn much of what has passed since you fled the city. The Judain are hanging dead in iron cages by the hundred. A few managed to flee the city but most have gone to ground in what the guards call 'their lairs and slum pits'. Things have been very bad for your people. The Overlord is trying to wipe you Judain from the face of the earth -- with a large measure of success, by the sound of it. After three hours on the gate you manage to slink unseen into the city while the others are in the gatehouse, brewing a pot of tea.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 300; }
};

class Story251 : public Story::Base
{
public:
    Story251()
    {
        ID = 251;

        Text = "You keep poling steadily along. The cresting wave smashes against the gondola and you are bumped by a large sea cow. It veers off and you pick yourself up from where you had fallen among the cushions and poll the boat further out. You call aloud but Hate has no ears wi.t h which to hear the pleas of the lost souls. Swanning around in a gondola is all very well but you haven't attracted the attentions of Hate. You pole back to the bank and return to your lair on Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 20; }
};

class Story252 : public Story::Base
{
public:
    Story252()
    {
        ID = 252;

        Text = "Two of the stanchions holding up the mound of rubble are cracked and buckling. It would be suicide to venture down there. If Lucie is buried down that hole she must be long since dead. There is nothing you can do to help her, only hope she spent the night in the arms of a lover and not in her own miserable little hovel. You return to your people to prepare them to face Hate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 195; }
};

class Story253 : public Story::Base
{
public:
    Story253()
    {
        ID = 253;

        Image = "images/filler2.png";

        Text = "Your fears were well founded. Put slightly off-balance because of the burden of the chest, you tread too heavily on a loose floorboard. There is an ominous creak. For a single ghastly moment your over-florid imagination likens it to the groan of scaffold timbers when a man is hanged. But the rope is not around your neck just yet -- even though the guards are already whirling, pulling the swords from their scabbards.\n\n\"A thief!\" they cry. \"Right under our very noses! Stop there, thief!\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY) && Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
        {
            Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 406, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            Choices.push_back(Choice::Base("Otherwise", 283));
        }
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 406;
        }
        else
        {
            return 283;
        }
    }
};

class Story254 : public Story::Base
{
public:
    Story254()
    {
        ID = 254;

        Image = "images/town-crier.png";

        Text = "\"Now hear the will of the Overlord. The salt tax will be doubled forthwith.\" The crier's voice rings out confidently but there are growls of discontent all around.\n\nA man turns to you and says, \"Doubled! Do they intend to squeeze us till we are nought but dried husks lying in the dust?\"\n\n\"Ssh,\" you say, wanting to hear what else the town crier is saying.\n\n\"The amnesty for those who worship false gods is at an end,\" he declaims to the crowd. \"The punishment for heresy is death\"\n\nThere is a wail from somewhere in the crowd and two of the soldiers barge their way towards the poor unfortunate. Townsfolk are knocked to the ground but no one lays hand on the soldieres. A woman dressed in a blue robe runs away up the street with the soldiers in hot pursuit.\n\nThe crier affects not to have noticed the disturbance. \"Now hear this. The Overlord decrees the Judain outcast. The life of a Judain is of no worth. The keeping of Judain as slaves within the precincts of the city may continue. It is the wish of the Overlord that all good citizens of Godorno shall not rest until the Judain have been driven out or enslaved.\"\n\nYou listen in horror. This means that none of your people is safe within the city. The crowds start to chant: \"Kill the Judain, kill the Judain.\" The man who spoke out with such indignation about the salt tax now looks at you and then points, shouting \"Judain!\" The mob will soon be baying for blood.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [CUNNING]", 301, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("[SPELLS] Cast a spell of disguise", 88, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Disappear in a puff of smoke", 104, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Use [STREETWISE]", 333, Skill::Type::STREETWISE));
        Choices.push_back(Choice::Base("[SWORDPLAY] Fight with a SWORD", 270, Skill::Type::SWORDPLAY));
        Choices.push_back(Choice::Base("Fight with [UNARMED COMBAT] ", 284, Skill::Type::UNARMED_COMBAT));
        Choices.push_back(Choice::Base("You have none of these skills, or think that using them now would only get you killed: you are pelted with loose cobblestones as you run off (LOSE 4 Life Points)", 70, Choice::Type::LIFE, -4));

        Controls = Story::Controls::STANDARD;
    }
};

class Story255 : public Story::Base
{
public:
    Story255()
    {
        ID = 255;

        Text = "You duck down the steps into the drinking house and find to your horror that it is a haunt of off-duty gate guards and the Overlord's mercenaries. They sit around tables, drinking. Many still wear the purple and black livery of the Overlord. You walk quickly across the room looking for a second way out but there is none. You hear your pursuers rein in outside. There are too many enemies to fight.";

        Choices.clear();
        Choices.push_back(Choice::Base("Hide in the privy", 329));
        Choices.push_back(Choice::Base("Surrender", 342));

        Controls = Story::Controls::STANDARD;
    }
};

class Story256 : public Story::Base
{
public:
    Story256()
    {
        ID = 256;

        Text = "Your own opinion is that the myth of the return of Harakadnezzar is only a story invented to deter would-be grave-robbers from rifling the more recently consecrated tombs. The story of Hate, however, is well known to all folklorists. Hate rises up in the foundations of ancient decadent cities, swallowing the proud, wicked and greedy into its ravening maw. This manifestation of the force of Hate was last heard of in the Old Empire city of Kush, a thousand years ago. There is nothing left of Kush now. The greatest and most powerful city the world has ever seen has become a giant dustbowl in the grasslands.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            Choices.push_back(Choice::Base("You are enjoying your ale", 267));
            Choices.push_back(Choice::Base("Spurn it", 276));
        }
    }

    int Continue(Character::Base &player) { return 287; }
};

class Story257 : public Story::Base
{
public:
    Story257()
    {
        ID = 257;

        Text = "You soon find Lucie, who is sprawled flat on her back in the road. She looks at you as though you have betrayed her and to your dismay you see she is going to cry. \"I only wanted to touch it, just for a moment,\" she cries, already in floods of tears.\n\n\"It is magically attuned to me. Only I can use it,\" you say hurriedly. You retrieve your amulet from the dust, but as you reach out to help Lucie up she shrugs you away, evading your grasp.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 261; }
};

class Story258 : public Story::Base
{
public:
    Story258()
    {
        ID = 258;

        Text = "Starting up suddenly from your chair you attempt to kill the Guildmaster of Thieves, but Melmelo is not one to be caught at a disadvantage. You encounter an invisible wall that stops you dead. It is coated in a transparent sticky slime and you are held fast. Defenceless, there is nothing you can do as Melmelo goes to work with his favourite knife. He takes no pleasure in killing you, he merely has the satisfaction that a dangerous enemy has been eliminated. There is no one left to save the Judain now. Hate will destroy everything.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story259 : public Story::Base
{
public:
    Story259()
    {
        ID = 259;

        Text = "They have only one reply to such a hideous threat. Even as you are calling the lepers forward, the guards shoot you with their crossbows from the arrow slits on either side and above the gates. You are peppered like a pincushion. As you die there is a low heartless cheer when the guards realize they have slaughtered yet another Judain. There is no one left now to save the Judain. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story260 : public Story::Base
{
public:
    std::string PreText = "";

    Story260()
    {
        ID = 260;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        Choices.clear();

        if (player.Money > 9)
        {
            PreText = "You have enough money in your purse to bribe the guards so you can enter the city.";

            Choices.push_back(Choice::Base("Hand over 10 gleenars", 300, Choice::Type::LOSE_MONEY, 10));
        }
        else
        {
            Type = Story::Type::DOOM;

            PreText = "You do have not enough to bribe the guards so they decide that the price the Overlord has put on every Judain's head makes it worth their while to kill you, steal your money, and claim the reward. Perhaps another hero will arise to save your people, but you cannot even save yourself.";
        }

        Text = PreText.c_str();
    }
};

class Story261 : public Story::Base
{
public:
    Story261()
    {
        ID = 261;

        Image = "images/filler1.png";

        Text = "Lucie's light little feet carry her to the door of the notorious Silver Eel tavern. A long, low, dark grey building without a single window facing out onto the street, it is a notorious haunt of thieves and cutthroats. On the steps Lucie is greeted by a huge man dressed in black quilted leather armour, who has a bush of corn yellow hair in corkscrew spirals.";

        Choices.clear();
        Choices.push_back(Choice::Base("Follow onto her turf, inside the Silver Eel", 86));
        Choices.push_back(Choice::Base("Slink back to your hidey-hole on Bumble Row", 199));

        Controls = Story::Controls::STANDARD;
    }
};

class Story262 : public Story::Base
{
public:
    Story262()
    {
        ID = 262;

        Text = "Your times spent skulking unseen while casing the houses of the well-to-do will stand you in good stead now. One of the things you have learned is to make sure you always know of two possible escape routes. One is the storm drain that feeds into the Imperial Basin, where the Crescent Canal and Grand Canal meet. The other is the secret tunnel that leads underground to the burial crypts of the Megiddo dynasty, a family of kings who made great conquests in Godorno's golden age and brought prosperity to the city they ruled.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE) && !Character::VERIFY_ITEMS(player, {Item::Type::BOOK_OF_MYTHS_AND_LEGENDS}))
        {
            return 339;
        }
        else
        {
            return 294;
        }
    }
};

class Story263 : public Story::Base
{
public:
    Story263()
    {
        ID = 263;

        Text = "You speak the word of power and disappear. But Skakshi is not dismayed. He reaches for a pouch at his belt and flings a sparkling dust from it into the air in your general direction. The dust clings to you and sparkles in the ruddy light, limning your outline brightly for all to see, Skakshi sends the knife hurtling across the room at your breast, which it grazes. He reaches for another stiletto immediately.\n\nYou LOSE 1 Life Point.";

        Choices.clear();
        Choices.push_back(Choice::Base("Flee from the inn and bolt for home", 200));
        Choices.push_back(Choice::Base("[SPELLS] Cast the potent spell of the Visceral Pang", 312, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast the puissant spell known as Miasma", 390, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] You wish to humiliate him by seizing his mind using Rulership", 242, Skill::Type::SPELLS));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }
};

class Story264 : public Story::Base
{
public:
    Story264()
    {
        ID = 264;

        Text = "You skulk in the shadows, then roll into the gutter where you play dead. This is an old thief's trick to avoid a hue and cry. The watchguards walk slowly past not giving yet another corpse in the plague-ridden city another glance and soon pass out of sight. Summoning all your strength you skulk through the shadows to the lighthouse-like garret, where Mameluke is warming some broth.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 316; }
};

class Story265 : public Story::Base
{
public:
    Story265()
    {
        ID = 265;

        Text = "How will you try to save him? You shout a warning but he is heedless of the danger, desperate to save his daughter who is already beyond salvation.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Magic has a chance of saving him", 97, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Grab one of the fishermen's ropes coiled nearby and lasso Tormil with it", 21));

        Controls = Story::Controls::STANDARD;
    }
};

class Story266 : public Story::Base
{
public:
    Story266()
    {
        ID = 266;

        Text = "You drop the concubine and the black cape-like monster wraps itself around her like the coils of a serpent. Her body twitches spasmodically as you leap from the bed, just clearing the edge of the carpet in safety.\n\nThe Overlord grunts and turns over; his fat form wobbles loosely as he stirs. He is waking up. You must make a run for it before he summons his bodyguards.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::SATORI);
        }
    }

    int Continue(Character::Base &player) { return 161; }
};

class Story267 : public Story::Base
{
public:
    Story267()
    {
        ID = 267;

        Text = "The honeyed ale slips down your gullet, filling your stomach with a heavy warm glow. The amber nectar is thick and almost sticky, yet strangely moreish. You finish the pot with relish, wipe your mouth backhanded and fall suddenly to the floor. The landlord has poisoned you in revenge for the pain you caused with your spell. You will not live to see this day out and there is no one who can save your people from extinction.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story268 : public Story::Base
{
public:
    Story268()
    {
        ID = 268;

        Text = "Which enchantment will you use on the heartless prison guards and torturers of Grond?";

        Choices.clear();
        Choices.push_back(Choice::Base("Cast a spell to make them feel uninterested in worldly affairs", 378));
        Choices.push_back(Choice::Base("Cast a spell to make them your friends", 361));
        Choices.push_back(Choice::Base("Cast a spell to terrify them", 341));

        Controls = Story::Controls::STANDARD;
    }
};

class Story269 : public Story::Base
{
public:
    Story269()
    {
        ID = 269;

        Text = "Luckily it is enough that the Judain can see by the look in your eyes you would kill them to protect the wretched guards. They fall back.\n\n\"Have mercy on these poor dogs,\" you say. \"Do not fall to the depths of their depravity. Is this not the fate they have reserved for you? Are we not more noble than they? Let us show them our superiority by sparing them, that their very existence may be a testament to our nobility.\"\n\nYour exhortations have appealed to their sense of vanity. They will spare the guards. You wander through the dark bones of the castle foundations, freeing those who are still alive, before returning to your hideout.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 159; }
};

class Story270 : public Story::Base
{
public:
    Story270()
    {
        ID = 270;

        Text = "The Overlord's soldiers close on you with drawn swords. You fight for your life valiantly, your blade thrumming through the air, but you can't keep them off for ever. There are too many foes and they cut you down, while the townsfolk howl with glee. Your dying thought is, \"How could I have been so foolish to think I could fight my way out of this?\"";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story271 : public Story::Base
{
public:
    Story271()
    {
        ID = 271;

        Text = "You seize the bridle and leap into the saddle. The chestnut horse bucks and then arches its back and makes a series of straight-legged jumps to shake you from the saddle. You decide to give it free rein as you feel the horse's fear, hoping this will stop it bucking. It surges into a gallop and you hang on grimly. Luckily for you the road to the main gate is straight. Within a few minutes you can see the wooden arches of the double gate ahead. People jump aside at the last moment from the path of your frothing mount.\n\nThe horse is still galloping wildly as you approach the gate and the gate guards tumble out of their guardhouse to stop you. One tries to grab the bridle but misses and falls over. Another is winding his crossbow. As you gallop past he lets fly and the bolt catches you in the side.\n\nYou LOSE 3 Life Points.";

        Bye = "You hang on grimly. The twangs of crossbow strings ring out behind you. Deadly quarrels go shooting past your ears. The horse gallops on, leaving pursuit behind. The towers and minarets of Godorno are lost to view by the time the horse runs itself out. It is lame. You dismount and carry on up the trade road on foot.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -3);
    }

    int Continue(Character::Base &player) { return 302; }
};

class Story272 : public Story::Base
{
public:
    Story272()
    {
        ID = 272;

        Image = "images/filler1.png";

        Text = "As head of the Judain resistance movement in Godorno you are now one of the most powerful people in the city. With power comes responsibility but you comfort yourself that you are doing your best. You wonder how many more Judain will die carrying out your orders. How many innocent people will suffer. Will the Overlord give in to your demands? Or will you all be taken to the prison fortress of Grond and tortured?\n\nThe Overlord is no longer the great enemy. It is Hate you must outwit. In order to do so you must know something about its movements. Where does it sleep? Can it be harmed? How long does it take to ingest lost souls? You need the answers to these questions but where will you seek them?";

        Choices.clear();
        Choices.push_back(Choice::Base("Take a gondola down Grand Canal and hope Hate comes to you", 292));
        Choices.push_back(Choice::Base("Explore the catacombs", 248));

        Controls = Story::Controls::STANDARD;
    }
};

class Story273 : public Story::Base
{
public:
    Story273()
    {
        ID = 273;

        Text = "You kneel beside her though her eyes implore you not to. She raises her arm to put it round you, then looks at the other. To your horror you see that a patch of wall has broken away to reveal something purple beneath. Lucie's arm has been drawn inside it. You are about to spring back when two tentacles whip out of the purple mass, twining round your windpipe and one wrist. Lucie is indeed a little lost soul, already being absorbed into the body of Hate. There is no escape for her -- and maybe no escape for you, either.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            return 343;
        }
        else
        {
            return 335;
        }
    }
};

class Story274 : public Story::Base
{
public:
    Story274()
    {
        ID = 274;

        Image = "images/filler3.png";

        Text = "Somehow, from the midst of chaos and despair, you must fashion a way that will deliver your people and save the city. But one wrong move will end in disaster.\n\nThere are three things you might use against the monster.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use the JADE WARRIOR's SWORD", 230, {Item::JADE_WARRIORS_SWORD}));
        Choices.push_back(Choice::Base("Use the JEWEL OF SUNSET FIRE", 349, {Item::JEWEL_OF_SUNSET_FIRE}));
        Choices.push_back(Choice::Base("Use the CHAINS from the prison gates of Grond to shackle Hate", 392, {Item::CHAINS}));
        Choices.push_back(Choice::Base("You have none of those items", 187));

        Controls = Story::Controls::STANDARD;
    }
};

class Story275 : public Story::Base
{
public:
    Story275()
    {
        ID = 275;

        Text = "The old woman doesn't betray the least surprise at your revelation. \"Best lie low, these are bad times for Judain and no mistake. Good luck.\"\n\nAnd with that she is off to find a place on the street to sell her meagre clutch of eggs. You walk on into the once bustling city.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 300; }
};

class Story276 : public Story::Base
{
public:
    Story276()
    {
        ID = 276;

        Text = "You pick up your alepot, then set it down on the bar again without drinking from it. It would not do to be poisoned when there are so many depending on you for leadership. The landlord's eyes flit from yours to the alepot and back again. It seems you have guessed aright: the landlord meant to avenge himself by poisoning you.\n\nThere is no sense in looking for more trouble here. You give the surly landlord a knowing look and prepare to quit the bar, determined never to darken its doors again.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave the Silver Eel", 199));
        Choices.push_back(Choice::Base("Ask about Lucie and the tall stranger before you go", 236));
        Choices.push_back(Choice::Base("Talk to her and her strange acquaintance", 227));

        Controls = Story::Controls::STANDARD;
    }
};

class Story277 : public Story::Base
{
public:
    Story277()
    {
        ID = 277;

        Text = "The JADE WARRIORS' SWORDs are the finest you have ever seen. One in particular seems almost to pulse with energy, catching light like droplets of honey along its sharp edge.\n\nWith such a SWORD you might conquer a kingdom. The lure of avarice is too great. Diving forward, you duck under the swipe of the nearest Jade Warrior and leap nimbly over the attack of the second. Jumping behind the Jade Warrior with the finest blade, you throw yourself against its sword arm, wrenching the blade from its strong grasp.\n\nThe others close in, and too late you realize your escape route is cut off. By reflex you raise the SWORD. \"Get away from me!\" you cry as menacingly as you can as they loom over you to slice your vitals.\n\nTo your relief and amazement they obey your command, lining up before you to stand at attention. They whirr and click as they follow you dutifully to the edge of the precincts of the burial chambers, and there they grind to a halt. There is nothing you can do to move them further. Although you cannot command the Jade Warriors to go forth and attack Hate, you tell them that they must attack Hate if it should loop its coils into the burial chambers of the Megiddo dynasty. You leave all doors and traps wide open in the hope that Hate will blunder in and get carved up.\n\nSure enough, when you return the next day the place shows the signs of an epic battle. Great gouts of translucent flesh hang from lintel and corners. There is a fine green powder in the air, like pulverized glass. The Jade Warriors have been ground to dust by Hate but, judging by the quantity of purple ichor smeared over the walls, they must have given the monster acute indigestion.\n\nYou OBTAINED a JADE WARRIOR's SWORD. You gained the codeword HECATOMB.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::JADE_WARRIORS_SWORD});

        Character::GET_CODEWORDS(player, {Codeword::Type::HECATOMB});

        Take = {Item::PLUMED_HELMET};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 174; }
};

class Story278 : public Story::Base
{
public:
    Story278()
    {
        ID = 278;

        Text = "You sit, exhausted, against a ramshackle wall and the city guards rein their horses in around you. You pass out with the sickness, only to come to a moment later as you are roughly hauled to your feet. The guards have dismounted to surround you. You are pushed around between them, then you double up as a knee is driven hard into your solar plexus.\n\nThey beat you badly and leave you for dead.\n\nYou LOSE 5 Life Points.";

        Bye = "You drag yourself out of the gutter and manage to stagger to Mameluke's garrett.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -5);
    }

    int Continue(Character::Base &player) { return 316; }
};

class Story279 : public Story::Base
{
public:
    Story279()
    {
        ID = 279;

        Text = "You are taking a terrible risk, stealing into the Overlord's palace. It is a dark night and you fight to control a blackness of heart which impels you to take revenge on the cruel tyrannical Overlord.\n\nEmerging out of the catacombs beneath the palace stables you make your way in by the postern gate and steal along strangely deserted corridors towards where you guess the Overlord's suite must be.\n\nThere are few guards here, though you can hear the sounds of a drunken brawl in the guardhouse itself. How can the Overlord's security be so lax? Is he losing his grip?\n\nAfter only five minutes inside the palace you are outside the Overlord's bedchamber. Holding your breath you push open the door and step through.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 30; }
};

class Story280 : public Story::Base
{
public:
    Story280()
    {
        ID = 280;

        Image = "images/filler1.png";

        Text = "The walls of the prison are purple, pulsating slowly. They are lined with guards, sucked into the tentacles of Hate which have infested the prison. A score of despairing, pleading looks are turned on you, followed by a chorus of low moans. This has been the work of but a single night for all-devouring Hate. Most of the men have been sucked in only as far as both elbows, or knees, but they are all exhausted by their fruitless struggles to break free. When they get tired and lose concentration they have all touched Hate with their other hand or foot and so become deeper enmeshed. Unable any longer to resist the pull of Hate they are being submerged in the purple morass inch by inch; every time Hate takes a breath its flesh advances over them imperceptibly.\n\nMost of the men are wailing out repentance for the atrocities they have committed on the poor prisoners of Grond.";

        Choices.clear();
        Choices.push_back(Choice::Base("Set them free", 249));
        Choices.push_back(Choice::Base("Leave them to their harsh but deserved fate and go on to free the Judain", 332));

        Controls = Story::Controls::STANDARD;
    }
};

class Story281 : public Story::Base
{
public:
    std::string PreText = "";

    Story281()
    {
        ID = 281;

        Image = "images/skakshi.png";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Try for a quick casting of Visceral Pang", 313, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Miasma", 390, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Vanish", 263, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Cast Rulership", 242, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SWORDPLAY] Fight", 223, Skill::Type::SWORDPLAY));
        Choices.push_back(Choice::Base("[CUNNING] Rely on your wits", 67, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("You have none of these skills", 357));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "How will you teach proud Skakshi a lesson? The thief vaults nimbly over the table and draws a stiletto from his boot. It is a balanced knife, good for throwing. You haven't long in which to do something.";

        if (Character::HAS_SKILL(player, Skill::Type::SPELLS))
        {
            PreText += "\n\nYou can use magic but be warned that it is difficult to work a spell in such a short time, however.";
        }

        Text = PreText.c_str();
    }
};

class Story282 : public Story::Base
{
public:
    std::string PreText = "";

    Story282()
    {
        ID = 282;

        Choices.clear();
        Choices.push_back(Choice::Base("Bandage yourself up before making your escape", 383));
        Choices.push_back(Choice::Base("Run for it straight away", 393));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The word of power you speak does its work and you disappear from view. One of the guards has the sense to let his crossbow off and the quarrel buries itself joltingly in your chest. You bite your lip to stop yourself moaning in agony.\n\nYou LOSE 6 Life Points.";

        Character::GAIN_LIFE(player, -6);

        if (player.Life > 0)
        {
            PreText += "\n\nYou hide in a doorway, satisfied that the guards can't see you yet.";
        }

        Text = PreText.c_str();
    }
};

class Story283 : public Story::Base
{
public:
    std::string PreText = "";

    Story283()
    {
        ID = 283;

        Image = "images/diamond.png";

        Bye = "You survive to gain victory. You step over the soldiers' bodies and snatch up the treasure chest, then hurry off into the night.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The penalty for fighting with the Overlord's guards is to be hung in chains until the wind dries you out like a raisin. That's if you get caught, of course. But either way -- whether you are killed in this struggle, or arrested and taken to Grond -- it means you are now in a fight to the death.\n\nIt is a grim battle, fought almost in silence. The only sounds are frantic pants of breath and the scuff of quick footfalls as you manoeuvre back and forth across the room. At least you have one thing in your favour: although outnumbered, you are able to get your back to a corner, making it difficult for the soldiers to press their advantage.\n\n";

        auto DAMAGE = -5;
        auto USE_SHIELD = false;

        if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
        {
            DAMAGE = -1;

            PreText += "[SWORDPLAY] ";

            USE_SHIELD = true;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::UNARMED_COMBAT))
        {
            DAMAGE = -3;

            PreText += "[UNARMED COMBAT] ";

            USE_SHIELD = false;
        }

        if (USE_SHIELD && Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY) && Character::VERIFY_ITEMS(player, {Item::Type::SHIELD}))
        {
            Character::DAMAGE(player, Skill::Type::SWORDPLAY, Item::Type::SHIELD, DAMAGE);

            PreText += "Your SHIELD absorbs " + std::to_string(-DAMAGE) + " Damage.";
        }
        else
        {
            Character::GAIN_LIFE(player, DAMAGE);

            PreText += "You LOST " + std::to_string(-DAMAGE) + " Life Point(s).";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 358; }
};

class Story284 : public Story::Base
{
public:
    Story284()
    {
        ID = 284;

        Text = "The Overlord's soldiers close in on you with drawn swords. You fight for your life valiantly. Your fists and feet are a blur, but you can't keep them off forever. There are too many foes and they cut you down while the townsfolk howl with glee. Your dying thought is: \"How could I have been so foolish to think I could fight my way out ot this?\"";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story285 : public Story::Base
{
public:
    Story285()
    {
        ID = 285;

        Text = "As you prepare to step off the bed, a black monstrous being emerges noiselessly from the canopy of the Overlord's bed and glides down to settle over the girl. It looks like a manta ray or a vampire's cape. You see that the underside of the creature is covered with barbed spines which ooze a yellow venom.";

        Choices.clear();
        Choices.push_back(Choice::Base("Drop the girl, who is still limp in your arms, and jump from the bed", 266));
        Choices.push_back(Choice::Base("Carry her quickly over the carpet before prising the thing off her", 322));

        Controls = Story::Controls::STANDARD;
    }
};

class Story286 : public Story::Base
{
public:
    Story286()
    {
        ID = 286;

        Text = "She is surprisingly sprightly for an aged crone. She scuttles along after you cackling to herself in a witch-like way. You turn towards Green bark Plaza when two lines of guards block the road at either end of the narrow short street you are in. They are armed with crossbows which they are pointing at your chest.\n\n\"We're taking you to Grond, Judain. The Overlord's torturers can amuse themselves with you.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Surrender to them and be tortured", 238));
        Choices.push_back(Choice::Base("[SPELLS] Turn invisible", 282, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Fight your way out", 405));

        Controls = Story::Controls::STANDARD;
    }
};

class Story287 : public Story::Base
{
public:
    Story287()
    {
        ID = 287;

        Text = "The AMULET gives a flare of violet light in the flickering lamplight of the inn. You know that signal well. It is a warning of poison and deceit, visible only to your own eyes. You look with narrowed eyes at the landlord, then at the alepot on the bar.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 276; }
};

class Story288 : public Story::Base
{
public:
    Story288()
    {
        ID = 288;

        Text = "It is hardly an act of trust to use magic against your own allies, even if the cause is a good one.\n\nCaiaphas pulls a long face at being asked to give up such a large part of the Judain hoard and asks in his rumbling basso voice, \"How many of our fellow Judain remain alive in Grond?\"\n\n\"If there is but one of our kind remaining alive it is worth it,\" you reply glibly.\n\nCaiaphas doesn't look as if he agrees. He turns to little high-voiced Annas, who asks, \"How can we be sure the guard will hand over the keys?\"\n\n\"No keys, no money,\" you say.\n\n\"He might just hand over a set of keys to the Overlord's kitchens!\"\n\n\"There would be no profit in it for him.\"\n\nAnnas peers at you, not sure if you understood his objection. \"And why do you suddenly wish to help the prison guards?\" he asks. \"Every day you give us orders to kill the Overlord's men and we obey. Have you lost your mind?\"\n\n\"It is the only course. We must show compassion if we are to avoid being consumed by Hate.\"\n\nAmazingly, Annas looks convinced, but Caiaphas asks, \"What of the murderers, the lunatics, and thieves who will also. be set free?\"\n\nYou give a curt wave of your hand. \"What of them? The city cannot fall into any worse state.\"\n\nCaiaphas shrugs. You have your gold.\n\nYou RECEIVED 500 gleenars.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::SATORI);
        }

        Character::GAIN_MONEY(player, 500);
    }

    int Continue(Character::Base &player) { return 415; }
};

class Story289 : public Story::Base
{
public:
    Story289()
    {
        ID = 289;

        Text = "Seizing the bridle you vault into the saddle. The chestnut horse bucks and then, arching its back, makes a series of straight-legged jumps that shake you from the saddle before you can settle. You fall to the cobbles, stunned, listening in a detached way as the hoofbeats of your pursuers come closer and stop. Your head is swimming as the soldiers dismount.\n\n\"Judain scum,\" says one of them, plunging a sword in your back, killing you as if you were no more than a dog. \"That's one less to worry about,\" he says.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story290 : public Story::Base
{
public:
    Story290()
    {
        ID = 290;

        Text = "A great crash echoes round the room and seems to shake the whole tower. It is followed by an explosion of spurting red flame which bathes the black spider in its punishing light. You feel giddy as the tower rocks. The spider recoils, its legs buckle under it and it struggles in vain to get up. The JEWEL OF SUNSET FIRE is yours for the taking. You make a dash for it before the gigantic spider, which is giving out a high keening hiss, can recover.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 308; }
};

class Story291 : public Story::Base
{
public:
    Story291()
    {
        ID = 291;

        Text = "Skakshi takes you by a devious route, perhaps hoping you will get lost in the foreigners' quarter, which you have been travelling through now for ten minutes.\n\n\"What do you have in mind for Melmelo?\" Skakshi is anxious to know whether you intend the Guildmaster of Thieves any harm. There is naked ambition gleaming in his eyes; he is a truly nasty piece of work.\n\n\"Wait and see,\" you tell him.\n\nAt last you stand before a white stuccoed villa with an ornamental steam bath bubbling in the garden.\n\n\"This is Melmelo's place. The soft living here has made him unfit to lead our guild. There are many who are just waiting for something to happen.\"\n\n\"Thank you, Skakshi, for guiding me here. What is the password? I don't want to be killed for calling without an invitation.\"\n\n\"Just shout, 'enchantress' and they will let you in. If anything happens remember it was me, honest Skakshi, who brought you here. Don't tell Melmelo though.\" With that he is gone; he blends into the shadows like a ghost.\n\nWalking up to the double doors of the villa you cry the password for all to hear.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 12; }
};

class Story292 : public Story::Base
{
public:
    Story292()
    {
        ID = 292;

        Text = "Taking the grandest gilded gondola from the tie-ups at Tartars' Quay you begin to pole effortlessly down the Grand Canal. Inside the gondola the benches are covered with black leather, neatly garnished with fine linen cloth, its edges trimmed with lace. The gilded ends of the boat are in the shape of dolphins' tails. There is no other traffic on the water and you are at leisure to notice the cracks developing in the waterfront villas as they begin to subside into the canal. Every now and then a cascade of tiles and chimney pots reminds you Godorno is sinking without trace.\n\nHow will you attract the attention of Hate as you pole down the canal?";

        Choices.clear();
        Choices.push_back(Choice::Base("Sing a song", 314));
        Choices.push_back(Choice::Base("Call aloud for Hate to come and make final reckoning with you", 323));

        Controls = Story::Controls::STANDARD;
    }
};

class Story293 : public Story::Base
{
public:
    Story293()
    {
        ID = 293;

        Image = "images/filler2.png";

        Text = "You find Lucie loitering around the moored gondolas on Circle Canal. In better days she might have had rich pickings from dipping her hand into the purses of the wealthy. In these troubled times, few people dare venture into the streets with money in their pockets.\n\nYou explain that you want to get into Grond and free the prisoners there.\n\n\"Help free those vermin?\" she says. \"Why would I want to? Many are murderers, rapists and madmen!\"\n\n\"Many are brave men whose only crime was to speak out against the Overlord. Others are even more blameless. My fellow Judain, for instance, declared criminal simply because of race and creed.\"\n\nLucie seems not even to have heard you. \"Those beasts in Grond -- they are animals! Let Hate take them!\" She looks at you as though you have lost your wits, her pretty face contorted with hatred. The glint in her eyes is frightening. She looks mad.";

        Choices.clear();
        Choices.push_back(Choice::Base("Slap her to end this hysterical outburst", 336));
        Choices.push_back(Choice::Base("Tell her to be calm", 346));

        Controls = Story::Controls::STANDARD;
    }
};

class Story294 : public Story::Base
{
public:
    Story294()
    {
        ID = 294;

        Text = "The burial crypts of the Megiddo dynasty are reputed to be guarded by the Jade Warriors, four enchanted statues of their most trusted and able bodyguards. If you are forced to flee into those crypts you risk disturbing them. It is said they have killed even the most cunning and dangerous grave robbers and defilers of tombs over the centuries.\n\nIt is also said that the Jade Warriors protect not only the ceremented mummies of the Megiddo dynasty but a vast panoply of war gear along with enough treasure to maintain a large army indefinitely. The SWORDs of the famed Megiddan Palace Guard are reputedly sharper than any ever made in the eastern world.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 409; }
};

class Story295 : public Story::Base
{
public:
    Story295()
    {
        ID = 295;

        Text = "Hate reaches for the crumbling building on either side of the street. Locking its tentacles around the famous Bridge of Sighs, it brings the whole structure crashing down on your head. You fall and are crushed under the rubble, while Hate goes lumbering past to bring about the final end of the cursed city of Godorno. You have failed.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story296 : public Story::Base
{
public:
    Story296()
    {
        ID = 296;

        Text = "You take up a martial stance before the first of the Jade Warriors, searching for a weakness to attack. Your fists and feet cannot shatter the jade, which is impervious to your blows. The BLADEs of the Jade Warriors are terribly sharp as you find to your cost when one bites into your thigh.\n\nYou LOSE 4 Life Points.";

        Bye = "You have no choice but to flee.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -4);
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story297 : public Story::Base
{
public:
    Story297()
    {
        ID = 297;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::SWORD}))
        {
            return 328;
        }
        else
        {
            return 384;
        }
    }
};

class Story298 : public Story::Base
{
public:
    Story298()
    {
        ID = 298;

        Text = "It tears you apart to leave Lucie but she is already a lost soul, lost for ever in despair. With a heavy heart you set out towards your lair on Bumble Row once more to get ready to prepare the Judain for battle.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 195; }
};

class Story299 : public Story::Base
{
public:
    Story299()
    {
        ID = 299;

        Text = "The surviving Judain of the city all look to you for leadership now. They are ashamed at not having stood up to the Overlord, but your news of his suffering has cheered them. They feel as if God has not yet forsaken them.\n\nYou circle various safe areas on your map of the city and assign a cell of five operatives to each, giving them a list of the people they are to support with their foraging. The high death rate at least means less mouths to feed.\n\nEach cell is also given a list of people to be assassinated. \"If you do your work well the Overlord will be forced to grant us pardon and we can begin life anew,\" you tell them to instil hope in their hearts. \"We will search for the Promised Land where there is only the one true God, Light of our Lives.\"\n\n\"Our miserable lives,\" grumbles one of the grandmothers.\n\n\"Enough,\" you say autocratically, beginning to revel in your leadership now, \"I want no dissent. You all know what you have to do. The heads of each resistance cell will meet at noon on the third day from now, underneath the Lord Mayor's house. I expect all of you to report success in your missions, and without loss. I'm relying on you. You know where to find me if you need me, now go, and keep your heads down.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 6; }
};

class Story300 : public Story::Base
{
public:
    Story300()
    {
        ID = 300;

        Text = "At last you face the noisome streets of the city once more. The facades of the palaces seem even more chipped and sullied than they were before you left. Several of the rows of grand villas along the river-front and up the Grand Canal seem to have subsided several feet towards the waterline. Where once the roofline was an uninterrupted plane from one end of the canal to the other, now it is a crooked saw-toothed succession of pinnacles and collapsed roofs. Something has shaken the city to its foundations while you have been away.\n\nWill you find a safe place to hide until the worst of the terror is over? Your old hovel on Copper Street is only a couple more miles' tramp from here. You decide to go back there to find old friends.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 4; }
};

class Story301 : public Story::Base
{
public:
    Story301()
    {
        ID = 301;

        Image = "images/filler3.png";

        Text = "Only a rogue like you would know how to save yourself. Slipping your dagger from your sleeve you step sideways and grab a timid-looking young woman, richly dressed, away from her aged retainer. You hold the blade to her throat. You are lucky, she is the only daughter of a nobleman and the soldiers check, fearful of her father's wrath.\n\n\"Put up your swords or the girl dies.\"\n\nThe mob falls silent and the soldiers look to the town crier who orders them to obey you.\n\nYou walk her away from the plaza, ordering everyone to stay where they are. As soon as you turn the corner you release her, shout a quick apology, and run for it.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 38; }
};

class Story302 : public Story::Base
{
public:
    Story302()
    {
        ID = 302;

        Text = "It is unusual for travellers to walk alone on the trade route. Brigands live in hill forts to the north of the road. Their crenellated keeps survey great sweeps of land from which they come down on poor travellers like wolves on the fold. They plunder the merchant caravans, doing battle with the mercenary guards. Walking alone you are not safe.\n\nThe road is already starting to climb towards the mountain passes, through meadowlands where the brigands keep herds of cattle.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go along the road", 3));
        Choices.push_back(Choice::Base("Strike off north through brigand territory towards the great forest", 14));

        Controls = Story::Controls::STANDARD;
    }
};

class Story303 : public Story::Base
{
public:
    Story303()
    {
        ID = 303;

        Image = "images/mameluke-eating.png";

        Text = "Mameluke greets you warmly. He is preparing to eat a cat which he has skinned and roasted over a slow fire; he offers to share it with you. Famished, you thank him and eat greedily while trying not to think of the rats the cat has itself dined upon in the past, in the fouled gutters of the city.\n\nMameluke insists on telling you about a mishap which befell him this morning: \"In going about three hours ago, to a rendezvous with a girl of Godorno -- unmarried and a daughter to one of the nobles -- I tumbled into the Grand Canal, my foot slipping as I got out of my gondola owing to the cursed slippery steps of the palaces here. In I flounced like a carp, and went dripping like a Triton to my Sea Nymph and had to scramble up to a grated window -- 'fenced with iron within and without, lest the lover get in or the lady get out'.\"\n\nMameluke is in a whimiscal mood. You are reminded of the man who sat around fiddling while the city burned. Nevertheless you implore him to help you for the sake of your people.\n\n\"I will help you, my friend,\" he says, \"if only to rid myself of the wailing of the prisoners, which are a constant affront to my sanity.\"\n\n\"Should I ask Lucie for help?\" you suggest. \"She might know someone in the fortress.\"\n\n\"I'll warrant she does, but I don't trust that wench. She acts so innocent yet I've never known her want for protection on the streets of Godorno, have you?\"\n\n\"Perhaps you're right, but we need a way in.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Take Mameluke to call on Lucie and ask for her help", 402));
        Choices.push_back(Choice::Base("Take him into the catacombs to look for a way into the prison fortress of Grond", 412));

        Controls = Story::Controls::STANDARD;
    }
};

class Story304 : public Story::Base
{
public:
    Story304()
    {
        ID = 304;

        Text = "You stumble through a door which opens onto a short staircase down and almost tumble into an inviting-looking blue pool. This room looks too big. It is oval and too long to fit inside the tower. Its centre is taken up with a thirty-foot wide pool surrounded with marble and majolica. A waterfall plunges into the pool from out of the wall near the ceiling. If this waterfall has fed this pool for centuries, where has the water conie from and why isn't the pool overflowing? The door that leads on upwards is on the other side of the room.";

        Choices.clear();
        Choices.push_back(Choice::Base("Walk round the pool to the door", 203));
        Choices.push_back(Choice::Base("Walk through the pool to it", 216));

        Controls = Story::Controls::STANDARD;
    }
};

class Story305 : public Story::Base
{
public:
    Story305()
    {
        ID = 305;

        Text = "There is a faint whispering sound above and the black shape settles heavily over you. Its skin sports rows of barbed spines that inject a poison into your bloodstream. Try as you might, you can't break free. The poison turns your blood to cloying syrup and your heart stops beating. You have died when revenge for the Judain was almost within your grasp. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story306 : public Story::Base
{
public:
    Story306()
    {
        ID = 306;

        Text = "Sailing amid a froth of high flitting cloud, the moon casts a thin creamy light down to the narrow streets. You slide from shadow to shadow until you reach Mire Street, where you pause in the lee of a doorway to take stock of your target. No lamp shows in the windows. On the upper storey, one of the latticed windows overlooking the street has been left ajar. According to the etiquette of your chosen profession, this is tantamount to an effusive invitation. Detaching yourself from the darkness, you make a nimble ascent of the shop front and slither in through the open window. Tiptoeing lightly over a large slumbering guard dog lying across the landing, you quickly reconnoitre the house, discovering three of the Overlord's soldiers on watch in an upstairs room. Surveying them from behind a drape, you notice a small locked treasure-chest in an alcove at the back of the room. Without a doubt that is where the diamond is kept.\n\nYou bite your lip, sizing up the situation. The three sentries are intent on a dice game, and the flickering lamplight in the room provides ample shadows for concealment, but even so the job will not be easy. With all your dexterous talents, you are not sure that even you could creep past them unnoticed and pick the lock on the chest.";

        Choices.clear();
        Choices.push_back(Choice::Base("Give it a try", 391));
        Choices.push_back(Choice::Base("Abandon the attempt and go back to where your comrades are waiting", 190));

        Controls = Story::Controls::STANDARD;
    }
};

class Story307 : public Story::Base
{
public:
    Story307()
    {
        ID = 307;

        Text = "You were bound to get taken sometime, using the streets as if they were your own before the resistance has cleared them for you. Two groups of guards have been tracking you and they ambush you in a cul-de-sac. You die in a pool of blood and there is no one left now to save the Judain. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story308 : public Story::Base
{
public:
    Story308()
    {
        ID = 308;

        Image = "images/filler2.png";

        Text = "Clutching the JEWEL OF SUNSET FIRE, you marvel at the play of coloured light in its facets.";

        Bye = "The climb back down is easier than coming up.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::JEWEL_OF_SUNSET_FIRE});

        Character::REMOVE_CODEWORD(player, Codeword::Type::SUNSET);
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story309 : public Story::Base
{
public:
    Story309()
    {
        ID = 309;

        Text = "You are looking out over the eastern courtyard where the prisoners are brought daily to exercise but there is no one in sight. The barred windows of the towers at each corner of the quadrangle are all shut. There is no sign of Captain Khmer, the commandant of the prison, or his men. You decide to go deeper into the prison and walk carefully to the opposite tower.\n\nThe door creaks open and the familiar cloying smell of Hate assails your nostrils. The silence is oppressive but you wonder why you can't hear the screams of the tormented prisoners. Screwing up your courage you walk on into the inner ring of the fortress. Piles of masonry and strange holes in the ground that lead to lightless pits among the old fortress foundations do nothing to calm your fears.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 280; }
};

class Story310 : public Story::Base
{
public:
    Story310()
    {
        ID = 310;

        Text = "You are in luck. He emerges from the palace about noon, borne in his gilded litter by eight slaves in silk tabards. The escort of heavily armed soldiers would deter any assassin. As the litter progresses slowly down the Avenue of Silent Glory towards the Greenbark Plaza, some of the soldiers hurry ahead with halberds raised, urging the onlookers to raise a feeble cheer.\n\nInside the litter, the Overlord is reclining rather more than usual. When he twitches the curtain aside to wave less fulsomely than is his wont his face has the purplish hue of a man stricken by gout and a disease of the blood. His eyes are hooded and lacklustre.\n\nYou make your way back to your hidey-hole on Bumble Row and find a messenger waiting for you there, a Judain nipper with big brown eyes. He hands you a note. It is from a girl you used to know, called Lucie. Her name means 'rays of the dawn'. She wants to meet you tomorrow morning. You tell the little messenger you will be at the appointed place at the appointed hour and he scampers off.\n\nIt is not worth venturing out again. The streets are deserted as the curfew hour approaches. You settle down to sleep.";

        Choices.clear();
        Choices.push_back(Choice::Base("Sleep with a SWORD ready by your side", 156, {Item::SWORD}));
        Choices.push_back(Choice::Base("Sleep with a SWORD tucked under the mattress", 90, {Item::SWORD}));
        Choices.push_back(Choice::Base("You have no SWORD", 7));

        Controls = Story::Controls::STANDARD;
    }
};

class Story311 : public Story::Base
{
public:
    Story311()
    {
        ID = 311;

        Text = "Grond is as you left it. There are still prisoners clamouring to be set free. You open as many doors as you can, prising the shackles off the poor prisoners, some of whom are too far gone even to begrateful.\n\nSoon you have released a multitude from the prison fortress. A mob of escaped convicts and their cruel guards start fighting outside the fortress walls. You leave them to it. They probably deserve each other. The city has sunk into a desperate state. You could almost imagine you were in hell.\n\nA moment of inspiration lightens your mood, however, as you decide to have the massive CHAINS which support the portcullis of the prison taken out. A sorcerer of ancient times forged those metal links. Perhaps you can use them to tether Hate.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::CHAINS});
    }

    int Continue(Character::Base &player) { return 45; }
};

class Story312 : public Story::Base
{
public:
    Story312()
    {
        ID = 312;

        Text = "It takes too long for you to concentrate your mind to produce the magical effect of the Visceral Pang. Your preparations are rudely and painfully interrupted by Skakshi's second stiletto dagger which buries its tip in your heart. You fall dead and there is no one left to save the wretched Judain from being wiped out for ever.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story313 : public Story::Base
{
public:
    Story313()
    {
        ID = 313;

        Text = "You speak the word of power that evokes the potent spell of Visceral Pang. Skakshi is seized by a palsy and he collapses to the sawdust-covered floor, writhing and frothing at the mouth.\n\n\"You, Skakshi, will take me to meet with your guildmaster, Melmelo. I have a proposition to put to him for his ears only.\"\n\n\"I'll do anything, Judain. Anything! Just release me from this wracking spell.\"\n\nYou take pity on the miserable wretch and banish the spell with a thought. Skakshi rises slowly to his feet and says he will take you to Melmelo's stronghold, claiming that only he knows the password. Skakshi must fear you are going to kill him.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 181; }
};

class Story314 : public Story::Base
{
public:
    Story314()
    {
        ID = 314;

        Image = "images/grand-canal.png";

        Text = "You sing the song of the traveller's return with as jaunty an air as you can muster. The murky waters of the canal ripple and bubble unnervingly as you glide across the surface. You stare through the surface reflection for any signs of the roiling coils of Hate moving below the surface.\n\nYou turn out onto Grand Canal, where a puff of wind turns the gondola sideways and towards the sea. A flock of seagulls passes overhead and still you have seen no one. Looking ahead of the prow you notice a swelling in the water ahead of you. Something large is on its way towards you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Jump over the side and swim for shore", 331));
        Choices.push_back(Choice::Base("Remain in the boat and pole towards the shore", 205));
        Choices.push_back(Choice::Base("Remain in the boat and pole towards the gargantuan underwater form", 251));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            Choices[0].Destination = 344;
        }
        else
        {
            Choices[0].Destination = 331;
        }
    }
};

class Story315 : public Story::Base
{
public:
    Story315()
    {
        ID = 315;

        Text = "Dodging the Overlord's soldiers turns what would be an easy walk into a nightmarish series of short hops between patrols. You are continually forced to lie low for long periods until the coast is clear. Not until early evening do you reach the row of crooked houses, long since abandoned and ransacked. They do, however, provide a snug hole in which to lie low. You make yourself as comfortable as possible in the dank cellar of one of the houses, using broken crates to make a rough pallet on which to sleep.\n\nYou begin to draw up your plans the next morning. It could be worth watching to see if the Overlord leaves his palace, as you might be able to spot a weak link in his security arrangements.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 310; }
};

class Story316 : public Story::Base
{
public:
    Story316()
    {
        ID = 316;

        Text = "Mameluke's garret is hung with silk prints and tapestries depicting the great cities of the Archipelago and their rulers. There is thick rush matting on the floor and Mameluke would have lit the fire to warm you both, but the smoking chimney would have given you away.\n\nYou don't feel well. The sickness is shaking you like a palsy. Your face burns where the ichor of Hate splashed you. Mameluke looks at you with concern in his eyes.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            return 325;
        }
        else
        {
            return 340;
        }
    }
};

class Story317 : public Story::Base
{
public:
    Story317()
    {
        ID = 317;

        Text = "The invisibility spell works again for you and you quickly duck under the arboretum and back onto the street. Once there you make for Bumble Row as fast as you prudently can. Behind you the soldiers are cursing but they cannot even keep up with Lucie. She knows the dens and dives, the secret ways and ambushes of the city even better than you. You will have to keep an eye out for that little minx.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story318 : public Story::Base
{
public:
    Story318()
    {
        ID = 318;

        Text = "Tarkamandor peeks out into the dusk, then hurriedly waves you in. \"I heard you'd fled the city,\" he says in a hushed voice as he closes the shutters.\n\nYou drop into a chair by the hearth without waiting for an invitation. \"Decided I don't much care for the countryside,\" you reply. \"Got anything for me?\"\n\nHe sighs. \"You're not thinking of fighting back against the Overlord?\"\n\n\"Why not?\" you say with a smile.\n\n\"The odds are stacked against you -- more than a hundred to one!\"\n\n\"That's why I need some gear off you, isn't it?\" you tell him.\n\nAt last he brings out a casket of special items which he is prepared to sell you. The first item on offer is a SALVE OF HEALING; you can use this once at any time except when in combat to RESTORE ALL LOST Life Points. The second item is a SHIELD which is only useful if you have [SWORDPLAY]; the SHIELD has 6 Life Points which it can LOSE instead of you in battle, but MUST THEN BE DISCARDED. The third item is a BOOK OF MYTHS AND LEGENDS; if you buy this you can choose options for [FOLKLORE] even if you do not have that skill.\n\nThe HEALING SALVE costs 100 gleenars. The one-use SHIELD costs 200 gleenars. The BOOK costs 150 gleenars.";

        Bye = "You realize the others will be getting worried. Bidding Tarkamandor good evening, you hurry back to join them.";

        Choices.clear();

        Controls = Story::Controls::SHOP;
    }

    void Event(Character::Base &player)
    {
        Shop = {{Item::HEALING_SALVE, 100}, {Item::SHIELD, 200}, {Item::BOOK_OF_MYTHS_AND_LEGENDS, 150}};
    }

    int Continue(Character::Base &player) { return 190; }
};

class Story319 : public Story::Base
{
public:
    Story319()
    {
        ID = 319;

        Text = "You jump to safety, holding one corner of the bedspread, then tug it hard so that the girl slips from the bed and is dragged across the carpet. As soon as the swaddled form touches the filigreed carpet the wires spring forth to entangle themselves in the counterpane. Try as you might you cannot drag her any further.\n\nA large black form, like a manta ray or a vampire's cloak, detaches itself from the underside of the canopy of the Overlord's bed and drifts down through the air towards your head. You still have time to make a run for it if you want to leave the girl.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave the girl", 266));
        Choices.push_back(Choice::Base("Go back onto the carpet to cut the concubine free", 322));

        Controls = Story::Controls::STANDARD;
    }
};

class Story320 : public Story::Base
{
public:
    std::string PreText = "";

    Story320()
    {
        ID = 320;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your compassion for the wounded and maimed stands you in good stead. Whatever black thoughts have plagued your heart in the past, your noble and good deeds here in the prison fortress of Grond have shown you to be a pure-hearted hero.";

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::VENEFIX);
        }
        else
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});

            PreText += "\n\nYou gained the codeword SATORI.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 159; }
};

class Story321 : public Story::Base
{
public:
    Story321()
    {
        ID = 321;

        Text = "Tyutchev is leading you by the back alleys towards the foreigners' quarter.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            Choices.push_back(Choice::Base("Keep following him", 198));
            Choices.push_back(Choice::Base("Give up and return to your hidey-hole on Bumble Row", 160));
        }
    }

    int Continue(Character::Base &player) { return 410; }
};

class Story322 : public Story::Base
{
public:
    Story322()
    {
        ID = 322;

        Image = "images/filler3.png";

        Text = "As soon as you step onto the carpet the gold and silver filigree threads seem to bunch and tighten beneath the balls of your feet. You take another step and then struggle to make another, but the wires have snared around your ankle. The slender metal thread is cutting into your skin like a cheesewire. Cursing, you drop the concubine and bend to free yourself. It should be easy enough to get free before the wire cuts through your leg.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 305; }
};

class Story323 : public Story::Base
{
public:
    Story323()
    {
        ID = 323;

        Text = "Call as loud as you like for Hate has no ears with which to hears the cries of the tormented. Your cries do attract two rowing boats, however, which glide out from the granary wharf and are soon overtaking you. They are probably pirates so you pole rapidly towards the bank and decide to descend into the catacombs to seek Hate there.";

        Choices.clear();
        Choices.push_back(Choice::Base("Enter the crypts of the Megiddo dynasty", 365));
        Choices.push_back(Choice::Base("Ascend through the cellars of the Overlord's palace", 339));

        Controls = Story::Controls::STANDARD;
    }
};

class Story324 : public Story::Base
{
public:
    Story324()
    {
        ID = 324;

        Text = "\"No, I will not place myself in danger. I would be a fool to do so.\"\n\n\"Don't you trust me?\" Lucie looks shocked and hurt. \"I've been doing my best to help you and now you won't trust me.\"\n\n\"Lucie...\" You reach out to touch her, but she spits at you and runs off. Bewildered at her strange behaviour, you return to Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story325 : public Story::Base
{
public:
    Story325()
    {
        ID = 325;

        Text = "Hate has nourished itself on your evil thoughts of murder and revenge. You are ready now, a soul already lost. Tonight you will walk open-armed into the sickly embrace of Hate and give yourself up for ever, sucked into Hate's orgy of despair. There is no one left to save your fellow Judain. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story326 : public Story::Base
{
public:
    Story326()
    {
        ID = 326;

        Text = "As soon as you order the retreat, panic breaks out. By the time you have restored some semblance of order and discipline all the barricades have been smashed. Barricades are of no use against the monster. Your only hope is to kill it. This is the moment of truth. Triumph or perish.\n\nDusk begins to fill the streets. Only the decaying spires of the cathedrals still catch the golden glint of daylight. This may be the last sunset you will ever see, as the great rolling bulk of Hate comes slithering through the canals and streets towards you.\n\nHate extrudes a tentacle. In the pits of its green eyes, a flicker of intelligence shows. It recognizes you as its foe. A beam of shimmering mauve light shines down on you as the monster unleashes its magic.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            return 399;
        }
        else
        {
            return 274;
        }
    }
};

class Story327 : public Story::Base
{
public:
    Story327()
    {
        ID = 327;

        Text = "You arrive back at the jeweller's house in the dead of night. Clouds cover the moon like grave soil on the face of a corpse. Underfoot, the cobblestones glisten blackly. A cat prowls in the shadows across the street, making barely less noise than you. You have always prided yourself on your stealth and cool nerve, but more useful than either of these is your mastery of magic. For tonight's work, your normal humdrum repertoire of charms will not suffice; you dredge your memory for a more arcane enchantment. Murmuring an antique rhyme, you work a charm that will keep all the house's occupants asleep by making their dreams more vivid than reality itself. Even an earthquake could not rouse them before dawn. Confident that nothing can go wrong now, you force the front and enter.\n\nThe interior of the shop is dark. You see no reason not to light the lamps; it will make your job easier, and any passer-by would just assume the jeweller is working late. A hasty but thorough search of the shop reveals no sign of the diamond, but that is only to be expected. Probably it is kept in a treasure chest. Stepping over a slumbering guard dog, you start up the stairs.\n\nA floorboard creaks on the landing above. Startled, you look up to see a young soldier in the uniform of the Overlord's troop standing there. His face is ashen with fright, but he musters a brave semblance of self-assurance as he calls: \"You there! You're under arrest!\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Advance up the stairs to attack him", 176));
        Choices.push_back(Choice::Base("Run out of the shop and go back to join your friends", 190));

        Controls = Story::Controls::STANDARD;
    }
};

class Story328 : public Story::Base
{
public:
    Story328()
    {
        ID = 328;

        Text = "Tyutchev is one of the greatest living warriors. His sword has drunk the blood of scores of unfortunates who crossed him, or perhaps just admitted to worshipping the wrong god. There is a gleam of pleasure in his cruel eyes as he hefts his sword in one hand. You can be sure he will grant you no mercy, if he bests you.\n\nHis weapon is almost two feet longer than your blade and his reach is immense.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to get in close", 338));
        Choices.push_back(Choice::Base("Warily keep your distance and try to parry his first blow", 363));

        Controls = Story::Controls::STANDARD;
    }
};

class Story329 : public Story::Base
{
public:
    std::string PreText = "";

    Story329()
    {
        ID = 329;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "The stinking latrine offers no escape but a very high window up near the ceiling.";

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            if (!Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
            {
                PreText += "\n\nWithout [AGILITY], you have no choice but to surrender.";
            }
            else
            {
                Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 368, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
                Choices.push_back(Choice::Base("Surrender", 342));
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 368;
        }
        else
        {
            return 342;
        }
    }
};

class Story330 : public Story::Base
{
public:
    Story330()
    {
        ID = 330;

        Text = "You manage to find a few hours' sleep, balm to your troubled spirit though you awake cold and stiff, at dawn. There is a weariness which numbs your soul but then adversity is said to bring out the best in people. The sun is shining and reflected off the millpond calm surface of the canals. You slink carefully along back alleyways to the rendezvous. By the time you are nearing Fortuny Street the wind has picked up, whipping the stench of death away from the city and bringing with it hope for renewal. Small waves lap at the canal walls.\n\nLucie is waiting just as she said she would, under the eaves of the tax collector's offices on Rackman Row. She smiles to see you, looking well, her cheeks are rosy red and she is as pretty as ever. She links her arm in yours and says she has something to show you. You walk beside her, enjoying a moment's peace from the burden of trying to save your people. She does have news for you.\n\n\"All is not well with the Overlord. He is being consumed by Hate like so many of his subjects. His concubine, Venus, has the marks of Hate on her body, yet still he lies with her. He has become morose and listless. Venus's handmaid told me all this. There is something terrible amiss at the palace. What will become of us if our leaders are falling into the embrace of the coils of Hate. How shall we be saved?\"\n\n\"I will save you, Lucie. Does the concubine's handmaid know why the Overlord ordered the purging of my people?\"\n\n\"He needed scapegoats so the wrath of the people could be deflected from him and his corrupt courtiers. The Judain have always made good scapegoats. Sorry, I didn't mean...\" She puts her hand on your shoulder to show she likes you.\n\n\"It doesn't matter, we Judain brave the slings and arrows of outrageous fortune by habit. We are inured to the hatred of others.\"\n\nLucie runs her hand over your chest.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 345; }
};

class Story331 : public Story::Base
{
public:
    Story331()
    {
        ID = 331;

        Text = "You flounder in the polluted waters of the Grand Canal. Like most people who live in Godorno, within a stone's throw of the water, you can't swim. Your life passes before you as you drown. There is no one left to save the Judain. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story332 : public Story::Base
{
public:
    Story332()
    {
        ID = 332;

        Text = "It is eerily silent down in the dank bones of the fortress. Hanging your lantern outside the nearest door reveals a starving pair of Judain, manacled to the wall. It takes three hours to set all the prisoners free. Most are pathetically grateful to you as their saviour, having long given up hope of any release save the merciful release of death. The prisoners are looking at you with awe. You hear them whispering that you are a god come down from the heavens to right the wrongs of the ancient city. You organize stretcher parties to bear those who cannot walk out of the prison. You might dare to set up a sanatorium now. that you have directly challenged the Overlord's power.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 320; }
};

class Story333 : public Story::Base
{
public:
    Story333()
    {
        ID = 333;

        Text = "\"I am one of the Overlord's paid informers,\" you shout with a commanding air. \"Follow me, I will take you to the nests of the Judain scum. Follow me.\" You turn your back and set out towards the fruit market. \"Come, I will show where three Judain spies and embezzlers are hiding out.\"\n\nThe mob follow eagerly, crying for Judain blood. One of them asks how they are to know you are the Overlord's informer. You start to run, calling: \"Hurry or we may be too late. If word reaches them before us they will flee the roost.\"\n\nYou run fast and the others can hardly keep up. Entering the fruit market you dive into a throng of people who are picking over a mound of rotting fruit that has been piled at the side of the road. As you make your escape into a narrow side-street, you hear the crowd calling for your blood.\n\nIt is not safe to remain in the city at the moment.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave by the usual means: the main gate to the trade road", 53));
        Choices.push_back(Choice::Base("Try to slip from the city unseen", 70));

        Controls = Story::Controls::STANDARD;
    }
};

class Story334 : public Story::Base
{
public:
    Story334()
    {
        ID = 334;

        Text = "You find Skakshi at the Inn of the Inner Temple, occupying his usual booth. But now he has a morose look, and the bluster has gone out of him. \"You still want to meet Melmelo ?\" he asks.\n\n\"You've changed your tune, Skakshi.\"\n\nHe drains his mug and gets up. \"The city's changed. Now the Overlord has ordered the rounding-up of all foreigners. My sister-in-law is from Kishtaria. Did you know that, Judain?\"\n\n\"I didn't. But soon the Overlord's measures will become still harsher. I'm glad you've seen reason, Skakshi.\"\n\nHe takes you by narrow back streets to an ornamental villa on the edge of the criminal dens of the poor quarter. The villa itself is quite lavish, in contrast to the hovels nearby. Melmelo is the king of this dungheap, all right. Thanking Skakshi, you watch him slip away into the shadows before knocking on the door.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::COOL);
    }

    int Continue(Character::Base &player) { return 12; }
};

class Story335 : public Story::Base
{
public:
    Story335()
    {
        ID = 335;

        Text = "Your mighty struggles are in vain. You are not ready for this untimely death. There is no one left now to save your people.\n\nMemories of the times you have felt Hate smoulder in your breast come unbidden into your mind and the strength seems to drain out of your muscles. The warm wet embrace of Hate welcomes you and your body is slowly and inexorably drawn inch by inch into the seething mass of the monster. Soon your head too is being drawn in. Your arms and legs have gone numb and you start to fight for breath as your nostrils and lips are sealed over by the soft purple flesh of Hate. You drown in the body of Hate and the city has lost its only saviour. Your tormented half-life has begun.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story336 : public Story::Base
{
public:
    Story336()
    {
        ID = 336;

        Text = "Lucie slaps you back and flounces away, back to her little hovel. She is a very headstrong young woman. There is no point in trying to follow her now, she knows at least as much as you do about the alleyways and dens of Godorno. You decide to ask your mulatto friend, Mameluke, to help you.\n\nMameluke greets you warmly. He is preparing to eat a cat which he has skinned and roasted over a slow fire; he offers to share it with you. Famished, you thank him and eat greedily while trying not to think of the rats the cat has itself dined upon in the past, in the fouled gutters of the city.\n\nMameluke insists on telling you about a mishap which befell him this morning: \"In going, about three hours ago, to a rendezvous with a girl of Godorno -- unmarried and a daughter to one of the nobles -- I tumbled into the Grand Canal, my foot slipping as I got out of my gondola owing to the cursed slippery steps of the palaces here. In I flounced like a carp, and went _ dripping like a Triton to my Sea Nymph and had to scramble up to a grated window -- 'fenced with iron within and without, lest the lover get in or the lady get out'.\"\n\nMameluke is in a whimsical mood. You are reminded of the man who sat around fiddling while the city burned. Nevertheless you implore him to help you for the sake of your people.\n\n\"I will help you, my friend,\" he says, \"if only to rid myself of the wailing of the prisoners, which is a constant affront to my sanity. What is your plan?\"\n\n\"I thought we'd descend into the catacombs below the city,\" you reply. \"There we can look for a way into the prison.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 412; }
};

class Story337 : public Story::Base
{
public:
    Story337()
    {
        ID = 337;

        Image = "images/filler2.png";

        Text = "You could go to find the jewel that Melmelo spoke of, somewhere in the Tower of the Sentinel.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go to the Tower of the Sentinel", 144));
        Choices.push_back(Choice::Base("Decide against that course of action for the present", 100));

        Controls = Story::Controls::STANDARD;
    }
};

class Story338 : public Story::Base
{
public:
    Story338()
    {
        ID = 338;

        Text = "Tyutchev is leading you by the back alleys towards the foreigners' quarter.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::AGILITY, Skill::Type::SWORDPLAY}))
        {
            Choices.push_back(Choice::Base("Fight on", 377));
            Choices.push_back(Choice::Base("Turn and flee", 199));

            if (Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
            {
                Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 367, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            }
        }
    }

    int Continue(Character::Base &player) { return 367; }
};

class Story339 : public Story::Base
{
public:
    Story339()
    {
        ID = 339;

        Text = "As far as you know no one who has desecrated the tombs of the Megiddo dynasty has ever come back out of the catacombs. You resolve to be very careful. It is said that four tomb robbers of the Savanorola years did escape but that they had been turned into foul-smelling scarab beetles, which were eaten alive by pigs.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 409; }
};

class Story340 : public Story::Base
{
public:
    Story340()
    {
        ID = 340;

        Image = "images/filler2.png";

        Text = "Hate is trying to claim you for its own. Your vision blurs and your head aches. You close your eyes and all you can see is the staring green pools of Hate's eyes. Hate is searching your soul for evil thoughts but you pass the test. You lie back as Hate leaves you to search for another lost soul and the fever passes.\n\nMameluke mops your brow with a moist sponge. You gratefully accept his offer of a couch for the night and wake up feeling a little refreshed, though the cries of Grond's tortured damned still sicken.\n\nYou RECOVER 2 Life Points.";

        Bye = "Thanking Mameluke for his help, you return to your hideout on Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 2);
    }

    int Continue(Character::Base &player) { return 159; }
};

class Story341 : public Story::Base
{
public:
    Story341()
    {
        ID = 341;

        Text = "Did you think you could frighten five hundred guards inside a huge fortress with ten-foot thick walls that stand forty feet high into letting you in among them? They have only one reply to such a hideous apparition as you have conjured: they shoot you with their crossbows from the arrow slits on either side and above the gates. You are peppered like a pincushion. As you die and the magic fades there is a low heartless cheer as the guards realize they have slaughtered yet another Judain. There is no hero left now to save the city. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story342 : public Story::Base
{
public:
    Story342()
    {
        ID = 342;

        Text = "You are taken under arrest to the prison fortress of Grond. The courtyard is thronged with captive Judain. More are being brought in all the time. Without a chance to say who you are, or to pretend loyalty to the Overlord, they force you into underground cellars where, in the cramped dark, you fight to breathe. When the air is gone the weight of dead people pressing on you cannot be borne. You have no choice but to give up your spirit as the rest of your people have already.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story343 : public Story::Base
{
public:
    Story343()
    {
        ID = 343;

        Text = "You are pure of heart and so manage to break free as two tentacles snap forth from Hate's coils and try to drag you into the soft cloying flesh of the monster. You turn tail and flee up the stairway and out into the street where the fresher air makes your senses swim. You will have to abandon Lucie. She is already a lost soul. You slink back towards your hidey-hole on Bumble Row to ponder your next actions.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 195; }
};

class Story344 : public Story::Base
{
public:
    Story344()
    {
        ID = 344;

        Text = "You strike out bravely for the nearest bank. Unlike most of the folk of Godorno, who pass their whole lives within a stone's throw of the water, you can swim quite strongly. Behind you there is a splash as the gilded gondola is moved by something large, and then the snort of an ugly but harmless sea cow. You have swum too far to turn back now so you swim on and soon gain the bank. You haul yourself out of the murky canal and sit on the road to dry in the midday sun. Soon you have the uneasy feeling of being watched.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 374; }
};

class Story345 : public Story::Base
{
public:
    Story345()
    {
        ID = 345;

        Image = "images/lucie.png";

        Text = "Lucie reaches up to touch the AMULET that swings around your neck and recoils. \"Ow, it's hot! How can you bear it?\"\n\n\"My leather jerkin protects me. If it is hot that means danger threatens. We must leave here.\"\n\nShe reaches up again and snatches at the AMULET, grimacing with pain. She rips it from your neck, scattering the links of the fine gold chain across the wbbles and runs quickly away from you. You give chase but she ducks beneath an overturned cart and down a hatch into a cellar. It is dark and you lose sight of her. Lucie knows the back ways and dives of the city even better than you do; you will never find her.\n\nYou cannot understand Lucie doing such a thing. She is a thief, admittedly, but it is not in her character to steal from friends. Perhaps she has been the victim of a dibbuk. These invisible creatures settle on a person's shoulder and take charge of their thoughts, causing them to do things that would normally be against their nature. Well, in that case it has made a mistake in causing her to take your AMULET. The protective magic will soon drive the dibbuk off, leaving Lucie with no memory of the event.\n\nStill, you have lost your AMULET. Until you find another you will not be able to use your [CHARMS] skill. There must be one somewhere in the city, so perhaps you should start looking. Alternatively, you could return to your hideout and see if anyone there knows where you might find one; after all, the Judain are famous for their skill in manufacturing magical AMULETs and luckstones.";

        Choices.clear();
        Choices.push_back(Choice::Base("Start scouring the city for a new AMULET to buy", 213));
        Choices.push_back(Choice::Base("Look for Lucie to see if she still has it once the dibbuk has released her from its control", 257));
        Choices.push_back(Choice::Base("Consult your own people first", 202));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::STREETWISE))
        {
            Choices[0].Destination = 243;
        }
        else
        {
            Choices[0].Destination = 213;
        }
    }
};

class Story346 : public Story::Base
{
public:
    Story346()
    {
        ID = 346;

        Text = "Lucie smirks coquettishly as you tell her off and says, \"Well, it's true. Hate take them all and good riddance to bad rubbish.\"\n\nYou sigh, knowing you will never change her. You suspect that at least one of the criminal inmates of Grond must have done something dreadful to her before his imprisonment.\n\n\"Surely there must be something you can do?\" you ask. \"Don't you know any of the guards?\"\n\n\"I suppose I do, one or two. There's Captain Khmer in the east tower. He oversees the towngate and the eastern courtyard. I could smuggle you in there.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Go along with Lucie's plan to smuggle you into the prison fortress of Grond", 354));
        Choices.push_back(Choice::Base("Thank Lucie but decline her brave offer of help", 366));
        Choices.push_back(Choice::Base("[CHARMS] Consult your AMULET", 388, Skill::Type::CHARMS));

        Controls = Story::Controls::STANDARD;
    }
};

class Story347 : public Story::Base
{
public:
    std::string PreText = "";

    Story347()
    {
        ID = 347;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You drag the pallet into the murk beside the back wall and fall into an unnaturally deep slumber. You dream of searching a forest for your lost mother.\n\nYou awake feeling nauseous. You move to turn over and find a trail of viscous slime across your outstretched arm, like the track of a gigantic slug. Gagging, you feel vomit burn the back of your throat.";

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            if (!Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
            {
                PreText += "\n\nYour arm is permanently withered.";

                if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::SWORDPLAY, Skill::Type::AGILITY}))
                {
                    auto count = 0;

                    std::string skills = " You can no longer use the ";

                    if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
                    {
                        count++;

                        PreText += "[SWORDPLAY]";
                    }

                    if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
                    {
                        if (count > 0)
                        {
                            PreText += " and ";
                        }

                        count++;

                        PreText += "[AGILITY]";
                    }

                    PreText += " skill";

                    if (count > 1)
                    {
                        PreText += "s";
                    }

                    PreText += ".";

                    Character::LOSE_SKILLS(player, {Skill::Type::SWORDPLAY, Skill::Type::AGILITY});
                }
            }
            else
            {
                PreText += "\n\nYou wash off the slime in a barrel of rainwater and find that you are unscathed.";
            }
        }
        else
        {
            PreText += "\n\nYour arm looks withered but you wash off the slime in a barrel of rainwater and find that you are unscathed.";
        }

        PreText += "\n\nThis is no place to stay -- it is time to find a new hideaway. You set out for Bumble Row, knowing that most of the shopkeepers there shut up shop long ago and it will be largely deserted.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 315; }
};

class Story348 : public Story::Base
{
public:
    Story348()
    {
        ID = 348;

        Text = "The slaughter is swift and bloody. The look of disgust in the eyes of your fellow Judain when it is over and there are only the moans of the dying is eloquent testimony that revenge is a bitter fruit. How could you have let your people commit such barbaric atrocities?";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::SATORI}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::SATORI);
        }
    }

    int Continue(Character::Base &player) { return 159; }
};

class Story349 : public Story::Base
{
public:
    std::string PreText = "";

    Story349()
    {
        ID = 349;

        Choices.clear();
        Choices.push_back(Choice::Base("Forget about Lucie and smash the tentacle to pulp", 147));
        Choices.push_back(Choice::Base("You hesitate", 103));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "There is no sunlight to power the Jewel down here in the street. Your gaze is drawn up to the towers and parapets of the city, where the sunset yet flickers like a golden flame against the blue-grey of the sky. You must scale the crumbling wall to reach the daylight. As you start to climb a pile of rubble, Hate lashes out at you.\n\n";

        auto DAMAGE = -5;

        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            DAMAGE = 0;

            PreText += "[AGILITY] You effortlessly dodge the attack and continue climbing unscathed.";
        }
        else if (Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
        {
            DAMAGE = 0;

            PreText += "[ELFIN BOOTS: AGILITY] You effortlessly dodge the attack and continue climbing unscathed.";

            Character::LOSE_ITEMS(player, {Item::Type::ELFIN_BOOTS});
        }

        if (DAMAGE < 0)
        {
            Character::GAIN_LIFE(player, DAMAGE);

            PreText += "You LOST " + std::to_string(-DAMAGE) + " Life Points.";
        }

        if (player.Life > 0)
        {
            PreText += "\n\nAt last you reach the parapet withjust a few steps left to climb. Sunset bathes the stone wall just above where you stand. A huge bloated tentacle, the largest of all, rises up out of the canal and looms over the rampart at the top of the parapet. It is blocking your way but you only have to drive this last tentacle aside and you will be able to reach the sunlight. You prepare to smite the tentacle but looking out of it at you is Lucie! Her face and body are embedded in the purple mass which you must rend and smash if you are to reach the top.";
        }

        Text = PreText.c_str();
    }
};

class Story350 : public Story::Base
{
public:
    Story350()
    {
        ID = 350;

        Text = "You have dared to wait in the lion's den for too long. The Overlord's personal bodyguard are led by a magician who binds your feet to the spot as soon as he sets eyes on you. You are borne away to be tormented in the fortress of Grond. You will not survive. There is no one left now to save the Judain. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story351 : public Story::Base
{
public:
    Story351()
    {
        ID = 351;

        Text = "Lucie watches as Tyutchev's blade chops into you as though you were already dead meat. It is indeed butchery and it takes Tyutchev only a few moments more to finish you off. He isn't even wounded. You have fought one of the greatest living swordsmen and you don't live to tell the tale. Now there is no one left to save the Judain.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story352 : public Story::Base
{
public:
    Story352()
    {
        ID = 352;

        Image = "images/filler2.png";

        Text = "When you reach the new breach iri the sea wall you find it choked with decaying bodies, almost as if Hate had voided itself into the sea. But they do not show the purple blotches of Hate's contagion. Something or someone else has piled these bodies here. Sickened by the stench you decide to find a different path.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 262; }
};

class Story353 : public Story::Base
{
public:
    Story353()
    {
        ID = 353;

        Image = "images/barricade.png";

        Text = "The barricade is composed of pews from the nearest temple, doors stripped from nearby deserted houses, flagstones and carts. The carts have been laden with mud. Even an elephant could not break through.\n\nThe blockage is ten feet high and in places a parapet has been built on the defenders' side from which potshots can be taken at the Overlord's city guards as they advance. You have archers in the windows and on the roofs of the houses on either side of the barricade. Morale is high, the stories of how you killed scores of guards in the prison fortress of Grond have placed you high in the esteem of your people.\n\nYou are conferring with the captain of the archers stationed in the houses when everyone suddenly goes quiet. They are all staring down the cracked road towards the Grand Canal from which Hate is raising its dripping baleful-eyed face. Its feelers quest in the air for your scent and it rises out of the canal, smashing houses on either side as it comes. The barricade is proof against a stampede of elephants but not against Hate itself.";

        Choices.clear();
        Choices.push_back(Choice::Base("Order a tactical withdrawal", 326));
        Choices.push_back(Choice::Base("Stand at the barricade and defy the monster", 233));

        Controls = Story::Controls::STANDARD;
    }
};

class Story354 : public Story::Base
{
public:
    Story354()
    {
        ID = 354;

        Text = "You wait in the bakery adjacent to the prison while Lucie goes in search of Captain Khmer. It is a long wait, but at least there is fresh bread to eat and the bakers and scullions will not give you away. They seem to be firm friends with Lucie. You have plenty of time to wonder how she binds people to her. These peasants are taking a terrible risk sheltering you under their roof.\n\nAt last Lucie comes back. She looks troubled. but says, \"I've arranged things for you. Walk up to the towngate in five minutes' time. They will open up and let you through. They won't harm you, but from then on you are on your own. I think something has gone terribly wrong in there. It wasn't easy to arrange. Don't waste my efforts in failure, Judain.\" She looks at you reproachfully. Mameluke is purple with embarrassment.\n\n\"I'm going to the Silver Eel. Come to me there and tell me how you fared.\" With that and a little squeeze of the shoulder she is gone.";

        Choices.clear();
        Choices.push_back(Choice::Base("Wait five minutes and then knock at the towngate of the prison fortress of Grond", 413));
        Choices.push_back(Choice::Base("Slink off back to Bumble Row", 220));

        Controls = Story::Controls::STANDARD;
    }
};

class Story355 : public Story::Base
{
public:
    Story355()
    {
        ID = 355;

        Text = "You arrive back at the jeweller's house later that night and stand surveying it in the moonlight. Your overwhelming impression is that this has all the hallmarks of a trap. The Overlord would hardly leave a priceless DIAMOND unguarded -- and he must be aware that his security measures, while enough to deter the casual thieves of the town, are simply an enticement to the pride of any true professional. So without a doubt there will be soldiers stationed in the house.\n\nClimbing up to the first floor, you prise open a window and tiptoe along the landing, listening at each door in turn. Sure enough, from behind one of the doors comes the rattle of gaming dice and the unmistakable banter of bored soldiers. You pause. This is where the DIAMOND must be kept.\n\nContinuing along the landing .to the next door, you hear the sound of thundering snores. The jeweller's bedroom. Quietly inching the door open, you go to a cupb_o_ard and extract a nightshirt and cap, which you put on over your clothes. Then, darting swiftly along the landing, you fling open the first door and cry: \"Thief! There's a thief downstairs!\"\n\nThe three soldiers leap up in amazement and grab their weapons, rushing past you along the landing with excited shouts. They are so intent on catching the thief -- and thereby earning a bonus -- that they don't even glance at your face.\n\nYou tear off the nightshirt and look around the room. A small locked chest catches your eye. Surely that is where the DIAMOND is. The lock looks pretty secure, but you can break it at your leisure once you are safely away from here. You pick up the chest, tucking it under your arm for a hasty getaway, but then an unpleasant shadow of doubt clouds your elation: what if the chest is only a decoy, and the DIAMOND is really kept somewhere else?";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave at once with the chest", 358));
        Choices.push_back(Choice::Base("First open it and make sure you have the DIAMOND", 394));

        Controls = Story::Controls::STANDARD;
    }
};

class Story356 : public Story::Base
{
public:
    Story356()
    {
        ID = 356;

        Text = "Melmelo's door is opened by his major-domo, a grizzled old man with a wooden leg, who growls, \"Get you gone, vile Skakshi, or you'll not live to see the dawn.\"\n\n\"What's this I hear about Hammer being hired to kill me?\" says Skakshi, ignoring his threat. \"I didn't know Melmelo feared me so strongly.\"\n\n\"You're beneath the notice of a man with Melmelo's wit and accomplishments. Melmelo wouldn't waste money on that greedy cutthroat Hammer over the likes of you, Skakshi.\"\"Do I have your word on that, pegleg?\"\n\nThe major-domo fixes him with an incandescent stare. \"Be off with you.\"\n\nSkakshi seems satisfied but as he goes he calls back over his shoulder, \"It was a Judain scumbag who told me Hammer was after me. Look out, you know what slippery customers the Judain are.\" He and the major-domo both hawk and spit into the gutter at the mention of the word Judain.\n\nYou wait till Skakshi has turned the corner out of sight before knocking on the door, not too loud and not too timid.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 12; }
};

class Story357 : public Story::Base
{
public:
    Story357()
    {
        ID = 357;

        Text = "As you square up to the cunning thief, he sends his throwing knife spinning end over end through the air towards your heart. Absolute quiet descends on the tavern as your life hangs in the balance.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 58, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            Choices.push_back(Choice::Base("Otherwise", 108));
        }
    }

    int Continue(Character::Base &player) { return 58; }
};

class Story358 : public Story::Base
{
public:
    Story358()
    {
        ID = 358;

        Text = "Only when you have put a safe distance between you and Mire Street do you pause to inspect the DIAMOND. It is as large as a walnut, and sparkles like a drop of crystallized starlight. The beauty takes your breath away -- and you have seen some excellent gems in your time. It would have made a fine sceptre for the Overlord, but you'll put it to more practical use. Dropping the DIAMOND into your pocket you go to fence it.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::DIAMOND});
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::STREETWISE))
        {
            return 114;
        }
        else
        {
            return 128;
        }
    }
};

class Story359 : public Story::Base
{
public:
    std::string PreText = "";

    Story359()
    {
        ID = 359;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The Judain are horrified at your suggestion they take the lepers in. Many of the unfortunates are suffering from wet leprosy, which is highly contagious. Your own people shun you for fear of catching the curse.\n\nThose who say the Judain are attracting too much attention to themselves with their campaign of assassinations win the vote in the general council of Judain. The resistance cells are disbanded. This will make it harder to get around the city, as before you could rely on the resistance for help.\n\nIt grieves you that you are unable to help the lepers. They go on their way, staggering about town, begging for scraps, fighting the dogs for any scraps of offal they can find in the gutter.";

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::VENEFIX);
        }
        else
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});

            PreText += "\n\nYou gained the codeword SATORI.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 20; }
};

class Story360 : public Story::Base
{
public:
    std::string PreText = "";

    Story360()
    {
        ID = 360;

        Choices.clear();
        Choices.push_back(Choice::Base("Do as Lucie implores", 387));
        Choices.push_back(Choice::Base("Kneel at her side to comfort her", 273));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "";

        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::VENEFIX);
        }
        else
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::SATORI});

            PreText = "You gained the codeword SATORI.\n\n";
        }

        PreText += "With great care, you crawl down into the basement. There is an unpleasant smell of honeysuckle and camphor. A glimmer of light filtering through the broken ceiling illuminates Lucie. She is too ill even to move from her bed. Her features are wan; the light in the room gives her a bluish look and her eyes are sunken slightly, ringed with dark circles of fatigue. She looks like a little lost soul.\n\nShe calls your name. Her arm falls limp after she beckons you to her side. \"Leave me. Go quickly. It is too late for me, but you can still save yourself. Don't let me die in vain.\"\n\n\"Lucie...\" You take another step towards the bed.\n\n\"No, don't come close!\" she gasps. \"Go now, while you still can.\"";

        Text = PreText.c_str();
    }
};

class Story361 : public Story::Base
{
public:
    Story361()
    {
        ID = 361;

        Text = "You cast the spell and hail the guards behind the grilles in the gate. They do not answer and you are beginnin to think your magic has missed its mark when there is a great clanking and grinding and the gates start to inch apart. It is a great labour to open them with the iron machinery forged by smiths from the mountains and you call out hearty thanks, as if to long-lost friends, but there is no one to answer your call. It is as if the gate was opened by ghosts. The sweet cloying smell of crushed roses and honeysuckle lingers here. Something is terribly wrong.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 413; }
};

class Story362 : public Story::Base
{
public:
    Story362()
    {
        ID = 362;

        Text = "Speaking the word of power and clapping your hands vigorously brings forth a cloud of poisonous gas which smothers the guards and the old egg-seller. You leave them coughing and Tetching and set out into the once bustling city.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 300; }
};

class Story363 : public Story::Base
{
public:
    std::string PreText = "";

    Story363()
    {
        ID = 363;

        Choices.clear();
        Choices.push_back(Choice::Base("Sit with her", 403));
        Choices.push_back(Choice::Base("Follow Tyutchev", 321));
        Choices.push_back(Choice::Base("Bid Lucie farewell and leave", 199));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Tyutchev's sword lashes out, smashing your parry aside. The blade cuts into your breast just above the heart. Luckily your jerkin absorbs some of the impact and the blow does not penetrate . the muscle. Even so, it is very painful.\n\nYou LOSE 4 Life Points.";

        Character::GAIN_LIFE(player, -4);

        if (player.Life > 0)
        {
            PreText += "\n\nLucie suddenly says, \"Spare the Judain, Tyutchev, for me. The Overlord's men will do for the poor wretch soon anyway.\"\n\n\"If it makes you happy.\" Tyutchev shrugs and carefully slides his sword back into the scabbard strapped to his back. \"What's the Judain to you?\"\n\n\"A hero, valiant and true. The one that the Judain have put their faith in to save them.\"\n\n\"I didn't know you had added such undesirables to your list of lovers,\" he says, giving you a sneering sidelong look.\n\n\"We had a meeting arranged but we were disturbed,\" says Lucie. \"I wish to speak with the Judain. Leave us, please, Tyutchev.\"\n\n\"As you wish, girl. Will you come to my abode this evening?\"\n\n\"Will Cassandra be there?\"\n\n\"No. She took ship for Aleppo on the rising tide. We'll be alone.\" So saying he turns on his heel, his black cloak flaring out like a sail, and walks out of the Silver Eel in five great strides.\n\nLucie touches your sleeve. \"Come my friend, join me. Are you hurt?\" she says, motioning to what had been Tyutchev's chair.";
        }

        Text = PreText.c_str();
    }
};

class Story364 : public Story::Base
{
public:
    Story364()
    {
        ID = 364;

        Text = "Hate squirms and writhes, shaking the city like an earthquake. The people creep out of hiding to pelt it with every missile they can find, but there seems to be no way of killing the monster. At length it tears itself free and slithers off. Its mighty efforts have undermined the plaza, which now collapses into the river. The facade of the Bargello topples and you plummet to your death in a cascade of falling masonry.\n\nThe city crumbles and is lost for ever beneath the waves. Hate has completed its work.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story365 : public Story::Base
{
public:
    std::string PreText = "";

    Story365()
    {
        ID = 365;

        Image = "images/jade-warriors.png";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The tunnels take you deeper and deeper into the bones of ancient Godorno. At last you stumble through a rotten tapestry into a chamber filled with gold-plated furniture and funeral biers with sarcophagi atop them. Four glassy green statues stand at the corners of the room.\n\nThe four Jade Warriors clank menacingly as they come to life before you. The green swords in their hands cut the beams of light, giving each blade an aura like a rainbow. The light shimmers off the jagged blades and off the chiselled planes of the huge warriors themselves. When they step towards you, their heavy tread grinds the rubble beneath their armoured feet to powder. The whole room reverberates to their measured advance.";

        Choices.clear();

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::SWORDPLAY, Skill::Type::UNARMED_COMBAT, Skill::Type::SPELLS, Skill::Type::AGILITY}) && !Character::VERIFY_ITEMS(player, {Item::Type::CENSER_OF_FRAGRANT_INCENSE}) && !Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
        {
            PreText += "\n\nThe nearest Jade Warrior slashes you, inflicting the LOSS of 6 Life Points";

            Character::GAIN_LIFE(player, -6);

            if (player.Life > 0)
            {
                PreText += "\n\nYou realize you must flee.";
            }
        }
        else
        {
            Choices.push_back(Choice::Base("[SWORDPLAY] Do battle", 389, Skill::Type::SWORDPLAY));
            Choices.push_back(Choice::Base("Fight with [UNARMED COMBAT]", 296, Skill::Type::UNARMED_COMBAT));
            Choices.push_back(Choice::Base("[SPELLS] Cast Encloud", 42, Skill::Type::SPELLS));
            Choices.push_back(Choice::Base("[SPELLS] Cast Rulership", 66, Skill::Type::SPELLS));
            Choices.push_back(Choice::Base("[SPELLS] Cast Bafflement", 96, Skill::Type::SPELLS));
            Choices.push_back(Choice::Base("[SPELLS] Cast Vanish", 102, Skill::Type::SPELLS));

            if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
            {
                Choices.push_back(Choice::Base("Fall back on [AGILITY]", 277, Skill::Type::AGILITY));
            }
            else
            {
                Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 277, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            }

            Choices.push_back(Choice::Base("Use the CENSER OF FRAGRANT_INCENSE", 204, {Item::CENSER_OF_FRAGRANT_INCENSE}));
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story366 : public Story::Base
{
public:
    Story366()
    {
        ID = 366;

        Text = "You drop in on your friend Mameluke, a man of far-off Tartary. He listens to your plans to enter Grond through the catacombs beneath the city, then shakes his head.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 412; }
};

class Story367 : public Story::Base
{
public:
    Story367()
    {
        ID = 367;

        Text = "Only a very agile fighter like yourself could slip past the mesmerizing point of Tyutchev's sword as it whistles through the air in deadly arcs. You crouch and spring forward, then lunge your SWORD into the gap in his armour, beneath his armpit. There is a satisfying groan from Tyutchev who staggers back and looks on you with new respect. But he is not beaten yet.";

        Choices.clear();
        Choices.push_back(Choice::Base("Call on him to put down his sword, saying that senseless slaughter serves no purpose", 397));
        Choices.push_back(Choice::Base("Fight on", 373));

        Controls = Story::Controls::STANDARD;
    }
};

class Story368 : public Story::Base
{
public:
    Story368()
    {
        ID = 368;

        Text = "You leap high and brace yourself against the corner walls, edging your way up to the window as they call for you to stop skulking in the privy like a criminal. By the time they risk following you into the cramped confines of the privy you have reached the window and dropped down through it into an alley below. You get away before they can run round to the back alley.\n\nListening to the bloodcurdling yells of a mob that seems to be rampaging back and forth across the city you decide the time has come to leave Godorno.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave by the usual means, through the main gate to the trade road", 53));
        Choices.push_back(Choice::Base("Try to slip from the city unseen", 70));

        Controls = Story::Controls::STANDARD;
    }
};

class Story369 : public Story::Base
{
public:
    Story369()
    {
        ID = 369;

        Text = "This is not the first time in your life you have had to escape from an angry mob. You turn down a side street and, seeing an open door, sneak into a house. The inhabitants are having supper and shouting at each other. You creep quietly upstairs, unnoticed, out onto a balcony from which you jump to the balcony of the house opposite. Creeping out through that house you rejoin another street and double back onto your old route to shake off your pursuers.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 201; }
};

class Story370 : public Story::Base
{
public:
    Story370()
    {
        ID = 370;

        Text = "Using the flat of your blade reduces the viscous purple flesh of the monster to a jelly. Several of the guards are now able to pull themselves out of the body of Hate as it recoils from your punishing blows. Those still trapped implore their comrades to stay and free them, but not one of those you have rescued is prepared to risk his life for his friends. Eyes wide with terror, they bolt past you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 34; }
};

class Story371 : public Story::Base
{
public:
    Story371()
    {
        ID = 371;

        Text = "Finding Lucie later in the day is easy. It turns out she has also been looking for you. \"Come!\" she says, tugging you by the sleeve. Her tone is urgent and breathless. \"I have someone important for you to meet. Someone who can help you to save your people. No friend of the Overlord, this man.\"\n\n\"Who is it? Who in all Godorno will help us Judain?\"\n\n\"You wouldn't believe me if I told you,\" she replies.\n\n\"Of course I would, Lucie, I believe every word you say.\"\n\n\"You'll see soon enough. Come, we must go to . Fortuny Street. We can meet him there.\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::CUNNING, Skill::Type::STREETWISE}))
        {
            Choices.push_back(Choice::Base("Put your trust in Lucie", 411));
            Choices.push_back(Choice::Base("Refuse to go with her in case she is leading you into a trap", 324));
        }
    }

    int Continue(Character::Base &player) { return 407; }
};

class Story372 : public Story::Base
{
public:
    Story372()
    {
        ID = 372;

        Text = "To your horror your spell backfires, singeing your eyebrows. Before you can recover the guards, who know better than to allow a magician time to cast a second spell, run you through with their rapiers, while the old woman screams with the shock of it. There is no one left alive to save the Judain now. They will all perish and be wiped from the face of the earth.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story373 : public Story::Base
{
public:
    Story373()
    {
        ID = 373;

        Text = "Now that he is wounded, Tyutchev is more deadly than ever. His blade cuts the air in a whirlwind of fury and you are driven back. You cannot parry Tyutchev' s flashing blade for ever and your ripostes fall short as the pale-faced swordsman then steps back to use his longer reach. There is no chance to break off combat or use a spell.";

        Choices.clear();
        Choices.push_back(Choice::Base("Beg Lucie to do something to save you", 363));
        Choices.push_back(Choice::Base("Fight on", 351));

        Controls = Story::Controls::STANDARD;
    }
};

class Story374 : public Story::Base
{
public:
    Story374()
    {
        ID = 374;

        Image = "images/lepers.png";

        Text = "You manage to hide in a doorway just as a band of lepers turns into sight. They are coming on up the street in a slow-moving throng, a parody of a dance troupe that shuffies from house to house striking guilt into the hearts of those who see it. They are starving and emaciated, many have lost fingers, toes and their noses. Some are missing a foot or a hand. A few are heaving themselves along on trolleys, with no legs left on which to walk. They have escaped from the sanatorium. No one has fed them for days.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave your hiding place and lead them to safety", 395));
        Choices.push_back(Choice::Base("Let them wander on until Hate swallows them into its qmvermg grey-green maw", 404));

        Controls = Story::Controls::STANDARD;
    }
};

class Story375 : public Story::Base
{
public:
    Story375()
    {
        ID = 375;

        Text = "You have the JEWEL OF SUNSET FIRE with which to focus the rays of the setting sun on the monster but you have no way of tethering Hate so that it must suffer the searing agony of the JEWEL until death wracks it. You stand alone upon the parapet of the Bargello, focusing the JEWEL, and Hate writhes in anguish. But the monster raises itself up, towering above you and then drops like an avalanche, crushing you into the midst of a mound of rubble that was once the strongest building in the city. The monster carries all before it. You lose the SWORD inside its flesh and soon you are all partners in the eternal orgy of despair. The city crumbles and is lost for ever beneath the waves. Hate has completed its work.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story376 : public Story::Base
{
public:
    Story376()
    {
        ID = 376;

        Text = "You pass a troubled night but an undisturbed one. You awake feeling heavy headed but you RECOVER 2 Life Points.\n\nThis place is cold and, looking at the back wall, you see traces of translucent purple slime. Was a demon questing here in the night for your defenceless soul? Perhaps the very demon that embodies Hate itself?\n\nIt is clearly not safe here, however, and it is time to find a new hideaway. You set out for Bumble Row, as you know that most of the shopkeepers there shut up shop long ago and there should be plenty of hideaways to choose from.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 2);
    }

    int Continue(Character::Base &player) { return 315; }
};

class Story377 : public Story::Base
{
public:
    Story377()
    {
        ID = 377;

        Text = "You have taken the wrong course. You have never seen a man so skilled with a sword as the tall pale-faced Tyutchev. He is fast and strong too, and he cuts you down in a welter of blood and iron. Lucie looks on mournfully as he delivers the coup de grace, severing your head from your shoulders. There is no one left to save the Judain now. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story378 : public Story::Base
{
public:
    Story378()
    {
        ID = 378;

        Text = "The magic works. The guards are feeling calm and tranquil now, completely unmoved by the horrors which have overtaken Godorno. They feel similarly unmoved about the idea of opening the gate to you or doing anything, for that matter. You will have to try another way.";

        Choices.clear();
        Choices.push_back(Choice::Base("Wait until the spell wears off and offer them gold", 206));
        Choices.push_back(Choice::Base("Try magic again in an attempt to terrorize them", 341));
        Choices.push_back(Choice::Base("Make friends with them", 361));
        Choices.push_back(Choice::Base("Return to your hideout now: bribes or magic will get you no further", 20));

        Controls = Story::Controls::STANDARD;
    }
};

class Story379 : public Story::Base
{
public:
    Story379()
    {
        ID = 379;

        Text = "The Judain look at you in horror. They are not suicide troops, nor religious zealots anxious to meet their maker. \"You have gone mad!\" shouts Caisphas. \"We follow you no more.\"\n\nWith that they start to flee the barricade and go back into hiding. You are left alone to face your foe. Dusk begins to fill the streets. Only the decaying spires of the cathedrals still catch the golden glint of daylight. This may be the last sunset you will ever see, as the great rolling bulk of Hate comes slithering through the canals and streets towards you.\n\nHate extrudes a tentacle. In the pits of its green eyes, a flicker of intelligence shows. It recognizes you as its foe. A beam of shimmering mauve light shines down on you as the monster unleashes its magic.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORDS(player, {Codeword::Type::VENEFIX}))
        {
            return 399;
        }
        else
        {
            return 274;
        }
    }
};

class Story380 : public Story::Base
{
public:
    Story380()
    {
        ID = 380;

        Text = "The old woman is looking at you shrewdly. She is dressed in rags and down-at-heels clogs. She probably comes to the city every second or third day to sell her eggs. She has the look of one who has outlived her children.";

        Choices.clear();
        Choices.push_back(Choice::Base("Confide in her that you are in fact a Judain", 275));
        Choices.push_back(Choice::Base("Try to lose her in the streets and hope she does you no harm", 286));

        Controls = Story::Controls::STANDARD;
    }
};

class Story381 : public Story::Base
{
public:
    Story381()
    {
        ID = 381;

        Text = "With a word of power and a clap of your hands you bring forth a cloud of poisonous gas which has the guards and Lucie retching helplessly while you make your getaway. You have found out the hard way that Lucie is not to be trusted. You could spend time trying to track her down and perhaps even murder her but she knows the back ways and dives of the city even better than you. You will never find her. And now that you know her for a traitor she is unlikely to trouble you again. After all, she has no reason to hate you, does she?\n\nYou make your way back into hiding trying not to think about what a fool the young strumpet made of you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story382 : public Story::Base
{
public:
    Story382()
    {
        ID = 382;

        Text = "Rulership is a good choice under these circumstances, as you have a clearly identified leader who can be forced to give your commands. He is a bored gate guard to boot and falls easily under the sway of your magic. You order him to have you let through while the old woman is detained and searched for weapons. You leave the guards behind and enter the once bustling city proper.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 300; }
};

class Story383 : public Story::Base
{
public:
    Story383()
    {
        ID = 383;

        Text = "It is a good job you took the time to bandage your wound. The dripping blood would have left a trail which would allow your enemies to locate you in spite of all your sorcery.\n\nYou RECOVER 1 Life Point.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 1);
    }

    int Continue(Character::Base &player) { return 300; }
};

class Story384 : public Story::Base
{
public:
    Story384()
    {
        ID = 384;

        Text = "Tyutchev orders the landlord to throw you a sword. You catch it; record it among your possessions. As you stand ready, trying to get the feel of your new weapon, Tyutchev draws his own sword over his shoulder in a single fluid motion full of grace and power. There is a merciless glint in his pale blue eyes as he advances steadily towards you. Lucie looks on with keen interest.";

        Choices.clear();
        Choices.push_back(Choice::Base("Rush past him and out of the inn", 199));
        Choices.push_back(Choice::Base("Stay and fight Tyutchev", 328));

        Controls = Story::Controls::STANDARD;
    }
};

class Story385 : public Story::Base
{
public:
    Story385()
    {
        ID = 385;

        Text = "You walk quickly down a side street, taking every first turn you come to and skirting round Greenbark Plaza. You can hear the bell of the town crier and then hear him making a proclamation. The crowd that has gathered to hear the Overlord's commandments starts to shout excitedly. You can't make out their cries, but they remind you of a pack of hounds baying for blood. Your spine tingles at the sound and you hurry away. Rounding a corner you see three Judain, unknown to you, running from the plaza. The mob is in full cry behind them.\n\nSeeing a derelict villa nearby you push through the gate to hide in the overgrown garden. Listening to the bloodcurdling yells of a mob that seems to be rampaging back and forth across the city you decide the time has come to leave Godorno.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave Godorno by the usual means, through the main gate to the trade road", 53));
        Choices.push_back(Choice::Base("Try to slip from the city unseen", 70));

        Controls = Story::Controls::STANDARD;
    }
};

class Story386 : public Story::Base
{
public:
    std::string PreText = "";

    Story386()
    {
        ID = 386;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Cloudswept moonlight washes the streets of Godorno, turning the dirty cobblestones and narrow cramped houses into eerie sculptures of silver. Rats scurry off into the shadows as you pass. Off in another street, you hear a drunkard singing bawdy songs only to fall suddenly silent as someone empties the contents of their bedpan over him.\n\nThe jeweller's house lies just ahead. Looking to left and right, you slink across the street and gain entry by forcing the door. You pray that no one heard the sound of splintering timber as the door frame gave way. There is no point in searching the ground floor; you expect to find the diamond locked away somewhere upstairs. Sure enough, the first floor on the landing opens onto a store room with a locked chest in the corner. You tiptoe over and bend over this, fingers twitching with greed as you pick it up, triumph spreading a smile across your face. Who would have thought it would be so easy?\n\nA lantern is suddenly unshuttered behind you. The smile disappears. You whirl around and find yourself face to face with three of the Overlord's soldiers. \"Drop that and stand where you are, villain!\" says one with a snarl.";

        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            if (!Character::VERIFY_ITEMS(player, {Item::Type::ELFIN_BOOTS}))
            {
                PreText += "\n\nWithout [AGILITY], you will have to fight.";
            }
            else
            {
                Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 406, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
                Choices.push_back(Choice::Base("Fight", 283));
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 406; }
};

class Story387 : public Story::Base
{
public:
    Story387()
    {
        ID = 387;

        Text = "You walk quickly down a side street, taking every first turn you come to and skirting round Greenbark Plaza. You can hear the bell of the town crier and then hear him making a proclamation. The crowd that has gathered to hear the Overlord's commandments starts to shout excitedly. You can't make out their cries, but they remind you of a pack of hounds baying for blood. Your spine tingles at the sound and you hurry away. Rounding a corner you see three Judain, unknown to you, running from the plaza. The mob is in full cry behind them.\n\nSeeing a derelict villa nearby you push through the gate to hide in the overgrown garden. Listening to the bloodcurdling yells of a mob that seems to be rampaging back and forth across the city you decide the time has come to leave Godorno.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go back to her and comfort her", 273));
        Choices.push_back(Choice::Base("Harden your heart and go on your way", 298));

        Controls = Story::Controls::STANDARD;
    }
};

class Story388 : public Story::Base
{
public:
    Story388()
    {
        ID = 388;

        Text = "Speaking a few magical riddle-me-rees you rub the AMULET and hold it up towards where Grond towers granite-grey against the violet twilighnky. It burns red and hot, but then what did you expect? Its function is to warn you of danger, after all. Only a fool would venture into Grond alone.\n\nYou cancel the charm and the stone grows cold once more. You catch Lucie eyeing the AMULET covetously. \"Of course,\" you say in a casual tone, \"this AMULET is magically attuned to my life force. It will not work for anyone else.\" You dart a look at Lucie to see if she believes you. \"In fact, it will explode in the face of anyone trying to steal it from me. What do you think of that?\"\n\n\"I think it sounds as if any thief would get a nasty surprise if they tried to steal from you.\"\n\n\"That's right, they would.\" Satisfied you have put Lucie off the idea of stealing your magical AMULET you tell her to lead on.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 354; }
};

class Story389 : public Story::Base
{
public:
    Story389()
    {
        ID = 389;

        Text = "You dart in to attack the first of the Jade Warriors. You fight well; your sword is an arcing blaze of light, but though it rings loudly against the jade bodies of your adversaries they are not dinted. Their heavy blows break down your guard and their blades are terribly sharp, as you find to your cost when one bites into your shoulder.\n\nYou LOSE 2 Life Points.";

        Choices.clear();
        Choices.push_back(Choice::Base("Attempt [UNARMED COMBAT] with the champions of the Megiddo dynasty", 296, Skill::Type::UNARMED_COMBAT));
        Choices.push_back(Choice::Base("Flee", 16));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }
};

class Story390 : public Story::Base
{
public:
    Story390()
    {
        ID = 390;

        Text = "This is a very confined space in which to let loose the awful spell of the Miasma. The billowing cloud of gas which erupts fills the Inn of the Inner Temple and all inside fall retching_ helplessly to the floor. You have taken the precaution of winding a damp scarf about your mouth and nose and can still breathe. Grabbing Skakshi you drag him out.\n\n\"You, Skakshi, will take me to meet your guildmaster, Melmelo. I have a proposition for his ears only.\"\n\n\"I'll -- ack! -- do anything you say... Just release me -- cough! -- from this wracking spell!\"\n\nSkakshi is only too glad to do your bidding as long as he is released from the pit of gas the Inn of the Inner Temple has become.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 181; }
};

class Story391 : public Story::Base
{
public:
    Story391()
    {
        ID = 391;

        Text = "Amateur rogues often assume that speed is the important thing in a job like this. Long experience has taught you better. The key to success is to take your time. Luckily patience is your only virtue, so you have had plenty of opportunity to practise it over the years.\n\nCreeping low, pressed hard back into the dingy shadows by the wainscoting, you inch round the room. All the while the three guards go on with their game. Though your eyes remain firmly fixed on the treasure-box you listen to the hisses of breath and grunts and curses that indicate when someone has lost a throw, to the gulps of watered wine taken during respites in the game, to the rattle of dice and the slap of copper coins on the wooden tabletop. But still the guards remain oblivious of the rogue at their backs who is intent on whisking away a greater fortune in this one night than they will win or lose in their whole lives.\n\nYou reach the treasure chest at last and allow yourself a backward glance. One of the guards is now slumped dozily across the table. Another fingers the dice idly, tired of squandering his pay. The third grunts and begins to clean his fingernails with a dagger. \"How much longer are we on duty for?\" he asks.\n\n\"The next watch ought to be here in a few minutes to relieve us,\" replies the man with the dice.\n\nNow you know you must work fast. When the next watch takes over they are bound to check the treasure chest. You can try picking the lock. On the other hand you could just take the chest with you and open it later. It isn't very large, but with any load under your arm you would find it harder to move silently.";

        Choices.clear();
        Choices.push_back(Choice::Base("Pick the lock", 217));
        Choices.push_back(Choice::Base("Open it later", 253));

        Controls = Story::Controls::STANDARD;
    }
};

class Story392 : public Story::Base
{
public:
    Story392()
    {
        ID = 392;

        Text = "You must try to bind the monster long enough to find a way to destroy it.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::ROGUERY, Skill::Type::CUNNING}))
        {
            return 89;
        }
        else
        {
            return 224;
        }
    }
};

class Story393 : public Story::Base
{
public:
    Story393()
    {
        ID = 393;

        Text = "If only you had taken the time to bandage your wound and staunch the flow of blood. The leg of your breeches is soaked and you are leaving red telltale footprints behind as you try to sidle past the line of guard. They could follow you as easily as if you had left chalk arrows on the ground. One of them sees the blood, shouts and points in your direction. They all fire their bows at you. It is a mercifully sudden death. There is no one left now to save the Judain. They will all perish and be wiped from the face of the earth.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story394 : public Story::Base
{
public:
    Story394()
    {
        ID = 394;

        Text = "A heavy footstep sounds in the open doorway. \"Hey, lads, we've been suckered!\" shouts the guard standing there. \"The thief is right here all along!\"\n\nAs you turn, you can already hear the other guards racing back to trap you.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            Choices.push_back(Choice::Base("(AGILITY) Use the ELFIN BOOTS", 406, Choice::Type::LOSE_ITEMS, {Item::ELFIN_BOOTS}));
            Choices.push_back(Choice::Base("Otherwise", 283));
        }
    }

    int Continue(Character::Base &player) { return 406; }
};

class Story395 : public Story::Base
{
public:
    Story395()
    {
        ID = 395;

        Text = "This motley crew would follow you anywhere. They shuffie along in your wake, calling out feebly for food and medicine, though there is no magic or medicine that can restore these disfigured unfortunates to health. You are not bothered by city guardsmen, nor thieves and cut-throats while surrounded by your crowd oflepers. The sweet putrefying smell that seeps from their bandages is an antidote to the stench of death that pervades the city.\n\nYou must decide where to lead your motley band.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take them to the prison fortress of Grond, in the hope of using them to set the prisoners free", 194));
        Choices.push_back(Choice::Base("Have them sheltered by the cells of the Judain resistance", 359));

        Controls = Story::Controls::STANDARD;
    }
};

class Story396 : public Story::Base
{
public:
    Story396()
    {
        ID = 396;

        Text = "All you have in the way of weaponry to defeat Hate is the Jade Warrior's sword. It is a potent magical weapon but it is perhaps a forlorn hope that it will allow you to vanquish the monster. Still, it is all the hope you have. You lead your doomed people in a final stand against Hate. The monster carries all before it. You lose the sword inside its flesh and soon you are all partners in the eternal orgy of despair. The city crumbles and is lost for ever beneath the waves. Hate has completed its work.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story397 : public Story::Base
{
public:
    Story397()
    {
        ID = 397;

        Text = "\"Slaughter is a fine end in itself. No end is finer than death and destruction. Slaughter is the reason the god Anarchil put me on this world.\" He is smiling as he says it but he really means what he is saying. Tyutchev is a very dangerous lunatic. You have never heard of his god but you can rest assured it is a vicious and barbaric cult that reveres him.\n\nHe turns to Lucie. \"I leave you to talk with this Judain. But you may call on me this evening.\"\n\n\"Will we be alone?\" she asks.\n\n\"Yes. Cassandra took ship for Aleppo on the rising tide.\"\n\nLucie looks pleased. \"Till tonight, then.\"\n\nTyutchev quits the tavern, leaving you alone with Lucie.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 403; }
};

class Story398 : public Story::Base
{
public:
    Story398()
    {
        ID = 398;

        Text = "You offer one of the gate guards money, but he just says, \"It's more than my life's worth to open the gate when the bell tolls. You'd best come with me...\"\n\nHe lays a calloused hand on your shoulder, then turns to call to his fellow guards: \"Got one here -- a Judain! Tried to bribe me.\"\n\nHe steps back as if to let you go but it is only to move away from you, the target of the other guards' crossbows. Your body is peppered with crossbow bolts and you fall to the ground.\n\n\"That's one less of those scum,\" says another guard as you die.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story399 : public Story::Base
{
public:
    Story399()
    {
        ID = 399;

        Image = "images/filler3.png";

        Text = "You scream in agony as the light seeps into your flesh. A moment later, you are horrified to see purple polyps sprouting from your chest. Hate has awakened the evil in your own heart, forming a cancer that gnaws at you from within.\n\nYou LOSE 5 Life Points.";

        Bye = "You are determined to destroy the monster before it can subvert you to its cause.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -5);
    }

    int Continue(Character::Base &player) { return 274; }
};

class Story400 : public Story::Base
{
public:
    Story400()
    {
        ID = 400;

        Text = "You disappear through the jaws of Hate. As it absorbs you into its being, it begins to be wracked by spasms of pain. It cannot tolerate the presence of goodness within its very being. Shuddering, Hate tries to flee back to the sewers, but it is rotting away by the moment. The people come out of hiding to watch as it dwindles. They take up rocks and sticks and pelt the dying monster. The Overlord's men stand shoulder to shoulder with Judain resistance fighters, smiting their common enemy. At last Hate gives a forlorn screech and dies, turning to dust which is carried off by the wind.\n\nYou lost your life, but you died a martyr's death, bringing salvation to your people and your city.";

        Type = Story::Type::MARTYR_DEATH;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story401 : public Story::Base
{
public:
    Story401()
    {
        ID = 401;

        Image = "images/diamond.png";

        Text = "Hate thrashes wildly and a tidal wave erupts from the canal, smashing against the Bargello keep. But it is the monster's death throes. Just as the sun sinks beneath the horizon, the JEWEL glows white hot and the ruby light becomes a coruscating fan of many-coloured motes that disintegrate the vile purple flesh. The monster falls and makes its own grave as the catacombs open up beneath its bulk, welcoming it to its final rest. The sun sets and the city is quiet.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 416; }
};

class Story402 : public Story::Base
{
public:
    Story402()
    {
        ID = 402;

        Text = "Lucie smiles as sweetly at Mameluke but Mameluke greets her gruffiy, disdaining to hide \"his dislike of the girl.\n\n\"I need strong and trusty Mameluke here as bodyguard if I am to go to Grand and get you smuggled into the prison,\" she says. \"Will you be my protector, Mameluke?\"\n\n\"If I must -- though I'd rather stick my head inside a lion's jaws.\"\n\n\"It's settled, then; come with me.\"\n\nLucie leads you by cunning back ways towards the prison fortress.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 354; }
};

class Story403 : public Story::Base
{
public:
    Story403()
    {
        ID = 403;

        Text = "You sit down beside Lucie, oblivious of the other vermin drinking in this slop hole. \"Why do people like him waste time in a place like this? I mean, I don't want to offend, but there must be girls like you in other cities north of the sea.\"\n\n\"Ah, but in Godorno everyone is desperate. Tyutchev likes desperate people.\"\n\n\"Are you desperate, Lucie?\"\n\n\"Aren't you, to survive?\"\n\nYou change the subject. \"I've never seen a man wield a sword like that before. I didn't know it was possible. He fights like a demigod.\"\n\n\"And he thinks he is demigod, too,\" says Lucie with an arch smile. \"It really gripes him when people don't treat him that way. And now you're going to ask what's a nice girl like me --\"\n\n\"-- doing with a murderous bastard like that?\"\n\n\"He amuses me.\"\n\n\"What about his woman friend, the one called Cassandra?\"\n\nLucie shivers. \"She'd like to kill me, that one. She's killed enough men in her time. Soon as she's tired of them she fires them with cold steel. I'll make a bargain with you, Judain. You kill her for me and I'll help you save your beloved people. I know I only look like a little sweetmeat of a girl, but I can do it, with people like Tyutchev on my side.\"\n\n\"He won't thank us for killing Cassandra.\"\n\n\"What's the matter, Judain? Are you frightened?\"\n\nYou coolly point out that Tyutchev said Cassandra had taken ship to Aleppo.\n\nLucie sneers prettily. \"She'll be back sooner or later.\"\n\n\"It's no business of mine,\" you reply.\n\nLucie looks annoyed for a moment, then turns a bright smile on you. \"You're quite the hero of your people, and I like heroes. You can call on me if you need me and I'll give you a reward for your heroism.\"\n\n\"Thank you, Lucie. All help is appreciated in these troubled days.\"\n\nBidding her farewell, you leave the inn.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 199; }
};

class Story404 : public Story::Base
{
public:
    Story404()
    {
        ID = 404;

        Text = "Who would have thought that lepers could have such a strong will to live? They wander unknowing onto a glassy mauve grey surface at the end of the street and fall into the morass of Hate. Their struggles to be free are every bit as mighty as the fit young people of Godorno who have also been summoned to the eternal embrace. With their harrowing cries still vivid in your memory, you return to Bumble Row.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 20; }
};

class Story405 : public Story::Base
{
public:
    Story405()
    {
        ID = 405;

        Text = "There is no way out. The crossbows of the guards pepper your body with quarrels and you fall dead to the cobbled street in a pool of blood. The old egg-seller steals your purse and goes on her way. There is no one left now to save the Judain. Hate will subdue all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story406 : public Story::Base
{
public:
    Story406()
    {
        ID = 406;

        Text = "\"You want this?\" you cry. \"Then catch!\"\n\nSo saying, you throw the treasure-box. It catches one of the guards with a resounding crack and he reels back onto the landing, clutching his nose, as the others close in. You dart back, seize the edge of the carpet on which they're standing, and give it a sharp tug. The breath comes out of their lungs in sharp surprised grunts as they lose their footing and tumble over backwards. Using their stomachs as a springboard, you bound over to the doorway and snatch up the box. The other guard has started to recover his wits. Despite the blood streaming from his nose, he advances along the landing towards you with an angry snarl.\n\nYou see no gain in fighting him. A few swift steps carry you to the window at the end of the landing, where you execute an agile dive, twisting in midair to land softly in a cart which you noticed earlier. The guards crowd to the window. \"Come back here, you cur!\" growls the one with the bloody nose.\n\n\"Sirrah,\" you reply with a courtly boW, \"I regret I must decline your gracious request. Adieu!\" And with that you dart off down the street, sniggering at the angry shouts which soon recede into the distance far behind you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 358; }
};

class Story407 : public Story::Base
{
public:
    Story407()
    {
        ID = 407;

        Text = "Though your instinct is to trust Lucie who seems open and without guile you know it makes no sense to agree to a meeting with a stranger, particularly in a city like Godorno where your people are the victims of genocide. You demand to be told who it is who can help you in your struggle to save your people.\n\n\"He made me promise to keep his identity secret, until you meet. He said he could help you only if you are able to trust. So many good people have fallen into the clutches of the coils of Hate. Trust me.\"\n\n\"Is he Judain?\"\n\n\"No, not Judain. Come, we are almost there.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Follow Lucie", 411));
        Choices.push_back(Choice::Base("Change your mind and tell her you are going back to your hideout", 324));

        Controls = Story::Controls::STANDARD;
    }
};

class Story408 : public Story::Base
{
public:
    Story408()
    {
        ID = 408;

        Text = "Your leadership has so inspired your people that they are prepared to man the barricade against Hate itself. They pelt it with missiles and arrows and hack at it with swords, cleavers and boathooks but all to no avail. Hate dines well today as it rolls over the barricade crushing everything there to a pulp. You could not desert your people now and you too are flattened and drawn in to the eternal orgy of despair. Hate will conquer all.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story409 : public Story::Base
{
public:
    Story409()
    {
        ID = 409;

        Text = "The catacombs under the palace are dark and eerie. There is an evil resonance here, as if unspeakable acts had been carried out far from the light of day. You find your way carefully forward until you reach the cellar stairs that lead up into the palace.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 279; }
};

class Story410 : public Story::Base
{
public:
    Story410()
    {
        ID = 410;

        Text = "Tyutchev seems to be a bit of a rogue as well as a swordsman. He moves stealthily and shows all the tricks of a footpad in moving through the dangerous streets. He may well be leading you into a trap, for you are being taken deeper and deeper into the foreigners' quarter and soon you will be up against the town wall, where you can be cornered. You decide to let him go and quit the foreigners' quarter as fast as you can.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 160; }
};

class Story411 : public Story::Base
{
public:
    Story411()
    {
        ID = 411;

        Text = "Of course you trust lovely little Lucie. She takes your hand and leads you into a quiet courtyard that gives out onto the upper end of Fortuny Street. You walk through an arboretum of magnolia trees and hanging baskets of weeping lilies and find yourself surrounded by the Overlord's men with crossbows pointed at your chest. Lucie smiles a wicked little smile.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] This is a good moment to turn invisible", 317, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[SPELLS] Send a fog of poison gas towards them", 381, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("You have no choice but to surrender", 196));

        Controls = Story::Controls::STANDARD;
    }
};

class Story412 : public Story::Base
{
public:
    Story412()
    {
        ID = 412;

        Text = "Mameluke comes up with a plan. \"No need to brave the horrors of the catacombs...\" He will distract the guards while you slip past into the fortress. You both scurry through the back alleys to the prison. At first it seems as though the plan will fail. When he hammers on the great gates of Grond there is no reply.\n\nHe hammers on the door again, saying he is the Overlord's messenger. Fortunately, the Overlord does use a Tartar like Mameluke as a courier. At length there is a great clanking and grinding and the gates start to inch apart. It is a great labour to open them with the iron machinery forged by smiths from the mountains and he calls out hearty thanks, but there is no one to answer his call. It is as if the gate was opened by ghosts. The sweet cloying smell of crushed roses and honeysuckle lingers here. Something is terribly wrong. You decide not to risk Mameluke's life any further and step inside the prison fortress alone, despite the Tartar's protestations.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 413; }
};

class Story413 : public Story::Base
{
public:
    Story413()
    {
        ID = 413;

        Text = "The towngate at Grand is a ten foot thick wall abutting a battlemented and turreted gatehouse. As the gates creak open you look into the bleak eastern courtyard. There is silence for a moment as you look at the grim grey stones that have witnessed the trials and tortures of so many. For fifteen hundred years Grand has stood at the rivermouth. Additions made in a new style every century or two, always in the same sombre hard grey stone, give it a chaotic air.\n\nFor centuries the prison fortress has struck terror into the hearts of the good burghers of Godorno. Its architect, Falsaphio the Gifted, was walled in above the gatehouse keystone because the prison had cost more to build than he had promised. You are standing beneath his remains.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 309; }
};

class Story414 : public Story::Base
{
public:
    Story414()
    {
        ID = 414;

        Text = "At last you manage to regain the safety of the underground cellars. There is a hole in the ceiling through which you can be spied on from the road unless you move back against the back wall, but the other Judain have taken all the best bolt holes. You will find a better hideaway in time.";

        Choices.clear();
        Choices.push_back(Choice::Base("Drag the palliasse to the back where you cannot be seen through the hole in the roof", 347));
        Choices.push_back(Choice::Base("Sleep on the street side near the hole", 376));

        Controls = Story::Controls::STANDARD;
    }
};

class Story415 : public Story::Base
{
public:
    Story415()
    {
        ID = 415;

        Text = "When the captain of the Eastgate at Grond sees how much gold you have brought him his eyes nearly pop out of his head. He hands you a huge bunch of keys on a belt and directs you by a circuitous route to the torture chambers. There are no other guards to be seen. He must have given orders that are keeping them busy. By the time you find the torture chambers, deep below the towers of the Great Keep, the captain of the guard is long gone, knowing full well what his grisly fate would be if he should be caught by those he has tortured.\n\nYou PAID 500 gleenars as BRIBE.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_MONEY(player, -500);
    }

    int Continue(Character::Base &player) { return 413; }
};

class Story416 : public Story::Base
{
public:
    Story416()
    {
        ID = 416;

        Text = "Then there is a murmuring from the catacombs: a sound that grows and swells from a hum to a roar. The lost souls are free once more and they climb into the streets to hail you as their saviour. You are a hero and you will be feted for a hundred days. Now is the time for the banquet at the Overlord's palace that you have promised your people. Together you will rebuild Godorno and make it once more thejewel of the east. You are carried aloft to the palace and set on the throne despite all your protestations. The city is yours. At last the Judain need have no fear.";

        Type = Story::Type::GOOD;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

auto prologue = Prologue();
auto story001 = Story001();
auto story002 = Story002();
auto story003 = Story003();
auto story004 = Story004();
auto story005 = Story005();
auto story006 = Story006();
auto story007 = Story007();
auto story008 = Story008();
auto story009 = Story009();
auto story010 = Story010();
auto story011 = Story011();
auto story012 = Story012();
auto story013 = Story013();
auto story014 = Story014();
auto story015 = Story015();
auto story016 = Story016();
auto story017 = Story017();
auto story018 = Story018();
auto story019 = Story019();
auto story020 = Story020();
auto story021 = Story021();
auto story022 = Story022();
auto story023 = Story023();
auto story024 = Story024();
auto story025 = Story025();
auto story026 = Story026();
auto story027 = Story027();
auto story028 = Story028();
auto story029 = Story029();
auto story030 = Story030();
auto story031 = Story031();
auto story032 = Story032();
auto story033 = Story033();
auto story034 = Story034();
auto story035 = Story035();
auto story036 = Story036();
auto story037 = Story037();
auto story038 = Story038();
auto story039 = Story039();
auto story040 = Story040();
auto story041 = Story041();
auto story042 = Story042();
auto story043 = Story043();
auto story044 = Story044();
auto story045 = Story045();
auto story046 = Story046();
auto story047 = Story047();
auto story048 = Story048();
auto story049 = Story049();
auto story050 = Story050();
auto story051 = Story051();
auto story052 = Story052();
auto story053 = Story053();
auto story054 = Story054();
auto story055 = Story055();
auto story056 = Story056();
auto story057 = Story057();
auto story058 = Story058();
auto story059 = Story059();
auto story060 = Story060();
auto story061 = Story061();
auto story062 = Story062();
auto story063 = Story063();
auto story064 = Story064();
auto story065 = Story065();
auto story066 = Story066();
auto story067 = Story067();
auto story068 = Story068();
auto story069 = Story069();
auto story070 = Story070();
auto story071 = Story071();
auto story072 = Story072();
auto story073 = Story073();
auto story074 = Story074();
auto story075 = Story075();
auto story076 = Story076();
auto story077 = Story077();
auto story078 = Story078();
auto story079 = Story079();
auto story080 = Story080();
auto story081 = Story081();
auto story082 = Story082();
auto story083 = Story083();
auto story084 = Story084();
auto story085 = Story085();
auto story086 = Story086();
auto story087 = Story087();
auto story088 = Story088();
auto story089 = Story089();
auto story090 = Story090();
auto story091 = Story091();
auto story092 = Story092();
auto story093 = Story093();
auto story094 = Story094();
auto story095 = Story095();
auto story096 = Story096();
auto story097 = Story097();
auto story098 = Story098();
auto story099 = Story099();
auto story100 = Story100();
auto story101 = Story101();
auto story102 = Story102();
auto story103 = Story103();
auto story104 = Story104();
auto story105 = Story105();
auto story106 = Story106();
auto story107 = Story107();
auto story108 = Story108();
auto story109 = Story109();
auto story110 = Story110();
auto story111 = Story111();
auto story112 = Story112();
auto story113 = Story113();
auto story114 = Story114();
auto story115 = Story115();
auto story116 = Story116();
auto story117 = Story117();
auto story118 = Story118();
auto story119 = Story119();
auto story120 = Story120();
auto story121 = Story121();
auto story122 = Story122();
auto story123 = Story123();
auto story124 = Story124();
auto story125 = Story125();
auto story126 = Story126();
auto story127 = Story127();
auto story128 = Story128();
auto story129 = Story129();
auto story130 = Story130();
auto story131 = Story131();
auto story132 = Story132();
auto story133 = Story133();
auto story134 = Story134();
auto story135 = Story135();
auto story136 = Story136();
auto story137 = Story137();
auto story138 = Story138();
auto story139 = Story139();
auto story140 = Story140();
auto story141 = Story141();
auto story142 = Story142();
auto story143 = Story143();
auto story144 = Story144();
auto story145 = Story145();
auto story146 = Story146();
auto story147 = Story147();
auto story148 = Story148();
auto story149 = Story149();
auto story150 = Story150();
auto story151 = Story151();
auto story152 = Story152();
auto story153 = Story153();
auto story154 = Story154();
auto story155 = Story155();
auto story156 = Story156();
auto story157 = Story157();
auto story158 = Story158();
auto story159 = Story159();
auto story160 = Story160();
auto story161 = Story161();
auto story162 = Story162();
auto story163 = Story163();
auto story164 = Story164();
auto story165 = Story165();
auto story166 = Story166();
auto story167 = Story167();
auto story168 = Story168();
auto story169 = Story169();
auto story170 = Story170();
auto story171 = Story171();
auto story172 = Story172();
auto story173 = Story173();
auto story174 = Story174();
auto story175 = Story175();
auto story176 = Story176();
auto story177 = Story177();
auto story178 = Story178();
auto story179 = Story179();
auto story180 = Story180();
auto story181 = Story181();
auto story182 = Story182();
auto story183 = Story183();
auto story184 = Story184();
auto story185 = Story185();
auto story186 = Story186();
auto story187 = Story187();
auto story188 = Story188();
auto story189 = Story189();
auto story190 = Story190();
auto story191 = Story191();
auto story192 = Story192();
auto story193 = Story193();
auto story194 = Story194();
auto story195 = Story195();
auto story196 = Story196();
auto story197 = Story197();
auto story198 = Story198();
auto story199 = Story199();
auto story200 = Story200();
auto story201 = Story201();
auto story202 = Story202();
auto story203 = Story203();
auto story204 = Story204();
auto story205 = Story205();
auto story206 = Story206();
auto story207 = Story207();
auto story208 = Story208();
auto story209 = Story209();
auto story210 = Story210();
auto story211 = Story211();
auto story212 = Story212();
auto story213 = Story213();
auto story214 = Story214();
auto story215 = Story215();
auto story216 = Story216();
auto story217 = Story217();
auto story218 = Story218();
auto story219 = Story219();
auto story220 = Story220();
auto story221 = Story221();
auto story222 = Story222();
auto story223 = Story223();
auto story224 = Story224();
auto story225 = Story225();
auto story226 = Story226();
auto story227 = Story227();
auto story228 = Story228();
auto story229 = Story229();
auto story230 = Story230();
auto story231 = Story231();
auto story232 = Story232();
auto story233 = Story233();
auto story234 = Story234();
auto story235 = Story235();
auto story236 = Story236();
auto story237 = Story237();
auto story238 = Story238();
auto story239 = Story239();
auto story240 = Story240();
auto story241 = Story241();
auto story242 = Story242();
auto story243 = Story243();
auto story244 = Story244();
auto story245 = Story245();
auto story246 = Story246();
auto story247 = Story247();
auto story248 = Story248();
auto story249 = Story249();
auto story250 = Story250();
auto story251 = Story251();
auto story252 = Story252();
auto story253 = Story253();
auto story254 = Story254();
auto story255 = Story255();
auto story256 = Story256();
auto story257 = Story257();
auto story258 = Story258();
auto story259 = Story259();
auto story260 = Story260();
auto story261 = Story261();
auto story262 = Story262();
auto story263 = Story263();
auto story264 = Story264();
auto story265 = Story265();
auto story266 = Story266();
auto story267 = Story267();
auto story268 = Story268();
auto story269 = Story269();
auto story270 = Story270();
auto story271 = Story271();
auto story272 = Story272();
auto story273 = Story273();
auto story274 = Story274();
auto story275 = Story275();
auto story276 = Story276();
auto story277 = Story277();
auto story278 = Story278();
auto story279 = Story279();
auto story280 = Story280();
auto story281 = Story281();
auto story282 = Story282();
auto story283 = Story283();
auto story284 = Story284();
auto story285 = Story285();
auto story286 = Story286();
auto story287 = Story287();
auto story288 = Story288();
auto story289 = Story289();
auto story290 = Story290();
auto story291 = Story291();
auto story292 = Story292();
auto story293 = Story293();
auto story294 = Story294();
auto story295 = Story295();
auto story296 = Story296();
auto story297 = Story297();
auto story298 = Story298();
auto story299 = Story299();
auto story300 = Story300();
auto story301 = Story301();
auto story302 = Story302();
auto story303 = Story303();
auto story304 = Story304();
auto story305 = Story305();
auto story306 = Story306();
auto story307 = Story307();
auto story308 = Story308();
auto story309 = Story309();
auto story310 = Story310();
auto story311 = Story311();
auto story312 = Story312();
auto story313 = Story313();
auto story314 = Story314();
auto story315 = Story315();
auto story316 = Story316();
auto story317 = Story317();
auto story318 = Story318();
auto story319 = Story319();
auto story320 = Story320();
auto story321 = Story321();
auto story322 = Story322();
auto story323 = Story323();
auto story324 = Story324();
auto story325 = Story325();
auto story326 = Story326();
auto story327 = Story327();
auto story328 = Story328();
auto story329 = Story329();
auto story330 = Story330();
auto story331 = Story331();
auto story332 = Story332();
auto story333 = Story333();
auto story334 = Story334();
auto story335 = Story335();
auto story336 = Story336();
auto story337 = Story337();
auto story338 = Story338();
auto story339 = Story339();
auto story340 = Story340();
auto story341 = Story341();
auto story342 = Story342();
auto story343 = Story343();
auto story344 = Story344();
auto story345 = Story345();
auto story346 = Story346();
auto story347 = Story347();
auto story348 = Story348();
auto story349 = Story349();
auto story350 = Story350();
auto story351 = Story351();
auto story352 = Story352();
auto story353 = Story353();
auto story354 = Story354();
auto story355 = Story355();
auto story356 = Story356();
auto story357 = Story357();
auto story358 = Story358();
auto story359 = Story359();
auto story360 = Story360();
auto story361 = Story361();
auto story362 = Story362();
auto story363 = Story363();
auto story364 = Story364();
auto story365 = Story365();
auto story366 = Story366();
auto story367 = Story367();
auto story368 = Story368();
auto story369 = Story369();
auto story370 = Story370();
auto story371 = Story371();
auto story372 = Story372();
auto story373 = Story373();
auto story374 = Story374();
auto story375 = Story375();
auto story376 = Story376();
auto story377 = Story377();
auto story378 = Story378();
auto story379 = Story379();
auto story380 = Story380();
auto story381 = Story381();
auto story382 = Story382();
auto story383 = Story383();
auto story384 = Story384();
auto story385 = Story385();
auto story386 = Story386();
auto story387 = Story387();
auto story388 = Story388();
auto story389 = Story389();
auto story390 = Story390();
auto story391 = Story391();
auto story392 = Story392();
auto story393 = Story393();
auto story394 = Story394();
auto story395 = Story395();
auto story396 = Story396();
auto story397 = Story397();
auto story398 = Story398();
auto story399 = Story399();
auto story400 = Story400();
auto story401 = Story401();
auto story402 = Story402();
auto story403 = Story403();
auto story404 = Story404();
auto story405 = Story405();
auto story406 = Story406();
auto story407 = Story407();
auto story408 = Story408();
auto story409 = Story409();
auto story410 = Story410();
auto story411 = Story411();
auto story412 = Story412();
auto story413 = Story413();
auto story414 = Story414();
auto story415 = Story415();
auto story416 = Story416();

void InitializeStories()
{
    Stories = {
        &prologue, &story001, &story002, &story003, &story004, &story005, &story006, &story007, &story008, &story009,
        &story010, &story011, &story012, &story013, &story014, &story015, &story016, &story017, &story018, &story019,
        &story020, &story021, &story022, &story023, &story024, &story025, &story026, &story027, &story028, &story029,
        &story030, &story031, &story032, &story033, &story034, &story035, &story036, &story037, &story038, &story039,
        &story040, &story041, &story042, &story043, &story044, &story045, &story046, &story047, &story048, &story049,
        &story050, &story051, &story052, &story053, &story054, &story055, &story056, &story057, &story058, &story059,
        &story060, &story061, &story062, &story063, &story064, &story065, &story066, &story067, &story068, &story069,
        &story070, &story071, &story072, &story073, &story074, &story075, &story076, &story077, &story078, &story079,
        &story080, &story081, &story082, &story083, &story084, &story085, &story086, &story087, &story088, &story089,
        &story090, &story091, &story092, &story093, &story094, &story095, &story096, &story097, &story098, &story099,
        &story100, &story101, &story102, &story103, &story104, &story105, &story106, &story107, &story108, &story109,
        &story110, &story111, &story112, &story113, &story114, &story115, &story116, &story117, &story118, &story119,
        &story120, &story121, &story122, &story123, &story124, &story125, &story126, &story127, &story128, &story129,
        &story130, &story131, &story132, &story133, &story134, &story135, &story136, &story137, &story138, &story139,
        &story140, &story141, &story142, &story143, &story144, &story145, &story146, &story147, &story148, &story149,
        &story150, &story151, &story152, &story153, &story154, &story155, &story156, &story157, &story158, &story159,
        &story160, &story161, &story162, &story163, &story164, &story165, &story166, &story167, &story168, &story169,
        &story170, &story171, &story172, &story173, &story174, &story175, &story176, &story177, &story178, &story179,
        &story180, &story181, &story182, &story183, &story184, &story185, &story186, &story187, &story188, &story189,
        &story190, &story191, &story192, &story193, &story194, &story195, &story196, &story197, &story198, &story199,
        &story200, &story201, &story202, &story203, &story204, &story205, &story206, &story207, &story208, &story209,
        &story210, &story211, &story212, &story213, &story214, &story215, &story216, &story217, &story218, &story219,
        &story220, &story221, &story222, &story223, &story224, &story225, &story226, &story227, &story228, &story229,
        &story230, &story231, &story232, &story233, &story234, &story235, &story236, &story237, &story238, &story239,
        &story240, &story241, &story242, &story243, &story244, &story245, &story246, &story247, &story248, &story249,
        &story250, &story251, &story252, &story253, &story254, &story255, &story256, &story257, &story258, &story259,
        &story260, &story261, &story262, &story263, &story264, &story265, &story266, &story267, &story268, &story269,
        &story270, &story271, &story272, &story273, &story274, &story275, &story276, &story277, &story278, &story279,
        &story280, &story281, &story282, &story283, &story284, &story285, &story286, &story287, &story288, &story289,
        &story290, &story291, &story292, &story293, &story294, &story295, &story296, &story297, &story298, &story299,
        &story300, &story301, &story302, &story303, &story304, &story305, &story306, &story307, &story308, &story309,
        &story310, &story311, &story312, &story313, &story314, &story315, &story316, &story317, &story318, &story319,
        &story320, &story321, &story322, &story323, &story324, &story325, &story326, &story327, &story328, &story329,
        &story330, &story331, &story332, &story333, &story334, &story335, &story336, &story337, &story338, &story339,
        &story340, &story341, &story342, &story343, &story344, &story345, &story346, &story347, &story348, &story349,
        &story350, &story351, &story352, &story353, &story354, &story355, &story356, &story357, &story358, &story359,
        &story360, &story361, &story362, &story363, &story364, &story365, &story366, &story367, &story368, &story369,
        &story370, &story371, &story372, &story373, &story374, &story375, &story376, &story377, &story378, &story379,
        &story380, &story381, &story382, &story383, &story384, &story385, &story386, &story387, &story388, &story389,
        &story390, &story391, &story392, &story393, &story394, &story395, &story396, &story397, &story398, &story399,
        &story400, &story401, &story402, &story403, &story404, &story405, &story406, &story407, &story408, &story409,
        &story410, &story411, &story412, &story413, &story414, &story415, &story416};
}

#endif