LIBDIR=/usr/lib
INCDIR=/usr/include
VAPIDIR=/usr/share/vala/vapi
TYPELIBDIR=/usr/lib/girepository-1.0
PCDIR=/usr/lib/pkgconfig

CC=valac
VERSION=1.0
LIBRARY=picolan

CFLAGS= --library=$(LIBRARY)-$(VERSION) -H $(LIBRARY).h --pkg gserial-1.0 --pkg gio-2.0 --pkg gee-0.8  --gir=$(LIBRARY)-$(VERSION).gir
SOURCES=$(wildcard src/*.vala)

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -X -fPIC -X -shared -o lib$(LIBRARY)-$(VERSION).so

clean:
	rm -f *.gir *.typelib *.so *.vapi *.tmp *.h
	rm src/*.c
	rm -rfd docs

install:
	cp lib$(LIBRARY)-$(VERSION).so $(LIBDIR)
	cp $(LIBRARY).h $(INCDIR)
	cp $(LIBRARY)-$(VERSION).vapi $(VAPIDIR)
	cp $(LIBRARY)-$(VERSION).typelib $(TYPELIBDIR)
	cp $(LIBRARY)-$(VERSION).pc $(PCDIR)

c:
	$(CC) -C $(CFLAGS) $(SOURCES)

typelib:
	g-ir-compiler --shared-library=lib$(LIBRARY)-$(VERSION).so --output=$(LIBRARY)-$(VERSION).typelib $(LIBRARY)-$(VERSION).gir

docs:
	valadoc -o docs --pkg gtk+-3.0 --pkg libsoup-2.4 --pkg glib-2.0 --package-name $(LIBRARY) $(SOURCES)
