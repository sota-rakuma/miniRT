make -C ".." fclean
make -C ".." bonus

for file in `find ok -mindepth 1 -maxdepth 1 | sort`; do
  TEST 0 "$file"
done

for file in `find ok_bonus -mindepth 1 -maxdepth 1 | sort`; do
  TEST 0 "$file"
done
