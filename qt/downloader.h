#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QWidget>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QtDebug>
#include <QStyle>
#include <QDesktopWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
  class downloader;
}
QT_END_NAMESPACE


class downloader : public QWidget {
  Q_OBJECT

public:
  downloader(QWidget *parent = nullptr);
  ~downloader();
public:
  void startRequest(QUrl url);


private slots:
  void on_analyzeButton_clicked();

  // slot for readyRead() signal
  void httpReadyRead();

  // slot for finished() signal from reply
  void httpDownloadFinished();

  void enableAnalyzeButton();
  
private:
  Ui::downloader *ui;
  QUrl url;
  QNetworkAccessManager *manager;
  QNetworkReply *reply;
  QByteArray text;

};
#endif // DOWNLOADER_H
