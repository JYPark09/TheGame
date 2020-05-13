#ifndef THEGAME_CARD_STACK_HPP
#define THEGAME_CARD_STACK_HPP

#include <stack>
#include <optional>

#include <TheGame/Cards/Card.hpp>

namespace TheGame
{
class CardStack final
{
 public:
    enum class Type
    {
        UP,
        DOWN
    };

 public:
    CardStack(Type type);

    [[nodiscard]] bool Stackable(const Card& card) const;

    void AddCard(Card card);
    [[nodiscard]] std::optional<Card> PopCard();
    const Card& TopCard() const;

 private:
    Type type_;

    std::stack<Card> cards_;
};
}  // namespace TheGame

#endif  // THEGAME_CARD_STACK_HPP
