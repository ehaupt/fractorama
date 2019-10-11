###############################################################################
# Makefile - designed to work on windows nt and all unix variants
#
# This Makefile assumes:
#
#    (a) Qt version >= 2.0
#    (b) g++ version >= 2.8.1 on unix
#    (c) MS VC++ version >= 5.0 on windows
#    (d) You are using gnu make, even if you are on windows nt
#    (e) You have available on windows nt the static qt library
#    (f) You have available on unix the dynamic qt library
#
# The only values in this Makefile that might need to be edited are
# the values acquired via: "include directories.inc" below
# environment
###############################################################################

include directories.inc

###############################################################################
# Debug or Release?
###############################################################################

ifeq "${RELEASE}" "1"
   MODE := release
else
   MODE := debug
endif

###############################################################################
# Determine which platform we're on ...
#
# We don't really need to know which unix platform we're on, but save off
# the result in ${PLATFORM} in case we need it for future funkiness
###############################################################################

ifeq "${OS}" "Windows_NT"
   PLATFORM := winnt
else
   PLATFORM := ${shell uname}
endif

###############################################################################
# Our .exe name ...
###############################################################################

ifeq "${MODE}" "release"
   EXE := ../fractorama.exe
else
   EXE := ../debug.exe
endif

###############################################################################
# Windows Settings
###############################################################################

ifeq "${PLATFORM}" "winnt"

   LINK_WIN32_ARGS := /out:${EXE} 
   
   ifeq "${MODE}" "release"
      OPTIMIZE := -O2
      LINK     := link ${LINK_WIN32_ARGS} /subsystem:windows
   else
      OPTIMIZE := -Zi
      LINK     := link /DEBUG ${LINK_WIN32_ARGS} /subsystem:console
   endif

   QTROOT            := ${WINDOWS_QTROOT}
   CPP               := cl
   PLATFORM_CPPFLAGS := -GX 
   WARN              := -W3
   PLATFORM_INCLUDE  := -I${WINDOWS_VC_INCLUDE}
   PLATFORM_LIBS     := ${QTROOT}/lib/qt.lib  \
                        ${QTROOT}/lib/qtmain.lib \
                        opengl32.lib glu32.lib delayimp.lib kernel32.lib \
                        user32.lib gdi32.lib comdlg32.lib advapi32.lib \
                        shell32.lib ole32.lib oleaut32.lib uuid.lib \
                        imm32.lib winmm.lib wsock32.lib winspool.lib \
                        comdlg32.lib gdi32.lib user32.lib
   OUT1              :=
   OUT2              := -Fo
   RM                := del
else

###############################################################################
# Unix Settings
###############################################################################

   ifeq "${MODE}" "release"
      OPTIMIZE := -O2
   else
      OPTIMIZE := -g
   endif

   QTROOT        := ${UNIX_QTROOT}
   PLATFORM_LIBS := -L${QTROOT}/lib -lqt
   CPP           := g++
   WARN          := -W -Wall
   LINK          := ${CPP} -o ${EXE}
   OUT1          := -o
   OUT2          := ${shell echo " "}
   RM            := rm

   ifeq "${MODE}" "debug"
      PLATFORM_LIBS := ${PLATFORM_LIBS}
   endif
endif

###############################################################################
# Platform Independent Settings
###############################################################################

LIBFRACTAL := lib/fractal/libfractal_${MODE}.a
LIBTIFF    := lib/tiff/libtiff_${MODE}.a
LIBPERSIST := lib/persist/libpersist_${MODE}.a

FRACT_LIBS := ${LIBFRACTAL} ${LIBTIFF} ${LIBPERSIST}

LIBS := ${FRACT_LIBS} ${PLATFORM_LIBS}

BUILD_LIBS := build_libfractal build_libtiff build_libpersist

OUT     := ${OUT1}${OUT2}
MOC     := ${QTROOT}/bin/moc

BASE_INCLUDE := -Ilib/fractal  \
                -Ilib/tiff     \
                -Ilib/persist  \
                -Iicons        \
                ${PLATFORM_INCLUDE}

INCLUDE := -I${QTROOT}/include \
           ${BASE_INCLUDE}


CPPFLAGS   := -c ${WARN} ${OPTIMIZE} ${INCLUDE} ${PLATFORM_CPPFLAGS}

OBJECTS     := main_${MODE}.o                  \
               antialiasdialog_${MODE}.o       \
               application_${MODE}.o           \
               help_${MODE}.o                  \
               fractalview_${MODE}.o           \
               state_${MODE}.o                 \
               zoomoutdialog_${MODE}.o         \
               zoomindialog_${MODE}.o          \
               fractalsplitter_${MODE}.o       \
               map_${MODE}.o                   \
               qinfiniteloopcallback_${MODE}.o \
               findreplacedialog_${MODE}.o     \
               gradienteditor_${MODE}.o

OBJECTS_MOC := moc_application_${MODE}.o       \
               moc_help_${MODE}.o              \
               moc_zoomoutdialog_${MODE}.o     \
               moc_zoomindialog_${MODE}.o      \
               moc_fractalsplitter_${MODE}.o   \
               moc_findreplacedialog_${MODE}.o \
               moc_gradienteditor_${MODE}.o

###############################################################################
# Rules
###############################################################################

top: ${BUILD_LIBS} ${EXE}

${EXE}: ${FRACT_LIBS} ${OBJECTS} ${OBJECTS_MOC}
	${LINK} ${OBJECTS} ${OBJECTS_MOC} ${LIBS}

build_libfractal:
	${MAKE} -C lib/fractal "RELEASE=${RELEASE}"

build_libtiff:
	${MAKE} -C lib/tiff "RELEASE=${RELEASE}"

build_libpersist:
	${MAKE} -C lib/persist "RELEASE=${RELEASE}"

%_${MODE}.o:%.cpp
	${CPP} ${CPPFLAGS} ${OUT}$@ $<

release:
	${MAKE} "RELEASE=1"

debug:
	${MAKE}

clean:
	-${RM} -f *.o *.exe moc_*.cpp *.pdb

realclean:
	${MAKE} clean
	${MAKE} -C lib/fractal clean
	${MAKE} -C lib/tiff clean
	${MAKE} -C lib/persist clean

###############################################################################
# MOC Build Rules
###############################################################################

moc_application.cpp: application.h
	${MOC} application.h -o moc_application.cpp

moc_help.cpp: help.h
	${MOC} help.h -o moc_help.cpp

moc_zoomoutdialog.cpp: zoomoutdialog.h
	${MOC} zoomoutdialog.h -o moc_zoomoutdialog.cpp

moc_zoomindialog.cpp: zoomindialog.h
	${MOC} zoomindialog.h -o moc_zoomindialog.cpp

moc_fractalsplitter.cpp: fractalsplitter.h
	${MOC} fractalsplitter.h -o moc_fractalsplitter.cpp

moc_findreplacedialog.cpp: findreplacedialog.h
	${MOC} findreplacedialog.h -o moc_findreplacedialog.cpp

moc_gradienteditor.cpp: gradienteditor.h
	${MOC} gradienteditor.h -o moc_gradienteditor.cpp

###############################################################################
# Unix Specific Targets
###############################################################################

depend:
	@g++ -MM ${BASE_INCLUDE} *.cpp 2>/dev/null | \
         sed 's/\.o/_$${MODE}.o/'

###############################################################################
# Dependencies - created by running: "make depend >> Makefile"
###############################################################################
antialiasdialog_${MODE}.o: antialiasdialog.cpp antialiasdialog.h
application_${MODE}.o: application.cpp application.h fractalobserver.h \
  statesupplier.h fractalview.h lib/fractal/Fractal.h \
  lib/fractal/ColorEnvironment.h lib/fractal/ComplexVariables.h \
  lib/fractal/dcomplex.h lib/fractal/DoubleVariables.h \
  lib/fractal/ColorTable.h lib/fractal/rowsupplier.h \
  lib/tiff/TiffWriter.h lib/fractal/fractal_parse.h state.h \
  zoomoutdialog.h zoomindialog.h zoominsettings.h antialiasdialog.h \
  fractalsplitter.h map.h qinfiniteloopcallback.h \
  lib/fractal/InfiniteLoopCallback.h findreplacedialog.h \
  lib/fractal/dmemory.h help.h gradienteditor.h version.h icons/open.xpm \
  icons/draw.xpm icons/draw_disabled.xpm icons/zoom.xpm \
  icons/zoom_disabled.xpm icons/zoomout.xpm icons/zoomout_disabled.xpm \
  icons/stop.xpm icons/stop_disabled.xpm
findreplacedialog_${MODE}.o: findreplacedialog.cpp findreplacedialog.h
fractalsplitter_${MODE}.o: fractalsplitter.cpp fractalsplitter.h fractalview.h
fractalview_${MODE}.o: fractalview.cpp fractalview.h lib/fractal/Fractal.h \
  lib/fractal/ColorEnvironment.h lib/fractal/ComplexVariables.h \
  lib/fractal/dcomplex.h lib/fractal/DoubleVariables.h \
  lib/fractal/ColorTable.h lib/fractal/rowsupplier.h fractalobserver.h \
  statesupplier.h state.h zoomoutdialog.h zoomindialog.h zoominsettings.h \
  qinfiniteloopcallback.h lib/fractal/InfiniteLoopCallback.h \
  lib/fractal/dmemory.h
gradienteditor_${MODE}.o: gradienteditor.cpp gradienteditor.h \
  lib/fractal/dmemory.h
help_${MODE}.o: help.cpp help.h icons/back.xpm icons/forward.xpm icons/home.xpm
main_${MODE}.o: main.cpp application.h fractalobserver.h statesupplier.h \
  lib/persist/persist.h lib/persist/environment.h \
  lib/persist/kvenvironment.h lib/persist/nocaseenvironment.h \
  lib/persist/filterenvironment.h lib/persist/fileenvironment.h \
  lib/persist/messagehandler.h state.h zoomoutdialog.h zoomindialog.h \
  zoominsettings.h lib/fractal/dmemory.h
map_${MODE}.o: map.cpp map.h lib/fractal/fractal_parse.h zoominsettings.h \
  zoomindialog.h
qinfiniteloopcallback_${MODE}.o: qinfiniteloopcallback.cpp \
  qinfiniteloopcallback.h lib/fractal/InfiniteLoopCallback.h
state_${MODE}.o: state.cpp state.h zoomoutdialog.h zoomindialog.h \
  zoominsettings.h main.h lib/persist/persist.h lib/persist/environment.h \
  application.h fractalobserver.h statesupplier.h lib/fractal/dmemory.h
zoomindialog_${MODE}.o: zoomindialog.cpp zoomindialog.h
zoomoutdialog_${MODE}.o: zoomoutdialog.cpp zoomoutdialog.h
