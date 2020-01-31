#include "progettoQt.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  progettoQt w;
  w.show();
  a.exec();
  return 0;
}
