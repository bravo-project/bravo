#!/bin/bash
curl --silent -XPOST -H "Authorization: token $GITHUB_SECRET" https://api.github.com/repos/bravocoin/bravo/statuses/$(git rev-parse HEAD) -d "{
  \"state\": \"failure\",
  \"target_url\": \"${BUILD_URL}\",
  \"description\": \"JenkinsCI reports the build has failed!\",
  \"context\": \"jenkins-ci-bravocoin\"
}"
rm -rf $WORKSPACE/*
# make docker cleanup after itself and delete all exited containers
sudo docker rm -v $(docker ps -a -q -f status=exited) || true
