#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

EXVOD=${EXVOD:-$SRCDIR/exvod}
EXVOCLI=${EXVOCLI:-$SRCDIR/exvo-cli}
EXVOTX=${EXVOTX:-$SRCDIR/exvo-tx}
EXVOQT=${EXVOQT:-$SRCDIR/qt/exvo-qt}

[ ! -x $EXVOD ] && echo "$EXVOD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
STAKVER=($($EXVOCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for exvod if --version-string is not set,
# but has different outcomes for exvo-qt and exvo-cli.
echo "[COPYRIGHT]" > footer.h2m
$EXVOD --version | sed -n '1!p' >> footer.h2m

for cmd in $EXVOD $EXVOCLI $EXVOTX $EXVOQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${STAKVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${STAKVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
