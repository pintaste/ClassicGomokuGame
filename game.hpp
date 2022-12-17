#pragma once
#include <vector>
#include <string>
#include <climits>

using std::pair;
using std::vector;
using std::string;

const int BOARD_SIZE = 15; // board size = 15 * 15
const char FLAG_EMPTY = '_';
const char FLAG_BLACK = 'x';
const char FLAG_WHITE = 'o';
const char FLAG_OVER = 'g';

class Game
{
private:
    char game_type;                     // '1'=PVP, '2'=PVA, '3'=AVA
    char game_state;                    // store the next turn: 'x'=Black, 'o'=White, 'g'=Game over
    char player_type[2];                // [0] is black,[1] is white. ='h' is human, ='a' is AI
    char board[BOARD_SIZE][BOARD_SIZE]; // store the stone information
    vector<pair<int, int>> history[2];  // store the position of stone
    vector<vector<int>> score;          // store the score of each position

    // minimax algorithm
    int evaluate(const char &player)
    {
        // init the score array
        score.clear();
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            vector<int> tmp;
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                tmp.push_back(0);
            }
            score.push_back(tmp);
        }
        // calculate the score
        int score = 0;
        for (int row = 0; row < BOARD_SIZE; row++)
        {
            for (int col = 0; col < BOARD_SIZE; col++)
            {
                // check the score in row

                // check the score in col

                // check the score in the diagonal

                // check the score in the reverse-diagonal
                
            }
        }

        return -1;
    }
    int minimax(const char &c, int row, int col, int depth)
    {
        if (depth == 0 || is_winner(c, row, col) == true)
        {
            return evaluate(c);
        }

        if (c == FLAG_BLACK)
        {
            int maxEval = INT_MIN;
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    if (board[i][j] == FLAG_EMPTY)
                    {
                        board[i][j] = c;
                        row = i, col = j;
                        int eval = minimax(FLAG_WHITE, row, col, depth - 1);
                        maxEval = std::max(maxEval, eval);
                        board[i][j] = FLAG_EMPTY;
                    }
                }
            }
            return maxEval;
        }
        else
        { // player2 is min player
            int minEval = INT_MAX;
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    if (board[i][j] == FLAG_EMPTY)
                    {
                        board[i][j] = c;
                        row = i, col = j;
                        int eval = minimax(FLAG_BLACK, row, col, depth - 1);
                        minEval = std::min(minEval, eval);
                        board[i][j] = FLAG_EMPTY;
                    }
                }
            }
            return minEval;
        }
    }

public:
    Game(const char &type)
    {
        init_game(type);
    }
    void init_game(const char &type)
    {
        game_type = type;
        game_state = FLAG_BLACK; // BLACK is the first player
        // init the board
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                board[i][j] = FLAG_EMPTY;
            }
        }
        // init the history
        history[0].clear();
        history[1].clear();
        // init the palyer type
        if (type == '1')
        {
            player_type[0] = 'h';
            player_type[1] = 'h';
        }
        else if (type == '2')
        {
            player_type[0] = 'h';
            player_type[1] = 'a';
        }
        else if (type == '3')
        {
            player_type[0] = 'a';
            player_type[1] = 'a';
        }
    }
    bool is_winner(const char &c, const int &row, const int &col)
    {
        // TODO: optimization: reduce the comparison times

        // determine the boundary row
        int count, row_start, row_end, col_start, col_end;
        if (row - 4 <= 0)
        {
            row_start = 0;
            row_end = row + 4;
        }
        else if (row >= BOARD_SIZE - 4)
        {
            row_start = row - 4;
            row_end = BOARD_SIZE - 1;
        }
        else
        {
            row_start = row - 4;
            row_end = row + 4;
        }
        // determine the boundary coloum
        if (col - 4 <= 0)
        {
            col_start = 0;
            col_end = col + 4;
        }
        else if (col >= BOARD_SIZE - 4)
        {
            col_start = col - 4;
            col_end = BOARD_SIZE - 1;
        }
        else
        {
            col_start = col - 4;
            col_end = col + 4;
        }

        // 1. check is five in row
        count = 0;
        for (int i = col_start; i <= col_end; i++)
        {
            if (board[row][i] == c)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if (count == 5)
            {
                game_state = 'g';
                return true;
            }
        }
        // 2. check is five in col
        count = 0;
        for (int i = row_start; i <= row_end; i++)
        {
            if (board[i][col] == c)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if (count == 5)
            {
                game_state = 'g';
                return true;
            }
        }
        // 3. check is five in diagonal
        count = 0;
        for (int i = row_start, j = col_start; i <= row_end && j <= col_end; i++, j++)
        {
            if (board[i][j] == c)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if (count == 5)
            {
                game_state = 'g';
                return true;
            }
        }

        // 4. check is five in reverse-diagonal
        count = 0;
        for (int i = row_start, j = col_end; i <= row_end && j >= col_start; i++, j--)
        {
            if (board[i][j] == c)
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if (count == 5)
            {
                game_state = 'g';
                return true;
            }
        }

        return false;
    }
    bool is_vaild_position(const int &row, const int &col) const
    {
        return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == FLAG_EMPTY;
    }
    char get_stone(const int &row, const int &col) const
    {
        return board[row][col];
    }
    char get_player_type(const int& i) const {
        return player_type[i];
    }
    void place_stone(const char &player, const int &row, const int &col)
    {
        board[row][col] = player;
        if (player == FLAG_BLACK)
        {
            history[0].push_back(std::make_pair(row, col));
            game_state = 'o'; // set next turn
        }
        else if (player == FLAG_WHITE)
        {
            history[1].push_back(std::make_pair(row, col));
            game_state = 'x'; // set next turn
        }
    }
    int get_score(const int &row, const int &col) const
    {
        return score[row][col];
    }
    void set_score(const int &score, const int &row, const int &col)
    {
        this->score[row][col] = score;
    }
    char get_game_type() const
    {
        return game_type;
    }
    void set_game_type(const char &type)
    {
        game_type = type;
    }
    char get_game_state() const
    {
        return game_state;
    }
    void set_game_state(const char &state)
    {
        game_state = state;
    }
    bool undo_last()
    {
        // TODO: undo the last step
        return true;
    }
    pair<int,int> get_next_move() const {
        int row, col;
        
        do {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
        } while (!is_vaild_position(row, col));

        return std::make_pair(row, col);
    }
};
