#include <TheGame/Game/Game.hpp>

#include <effolkronium/random.hpp>
#include <numeric>
#include <stdexcept>
#include <utility>

namespace TheGame
{
Game::Game()
{
	for (auto& s : state_.CardStacks)
	{
		s = nullptr;
	}
}

void Game::AddPlayer(Player* player)
{
	player->SetGame(this);
    players_.emplace_back(player);
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
    return *(players_[turn_]);
}

const GameState& Game::GetState() const
{
    return state_;
}

void Game::Begin()
{
    if (players_.empty())
        throw std::runtime_error("No players added");

    std::size_t numOfPlayers = players_.size();
    switch (numOfPlayers)
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
    state_.Result = GameResult::NOT_FINISHED;

    turn_ = effolkronium::random_thread_local::get<std::size_t>(
        0, numOfPlayers - 1);

    std::vector<int> cardIdx(Card::Max - Card::Min - 1);
    std::iota(begin(cardIdx), end(cardIdx), Card::Min + 1);

    effolkronium::random_thread_local::shuffle(cardIdx);

    for (const auto idx : cardIdx)
    {
        state_.Cards.emplace_back(Card(idx));
    }

    for (std::size_t i = 0; i < numOfPlayers; ++i)
    {
        players_[i]->Cards.assign(begin(state_.Cards),
                                  begin(state_.Cards) + state_.CardsToHave);
        state_.Cards.erase(begin(state_.Cards),
                           begin(state_.Cards) + state_.CardsToHave);
    }

    for (std::size_t i = 0; i < GameState::STACK_COUNT; ++i)
	{
        delete state_.CardStacks[i];
		state_.CardStacks[i] = nullptr;
	}

    for (std::size_t i = 0; i < GameState::STACK_COUNT / 2; ++i)
        state_.CardStacks[i] = new CardStack(CardStack::Type::UP);

    for (std::size_t i = GameState::STACK_COUNT / 2; i < GameState::STACK_COUNT;
         ++i)
        state_.CardStacks[i] =
            new CardStack(CardStack::Type::DOWN);
}

void Game::InvokeCurrentPlayer()
{
    GetCurrentPlayer().Invoke();
}

void Game::ProcessTurn(Task&& task)
{
    auto& curPlayer = GetCurrentPlayer();

    task.SetPlayer(&curPlayer);
    task.Process(&state_);
}

void Game::EndTurn()
{
    auto& curPlayer = GetCurrentPlayer();
    const std::size_t diffCards = state_.CardsToHave - curPlayer.Cards.size();
    for (std::size_t i = 0; i < diffCards && !state_.Cards.empty(); ++i)
    {
        curPlayer.Cards.emplace_back(state_.Cards.back());
        state_.Cards.pop_back();
    }

    // now turn_ points next player
    turn_ = (turn_ + 1) % players_.size();

    if (state_.Cards.empty())
        state_.MinCardsToDraw = 1;

    updateResult();
}

void Game::updateResult()
{
    std::size_t sumOfPlayerCards = 0;
    for (const auto& p : players_)
        sumOfPlayerCards += p->Cards.size();

    if (sumOfPlayerCards == 0)
    {
        state_.Result = GameResult::WIN;
        return;
    }
    
    // this method called when turn points next player
    const auto& nextPlayer = GetCurrentPlayer();
    for (const auto& card : nextPlayer.Cards)
    {
        for (const auto& s : state_.CardStacks)
        {
            if (s->Stackable(card))
            {
                state_.Result = GameResult::NOT_FINISHED;
                return;
            }
        }
    }

    // there are no stackable cards
    state_.Result = GameResult::LOSE;
}
}  // namespace TheGame
