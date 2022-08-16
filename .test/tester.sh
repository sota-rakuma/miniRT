#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function TEST() {
  expected="$1"
  rtfile="$2"

  echo "$rtfile" "================" >> test.log
  ../miniRT "${rtfile}" 2>>test.log >>test.log
  result="$?"
  echo >> test.log

  if [ "$result" = "$expected" ]; then
    echo -n -e "${GREEN}OK: ${NC}"
    echo "$rtfile"
  else
    echo -n -e "${RED}KO: ${NC}"
    echo "$rtfile"
  fi
}

rm -f test.log
