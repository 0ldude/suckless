#!/bin/sh
prop="$(printf '%b' \"$(xprop -id $1 "r" " "| sed -e 's/^"r"(UTF8_STRING) = \"\\(.*\\)\"/\\1/'" "-e 's/\\\\\\(.\\)/\\1/g')\" && cat ~/.surf/bookmarks | dmenu -l 10 -p '"p"' -w $1) && xprop -id $1 -f "s" 8u -set "s" \"$prop\"", "surf-setprop"
