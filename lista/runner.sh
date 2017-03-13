#!/usr/bin/env bash
echo "Running benchmarker"

echo "tester" > results.txt
cmake . -DALL=ON -DOPTIMIZATION= >> /dev/null
make >> /dev/null
echo "----------------------------------testing_with_optimization_lvl-o-----------------------------------------" >>results.txt
echo "----------------------------------static-----------------------------------------" >>results.txt
./tester_static >> results.txt
echo "----------------------------------shared-----------------------------------------" >>results.txt
./tester_shared >> results.txt
echo "----------------------------------dynamic----------------------------------------" >>results.txt
./tester_dynamic >> results.txt

cmake . -DALL=ON -DOPTIMIZATION=2 >> /dev/null
make >> /dev/null
echo "----------------------------------testing_with_optimization_lvl-o2-----------------------------------------" >>results.txt
echo "----------------------------------static-----------------------------------------" >>results.txt
./tester_static >> results.txt
echo "----------------------------------shared-----------------------------------------" >>results.txt
./tester_shared >> results.txt
echo "----------------------------------dynamic----------------------------------------" >>results.txt
./tester_dynamic >> results.txt

cmake . -DALL=ON -DOPTIMIZATION=3 >> /dev/null
make >> /dev/null
echo "----------------------------------testing_with_optimization_lvl-o3-----------------------------------------" >>results.txt
echo "----------------------------------static-----------------------------------------" >>results.txt
./tester_static >> results.txt
echo "----------------------------------shared-----------------------------------------" >>results.txt
./tester_shared >> results.txt
echo "----------------------------------dynamic----------------------------------------" >>results.txt
./tester_dynamic >> results.txt

cmake . -DALL=ON -DOPTIMIZATION=s >> /dev/null
make >> /dev/null
echo "----------------------------------testing_with_optimization_lvl-os-----------------------------------------" >>results.txt
echo "----------------------------------static-----------------------------------------" >>results.txt
./tester_static >> results.txt
echo "----------------------------------shared-----------------------------------------" >>results.txt
./tester_shared >> results.txt
echo "----------------------------------dynamic----------------------------------------" >>results.txt
./tester_dynamic >> results.txt


echo "Results saved in results.txt"
