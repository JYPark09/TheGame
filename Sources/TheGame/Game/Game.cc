#include <TheGame/Game/Game.hpp>

#include <effolkronium/random.hpp>
#include <numeric>
#include <stdexcept>
#include <utility>

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

std::size_t Game::GetTurn() const
{
    return turn_;
}

Player& Game::GetCurrentPlayer()
{
    return const_cast<Player&>(std::as_const(*this).GetCurrentPlayer());
}

const Player& Game::GetCurrentPlayer() const
{
    return *(players_[turn_].get());
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

    turn_ = effolkronium::random_thread_local::get<std::size_t>(
        0, players_.size() - 1);

    std::vector<int> cardIdx(Card::Max - Card::Min - 1);
    std::iota(begin(cardIdx), end(cardIdx), Card::Min + 1);

    effolkronium::random_thread_local::shuffle(cardIdx);

    for (const auto idx : cardIdx)
    {
        state_.Cards.emplace_back(Card(idx));
    }

    for (std::size_t i = 0; i < GameState::STACK_COUNT; ++i)
        state_.CardStacks[i].reset();

    for (std::size_t i = 0; i < GameState::STACK_COUNT / 2; ++i)
        state_.CardStacks[i] = std::make_unique<CardStack>(CardStack::Type::UP);

    for (std::size_t i = GameState::STACK_COUNT / 2; i < GameState::STACK_COUNT;
         ++i)
        state_.CardStacks[i] =
            std::make_unique<CardStack>(CardStack::Type::DOWN);
}

void Game::InvokeCurrentPlayer()
{
    GetCurrentPlayer().Invoke();
}

void Game::ProcessTurn(Task::Arr& tasks)
{
    for (auto& task : tasks)
        task.Process();

    turn_ = (turn_ + 1) % players_.size();
}
}  // namespace TheGame
