#! /bin/bash

path=$1

if (($# != 1)) ; then
echo "usage: $0 /path/to/asmjit"
echo
exit 0
fi

rm -f *.cpp *.h

for file in $path/src/asmjit/*.h
do
move=${file##*/}
sed 's|/base/string.h|/moved_string.h|' $file |
sed "s|/base/|/|" |
sed "s|/x86/|/|" |
sed "s/::asmjit/::PLMD::asmjit/" |
sed "s/defined(ASMJIT_EMBED)/1/" |
cat > $move
done

for file in $path/src/asmjit/{base,x86}/*.{h,cpp}
do
move=${file##*/}
if [ $move == "string.h" ] ; then
  move=moved_string.h # should be moved to avoid problems with include <string.h>
fi
test -f "$move" && echo "ERROR $file" && exit 1
sed 's|/base/string.h|/moved_string.h|' $file |
sed 's|\.\./[a-z0-9A-Z_]*/|./|' |
sed 's|\.\./|./|' |
sed "s/::asmjit/::PLMD::asmjit/" |
awk '
BEGIN{
print "#ifdef __PLUMED_HAS_ASMJIT"
}
{
if($1=="namespace" && $2=="asmjit") print "namespace PLMD {"
print
if($1=="}" && $2=="//" && $3=="asmjit") print "} // namespace PLMD"
}END{
print "#endif // __PLUMED_HAS_ASMJIT"
}' > $move
done

cd ../
./header.sh asmjit





