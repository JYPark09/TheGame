#include <TheGame/Game/Game.hpp>

#include <effolkronium/random.hpp>
#include <numeric>
#include <stdexcept>

namespace TheGame
{
void Game::AddPlayer(std::unique_ptr<Player>&& player)
{
    players_.emplace_back(std::move(player));
}

std::size_t Game::GetPlayerNumber() const
{
    return players_.size();
}

void Game::Begin()
{
    if (players_.empty())
        throw std::runtime_error("No players added");

    switch (players_.size())
    {
        case 1:
            cardsToHave_ = 8;
            break;

        case 2:
            cardsToHave_ = 7;
            break;

        default:
            cardsToHave_ = 6;
            break;
    }

    minCardsToDraw_ = 2;
    finished_ = false;

    std::vector<int> cardIdx(100 - 2);  // 2 to 99
    std::iota(begin(cardIdx), end(cardIdx), 2);

    effolkronium::random_thread_local::shuffle(cardIdx);

    for (const auto idx : cardIdx)
    {
        cards_.emplace_back(Card(idx));
    }

    for (std::size_t i = 0; i < STACK_COUNT; ++i)
        stacks_[i].reset();

    for (std::size_t i = 0; i < STACK_COUNT / 2; ++i)
        stacks_[i] = std::make_unique<CardStack>(CardStack::Type::UP);

    for (std::size_t i = STACK_COUNT / 2; i < STACK_COUNT; ++i)
        stacks_[i] = std::make_unique<CardStack>(CardStack::Type::DOWN);
}

bool Game::IsEnd() const
{
    return finished_;
}

Game::Result Game::GetResult() const
{
    if (finished_)
        return Result::NOT_FINISHED;

    // TODO: Check game result

    return Result::LOSE;
}

std::size_t Game::GetMinCardsToDraw() const
{
    return minCardsToDraw_;
}
}  // namespace TheGame
