#!/bin/bash

# Sachin Shah
# April 3, 2020

# Init Vars
PASS=0
NUM_CASES=9


# Run test cases

echo ""
echo "###########################"
echo "   Running test cases...   "
echo "###########################"
echo ""

run_test()
{
	local testcase=$1

	echo -n "   Test Case $testcase: "

	./bin/main "test-cases/$testcase" > /dev/null

	gcc out.c 2> /dev/null
	val=$?

	if [[ $val != 0 ]]; then
		echo "failed on compile"
		return
	fi

	./a.out > out.txt 2> /dev/null
	val=$?
	if [[ $val != 0 ]]; then
		echo "failed on run"
		exit
		return
	fi

	gcc "test-cases/$testcase" && ./a.out > case.txt 2> /dev/null
	diff out.txt case.txt > /dev/null
	val=$?

	if [[ $val != 0 ]]; then
		echo "failed on output"
		return
	fi

	echo "passed"

	PASS=`expr $PASS + 1`
}

for i in `seq -f "%02g" 1 $NUM_CASES`;
do
	run_test "test$i.c"
done

echo ""

# Cleanup produced files
rm -f a.out
rm -f out.txt
rm -f case.txt
rm -f out.c
