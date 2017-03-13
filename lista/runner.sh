#!/usr/bin/env bash
echo "Running benchmarker"

echo "tester" > results.txt
#echo "" > wnioski.txt
export LD_LIBRARY_PATH=.
cmake . -DALL=ON >> /dev/null
make >> /dev/null
echo "----------------------------------testing_with_optimization_lvl-o-----------------------------------------" >>results.txt
echo "----------------------------------static-----------------------------------------" >>results.txt
./tester_static >> results.txt
#echo "-o" >> wnioski.txt 2>>wnioski.txt
#((time ./tester_static) | tail -1) >> wnioski.txt 2>>wnioski.txt
echo "----------------------------------shared-----------------------------------------" >>results.txt
./tester_shared >> results.txt
#((time ./tester_shared) | tail -1) >> wnioski.txt 2>>wnioski.txt
echo "----------------------------------dynamic----------------------------------------" >>results.txt
./tester_dynamic >> results.txt
#((time ./tester_dynamic) | tail -1) >> wnioski.txt 2>>wnioski.txt


cmake . -DALL=ON -DOPTIMIZATION=2 >> /dev/null
make >> /dev/null
echo "----------------------------------testing_with_optimization_lvl-o2-----------------------------------------" >>results.txt
echo "----------------------------------static-----------------------------------------" >>results.txt
./tester_static >> results.txt
#echo "-o2" >> wnioski.txt
#((time ./tester_static) | tail -1) >> wnioski.txt 2>>wnioski.txt
echo "----------------------------------shared-----------------------------------------" >>results.txt
./tester_shared >> results.txt
#((time ./tester_shared) | tail -1) >> wnioski.txt 2>>wnioski.txt
echo "----------------------------------dynamic----------------------------------------" >>results.txt
./tester_dynamic >> results.txt
#((time ./tester_dynamic) | tail -1) >> wnioski.txt 2>>wnioski.txt

cmake . -DALL=ON -DOPTIMIZATION=3 >> /dev/null
make >> /dev/null 2>>wnioski.txt
echo "----------------------------------testing_with_optimization_lvl-o3-----------------------------------------" >>results.txt
echo "----------------------------------static-----------------------------------------" >>results.txt
./tester_static >> results.txt
#echo "-o3" >> wnioski.txt 2>>wnioski.txt
#((time ./tester_static) | tail -1) >> wnioski.txt 2>>wnioski.txt
echo "----------------------------------shared-----------------------------------------" >>results.txt
./tester_shared >> results.txt
#((time ./tester_shared) | tail -1) >> wnioski.txt 2>>wnioski.txt
echo "----------------------------------dynamic----------------------------------------" >>results.txt
./tester_dynamic >> results.txt
#((time ./tester_dynamic) | tail -1) >> wnioski.txt 2>>wnioski.txt


cmake . -DALL=ON -DOPTIMIZATION=s >> /dev/null
make >> /dev/null
echo "----------------------------------testing_with_optimization_lvl-os-----------------------------------------" >>results.txt
echo "----------------------------------static-----------------------------------------" >>results.txt
./tester_static >> results.txt
#echo "-os" >> wnioski.txt 2>>wnioski.txt
#((time ./tester_static) | tail -1)  >> wnioski.txt 2>>wnioski.txt
echo "----------------------------------shared-----------------------------------------" >>results.txt
./tester_shared >> results.txt
#((time ./tester_shared) | tail -1)  >> wnioski.txt 2>>wnioski.txt
echo "----------------------------------dynamic----------------------------------------" >>results.txt
./tester_dynamic >> results.txt
#((time ./tester_dynamic) | tail -1)  >> wnioski.txt 2>>wnioski.txt


echo "-----------------------------------------------END_OF_BENCHMARK--------------------------------------------" >>results.txt
echo "Results saved in results.txt"

make clean >> /dev/null