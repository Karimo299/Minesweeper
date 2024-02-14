/*
  Author: Karim Abousamra
  Description: Header file for the Button class, Which inherits from QPushButton 
  Date: February 6, 2024
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <QDebug>
#include <QMouseEvent>
#include <QPushButton>
#include <QString>

class Grid;

class Button : public QPushButton {
  Q_OBJECT

 public:
  //  Constructor
  Button(int row, int col, Grid *grid, int val);

  // Public Instance Variables
  bool solved;

  // Public Getters
  bool getSolved();

  // Public Setters
  void setSolved();

  // Public Methods
  void reset(int val);
  void openTile();

  // Slots to be connected with signals
 private slots:
  void handleRightClick();
  void handleLeftClick();

  // Signals
 signals:
  void rightClicked();

 private:
  //  Private Instance Variables
  int row;
  int col;
  int state;
  int value;
  Grid *grid;

  // Private Getters
  int getRow();
  int getCol();
  int getState();
  Grid *getParentGrid();

  // Private Setters
  void setRow(int row);
  void setCol(int col);
  void changeState();

  // Private Methods
  void mousePressEvent(QMouseEvent *e);
};

#endif  // BUTTON_H
