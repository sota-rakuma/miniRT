make -C ".." fclean
make -C ".." bonus

for file in `find ng -mindepth 1 -maxdepth 1 | sort`; do
  TEST 1 "$file"
done

for file in `find ng_bonus -mindepth 1 -maxdepth 1 | sort`; do
  TEST 1 "$file"
done
