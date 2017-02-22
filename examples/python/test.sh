rm -f error.txt

for i in *.py; do
  name=`echo $i | sed 's/\.java//'`;
  echo ==================Running  $name ==================
  if python $name; then 
    echo $name run OK >> error.txt
  else
    echo $name run Error >> error.txt
  fi
done
