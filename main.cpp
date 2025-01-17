#include <iostream>
#include <vector>
#include <thread>
#include "sudokusolver.h"

int main()
{
  SudokuSolver sudokuSolver;
  std::vector<std::vector<int>> sudoku = {
      {5, 3, 0, 0, 7, 0, 0, 0, 0},
      {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0},
      {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1},
      {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0},
      {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9}};
  std::vector<std::vector<int>> solvedSudoku = sudokuSolver.sudokuSolver(sudoku);
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      std::cout << solvedSudoku[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
