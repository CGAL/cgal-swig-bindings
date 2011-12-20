LD_LIBRARY_PATH=$PWD/lib
export LD_LIBRARY_PATH

rm -f error.txt

for i in `egrep -l "public\s+static\s+void\s+main" *.java`; do
  name=`echo $i | sed 's/\.java//'`;
  echo ==================Running  $name ==================
  if javac $i; then 
    echo $i compiled >> error.txt
    if java $name; then 
      echo $name run OK >> error.txt
    else
      echo $name run Error >> error.txt
    fi
  else
    echo $i compilation error >> error.txt
  fi
done
