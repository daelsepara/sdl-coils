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

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 50;
        }
        else
        {
            return 203;
        }
    }
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

        Text = "You have made the right choice. Skakshi cannot get past your guard as your BLADE cuts through the air. He is becoming increasingly desperate. \"Impossible ...\" he gasps, face twisted into a look of fury. \"You must be cheating -- using some Judain sorcery to aid you!\"\n\nYou are about to step up the tempo of your attack when he throws down the club and tries to make a run for the door.";

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

        PreText = "You gained the codeword IMPASSE.\n\nYou cut Skakshi down in a welter of blood, wipe your BLADE on a barcloth, and replace it in its scabbard before looking round you once more.\n\nAll is quiet in the Inn of the Inner Temple. No one will meet your eye. They stare at Skakshi's corpse, shocked at the sudden violence you have done to one of their comrades. You don't expect any trouble from them after that demonstration. Nor will you make many friends here. You feel Skakshi's pockets, quickly finding a concealed flap in which you discover a set of THROWING KNIVES.\n\nYou look up from the body. One man gives you a narrow glare and spits on the floor. You won't make any friends here so you decide to go back to your· lair on Bumble Row.\n\nIn your heart you know that you did not have to kill Skakshi. Perhaps you are beginning to succumb to the general hysteria and hatred that seems to be infetting most others in the city?";

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

        Text = "People turn to stare as you run past and then take up the hue and cry as they are engulfed by the mob that pursues you. You run on, your lungs beginning to hurt. They are not closing but you don't know how much longer you can keep going like this. Every time you see a likely place to hide t~ere seems to be someone else there. You turn a corner and run on in the direction of the main gate where the trade road enters the city. Behind you can hear the sound of hoofs on the cobbles. A squadron of the Overlord's cavalry is giving chase. Ahead there is a drinking house, outside is a HORSE tethered to a post.";

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
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 119;
        }
        else
        {
            return 133;
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

        Choices.clear();
        Choices.push_back(Choice::Base("Change your mind about fleeing and offer to throw your lot in with them", 64));
        Choices.push_back(Choice::Base("Keep running and hide in the city once more", 76));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            Choices[1].Destination = 188;
        }
        else
        {
            Choices[1].Destination = 76;
        }
    }
};

class Story045 : public Story::Base
{
public:
    Story045()
    {
        ID = 45;

        Text = "You also manage to free two hundred of the grateful guards who cannot believe their luck. They wipe themselves off along the walls. Most of them look as if they are in shock. They shouldn't give you too much trouble. You are more likely to face trouble from the Judain you have set free. They can see their tormenters among them and they want to take their revenge. \"Now die, dogs, die slowly and in pain!\" they cry. \"Let us see how you like to be put to the torture. Kill them! Heat the irons and warm their vitals.\" The Judain are near hys~erical and they begin to slaughter the guards out of hand, while others try to drag some of them back to the torture chambers. The guards are petrified.\n\nWill you stop the slaughter by killing one of your fellow Judain? In the heat of the moment there is no time for finesse, and your people are behaving no better than savage beasts who have lost all control.";

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

        Text = "You find the librarian outside the building, staring at a glimmering pile of ashes. As you go closer, you see that someone has piled up the books of the library and torched them. The librarian falls to his knees, overcome with distress. \"They burned my books!\" he groans, tears running into his beard. \n\n\"Who did? And why?\" you ask.\n\n\"The Overlord's men. They said that knowledge was the enemy oflaw and order. They claimed that lies had been written in the books by Judain authors. Oh, such a waste ... !\"\n\nThere is no chance now of finding more about Hate from the writings of ancient scholars; you may not visit the library again should you be given the option. You wonder if the Overlord has truly gone mad.";

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

        Text = "Tarkamandor tells you he has decided to quit the city. \"Matters have gone too far,\" he says. \"Each day I fear the guards will come to drag me off to Grond.\"\n\n\"Why should you fear?\" you say with a trace of bitterness. \"You are not Judain.\"\n\nHe gives a snort of ironic laughter. \"Do you think that what has been going on is a simple matter of persecution? It goes deeper than that. The Overlord started his attacks on your people to distract attention from his disastrous policies, reasoning that once the populace had a scapegoat to blame they would be easier to control.\"\n\n\"That strategy has worked well, them\"\n\n\"Now it is out of control! Hate is rife in the city. It extends its influence like a cancer. Today it is you Judain who are marched off to the prison. Tomorrow it may he the aged, or the infirm, or those who dare to speak out against the Overlord. That's why I'm leaving.\" He takes a few more steps, the wheels of his cart sloshing through the rut of mire in the middle of the street, then pauses and looks back. \"As long as I'm going, I suppose I ought to sell some of my stock. Are you interested?\"\n\nHe has a HEALING SALVE which can be used once at any time except when in combat; it will RESTORE ALL LOST Life Points. Another item on the cart is a pair of ELFIN BOOTS which grant their wearer one use of the AGILITY skill and must then be discarded. Tarkamandor also offers you a CENSER OF FRAGRANT INCENSE which he swears is blessed by the temple, a SWORD, a set of THROWING KNIVES, and a MAGIC WAND.";

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

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You advance quickly on Skakshi, getting in close to match your sword against his club. As you lunge forward, the haft of the club catches you a painful blow on the shoulder and you feel the spikes tear your jerkin and bite into the flesh beneath.\n\nYou LOSE 3 Life Points.";

        Character::GAIN_LIFE(player, -3);

        if (player.Life > 0)
        {
            PreText += "\n\nYou send the pommel of your sword crashing into Skakshi's jaw with stunning force. He gives a surprised grunt as his knees fold under him. Before he can rise and continue the battle, you have the point of your sword at his throat. \"Take me to Melmelo,\" you say to him as you get your breath back.\n\nHe looks at your sword uneasily as he slowly gets to his feet. \"I'll take you,\" he says sullenly.";
        }

        Text = PreText.c_str();
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

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You fling up the door and jump down into the cellar to find yourself surrounded by several men, one of whomjabs you with a rusty old spear before you can regain your balance.\n\nYou LOSE 3 Life Points.";

        Character::GAIN_LIFE(player, -3);

        if (player.Life > 0)
        {
            PreText += "\n\n\"Wait! A fellow Judain!\" realizes one of them. You recognize the tall imposing figure of Caiaphas, rabbi at the synagogue before it was torn down by the mob.\n\n\"I am,\" you reply with a nod. \"As, I see, are all of you.\"\n\nThere are three Judain families hiding down here from the Overlord's butchers. The rusty old spear is thrown aside as they welcome you with open arms.";
        }

        Text = PreText.c_str();
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
        &story080, &story081, &story082, &story083, &story084, &story085, &story086, &story087, &story088, &story089};
}

#endif