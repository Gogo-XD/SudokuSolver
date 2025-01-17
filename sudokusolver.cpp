#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include "sudokusolver.h"

bool SudokuSolver::isValid(std::vector<std::vector<int>> sudoku, int row, int col, int num)
{
  if (checkRow(sudoku, row, num) && checkCol(sudoku, col, num) && checkBox(sudoku, row, col, num))
  {
    return true;
  }
  return false;
}

bool SudokuSolver::checkRow(std::vector<std::vector<int>> sudoku, int row, int num)
{
  for (int i = 0; i < 9; i++)
  {
    if (sudoku[row][i] == num)
    {
      return false;
    }
  }
  return true;
}

bool SudokuSolver::checkCol(std::vector<std::vector<int>> sudoku, int col, int num)
{
  for (int i = 0; i < 9; i++)
  {
    if (sudoku[i][col] == num)
    {
      return false;
    }
  }
  return true;
}

bool SudokuSolver::checkBox(std::vector<std::vector<int>> sudoku, int row, int col, int num)
{
  int startRow = row - row % 3;
  int startCol = col - col % 3;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (sudoku[i + startRow][j + startCol] == num)
      {
        return false;
      }
    }
  }
  return true;
}

bool SudokuSolver::sudokuHelper(std::vector<std::vector<int>> &sudoku, int row, int col)
{
  if (col == 9)
  {
    col = 0;
    row++;
    if (row == 9)
    {
      return true;
    }
  }

  if (sudoku[row][col] != 0)
  {
    return sudokuHelper(sudoku, row, col + 1);
  }

  for (int num = 1; num <= 9; num++)
  {
    if (isValid(sudoku, row, col, num))
    {
      sudoku[row][col] = num;

      if (sudokuHelper(sudoku, row, col + 1))
      {
        return true;
      }
      sudoku[row][col] = 0;
    }
  }

  return false;
}

bool SudokuSolver::multiThreader(std::vector<std::vector<int>> &sudoku, int num)
{
  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      if (sudoku[row][col] == 0)
      {
        if (isValid(sudoku, row, col, num))
        {
          sudoku[row][col] = num;
          if (sudokuHelper(sudoku, row, col + 1))
          {
            return true;
          }
          sudoku[row][col] = 0;
        }
      }
    }
  }
  return false;
}

std::vector<std::vector<int>> SudokuSolver::sudokuSolver(std::vector<std::vector<int>> sudoku)
{
  std::vector<std::vector<std::vector<int>>> duplicates(9, sudoku);
  std::vector<std::thread> threads;
  std::vector<bool> results(9, false);
  std::atomic<bool> solutionFound(false);

  for (int i = 0; i < 9; i++)
  {
    threads.emplace_back([&duplicates, &results, &solutionFound, i, this]()
                         {
            results[i] = multiThreader(duplicates[i], i + 1);
            if (results[i]) {
                solutionFound = true;
            } });
  }

  for (auto &thread : threads)
  {
    thread.join();
  }

  for (int i = 0; i < 9; i++)
  {
    if (results[i])
    {
      return duplicates[i];
    }
  }

  std::cout << "No solution exists for the provided sudoku puzzle." << std::endl;
  return std::vector<std::vector<int>>();
}
