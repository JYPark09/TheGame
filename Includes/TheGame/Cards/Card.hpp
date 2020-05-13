#ifndef THEGAME_CARD_HPP
#define THEGAME_CARD_HPP

namespace TheGame
{
class Card final
{
public:
    explicit Card(int value);

    [[nodiscard]] bool IsValid() const;

    operator int() const;

private:
    int value_;
};
}  // namespace TheGame

#endif  // THEGAME_CARD_HPP
