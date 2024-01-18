#!/bin/bash

if [ "$EUID" -ne 0 ]; then
  echo "Please run this script with sudo or as root."
  exit 1
fi

detect_distro() {
  if [ -f /etc/os-release ]; then
    . /etc/os-release
    if [ -n "$ID" ]; then
      echo "$ID"
    fi
  fi
}

install_deps() {
  distro=$(detect_distro)
  case "$distro" in
    "ubuntu" | "debian")
      apt update
      apt install -y cmake make gcc-g++ gcc gcc-multilib
      ;;
    "centos" | "rhel" | "fedora")
      dnf install -y cmake make gcc-g++ gcc gcc-multilib
      ;;
    "arch")
      pacman -S cmake make gcc-g++ gcc gcc-multilib
      ;;    
    *)
      echo "Unsupported distribution: $distro"
      exit 1
      ;;
  esac
}

install_deps

echo "Installation completed successfully."
