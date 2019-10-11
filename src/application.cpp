// C/C++ headers

#include <iostream>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::ostream;

// Qt headers

#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qmenubar.h>
#include <qkeycode.h>
#include <qfiledialog.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qtextstream.h>
#include <qscrollview.h>
#include <qprogressdialog.h>
#include <qtimer.h>
#include <qiconset.h>
#include <qwidcoll.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qcolordialog.h>
#include <qfileinfo.h>
#include <qfont.h>
#include <qpopupmenu.h>
#include <qmultilineedit.h>
#include <qregexp.h>

// Local Headers

#include "application.h"
#include "fractalview.h"
#include "Fractal.h"
#include "TiffWriter.h"
#include "fractal_parse.h"
#include "state.h"
#include "zoomoutdialog.h"
#include "zoomindialog.h"
#include "antialiasdialog.h"
#include "fractalsplitter.h"
#include "map.h"
#include "zoominsettings.h"
#include "qinfiniteloopcallback.h"
#include "findreplacedialog.h"
#include "dmemory.h"
#include "help.h"
#include "gradienteditor.h"

// History/Revisions

#include "version.h"

// Pixmaps

#include "open.xpm"
#include "draw.xpm"
#include "draw_disabled.xpm"
#include "zoom.xpm"
#include "zoom_disabled.xpm"
#include "zoomout.xpm"
#include "zoomout_disabled.xpm"
#include "stop.xpm"
#include "stop_disabled.xpm"

// Local #defines

#define TEXT_EXTENSION  ".jfd"
#define IMAGE_EXTENSION ".tif"
#define DEFAULT_NAME    "untitled"TEXT_EXTENSION

static char *fontSizes[] =
{
   "8", "10", "12", "14", "18", "24"
};

/*****************************************************************************
 * Constructor
 *
 * Note: We always create our ApplicationWindow objects using the
 *       "WDesctructiveClose" flag so that they will be deleted when closed.
 *       As a consequence, all ApplicationWindow object *must* be
 *       created on the heap (via new) *never* on the stack.
 *****************************************************************************/

ApplicationWindow::ApplicationWindow(
   State *theState,
   QString home,
   const char *fileName,
   const char *contents,
   int drawImmediately
)
   :
   QMainWindow(0, "Main Window", Qt::WDestructiveClose),
   mProgressDialog(0),
   mDrawButton(0),
   mZoomButton(0),
   mZoomOutButton(0),
   mStopButton(0),
   mDrawIconSet(0),
   mZoomIconSet(0),
   mZoomOutIconSet(0),
   mStopIconSet(0),
   mFileName(0),
   mOriginalText(0),
   mTextNeedsSaving(0),
   mMessage(0),
   mProgress(0),
   mSplitter(0),
   mState(theState),
   mResizeTimer(0),
   mFontSizes(0),
   mCurrentlyDrawing(FALSE),
   mSaveCancelled(FALSE),
   mSaveImageMenu(0),
   mUseCurrentImageIndex(0),
   mFindReplace(0),
   mHome(home)
{
   // Set our size

   int width  = 0;
   int height = 0;

   mState->getDimensions(&width, &height);

   resize(width, height);

   // Set up our resize timer, the purpose of the resize timer is
   // to avoid updating our state for all the intermittent sizes we pass
   // through as we resize the window - the timer ensures it has been
   // at least 1/4 second since the last resize event

   DNEW(mResizeTimer, QTimer(this));
   
   QObject::connect(
      mResizeTimer,
      SIGNAL(timeout()),
      this,
      SLOT(resizeTimerFinished())
   );

   // Our main dialog will be split between the text editor portion
   // and the display portion

   mSplitter = new FractalSplitter(this);
   setCentralWidget(mSplitter);

   // Arrange to be notified when the sizes of the splitter's windows
   // change

   QObject::connect(
      mSplitter,
      SIGNAL(sizesChanged(int,int)),
      this,
      SLOT(sizesChanged(int,int))
   );

   QObject::connect(
      mSplitter->getEdit(),
      SIGNAL(textChanged()),
      this,
      SLOT(textChanged())
   );

   QObject::connect(
      mSplitter->getEdit(),
      SIGNAL(cursorPositionChanged(int, int)),
      this,
      SLOT(cursorPositionChanged(int, int))
   );

   mSplitter->getEdit()->setFocus();

   // Size the children of our mSplitter

   int top    = 0;
   int bottom = 0;

   mState->getSplitSizes(&top, &bottom);

   // There aren't sensible defaults for top and bottom since their
   // real default values would be dependent upon ApplicationWindow's
   // current geometry so we check for bad values by comparing top/bottom
   // with 0 and don't set the sizes if top/bottom aren't valid (not
   // setting the values gives the top and bottom widgets their
   // default sizes)

   if(top > 0 && bottom > 0)
      mSplitter->setTopAndBottomSize(top, bottom);

   // Set our font size

   QFont current = mSplitter->getEdit()->font();
   current.setPointSize(mState->getFontSize());
   mSplitter->getEdit()->setFont(current);

   // Create our tool, menu and status bars ...

   addToolBar();
   addMenuBar();
   addStatusBar();

   // Deal with our zoom color now

   int red   = 0;
   int green = 0;
   int blue  = 0;

   mState->getZoomColor(&red, &green, &blue);
   mSplitter->getView()->setZoomColor(red, green, blue);

   // Set our buttons to reasonable default states

   mDrawButton->setEnabled(FALSE);
   mZoomButton->setEnabled(FALSE);
   mZoomOutButton->setEnabled(FALSE);
   mStopButton->setEnabled(FALSE);

   if(fileName)
   {
      if(contents)
      {
         mSplitter->getEdit()->append(contents);
         mSplitter->getEdit()->setCursorPosition(1, 1);
         setCurrentFileName(fileName);

         // We've artificially loaded a .jfd file, ensure drawing and
         // zooming out are permitted and flag the text as needing saving

         mDrawButton->setEnabled(TRUE);
         mZoomOutButton->setEnabled(TRUE);
         mTextNeedsSaving = TRUE;

         setOriginalText(contents);
      }

      else
         loadFile(fileName);

      if(drawImmediately)
         draw();
   }
   else
   {
      setCurrentFileName(DEFAULT_NAME);
   }
}

/*****************************************************************************
 * Destructor
 *****************************************************************************/

ApplicationWindow::~ApplicationWindow()
{
   DADELETE(mFileName);
   DADELETE(mOriginalText);
   DDELETE(mDrawIconSet);
   DDELETE(mZoomIconSet);
   DDELETE(mStopIconSet);
   DDELETE(mZoomOutIconSet);
   DDELETE(mState);
   DDELETE(mResizeTimer);
   DDELETE(mFontSizes);
}

/*****************************************************************************
 * Methods to fulfill our role as "FractalObserver"
 *****************************************************************************/

void ApplicationWindow::percentComplete(double percent)
{
   mProgress->setProgress((int)(percent + 0.5));
}

void ApplicationWindow::drawingStarted()
{
   // Set our buttons, etc. to appropriate states

   mDrawButton->setEnabled(FALSE);
   mStopButton->setEnabled(TRUE);
   mProgress->setProgress(0);

   mCurrentlyDrawing = TRUE;
   mSaveImageMenu->setItemEnabled(mUseCurrentImageIndex, FALSE);
}

void ApplicationWindow::drawingFinished(char *text, int wasCancelled)
{
   mDrawButton->setEnabled(TRUE);
   mStopButton->setEnabled(FALSE);
   mProgress->reset();

   message(text, 3000);

   mCurrentlyDrawing = FALSE;

   if(!wasCancelled)
      mSaveImageMenu->setItemEnabled(mUseCurrentImageIndex, TRUE);
}

void ApplicationWindow::zoomAllowed()
{
   mZoomButton->setEnabled(TRUE);
}

void ApplicationWindow::zoomNotAllowed()
{
   mZoomButton->setEnabled(FALSE);
}

State *ApplicationWindow::getState()
{
   return(mState);
}

/*****************************************************************************
 * public static functions
 *****************************************************************************/

int ApplicationWindow::writeTiffFile(
   const char *fileName,
   int doAntiAlias,
   int theWidth,
   int theHeight
)
{
   cout << VERSION << endl;

   // This function is just a static helper function to facilitate
   // easily converting a .jfd file to a .tif file in command-line mode

   int returnValue = -1;
   char *errMsg    = 0;
   char *text      = fractal_slurpFile(fileName, &errMsg);

   if(!text)
   {
      cout << "Error reading file: [" << fileName << "]\n";
      cout << errMsg << "\n";
      DADELETE(errMsg);
   }
   else
   {
      int errLineNumber = 0;

      Fractal *theFractal =
         fractal_createFromText(text, &errMsg, &errLineNumber);

      DADELETE(text);

      if(!theFractal)
      {
         cout << errMsg << "\n";
         DADELETE(errMsg);
      }
      else
      {
         char *baseName = ApplicationWindow::getBaseName(fileName);
         char *tiffName = 0;

         DNEW(
            tiffName,
            char[strlen(baseName) + strlen(IMAGE_EXTENSION) + 1]
         );

         sprintf(tiffName, "%s%s", baseName, IMAGE_EXTENSION);
         DADELETE(baseName);

         if(theWidth != 0 || theHeight != 0)
         {
            int fWidth   = theFractal->getWidth();
            int fHeight  = theFractal->getHeight();
            double scale = 0.0;

            if(theHeight == 0)
            {
               scale     = (double)theWidth / (double)fWidth;
               theHeight = (int)(fHeight * scale + 0.5);
            }
            else if(theWidth == 0)
            {
               scale    = (double)theHeight / (double)fHeight;
               theWidth = (int)(fWidth * scale + 0.5);
            }
            else
            {
               scale     = (double)theWidth / (double)fWidth;
               int value = (int)(fHeight * scale + 0.5);

               if(value > theHeight)
               {
                  scale    = (double)theHeight / (double)fHeight;
                  theWidth = (int)(fWidth * scale + 0.5);
               }
               else
               {
                  theHeight = value;
               }
            }

            theFractal->setDimensions(theWidth, theHeight);
         }

         int height = theFractal->getHeight();

         TiffWriter *writer = TiffWriter::makeWriter(
            tiffName, theFractal->getWidth(), height, doAntiAlias, &errMsg
         );

         if(writer != NULL)
         {
            cout << "Writing file: [" << tiffName << "]\n";

            // We're working non-interactively here, so use
            // InfiniteLoopCallback directly (we'll never
            // interrupt processing)

            InfiniteLoopCallback callback;

            theFractal->begin();

            int i = 0;

            while(theFractal->hasMoreRows())
            {
               writer->writeRow(theFractal->nextRow(&callback));
               i++;

               double percent = 100.0 * ((double)i / (double)height);

               printf("\rpercentComplete => %.2f ", percent);
               fflush(stdout);
            }

            printf("\n");

            DDELETE(writer);
            returnValue = 0;
         }
         else
         {
            cout << errMsg << endl;
            DADELETE(errMsg);
         }

         DADELETE(tiffName);
         DDELETE(theFractal);
      }
   }

   return(returnValue);
}

char *ApplicationWindow::getBaseName(const char *name)
{
   char *dotPtr = strrchr(name, '.');
   int count    = (dotPtr == NULL ? strlen(name) : dotPtr - name);

   char *result = 0;

   DNEW(result, char[count + 1]);

   sprintf(result, "%.*s", count, name);

   return(result);
}

void ApplicationWindow::closeEvent(QCloseEvent *e)
{
   if(mCurrentlyDrawing)
   {
      e->ignore();
   }
   else
   {
      if(checkForSave())
         QMainWindow::closeEvent(e);
      else
         e->ignore();
   }
}

void ApplicationWindow::resizeEvent(QResizeEvent *)
{
   if(mResizeTimer->isActive())
      mResizeTimer->stop();

   mResizeTimer->start(250, TRUE);
}

/*****************************************************************************
 * slots
 *****************************************************************************/

void ApplicationWindow::newDoc()
{
   // Create a new (empty) window

   ApplicationWindow *window =
      new ApplicationWindow(mState->clone(), mHome);

   window->show();
}

void ApplicationWindow::load()
{
   // Load a new file

   QString theString = QFileDialog::getOpenFileName(
      mState->getOpenDirectory(), "*"TEXT_EXTENSION, this
   );

   if(!theString.isEmpty())
   {
      // Save off the directory from which we selected our file

      QFileInfo fileInfo(theString);
      mState->setOpenDirectory(fileInfo.dirPath(TRUE).latin1());

      loadFile(theString);
   }

   else
      message("Loading Aborted", 2000);
}

void ApplicationWindow::saveText()
{
   while(true)
   {
      QFileInfo startInfo(
         QDir(mState->getSaveDirectory()),
         QFileInfo(mFileName).fileName()
      );

      QString theString = QFileDialog::getSaveFileName(
         startInfo.filePath(), "*"TEXT_EXTENSION
      );

      if(theString.isEmpty())
      {
         // User cancelled the save

         break;
      }

      // Store off the directory to which we're saving our file

      QFileInfo fileInfo(theString);
      mState->setSaveDirectory(fileInfo.dirPath(TRUE).latin1());

      // If the supplied filename doesn't end in TEXT_EXTENSION,
      // add TEXT_EXTENSION

      int length = theString.length();
      int index  = theString.findRev(TEXT_EXTENSION, -1, FALSE);

      if(index == -1 || index != (int)(length - strlen(TEXT_EXTENSION)))
         theString.append(TEXT_EXTENSION);

      // See if the user is attempting to overwrite an existing file

      int saveFile = true;
      QFile theFile(theString);

      if(theFile.exists())
      {
         int response = QMessageBox::information(
            this,
            "SaveText",
            "Overwrite existing file?",
            "&Yes", "&No", "&Cancel",
            0, 2
         );

         if(response == 1)
            saveFile = false;

         else if(response == 2)
            break;
      }

      if(saveFile)
      {
         char *text = grabText();

         QFile dest(theString);

         if(!dest.open(IO_WriteOnly))
         {
            QString error("Error writing file: [");
            error.append(theString);
            error.append("]");

            QMessageBox::message("Error", error);
         }
         else
         {
            dest.writeBlock(text, strlen(text));
            dest.close();

            // Update our filename (and our caption) to
            // reflect the name we just saved to

            setCurrentFileName(theString.latin1());
            mTextNeedsSaving = FALSE;
         }

         DADELETE(text);
         break;
      }
   }
}

void ApplicationWindow::saveImageFromText()
{
   QString name = getSaveImageName();

   if(!name.isEmpty())
   {
      Fractal *saveImageFractal = NULL;

      if((saveImageFractal = getFractal()) != NULL)
      {
         saveImageFractal->begin();

         saveImage(
            name,
            saveImageFractal->getWidth(),
            saveImageFractal->getHeight(),
            saveImageFractal
         );

         DDELETE(saveImageFractal);
      }
   }
}

void ApplicationWindow::saveImageFromImage()
{
   QString name = getSaveImageName();

   if(!name.isEmpty())
   {
      int width  = 0;
      int height = 0;

      RowSupplier *supplier =
         mSplitter->getView()->getRowSupplier(&width, &height);

      saveImage(name, width, height, supplier);

      DDELETE(supplier);
   }
}

void ApplicationWindow::draw()
{
   // Even though the draw button will be disabled if we're already
   // drawing - we might still wrongly end up here via the associated
   // hot key so make sure we're not already drawing before we draw

   if(!mCurrentlyDrawing)
   {
      Fractal *ptr = NULL;

      if((ptr = getFractal()) != NULL)
      {
         // We need this call to 'show()' to ensure our window
         // is visible before we begin drawing when we're zooming in
         // or out.  This wasn't necessary until we changed our
         // drawing logic to use qApp->processEvents (we used to
         // draw via timer) but qApp-processEvents seems to be faster
         // and it also allows us to 'break' when the fractal is
         // stuck in an infinite loop

         show();

         mSplitter->getView()->newFractal(ptr, this, this);
      }
   }
}

void ApplicationWindow::stop()
{
   mSplitter->getView()->stop();
}

void ApplicationWindow::zoom()
{
   // We may have arrived here via the hot key, ensure that we're
   // actually allowed to zoom (i.e. there is currently a zoom
   // rectangle active)

   if(mZoomButton->isEnabled())
   {
      double x0 = 0;
      double y0 = 0;
      double x1 = 0;
      double y1 = 0;

      if(mSplitter->getView()->getZoomCoordinates(&x0, &y0, &x1, &y1))
         zoomToCoordinates(x0, y0, x1, y1, mState);
   }
}

// When zooming out, we always want to match our parent fractal's
// height and width.  'Settings' is a local class that ensures
// this will be the case.  Previously this class was defined inside
// zoomOut (below) but this apparently caused linking problems
// with at least one version of egcs (egcs-2.91.66) so this class
// was moved outside that method

class Settings : public ZoomInSettings
{
   public:
      ZoomInDialog::WidthOption getZoomInWidthOption()
      {
         return(ZoomInDialog::USE_PARENT_WIDTH);
      }
      ZoomInDialog::HeightOption getZoomInHeightOption()
      {
         return(ZoomInDialog::USE_PARENT_HEIGHT);
      }

      // These methods shouldn't ever actually be called

      int getZoomInWidth()  { return(0); }
      int getZoomInHeight() { return(0); }
};

void ApplicationWindow::zoomOut()
{
   Fractal *ptr = NULL;

   if((ptr = getFractal()) != NULL)
   {
      double w = ptr->getWidth()  / 2.0;
      double h = ptr->getHeight() / 2.0;

      DDELETE(ptr);
      double factor = mState->getZoomOutFactor();

      double x0 = w - factor * w;
      double y0 = h - factor * h;
      double x1 = w + factor * w;
      double y1 = h + factor * h;

      Settings s;
      zoomToCoordinates(x0, y0, x1, y1, &s);
   }
}

void ApplicationWindow::closeDoc()
{
   close();
}

void ApplicationWindow::textChanged()
{
   mTextNeedsSaving = TRUE;

   if(!mCurrentlyDrawing)
   {
      mDrawButton->setEnabled(TRUE);
      mZoomOutButton->setEnabled(TRUE);
   }
}

void ApplicationWindow::setZoomColor()
{
   int red   = 0;
   int green = 0;
   int blue  = 0;

   mState->getZoomColor(&red, &green, &blue);

   QColor currentColor(red, green, blue);

   QColor newColor = QColorDialog::getColor(
      currentColor, this, "colorDialog"
   );

   if(newColor.isValid())
   {
      int newRed   = newColor.red();
      int newGreen = newColor.green();
      int newBlue  = newColor.blue();

      if(newRed   != red   ||
         newGreen != green ||
         newBlue  != blue)
      {
         mSplitter->getView()->setZoomColor(
            newRed, newGreen, newBlue
         );

         mState->setZoomColor(newRed, newGreen, newBlue);
      }
   }
}

void ApplicationWindow::setZoomOutOptions()
{
   ZoomOutDialog theDialog(
      mState->getZoomOutFactor()
   );

   if(theDialog.exec())
   {
      // User pressed 'ok', update our scale factor

      mState->setZoomOutFactor(theDialog.getScaleFactor());
   }
}

void ApplicationWindow::setZoomInOptions()
{
   ZoomInDialog theDialog(
      mState->getZoomInWidthOption(),
      mState->getZoomInWidth(),
      mState->getZoomInHeightOption(),
      mState->getZoomInHeight()
   );

   if(theDialog.exec())
   {
      // User pressed 'ok', update our state information

      ZoomInDialog::WidthOption widthOption   = theDialog.getWidthOption();
      ZoomInDialog::HeightOption heightOption = theDialog.getHeightOption();

      mState->setZoomInWidthOption(widthOption);
      mState->setZoomInHeightOption(heightOption);

      if(widthOption == ZoomInDialog::USER_SPECIFIED_WIDTH)
         mState->setZoomInWidth(theDialog.getUserSpecifiedWidth());

      if(heightOption == ZoomInDialog::USER_SPECIFIED_HEIGHT)
         mState->setZoomInHeight(theDialog.getUserSpecifiedHeight());

      // Ensure FractalView knows the zoom in settings have changed

      mSplitter->getView()->zoomInSettingsChanged();
   }
}

void ApplicationWindow::setAntiAliasOption()
{
   AntiAliasDialog theDialog(mState->getAntiAlias());

   if(theDialog.exec())
   {
      int value = theDialog.getAntiAlias();
      mState->setAntiAlias(value);
   }
}

void ApplicationWindow::doGradientEditor()
{
   // Ensure we've got a formula file loaded ...

   Fractal *ptr = getFractal();

   if(ptr)
   {
      DDELETE(ptr);

      // Ok, scan the lines of our fractal and see if we've got
      // an appropriate 'colors' section from which to begin

      int nLines      = mSplitter->getEdit()->numLines();
      int i           = 0;
      int colorsLine  = -1;
      int formulaLine = -1;

      QRegExp colorsRegex("^\\s*colors\\s*");
      QRegExp formulaRegex("^\\s*formula\\s*");

      for(i = 0; formulaLine == -1 && i < nLines; i ++)
      {
         QString line = mSplitter->getEdit()->textLine(i);

         if(colorsLine == -1)
         {
            if(colorsRegex.search(line) != -1)
               colorsLine = i;
         }

         if(formulaRegex.search(line) != -1)
            formulaLine = i;
      }

      GradientEditor editor(mFileName, this, "GradientEditor", TRUE);

      if(colorsLine != -1)
      {
         QStringList theList;

         for(i = colorsLine + 1; i < formulaLine; i ++)
            theList += mSplitter->getEdit()->textLine(i);

         editor.loadFromStringList(theList);
      }

      if(editor.exec())
      {
         QString theGradient;

         editor.getGradient(theGradient);

         QString theText;

         int stop = (colorsLine == -1 ? formulaLine : colorsLine);

         for(i = 0; i < stop; i ++)
            theText += mSplitter->getEdit()->textLine(i) + "\n";

         theText += theGradient + "\n";

         for(i = formulaLine; i < nLines; i ++)
            theText += mSplitter->getEdit()->textLine(i) + "\n";

         applyBuffer(theText.latin1());
      }
   }
}

void ApplicationWindow::doQuit()
{
   // Ensure that all our ApplicationWindow objects get a chance
   // to save their text before exiting.  We've overridden closeEvent
   // to handle this for ApplicationWindow, here we just ensure every
   // ApplicationWindow's close method is called

   QWidgetList *list = QApplication::topLevelWidgets();
   int allClosed     = TRUE;

   for(QWidgetListIt it(*list); it.current(); ++ it)
   {
      if(it.current()->isA("ApplicationWindow"))
      {
         ApplicationWindow *window = ((ApplicationWindow *)it.current());

         // Don't call 'close' on ourself, we'll handle ensuring that
         // our text was saved below

         if(window != this)
         {
            if(!window->close())
               allClosed = FALSE;
         }
      }
   }

   DDELETE(list);

   if(!close())
      allClosed = FALSE;

   if(allClosed)
      qApp->quit();
}

void ApplicationWindow::clearStatus()
{
   mMessage->setText("");
}

void ApplicationWindow::about()
{
   QMessageBox::message(
      "About",
      VERSION "\n\n"
      "By: " AUTHOR "\n\n"
   );
}

void ApplicationWindow::documentation()
{
   int width  = 0;
   int height = 0;

   mState->getDimensions(&width, &height);

   Help *help = new Help(mHome, width, height, 0, "Help Viewer");

   help->show();
}

void ApplicationWindow::cursorPositionChanged(int row, int column)
{
   QString s;

   // Convert from zero-based numbers to one-based numbers for display

   s = s.sprintf(
      "Ln: %d, Col: %d",
      (row    + 1),
      (column + 1)
   );

   mPosition->setText(s);
}

void ApplicationWindow::resizeTimerFinished()
{
   mState->setDimensions(width(), height());
}

void ApplicationWindow::sizesChanged(int top, int bottom)
{
   mState->setSplitSizes(top, bottom);
}

void ApplicationWindow::revert()
{
   if(mOriginalText)
      mSplitter->getEdit()->setText(mOriginalText);
}

void ApplicationWindow::undo()
{
   mSplitter->getEdit()->undo();
}

void ApplicationWindow::redo()
{
   mSplitter->getEdit()->redo();
}

void ApplicationWindow::findReplace()
{
   if(!mFindReplace)
      mFindReplace = new FindReplaceDialog(this, mSplitter->getEdit());

   mFindReplace->show();
}

void ApplicationWindow::showMatch()
{
   int row    = 0;
   int column = 0;

   QMultiLineEdit *edit = mSplitter->getEdit();

   edit->getCursorPosition(&row, &column);

   QString theLine = edit->textLine(row);
   QChar theChar   = theLine[column];

   if(theChar != '(' && theChar != '{' && theChar != '[' &&
      theChar != ')' && theChar != '}' && theChar != ']')
   {
      return;
   }

   QChar thisChar  = theChar;
   QChar otherChar = '\0';
   int increment   = 1;
   int nLines      = edit->numLines();

   switch((char)thisChar)
   {
      case '(': otherChar = ')'; break;
      case '{': otherChar = '}'; break;
      case '[': otherChar = ']'; break;
      case ')': otherChar = '('; increment = -1; break;
      case '}': otherChar = '{'; increment = -1; break;
      case ']': otherChar = '['; increment = -1; break;
   }

   int currentRow    = row;
   int currentColumn = column;
   int length        = theLine.length();
   int count         = 1;

   while(TRUE)
   {
      // Advance to the next character

      currentColumn += increment;

      if(currentColumn < 0 || currentColumn >= length)
      {
         // We need to go to the next line, advance until we find
         // a non-blank line

         do
         {
            if(increment == -1)
            {
               if(--currentRow == -1)
                  currentRow = nLines - 1;
            }
            else
            {
               if(++currentRow == nLines)
                  currentRow = 0;
            }

            theLine = edit->textLine(currentRow);
            length  = theLine.length();

         }  while(length == 0);

         if(increment == -1)
            currentColumn = length - 1;

         else
            currentColumn = 0;
      }

     // If we're back where we started no match was found - we're done

     if(currentColumn == column &&  currentRow == row)
        return;

      QChar currentChar = theLine[currentColumn];

      if(currentChar == otherChar)
         --count;

      else if(currentChar == thisChar)
         ++count;

      if(count == 0)
         break;
   }

   edit->setCursorPosition(currentRow, currentColumn);
}

void ApplicationWindow::massageCurrentLine(int doIndent)
{
   int row    = 0;
   int column = 0;

   QMultiLineEdit *edit = mSplitter->getEdit();
   edit->getCursorPosition(&row, &column);

   QString currentLine = edit->textLine(row);

   if(doIndent)
   {
      currentLine = "   " + currentLine;
   }
   else
   {
      currentLine = currentLine.stripWhiteSpace();
   }

   // Disable auto update temporarily to reduce flicker since
   // in order to replace the current line we have to delete then insert

   edit->setAutoUpdate(FALSE);
   edit->removeLine(row);
   edit->insertLine(currentLine, row);
   edit->setAutoUpdate(TRUE);
   edit->repaint();

   // Also the cursor comes out one line too high so reset the cursor
   // to the correct line

   edit->setCursorPosition(row, column);

   // Lastly, these sorts of edits don't seem to register as changes
   // to the text buffer so indicate this manually

   textChanged();
}

void ApplicationWindow::indentCurrentLine()
{
   massageCurrentLine(TRUE);
}

void ApplicationWindow::unindentCurrentLine()
{
   massageCurrentLine(FALSE);
}

void ApplicationWindow::fontSizeChanged(int index)
{
   int count = sizeof(fontSizes) / sizeof(fontSizes[0]);

   for(int i = 0; i < count; i ++)
      mFontSizes->setItemChecked(i, i == index);

   mState->setFontSize(atoi(fontSizes[index]));

   // Set our font size

   QFont current = mSplitter->getEdit()->font();
   current.setPointSize(mState->getFontSize());
   mSplitter->getEdit()->setFont(current);

   // If we're changing from a smaller font size to a larger size,
   // setting the font alone isn't enough (the right hand side of the
   // text will be clipped to the original boundary).  To ensure that
   // the text is fully and properly displayed at the new size, we
   // do a 'setText' using the current contents.  Note that we don't
   // want this action to affect the state of the 'mTextNeedsSaving'
   // flag so we save and restore that flag as well.

   int flag   = mTextNeedsSaving;
   char *text = grabText();

   mSplitter->getEdit()->setText(text);

   mTextNeedsSaving = flag;
   DADELETE(text);
}

void ApplicationWindow::saveCancelled()
{
   mSaveCancelled = TRUE;
}

/*****************************************************************************
 * Functions to create our tool bar, menu bar and status bar
 *****************************************************************************/

void ApplicationWindow::addToolBar()
{
   // create our toolbar

   QToolBar *fileTools = new QToolBar(this, "fileTools");

   // Create all our icons

   QPixmap openIcon            = QPixmap(_open);
   QPixmap drawIcon            = QPixmap(_draw);
   QPixmap drawDisabledIcon    = QPixmap(_draw_disabled);
   QPixmap zoomIcon            = QPixmap(_zoom);
   QPixmap zoomDisabledIcon    = QPixmap(_zoom_disabled);
   QPixmap zoomOutIcon         = QPixmap(_zoomout);
   QPixmap zoomOutDisabledIcon = QPixmap(_zoomout_disabled);
   QPixmap stopIcon            = QPixmap(_stop);
   QPixmap stopDisabledIcon    = QPixmap(_stop_disabled);

   // Create icon sets for zoom, zoomout, draw and stop

   DNEW(mDrawIconSet,     QIconSet(drawIcon));
   DNEW(mZoomIconSet,     QIconSet(zoomIcon));
   DNEW(mZoomOutIconSet,  QIconSet(zoomOutIcon));
   DNEW(mStopIconSet,     QIconSet(stopIcon));

   mDrawIconSet->setPixmap(
      drawDisabledIcon,
      QIconSet::Small,
      QIconSet::Disabled
   );

   mZoomIconSet->setPixmap(
      zoomDisabledIcon,
      QIconSet::Small,
      QIconSet::Disabled
   );

   mZoomOutIconSet->setPixmap(
      zoomOutDisabledIcon,
      QIconSet::Small,
      QIconSet::Disabled
   );

   mStopIconSet->setPixmap(
      stopDisabledIcon,
      QIconSet::Small,
      QIconSet::Disabled
   );

   // Now create our tool buttons

   (void)new QToolButton(
      openIcon,
      "Open File",
      0,
      this,
      SLOT(load()),
      fileTools,
      "Open File"
   );

   mDrawButton = new QToolButton(
      *mDrawIconSet,
      "Draw",
      0,
      this,
      SLOT(draw()),
      fileTools,
      "Draw"
   );

   mZoomButton = new QToolButton(
      *mZoomIconSet,
      "Zoom",
      0,
      this,
      SLOT(zoom()),
      fileTools,
      "Zoom"
   );

   mZoomOutButton = new QToolButton(
      *mZoomOutIconSet,
      "Zoom Out",
      0,
      this,
      SLOT(zoomOut()),
      fileTools,
      "Zoom Out"
   );

   mStopButton = new QToolButton(
      *mStopIconSet,
      "Stop",
      0,
      this,
      SLOT(stop()),
      fileTools,
      "Stop"
   );
}

void ApplicationWindow::addFileMenu(QMenuBar *menuBar)
{
   // Create a "File =>" popup menu with accelerator keys

   QPopupMenu *file = new QPopupMenu();

   menuBar->insertItem("&File", file);

   // Create our save image popup menu first ...

   mSaveImageMenu = new QPopupMenu(file);

   mSaveImageMenu->insertItem(
      "Generate From Text",
      this,
      SLOT(saveImageFromText()),
      CTRL + Key_G
   );

   mUseCurrentImageIndex = mSaveImageMenu->insertItem(
      "Use Current Image",
      this,
      SLOT(saveImageFromImage()),
      CTRL + Key_U
   );

   // Initially we don't have an image available to save from so
   // disable this menu item

   mSaveImageMenu->setItemEnabled(mUseCurrentImageIndex, FALSE);

   // Now set up our table to fill in the 'File' popup menu ...

   typedef struct
   {
      char *text;
      char *slot;
      int key;
      QPopupMenu *menu;

   } Entry;

   Entry entries[] =
   {
      { "New",        SLOT(newDoc()),    CTRL + Key_N, 0              },
      { "Save Text",  SLOT(saveText()),  CTRL + Key_T, 0              },
      { "Save Image", 0,                 0,            mSaveImageMenu },
      { 0,            0,                 0,            0              },
      { "Open",       SLOT(load()),      CTRL + Key_O, 0              },
      { "Draw",       SLOT(draw()),      CTRL + Key_D, 0              },
      { "Stop",       SLOT(stop()),      CTRL + Key_S, 0              },
      { "Zoom",       SLOT(zoom()),      CTRL + Key_Z, 0              },
      { "ZoomOut",    SLOT(zoomOut()),   ALT  + Key_Z, 0              },
      { 0,            0,                 0,            0              },
      { "Close",      SLOT(closeDoc()),  CTRL + Key_W, 0              },
      { "Quit",       SLOT(doQuit()),    CTRL + Key_Q, 0              },
   };

   int size = sizeof(entries) / sizeof(entries[0]);

   for(int i = 0; i < size; i ++)
   {
      if(entries[i].text)
      {
         if(entries[i].menu)
         {
            file->insertItem(entries[i].text, entries[i].menu);
         }
         else
         {
            file->insertItem(
               entries[i].text,
               this,
               entries[i].slot,
               entries[i].key
            );
         }
      }
      else
         file->insertSeparator();
   }
}

void ApplicationWindow::addEditMenu(QMenuBar *menuBar)
{
   QPopupMenu *edit = new QPopupMenu();
   menuBar->insertItem("&Edit", edit);

   QObject *target = mSplitter->getEdit();

   edit->insertItem(
      "Cut",
      target,
      SLOT(cut()),
      CTRL + Key_X
   );

   edit->insertItem(
      "Copy",
      target,
      SLOT(copy()),
      CTRL + Key_C
   );

   edit->insertItem(
      "Paste",
      target,
      SLOT(paste()),
      CTRL + Key_V
   );

   edit->insertItem(
      "Select All",
      target,
      SLOT(selectAll()),
      CTRL + Key_A
   );

   edit->insertItem(
      "Deselect",
      target,
      SLOT(deselect()),
      ALT + Key_D
   );

   edit->insertSeparator();

   edit->insertItem(
      "Revert",
      this,
      SLOT(revert()),
      CTRL + Key_R
   );

   edit->insertItem(
      "Undo",
      this,
      SLOT(undo()),
      ALT + Key_U
   );

   edit->insertItem(
      "ReDo",
      this,
      SLOT(redo()),
      ALT + Key_R
   );

   edit->insertItem(
      "Find/Replace",
      this,
      SLOT(findReplace()),
      CTRL + Key_1
   );

   edit->insertItem(
      "Show Match",
      this,
      SLOT(showMatch()),
      CTRL + Key_2
   );

   edit->insertItem(
      "Unindent Current Line",
      this,
      SLOT(unindentCurrentLine()),
      CTRL + Key_3
   );

   edit->insertItem(
      "Indent Current Line",
      this,
      SLOT(indentCurrentLine()),
      CTRL + Key_4
   );
}

void ApplicationWindow::addMappingMenu(QMenuBar *menuBar)
{
   QPopupMenu *mapping = new QPopupMenu();
   menuBar->insertItem("&Mapping", mapping);

   mapping->insertItem(
      "Mapping Reset",
      this,
      SLOT(mappingReset()),
      Key_F1
   );

   mapping->insertSeparator();

   mapping->insertItem(
      "Image Half Size",
      this,
      SLOT(mappingHalf()),
      Key_F2
   );

   mapping->insertItem(
      "Image Double Size",
      this,
      SLOT(mappingDouble()),
      Key_F3
   );

   mapping->insertItem(
      "Image 10% Smaller",
      this,
      SLOT(mappingTenPercentSmaller()),
      Key_F4
   );

   mapping->insertItem(
      "Image 10% Larger",
      this,
      SLOT(mappingTenPercentLarger()),
      Key_F5
   );

   mapping->insertSeparator();

   mapping->insertItem(
      "Mirror View in X",
      this,
      SLOT(mappingViewXMirror()),
      CTRL + Key_F5
   );

   mapping->insertItem(
      "Mirror View in Y",
      this,
      SLOT(mappingViewYMirror()),
      CTRL + Key_F6
   );

   mapping->insertSeparator();

   mapping->insertItem(
      "View Half Size",
      this,
      SLOT(mappingViewHalf()),
      Key_F6
   );

   mapping->insertItem(
      "View Double Size",
      this,
      SLOT(mappingViewDouble()),
      Key_F7
   );

   mapping->insertItem(
      "View 10% Smaller",
      this,
      SLOT(mappingViewTenPercentSmaller()),
      Key_F8
   );

   mapping->insertItem(
      "View 10% Larger",
      this,
      SLOT(mappingViewTenPercentLarger()),
      Key_F9
   );

   mapping->insertSeparator();

   typedef struct
   {
      char *text;
      int key;
      char *slotTenPercent;
      char *slotFiftyPercent;
      char *slotOneHundredPercent;

   } Entry;

   Entry entries[] =
   {
      {
         "Pan Right",
         Key_F9,
         SLOT(slotPanRightTenPercent()),
         SLOT(slotPanRightFiftyPercent()),
         SLOT(slotPanRightOneHundredPercent())
      },
      {
         "Pan Left",
         Key_F10,
         SLOT(slotPanLeftTenPercent()),
         SLOT(slotPanLeftFiftyPercent()),
         SLOT(slotPanLeftOneHundredPercent())
      },
      {
         "Pan Up",
         Key_F11,
         SLOT(slotPanUpTenPercent()),
         SLOT(slotPanUpFiftyPercent()),
         SLOT(slotPanUpOneHundredPercent())
      },
      {
         "Pan Down",
         Key_F12,
         SLOT(slotPanDownTenPercent()),
         SLOT(slotPanDownFiftyPercent()),
         SLOT(slotPanDownOneHundredPercent())
      },
   };

   int size = sizeof(entries) / sizeof(entries[0]);

   for(int i = 0; i < size; i ++)
   {
      QPopupMenu *menu = new QPopupMenu(mapping);

      menu->insertItem(
         "10%",  this, entries[i].slotTenPercent, SHIFT + entries[i].key
      );

      menu->insertItem(
         "50%",  this, entries[i].slotFiftyPercent, CTRL + entries[i].key
      );

      menu->insertItem(
         "100%", this, entries[i].slotOneHundredPercent, ALT + entries[i].key
      );

      mapping->insertItem(entries[i].text, menu);
   }
}

void ApplicationWindow::addOptionsMenu(QMenuBar *menuBar)
{
   QPopupMenu *options = new QPopupMenu();

   menuBar->insertItem("&Options", options);

   DNEW(mFontSizes, QPopupMenu(options));
   int count  = sizeof(fontSizes) / sizeof(fontSizes[0]);

   mFontSizes->setCheckable(TRUE);

   for(int i = 0; i < count; i ++)
   {
      mFontSizes->insertItem(fontSizes[i], i);

      if(atoi(fontSizes[i]) == mState->getFontSize())
         mFontSizes->setItemChecked(i, TRUE);
   }

   QObject::connect(
      mFontSizes,
      SIGNAL(activated(int)),
      this,
      SLOT(fontSizeChanged(int))
   );

   options->insertItem(
      "Font Size",
      mFontSizes,
      CTRL + Key_F
   );

   options->insertItem(
      "Zoom Rectangle Color",
      this,
      SLOT(setZoomColor()),
      ALT + Key_C
   );

   options->insertItem(
      "Zoom Out Options",
      this,
      SLOT(setZoomOutOptions()),
      ALT + Key_T
   );

   options->insertItem(
      "Zoom In Options",
      this,
      SLOT(setZoomInOptions()),
      ALT + Key_I
   );

   options->insertItem(
      "Anti Alias Option",
      this,
      SLOT(setAntiAliasOption()),
      ALT + Key_A
   );

   options->insertItem(
      "Gradient Editor",
      this,
      SLOT(doGradientEditor()),
      ALT + Key_G
   );
}

void ApplicationWindow::addHelpMenu(QMenuBar *menuBar)
{
   QPopupMenu *help = new QPopupMenu(this);
   menuBar->insertSeparator();
   menuBar->insertItem("&Help", help);

   help->insertItem("About",         this, SLOT(about()));
   help->insertItem("Documentation", this, SLOT(documentation()));
}

void ApplicationWindow::addMenuBar()
{
   QMenuBar *bar = menuBar();

   addFileMenu(bar);
   addEditMenu(bar);
   addMappingMenu(bar);
   addOptionsMenu(bar);
   addHelpMenu(bar);

   bar->setSeparator(QMenuBar::InWindowsStyle);
}

void ApplicationWindow::addStatusBar()
{
   // We want our status bar to have:
   //    (a) a label area for displaying messages
   //    (b) a label area for display the current x/y cursor location
   //        for our text editor
   //    (c) a progress bar

   // First the general message area

   mMessage = new QLabel(statusBar(), "mMessage");
   mMessage->setAlignment(AlignLeft | AlignVCenter);
   mMessage->setText("Message");
   mMessage->setMinimumHeight(mMessage->sizeHint().height());
   mMessage->setText("");

   statusBar()->addWidget(mMessage, 8);

   // Now the cursor position label area

   mPosition = new QLabel(statusBar(), "mPosition");
   mPosition->setAlignment(AlignHCenter | AlignVCenter);
   mPosition->setMinimumHeight(mMessage->sizeHint().height());

   statusBar()->addWidget(mPosition, 3);

   // Now the progress bar

   mProgress = new QProgressBar(statusBar(), "mProgress");
   mProgress->setTotalSteps(100);
   mProgress->setProgress(0);

   statusBar()->addWidget(mProgress, 4);
}

/*****************************************************************************
 * Filename related utility functions
 *****************************************************************************/

QString ApplicationWindow::getSaveImageName()
{
   char *baseName = getBaseName();
   char *name     = 0;

   DNEW(name, char[strlen(baseName) + 1 + strlen(IMAGE_EXTENSION)]);

   sprintf(name, "%s%s", baseName, IMAGE_EXTENSION);

   DADELETE(baseName);

   QString saveImageName("");

   while(true)
   {
      QFileInfo startInfo(
         QDir(mState->getSaveDirectory()),
         QFileInfo(name).fileName()
      );

      QString theString = QFileDialog::getSaveFileName(
         startInfo.filePath(), "*"IMAGE_EXTENSION
      );

      if(theString.isEmpty())
      {
         // User cancelled save - we're done

         break;
      }

      // Store off the directory to which we're saving our file

      QFileInfo fileInfo(theString);
      mState->setSaveDirectory(fileInfo.dirPath(TRUE).latin1());

      // If the supplied filename doesn't end in IMAGE_EXTENSION,
      // add IMAGE_EXTENSION

      int length = theString.length();
      int index  = theString.findRev(IMAGE_EXTENSION, -1, FALSE);

      if(index == -1 || index != (int)(length - strlen(IMAGE_EXTENSION)))
         theString.append(IMAGE_EXTENSION);

      // See if the user is attempting to overwrite an existing file

      QFile theFile(theString);

      if(!theFile.exists())
      {
         saveImageName = theString;
         break;
      }

      int response = QMessageBox::information(
         this,
         "SaveImage",
         "Overwrite existing file?",
         "&Yes", "&No", "&Cancel",
         0, 2
      );

      if(response == 0)
      {
         saveImageName = theString;
         break;
      }

      if(response == 2)
      {
         break;
      }
   }

   DADELETE(name);

   return(saveImageName);
}

char *ApplicationWindow::getBaseName() const
{
   return(getBaseName(mFileName));
}

char *ApplicationWindow::getZoomName() const
{
   //---------------------------------------------------------------
   // Determine our zoom name, the naming rules work like this:
   //
   //    (a) If the base name does not end in 3 digits, the zoom
   //        name will be: baseName + "_001"
   //
   //    (b) If the base name does end in 3 digits (meaning that it is
   //        very likely that the base name is a zoom name itself), the
   //        zoom name will be generated by incrementing the 3 digit
   //        number
   //
   //    (c) If the base name ends in "999", the zoom name will
   //        end in "000"
   //---------------------------------------------------------------

   char *zoomName = NULL;
   char *baseName = getBaseName();
   int length     = strlen(baseName);
   int flag       = 0;

   if(length > 3)
   {
      char ending[4] = {
         baseName[length - 3],
         baseName[length - 2],
         baseName[length - 1],
         '\0'
      };

      if(!isdigit(ending[0]) || !isdigit(ending[1]) || !isdigit(ending[2]))
      {
         flag = 1;
      }
      else
      {
         for(int i = 2; i >= 0; i --)
         {
            if(ending[i] == '9')
               ending[i] = '0';

            else
            {
               ending[i]++;
               break;
            }
         }

         DNEW(zoomName, char[length + 1 + strlen(TEXT_EXTENSION)]);

         sprintf(
            zoomName,
            "%.*s%s%s",
            length - 3,
            baseName,
            ending,
            TEXT_EXTENSION
         );
      }
   }
   else
      flag = 1;

   if(flag)
   {
      DNEW(zoomName, char[length + 1 + strlen("_001"TEXT_EXTENSION)]);
      sprintf(zoomName, "%s_001%s", baseName, TEXT_EXTENSION);
   }

   DADELETE(baseName);

   return(zoomName);
}

void ApplicationWindow::setCurrentFileName(const char *name)
{
   if(mFileName)
   {
      DADELETE(mFileName);
   }

   DNEW(mFileName, char[strlen(name) + 1]);
   strcpy(mFileName, name);

   setCaption(mFileName);
}

char *ApplicationWindow::grabText() const
{
   // JFD: Grab all text from our MultiLineEditWindow (there must be
   //      a more straightforward way of doing this!)

   int size = 0;
   int i    = 0;
   int nLines = mSplitter->getEdit()->numLines();

   for(i = 0; i < nLines; i ++)
      size += strlen(mSplitter->getEdit()->textLine(i)) + strlen("\n");

   char *text = 0;

   DNEW(text, char[size + 1]);

   *text      = '\0';

   for(i = 0; i < nLines; i ++)
   {
      sprintf(
         text + strlen(text),
         "%s\n",
         mSplitter->getEdit()->textLine(i).latin1()
      );
   }

   return(text);
}

void ApplicationWindow::setOriginalText(const char *text)
{
   if(mOriginalText)
   {
      DADELETE(mOriginalText);
   }

   DNEW(mOriginalText, char[strlen(text) + 1]);

   strcpy(mOriginalText, text);
}

/*****************************************************************************
 * Additional assorted utility routines
 *****************************************************************************/

void ApplicationWindow::saveImage(
   QString &name,
   int width,
   int height,
   RowSupplier *supplier
)
{
   const char *fileName = name;

   char *errMsg       = NULL;
   TiffWriter *writer = TiffWriter::makeWriter(
      fileName, width, height, mState->getAntiAlias(), &errMsg
   );

   if(writer == NULL)
   {
      QString error(errMsg);

      QMessageBox::message("Error", error);

      DADELETE(errMsg);
      return;
   }

   QString s;
   s.sprintf("   Saving file: [%s]   ", fileName);

   QProgressDialog *progressDialog = 0;

   DNEW(
      progressDialog,
      QProgressDialog(s, "Cancel", height, this, "progressDialog", false)
   );

   progressDialog->setMinimumDuration(0);
   progressDialog->setProgress(0);
   progressDialog->show();

   mSaveCancelled = FALSE;

   QObject::connect(
      progressDialog,
      SIGNAL(cancelled()),
      this,
      SLOT(saveCancelled())
   );

   QInfiniteLoopCallback callback(&mSaveCancelled);

   for(int i = 0; i < height; i ++)
   {
      unsigned char *row = supplier->nextRow(&callback);

      if(mSaveCancelled)
         break;

      writer->writeRow(row);
      progressDialog->setProgress(i + 1);

      qApp->processEvents();
   }

   DDELETE(progressDialog);

   if(mSaveCancelled)
   {
      QFile theFile(writer->getName());
      theFile.remove();

      message("Save Aborted", 2000);
   }
   else
   {
      message("Save Complete", 2000);
   }

   DDELETE(writer);
}

void ApplicationWindow::loadFile(const char *fileName)
{
   // Before this function returns, it is our responsibility to ensure
   // that our window's filename and caption is set appropriately

   QFile theFile(fileName);

   if(!theFile.open(IO_ReadOnly))
   {
      QString error("Unable to open file: [");
      error.append(fileName);
      error.append("]");

      QMessageBox::message("Error", error);

      // Do we have a filename? If not, use our default name

      if(!mFileName)
         setCurrentFileName(DEFAULT_NAME);
   }
   else
   {
      if(!checkForSave())
         return;

      mSplitter->getEdit()->setAutoUpdate(FALSE);
      mSplitter->getEdit()->clear();

      QTextStream theStream(&theFile);
      mSplitter->getEdit()->setText(theStream.read());
      theFile.close();

      mSplitter->getEdit()->setAutoUpdate(TRUE);
      mSplitter->getEdit()->repaint();
      mTextNeedsSaving = FALSE;

      // Sync our filename with the selected file

      setCurrentFileName(fileName);

      // If we're not already drawing, enable our zoom out and draw
      // buttons

      if(!mCurrentlyDrawing)
      {
         mDrawButton->setEnabled(TRUE);
         mZoomOutButton->setEnabled(TRUE);
      }

      // Save the original

      char *text = grabText();
      setOriginalText(text);
      DADELETE(text);
   }
}

void ApplicationWindow::message(char *text, int timeoutInMillis) const
{
   mMessage->setText(text);
   QTimer::singleShot(timeoutInMillis, (QObject *)this, SLOT(clearStatus()));
}

int ApplicationWindow::checkForSave()
{
   int returnValue = TRUE;

   if(mTextNeedsSaving)
   {
      QString s("File: [");
      s.append(mFileName);
      s.append("] has not been saved\n");
      s.append("do you wish to save it?");

      int response = QMessageBox::information(
         this,
         "SaveText",
         s,
         "&Yes", "&No", "&Cancel", 0, 2
      );

      if(response == 0)
         saveText();

      else if(response == 2)
         returnValue = FALSE;
   }

   return(returnValue);
}

static char *getZoomBuffer(
   char *text,
   QMultiLineEdit *edit,
   double x0,
   double y0,
   double x1,
   double y1,
   void *clientData,
   void (*mapFunction)(
      FractalDefinition *parent,
      FractalDefinition *child,
      double x0, double y0, double x1, double y1,
      void *clientData                
   )
)
{
   int success         = 0;
   char *zoomBuffer    = 0;
   char *errorMessage  = 0;
   int errorLineNumber = 0;

   success = fractal_createZoomBuffer(
      text,
      &zoomBuffer,
      x0, y0, x1, y1,
      &errorMessage,
      &errorLineNumber,
      clientData,
      mapFunction
   );

   DADELETE(text);

   if(!success)
   {
      QMessageBox::message("Error", errorMessage);

      // Move the cursor to the line containing the error.  Note
      // that MultiLineEdit is zero-based while our error line
      // numbers are one-based so we have to subtract 1 to
      // position the cursor appropriately

      edit->setCursorPosition(errorLineNumber - 1, 0);

      DADELETE(errorMessage);
   }

   return(zoomBuffer);
}

void ApplicationWindow::zoomToCoordinates(
   double x0, double y0, double x1, double y1, ZoomInSettings *s
)
{
   char *zoomBuffer = getZoomBuffer(
      grabText(), mSplitter->getEdit(),
      x0, y0, x1, y1, (void *)s, Map::mapFunction
   );

   if(zoomBuffer)
   {
      char *zoomName = getZoomName();

      ApplicationWindow *window = new ApplicationWindow(
         mState->clone(),
         mHome,
         zoomName,
         zoomBuffer,
         TRUE
      );

      DADELETE(zoomBuffer);

      window->show();
   }
}

Fractal *ApplicationWindow::getFractal()
{
   int errorLineNumber = 0;
   char *text          = grabText();
   char *errorMessage  = 0;
   Fractal *ptr        = fractal_createFromText(
      text, &errorMessage, &errorLineNumber
   );

   DADELETE(text);

   if(ptr == NULL)
   {
      QMessageBox::message("Error", errorMessage);

      int length        = strlen(errorMessage);
      int caretOffset   = -1;
      int newlineOffset = -1;

      for(int i = length - 1; i >= 0; i --)
      {
         switch(errorMessage[i])
         {
            case '^':
            {
               if(caretOffset == -1)
                  caretOffset = i;
            }
            break;

            case '\r':
            case '\n':
            {
               if(newlineOffset == -1)
                  newlineOffset = i;
            }
            break;
         }
      }

      int offset = 0;

      if(caretOffset > newlineOffset && newlineOffset != -1)
      {
         offset = (caretOffset - newlineOffset) - 1;
      }

      // Move the cursor to the line containing the error.  Note
      // that MultiLineEdit is zero-based while our error line
      // numbers are one-based so we have to subtract 1 to
      // position the cursor appropriately

      mSplitter->getEdit()->setCursorPosition(errorLineNumber - 1, offset);

      DADELETE(errorMessage);
   }
   else
   {
      if(false)
         cout << *ptr << endl;
   }

   return(ptr);
}

static void mappingResetMapFunction(
   FractalDefinition *,
   FractalDefinition *child,
   double, double, double, double, void *
)
{
   // Ultimately it might be worthwhile to have a dialog box to allow
   // the user to specify his/her preferences for these values ...

   child->xStart      = -2;
   child->yStart      = -2;
   child->xEnd        = 2;
   child->yEnd        = 2;
   child->pixelWidth  = 200;
   child->pixelHeight = 200;
}

void ApplicationWindow::applyBuffer(const char *theBuffer)
{
   // First, we need to save off the current x/y cursor location

   int row    = 0;
   int column = 0;

   QMultiLineEdit *edit = mSplitter->getEdit();
   int nLines           = edit->numLines();

   edit->getCursorPosition(&row, &column);

   // Now set our editor text to the zoom buffer and restore
   // our original row/column position (adjusting for possible changes
   // in the number of lines due to our editing of the text ...
 
   edit->setText(theBuffer);
   edit->setCursorPosition(row + (edit->numLines() - nLines), column);
}

void ApplicationWindow::applyZoomBuffer(char *zoomBuffer)
{
   if(zoomBuffer)
   {
      applyBuffer(zoomBuffer);
      DADELETE(zoomBuffer);
   }
}

void ApplicationWindow::mappingReset()
{
   applyZoomBuffer(
      getZoomBuffer(
         grabText(), mSplitter->getEdit(),
         0.0, 0.0, 0.0, 0.0, NULL, mappingResetMapFunction
      )
   );
}

static void mappingScaleFunction(
   FractalDefinition *parent,
   FractalDefinition *child,
   double, double, double, double, void *clientData
)
{
   double factor = *((double *)clientData);

   child->xStart      = parent->xStart;
   child->yStart      = parent->yStart;
   child->xEnd        = parent->xEnd;
   child->yEnd        = parent->yEnd;
   child->pixelWidth  = parent->pixelWidth * factor;
   child->pixelHeight = parent->pixelHeight * factor;
}

typedef struct
{
   enum { PAN_LEFT, PAN_RIGHT, PAN_UP, PAN_DOWN };
   double factor;
   int direction;

} PanData;

static void mappingPanFunction(
   FractalDefinition *parent,
   FractalDefinition *child,
   double, double, double, double, void *clientData
)
{
   PanData *p = (PanData *)clientData;

   child->xStart      = parent->xStart;
   child->yStart      = parent->yStart;
   child->xEnd        = parent->xEnd;
   child->yEnd        = parent->yEnd;
   child->pixelWidth  = parent->pixelWidth;
   child->pixelHeight = parent->pixelHeight;

   if(p->direction == PanData::PAN_LEFT ||
      p->direction == PanData::PAN_RIGHT)
   {
      double offset = (parent->xEnd - parent->xStart) * p->factor;

      if(p->direction == PanData::PAN_LEFT)
         offset = -offset;

      child->xStart = parent->xStart + offset;
      child->xEnd   = parent->xEnd   + offset;
   }
   else
   {
      double offset = (parent->yEnd - parent->yStart) * p->factor;

      if(p->direction == PanData::PAN_DOWN)
         offset = -offset;

      child->yStart = parent->yStart + offset;
      child->yEnd   = parent->yEnd   + offset;
   }
}

static void mappingScaleViewFunction(
   FractalDefinition *parent,
   FractalDefinition *child,
   double, double, double, double, void *clientData
)
{
   double factor = *((double *)clientData);

   double xCenter = (parent->xStart + parent->xEnd) / 2.0;
   double yCenter = (parent->yStart + parent->yEnd) / 2.0;

   child->xStart = xCenter + (parent->xStart - xCenter) * factor;
   child->xEnd   = xCenter + (parent->xEnd   - xCenter) * factor;
   child->yStart = yCenter + (parent->yStart - yCenter) * factor;
   child->yEnd   = yCenter + (parent->yEnd   - yCenter) * factor;

   child->pixelWidth  = parent->pixelWidth;
   child->pixelHeight = parent->pixelHeight;
}

void ApplicationWindow::mappingScale(double factor)
{
   applyZoomBuffer(
      getZoomBuffer(
         grabText(), mSplitter->getEdit(),
         0.0, 0.0, 0.0, 0.0, &factor, mappingScaleFunction
      )
   );
}

static void mappingMirrorFunction(
   FractalDefinition *parent,
   FractalDefinition *child,
   double, double, double, double, void *clientData
)
{
   int yFlag = *((int *)clientData);

   child->xStart = parent->xStart;
   child->xEnd   = parent->xEnd;
   child->yStart = parent->yStart;
   child->yEnd   = parent->yEnd;

   double *firstPtr  = NULL;
   double *secondPtr = NULL;

   if(yFlag)
   {
      firstPtr  = &child->yStart;
      secondPtr = &child->yEnd;
   }
   else
   {
      firstPtr  = &child->xStart;
      secondPtr = &child->xEnd;
   }

   double temp = *firstPtr;
   *firstPtr   = *secondPtr;
   *secondPtr  = temp;

   child->pixelWidth  = parent->pixelWidth;
   child->pixelHeight = parent->pixelHeight;
}

void ApplicationWindow::mappingMirror(int yFlag)
{
   applyZoomBuffer(
      getZoomBuffer(
         grabText(), mSplitter->getEdit(),
         0.0, 0.0, 0.0, 0.0, &yFlag, mappingMirrorFunction
      )
   );
}

void ApplicationWindow::mappingPan(double factor, int direction)
{
   PanData data;

   data.factor    = factor;
   data.direction = direction;

   applyZoomBuffer(
      getZoomBuffer(
         grabText(), mSplitter->getEdit(),
         0.0, 0.0, 0.0, 0.0, &data, mappingPanFunction
      )
   );
}

void ApplicationWindow::mappingScaleView(double factor)
{
   applyZoomBuffer(
      getZoomBuffer(
         grabText(), mSplitter->getEdit(),
         0.0, 0.0, 0.0, 0.0, &factor, mappingScaleViewFunction
      )
   );
}

void ApplicationWindow::mappingHalf()
{
   mappingScale(0.5);
}

void ApplicationWindow::mappingDouble()
{
   mappingScale(2.0);
}

void ApplicationWindow::mappingTenPercentSmaller()
{
   mappingScale(0.9);
}

void ApplicationWindow::mappingTenPercentLarger()
{
   mappingScale(1.1);
}

void ApplicationWindow::mappingViewXMirror()
{
   mappingMirror(0);
}

void ApplicationWindow::mappingViewYMirror()
{
   mappingMirror(1);
}

void ApplicationWindow::mappingViewHalf()
{
   mappingScaleView(0.5);
}

void ApplicationWindow::mappingViewDouble()
{
   mappingScaleView(2.0);
}

void ApplicationWindow::mappingViewTenPercentSmaller()
{
   mappingScaleView(0.9);
}

void ApplicationWindow::mappingViewTenPercentLarger()
{
   mappingScaleView(1.1);
}

void ApplicationWindow::slotPanRightTenPercent()
{
   mappingPan(0.1, PanData::PAN_RIGHT);
}

void ApplicationWindow::slotPanRightFiftyPercent()
{
   mappingPan(0.5, PanData::PAN_RIGHT);
}

void ApplicationWindow::slotPanRightOneHundredPercent()
{
   mappingPan(1.0, PanData::PAN_RIGHT);
}

void ApplicationWindow::slotPanLeftTenPercent()
{
   mappingPan(0.1, PanData::PAN_LEFT);
}

void ApplicationWindow::slotPanLeftFiftyPercent()
{
   mappingPan(0.5, PanData::PAN_LEFT);
}

void ApplicationWindow::slotPanLeftOneHundredPercent()
{
   mappingPan(1.0, PanData::PAN_LEFT);
}

void ApplicationWindow::slotPanUpTenPercent()
{
   mappingPan(0.1, PanData::PAN_UP);
}

void ApplicationWindow::slotPanUpFiftyPercent()
{
   mappingPan(0.5, PanData::PAN_UP);
}

void ApplicationWindow::slotPanUpOneHundredPercent()
{
   mappingPan(1.0, PanData::PAN_UP);
}

void ApplicationWindow::slotPanDownTenPercent()
{
   mappingPan(0.1, PanData::PAN_DOWN);
}

void ApplicationWindow::slotPanDownFiftyPercent()
{
   mappingPan(0.5, PanData::PAN_DOWN);
}

void ApplicationWindow::slotPanDownOneHundredPercent()
{
   mappingPan(1.0, PanData::PAN_DOWN);
}
