###############################################################################
# Makefile - designed to work on windows nt and all unix variants
#
# This Makefile assumes:
#
#    (a) You are using gnu make, even if you are on windows nt
#    (b) g++ version >= 2.8.1 on unix
#    (c) MS VC++ version >= 5.0 on windows
###############################################################################

include ../../directories.inc

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

LIBRARY := libtiff_${MODE}.a

###############################################################################
# Windows settings ...
###############################################################################

ifeq "${PLATFORM}" "winnt"

   ifeq "${MODE}" "release"
      OPTIMIZE := -O2
   else
      OPTIMIZE := -Zi
   endif

   PLATFORM_INCLUDE  := -I${WINDOWS_VC_INCLUDE}
   CPP               := cl
   CC                := cl
   WARN              := -W3
   OUT1              :=
   OUT2              := -Fo
   MKLIB             := lib /out:${LIBRARY}
   PLATFORM_CPPFLAGS := -GX
   RM                := del

else

###############################################################################
# Unix settings ...
###############################################################################

   ifeq "${MODE}" "release"
      OPTIMIZE := -O2
   else
      OPTIMIZE := -g
   endif

   CPP   := g++
   CC    := gcc
   WARN  := -W -Wall
   OUT1  := -o
   OUT2  := ${shell echo " "}
   MKLIB := ar ruv ${LIBRARY}
   RM    := rm

endif

###############################################################################
# Platform Independent Settings
###############################################################################

INCLUDE   := ${PLATFORM_INCLUDE} -I../fractal
OUT       := ${OUT1}${OUT2}
CFLAGS    := -c ${WARN} ${INCLUDE} ${OPTIMIZE}
CPPFLAGS  := ${CFLAGS} ${PLATFORM_CPPFLAGS}

OBJECTS   := TiffWriter_${MODE}.o   \
             tif_aux_${MODE}.o      \
             tif_close_${MODE}.o    \
             tif_codec_${MODE}.o    \
             tif_compress_${MODE}.o \
             tif_dir_${MODE}.o      \
             tif_dirinfo_${MODE}.o  \
             tif_dirread_${MODE}.o  \
             tif_dirwrite_${MODE}.o \
             tif_dumpmode_${MODE}.o \
             tif_error_${MODE}.o    \
             tif_fax3_${MODE}.o     \
             tif_fax3sm_${MODE}.o   \
             tif_flush_${MODE}.o    \
             tif_getimage_${MODE}.o \
             tif_jpeg_${MODE}.o     \
             tif_luv_${MODE}.o      \
             tif_lzw_${MODE}.o      \
             tif_next_${MODE}.o     \
             tif_open_${MODE}.o     \
             tif_packbits_${MODE}.o \
             tif_pixarlog_${MODE}.o \
             tif_predict_${MODE}.o  \
             tif_print_${MODE}.o    \
             tif_read_${MODE}.o     \
             tif_strip_${MODE}.o    \
             tif_swab_${MODE}.o     \
             tif_thunder_${MODE}.o  \
             tif_tile_${MODE}.o     \
             tif_unix_${MODE}.o     \
             tif_version_${MODE}.o  \
             tif_warning_${MODE}.o  \
             tif_win32_${MODE}.o    \
             tif_write_${MODE}.o    \
             tif_zip_${MODE}.o

###############################################################################
# Rules
###############################################################################

${LIBRARY}: ${OBJECTS}
	${MKLIB} ${OBJECTS}

release:
	${MAKE} RELEASE=1

debug:
	${MAKE}

%_${MODE}.o: %.c
	${CC} ${CFLAGS} ${OUT}$@ $<

%_${MODE}.o: %.cpp
	${CPP} ${CPPFLAGS} ${OUT}$@ $<

clean:
	-${RM} *.a *.o *.pdb

###############################################################################
# Unix Only Rules
###############################################################################

depend:
	@g++ -MM ${INCLUDE} *.c *.cpp | sed 's/\.o/_$${MODE}.o/'

###############################################################################
# Dependencies - created by running: "make depend >> Makefile"
###############################################################################
tif_aux_${MODE}.o: tif_aux.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_close_${MODE}.o: tif_close.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_codec_${MODE}.o: tif_codec.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_compress_${MODE}.o: tif_compress.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_dir_${MODE}.o: tif_dir.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_dirinfo_${MODE}.o: tif_dirinfo.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_dirread_${MODE}.o: tif_dirread.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_dirwrite_${MODE}.o: tif_dirwrite.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_dumpmode_${MODE}.o: tif_dumpmode.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_error_${MODE}.o: tif_error.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_fax3_${MODE}.o: tif_fax3.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h tif_fax3.h t4.h
tif_fax3sm_${MODE}.o: tif_fax3sm.c tiff.h tif_fax3.h
tif_flush_${MODE}.o: tif_flush.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_getimage_${MODE}.o: tif_getimage.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_jpeg_${MODE}.o: tif_jpeg.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_luv_${MODE}.o: tif_luv.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h uvcode.h
tif_lzw_${MODE}.o: tif_lzw.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h tif_predict.h
tif_next_${MODE}.o: tif_next.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_open_${MODE}.o: tif_open.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_packbits_${MODE}.o: tif_packbits.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_pixarlog_${MODE}.o: tif_pixarlog.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_predict_${MODE}.o: tif_predict.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h tif_predict.h
tif_print_${MODE}.o: tif_print.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_read_${MODE}.o: tif_read.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_strip_${MODE}.o: tif_strip.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_swab_${MODE}.o: tif_swab.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_thunder_${MODE}.o: tif_thunder.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_tile_${MODE}.o: tif_tile.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_unix_${MODE}.o: tif_unix.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_version_${MODE}.o: tif_version.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h version.h
tif_warning_${MODE}.o: tif_warning.c tiffiop.h port.h ../fractal/unistd.h \
  tiffconf.h tiffio.h tiff.h tif_dir.h
tif_win32_${MODE}.o: tif_win32.c
tif_write_${MODE}.o: tif_write.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
tif_zip_${MODE}.o: tif_zip.c tiffiop.h port.h ../fractal/unistd.h tiffconf.h \
  tiffio.h tiff.h tif_dir.h
TiffWriter_${MODE}.o: TiffWriter.cpp ../fractal/dmemory.h tiffio.h tiff.h \
  TiffWriter.h
