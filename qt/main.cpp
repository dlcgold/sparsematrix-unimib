#include <QCoreApplication>
#include "downloader.h"

int main(int argc, char* argv[]){
  
  QCoreApplication app(argc, argv);
  Downloader d;
  d.doDownload("https://www.cs.cmu.edu/~spok/grimmtmp/016.txt");
  
  return app.exec();


}
