#include "downloader.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  downloader w;
  w.show();
  return a.exec();
}
