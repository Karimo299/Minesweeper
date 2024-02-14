
/*
  Author: Karim Abousamra
  Description: Main file that is initially executed
  Date: February 6, 2024
*/

#include <QApplication>
#include <QMainWindow>

#include "../headers/Grid.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);


  // Create Window and set its details
  QMainWindow window;
  window.setWindowTitle("Assignment 1");
  window.setFixedSize(720, 1280);

  // Create a widget to put the grid in
  QWidget *wid = new QWidget(&window);
  new Grid(wid);
  
  window.setCentralWidget(wid);
  window.show();

  return app.exec();
}