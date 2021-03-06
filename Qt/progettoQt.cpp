#include "progettoQt.h"
#include "ui_progettoQt.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <iostream>



// funzione che conta il numero di parole basandosi sul fatto che se
// un carattere che rappresenta una lettera segue uno che non ne rsppresenta
// allora ho una parola
int countWords(QString sentence) {
  int numberOfWords = 0;
  if (sentence[0].isLetter()) {
    numberOfWords++;
  }

  // verifico che se ho una lettera che segue un carattere che non lo è
  // ho trovato una parola
  for (int i = 1; i < sentence.length(); i++) {
    if ((sentence[i].isLetter()) && (!sentence[i-1].isLetter())) {
      numberOfWords++;
    }
  }

  return numberOfWords;
}

// costruttore dell'interfaccia del progetto
progettoQt::progettoQt(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::progettoQt) {

  // il widget viene rimpicciolito per mostrare solo campo di testo e bottone
  ui->setupUi(this);
  this->resize(270, 40);

  // inserisco testo placeholder nella casella di testo
  ui->urlBox->setPlaceholderText("inserire url");

  // inizializzo il bottone
  ui->analyzeButton->setDefault(true);
  ui->analyzeButton->setAutoDefault(true);
  ui->analyzeButton->setEnabled(false);


  // il bottone si abilita all'inserimento del testo
  connect(ui->urlBox, SIGNAL(textChanged(QString)),
	  this, SLOT(enableAnalyzeButton()));

}

// distruttore
progettoQt::~progettoQt() {
  delete ui;
}

// abilitazione del bottone se ho testo nella box
void progettoQt::enableAnalyzeButton() {
  ui->analyzeButton->setEnabled(!(ui->urlBox->text()).isEmpty());
}

// alla pressione del tatso parte l'analisi
void progettoQt::on_analyzeButton_clicked() {
  // inizializzo il manager
  manager = new QNetworkAccessManager(this);

  // prendo l'url dalla box
  url = (ui->urlBox->text());

  // disabilito il bottone fino a nuovo inserimento
  ui->analyzeButton->setEnabled(false);

  // parte la richiesta 
  startRequest(url);
}

void progettoQt::startRequest(QUrl url) {
  // salvo in reply il contenuto della richiesta ottenuto col metodo get
  // che restutisce un QNetworkReply
  reply = manager->get(QNetworkRequest(url));

  // il segnale readyRead() si ha all'arrivo di nuove informazioni
  // chiamo quindi httpReadyRead per la lettura dei dati
  connect(reply, SIGNAL(readyRead()),
	  this, SLOT(httpReadyRead()));

  // il segnale finished avvisa che si è finito di ricevere informazioni
  // chiamo quindi httpDownloadFinished per la rappresentazione del testo
  // e l'analisi dei dati
  connect(reply, SIGNAL(finished()),
	  this, SLOT(httpDownloadFinished()));


}
void progettoQt::httpReadyRead() {
  // ogni volta che ho nuove informazioni (ovvero il testo che sto elaborando)
  // le "scrivo" in una variabile QString chiamata text dopo averle lette con il
  // metodo readALL() che restituisce un QByteArray (si puà costurire una
  // QString a partire da un QByteArray)
  text += QString(reply->readAll());
    
}

void progettoQt::httpDownloadFinished() {
  
  // tutte le informazioni sono state lette
  // se la reply mi restituisce un errore grazie al metodo error()
  // resituisco un "popup" replyError di tipo QMEssagebox che segnala l'errore 
  if(reply->error()){
    QMessageBox replyError;
    // coloro il messaggio d'errore di rosso e lo setto per il messaggio
    replyError.setText("<font color=\"red\">url errato</font>");

    // cancello il contenuto della box per l'url in quanto errato
    ui->urlBox->setText("");
    
    // lancio l'esecuzione del messaggio d'errore
    replyError.exec();

  }else{

    // la reply può essere analizzata
    // ingrandisco il widget per mostare testo e statistiche
    this->resize(800, 320);
    // centro il widget 
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,
					  Qt::AlignCenter,
					  this->size(),
					  qApp->desktop()->availableGeometry())
		      );
    // ingrandisco la box dell'url e sposto il bottone dopo aver
    // ingrandito il widget (mi baso sulla dimensione della box del testo
    // da visualizzare più la distanza "dis" di default che
    // c'era tra bottone e url box)
    int dis = ui->analyzeButton->pos().x() - ui->urlBox->size().width();

    ui->urlBox->resize(ui->textBrowser->size().width() -
               ui->analyzeButton->size().width() - dis,
		       ui->urlBox->size().height());
    ui->analyzeButton->move(ui->urlBox->size().width() + dis,
			    ui->analyzeButton->pos().y());
    
    // mostro il testo 
    ui->textBrowser->setText(text);

    // azzero i contatori necessari per l'analisi dati
    int countPhrase = 0;
    int countChars = 0;
    int countSpace = 0;
    int countPara = 0;
    
    // conto iterando sul testo (tranne il numero di parole)
    for(int i = 0; i < text.length(); i++){
      if(text[i] == '.' || text[i] == '?' || text[i] == '!' || text[i] == ';')
	countPhrase++;
      if(text[i] == ' ')
	countSpace++;
      if(text[i] == '\n' || text[i] == '\t')
    countPara++;
      countChars++;
    }


    // preparo le varie QString per mostare i risultati, colorando di verde
    // il nome del dato che voglio visualizzare
    // inserisco le stringhe nelle varie label
    QString infoPhrase =
      "<font color=\"green\"><b>Frasi: </b><font color=\"black\">"
      + QString::number(countPhrase);
    ui->phraseLabel->setText(infoPhrase);

    QString infoWord =
      "<font color=\"green\"><b>Parole: </b><font color=\"black\">"
      + QString::number(countWords(text));
    ui->wordLabel->setText(infoWord);

    QString infoChar =
      "<font color=\"green\"><b>Caratteri: </b><font color=\"black\">"
      + QString::number(countChars);
    ui->charLabel->setText(infoChar);

    QString infoNoSpace =
      "<font color=\"green\"><b>Caratteri senza spazi: </b><font color=\"black\">"
      + QString::number(countChars - countSpace);
    ui->noSpaceLabel->setText(infoNoSpace);

    QString infoPara =
      "<font color=\"green\"><b>Paragrafi: </b><font color=\"black\">"
      + QString::number(countPara);
    ui->paraLabel->setText(infoPara);

    // pongo il testo a stringa vuota in attesa di eventuale nuove richieste
    // in quanto text viene caricato con += in httpReadyRead()
    text = "";

    // inizializzo nuovamente la url box e il bottone
    ui->analyzeButton->setEnabled(false);
    ui->urlBox->setPlaceholderText("insert url");
  }
}
