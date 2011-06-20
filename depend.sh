#!/bin/sh
DIR="$1"
shift 1
case "$DIR" in
	"" | ".")
		g++ -MM -MG "$@" | sed -e 's@^\(.*\)\.o:@\1.dep \1.o:@'
	;;
	*)
		g++ -MM -MG "$@" | sed -e "s@^\(.*\)\.o:@$DIR/\1.dep $DIR/\1.o:@"
	;;
esac
