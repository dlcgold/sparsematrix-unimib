#ifndef progettoQT_H
#define progettoQT_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QtDebug>
#include <QStyle>
#include <QDesktopWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
  class progettoQt;
}
QT_END_NAMESPACE


class progettoQt : public QWidget {
  Q_OBJECT

public:
  progettoQt(QWidget *parent = nullptr);
  ~progettoQt();
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
  Ui::progettoQt *ui;
  QUrl url;
  QNetworkAccessManager *manager;
  QNetworkReply *reply;
  QByteArray text;

};
#endif // progettoQt_H
