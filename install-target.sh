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

IP=$1
PORT=$2
SECRET=$3
INST_PATH=$4

if [[ -z "$IP" ]]; then
    echo "IP missing. exit."
    exit 1
fi

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
  ./build-target.sh

  echo "Installing lacus-target."
  sudo cp ./dist/target/lacus-target ${INST_PATH}

  echo "Writing config files."
  mkdir -p ~/.config/lacus/target

  echo "$IP" > ~/.config/lacus/target/ip
  echo "$PORT" > ~/.config/lacus/target/port
  echo "$SECRET" > ~/.config/lacus/target/key

  echo "writing crontab."
  (crontab -l ; echo "*/5 * * * * $INST_PATH/lacus-target") | crontab -

  echo "done."
fi
