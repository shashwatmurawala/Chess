#include "game.h"

Game::Game (Board **b, GameManager *gm, Player *player1, Player *player2):
    move{0}, head{b}, gm{gm}, stack{}, white_king{-1, -1}, black_king{-1, -1}, player1{player1}, player2{player2} {}


Game::~Game () {
	delete gm;
    delete player1;
    delete player2;
}

char Game::pieceAt (int x, int y) {
    return (*head)->getTile(x, y);
}

std::pair<int, int> Game::getCoords() {
    std::string inp;
    std::pair<int, int> res {-1, -1};
    if (std::cin >> inp) {
   	 if (inp.length() != 2) return res;
	 res.first = inp[0] - 'a';
	 res.second = inp[1] - '1';
	 if (0 > res.first || res.first > 7) res.first = -1;
	 if (0 > res.second || res.second > 7) res.second = -1;
    }
    else {
    	out << "Could not interpret " << inp << std::endl;
    }
    return res;
}

void Game::removePiece () {
    std::string inp;
    std::pair<int, int> coords = getCoords();
    if (coords.first != -1 && coords.second != -1) {
        (*head)->setDead(coords.first, coords.second);
        char tile = this->pieceAt(coords.first, coords.second);
        if (tile == 'k') {
            white_king.first = -1;
            white_king.second = -1;
        }
        if (tile == 'K') {
            black_king.first = -1;
            black_king.second = -1;
        }
        if ('a' <= tile && tile <= 'z' && this->isCheck('w')) (*head)->setAlive (coords.first, coords.second);
        else if ('A' <= tile && tile <= 'Z' && this->isCheck('b')) (*head)->setAlive (coords.first, coords.second);
    }
    else out << "Invalid command " << inp << " use --help for more options" << std::endl;
}

void Game::placePiece () {
    // big fat ugly function to create pieces
    std::string inp;
    if (std::cin >> inp) {
        if (inp == "k" && (white_king.first != -1 && white_king.second != -1)) {
            out << "White king already placed" << std::endl;
            return;
        }
        if (inp == "K" && (black_king.first != -1 && black_king.second != -1)) {
            out << "Black king already placed" << std::endl;
            return;
        }
        if (inp == "K") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new King {*head, coords.first, coords.second, 'b'};
                    // if in check undo this
                    if (this->isCheck('b')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "The king cannot be placed in check" << std::endl;
                    }
                    else {
                        this->black_king.first = coords.first;
                        this->black_king.second = coords.second;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        else if (inp == "k") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new King {*head, coords.first, coords.second, 'w'};
                    // if in check undo this
                    if (this->isCheck('w')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "The king cannot be placed in check" << std::endl;
                    }
                    else {
                        this->white_king.first = coords.first;
                        this->white_king.second = coords.second;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        // queen case
        else if (inp == "Q") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Queen {*head, coords.first, coords.second, 'b'};
                    // if in check undo this
                    if (this->isCheck('w')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        else if (inp == "q") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Queen {*head, coords.first, coords.second, 'w'};
                    // if in check undo this
                    if (this->isCheck('b')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        // bishop case
        else if (inp == "B") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Bishop {*head, coords.first, coords.second, 'b'};
                    // if in check undo this
                    if (this->isCheck('w')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        else if (inp == "b") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Bishop {*head, coords.first, coords.second, 'w'};
                    // if in check undo this
                    if (this->isCheck('b')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        // knight case
        else if (inp == "N") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Knight {*head, coords.first, coords.second, 'b'};
                    // if in check undo this
                    if (this->isCheck('w')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        else if (inp == "n") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Knight {*head, coords.first, coords.second, 'w'};
                    // if in check undo this
                    if (this->isCheck('b')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        // rook case
        else if (inp == "R") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Rook {*head, coords.first, coords.second, 'b'};
                    // if in check undo this
                    if (this->isCheck('w')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        else if (inp == "r") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Rook {*head, coords.first, coords.second, 'w'};
                    // if in check undo this
                    if (this->isCheck('b')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        // pawn case
        else if (inp == "P") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1 && coords.second != 0) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Pawn {*head, coords.first, coords.second, 'b'};
                    // if in check undo this
                    if (this->isCheck('w')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
        else if (inp == "p") {
            std::pair<int, int> coords = getCoords();
            if (coords.first != -1 && coords.second != -1 && coords.second != 7) {
                char tile = this->pieceAt(coords.first, coords.second);
                if (tile == ' ' || tile == '_') {
                    *head = new Pawn {*head, coords.first, coords.second, 'w'};
                    // if in check undo this
                    if (this->isCheck('b')) {
                        (*head)->setDead(coords.first, coords.second);
                        out << "Cannot place piece that would put the king in check" << std::endl;
                    }
                }
                else {out << "A piece already occupies this tile"  << std::endl;}
            }
            else {out << "Invalid command " << inp << " use --help for more options" << std::endl;}
        }
    }
    else {
        out << "Fatal error" << std::endl;
    }
}

void Game::defaultSetup () {
    // setup white pieces
    for (int i = 0; i < 8; i++) {
        *head = new Pawn {*head, i, 1, 'w'};
    }
    *head = new Rook {*head, 0, 0, 'w'};
    *head = new Rook {*head, 7, 0, 'w'};
    *head = new Knight {*head, 1, 0, 'w'};
    *head = new Knight {*head, 6, 0, 'w'};
    *head = new Bishop {*head, 2, 0, 'w'};
    *head = new Bishop {*head, 5, 0, 'w'};
    *head = new Queen {*head, 4, 0, 'w'};
    *head = new King {*head, 3, 0, 'w'};
    white_king.first = 3;
    white_king.second = 0;
    // setup black pieces
    for (int i = 0; i < 8; i++) {
        *head = new Pawn {*head, i, 6, 'b'};
    }
    *head = new Rook {*head, 0, 7, 'b'};
    *head = new Rook {*head, 7, 7, 'b'};
    *head = new Knight {*head, 1, 7, 'b'};
    *head = new Knight {*head, 6, 7, 'b'};
    *head = new Bishop {*head, 2, 7, 'b'};
    *head = new Bishop {*head, 5, 7, 'b'};
    *head = new Queen {*head, 4, 7, 'b'};
    *head = new King {*head, 3, 7, 'b'};
    black_king.first = 3;
    black_king.second = 7;
    out << "Board default constructed" << std::endl;
    gm->displayBoard();
}

void Game::customSetup () {
    gm->displayBoard();
    std::string inp;
    while (std::cin >> inp) {
        if (inp == "--help") {
            out << " + <piece> <coordinate>" << std::endl;
            out << "\t - <piece> is one of K, k, Q, q, B, b, N, n, R, r, P, p" << std::endl;
            out << "\t - <coordinate> is composed of a letter a-h and number 1-8" << std::endl;
            out << " - <piece> <coordinate>" << std::endl;
            out << " = <colour>" << std::endl;
            out << "\t - where <colour> is either <white> or <black>" << std::endl;
            out << "done" << std::endl;
            out << "\t - to leave setup mode (can only be performed if setup is valid" << std::endl;
        }
        else if (inp == "+") {
                this->placePiece();
                gm->displayBoard();
        }
        else if (inp == "-"){
            this->removePiece();
            gm->displayBoard();
        }
        else if (inp == "=") {
            if (std::cin >> inp) {
                if (inp == "white") {
                    out << "White's turn to begin the game" << std::endl;
                    move = 0;
                }
                else if (inp == "black") {
                    out << "Black's turn to begin the game" << std::endl;
                    move = 1;
                }
                else {
                    out << inp << " not one of <white> or <black>" << std::endl;
                }
            }
        }
        else if (inp == "done") {
            out << "Custom setup finished" << std::endl;
            if (black_king.first == -1 || black_king.second == -1) {
                out << "Cannot exit - Black King not placed" << std::endl;
                gm->displayBoard();
            }
            else if (white_king.first == -1 || white_king.second == -1) {
                out << "Cannot exist - White King is not placed" << std::endl;
                gm->displayBoard();
            }
            else return;
        }
        else {
            out << "Invalid command " << inp << " use --help to display options." << std::endl;
            gm->displayBoard();
        }
    }
}

void Game::setAlive (int x1, int y1) {
    return (*head)->setAlive(x1, y1);
}

void Game::setDead (int x1, int y1) {
    return (*head)->setDead(x1, y1);
}

bool Game::pawnValidMove(int x1, int y1, int x2, int y2) {
    char team = (*head)->getTeam(x1, y1);
    char targ = (*head)->getTile(x2, y2);
    int dir = 1;
    if (team == 'b') dir = -1;
    if ((x2 - x1 == 0) && (y1 + dir + dir == y2) && (*head)->getFirstMove(x1, y1)) { // double pawn first mov
        this->setDead(x2, y2);
        (*head)->move(x1, y1, x2, y2);
        if (this->isCheck(team)) {
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return false;
        }
        if (targ == 'k' || targ == 'K'){
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return true;
        }
    }
    else if (x2 - x1 == 0 && (y1 + dir == y2)) { // normal pawn move
        this->setDead(x2, y2);
        (*head)->move(x1, y1, x2, y2); 
        if (this->isCheck(team)) {
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return false;
        }
        if (targ == 'k' || targ == 'K'){
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return true;
        }
    }
    else if ((x2 - x1 == 1 || x2 - x1 == -1) && (y1 + dir == y2) && ((*head)->getTile(x2, y2) != ' ')) { // diagonal pawn move
        this->setDead(x2, y2);
        (*head)->move(x1, y1, x2, y2);
        if (this->isCheck(team)) {
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return false;
        }
        if (targ == 'k' || targ == 'K'){
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return true;
        }
    }
    else {
        return false;
    }
    if ((team == 'B' && y2 == 0) || (team == 'w' && y2 == 7)) {
        std::string inp;
        while (std::cin >> inp) {
            if (inp == "Q") {
                this->setDead(x2, y2);
                *head = new Queen {*head, x2, y2, team};
                break;
            }
            else if (inp == "R") {
                this->setDead(x2, y2);
                *head = new Queen {*head, x2, y2, team};
                break;
            }
            else if (inp == "B") {
                this->setDead(x2, y2);
                *head = new Queen {*head, x2, y2, team};
                break;
            }
            else if (inp == "N") {
                this->setDead(x2, y2);
                *head = new Queen {*head, x2, y2, team};
                break;
            }
            else {
                out << "Invalid piece " << inp << " ensure the piece you enter is capitalized" << std::endl;
            }
        }
    }
    (*head)->setFirstMove(x2, y2);
    return true;
}

bool Game::rookValidMove(int x1, int y1, int x2, int y2) {
    char team = (*head)->getTeam(x1, y1);
    char targ = (*head)->getTile(x2, y2);   
    int newX = x2 - x1;
    int newY = y2 - y1;

    if ((newX == 0 && newY != 0) || (newY == 0 && newX != 0)) {
        int delta_x = -1;
        int delta_y = -1;
        if (newX == 0) delta_x = 0;
        else if (newY == 0) delta_y = 0;
        if (newX > 0) delta_x = 1;
        else if (newY > 0) delta_y = 1;
        for (int l = 1; ; l++) {
            int i = x1 + (l * delta_x);
            int j = y1 + (l * delta_y);
            if ((i == x2 && y1 == y2 ) || (j == y2 && x1 == x2)) break;
            char tile = (*head)->getTile(i, j);
            if ((tile != ' ' && tile != '_') && (i != x1 || j != y1)) {
                return false;
            }
        }
        this->setDead(x2, y2);
        (*head)->move(x1, y1, x2, y2);
        if (this->isCheck(team)) {
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return false;
        }
        if (targ == 'k' || targ == 'K'){
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return true;
        }
        (*head)->setFirstMove(x2, y2);
        return true;
    }
    return false;
}
bool Game::knightValidMove(int x1, int y1, int x2, int y2) {
    char team = (*head)->getTeam(x1, y1);
    char targ = (*head)->getTile(x2, y2);
    int newX = x2 - x1;
    int newY = y2 - y1;
    if ((newX == 1 || newX == -1) && (newY == 2 || newY == -2)) {
        this->setDead(x2, y2);
        (*head)->move(x1, y1, x2, y2);
        if (this->isCheck(team)) {
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            
            return false;
        }
        if (targ == 'k' || targ == 'K'){
            (*head)->move(x2, y2, x1, y1);
            (*head)->setAlive(x2, y2);
            return true;
        }
        (*head)->setFirstMove(x2, y2);
        return true;
    }
    else if ((newX == 2 || newX == -2) && (newY == 1 || newY == -1)) {
        this->setDead(x2, y2);
        (*head)->move(x1, y1, x2, y2);
        if (this->isCheck(team)) {
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            
            return false;
        }
        if (targ == 'k' || targ == 'K'){
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return true;
        }
        (*head)->setFirstMove(x2, y2);
        return true;
    }
    else return false;
}

bool Game::bishopValidMove(int x1, int y1, int x2, int y2) {
    char team = (*head)->getTeam(x1, y1);
    char targ = (*head)->getTile(x2, y2);
    int newX = x2 - x1;
    int newY = y2 - y1;

    int dist = newX;
    if (dist < 0) dist *= -1;

    if (newX != -newY && newX != newY) {
        return false;
    }
    else {
        int delta_x = 1;
        if (newX < 0) delta_x = -1;
        int delta_y = 1;
        if (newY < 0) delta_y = -1;
        for (int i = x1; i != x2; i += delta_x) {
            int j = i - delta_x - x1 + y1 + delta_y;
            char tile = (*head)->getTile(i, j);
            if (tile != ' ' && tile != '_' && i != x1 && j != y1) {
                return false;
            }
        }
        this->setDead(x2, y2);
        (*head)->move(x1, y1, x2, y2);
        if (this->isCheck(team)) {
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            
            return false;
        }
        if (targ == 'k' || targ == 'K'){
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return true;
        }
        (*head)->setFirstMove(x2, y2);
        return true;
    }
}

bool Game::queenValidMove(int x1, int y1, int x2, int y2) {
    return this->rookValidMove(x1, y1, x2, y2) || this->bishopValidMove(x1, y1, x2, y2);
    
}
bool Game::kingValidMove(int x1, int y1, int x2, int y2, bool castle) {
    char team = (*head)->getTeam(x1, y1);
    int newX = x2 - x1;
    int newY = y2 - y1;

    if (castle && (y1 == y2) && (*head)->getFirstMove(x1, y1) && (*head)->getFirstMove(x2, y2)){ // handles castling
        int dir = -1;
        if (newX < 0) dir = 1;
        for (int i = x1; x1 != x2; i += dir){
            if ((*head)->getTile(i, y1) != ' ') return false;
        }
        (*head)->move(x2, y2, -1, -1);
        (*head)->move(x1, y1, x2 - dir, y2);
        if (this->isCheck(team)) {
            (*head)->move(x2, y2, x1, y1);
            (*head)->move(-1, -1, x2, y2);
            this->setAlive(x2, y2);
            return false;
        }
        (*head)->move(-1, -1, x1 + dir, y1);
        (*head)->setFirstMove(x2, y2);
        return true;
    }
    if (newX < 0) newX *= -1;
    if (newY < 0) newY *= -1;

    if ((newX == 0 || newX == 1) && (newY == 0 || newY == 1)) {
        this->setDead(x2, y2);
        (*head)->move(x1, y1, x2, y2);
        if (this->isCheck(team)) {
            (*head)->move(x2, y2, x1, y1);
            this->setAlive(x2, y2);
            return false;
        }
        (*head)->setFirstMove(x2, y2);
	    return true;
    }
    else return false;
}

bool Game::validMove (int x1, int y1, int x2, int y2) {
    if (0 > x1 || x1 > col || 0 > y1 || y1 > row || 0 > x2 || x2 > col || 0 > y2 || y2 > row) {
        return false;
    }
    char piece1 = (*head)->getTile(x1, y1);
    char piece2 = (*head)->getTile(x2, y2);
    char team1 = (*head)->getTeam(x1, y1);
    char team2 = (*head)->getTeam(x2, y2);

    if (piece1 == 'k' && piece2 == 'r'){
        return kingValidMove(x1, y1, x2, y2, true);
    }
    else if (piece1 == 'K' && piece2 == 'R') {
        return kingValidMove(x1, y1, x2, y2, true);
    }
    if ((team1 == team2) || (move % 2 == 0 && team1 != 'w') || (move % 2 == 1 && team1 != 'b'))  {
        return false;
    }
    char piece = (*head)->getTile(x1, y1);
    if (piece == 'P' || piece == 'p') {
        return pawnValidMove(x1, y1, x2, y2);
    }
    else if (piece == 'R' || piece == 'r') {
        return rookValidMove(x1, y1, x2, y2);
    }
    else if (piece == 'B' || piece == 'b') {
        return bishopValidMove(x1, y1, x2, y2);
    }
    else if (piece == 'N' || piece == 'n') {
        return knightValidMove(x1, y1, x2, y2); 
    }
    else if (piece == 'Q' || piece == 'q') {
        return queenValidMove(x1, y1, x2, y2);
    }
    else if (piece == 'K' || piece == 'k') {
        return kingValidMove(x1, y1, x2, y2);
    }
    else {
        return false;
    }
}

bool Game::isCheck (char team) {
    int x = -1;
    int y = -1;
    if (team == 'w') {
        x = white_king.first;
        y = white_king.second;
    }
    else {
        x = black_king.first;
        y = black_king.second;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            char tile = (*head)->getTeam(j, i);
            if (tile != ' ' && tile != '_' && tile != team) {
                if (this->validMove(j, i, x, y)) {
                    return true;
                }
                else {
                    move++;
                    if (this->validMove(j, i, x, y)) {
                        move--;
                        return true;
                    }
                    move--;
                }
            }
        }
    }
    return false;
}

bool Game::isStalemate(char team) {
    return false;
    if (team == 'w') move = 0;
    else if (team == 'b') move = 1;
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            for (int k = 0; k < row; k++){
                for (int l  = 0; l < col; l++){
                    out << "i=" << i << " j=" << j << " k=" << k << " l=" << l << std::endl;
                    char tile = (*head)->getTile(l, k);
                    if (tile != ' ' && tile != ' ' && tile == team) {
                        if (this->validMove(l, k, j, i)) {
                            return false;
                        }
                        else {
                            move++;
                            if (this->validMove(l, k, j, i)) {
                                move--;
                                return false;
                            }
                            move--;
                        }
                    }
                }   
            }
        }
    }
    return true;
}

bool Game::isCheckmate (char team) {
    return isCheck(team) && isStalemate(team);
}

void Game::playGame () {
    out << "The game has started. Use  --help to display options" << std::endl;
    std::string inp;
    while (true) {
	Player *player;
        if (move % 2 == 0) {
            player = player1;
            out << "White's turn" << std::endl;
        }
        else if (move % 2 == 1) {
        	player = player2;
            out << "Black's turn" << std::endl;
        } 
        if (std::cin >> inp) {
            if (inp == "move") {
                std::pair<int, int> piece = player->getMove();
                std::pair<int, int> newMove = player->getMove();
                bool res = this->validMove(piece.first, piece.second, newMove.first, newMove.second);
                if (!res) {
                    out << "Invalid move" << std::endl;
                }
                else {
                    move++;
                    std::pair<std::pair<int,int>, std::pair<int,int>> *fullMove = new std::pair<std::pair<int,int>, std::pair<int,int>> {piece, newMove};
                    stack.push(fullMove);
                    gm->displayBoard();
                    if (this->isCheckmate('w')) {
                        out << "Black checkmates White!" << std::endl;
                        move = 0;
                        increaseBlack();
                        return;
                    }
                    else if (this->isCheckmate('b')) {
                        out << "White checkmates Black!" << std::endl;
                        move = 0;
                        increaseWhite();
                        return;
                    }
                    else if (this->isCheck('w')){
                        out << "Black checks White!" << std::endl;
                    }
                    else if (this->isCheck('b')) {
                        out << "White checks Black!" << std::endl;
                    }
                    else if (this->isStalemate('w')) {
                        out << "Stalemate on White move!" << std::endl;
                        move = 0;
                        return;
                    }
                    else if (this->isStalemate('b')) {
                        out << "Stalemate on Black move!" << std::endl;
                        move = 0;
                        return;
                    }
                }
            }
            else if (inp == "resign") {
                if (move % 2 == 0) {
                    out << "White has resigned" << std::endl;
                    move = 0;
                    increaseBlack();
                    return;
                }
                else {
                    out << "Black has resigned" << std::endl;
                    move = 0;
                    increaseWhite();
                    return;
                }
            }
            else if (inp == "undo") {
                if (stack.length() == 0) {
                    out << "No previous move" << std::endl;
                    continue;
                }
                else if ((move + 1) % 2 == 0) {
                    out << "undoing White's move" << std::endl;
                }
                else {
                    out << "undoing Black's move" << std::endl;
                    
                }
                std::pair<std::pair<int,int>, std::pair<int,int>> *oldMove = stack.pop();
                (*head)->move((*oldMove).second.first, (*oldMove).second.second, (*oldMove).first.first, (*oldMove).first.second);
                (*head)->setAlive((*oldMove).first.first, (*oldMove).first.second);
                move++;
                gm->displayBoard();
            }
            else if (inp == "--help") {
                out << "Commands:" << std::endl;
                out << "- move <coordinate> <coordinate>" << std::endl;
                out << "\twhere <coordinate> is composed of a letter a-h and number 1-8" << std::endl;
                out << " - resign" << std::endl;
                out << " - undo" << std::endl;
            }
            else {
                out << " Invalid input " << inp << " use --help for more options" << std::endl; 
            }
        }
	else {
		out << "Fatal Error" << std::endl;
      		move = 0;
        	return;
	}
    }
}

void Game::setPlayer1 (Player *p){
    player1 = p;
}

void Game::setPlayer2 (Player *p) {
    player2 = p;
}

int Game::getWhite(){
    return white_score;
}

int Game::getBlack(){
    return black_score;
}

void Game::increaseWhite(){
    ++white_score;
}

void Game::increaseBlack(){
    ++black_score;
}
