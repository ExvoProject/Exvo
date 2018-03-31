#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/exvo.png
ICON_DST=../../src/qt/res/icons/exvo.ico
convert ${ICON_SRC} -resize 16x16 exvo-16.png
convert ${ICON_SRC} -resize 32x32 exvo-32.png
convert ${ICON_SRC} -resize 48x48 exvo-48.png
convert exvo-16.png exvo-32.png exvo-48.png ${ICON_DST}

