# Copyright 1999-2004 Gentoo Technologies, Inc.
# Distributed under the terms of the GNU General Public License, v2 or later
# Maintainer: Nuno Araujo <araujo_n@russo79.com>
# $Header$

S="${WORKDIR}/${P}"

inherit gnome2

DESCRIPTION="A full featured, dual-pane file manager for Gnome2"
HOMEPAGE="http://www.nongnu.org/gcmd/"

SRC_URI="http://ftp.gnome.org/pub/GNOME/sources/gnome-commander/1.2/${P}.tar.bz2";

LICENSE="GPL-2"

IUSE="doc exif"
SLOT="0"
KEYWORDS="alpha amd64 ia64 ppc ppc64 sparc x86"

RDEPEND=">=x11-libs/gtk+-2.6.0
	>=gnome-base/gnome-vfs-2.0
	>=dev-libs/glib-2.0.0
	>=gnome-base/libgnomeui-2.0
	>=gnome-base/gconf-2.0
	|| (
		app-admin/gamin
		app-admin/fam
	)
	exif? media-libs/libexif"

DEPEND="${RDEPEND}
	dev-util/intltool
	dev-util/pkgconfig"

src_compile() {
	./configure \
		--host=${CHOST} \
		--prefix=/usr \
		--infodir=/usr/share/info \
		--mandir=/usr/share/man || die "./configure failed"
	emake || die
}

src_install () {
	emake DESTDIR=${D} install || die
	dodoc AUTHORS ChangeLog COPYING INSTALL NEWS README TODO
}
