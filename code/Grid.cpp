
/*
  Author: Karim Abousamra
  Description: Implementation file for the Grid class
  Date: February 6, 2024
*/

#include "../headers/Grid.h"

#include "../headers/Button.h"


/*
Function: Grid::Grid
Description: Constructor for the Grid class. Initializes the grid layout and populates it with buttons representing the grid cells.
Parameters:
    - parent: Pointer to the parent widget.
Return: None
*/
Grid::Grid(QWidget *parent) : QGridLayout(parent) {
  memset(valueGrid, 0, sizeof(valueGrid));
  openSpaces = 0;

  populateMines();
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLUMNS; col++) {
      valueGrid[row][col] = calculateValue(row, col);
      Button *button = new Button(row, col, this, valueGrid[row][col]);
      buttonGrid[row][col] = button;
      this->addWidget(button, row, col);
    }
  }
}


/*
  Function: Grid::populateMines
  Description: Populates the grid with mines.
  Parameters: None
  Return: None
*/
void Grid::populateMines() {
  QRandomGenerator generator = QRandomGenerator::global()->generate();

  int mines = 99;
  while (mines > 0) {
    int randRow = generator.bounded(ROWS);
    int randCol = generator.bounded(COLUMNS);

    if (valueGrid[randRow][randCol] == -1) continue;

    valueGrid[randRow][randCol] = -1;
    mines--;
  }
}


/*
  Function: Grid::reset
  Description: Resets the grid, clearing existing values and mines, and repopulates it.
  Parameters: None
  Return: None
*/
void Grid::reset() {
  openSpaces = 0;
  memset(valueGrid, 0, sizeof(valueGrid));
  populateMines();

  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLUMNS; col++) {
      valueGrid[row][col] = calculateValue(row, col);
      buttonGrid[row][col]->reset(valueGrid[row][col]);
    }
  }
}


/*
  Function: Grid::calculateValue
  Description: Calculates the value of a cell in the grid, representing the number of neighboring mines.
  Parameters:
      - row: The row index of the cell.
      - col: The column index of the cell.
  Return:
      - The calculated value of the cell.
*/
int Grid::calculateValue(int row, int col) {
  if (valueGrid[row][col] == -1) return -1;
  int directions[][2] = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                         {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

  // Iterate through each direction
  int currVal = 0;
  for (int i = 0; i < 8; ++i) {
    int newRow = row + directions[i][0];
    int newCol = col + directions[i][1];

    // Check if the neighboring cell is within the bounds of the grid
    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLUMNS) {
      int neighborVal = valueGrid[newRow][newCol];

      if (neighborVal < 0) {
        currVal += 1;
      }
    }
  }
  return currVal;
}


/*
  Function: Grid::getOpenSpaces
  Description: Getter function to retrieve the number of open spaces in the grid.
  Parameters: None
  Return:
      - The number of open spaces in the grid.
*/
int Grid::getOpenSpaces() { return openSpaces; }


/*
  Function: Grid::setOpenSpaces
  Description: Setter function to set the number of open spaces in the grid.
  Parameters:
      - openSpace: The new number of open spaces.
  Return: None
*/
void Grid::setOpenSpaces(int openSpace) { this->openSpaces = openSpace; }


/*
  Function: Grid::openEmptyCells
  Description: Recursively opens empty cells and their neighbors in the grid.
  Parameters:
      - row: The row index of the cell to open.
      - col: The column index of the cell to open.
  Return: None
*/
void Grid::openEmptyCells(int row, int col) {
  if (valueGrid[row][col] < 0) return;
  if (buttonGrid[row][col]->solved) return;

  // qDebug() << "Running";
  buttonGrid[row][col]->openTile();
  buttonGrid[row][col]->solved = true;

  int directions[][2] = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                         {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

  for (int i = 0; i < 8; ++i) {
    int newRow = row + directions[i][0];
    int newCol = col + directions[i][1];

    // Check if the neighboring cell is within the bounds of the grid
    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLUMNS) {
      int neighborVal = valueGrid[newRow][newCol];
      if (neighborVal >= 0 && valueGrid[row][col] == 0 &&
          !buttonGrid[newRow][newCol]->solved) {
        openEmptyCells(newRow, newCol);
      }
    }
  }
}
