LD_LIBRARY_PATH=$PWD/lib
export LD_LIBRARY_PATH

for i in test_*.java; do
  name=`echo $i | sed 's/\.java//'`;
  if  /usr/lib/jvm/java-6-sun/bin/javac $i; then 
    echo $i compiled
    if /usr/lib/jvm/java-6-sun/bin/java $name; then 
      echo $name run OK
    else
      echo $name run Error
    fi
  else
    echo $i compilation error
  fi
done
