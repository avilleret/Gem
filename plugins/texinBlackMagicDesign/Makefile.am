
ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4
AM_CPPFLAGS = -I$(top_srcdir)/src @GEM_EXTERNAL_CPPFLAGS@

pkglib_LTLIBRARIES=
gemhelpdir=$(pkglibdir)
dist_gemhelp_DATA =

# if HAVE_LIB_LIBBLACKMAGIC
pkglib_LTLIBRARIES+=gem_texinBlackMagicDesign.la
dist_gemhelp_DATA +=BlackMagicDesign-texinplugin.pd
# endif

gem_texinBlackMagicDesign_la_CXXFLAGS =
gem_texinBlackMagicDesign_la_LDFLAGS  = -module -avoid-version -shared
if WINDOWS
gem_texinBlackMagicDesign_la_LDFLAGS += -no-undefined
endif
gem_texinBlackMagicDesign_la_LIBADD   =

# RTE
gem_texinBlackMagicDesign_la_CXXFLAGS += @GEM_RTE_CFLAGS@ @GEM_ARCH_CXXFLAGS@
gem_texinBlackMagicDesign_la_LDFLAGS  += @GEM_RTE_LIBS@   @GEM_ARCH_LDFLAGS@
# flags for building Gem externals
gem_texinBlackMagicDesign_la_CXXFLAGS += @GEM_EXTERNAL_CFLAGS@
gem_texinBlackMagicDesign_la_LIBADD   += -L$(top_builddir) @GEM_EXTERNAL_LIBS@
# gem_texinBlackMagicDesign_la @MOREFLAGS@

# Dependencies

gem_texinBlackMagicDesign_la_CXXFLAGS += @GEM_LIB_DECKLINKAPI_CFLAGS@ @PKG_DECKLINKAPI_CFLAGS@
gem_texinBlackMagicDesign_la_LIBADD   += @GEM_LIB_DECKLINKAPI_LIBS@

# convenience symlinks
include $(srcdir)/../symlink_ltlib.mk


### SOURCES
gem_texinBlackMagicDesign_la_SOURCES= texinBlackMagicDesign.cpp texinBlackMagicDesign.h
