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

        Image = "images/vr-logo.png";

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

        Image = "images/filler3.png";

        Text = "Walk the streets you must, for there is no food and nothing to be gained from idling here in the hovel you call home. You push the rotten front door open gently. There is a wet cracking noise and it splinters, coming off its hinges. You jump past into Copper Street as it falls into the street and breaks. It is beyond repair.\n\nEven before you turn the corner of the narrow mired street a prowling thief, a sewer rat escaped from the fleet, is going into your home. Let him. You are carrying everything you own. He will find nothing but tick-ridden blankets and a leaking earthenware pot or two.\n\nAs you turn your back on the grey stone shacks of Copper Street a youth, gangling and pasty-faced, spits in your eye and calls out \"Judain scum.\" The boy is beneath not~ce. He sneers with his nose in the air, like the rich folk of the riverfront, but his sailcloth breeches are out at the knees. His father is probably a tanner or a tinker or some such.\n\nYour time in Godorno has taught you to ignore such insults.";

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

        Text = "As nightfall approaches and a thunderstorm brews, you leave the road to find shelter in a copse of trees. But you are destined to sleep under better than a canopy of leaves -- hidden among the trees is a dilapidated cottage by a well. The dwelling's solid, green-tiled roof alone will mean you'll not get wet tonight.\n\nThe well is an even more welcome sight; you have fled Godorno ill-prepared and have travelled most of the day without a single drink. Drawing water from the well, you drink deeply.\n\nOn entering the rude shelter, you find it is empty but largely clean, with no signs of recent habitation by men or animals. Making yourself as comfortable as you can on the hard-packed earth floor you settle down to sleep.\n\nWhen you awake in the morning, however, you feel strangely feverish. The trials of your journey might have been too much for you and perhaps you have sunstroke. Or did you dehydrate too much, and that refreshing drink come too late? There again, perhaps the water from the well is tainted, though to you it was as sweet as honeyed wine upon thetongue.\n\nSuch thoughts plague your mind as you sink deeper into delirium, restlessly tossing and turning on the cottage's floor. A kind of madness possesses you, and you are sure that several times you run out into the copse in search of food, grasping at and eating anything that seems remotely edible. How many days must you be gripped by the. coils of madness that threaten to destroy your mind and body?\n\nYou LOSE 2 Life Points.";

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

        Text = "The road leading up to Greenbank Plaza has been renamed the A venue of Skulls. At regular intervals posts have been erected from which iron cages swing. Inside the cages are executed Judain. Hundreds have been slain. The smell of rank corruption has drawn clouds of flies. Nearby you hear the clang of a bell and a dolorous voice calling, \"Bring out your dead. Bring out your dead.\"\n\nThe plague has struck Godorno like a ravaging scourge. No respecter of a man's station, it has carried off nobleman and beggar alike. The streets have not been swept for what must have been weeks.  Refuse is piling up in drifts in the wind. There is a blank look of despair on the faces of the people you pass and even the guards seem too preoccupied to notice a Judain. The sun is drawing the humours from the city like the fumes from a witch's kettle by the time you turn the corner into Copper Street.\n\nYou return to the hovel which you used to call home. You can use it as a base to see if you can contact some of your fellow Judain and learn what has taken place in the city. The old door has been broken up and used for firewood. There is nobody and nothing in the hovel -- but did you hear voices from beneath the trap door that leads to the hidden cellar?";

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

        Text = "\"You'll burn in hell for this, Judain scum, for all eternity. You'll join me here in the swamp of Hate. You'll rue the day you wouldn't offer a helping hand to an old soldier ...\"\n\nHe breaks off and moans in despair. His flesh is mottled horribly and a gaping wound on his neck seems to have the pus of Hate oozing into it rather than his own fluids leaking out. You could never describe the horror of seeing these lost souls in their degradation. All you can do is try to keep hold of your sanity. You close your ears to the sounds of torment and walk on.";

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
    std::string PreText = "";

    Story016()
    {
        ID = 16;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You turn tail and flee from the Jade Warriors, but on your way out you fall foul of a trap that stabs your thigh with a broken-off spear shaft.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYou pull the shaft out. The blood wells forth ominously; you are lucky it didn't sever an artery. You hobble back to your bolt-hole on Bumble Row and lie down to recuperate.";
        }

        Text = PreText.c_str();
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

void InitializeStories()
{
    Stories = {
        &prologue, &story001, &story002, &story003, &story004, &story005, &story006, &story007, &story008, &story009,
        &story010, &story011, &story012, &story013, &story014, &story015, &story016, &story017, &story018, &story019};
}

#endif