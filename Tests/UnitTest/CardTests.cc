#include <doctest.h>

#include <TheGame/Cards/CardStack.hpp>

using namespace TheGame;

TEST_CASE("[CardTests] - Card initializer")
{
    Card c0(0);
    CHECK_FALSE(c0.IsValid());
    CHECK_EQ(c0, 0);

    Card c1(1);
    CHECK_FALSE(!c1.IsValid());
    CHECK_EQ(c1, 1);

    Card c100(100);
    CHECK_FALSE(!c100.IsValid());
    CHECK_EQ(c100, 100);

    Card c101(101);
    CHECK_FALSE(c101.IsValid());
    CHECK_EQ(c101, 101);
}

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
    CHECK_NOTHROW(cards.AddCard(Card(89)));
    CHECK_EQ(cards.TopCard(), 89);
    CHECK_NOTHROW(cards.AddCard(Card(90)));
    CHECK_EQ(cards.TopCard(), 90);
    CHECK_THROWS(cards.AddCard(Card(101)));
    CHECK_EQ(cards.TopCard(), 90);

    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(cards.PopCard().has_value());
}

using namespace TheGame;

TEST_CASE("[CardTests] - Down CardStack")
{
    CardStack cards(CardStack::Type::DOWN);


    CHECK_FALSE(!cards.Stackable(Card(99)));
    CHECK_FALSE(cards.Stackable(Card(100)));

    CHECK_NOTHROW(cards.AddCard(Card(98)));
    CHECK_EQ(cards.TopCard(), 98);
    CHECK_THROWS(cards.AddCard(Card(99)));
    CHECK_EQ(cards.TopCard(), 98);
    CHECK_NOTHROW(cards.AddCard(Card(80)));
    CHECK_EQ(cards.TopCard(), 80);
    CHECK_NOTHROW(cards.AddCard(Card(90)));
    CHECK_EQ(cards.TopCard(), 90);

    CHECK_NOTHROW(cards.AddCard(Card(1)));
    CHECK_EQ(cards.TopCard(), 1);

    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(!cards.PopCard().has_value());
    CHECK_FALSE(cards.PopCard().has_value());
}
