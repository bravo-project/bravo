#!/bin/bash

echo /tmp/core | tee /proc/sys/kernel/core_pattern
ulimit -c unlimited

# if we're not using PaaS mode then start bravod traditionally with sv to control it
if [[ ! "$USE_PAAS" ]]; then
  mkdir -p /etc/service/bravod
  cp /usr/local/bin/bravo-sv-run.sh /etc/service/bravod/run
  chmod +x /etc/service/bravod/run
  runsv /etc/service/bravod
else
  /usr/local/bin/startpaasbravod.sh
fi
