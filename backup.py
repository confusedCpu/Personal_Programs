#!/usr/bin/python3

'''
Python3 scipt - backup.py
This script will back up the users profile 
This script is intended to be cross platform ( Linux, OSX, Windows ), but has
not reached the point 
Updated by: martinak Date: 2/9/18 
'''

from math import floor
from os import access, listdir, mkdir, popen, stat
from os.path import exists, isdir, ismount, join
from shutil import copy2
from sys import argv, exit


def backup(src, dest):
    # handles the actuall transfer of the files from the source to the destination
    # Inspired by a response by 'Mital Vora' on Stack Overflow

    if not exists(dest):
        mkdir(dest)

    for item in listdir(src):
        item_path = join(src, item)
        dest_path = join(dest, item)

        if isdir(item_path):
            backup(item_path, dest_path)

        else:
            if not exists(dest_path) or stat(item_path).st_mtime - stat(dest_path).st_mtime > 1:
                try:
                    print("** Copying {} -> {}".format(item_path, dest_path))
                    copy2(item_path, dest_path)
                except OSError as error:
                    print("[ERROR] Failed to copy {}! Skiping! \n{}"
                          .format(item_path, error))
                    continue
            else:
                print("** Skipping {}; It already exists and has not been updated since last backup"
                      .format(item_path))


def build_dirs(src):
    # bulds a list of the folders that need to be backed up depending on your OS

    if isdir("Library"):
        # is OSX
        print("** OSX user profile detected")
        return ["Desktop", "Documents", "Downloads", "Movies", "Music", "Pictures"]
    else:
        # is Windows
        print("** Windows user profile detected")
        return ["Desktop", "Documents", "Downloads", "Music", "Pictures", "Videos"]
# end build_dirs


def build_profiles(src):
    # build a list of profiles to back up on multi-user systems
    pass


def check_input(src, mount, dest):
    ''' 
    verifies that the source and destination directories exists.
    If source is not a directory the script fails
    If dest does not exist, it will attempt to create it and fails if it cant
    '''
    # verify source directory exists
    if not isdir(src):
        print("[ERROR] {} is not a directory \nThe script will now exit!".format(src))
        exit()

    # verify that mount is a mount point
    if not ismount(mount):
        print("[ERROR] {} is not a mount point. The script will now exit!".format(mount))
        exit()

    # verify there is enough space on the mount point
    check_space(src, mount)

    # verify existence of the destination dir and attempts to create it
    if not isdir(dest):
        print(
            "** {0} is not a directory. Attempting to make {0}".format(dest))
        try:
            mkdir(dest)
            print("** {} created".format(dest))
        except OSError as error:
            print("[ERROR] Failed to make {} \n{} \nThe script will now exit!"
                  .format(dest, error))
            exit()

# end check_input


def check_space(src, mount):
    # verifies that there is enough space on the destination

    ssize = popen("du -sh " + src + "| awk '{print $1}'").read()[:-1]
    sfree = popen("df -h | grep " +
                  mount[:-1] + " | awk '{print $4}'").read()[:-1]

    size_bits = convert_to_bits(ssize)
    free_bits = convert_to_bits(sfree)

    if size_bits >= free_bits:
        print("[ERROR] there is not enough space on the destination: Src={} -> Dest={}"
              .format(ssize, sfree))
    else:
        print("** Src size: {} -> Dest free: {}".format(ssize, sfree))
        print("** There is enough free space for the transfer.")
# end check_space


def convert_to_bits(str_size):
    # converts a string to an integer then determines it's size in bits
    '''
    could instead set up an enum that compares the last character and the 
    number instead of doing a conversion. This might speed up the script
    '''
    unit = str_size[-1]
    size = floor(float(str_size[:-1]))

    if unit == 'B':
        size *= 8
    elif unit == 'K':
        size *= 8000
    elif unit == 'M':
        size *= 8000000
    elif unit == 'G':
        size *= 8000000000
    elif unit == 'T':
        size *= 8000000000000
    else:
        print("[ERROR] The unit denoted by '{}', is not recognized. \n Exiting!"
              .format(unit))
        exit()

    return size
# end convert_to_bits


def get_help():
    print('''\nThis script will back up user profile information.
                Three parameters are passed in: 
                first is the source directory usually the 'Users' directory
                second is the destination mount point
                third is the directory name where the files will be backedup 

                Usage:
                    backup.py <src_dir> <dest_mount point> <dest_dir>

                Example:
                    backup.py "/mnt/Macintosh HD/Users" /mnt doej
                    

                If an OSX user profile is detected it will back up:
                    Desktop, Documents, Movies, Music, and Pictures

                If a Windows user profile is detected it will back up:
                    Desktop, Documents, Music, Pictures, and Videos''')
# end get_help


def main():  # argv - 0: script name 1: src directory 2: mount point 3: dest directory name

    if 4 != len(argv):
        get_help()
        exit()
    elif popen("whoami") != "root":
        print(r'This script must be ran as root. Re-run the script with elevated privlages')
        exit()

    src = argv[1]
    mount = argv[2]
    dest = join(mount, "backups", argv[3])

    # verify directories, permissions, and if there is enough free space
    check_input(src, mount, dest)

    # build a list of the dirs that need to be backedup
    dirs = build_dirs(src)

    # transfer the files from src -> dest
    for item in dirs:
        _src = join(src, item)
        if exists(_src):
            _dest = join(dest, item)
            backup(_src, _dest)
# end main


if __name__ == "__main__":
    main()
