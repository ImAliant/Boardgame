#include "../../../include/game/checkers/Checkers.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>
#include <random>

Checkers::Checkers() {}

Checkers::~Checkers() {}

void Checkers::SwitchPlayer() {
    if (GetCurrentPlayer() == m_players[GameConstants::PLAYER_ONEID])
        m_status.SetCurrentPlayer(m_players[GameConstants::PLAYER_TWOID]);
    else m_status.SetCurrentPlayer(m_players[GameConstants::PLAYER_ONEID]);

    m_flags.CurrentPlayerChanged();
}

void Checkers::Turn(coord_t coord) {
    // On teste si la partie est déjà terminée
    if (IsGameFinished()) 
        throw InvalidUsageException("Checkers::Turn() : m_isGameFinished is true");
    // On teste si la partie n'est pas encore commencée
    if (!IsGameStarted()) 
        throw InvalidUsageException("Checkers::Turn() : m_isGameStarted is false");
    // On teste si les coordonnées sont valides
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::Turn() : coord are invalid");

    if (IsPieceOfCurrentPlayer(coord))
    {
        m_flags.SetCapturingMoveRequiredFlag(HasCapturingMoves(coord));

        if (m_flags.IsCapturingMoveRequired() || !HavePieceWithCapturingMoves())
            SelectPiece(coord);
        else 
        {
            //ShowErrorMessage("You must capture an opponent's piece");
            printf("You must select a piece that can capture an opponent's piece\n");
            m_flags.CapturingMoveRequired();
        }
    }
    else if (IsMovePossible(coord) && m_flags.IsPieceSelected())
    {
        PerformMove(coord);

        CheckForWin();

        if (IsGameFinished()) return;

        if (!m_flags.IsReplay())
            SwitchPlayer();

        m_flags.ResetPieceCapturedFlag();
        if (!m_flags.IsReplay())
            m_flags.ResetCapturingMoveRequiredFlag();
    }
    else
    {
        if (m_flags.IsPieceSelected() && m_flags.IsReplay())
            DeselectPiece();
    }
}

bool Checkers::IsPieceOfCurrentPlayer(coord_t coord) const
{
    auto piece = GetPiece(coord);
    if (piece == nullptr) return false;
    
    auto pieceOwner = piece->GetOwner();
    auto idPieceOwner = pieceOwner->GetId();
    auto idCurrentPlayer = GetCurrentPlayer()->GetId();

    return idCurrentPlayer == idPieceOwner;
}

bool Checkers::IsMovePossible(coord_t coord) const
{
    // On teste si la piece est selectionnée
    if (!m_flags.IsPieceSelected()) {
        return false;
    }

    // On teste si la piece peut se déplacer à la coordonnée
    auto possibleMoves = GetPossibleMoves(GetSelectedPiece());
    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}

void Checkers::CheckForWin() {
    int nbWhitePieces = 0;
    int nbBlackPieces = 0;

    CountPieces(nbWhitePieces, nbBlackPieces);

    EndGameIfNoPieces(nbWhitePieces, nbBlackPieces);
    EndGameIfNoMoves();
}
void Checkers::CountPieces(int& whitePieces, int& blackPieces) const
{
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            auto piece = GetPiece(std::make_pair(i, j));
            if (piece == nullptr) continue;
            if (piece->GetSymbol() == GameConstants::CheckersConstants::WHITE) whitePieces++;
            else if (piece->GetSymbol() == GameConstants::CheckersConstants::BLACK) blackPieces++;
        }
    }
}
void Checkers::EndGameIfNoPieces(int whitePieces, int blackPieces)
{
    if (whitePieces == 0 || blackPieces == 0)
    {
        m_status.SetWinner((whitePieces == 0) ? GameConstants::CheckersConstants::BLACK : GameConstants::CheckersConstants::WHITE);
        m_flags.GameFinished();
    }
}
void Checkers::EndGameIfNoMoves()
{
    bool canMove = HavePieceWithCapturingMoves() || HavePieceWithNonCapturingMoves();
    if (!canMove)
    {
        m_status.SetWinner((GetCurrentPlayer()->GetId() == GameConstants::PLAYER_ONEID) ? 
            GameConstants::CheckersConstants::BLACK : GameConstants::CheckersConstants::WHITE);
        m_flags.GameFinished();
    }
}
void Checkers::SelectPiece(coord_t coord)
{
    // On teste si la piece est selectionnée
    if (m_flags.IsPieceSelected()) DeselectPiece();

    m_status.SetSelectedPiece(coord);
    auto possibleMoves = GetPossibleMoves(coord);
    m_status.SetPossibleMoves(possibleMoves);
    m_flags.PieceIsSelected();
}
void Checkers::DeselectPiece()
{
    m_status.SaveLastPossibleMoves();
    m_status.SaveLastSelectedPiece();
    m_flags.SelectPieceChanged();
    m_flags.PieceIsNotSelected();
    m_status.ResetSelectedPiece();
}

void Checkers::PerformMove(coord_t coord)
{
    if (!(IsMovePossible(coord) && m_flags.IsPieceSelected()))
        throw InvalidUsageException("Checkers::PerformMove() : IsMovePossible() or IsPieceSelected() is false");

    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::PerformMove() : coord are invalid");

    if (m_flags.IsCapturingMoveRequired() || m_flags.IsReplay())
    {
        if (IsCapturingMove(coord))
        {
            PerformCapturingMove(coord);

            m_flags.ResetCapturingMoveRequiredFlag();
        }
        else
        {
            //ShowErrorMessage("You must capture an opponent's piece");
            printf("You must capture an opponent's piece\n");
        }
    }
    else
    {
        PerformNonCapturingMove(coord);
    }
}

bool Checkers::HasCapturingMoves(coord_t coord) const
{
    auto piece = GetPiece(coord);
    if (piece == nullptr) return false;

    auto possibleCaptures = piece->GetPossibleCaptures();
    return !possibleCaptures.empty();
}

bool Checkers::IsCapturingMove(const coord_t coord) const
{
    auto piece = GetPiece(GetSelectedPiece());
    if (piece == nullptr) return false;

    auto possibleMoves = piece->GetPossibleMoves();

    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}

void Checkers::PerformCapturingMove(coord_t coord)
{
    auto piece = GetPiece(GetSelectedPiece());
    if (piece == nullptr) return;

    auto possibleCaptures = piece->GetPossibleCaptures();
    auto possibleMoves = piece->GetPossibleMoves();

    auto it = std::find(possibleMoves.begin(), possibleMoves.end(), coord);
    if (it == possibleMoves.end()) return;

    const auto index = std::distance(possibleMoves.begin(), it);
    const auto [captx, capty] = possibleCaptures[index];
    
    auto x = coord.first - captx;
    auto y = coord.second - capty;

    m_board->MovePiece(GetSelectedPiece(), coord);

    bool capt = false;
    while (!capt)
    {
        const auto& captureCoord = std::make_pair(x, y);
        const auto& pieceCapture = GetPiece(captureCoord);
        if (!AreCoordinatesValid(captureCoord)) throw InvalidCoordinatesException("Checkers::PerformCapturingMove() : captureCoord are invalid");

        if (pieceCapture == nullptr)
        {
            x -= captx;
            y -= capty;
            continue;
        }
        
        if (piece->GetSymbol() != pieceCapture->GetSymbol())
        {
            m_board->RemovePiece(captureCoord);
            capt = true;
        }
        else break;
    }

    if (CanPromotePiece(coord)) PromotePiece(coord);

    DeselectPiece();

    UpdatePossibleMoves();

    m_flags.PieceIsCaptured();

    // Si la piece peut encore capturer, on la selectionne
    if (m_flags.IsPieceCaptured() && HasCapturingMoves(coord))
    {
        SelectPiece(coord);
        m_flags.NeedReplay();
        m_flags.CapturingMoveRequired();
    }
    else m_flags.ResetReplayFlag();

    m_flags.BoardNeedUpdate();
}

void Checkers::PerformNonCapturingMove(coord_t coord)
{
    auto piece = GetPiece(GetSelectedPiece());
    if (piece == nullptr) return;

    auto possibleMoves = piece->GetPossibleMoves();

    auto it = std::find(possibleMoves.begin(), possibleMoves.end(), coord);
    if (it == possibleMoves.end()) return;

    m_board->MovePiece(GetSelectedPiece(), coord);

    if (CanPromotePiece(coord))
    {
        PromotePiece(coord);
    }

    DeselectPiece();

    UpdatePossibleMoves();

    m_flags.BoardNeedUpdate();
}

bool Checkers::HavePieceWithMoves(bool capturing) const
{
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            auto coord = std::make_pair(i, j);
            auto piece = GetPiece(coord);
            if (piece == nullptr) continue;
            if (piece->GetOwner() != GetCurrentPlayer()) continue;

            auto possibleMoves = capturing ? piece->GetPossibleCaptures() : piece->GetPossibleMoves();
            if (!possibleMoves.empty()) return true;
        }
    }

    return false;
}

bool Checkers::HavePieceWithCapturingMoves() const
{
    return HavePieceWithMoves(true);
}

bool Checkers::HavePieceWithNonCapturingMoves() const
{
    return HavePieceWithMoves(false);
}

bool Checkers::CanPromotePiece(coord_t coord) const
{  
    // Un pion devient une dame si il atteint la dernière ligne du plateau adverse
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::CanPromotePiece() : coord are invalid");

    auto piece = GetPiece(coord);

    if (piece->IsPromoted()) return false;
    if (piece == nullptr) return false;

    auto x = piece->GetX();

    if (piece->GetSymbol() == GameConstants::CheckersConstants::WHITE) return (x == GameConstants::BOARD_UPPER_LIMIT);
    else return (x == GameConstants::BOARD_LOWER_LIMIT);
}

void Checkers::PromotePiece(coord_t coord)
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::PromotePiece() : coord are invalid");

    auto piece = GetPiece(coord);

    piece->Promote();

    m_flags.BoardNeedUpdate();
}

void Checkers::Init()
{
    InitPlayers();
    InitBoard();
    UpdatePossibleMoves();
}

void Checkers::InitPlayers() {
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

void Checkers::InitBoard() {
    // On teste si le board est déjà initialisé
    if (m_board != nullptr) {
        m_board.reset();
    }
    // On teste si les joueurs sont bien initialisés
    if (m_players.empty()) {
        throw std::runtime_error("Checkers::InitBoard() : m_players is empty");
    }

    m_board = std::make_unique<CheckersBoard>(m_players);

    int row = m_board->GetRows();
    int col = m_board->GetCols();

    if (row != GameConstants::CheckersConstants::CHECKERSROWS || col != GameConstants::CheckersConstants::CHECKERSCOLS) {
        throw std::runtime_error("Checkers::InitBoard() : row and col have incorrect values");
    }
}

void Checkers::UpdatePossibleMoves() const
{
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            const auto& coord = std::make_pair(i, j);
            const auto& piece = GetPiece(coord);
            if (piece == nullptr) continue;
                
            piece->FindPossibleMoves(*m_board);
        }
    }
}

bool Checkers::AreCoordinatesValid(coord_t coord) const
{
    return coord.first >= 0 && coord.first < 10 && coord.second >= 0 && coord.second < 10;
}

void Checkers::GameStart()
{
    m_flags.GameStarted();
}

void Checkers::ResetCurrentPlayerChangedFlag()
{
    m_flags.ResetCurrentPlayerChangedFlag();
}
void Checkers::ResetSelectedPieceFlag()
{
    m_flags.ResetSelectedPieceFlag();
}
void Checkers::ResetBoardNeedUpdateFlag()
{
    m_flags.ResetBoardNeedUpdateFlag();;
}

std::shared_ptr<Player> Checkers::GetCurrentPlayer() const
{
    return m_status.GetCurrentPlayer();
}
CheckersPiece* Checkers::GetPiece(coord_t coord) const
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::GetPiece(): coord are invalid");

    return m_board->GetValueAt(coord);
}
char Checkers::GetWinner() const
{
    return m_status.GetWinner();
}

std::vector<coord_t> Checkers::GetPossibleMoves(coord_t coord) const
{
    return GetPiece(coord)->GetPossibleMoves();
}
std::unique_ptr<CheckersBoard>& Checkers::GetBoard()
{
    return m_board;
}
bool Checkers::IsGameStarted() const
{
    return m_flags.IsGameStarted();
}
bool Checkers::IsGameFinished() const
{
    return m_flags.IsGameFinished();
}
coord_t Checkers::GetSelectedPiece() const
{
    return m_status.GetSelectedPiece();
}
coord_t Checkers::GetLastSelectedPiece() const
{
    return m_status.GetLastSelectedPiece();
}
bool Checkers::IsPieceSelected() const
{
    return m_flags.IsPieceSelected();
}
bool Checkers::IsSelectedPieceChanged() const
{
    return m_flags.IsSelectedPieceChanged();
}
std::vector<coord_t> Checkers::GetLastPossibleMoves() const
{
    return m_status.GetLastPossibleMoves();
}
bool Checkers::IsBoardNeedUpdate() const
{
    return m_flags.IsBoardNeedUpdate();
}
bool Checkers::IsCurrentPlayerChanged() const
{
    return m_flags.IsCurrentPlayerChanged();
}