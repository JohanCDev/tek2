#!/bin/sh

cat tests_files/input | ./groundhog 7 > tests_files/our_out
diff tests_files/output tests_files/our_out &> /dev/null
var=$(echo $?)
if [ $var = "0" ]
then
    echo "\033[0;32mOutput is the same \033[0m"
else
    echo "\033[0;31mWrong output\033[0m"
fi