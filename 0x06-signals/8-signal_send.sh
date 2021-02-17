#!/bin/bash
# script that sends the signal SIGQUIT to a process, given its PID
if [ $# -ne 1 ]
then
  echo "Usage: $0 <pid>"
  exit 1
fi

kill -s SIGQUIT $1
