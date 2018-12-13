#!/bin/bash

# if all of the reader nodes die, kill runsv causing the container to exit
if [[ "$USE_MULTICORE_READONLY" ]]; then
  BRAVOD_READONLY_PIDS=`pgrep -f read-only`
  if [[ ! $? -eq 0 ]]; then
  	echo NOTIFYALERT! bravod reader nodes have quit unexpectedly, starting a new instance..
    RUN_SV_PID=`pgrep -f /etc/service/bravod`
    kill -9 $RUN_SV_PID
  fi
fi

# if the writer node dies, kill runsv causing the container to exit
BRAVOD_PID=`pgrep -f p2p-endpoint`
if [[ ! $? -eq 0 ]]; then
  echo NOTIFYALERT! bravod has quit unexpectedly, checking for core dump and then starting a new instance..
  sleep 30
  SAVED_PID=`cat /tmp/bravodpid`
  if [[ -e /tmp/core.$SAVED_PID ]]; then
    gdb --batch --quiet -ex "thread apply all bt full" -ex "quit" /usr/local/bravod-full/bin/bravod /tmp/core.$SAVED_PID >> /tmp/stacktrace
    STACKTRACE=`cat /tmp/stacktrace`
    echo NOTIFYALERT! bravodsync stacktrace from coredump: $STACKTRACE
  fi
  RUN_SV_PID=`pgrep -f /etc/service/bravod`
  kill -9 $RUN_SV_PID
fi

# check on this every 10 seconds
sleep 10
