#!/bin/bash
script_dir=$(dirname $0)
test_dir=$script_dir/test-parse
lst_file=$test_dir/treeviewer.lst
rm -f $lst_file
for filename in $test_dir/*.in; do
	echo ..................................................$filename
	output=$test_dir/$(basename "$filename" .in).tree
	answer=$test_dir/$(basename "$filename" .in).std
	echo $filename $output >>$lst_file
	echo $filename $answer >>$lst_file
	$script_dir/compiler --parse $filename >$output
	diff $output $answer && rm -f $output
done
#for filename in $test_dir/*.errin; do
#	echo ..................................................$filename
#	output=$test_dir/$(basename "$filename" .errin).out
#	answer=$test_dir/$(basename "$filename" .errin).std
#	$script_dir/compiler --parse $filename 2>$output >/dev/null
#	diff $output $answer && rm -f $output
#done
total=$(find $test_dir/*.std 2>/dev/null | wc -l)
failed=$(find $test_dir/*.tree 2>/dev/null | wc -l)
errfailed=$(find $test_dir/*.out 2>/dev/null | wc -l)
passed=`expr $total - $failed - $errfailed`
echo $passed of $total tests passed
$script_dir/treeviewer $test_dir/treeviewer.lst
