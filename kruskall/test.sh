#!/bin/csh
echo "pa2 cs315001s15: Kruskal Tests"
echo "------------------"
echo "output expected: IMPOSSIBLE"
echo "output computed"
./pa2 ./tests/in0.in
echo "------------------"
echo "output expected: 3, 9"
echo "output computed"
./pa2 ./tests/in1.in
echo "------------------"
echo "output expected: 3, 12"
echo "output computed"
./pa2 ./tests/in2.in
echo "------------------"
echo "output expected: 4, 16"
echo "output computed"
./pa2 ./tests/in3.in
echo "------------------"
echo "output expected: 8, 14"
echo "output computed"
./pa2 ./tests/in9.in
echo "------------------"
echo "output expected: 8, 14"
echo "output computed"
./pa2 ./tests/in9c.in
echo "------------------"
echo "output expected: 8, 19"
echo "output computed"
./pa2 ./tests/in9d.in
echo "------------------"
echo "output expected: 99, 1533"
echo "output computed"
./pa2 ./tests/in100.in
echo "------------------"
echo "output expected: 100, 100, 1 cycle"
echo "output computed"
./pa2 ./tests/in100c.in
echo "------------------"
echo "output expected: 99, 200"
echo "output computed"
./pa2 ./tests/in100e.in
echo "----END-----------"
