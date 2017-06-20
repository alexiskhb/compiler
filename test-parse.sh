#!/bin/bash
script_dir=$(dirname $0)
test_dir=$script_dir/test-parse
lst_file=$test_dir/treeviewer.lst
failed=`expr 0`
rm -f $lst_file
for filename in $test_dir/*.in; do
	echo ..................................................$filename
	output=$test_dir/$(basename "$filename" .in).tree
	answer=$test_dir/$(basename "$filename" .in).std
	echo $filename $output >>$lst_file
	echo $filename $answer >>$lst_file
	$script_dir/compiler --parse $filename >$output || (failed=`expr $failed + 1` && echo "$filename failed")
done
for filename in $test_dir/*.errin; do
	echo ..................................................$filename
	output=$test_dir/$(basename "$filename" .errin).tree
	answer=$test_dir/$(basename "$filename" .errin).std
	echo $filename $output >>$lst_file
	echo $filename $answer >>$lst_file
	$script_dir/compiler --parse $filename 2>$output >/dev/null && (failed=`expr $failed + 1` && echo "$filename failed")
	diff $output $answer && rm -f $output
done
total=$(find $test_dir/*in 2>/dev/null | wc -l)
# errfailed=$(find $test_dir/*.out 2>/dev/null | wc -l)
passed=`expr $total - $failed`
echo $passed of $total tests passed
$script_dir/treeviewer $test_dir/treeviewer.lst

for filename in $test_dir/*.tree; do
	answer=$test_dir/$(basename "$filename" .tree).std
	cat $answer 2>/dev/null >/dev/null || rm -f $filename
done
