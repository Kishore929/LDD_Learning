#!/bin/sh

# ANSI escape codes
BOLD='\033[1m'
BLINK='\033[5m'
RESET='\033[0m'

# Colors
RED='\033[31m'
BROWN='\033[33m'
GREEN='\033[32m'
BLUE='\033[34m'

# Example: Hello World in bold, blink, red
echo "${BOLD}${BLINK}${RED}Hello World${RESET}"

# You can repeat for other colors too:
echo "${BOLD}${BROWN}Hello World in Brown${RESET}"
echo "${BOLD}${GREEN}Hello World in Green${RESET}"
echo "${BOLD}${BLUE}Hello World in Blue${RESET}"
