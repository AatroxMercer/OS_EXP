#! /bin/bash

for name in dev run sys proc; do
	sudo mount -R /$name ubuntu-base/$name
done

exit 0
