#!/usr/bin/zsh

cmake .
make

echo "---------------------Begining-of-the-test---------------------" > wyniki.txt
echo "---------------------1000_records_4_bytes---------------------" >> wyniki.txt
./cw02 lib generate test1 1000 4
cp test1 test1_2
(time ./cw02 lib sort test1 1000 4) 2>> wyniki.txt
(time ./cw02 lib shuffle test1 1000 4) 2>> wyniki.txt
(time ./cw02 sys sort test1_2 1000 4) 2>> wyniki.txt
(time ./cw02 sys shuffle test1_2 1000 4) 2>> wyniki.txt
echo "---------------------10000_records_4_bytes---------------------" >> wyniki.txt
./cw02 lib generate test1 10000 4
cp test1 test1_2
(time ./cw02 lib sort test1 10000 4) 2>> wyniki.txt
(time ./cw02 lib shuffle test1 10000 4) 2>> wyniki.txt
(time ./cw02 sys sort test1_2 10000 4) 2>> wyniki.txt
(time ./cw02 sys shuffle test1_2 10000 4) 2>> wyniki.txt
echo "---------------------1000_records_512_bytes---------------------" >> wyniki.txt
./cw02 lib generate test1 1000 512
cp test1 test1_2
(time ./cw02 lib sort test1 1000 512) 2>> wyniki.txt
(time ./cw02 lib shuffle test1 1000 512) 2>> wyniki.txt
(time ./cw02 sys sort test1_2 1000 512) 2>> wyniki.txt
(time ./cw02 sys shuffle test1_2 1000 512) 2>> wyniki.txt
echo "---------------------10000_records_512_bytes---------------------" >> wyniki.txt
./cw02 lib generate test1 10000 512
cp test1 test1_2
(time ./cw02 lib sort test1 10000 512) 2>> wyniki.txt
(time ./cw02 lib shuffle test1 10000 512) 2>> wyniki.txt
(time ./cw02 sys sort test1_2 10000 512) 2>> wyniki.txt
(time ./cw02 sys shuffle test1_2 10000 512) 2>> wyniki.txt
echo "---------------------1000_records_4096_bytes---------------------" >> wyniki.txt
./cw02 lib generate test1 1000 4096
cp test1 test1_2
(time ./cw02 lib sort test1 1000 4096) 2>> wyniki.txt
(time ./cw02 lib shuffle test1 1000 4096) 2>> wyniki.txt
(time ./cw02 sys sort test1_2 1000 4096) 2>> wyniki.txt
(time ./cw02 sys shuffle test1_2 1000 4096) 2>> wyniki.txt
echo "---------------------10000_records_4096_bytes---------------------" >> wyniki.txt
./cw02 lib generate test1 10000 4096
cp test1 test1_2
(time ./cw02 lib sort test1 10000 4096) 2>> wyniki.txt
(time ./cw02 lib shuffle test1 10000 4096) 2>> wyniki.txt
(time ./cw02 sys sort test1_2 10000 4096) 2>> wyniki.txt
(time ./cw02 sys shuffle test1_2 10000 4096) 2>> wyniki.txt
echo "---------------------1000_records_8192_bytes---------------------" >> wyniki.txt
./cw02 lib generate test1 1000 8192
cp test1 test1_2
(time ./cw02 lib sort test1 1000 8192) 2>> wyniki.txt
(time ./cw02 lib shuffle test1 1000 8192) 2>> wyniki.txt
(time ./cw02 sys sort test1_2 1000 8192) 2>> wyniki.txt
(time ./cw02 sys shuffle test1_2 1000 8192) 2>> wyniki.txt
echo "---------------------10000_records_8192_bytes---------------------" >> wyniki.txt
./cw02 lib generate test1 10000 8192
cp test1 test1_2
(time ./cw02 lib sort test1 10000 8192) 2>> wyniki.txt
(time ./cw02 lib shuffle test1 10000 8192) 2>> wyniki.txt
(time ./cw02 sys sort test1_2 10000 8192) 2>> wyniki.txt
(time ./cw02 sys shuffle test1_2 10000 8192) 2>> wyniki.txt
echo "---------------------END_OF_TEST---------------------" >> wyniki.txt

rm test1
rm test1_2