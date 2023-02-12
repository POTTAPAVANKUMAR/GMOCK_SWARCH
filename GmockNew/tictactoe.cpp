#include <iostream>
#include <string>
#include "gmock/gmock.h"

// Collaborator class
class TicTacToe_Game {
public:
    virtual std::string GetSquare(int row, int col) = 0;
    virtual void SetSquare(int row, int col, const std::string& value) = 0;
};




// System Under Test class
class TicTacToe {
public:
    TicTacToe(TicTacToe_Game* board) : board_(board) {}

    std::string Play(int row, int col) {
        std::string current_square = board_->GetSquare(row, col);
        if (current_square.empty()) {
            board_->SetSquare(row, col, "X");
            return "Player X placed at (" + std::to_string(row) + ", " +
                std::to_string(col) + ")";
        }
        else {
            return "Square is already occupied at (" + std::to_string(row) + ", " +
                std::to_string(col) + ")";
        }
    }

private:
    TicTacToe_Game* board_;
};








// Mock class for TicTacToe_Game
class MockTicTacToe_Game : public TicTacToe_Game {
public:
    MOCK_METHOD(std::string, GetSquare, (int row, int col), (override));
    MOCK_METHOD(void, SetSquare, (int row, int col, const std::string& value),
        (override));
};









// Unit tests

TEST(TicTacToeTest, PlayOnEmptySquare) {
    MockTicTacToe_Game board;
    TicTacToe tic_tac_toe(&board);

    EXPECT_CALL(board, GetSquare(0, 0)).WillOnce(testing::Return(""));
    EXPECT_CALL(board, SetSquare(0, 0, "X"));

    std::string result = tic_tac_toe.Play(0, 0);
    EXPECT_EQ("Player X placed at (0, 0)", result);
}

TEST(TicTacToeTest, PlayOnOccupiedSquare) {
    MockTicTacToe_Game board;
    TicTacToe tic_tac_toe(&board);

    EXPECT_CALL(board, GetSquare(0, 0)).WillOnce(testing::Return("O"));

    std::string result = tic_tac_toe.Play(0, 0);
    EXPECT_EQ("Square is already occupied at (0, 0)", result);
}

