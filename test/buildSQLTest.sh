#!/usr/bin/env bash
FILES=`find $1/../src/SQL -name \*.h -not -name SQLParserFailedException.h`
OUT="`pwd`/SQLTests.cpp"
IN="$1/SQLTests.cpp.in"

if [ -z "$FILES" ]
then
  echo No files
  exit 1
fi

TYPES=`sed -e '/abstract/d;/template/d;/class SQL[a-zA-Z]*.*:/!d;s/class //;s/[:;{].*//;s/  *//;' $FILES </dev/null |
 sort | uniq`
echo '#line' 1 "\"$IN\"" > $OUT
cat "$IN" >> $OUT
LINES=`wc -l < $OUT`
echo '#line' `expr $LINES + 2` "\"$OUT\"" >> $OUT

for i in $FILES
do
  echo "#include <`basename $i`>" >> $OUT
done

for i in $TYPES
do
  echo "SQLTEST($i)" >> $OUT
done

