#!/usr/bin/python3
# This script will back up the users profile
# Updated by: martinak Date: 2/1/18

from os import access, chdir, getcwd, mkdir 
from os.path import isdir, islink, join
from shutil import copytree
from sys import argv, exit

def get_help():
    print( '''\nThis script will back up user profile information.
                Two parameters are passed in; the first is the source directory,
                the second is the destination directory

                Usage:
                    backup.py <src_dir> <dest_dir>

                Example:
                    backup.py "/mnt/Macintosh HD/Users/John Doe" "/mnt/backup_dir/John Doe"

                If an OSX user profile is detected it will back up:
                    Desktop, Documents, Library, Movies, Music, and Pictures

                If a Windows user profile is detected it will back up:
                    Desktop, Documents, Music, Pictures, and Videos''' )
# end get_help

def main():

    if 3 != len( argv ): 
        get_help()
        exit()

    src = argv[1]
    dest = argv[2]

    starting_dir = getcwd()

    if not isdir( src ):
        print( "[ERROR] {} is not a directory \nThe script will now exit!".format( src ) )
        exit()
    # verify existence of the destination dir and attempts to create is 
    elif not isdir( dest ):
        print( "[ERROR] {0} is not a directory. Attempting to make {0}".format( dest ) )
        try:
            mkdir( dest )
            print( "** {} created".format( dest ) )
        except OSError as error:
            print( "[ERROR] Failed to make {} \n{} \nThe script will now exit!"
                    .format( dest, error ) )
            exit()

    chdir( src )
    print( "** Changed working directory to {}".format( src ) )

    if isdir( "Library" ):
        # is OSX
        dirs = [ "Desktop", "Documents", "Library", "Movies", "Music",
                 "Pictures" ]
        print( "** OSX user profile detected" )
    else:
        # is Windows
        dirs = [ "Desktop", "Documents", "Music", "Pictures", "Videos" ]
        print( "** Windows user profile detected" )

        for a_dir in dirs:
            try:
                if isdir( a_dir ):
                    print( "** copying {0} -> {1}/{0}".format( a_dir, dest ) )
                    copytree( a_dir , join( dest, a_dir ) )
                else:
                    print( "** Skipping {}, it is not a valid dir".format( a_dir ) )
            except OSError as error:
                print( "[ERROR] Failed to copy {0} \n{1} \nSkipping {0}".format( a_dir, error ) )

    # return to the original working dir
    chdir( starting_dir )

# end main


if __name__ == "__main__":
    main()
