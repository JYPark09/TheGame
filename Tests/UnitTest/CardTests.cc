#include <doctest.h>

#include <TheGame/Cards/CardStack.hpp>

using namespace TheGame;

TEST_CASE("[CardTests] - Up CardStack")
{
    CardStack cards(CardStack::Type::UP);

    CHECK_FALSE(cards.Stackable(Card(0)));
    CHECK_THROWS(cards.AddCard(Card(0)));
    CHECK_FALSE(cards.Stackable(Card(1)));
    CHECK_THROWS(cards.AddCard(Card(1)));

    CHECK_EQ(cards.TopCard(), 1);

    CHECK_NOTHROW(cards.AddCard(Card(2)));
    CHECK_EQ(cards.TopCard(), 2);
    CHECK_NOTHROW(cards.AddCard(Card(99)));
    CHECK_EQ(cards.TopCard(), 99);
    CHECK_THROWS(cards.AddCard(Card(98)));
    CHECK_EQ(cards.TopCard(), 99);

    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(cards.PopCard().has_value());
}

using namespace TheGame;

TEST_CASE("[CardTests] - Down CardStack")
{
    CardStack cards(CardStack::Type::DOWN);

    CHECK_FALSE(cards.Stackable(Card(1)));
    CHECK_THROWS(cards.AddCard(Card(1)));

    CHECK_EQ(cards.TopCard(), 1);

    CHECK_NOTHROW(cards.AddCard(Card(99)));
    CHECK_EQ(cards.TopCard(), 99);
    CHECK_THROWS(cards.AddCard(Card(98)));
    CHECK_EQ(cards.TopCard(), 99);

    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(cards.PopCard().has_value());
}
