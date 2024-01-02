#include "../../../include/game/bulltricker/Bulltricker.hpp"
#include "../../../include/game/bulltricker/BulltrickerBoard.hpp"


    void Bulltricker::SelectPiece(const coord_t coord) {}
    void Bulltricker::DeselectPiece()  {}

    bool Bulltricker::IsMovePossible(const coord_t coord) const { return false; }
    void Bulltricker::PerformMove(const coord_t coord) {}
    void Bulltricker::ProcessConditionalMove(const coord_t coord) {}
    void Bulltricker::ApplyCapture(const coord_t coord) {}
    void Bulltricker::HandlePieceCaptureAndReplay(const coord_t coord) {}

    void Bulltricker::InitPlayers() {InitPlayersBase(m_status);}

    void Bulltricker::SwitchPlayer() {}

    void Bulltricker::CheckForWin() {}

   void Bulltricker::CreateGameBoard()
{
    m_board = std::make_unique<BulltrickerBoard>(m_players);
}
    void Bulltricker::CheckBoardDimensions(const int row, const int col) const {}

    void Bulltricker::Turn(const coord_t coord) {}
    void Bulltricker::GameStart() {}

    bool Bulltricker::IsGameStarted() const { return false; }
    bool Bulltricker::IsGameFinished() const { return false; }
    bool Bulltricker::IsPieceSelected() const { return false; }
    bool Bulltricker::IsSelectedPieceChanged() const { return false; }
    bool Bulltricker::IsBoardNeedUpdate() const { return false; }
    bool Bulltricker::IsCurrentPlayerChanged() const { return false; }

    void Bulltricker::ResetCurrentPlayerChangedFlag() {}
    void Bulltricker::ResetSelectedPieceFlag() {}
    void Bulltricker::ResetBoardNeedUpdateFlag() {}

    Player* Bulltricker::GetWinner() const { return nullptr; }

    std::shared_ptr<Player> Bulltricker::GetCurrentPlayer() const { return nullptr; }
    coord_t Bulltricker::GetSelectedPiece() const { return {0, 0}; }
    coord_t Bulltricker::GetLastSelectedPiece() const { return {0, 0}; }
    std::vector<coord_t> Bulltricker::GetLastPossibleMoves() const { return {};} 
