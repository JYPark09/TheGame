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
            state_.CardsToHave = 8;
            break;

        case 2:
            state_.CardsToHave = 7;
            break;

        default:
            state_.CardsToHave = 6;
            break;
    }

    state_.MinCardsToDraw = 2;
    state_.Finished = false;

    std::vector<int> cardIdx(100 - 2);  // 2 to 99
    std::iota(begin(cardIdx), end(cardIdx), 2);

    effolkronium::random_thread_local::shuffle(cardIdx);

    for (const auto idx : cardIdx)
    {
        state_.Cards.emplace_back(Card(idx));
    }

    for (std::size_t i = 0; i < GameState::STACK_COUNT; ++i)
        state_.CardStacks[i].reset();

    for (std::size_t i = 0; i < GameState::STACK_COUNT / 2; ++i)
        state_.CardStacks[i] = std::make_unique<CardStack>(CardStack::Type::UP);

    for (std::size_t i = GameState::STACK_COUNT / 2; i < GameState::STACK_COUNT; ++i)
        state_.CardStacks[i] = std::make_unique<CardStack>(CardStack::Type::DOWN);
}

bool Game::ProcessTurn()
{
    return false;
}
}  // namespace TheGame
