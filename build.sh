#!/bin/bash
#
# To run program after build, use build.sh -r
#

while [ $# -gt 0 ]; do
    case "$1" in
        -m) tgt=manual;;
        -r) run=1;;
    esac
    shift
done

tgt="$(gcc -v 2>&1 |grep -e '^Target' |cut -d' ' -f2-)";
case $tgt in
    i?86*linux*)
        cp src/lib/aquila/libAquila.a.86 src/lib/aquila/libAquila.a
        cp src/lib/aquila/libOoura_fft.a.86 src/lib/aquila/libOoura_fft.a
        ;;
    x86_64*|amd64*)
        cp src/lib/aquila/libAquila.a.64 src/lib/aquila/libAquila.a
        cp src/lib/aquila/libOoura_fft.a.64 src/lib/aquila/libOoura_fft.a
        ;;
    "manual") ;;
    *)
        echo "Your target architecture is not defined. Copy libAquila.a manually"
        echo "and issue $0 -m"
        exit 1
        ;;
esac
rm -rf build/
mkdir build
cd build/
cmake ../src/
make

[ ! -z ${run} ] && ./raspoznavayka
