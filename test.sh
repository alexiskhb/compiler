#!/bin/bash
script_dir=$(dirname $0)
for filename in $script_dir/test/*.in; do
	echo ..................................................$filename
	output=$script_dir/test/$(basename "$filename" .in).out
	answer=$script_dir/test/$(basename "$filename" .in).std
	$script_dir/compiler --lexical $filename >$output
	diff $output $answer && rm -f $output
done
for filename in $script_dir/test/*.errin; do
	echo ..................................................$filename
	output=$script_dir/test/$(basename "$filename" .errin).out
	answer=$script_dir/test/$(basename "$filename" .errin).std
	$script_dir/compiler --lexical $filename 2>$output >/dev/null
	diff $output $answer && rm -f $output
done
total=$(find $script_dir/test/*.std 2>/dev/null | wc -l)
failed=$(find $script_dir/test/*.out 2>/dev/null | wc -l)
passed=`expr $total - $failed`
echo $passed of $total tests passed