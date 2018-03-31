
Debian
====================
This directory contains files used to package exvod/exvo-qt
for Debian-based Linux systems. If you compile exvod/exvo-qt yourself, there are some useful files here.

## exvo: URI support ##


exvo-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install exvo-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your exvo-qt binary to `/usr/bin`
and the `../../share/pixmaps/exvo128.png` to `/usr/share/pixmaps`

exvo-qt.protocol (KDE)

