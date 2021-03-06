## Process this file with automake to produce Makefile.in.

desktopdir = $(datadir)/applications
desktop_in_files = @PACKAGE@.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

$(desktop_DATA): %.desktop: %.desktop.in
	$(AM_V_GEN) $(MSGFMT) --desktop --template $< -d $(top_srcdir)/po -o $@

gsettings_ENUM_NAMESPACE = org.gnome.gnome-commander
gsettings_ENUM_FILES = $(top_srcdir)/src/gnome-cmd-types.h \
                       $(top_srcdir)/src/gnome-cmd-data.h \
                       $(top_srcdir)/src/intviewer/search-dlg.h

gsettings_SCHEMAS = org.gnome.@PACKAGE@.gschema.xml
@GSETTINGS_RULES@

appdatadir = $(datadir)/appdata
appdata_in_files = @PACKAGE@.appdata.xml.in
appdata_DATA = $(appdata_in_files:.xml.in=.xml)

$(appdata_DATA): $(appdata_in_files)
	$(AM_V_GEN) $(MSGFMT) --xml --template $< -d $(top_srcdir)/po -o $@

mimetopdir = $(datadir)/@PACKAGE@/mime
mimexmldir = $(mimetopdir)/packages
mimexml_DATA = gnome-commander-mime.xml

ebuild_files = @PACKAGE@.ebuild
ebuild_DATA_NOINST = @PACKAGE@-@VERSION@.ebuild

@PACKAGE@-@VERSION@.ebuild: $(ebuild_files)
	ln -sf @PACKAGE@.ebuild @PACKAGE@-@VERSION@.ebuild

EXTRA_DIST =              \
	$(appdata_in_files)   \
	$(desktop_in_files)   \
	@PACKAGE@.spec        \
	$(ebuild_files)       \
	$(ebuild_DATA_NOINST) \
	$(mimexml_DATA)       \
	$(gsettings_SCHEMAS)

CLEANFILES = org.gnome.@PACKAGE@.gschema.valid

DISTCLEANFILES = $(appdata_DATA) $(desktop_DATA)

HAVE_UPDATE_MIME_DATABASE = @HAVE_UPDATE_MIME_DATABASE@

#
# Keep in mind: Although $DESTDIR is often empty, it is needed
# for 'make distcheck' so leave it here, please!
#
install-data-hook:
	test "x$(HAVE_UPDATE_MIME_DATABASE)" == "xyes" && \
		update-mime-database -V $(DESTDIR)/$(mimetopdir)

uninstall-hook:
	for target in $(DESTDIR)/$(mimetopdir)/* ; \
		do test "x$${target}" != "x$(DESTDIR)/$(mimexmldir)" && rm -rf $${target} ; done

-include $(top_srcdir)/git.mk
