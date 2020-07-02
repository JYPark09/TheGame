#include <TheGame/Cards/CardStack.hpp>

#include <stdexcept>

namespace TheGame
{
CardStack::CardStack(Type type) : type_(type)
{
    cards_.emplace(type == Type::UP ? Card::Min : Card::Max);
}

bool CardStack::Stackable(const Card& card) const
{
    if (!card.IsValid())
        return false;

    if (type_ == Type::UP)
    {
        return (card > cards_.top()) || (card == cards_.top() - 10);
    }

    return (card < cards_.top()) || (card == cards_.top() + 10);
}

void CardStack::AddCard(Card card)
{
    if (!Stackable(card))
        throw std::runtime_error("Not stackable");

    cards_.emplace(card);
}

std::optional<Card> CardStack::PopCard()
{
    if (cards_.size() == 1)
        return std::nullopt;

    const Card temp = cards_.top();
    cards_.pop();

    return temp;
}

const Card& CardStack::TopCard() const
{
    return cards_.top();
}
}  // namespace TheGame
