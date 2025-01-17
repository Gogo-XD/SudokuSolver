class SudokuSolver
{
private:
  bool isValid(std::vector<std::vector<int>> sudoku, int row, int col, int num);
  bool checkRow(std::vector<std::vector<int>> sudoku, int row, int num);
  bool checkCol(std::vector<std::vector<int>> sudoku, int col, int num);
  bool checkBox(std::vector<std::vector<int>> sudoku, int row, int col, int num);
  bool sudokuHelper(std::vector<std::vector<int>> &sudoku, int row, int col);
  bool multiThreader(std::vector<std::vector<int>> &sudoku, int num);

public:
  std::vector<std::vector<int>> sudokuSolver(std::vector<std::vector<int>> sudoku);
};
