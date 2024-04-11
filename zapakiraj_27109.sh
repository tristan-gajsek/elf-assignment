#!/usr/bin/env bash

if [[ $# -eq 0 ]]; then
	echo "No password provided"
	exit 1
fi

if echo "$1" | docker login -u tristangajsek --password-stdin; then
	docker build -t tristangajsek/elf-changer .
	docker push tristangajsek/elf-changer:latest
	docker logout

    exit 0
fi

exit 1
