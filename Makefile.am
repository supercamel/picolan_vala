## Process this file with automake to produce Makefile.in

SUBDIRS = src
DISTCHECK_CONFIGURE_FLAGS = --enable-introspection

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
doc_DATA =                                      \
	README                                      \
	COPYING                                     \
	AUTHORS                                     \
	NEWS

#


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gpicolan-1.0.pc


release: dist
	scp @PACKAGE@-@VERSION@.tar.gz samuel.cowen@camelsoftware.com:/var/www/camelsoftware.com/gpicolan/



