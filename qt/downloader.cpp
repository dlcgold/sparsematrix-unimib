#include "downloader.h"


Downloader::Downloader(QObject *parent) :
  QObject(parent)
{
}

void Downloader::doDownload(char* const url)
{
  manager = new QNetworkAccessManager(this);

  connect(manager, SIGNAL(finished(QNetworkReply*)),
	  this, SLOT(replyFinished(QNetworkReply*)));

  manager->get(QNetworkRequest(QUrl(url)));
}

void Downloader::replyFinished (QNetworkReply *reply)
{
  if(reply->error())
    {
      qDebug() << "ERROR!";
      qDebug() << reply->errorString();
    }
  else
    {
      qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
      qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
      qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
      qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
      qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

      QFile *file = new QFile("downloaded.txt");
      if(file->open(QFile::Append))
        {
	  file->write(reply->readAll());
	  file->flush();
	  file->close();
        }
      delete file;
    }

  reply->deleteLater();
}
