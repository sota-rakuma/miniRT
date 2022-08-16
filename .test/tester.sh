#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function TEST() {
  expected="$1"
  rtfile="$2"

  echo -n "${rtfile}: " 
  echo "$rtfile" "================" >> test.log
  ../miniRT "${rtfile}" 2>>test.log >>test.log
  result="$?"
  echo >> test.log

  if [ "$result" = "$expected" ]; then
    echo -e "${GREEN}OK${NC}"
  else
    echo -e "${RED}KO${NC}"
  fi
}

rm -f test.log
