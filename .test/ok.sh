make -C ".." re

for file in `find ok -mindepth 1 -maxdepth 1 | sort`; do
  TEST 0 "$file"
done

for file in `find ok_mandatory -mindepth 1 -maxdepth 1 | sort`; do
  TEST 0 "$file"
done
