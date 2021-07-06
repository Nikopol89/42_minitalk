#!/bin/bash
#
# leaks -atExit --

ARG=$(cat ./var/text.txt);

if [[ "$(uname)" = "Linux" ]]
	then
	PID=$(ps aux | pgrep server);
else
	PID=$(ps aux | pgrep -f ./server);
fi

time -p ./client $PID "$ARG"
