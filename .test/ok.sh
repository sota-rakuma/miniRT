# make -C ".." re

for file in `find ok -mindepth 1 -maxdepth 1`; do
  TEST "$file"
done
