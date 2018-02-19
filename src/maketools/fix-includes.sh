for file in */*.cpp */*.h */*.c
do
list=$(grep "^USE=" ${file%/*}/Makefile | sed "s/^USE=//")
awk -v list="$list" '{
split(list,ar)
for(a in ar){
  if(match($0,"^# *include +\\\"" ar[a] "/")) {
    sub(ar[a] "/","../"ar[a] "/")
  }
}
print
}' $file  > $file.tmp
mv $file.tmp $file
git add $file

done
