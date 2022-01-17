#!/bin/sh
echo "--------------ls---------"
ls
echo "-------------------------"
echo "----- read and echo functions-------"


echo "What is your name?"
read name
echo "How do you do, $name?"
read remark
echo "I am $remark too!"
echo "---------------------"

echo "-------grep---------"

grep 'just' sampleText.txt

echo "--------------------"

echo "------- cat ---------"
cat sortExample.txt
echo "--------------------------"
echo "---------sort------------"
sort sortExample.txt

echo "-------------------------"
echo "-------------cd--------"
cd Project-0

echo "-----------------"
echo "------ls to prove cd---------"
ls
