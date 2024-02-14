/*
  Author: Karim Abousamra
  Description: Header file for the Grid class, Which inherits from QGridLayout 
  Date: February 6, 2024
*/

#ifndef GRID_H
#define GRID_H

#include <QGridLayout>
#include <QRandomGenerator>

class Button;
constexpr int ROWS = 30;
constexpr int COLUMNS = 16;

class Grid : public QGridLayout {
  Q_OBJECT

 private:
  //  Instance Variables
  int openSpaces;
  Button* buttonGrid[ROWS][COLUMNS];
  int valueGrid[ROWS][COLUMNS];

  // Private methods
  void populateMines();
  int calculateValue(int row, int col);

 public:
  Grid(QWidget* parent = nullptr);

  // Getters
  int getOpenSpaces();

  // Setters
  void setOpenSpaces(int spaces);

  // Methods
  void openEmptyCells(int row, int col);
  void reset();
};

#endif  // GRID_H
