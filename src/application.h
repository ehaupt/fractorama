#ifndef APPLICATION_H
#   define APPLICATION_H

// Required Headers

#include <qmainwindow.h>
#include <qvaluelist.h>
#include "fractalobserver.h"
#include "statesupplier.h"

// Forward Declarations

class QToolBar;
class Fractal;
class QProgressDialog;
class TiffWriter;
class QToolButton;
class QIconSet;
class QLabel;
class QPushButton;
class QProgressBar;
class QMenuBar;
class FractalSplitter;
class State;
class QTimer;
class ZoomInSettings;
class RowSupplier;
class FindReplaceDialog;

class ApplicationWindow :
   public QMainWindow, public FractalObserver, public StateSupplier
{
   Q_OBJECT

   public:

      ApplicationWindow(
         State *theState,
         QString home,
         const char *fileToLoad = 0,
         const char *contents   = 0,
         int drawImmediately    = FALSE
      );

      ~ApplicationWindow();

      // Functions to fulfill our role as "FractalObserver"

      void percentComplete(double percent);
      void drawingStarted();
      void drawingFinished(char *text, int wasCancelled);
      void zoomAllowed();
      void zoomNotAllowed();

      // Method to fulfill our role as "StateSupplier"

      State *getState();

      static int writeTiffFile(
         const char *fileName,
         int doAntiAlias,
         int theWidth,
         int theHeight
      );

      static char *getBaseName(const char *name);

   protected:
      void closeEvent(QCloseEvent *);
      void resizeEvent(QResizeEvent *);
    
   private slots:
      void newDoc();
      void load();
      void saveText();
      void saveImageFromText();
      void saveImageFromImage();
      void draw();
      void stop();
      void zoom();
      void zoomOut();
      void closeDoc();
      void textChanged();
      void setZoomColor();
      void setZoomOutOptions();
      void setZoomInOptions();
      void setAntiAliasOption();
      void doGradientEditor();
      void doQuit();
      void clearStatus();
      void about();
      void documentation();
      void cursorPositionChanged(int row, int column);
      void resizeTimerFinished();
      void sizesChanged(int top, int bottom);
      void revert();
      void undo();
      void redo();
      void findReplace();
      void showMatch();
      void indentCurrentLine();
      void unindentCurrentLine();
      void mappingReset();
      void fontSizeChanged(int index);
      void saveCancelled();
      void mappingHalf();
      void mappingDouble();
      void mappingTenPercentSmaller();
      void mappingTenPercentLarger();
      void mappingViewXMirror();
      void mappingViewYMirror();
      void mappingViewHalf();
      void mappingViewDouble();
      void mappingViewTenPercentSmaller();
      void mappingViewTenPercentLarger();
      void slotPanRightTenPercent();
      void slotPanRightFiftyPercent();
      void slotPanRightOneHundredPercent();
      void slotPanLeftTenPercent();
      void slotPanLeftFiftyPercent();
      void slotPanLeftOneHundredPercent();
      void slotPanUpTenPercent();
      void slotPanUpFiftyPercent();
      void slotPanUpOneHundredPercent();
      void slotPanDownTenPercent();
      void slotPanDownFiftyPercent();
      void slotPanDownOneHundredPercent();


   private:
      void addToolBar();
      void addFileMenu(QMenuBar *menuBar);
      void addEditMenu(QMenuBar *menuBar);
      void addMappingMenu(QMenuBar *menuBar);
      void addOptionsMenu(QMenuBar *menuBar);
      void addHelpMenu(QMenuBar *menuBar);
      void addMenuBar();
      void addStatusBar();

      void massageCurrentLine(int doIndent);

      QString getSaveImageName();
      char *getBaseName() const;
      char *getZoomName() const;
      void setCurrentFileName(const char *name);
      char *grabText() const;
      void setOriginalText(const char *text);

      int getAntiAliasSetting() const;

      void saveImage(
         QString &name,
         int width,
         int height,
         RowSupplier *supplier
      );

      void loadFile(const char *name);
      void message(char *text, int timeoutInMillis) const;
      int checkForSave();
      void zoomToCoordinates(
         double x0, double y0, double x1, double y1, ZoomInSettings *z
      );
      Fractal *getFractal();
      void applyBuffer(const char *theBuffer);
      void applyZoomBuffer(char *zoomBuffer);
      void mappingScale(double factor);
      void mappingMirror(int yFlag);
      void mappingPan(double factor, int direction);
      void mappingScaleView(double factor);

      QProgressDialog   *mProgressDialog;
      QToolButton       *mDrawButton;
      QToolButton       *mZoomButton;
      QToolButton       *mZoomOutButton;
      QToolButton       *mStopButton;
      QIconSet          *mDrawIconSet;
      QIconSet          *mZoomIconSet;
      QIconSet          *mZoomOutIconSet;
      QIconSet          *mStopIconSet;
      char              *mFileName;
      char              *mOriginalText;
      int                mTextNeedsSaving;
      QLabel            *mMessage;
      QLabel            *mPosition;
      QProgressBar      *mProgress;
      FractalSplitter   *mSplitter;
      State             *mState;
      QTimer            *mResizeTimer;
      QPopupMenu        *mFontSizes;
      int               mCurrentlyDrawing;
      int               mSaveCancelled;
      QPopupMenu        *mSaveImageMenu;
      int               mUseCurrentImageIndex;
      FindReplaceDialog *mFindReplace;
      QString           mHome;
};

#endif
