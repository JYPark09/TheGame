#include <TheGame/Cards/Card.hpp>

namespace TheGame
{
Card::Card(int value) : value_(value)
{
    // Do Nothing
}

bool Card::IsValid() const
{
    return (value_ > 0 && value_ <= 100);
}

Card::operator int() const
{
    return value_;
}
}  // namespace TheGame
