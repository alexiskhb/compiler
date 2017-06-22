#!/bin/bash
script_dir=$(dirname $0)
test_dir=$script_dir/test-gen
ddots=..................................................
dots=.........................
for filename in $test_dir/*.in; do
	echo $ddots $filename
	asm=$test_dir/$(basename "$filename" .in).s
	answer=$test_dir/$(basename "$filename" .in).std
	output=$test_dir/$(basename "$filename" .in).out
	executable=$test_dir/$(basename "$filename" .in).exe

	{ $script_dir/compiler -S $filename >$asm || { echo "$dots pascal compilation failed" && false; }; }  &&
	{ clang $asm -o $executable               || { echo "$dots asm compilation failed"    && false; }; }  &&
	{ $executable >$output                    || { echo "$dots execution failed"          && false; }; }  &&
	{ rm $executable                          || { echo "$dots rm executable failed"      && false; }; }    
	# diff $output $answer && rm -f $output
done
