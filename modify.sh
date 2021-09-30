for i in `ls eff_*.dat`; do
   echo "nevt 1000 nrun 1000" > $i.modified;
   cat $i >> $i.modified;
done

