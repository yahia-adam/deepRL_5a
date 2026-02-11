
#include <iostream>
#include <vector>
using std::vector;

class QuartoEnv {
public:
    static constexpr int NUM_PIECES = 16;
    static constexpr int PIECE_ATTRIBUTES = 4;
    static constexpr int COLOR_IDX = 0;   // light/dark
    static constexpr int SIZE_IDX = 1;    // large/small
    static constexpr int SHAPE_IDX = 2;   // square/round
    static constexpr int FILL_IDX = 3;    // solid/hollow
    static constexpr int NUM_VICTORY_PATTERNS = 10;
    static constexpr int BOARD_SIZE = NUM_PIECES * PIECE_ATTRIBUTES;

    vector<int> all_pieces;
    vector<vector<int>> victory_patterns;
    mutable vector<int> board;
    mutable vector<int> observation_space_cache;
    mutable vector<int> selected_piece;
    mutable vector<int> action_space;

    static int index(const int cell, const int attr) {
        return cell * PIECE_ATTRIBUTES + attr;
    }

    mutable vector<int> available_pieces;

    void place_piece(const int cell, const int piece_number) const {
        for (int a = 0; a < PIECE_ATTRIBUTES; a++) {
            board[index(cell, a)] = available_pieces[piece_number * PIECE_ATTRIBUTES + a];
        }
    }

    QuartoEnv() {
        reset();
        observation_space_cache.assign(BOARD_SIZE + PIECE_ATTRIBUTES + BOARD_SIZE,-1);
        action_space.assign((BOARD_SIZE / PIECE_ATTRIBUTES) * 2, -1);
        victory_patterns = {
            // Lignes horizontales
            {0, 1, 2, 3},    {4, 5, 6, 7},    {8, 9, 10, 11},  {12, 13, 14, 15},
            // Colonnes verticales
            {0, 4, 8, 12},   {1, 5, 9, 13},   {2, 6, 10, 14},  {3, 7, 11, 15},
            // Diagonales
            {0, 5, 10, 15},  {3, 6, 9, 12}
        };
        all_pieces = {
            1, 1, 1, 1,  1, 0, 0, 0,  1, 0, 0, 1,  1, 1, 0, 0,
            1, 1, 0, 1,  1, 0, 1, 0,  1, 0, 1, 1,  1, 1, 1, 0,
            0, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 1, 0, 0,
            0, 1, 0, 1,  0, 0, 1, 0,  0, 0, 1, 1,  0, 1, 1, 0
        };
    }

    void reset() const {
        available_pieces = {
            1, 1, 1, 1,  1, 0, 0, 0,  1, 0, 0, 1,  1, 1, 0, 0,
            1, 1, 0, 1,  1, 0, 1, 0,  1, 0, 1, 1,  1, 1, 1, 0,
            0, 1, 1, 1,  0, 0, 0, 0,  0, 0, 0, 1,  0, 1, 0, 0,
            0, 1, 0, 1,  0, 0, 1, 0,  0, 0, 1, 1,  0, 1, 1, 0
        };
        board.assign(BOARD_SIZE, -1);
        selected_piece.assign(PIECE_ATTRIBUTES, -1);
    }

    vector<int> get_action_space() const {
        // Choisir une case a jouer
        int i = 0;
        for (; i < BOARD_SIZE; i += 4) {
            switch (board[i]) {
                case -1:
                    action_space[i] = 1;
                    break;
                default:
                    action_space[i] = 0;
                    break;
            }
        }

        // choisir la piece pour l'adverse
        for (int j = 0; j < BOARD_SIZE; j++) {
            action_space[j + i] = 0;
        }
        return action_space;
    }

    vector<int> get_observation_space() const {
        int i = 0;
        for (; i < BOARD_SIZE; i++) {
            observation_space_cache[i] = board[i];
        }
        for (int j = 0; j < PIECE_ATTRIBUTES; j++, i++) {
            observation_space_cache[i] = selected_piece[j];
        }
        for (int j = 0; j < BOARD_SIZE; j++, i++) {
            observation_space_cache[i] = available_pieces[j];
        }
        return observation_space_cache;
    }

    bool is_game_over() const {
        for (int vp = 0; vp < NUM_VICTORY_PATTERNS; vp++) {
            for (int attr = 0; attr < PIECE_ATTRIBUTES; attr++) {
                const int pos0 = index(victory_patterns[vp][0], attr);
                const int pos1 = index(victory_patterns[vp][1], attr);
                const int pos2 = index(victory_patterns[vp][2], attr);
                const int pos3 = index(victory_patterns[vp][3], attr);

                if (board[pos0] != -1 &&
                    board[pos0] == board[pos1] &&
                    board[pos1] == board[pos2] &&
                    board[pos2] == board[pos3]
                ) {
                    return true;
                }
            }
        }
        return false;
    }

    void render() const {
        for (int i = 0; i < BOARD_SIZE; i += PIECE_ATTRIBUTES) {
            if (i % (PIECE_ATTRIBUTES * PIECE_ATTRIBUTES) == 0) {
                std::cout << std::endl;
            }
            std::cout << board[i] << board[i + 1] << board[i + 2] << board[i + 3] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < BOARD_SIZE; i += PIECE_ATTRIBUTES) {
            if (i % (PIECE_ATTRIBUTES * PIECE_ATTRIBUTES) == 0) {
                std::cout << std::endl;
            }
            std::cout << available_pieces[i] << available_pieces[i + 1] << available_pieces[i + 2] << available_pieces[i + 3] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    auto quarto = QuartoEnv();
    int piece_number;
    int cell_number;

    bool is_game_over = false;

    while (!is_game_over) {
        quarto.render();

        std::cout << "PN $ ";
        std::cin >> piece_number;

        std::cout << "CN $ ";
        std::cin >> cell_number;

        quarto.place_piece(cell_number, piece_number);
        is_game_over = quarto.is_game_over();
    }
}
