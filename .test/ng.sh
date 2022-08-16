make -C ".." re

for file in `find ng -mindepth 1 -maxdepth 1 | sort`; do
  TEST 1 "$file"
done

for file in `find ng/mandatory -mindepth 1 -maxdepth 1 | sort`; do
  TEST 1 "$file"
done
