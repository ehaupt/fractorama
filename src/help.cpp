/*****************************************************************************
 * Qt Headers
 *****************************************************************************/

#include <qstatusbar.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qiconset.h>
#include <qfiledialog.h>
#include <qapplication.h>
#include <qcombobox.h>
#include <qfileinfo.h>
#include <qtextbrowser.h>

/*****************************************************************************
 * Local Headers
 *****************************************************************************/

#include "help.h"

/*****************************************************************************
 * Icons
 *****************************************************************************/

#include "back.xpm"
#include "forward.xpm"
#include "home.xpm"

// Both netscape and internet explorer treat the space bar as
// a "page down" and I've become quite accustomed to that feature
// so here we subclass QTextBrowser to support that behavior

class SpaceBarTextBrowser : public QTextBrowser
{
   public:
      SpaceBarTextBrowser(QWidget *parent);

   protected:
      void keyPressEvent(QKeyEvent *e);
};

SpaceBarTextBrowser::SpaceBarTextBrowser(QWidget *parent)
   : QTextBrowser(parent)
{
}

void SpaceBarTextBrowser::keyPressEvent(QKeyEvent *e)
{
   // If this is the space bar, do a "page down"

   if(e->key() == Key_Space)
      scrollBy(0, visibleHeight()); 

   else
      QTextBrowser::keyPressEvent(e);
}

Help::Help(
   const QString& home,
   int width,
   int height,
   QWidget *parent,
   const char *name
)
   :
   QMainWindow(parent, name, WDestructiveClose),
   mPathCombo(0),
   mSelectedURL(),
   mHomeDirectory(QFileInfo(home).dirPath(TRUE))
{
   mBrowser = new SpaceBarTextBrowser(this);
   mBrowser->mimeSourceFactory()->setFilePath(mHomeDirectory);
   mBrowser->setFrameStyle(QFrame::Panel | QFrame::Sunken);

   connect(
      mBrowser, SIGNAL(textChanged()), this, SLOT(textChanged())
   );

   setCentralWidget(mBrowser);
   mBrowser->setSource(home);

   connect(
      mBrowser,    SIGNAL(highlighted(const QString&)),
      statusBar(), SLOT(message(const QString&))
   );

   resize(width, height);

   QPopupMenu *file = new QPopupMenu(this);

   file->insertItem("Open File",  this, SLOT(openFile()));
   file->insertItem("Close Help", this, SLOT(close()));

   QPixmap backPixmap(backXPM);
   QPixmap forwardPixmap(forwardXPM);
   QPixmap homePixmap(homeXPM);

   QIconSet icon_back(backPixmap);
   QIconSet icon_forward(forwardPixmap);
   QIconSet icon_home(homePixmap);

   menuBar()->insertItem("File", file );

   QToolBar *toolbar = new QToolBar(this);
   addToolBar(toolbar, "Toolbar");
   QToolButton *button = 0;

   button = new QToolButton(
      icon_back, "Backward", "", mBrowser, SLOT(backward()), toolbar
   );

   connect(
      mBrowser, SIGNAL(backwardAvailable(bool)), button, SLOT(setEnabled(bool))
   );

   button->setEnabled(FALSE);

   button = new QToolButton(
      icon_forward, "Forward", "", mBrowser, SLOT(forward()), toolbar
   );

   connect(
      mBrowser, SIGNAL(forwardAvailable(bool)), button, SLOT(setEnabled(bool))
   );

   button->setEnabled(FALSE);

   button = new QToolButton(
      icon_home, "Home", "", mBrowser, SLOT(home()), toolbar
   );

   toolbar->addSeparator();

   mPathCombo = new QComboBox(TRUE, toolbar);

   connect(
      mPathCombo, SIGNAL(activated(const QString &)),
      this,       SLOT(pathSelected(const QString &))
   );

   toolbar->setStretchableWidget( mPathCombo );

   setRightJustification(TRUE);
   setDockEnabled(Left, FALSE);
   setDockEnabled(Right, FALSE);

   mPathCombo->insertItem(home);

   mBrowser->setFocus();
}

void Help::textChanged()
{
   if(mBrowser->documentTitle().isNull())
      setCaption(mBrowser->context());

   else
      setCaption(mBrowser->documentTitle());

   mSelectedURL = caption();

   if(!mSelectedURL.isEmpty() && mPathCombo)
   {
      bool exists = FALSE;
      int i       = 0;

      for(i = 0; i < !exists && mPathCombo->count(); ++i)
         if(mPathCombo->text(i) == mSelectedURL )
            exists = TRUE;

      if(!exists)
      {
         mPathCombo->insertItem(mSelectedURL, 0);
         mPathCombo->setCurrentItem(0);
      }
      else
         mPathCombo->setCurrentItem(i);

      mSelectedURL = QString::null;
   }
}

void Help::openFile()
{
   QString fileName = QFileDialog::getOpenFileName(
      mHomeDirectory, QString("*.html"), this
   );

   if(!fileName.isEmpty())
      mBrowser->setSource(fileName);
}

void Help::pathSelected(const QString &path)
{
   mBrowser->setSource(path);
}
