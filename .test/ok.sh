make -C ".." re

for file in `find ok -mindepth 1 -maxdepth 1 -type f | sort`; do
  TEST 0 "$file"
done

for file in `find ok/mandatory -mindepth 1 -maxdepth 1 -type f | sort`; do
  TEST 0 "$file"
done
