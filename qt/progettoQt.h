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
  // slot per far partire l'analisi al click
  void on_analyzeButton_clicked();

  // slot per il segnale readyRead()
  void httpReadyRead();

  // slot per seganle finished()
  void httpDownloadFinished();

  // slot per abilitare bottone
  void enableAnalyzeButton();
  
private:
  
  Ui::progettoQt *ui;
  QUrl url;
  QNetworkAccessManager *manager;
  QNetworkReply *reply;
  QString text;

};
#endif // progettoQt_H
