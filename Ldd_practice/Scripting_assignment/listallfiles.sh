#!/bin/sh

for name in *
do
if [ -r $name ] && [ -w $name ] && [ -x $name ]
then
echo $name
fi
done
exit 0