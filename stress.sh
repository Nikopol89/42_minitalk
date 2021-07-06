#!/bin/bash

ARG=$(cat ./var/text.txt);

if [[ "$(uname)" = "Linux" ]]
	then
	PID=$(ps aux | pgrep server);
else
	PID=$(ps aux | pgrep -f ./server);
fi

declare -i i=1

while [[ 1 ]]
	do
	echo TEST $i
	i=$(( i + 1 ))
	time -p ./client $PID "$ARG"
	done