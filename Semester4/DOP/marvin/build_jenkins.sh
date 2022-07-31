#!/bin/zsh
docker stop Jenkins && docker rm Jenkins
docker build -t jenkinsdockerfile . && \
docker run -d -p 8080:8080 --name Jenkins --env-file env.list jenkinsdockerfile && \
sleep 5 && open -a safari localhost:8080