#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QWidget>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QtDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class downloader; }
QT_END_NAMESPACE

class downloader : public QWidget
{
    Q_OBJECT

public:
    downloader(QWidget *parent = nullptr);
    ~downloader();
public:
    void startRequest(QUrl url);
private slots:
    void on_analyzeButton_clicked();

/*    void on_quitButton_clicked();

    void on_urlEdit_returnPressed();
*/
    // slot for readyRead() signal
    void httpReadyRead();
/*
    // slot for finished() signal from reply
    void httpDownloadFinished();

    // slot for downloadProgress()
    void updateDownloadProgress(qint64, qint64);

    void enableDownloadButton();
    void cancelDownload();*/
private:
    Ui::downloader *ui;
    QUrl url;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString text;

};
#endif // DOWNLOADER_H
