LD_LIBRARY_PATH=$PWD/lib
export LD_LIBRARY_PATH

rm -f error.txt

for i in test_*.java; do
  name=`echo $i | sed 's/\.java//'`;
  if  /usr/lib/jvm/java-6-sun/bin/javac $i; then 
    echo $i compiled >> error.txt
    if /usr/lib/jvm/java-6-sun/bin/java $name; then 
      echo $name run OK >> error.txt
    else
      echo $name run Error >> error.txt
    fi
  else
    echo $i compilation error >> error.txt
  fi
done
