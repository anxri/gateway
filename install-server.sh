#!/bin/bash

if ! command -v curl &> /dev/null
then
    echo "curl could not be found"
    exit
fi

if ! command -v make &> /dev/null
then
    echo "make could not be found"
    exit
fi

if ! command -v cmake &> /dev/null
then
    echo "cmake could not be found"
    exit
fi

if ! command -v crontab &> /dev/null
then
    echo "crontab could not be found"
    exit
fi

PORT=$1
SECRET=$2
INST_PATH=$3

if [[ -z "$PORT" ]]; then
    echo "Port missing. exit."
    exit 1
fi

if [[ -z "$SECRET" ]]; then
    echo "Secret missing. exit."
    exit 1
fi

if [[ -z "$INST_PATH" ]]; then
    INST_PATH="/usr/bin"
fi

if [ -d "$INST_PATH" ]; then
  ./build-server.sh

  echo "Installing lacus-server."
  cp ./dist/server/lacus-server ${INST_PATH}

  echo "Writing config files."
  mkdir -p ~/.config/lacus/server

  echo "$PORT" > ~/.config/lacus/server/port
  echo "$SECRET" > ~/.config/lacus/server/key

  echo "writing crontab."
  (crontab -l ; echo "@reboot $INST_PATH/lacus-server") | crontab -

  echo "done."
fi








