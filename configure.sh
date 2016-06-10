EXEC_NAME="busca_paralela"

echo "Compiling..."
make

echo "Giving permission..."
chmod +x $EXEC_NAME

count=0

while read ip; do
  if test $count != 0
   then
    echo "Synchronizing files from $ip..."
    rsync -aq $EXEC_NAME $ip:`pwd`
  fi
  count=$count+1
done < hosts

echo "Raising network..."
lamboot hosts

echo "Configuration finalized."
