
ACLOCAL_AMFLAGS = -I ../../m4 -I .
AM_CPPFLAGS = -I$(srcdir)/../../src

EXTRA_DIST = LICENSE.txt README.txt

plugindir=$(libdir)/Gem

plugin_LTLIBRARIES=
dist_plugin_DATA  =

if HAVE_LIB_DECKLINK
plugin_LTLIBRARIES+= gem_texinDECKLINK.la
dist_plugin_DATA  += decklink-texinplugin.pd
endif

gem_texinDECKLINK_la_CXXFLAGS =
gem_texinDECKLINK_la_LDFLAGS  = -module -avoid-version -shared
if WINDOWS
gem_texinDECKLINK_la_LDFLAGS += -no-undefined
endif
gem_texinDECKLINK_la_LIBADD   =

# RTE
gem_texinDECKLINK_la_CXXFLAGS += @GEM_RTE_CFLAGS@
gem_texinDECKLINK_la_LDFLAGS  += @GEM_RTE_LIBS@
#gem_texinDECKLINK_la_CXXFLAGS += @GEM_ARCH_CXXFLAGS@
#gem_texinDECKLINK_la_LDFLAGS  += @GEM_ARCH_LDFLAGS@
# #gem_texinDECKLINK_la @MOREFLAGS@

# Dependencies
gem_texinDECKLINK_la_CXXFLAGS += @GEM_LIB_DECKLINK_CFLAGS@
gem_texinDECKLINK_la_LIBADD   += @GEM_LIB_DECKLINK_LIBS@

# convenience symlinks
include $(srcdir)/../symlink_ltlib.mk


### SOURCES
gem_texinDECKLINK_la_SOURCES= texinDECKLINK.cpp texinDECKLINK.h
