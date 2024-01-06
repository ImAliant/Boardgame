#include "../../../include/game/bulltricker/Bulltricker.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"

void Bulltricker::Turn(const coord_t coord)
{

}

void Bulltricker::SelectPiece(const coord_t coord)
{

}

void Bulltricker::DeselectPiece()
{

}

bool Bulltricker::IsMovePossible(const coord_t coord) const
{
    return false;
}

void Bulltricker::PerformMove(const coord_t coord)
{

}

void Bulltricker::ProcessConditionalMove(const coord_t coord)
{

}

void Bulltricker::ApplyCapture(const coord_t coord)
{

}

void Bulltricker::HandlePieceCaptureAndReplay(const coord_t coord)
{

}

void Bulltricker::InitPlayers()
{
   InitPlayersBase(m_status);
}

void Bulltricker::CreateGameBoard()
{
    m_board = std::make_unique<BulltrickerBoard>(m_players);
}
void Bulltricker::CheckBoardDimensions(const int row, const int col) const
{
    if (row != GameConstants::BulltrickerConstants::BULLTRICKERROWS || 
        col != GameConstants::BulltrickerConstants::BULLTRICKERCOLS)
        throw InvalidUsageException("Bulltricker::CheckBoardDimensions() : Invalid board dimensions");
}

void Bulltricker::SwitchPlayer()
{
    // TODO
}

void Bulltricker::CheckForWin()
{
    // TODO
}

void Bulltricker::EndGameIfNoMoves()
{
    // TODO
}

void Bulltricker::GameStart()
{
    // TODO
}

bool Bulltricker::IsGameStarted() const
{
    // TODO
    return false;
}

bool Bulltricker::IsGameFinished() const
{
    // TODO
    return false;
}

bool Bulltricker::IsPieceSelected() const
{
    // TODO
    return false;
}

bool Bulltricker::IsSelectedPieceChanged() const
{
    // TODO
    return false;
}

bool Bulltricker::IsBoardNeedUpdate() const
{
    // TODO
    return false;
}

bool Bulltricker::IsCurrentPlayerChanged() const
{
    // TODO
    return false;
}

void Bulltricker::ResetCurrentPlayerChangedFlag()
{
    // TODO
}

void Bulltricker::ResetSelectedPieceFlag()
{
    // TODO
}

void Bulltricker::ResetBoardNeedUpdateFlag()
{
    // TODO
}

Player* Bulltricker::GetWinner() const
{
    // TODO
    return nullptr;
}

std::shared_ptr<Player> Bulltricker::GetCurrentPlayer() const
{
    // TODO
    return nullptr;
}

coord_t Bulltricker::GetSelectedPiece() const
{
    // TODO
    return coord_t();
}

coord_t Bulltricker::GetLastSelectedPiece() const
{
    // TODO
    return coord_t();
}

std::vector<coord_t> Bulltricker::GetLastPossibleMoves() const
{
    // TODO
    return std::vector<coord_t>();
}