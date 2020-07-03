#ifndef THEGAME_CARD_HPP
#define THEGAME_CARD_HPP

#include <vector>

namespace TheGame
{
class Card final
{
 public:
    static constexpr int Min = 1;
    static constexpr int Max = 100;

    using Arr = std::vector<Card>;

 public:
    explicit Card(int value);

    [[nodiscard]] bool IsValid() const;

    operator int() const;

 private:
    int value_;
};
}  // namespace TheGame

#endif  // THEGAME_CARD_HPP
