#!/bin/sh
set -e

if [ -z "$CC" ]; then
    CC=gcc
fi

rm NAR
rm src/RuleTable.c
Str=`ls src/*.c src/NetworkNAR/*.c | xargs`
echo $Str
echo "Compilation started:"
BaseFlags="-g -pthread -lpthread -D_POSIX_C_SOURCE=199506L -pedantic -std=c99 -g3 -O3 $Str -lm -oNAR"
NoWarn="-Wno-tautological-compare -Wno-dollar-in-identifier-extension -Wno-unused-parameter -Wno-unused-variable"
$CC -DSTAGE=1 -Wall -Wextra -Wformat-security $NoWarn $BaseFlags
echo "First stage done, generating RuleTable.c now, and finishing compilation."
./NAR NAL_GenerateRuleTable > ./src/RuleTable.c

if [[ "$*" == *"-fopenmp"* ]]; then
    echo "Building with OpenMP support."
fi

$CC -DSTAGE=2 $NoWarn $BaseFlags $@ src/RuleTable.c
echo "Done."
