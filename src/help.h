#ifndef HELPWINDOW_H
#   define HELPWINDOW_H

#include <qmainwindow.h>

class QComboBox;
class QTextBrowser;

class Help : public QMainWindow
{
    Q_OBJECT

public:
    Help(
      const QString& home,
      int width,
      int height,
      QWidget *parent = 0,
      const char *name = 0
);

private slots:
    void textChanged();
    void openFile();
    void pathSelected(const QString &);
    
private:
    QTextBrowser *mBrowser;
    QComboBox    *mPathCombo;
    QString       mSelectedURL;
    QString       mHomeDirectory;
};

#endif

