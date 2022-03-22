#!/usr/bin/env bash

CC="clang++"
CFLAGS="-Wall -Wextra -Werror -std=c++98"

compile ()
{
	# 1=file 2=define used {ft/std} 3=output_file
	$CC $CFLAGS -D ${2} ${1} && (time ./a.out) > ${3} 2> time.txt
	# $CC $CFLAGS -D ${2} ${1} && (time valgrind ./a.out) > ${3} 2> time.txt
}

make_diff ()
{
	TEST=${1}
	
	TMP=${TEST::-4}
	FT="_ft"
	DIFF_FT=$TMP$FT

	STD="_stl"
	DIFF_STD=$TMP$STD

	printf "%s\n" $TMP
	compile ${1} "TESTED_NAMESPACE=ft" $DIFF_FT
	echo -n "Execution time FT ------------>"
	sed -n '2p' < time.txt
	printf "\n"

	compile ${1} "TESTED_NAMESPACE=std" $DIFF_STD
	echo -n "Execution time STL ----------->"
	sed -n '2p' < time.txt
	printf "\n"
	
	diff $DIFF_FT $DIFF_STD > diff.txt
	if [ -s diff.txt ]; then
		printf "diff for %-23s" $TMP
		echo -e "💔"
		cat diff.txt
	else
		printf "diff for %-23s" $TMP
		echo -e "✅"
		# cat $DIFF_FT
		# printf "\n\n"
	fi
	echo "------------------------------------------------"
	rm $DIFF_FT
	rm $DIFF_STD
	rm diff.txt
	rm time.txt
	rm a.out
}

if [ $# -eq 0 ]; then
	echo -e "\e[1;35mSTACK\e[0m"
	TEST="stack.cpp"
	make_diff $TEST

	echo -e "\e[1;35m\nVECTOR\e[0m"
	TEST="vector_allocator.cpp"
	make_diff $TEST

	TEST="vector_capacity.cpp"
	make_diff $TEST

	TEST="vector_constructors.cpp"
	make_diff $TEST

	TEST="vector_elements.cpp"
	make_diff $TEST

	TEST="vector_it_class.cpp"
	make_diff $TEST

	TEST="vector_it_string.cpp"
	make_diff $TEST

	TEST="vector_it_nonmember.cpp"
	make_diff $TEST

	TEST="vector_modifiers.cpp"
	make_diff $TEST

	TEST="vector_operators.cpp"
	make_diff $TEST

	echo -e "\n\e[1;35mMAP\e[0m"
	TEST="map_cap_elem_access.cpp"
	make_diff $TEST

	TEST="map_constructeurs.cpp"
	make_diff $TEST

	TEST="map_element_modifiers.cpp"
	make_diff $TEST

	TEST="map_iter.cpp"
	make_diff $TEST

	TEST="map_operations.cpp"
	make_diff $TEST

	echo -e "\e[1;35mBIG VALUES\e[0m"
	TEST="big_vector_stack.cpp"
	make_diff $TEST

	TEST="big_map.cpp"
	make_diff $TEST
	exit 1;

elif [ $@ == "stack" ]; then
	echo -e "\e[1;35mSTACK\e[0m"
	TEST="stack.cpp"
	make_diff $TEST
	exit 1;

elif [ $@ == "vector" ]; then
	echo -e "\e[1;35mVECTOR\e[0m"
	TEST="vector_allocator.cpp"
	make_diff $TEST

	TEST="vector_capacity.cpp"
	make_diff $TEST

	TEST="vector_constructors.cpp"
	make_diff $TEST

	TEST="vector_elements.cpp"
	make_diff $TEST

	TEST="vector_it_class.cpp"
	make_diff $TEST

	TEST="vector_it_string.cpp"
	make_diff $TEST

	TEST="vector_it_nonmember.cpp"
	make_diff $TEST

	TEST="vector_modifiers.cpp"
	make_diff $TEST

	TEST="vector_operators.cpp"
	make_diff $TEST

elif [ $@ == "map" ]; then
	echo -e "\e[1;35mMAP\e[0m"
	TEST="map_cap_elem_access.cpp"
	make_diff $TEST

	TEST="map_constructeurs.cpp"
	make_diff $TEST

	TEST="map_element_modifiers.cpp"
	make_diff $TEST

	TEST="map_iter.cpp"
	make_diff $TEST

	TEST="map_operations.cpp"
	make_diff $TEST
	exit 1;

elif [ $@ == "big" ]; then
	echo -e "\e[1;35mBIG VALUES\e[0m"
	TEST="big_vector_stack.cpp"
	make_diff $TEST

	TEST="big_map.cpp"
	make_diff $TEST
	exit 1;
fi

