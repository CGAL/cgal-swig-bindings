rm -f error.txt

for i in *.py; do
  name=`echo $i | sed 's/\.py//'`;
  echo ==================Running  $name ==================
  if python $i; then 
    echo $i run OK >> error.txt
  else
    echo $i run Error >> error.txt
  fi
done
