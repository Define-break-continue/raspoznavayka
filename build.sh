#!/bin/bash
#
# To run program after build, use build.sh -r
#

if [ $(date  +"%Y%m%d") -le 20160520 ]; then
    echo ""
    echo "Note the new build.sh syntax!    <<<   <<<   <<<   <<<   <<<   <<<   <<<   <<<";
    echo "$0 [-d] [-r] -- (args...)";
    echo "Use -r to run raspoznavayka after build";
    echo "    -d to delete build/ directory before build (it's safe)";
    echo "    -- (args...) to pass args to raspoznavayka when running";
    echo ""
fi

while [ $# -gt 0 ]; do
    case "$1" in
        -m) tgt=manual;;
        -r) run=1;;
        -d) del=1;;
        --) break;;
    esac
    shift
done

cd $( git rev-parse --show-toplevel )

tgt="$(gcc -v 2>&1 |grep -e '^Target' |cut -d' ' -f2-)";
case $tgt in
    i?86*linux*)
        cp src/lib/aquila/libAquila.a.86 src/lib/aquila/libAquila.a
        cp src/lib/aquila/libOoura_fft.a.86 src/lib/aquila/libOoura_fft.a
        ;;
    x86_64*linux*|amd64*linux*)
        cp src/lib/aquila/libAquila.a.64 src/lib/aquila/libAquila.a
        cp src/lib/aquila/libOoura_fft.a.64 src/lib/aquila/libOoura_fft.a
        ;;
    x86_64-apple-darwin*)
        cp src/lib/aquila/libAquila.a.x86_64-apple-darwin15.4.0 src/lib/aquila/libAquila.a
        cp src/lib/aquila/libOoura_fft.a.x86_64-apple-darwin15.4.0 src/lib/aquila/libOoura_fft.a
        ;;
    "manual") ;;
    *)
        echo "Your target architecture is not defined. Copy libAquila.a manually"
        echo "and issue $0 -m"
        exit 1
        ;;
esac
if [ ! -z ${del} ]; then
    rm -rf build/
    mkdir build
fi
cd build/
cmake -DCMAKE_BUILD_TYPE=Debug ../src/ && \
make && \
if [ ! -z ${run} ]; then 
    echo 'Running raspoznavayka...'
    cd ..
    build/raspoznavayka $@
fi
