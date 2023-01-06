#!/bin/bash

sudo apt install libxcb-dri3-dev libxcb-util-dev libxcb-util-dev libxcb-xinerama0-dev libxcb-sync-dev libxcb-render-util0-dev libxcb-keysyms1-dev libxcb-image0-dev libxcb-icccm4-dev libxcb-icccm-dev libxcb-xkb-dev libxvmc-dev libxv-dev libxss-dev libxres-dev libxmuu-dev libxkbfile-dev libxaw7-dev libfontenc-dev libx11-xcb-dev lib-x11-xcb-dev

command -v cmake || python -m pip install cmake

python3 -m pip install -r requirements.txt