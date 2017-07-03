#!/bin/bash
# This script installs the basics for a new Arch Linux system

# Install basic tools to get started
  echo 'Installing packages from the Arch repositories and upgrading the system'
  sudo pacman -Syu base-devel zsh make git curl vim xorg arandr dosfstools exfat-utils

# Creates a home dir if one is not there
  if ! [ -d $HOME ]; then
    echo 'Making home dir for user at /home/'$USER
    mkdir -p /Home/$USER
  fi

# checks for the existence of a source folder in the users home dir
  if ! [ -d $HOME/Src ]; then
    echo 'Making Source code dir at '$HOME/'Src'
    mkdir -p $HOME/Src
  fi
  cd $HOME/Src

# Install Oh-My-Zsh for zsh themes
  echo 'Installing Oh-My-Zsh'
  sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

# Clones the package-query dependency for yaourt then builds it if not already installed
  if ! [ -d $HOME/Src/package-query ]; then 
    echo 'Cloning "package-query" from git-hub and installing'
    git clone https://aur.archlinux.org/package-query.git
    cd $HOME/Src/package-query
    makepkg -si
    cd ..
  fi

# Clones yaourt and builds it if not already installed
  if ! [ -d $HOME/Src/yaourt ]; then 
    echo 'Cloning 'yaourt' and installing'
    git clone https://aur.archlinux.org/yaourt.git
    cd yaourt
    makepkg -si
  fi

# Updates systems with AUR packages and DE tools
  echo 'Installing packages from the AUR and upgrading existing packages with AUR equivilents'
  yaourt -Syuab i3-gaps-git conky compton xautolock i3bar lightdm lightdm-webkit2-greeter chronie \
	  ranger alsa-firmware alsa-lib alsa-util w3m vlc libreoffice-fresh gnome-disk-utility \
	  testdisk parted ntfs-3g hfsprogs rust cargo-git g++ clamtk mutt \
	  htop refind-efi python3 

# Download and install Pathogen for Vim plugins
  if ! [ -d $HOME/.vim/autoload || -d $HOME/.vim/autoload ]; then
    echo 'Creating the .vim/autoload and .vim/bundle dirs in '$HOME
    mkdir -p ~/.vim/autoload ~/.vim/bundle 
    sh -c "$(curl -LSso ~/.vim/autoload/pathogen.vim https://tpo.pe/pathogen.vim)"
  fi

# Clones plugins from github
  vimPath=$HOME/.vim/bundle/

  git clone https://github.com/scrooloose/nerdtree.git $vimPath/nerdtree # nerdTree

  git clone https://github.com/vim-syntastic/syntastic.git $vimPath/syntastic # syntastic

  git clone https://github.com/vim-airline/vim-airline.git $vimPath/vim-airline # vim-airline

  git clone https://github.com/airblade/vim-gitgutter.git $vimPath/vin-gitgutter # vim-gitgutter

  git clone https://github.com/ervandew/supertab.git $vimPath/supertab # supertab

  unset vimPath

# Add services to systemd
  echo 'Adding services to systemd'
  systemctl enable lightdm alsa

# Set user settings
  chsh -s /bin/zsh
  echo "Shell has been changed to ZSH"

# Move personal config files to $Home
  cd $HOME/Src/Personal_Configs
  cp -rfvL .zshrc .config .vimrc .conkyrc .bashrc $HOME/
  echo "Config files have been copied to $HOME"
  
# Add some error checking with diff to verify sucessfull transfer
