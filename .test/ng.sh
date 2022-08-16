# make -C ".." re

for file in `find ng -mindepth 1 -maxdepth 1`; do
  TEST "$file"
done
