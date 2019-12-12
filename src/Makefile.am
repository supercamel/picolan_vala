## Process this file with automake to produce Makefile.in
lib_LTLIBRARIES = libgpicolan.1.0.la

VALAC=valac
VALAFLAGS= --pkg gserial-1.0 --pkg gio-2.0 --library gpicolan-1.0 -H gpicolan.h -X -fPIC -X -shared --gir gpicolan-1.0.gir

GPICOLAN_CFLAGS =          \
	$(GLIB_CFLAGS)          \
	$(GOBJECT_CFLAGS) \
	$(GSERIAL_CFLAGS)

GPICOLAN_LIBS =            \
    $(GLIB_LIBS)            \
    $(GOBJECT_LIBS) \
	$(GSERIAL_LIBS)

## Shared library
libgpicolan_1_0_la_CFLAGS =    \
    $(WARN_CFLAGS)          \
    $(DISABLE_DEPRECATED)   \
    $(GPICOLAN_CFLAGS)     \
	-DG_LOG_DOMAIN=\"gpicolan\"

if OS_WIN32
no_undefined = -no-undefined
endif

libgpicolan_1_0_la_LDFLAGS = \
	-version-info $(LT_VERSION_INFO)    \
	$(no_undefined)

libgpicolan_1_0_la_LIBADD =    \
    $(GPICOLAN_LIBS)

sources_vala =                 \
	address_field.vala \
	client.vala \
	datagram.vala \
	interface.vala \
	socket.vala \
	socket_stream.vala
					
sources_c = $(sources_vala:.vala=.c)
							

libgpicolan_1_0_la_SOURCES =   \
	$(sources_vala)

libgpicolanincdir = $(includedir)/gpicolan-1.0

## Misc
CLEANFILES = $(sources_c) gpicolan.h

## GObject Introspection Support
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = $(INTROSPECTION_FLAGS) --add-include-path=$(srcdir) --add-include-path=$(builddir) --warn-all --warn-error
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir) --includedir=$(builddir)

if HAVE_INTROSPECTION
all-local:
	g-ir-compiler --shared-library=libgpicolan-1.0.so --output=gpicolan-1.0.typelib gpicolan-1.0.gir

CLEANFILES += $(gir_DATA) $(typelib_DATA)
endif

if ENABLE_VAPIGEN
-include $(VAPIGEN_MAKEFILE)

gpicolan-1.0.vapi: gpicolan-1.0.gir

VAPIGEN_VAPIS = gpicolan-1.0.vapi

gpicolan_1_0_vapi_METADATADIRS = $(srcdir)
gpicolan_1_0_vapi_FILES = gpicolan-1.0.gir

vapidir = $(datadir)/vala/vapi

endif
