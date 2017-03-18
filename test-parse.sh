#!/bin/bash
script_dir=$(dirname $0)
test_dir=$script_dir/test-parse
rm -f test-lst
for filename in $test_dir/*.in; do
	echo ..................................................$filename
	output=$test_dir/$(basename "$filename" .in).tree
	answer=$test_dir/$(basename "$filename" .in).std
	echo $filename $output >>$test_dir/test-lst
	echo $filename $answer >>$test_dir/test-lst
	$script_dir/compiler $filename >$output
	diff $output $answer && rm -f $output
done
total=$(find $test_dir/*.std 2>/dev/null | wc -l)
failed=$(find $test_dir/*.tree 2>/dev/null | wc -l)
passed=`expr $total - $failed`
echo $passed of $total tests passed
$test_dir/treeviewer