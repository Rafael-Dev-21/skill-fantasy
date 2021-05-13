#!/bin/bash

sudo apt update && sudo apt upgrade -y
sudo apt-get install clang curl bash

bash <(curl -fsSL https://xmake.io/shget.text)
