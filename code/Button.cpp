
/*
  Author: Karim Abousamra
  Description: Implementation file for the Button class
  Date: February 6, 2024
*/

#include "../headers/Button.h"

#include <QApplication>
#include <QMessageBox>

#include "../headers/Grid.h"


/*
Function: Button::~Button
Description: Constructor for the Button class.
Parameters: 
  int row: the index of the row in the grid
  int col: the index of the col in the grid
  Grid* gird: the grid instance
  int val: the value of that button (based on how many mines near it)
Return: None
*/
Button::Button(int row, int col, Grid* grid, int val) : QPushButton() {
  this->setFixedSize(40, 40);
  this->setIconSize(QSize(40, 40));

  this->state = 0;
  this->solved = false;
  this->value = val;
  this->grid = grid;
  this->row = row;
  this->col = col;

  connect(this, &Button::clicked, this, &Button::handleLeftClick);
  connect(this, &Button::rightClicked, this, &Button::handleRightClick);
}



/*
  Function: Button::mousePressEvent
  Description: Event handler for mouse press events.
  Parameters:
      - e: Pointer to the QMouseEvent object containing information about the event.
  Return: None
  */
void Button::mousePressEvent(QMouseEvent* e) {
  if (e->button() == Qt::LeftButton) emit clicked();
  if (e->button() == Qt::RightButton) emit rightClicked();
}


/*
  Function: Button::handleLeftClick
  Description: Handles left-click events on the button.
  Parameters: None
  Return: None
*/
void Button::handleLeftClick() {
  if (value == 0) {
    grid->openEmptyCells(row, col);
  } else {
    openTile();
  }
}

/*
  Function: Button::handleRightClick
  Description: Handles right-click events on the button.
  Parameters: None
  Return: None
*/
void Button::handleRightClick() {
  if (solved) return;
  changeState();
}

// Getters
int Button::getRow() { return row; }
int Button::getCol() { return col; }
int Button::getState() { return state; }
Grid* Button::getParentGrid() { return this->grid; };

// Setters
void Button::setRow(int row) { this->row = row; }
void Button::setCol(int col) { this->col = col; }

void Button::changeState() {
  state = (state + 1) % 3;
  QIcon flagIcon = QIcon("./assets/mine_flag.png");
  QIcon QuestionIcon = QIcon("./assets/question_mark.png");
  QIcon emptyIcon = QIcon();

  if (state == 0) {
    setIcon(emptyIcon);
  } else if (state == 1) {
    setIcon(flagIcon);
  } else {
    setIcon(QuestionIcon);
  }
}

// Methods
void Button::reset(int val) {
  setText("");
  setIcon(QIcon());
  state = 0;
  solved = false;
  value = val;
  setStyleSheet("");
}

void Button::openTile() {
  if (value < 0) {
    QIcon mineIcon = QIcon("./assets/bomb_explode.png");
    this->setIcon(mineIcon);
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(
        this, "Game Over",
        "Game Over! You hit a bomb! Would you like to try again?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
      grid->reset();
    } else {
      qApp->quit();
    }
  } else {
    if (value > 0) this->setText(QString::number(value));
    this->solved = true;
    this->setStyleSheet("border: none;font-size: 30px;");
    this->setIcon(QIcon());

    int newOpenSpaces = grid->getOpenSpaces() + 1;
    grid->setOpenSpaces(newOpenSpaces);

    if (newOpenSpaces >= (30 * 16) - 99) {
      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "You Won!",
                                    "Would you like to play Again?",
                                    QMessageBox::Yes | QMessageBox::No);

      if (reply == QMessageBox::Yes) {
        grid->reset();
      } else {
        qApp->quit();
      }
    }
  }
}