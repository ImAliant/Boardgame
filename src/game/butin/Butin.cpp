#include "../../../include/game/butin/Butin.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>

Butin::Butin() {}

Butin::~Butin() {}

void Butin::Init()
{
    InitPlayers();
    InitBoard();
    UpdatePossibleMoves();
}

void Butin::Turn(coord_t coord)
{
    if (IsGameFinished()) throw InvalidUsageException("Butin::Turn() : m_isGameFinished is true");
    if (!IsGameStarted()) throw InvalidUsageException("Butin::Turn() : m_isGameStarted is false");
    if (!AreCoordinatesValid(coord)) throw InvalidCoordinatesException("Butin::Turn() : coord are invalid");

    if (IsFirstRound())
    {
        HandleFirstRoundSelection(coord);

        SwitchPlayer();

        EndFirstRoundIfNeeded();
    }
    else
    {
        if (IsYellowPiece(coord) && !m_flags.IsReplay()) SelectPiece(coord);
        else if (IsMovePossible(coord) && IsPieceSelected())
        {
            PerformMove(coord);
            
            CheckForWin();

            if (IsGameFinished()) return;

            if (!m_flags.IsReplay()) SwitchPlayer();

            m_flags.ResetPieceCapturedFlag();
        }
        else
        {
            if (IsPieceSelected() && !m_flags.IsReplay()) DeselectPiece();
        }
    }
}

void Butin::SelectPiece(const coord_t coord)
{
    if (m_flags.IsPieceSelected()) DeselectPiece();

    m_status.SetSelectedPiece(coord);
    auto possibleMoves = GetPossibleMoves(coord);
    m_status.SetPossibleMoves(possibleMoves);
    m_flags.PieceIsSelected();
}
void Butin::DeselectPiece()
{
    m_status.SaveLastPossibleMoves();
    m_status.SaveLastSelectedPiece();
    m_flags.SelectPieceChanged();
    m_flags.PieceIsNotSelected();
    m_status.ResetSelectedPiece();
}

bool Butin::IsMovePossible(const coord_t coord) const
{
    if (!IsPieceSelected()) return false;

    auto possibleMoves = GetPossibleMoves(GetSelectedPiece());
    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}
void Butin::PerformMove(const coord_t coord)
{
    if (!(IsMovePossible(coord) && IsPieceSelected())) throw InvalidUsageException("Butin::PerformMove() : move is not possible");

    if (!AreCoordinatesValid(coord)) throw InvalidCoordinatesException("Butin::PerformMove() : coord are invalid");

    auto piece = GetPiece(GetSelectedPiece());
    if (piece == nullptr) throw InvalidUsageException("Butin::PerformMove() : piece is null");

    auto possibleCaptures = piece->GetPossibleCaptures();
    auto possibleMoves = piece->GetPossibleMoves();
  
    auto it = std::find(possibleMoves.begin(), possibleMoves.end(), coord);
    if (it == possibleMoves.end()) throw InvalidUsageException("Butin::PerformMove() : move is not possible");

    const auto index = std::distance(possibleMoves.begin(), it);
    const auto [captx, capty] = possibleCaptures[index];

    const auto x = coord.first - captx;
    const auto y = coord.second - capty;

    const auto& captureCoord = std::make_pair(x, y);
    if (!AreCoordinatesValid(captureCoord)) throw InvalidCoordinatesException("Butin::PerformMove() : captureCoord are invalid");

    const auto pieceCapture = GetPiece(captureCoord);
    if (pieceCapture == nullptr) throw InvalidUsageException("Butin::PerformMove() : pieceCapture is null");

    m_board->MovePiece(GetSelectedPiece(), coord);
    UpdatePlayerScore(pieceCapture->GetSymbol());
    m_board->RemovePiece(captureCoord);

    DeselectPiece();
    UpdatePossibleMoves();
    m_flags.PieceIsCaptured();

    if (m_flags.IsPieceCaptured() && HasCapturingMoves(coord))
    {
        SelectPiece(coord);
        m_flags.NeedReplay();
    }
    else m_flags.ResetReplayFlag();

    m_flags.BoardNeedUpdate();
}

bool Butin::HasCapturingMoves(const coord_t coord) const
{
    auto piece = GetPiece(coord);
    if (piece == nullptr) return false;

    auto possibleCaptures = piece->GetPossibleCaptures();
    return !possibleCaptures.empty();
}

void Butin::UpdatePlayerScore(const char color) const
{
    int scoreIncrement = 0;
    if (color == GameConstants::ButinConstants::BUTIN_YELLOW) scoreIncrement = 1;
    else if (color == GameConstants::ButinConstants::BUTIN_RED) scoreIncrement = 2;
    else if (color == GameConstants::ButinConstants::BUTIN_BLACK) scoreIncrement = 3;
    else return;

    m_status.GetCurrentPlayer()->AddScore(scoreIncrement);
}

void Butin::HandleFirstRoundSelection(const coord_t coord)
{
    const auto piece = GetPiece(coord);
    if (piece == nullptr) return;
    
    if (IsYellowPiece(coord))
    {
        m_board->RemovePiece(coord);
        m_status.IncrementCurrentPlayerIndex();
        m_flags.BoardNeedUpdate();
    }
}
void Butin::EndFirstRoundIfNeeded()
{
    int numberOfPlayers = m_players.size();
    if (m_status.GetCurrentPlayerIndex() >= numberOfPlayers)
    {
        EndFirstRound();
        m_status.SetCurrentPlayerIndex(0);
        UpdatePossibleMoves();
    }
}

void Butin::CheckForWin()
{
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            const auto& coord = std::make_pair(i, j);
            const auto piece = GetPiece(coord);
            if (piece == nullptr) continue;
            
            if (IsYellowPiece(coord) && HasCapturingMoves(coord))
            {
                return;
            }
        }
    }

    DetermineWinner();
    m_flags.GameFinished();
}
void Butin::DetermineWinner()
{
    Player* winner = nullptr;
    const auto& playerOneScore = m_players[GameConstants::PLAYER_ONEID]->GetScore();
    const auto& playerTwoScore = m_players[GameConstants::PLAYER_TWOID]->GetScore();

    if (playerOneScore > playerTwoScore) winner = m_players[GameConstants::PLAYER_ONEID].get();
    else if (playerOneScore < playerTwoScore) winner = m_players[GameConstants::PLAYER_TWOID].get();

    m_status.SetWinner(winner);
    if (winner != nullptr)
        m_status.SetWinnerScore(winner->GetScore());
}

bool Butin::IsYellowPiece(const coord_t coord) const
{
    const auto piece = GetPiece(coord);
    if (piece == nullptr) return false;

    return piece->GetSymbol() == GameConstants::ButinConstants::BUTIN_YELLOW;
}

void Butin::SwitchPlayer()
{
    if (m_status.GetCurrentPlayer() == m_players[GameConstants::PLAYER_ONEID])
        m_status.SetCurrentPlayer(m_players[GameConstants::PLAYER_TWOID]);
    else m_status.SetCurrentPlayer(m_players[GameConstants::PLAYER_ONEID]);

    m_flags.ResetReplayFlag();
    m_flags.CurrentPlayerChanged();
}

void Butin::InitPlayers() {
    // On teste si les joueurs sont déjà initialisés
    if (!m_players.empty()) {
        m_players.clear();
    }

    // On crée les joueurs
    m_players.push_back(std::make_shared<Player>());
    m_players.push_back(std::make_shared<Player>());

    // On définit le joueur courant
    m_status.SetCurrentPlayer(m_players[GameConstants::PLAYER_ONEID]);
}

void Butin::InitBoard()
{
    // On teste si le board est déjà initialisé
    if (m_board != nullptr) {
        m_board.reset();
    }
    // On teste si les joueurs sont bien initialisés
    if (m_players.empty()) {
        throw std::runtime_error("Checkers::InitBoard() : m_players is empty");
    }

    m_board = std::make_unique<ButinBoard>(m_players);

    int row = m_board->GetRows();
    int col = m_board->GetCols();

    if (row != GameConstants::ButinConstants::BUTINROWS || col != GameConstants::ButinConstants::BUTINCOLS) {
        throw std::runtime_error("Checkers::InitBoard() : row and col have incorrect values");
    }
}

void Butin::UpdatePossibleMoves() const
{
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) 
        {
            const auto& coord = std::make_pair(i, j);
            const auto piece = GetPiece(coord);
            if (piece == nullptr) continue;

            piece->FindPossibleMoves(*m_board);
        }
    }
}

bool Butin::AreCoordinatesValid(coord_t coord) const
{
    return coord.first >= 0 
        && coord.first < GameConstants::ButinConstants::BUTINROWS 
        && coord.second >= 0 
        && coord.second < GameConstants::ButinConstants::BUTINCOLS;
}

void Butin::GameStart() 
{
    m_flags.GameStarted();
}
void Butin::EndFirstRound() 
{
    m_flags.EndFirstRound();
}

bool Butin::IsGameStarted() const
{
    return m_flags.IsGameStarted();
}
bool Butin::IsGameFinished() const
{
    return m_flags.IsGameFinished();
}
bool Butin::IsFirstRound() const
{
    return m_flags.IsFirstRound();
}
bool Butin::IsPieceSelected() const 
{
    return m_flags.IsPieceSelected();
}
bool Butin::IsSelectedPieceChanged() const 
{
    return m_flags.IsSelectedPieceChanged();
}
bool Butin::IsBoardNeedUpdate() const
{
    return m_flags.IsBoardNeedUpdate();
}
bool Butin::IsCurrentPlayerChanged() const
{
    return m_flags.IsCurrentPlayerChanged();
}

void Butin::ResetSelectedPieceFlag()
{
    return m_flags.ResetSelectedPieceFlag();
}
void Butin::ResetBoardNeedUpdateFlag()
{
    return m_flags.ResetBoardNeedUpdateFlag();
}
void Butin::ResetCurrentPlayerChangedFlag()
{
    return m_flags.ResetCurrentPlayerChangedFlag();
}

Piece* Butin::GetPiece(coord_t coord) const
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Butin::GetPiece(): coord are invalid");

    return m_board->GetPiece(coord);
}
std::unique_ptr<ButinBoard>& Butin::GetBoard()
{
    return m_board;
}
std::vector<std::shared_ptr<Player>>& Butin::GetPlayers()
{
    return m_players;
}
coord_t Butin::GetSelectedPiece() const
{
    return m_status.GetSelectedPiece();
}
coord_t Butin::GetLastSelectedPiece() const
{
    return m_status.GetLastSelectedPiece();
}
std::vector<coord_t> Butin::GetPossibleMoves(coord_t coord) const
{
    return GetPiece(coord)->GetPossibleMoves();
}
std::vector<coord_t> Butin::GetLastPossibleMoves() const
{
    return m_status.GetLastPossibleMoves();
}
std::shared_ptr<Player> Butin::GetCurrentPlayer() const
{
    return m_status.GetCurrentPlayer();
}
Player* Butin::GetWinner() const
{
    return m_status.GetWinner();
}
int Butin::GetWinnerScore() const
{
    return m_status.GetWinnerScore();
}