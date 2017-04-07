#!/usr/bin/env bash
FILES=`find $1/../src/SQL -name \*.h -not -name SQLParserFailedException.h`

if [ -z "$FILES" ]
then
  echo No files
  exit 1
fi

TYPES=`sed -e '/abstract/d;/template/d;/class SQL[a-zA-Z]*.*:/!d;s/class //;s/[:;{].*//;s/  *//;' $FILES </dev/null |
 sort | uniq`

cat $1/SQLTests.cpp.in > SQLTests.cpp

for i in $FILES
do
  echo "#include <`basename $i`>" >> SQLTests.cpp
done

for i in $TYPES
do
  echo "SQLTEST($i)" >> SQLTests.cpp
done

