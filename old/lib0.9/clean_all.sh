for dir in  VecNd SE2d LLcells Wrap_plplot Test MC-SE2d
do
  cd $dir; echo $dir; make clean; echo; cd .. 
done
rm */lib*.a *~ */*~
