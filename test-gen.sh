#!/bin/bash
script_dir=$(dirname $0)
test_dir=$script_dir/test-gen
ddots=..................................................
dots=.........................
for filename in $test_dir/*.in; do
	echo $ddots $filename
	asm=$test_dir/$(basename "$filename" .in).s
	opt_asm=$test_dir/$(basename "$filename" .in).opt.s
	answer=$test_dir/$(basename "$filename" .in).std
	output=$test_dir/$(basename "$filename" .in).out
	opt_output=$test_dir/$(basename "$filename" .in).opt.out
	executable=$test_dir/$(basename "$filename" .in).exe
	opt_executable=$test_dir/$(basename "$filename" .in).opt.exe

	{ $script_dir/compiler -S $filename >$asm          || { echo "$dots pascal compilation failed"     && false; }; }  &&
	{ $script_dir/compiler -S -O $filename -o $opt_asm || { echo "$dots pascal compilation failed"     && false; }; }  &&
	{ clang $asm -o $executable                        || { echo "$dots asm compilation failed"        && false; }; }  &&
	{ clang $opt_asm -o $opt_executable                || { echo "$dots opt_asm compilation failed"    && false; }; }  &&
	{ $executable >$output                             || { echo "$dots execution failed"              && false; }; }  &&
	{ $opt_executable >$opt_output                     || { echo "$dots opt_execution failed"          && false; }; }  &&
	{ { diff $output $opt_output && rm $output ;}      || { echo "$dots outputs are different"         && false; }; }  &&
	{ { rm $executable && rm $opt_executable ;}        || { echo "$dots rm executable failed"          && false; }; }  
	# diff $asm $opt_asm
done
