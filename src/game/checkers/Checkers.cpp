#include "../../../include/game/checkers/Checkers.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>
#include <random>

Checkers::Checkers() {}

Checkers::~Checkers() {}

void Checkers::SwitchPlayer() {
    if (m_currentPlayer == m_players[CheckersConstants::PLAYER_ONEID])
        m_currentPlayer = m_players[CheckersConstants::PLAYER_TWOID];
    else m_currentPlayer = m_players[CheckersConstants::PLAYER_ONEID];

    m_flags.CurrentPlayerChanged();
}

void Checkers::Turn(coord_t coord) {
    // On teste si la partie est déjà terminée
    if (IsGameFinished()) {
        throw InvalidUsageException("Checkers::Turn() : m_isGameFinished is true");
    }
    // On teste si la partie n'est pas encore commencée
    if (!IsGameStarted()) {
        throw InvalidUsageException("Checkers::Turn() : m_isGameStarted is false");
    }
    // On teste si les coordonnées sont valides
    if (!AreCoordinatesValid(coord)) {
        throw InvalidCoordinatesException("Checkers::Turn() : coord are invalid");
    }

    // Si la coordonnée est une piece du joueur courant
    if (IsPieceOfCurrentPlayer(coord)) {
        SelectPiece(coord);
    }
    else if (IsMovePossible(coord) && IsPieceSelected())
    {
        // Si le mouvement est possible alors on déplace la piece
        ApplyMove(coord);

        // On teste si la partie est terminée
        CheckForWin();

        // On change de joueur si aucune piece n'a été capturée
        if (!m_flags.m_isPieceCaptured)
            SwitchPlayer();

        // On reset le flag de piece capturée
        m_flags.ResetPieceCapturedFlag();
    }
    else {
        if (m_flags.m_isPieceSelected)
            DeselectPiece();
    }
}

bool Checkers::IsPieceOfCurrentPlayer(coord_t coord) const
{
    auto piece = GetPiece(coord);
    auto idCurrentPlayer = m_currentPlayer->GetId();

    auto pieceOwner = piece->GetOwner();
    if (pieceOwner == nullptr) return false;
    auto idPieceOwner = pieceOwner->GetId();

    return idCurrentPlayer == idPieceOwner;
}

bool Checkers::IsMovePossible(coord_t coord) const
{
    // On teste si la piece est selectionnée
    if (!IsPieceSelected()) {
        return false;
    }

    // On teste si la piece peut se déplacer à la coordonnée
    auto possibleMoves = GetPossibleMoves(m_status.m_selectedPiece);
    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}

void Checkers::CheckForWin() {
    // TODO
    // Simple solution pour tester la fin de partie
    // On compte les pieces de chaque joueur
    // Si un joueur n'a plus de pieces, il a perdu

    int nbWhitePieces = 0;
    int nbBlackPieces = 0;

    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            auto piece = GetPiece(std::make_pair(i, j));
            if (piece->GetSymbol() == CheckersConstants::WHITE) nbWhitePieces++;
            else if (piece->GetSymbol() == CheckersConstants::BLACK) nbBlackPieces++;
        }
    }

    if (nbWhitePieces == 0 || nbBlackPieces == 0)
    {
        m_status.m_winner = (nbWhitePieces == 0) ? CheckersConstants::BLACK : CheckersConstants::WHITE;
        m_flags.GameFinished();
    }
}

void Checkers::SelectPiece(coord_t coord)
{
    std::cout << "SelectPiece: " << coord.first << ", " << coord.second << std::endl;

    // On teste si la piece est selectionnée
    if (m_flags.m_isPieceSelected) {
        DeselectPiece();
    }

    m_status.SetSelectedPiece(coord);
    auto possibleMoves = GetPossibleMoves(coord);
    m_status.SetPossibleMoves(possibleMoves);
    m_flags.PieceIsSelected();
}
void Checkers::DeselectPiece()
{
    std::cout << "DeselectPiece" << std::endl;

    m_status.SaveLastPossibleMoves();
    m_status.SaveLastSelectedPiece();
    m_flags.SelectPieceChanged();
    m_flags.PieceIsNotSelected();
    m_status.ResetSelectedPiece();
}
void Checkers::ApplyMove(coord_t coord)
{
    // On teste si la piece est selectionnée
    if (!IsPieceSelected())
    {
        throw InvalidCoordinatesException("Checkers::ApplyMove() : m_selectedPiece is invalid");
    }
    
    // On teste si le mouvement est possible
    if (!IsMovePossible(coord))
    {
        return;
    }

    // On déplace la piece
    m_board->MovePiece(m_status.m_selectedPiece, coord);

    // Si il y a une capture, on supprime la piece capturée
    // Le joueur courant peut rejouer avec la meme piece
    if (CheckCapture(coord))
    {
        m_flags.m_isPieceCaptured = true;
    }

    // Si la piece est un pion, on teste si elle peut se promouvoir
    if (CanPromotePiece(coord))
    {
        PromotePiece(coord);
    }
     
    DeselectPiece();
    
    // On met à jour les mouvements possibles
    UpdatePossibleMoves();

    m_flags.BoardNeedUpdate();
}

bool Checkers::CheckCapture(coord_t coord)
{
    bool capt = false;

    const auto& piece = GetPiece(coord);
    const auto& possibleCaptures = piece->GetPossibleCaptures();
    
    if (possibleCaptures.empty()) return false;

    for (const auto& [captx, capty]: possibleCaptures)
    {
        int x = coord.first - captx;
        int y = coord.second - capty;

        while (!capt)
        {
            const auto& c = std::make_pair(x, y);
            const auto& pieceCapture = GetPiece(c);;
            if (!AreCoordinatesValid(c) || pieceCapture->GetSymbol() == piece->GetSymbol()) break;

            if (pieceCapture->GetSymbol() == CheckersConstants::TRANSPARENT)
            {
                x -= captx;
                y -= capty;
                continue;
            }
            
            if (piece->GetSymbol() != pieceCapture->GetSymbol())
            {
                CapturePiece(c);
                capt = true;
            }
        }
    }

    return capt;
}
void Checkers::CapturePiece(coord_t coord)
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::CapturePiece() : coord are invalid");

    m_board->RemovePiece(coord);
}

bool Checkers::CanPromotePiece(coord_t coord) const
{  
    // Un pion devient une dame si il atteint la dernière ligne du plateau adverse
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::CanPromotePiece() : coord are invalid");

    auto piece = GetPiece(coord);

    if (piece->IsPromoted()) return false;
    if (piece->GetSymbol() == CheckersConstants::TRANSPARENT) return false;

    auto x = piece->GetX();

    if (piece->GetSymbol() == CheckersConstants::WHITE) return (x == CheckersConstants::BOARD_UPPER_LIMIT);
    else return (x == CheckersConstants::BOARD_LOWER_LIMIT);
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
    m_currentPlayer = m_players[CheckersConstants::PLAYER_ONEID];

    // Solution pour choisir un joueur au hasard
    /*std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, 1);
    int random = dis(g);

    m_currentPlayer = m_players[random];*/
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

    if (row != 10 || col != 10) {
        throw std::runtime_error("Checkers::InitBoard() : row and col have incorrect values");
    }

    // debug
    GetPiece(std::make_pair(3, 2))->Promote();
    //
}

void Checkers::UpdatePossibleMoves() const
{
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            const auto& coord = std::make_pair(i, j);
            m_board->GetValueAt(coord)->FindPossibleMoves(*m_board);
        }
    }
}

void Checkers::GameStart()
{
    m_flags.GameStarted();
}

void flagsmodel_t::PieceIsSelected()
{
    m_isPieceSelected = true;
}
void flagsmodel_t::PieceIsNotSelected()
{
    m_isPieceSelected = false;
}
void flagsmodel_t::CurrentPlayerChanged()
{
    m_currentPlayerChanged = true;
}
void flagsmodel_t::SelectPieceChanged()
{
    m_selectedPieceChanged = true;
}
void flagsmodel_t::BoardNeedUpdate()
{
    m_boardNeedUpdate = true;
}
void flagsmodel_t::GameStarted()
{
    m_isGameStarted = true;
}
void flagsmodel_t::GameFinished()
{
    m_isGameFinished = true;
}

void Checkers::ResetCurrentPlayerChangedFlag()
{
    m_flags.m_currentPlayerChanged = false;
}
void flagsmodel_t::ResetPieceCapturedFlag()
{
    m_isPieceCaptured = false;
}
void Checkers::ResetSelectedPieceFlag()
{
    m_flags.m_selectedPieceChanged = false;
}
void Checkers::ResetBoardNeedUpdateFlag()
{
    m_flags.m_boardNeedUpdate = false;
}

bool Checkers::AreCoordinatesValid(coord_t coord) const
{
    return coord.first >= 0 && coord.first < 10 && coord.second >= 0 && coord.second < 10;
}

std::shared_ptr<Player> Checkers::GetCurrentPlayer() const
{
    return m_currentPlayer;
}
CheckersPiece* Checkers::GetPiece(coord_t coord) const
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::GetPiece(): coord are invalid");

    return m_board->GetValueAt(coord);
}
char Checkers::GetWinner() const
{
    return m_status.m_winner;
}

std::vector<coord_t> Checkers::GetPossibleMoves(coord_t coord) const
{
    return m_board->GetValueAt(coord)->GetPossibleMoves();
}
std::unique_ptr<CheckersBoard>& Checkers::GetBoard()
{
    return m_board;
}
bool& Checkers::IsGameStarted()
{
    return m_flags.m_isGameStarted;
}
coord_t Checkers::GetSelectedPiece() const
{
    return m_status.m_selectedPiece;
}
coord_t Checkers::GetLastSelectedPiece() const
{
    return m_status.m_lastSelectedPiece;
}
bool Checkers::IsPieceSelected() const
{
    return m_flags.m_isPieceSelected;
}
bool Checkers::IsSelectedPieceChanged() const
{
    return m_flags.m_selectedPieceChanged;
}
std::vector<coord_t> Checkers::GetLastPossibleMoves() const
{
    return m_status.m_lastPossibleMoves;
}
bool& Checkers::IsGameFinished()
{
    return m_flags.m_isGameFinished;
}
bool Checkers::IsBoardNeedUpdate() const
{
    return m_flags.m_boardNeedUpdate;
}
bool Checkers::IsCurrentPlayerChanged() const
{
    return m_flags.m_currentPlayerChanged;
}