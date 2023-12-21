#include "../../../include/game/Butin/Butin.hpp"
#include "../../../include/GameType.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>

Butin::Butin() {}

Butin::~Butin() {}

// Method to check if it's the first round
    bool Butin::IsFirstRound() const {
        return m_flags.isFirstRound;
    }

    // Method to mark the end of the first round
    void Butin::EndFirstRound() {
        m_flags.isFirstRound = false;
    }


void Butin::Turn(std::pair<int, int> coord) {
    // On teste si la partie est déjà terminée
   
    // On teste si la partie n'est pas encore commencée
    if (!IsGameStarted()) {
        throw InvalidUsageException("Butin::Turn() : m_isGameStarted is false");
    }
    if (IsFirstRound())
    {
            HandleFirstRoundSelection(coord);
    } else {
                
                //HandlePieceSelection(coord);
                if (m_flags.m_isPieceSelected)
                    DeselectPiece();
                else{
                    SelectPiece(coord);
                    m_board->GetValueAt(coord.first,coord.second)->FindPossibleMoves(*m_board);
                    //TODO: Avoid multiple calls to FindPossibleMoves if used with select 
                    
                }
            }
  
    
}

void Butin::Init()
{
    InitPlayers();
    InitBoard();
    UpdatePossibleMoves();
}

void Butin::UpdatePossibleMoves() const
{
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            m_board->GetValueAt(i, j)->FindPossibleMoves(*m_board);
        }
    }
}



void Butin::InitPlayers() {
    // On teste si les joueurs sont déjà initialisés
    if (!m_players.empty()) {
        m_players.clear();
    }

    // On crée les joueurs
    m_players.push_back(std::make_shared<Player>(Players::PLAYER_ONE));
    m_players.push_back(std::make_shared<Player>(Players::PLAYER_TWO));
    m_players.push_back(std::make_shared<Player>(Players::NONE));

    // On définit le joueur courant
    m_currentPlayer = m_players[static_cast<int>(Players::PLAYER_ONE)];
}



void Butin::InitBoard() {
    // On teste si le board est déjà initialisé
    if (m_board != nullptr) {
        m_board.reset();
    }
    // On teste si les joueurs sont bien initialisés
    if (m_players.empty()) {
        throw std::runtime_error("Butin::InitBoard() : m_players is empty");
    }

    m_board = std::make_unique<ButinBoard>(m_players);

    int row = m_board->GetRows();
    int col = m_board->GetCols();

    if (row != 8 || col != 8) {
        throw std::runtime_error("Butin::InitBoard() : row and col have incorrect values");
    }
}

void Butin::GameStart()
{
    m_flags.m_isGameStarted = true;
}

void Butin_flagsmodel_t::BoardNeedUpdate()
{
    m_boardNeedUpdate = true;
}

void Butin::ResetBoardNeedUpdateFlag()
{
    m_flags.m_boardNeedUpdate = false;
}

std::shared_ptr<Player> Butin::GetCurrentPlayer() const
{
    return m_currentPlayer;
}

ButinPiece* Butin::GetPiece(std::pair<int, int> coord) const
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Butin::GetPiece(): coord are invalid");

    auto x = coord.first;
    auto y = coord.second;

    return m_board->GetValueAt(x, y);
}


std::unique_ptr<ButinBoard>& Butin::GetBoard()
{
    return m_board;
}

bool& Butin::IsGameStarted()
{
    return m_flags.m_isGameStarted;
}

bool Butin::IsBoardNeedUpdate() const
{
    return m_flags.m_boardNeedUpdate;
}

bool Butin::IsCurrentPlayerChanged() const
{
    return m_flags.m_currentPlayerChanged;
}


bool Butin::AreCoordinatesValid(std::pair<int, int> coord) const
{
    return coord.first >= 0 && coord.first < 10 && coord.second >= 0 && coord.second < 10;
}

void Butin::HandleFirstRoundSelection(const std::pair<int, int>& coords) {
    // Assuming GetPieceAt returns the color of the piece at given coordinates
    char pieceColor = m_board->GetValueAt(coords.first,coords.second)->GetSymbol();
    
    if (pieceColor == 'Y') { // 'Y' represents a yellow piece
        m_board->RemovePiece(coords.first,coords.second); // Remove the piece from the board
        m_currentPlayerIndex++; // Increment the current player index
        m_flags.BoardNeedUpdate();
        EndFirstRoundIfNeeded(); // Check if the first round should end
    }
}

void Butin::EndFirstRoundIfNeeded() {
    // Logic to check if all players have had their turn in the first round
    // This could be a counter that increments each time a player removes a yellow piece
    int numberOfPlayers=m_players.size();
   
   if(m_currentPlayerIndex >= numberOfPlayers){
        EndFirstRound();
        m_currentPlayerIndex = 1;
    }    
}
    

    std::vector<std::pair<int, int>> Butin::GetPossibleMoves(int x, int y) const
{   
    //UpdatePossibleMoves();
    return m_board->GetValueAt(x, y)->GetPossibleMoves();
}


void Butin::SelectPiece(std::pair<int, int> coord) {
    std::cout << "SelectPiece: " << coord.first << ", " << coord.second << std::endl;

    // Check if a piece is already selected
    if (m_flags.m_isPieceSelected) {
        DeselectPiece();
    }
    if(m_board->GetValueAt(coord.first, coord.second)->GetSymbol() != 'Y'){
        std::cout << "Not a yellow piece" << std::endl;
    }
    //UpdatePossibleMoves();

    // Assuming GetPossibleJumps returns the possible jumps for a yellow piece at the given coordinates
    m_status.m_currentPossibleMoves = GetPossibleMoves(coord.first, coord.second);
    //UpdatePossibleMoves();
    
    SetSelectedPiece(coord);
    m_flags.PieceIsSelected();
}

void Butin::DeselectPiece() {
    std::cout << "DeselectPiece" << std::endl;

    m_flags.SelectPieceChanged();
    m_flags.PieceIsNotSelected();
    SetSelectedPiece(std::make_pair(-1, -1));
}

// Helper methods to manage selected piece
void Butin::SetSelectedPiece(const std::pair<int, int>& coords) {
    m_status.m_selectedPiece = coords;
}


bool Butin::IsPieceSelected() const
{
    return m_flags.m_isPieceSelected;
}

bool Butin::IsSelectedPieceChanged() const
{
    return m_flags.m_selectedPieceChanged;
}


std::pair<int, int> Butin::GetSelectedPiece() const
{
    return m_status.m_selectedPiece;
}

void Butin_flagsmodel_t::PieceIsSelected()
{
    m_isPieceSelected = true;
}
void Butin_flagsmodel_t::PieceIsNotSelected()
{
    m_isPieceSelected = false;
}
void Butin_flagsmodel_t::CurrentPlayerChanged()
{
    m_currentPlayerChanged = true;
}
void Butin_flagsmodel_t::SelectPieceChanged()
{
    m_selectedPieceChanged = true;
}

std::pair<int, int> Butin::GetLastSelectedPiece() const
{
    return m_status.m_lastSelectedPiece;
}

std::vector<std::pair<int, int>> Butin::GetLastPossibleMoves() const
{
    return m_status.m_lastPossibleMoves;
}

void Butin::ResetSelectedPieceFlag()
{
    m_flags.m_selectedPieceChanged = false;
}