#!/usr/bin/python3
# sortdir.py
#
# This program will sort files in a directory or give you usefull information
# about the types of files


import os
import re
import shutil


# produce a list of file types in a given directory
def gen_file_types( directory ):

    file_types = []
    types_re   = re.compile( r'(?<=\.)\w+$' )

    for files in os.listdir( directory ):

        match = re.search( types_re, files )

        if match not None:
            print( '** Found --> {}'.format( match.group( 0 )))

            if match.group( 0 ) not in file_types:
                print( '** {} has been added to the list'.format(match.group(0)) )
                file_types.append( match.group( 0 ))
            else:
                print('**')

        else:
            print( '**Could not process {}, moving on!'.format(match.group(0)) )

    return file_types

    # end gen_file_types


# makes the directories that the files will be sorted in to
def make_dirs( type_list, target_dir ):

        for types in type_list:
            try:
                os.mkdir( os.path.join( target_dir, types ))
                print( '** {} directory created.'.format( types ))

            except OSError as error:
                print( '[ERROR] Failed to make {}/{}:    {}'.format( target_dir, types, str( error )))
                print( '** Skipping..' )
                continue

#  end make_dirs


# move files into their appropriate directory
def move_files( type_list, target_dir ):

    re_template = r'\w+\.{}$'

    for types in type_list:

        types_re = re.compile( re_template.format( types ))

        for files in os.listdir( target_dir ):

            if re.match( types_re ) not None:
                try:
                    print( '** Moving {}  -->  {}/{}'.format( files, target_dir, types))
                    shutil.copy2( os.path.join( target_dir, types, files ))

                except OSError as error:
                    print( '[ERROR] Moving {}  -->  {}/{}:    {}'.format( files, target_dir, str( error )))

                finally:
                    print( '**' )

            else:
                print( '**' )

    # end move_files


# prints a summary of the folders made and the number of files contained within each
def summary( type_list, target_dir ):

    print( '''
            ** Summary **
            *************
            ** Directories Made: {}
            ***************************
            '''.format( len( types_list )))

    for i in { 0..len( type_list ) }:
        print( "** {} : {}".format( type_list[i], len( os.listdir(os.build.path( target_dir, type_list[i] ))))

    # end summary

# confirms that the user has read and write permissions on the directory
def verify_permissions( target_dir ):

    if not access( target_dir, os.R_OK ):
        print( '[ERROR] You do not have read permissions on {}!'.format( target_dir ))
        return 1

    elif not os.access( target_dir, os.W_OK ):
        print( '[ERROR] You do not have write permissions on {}!'.format( target_dir ))
        return 2

    else:
        print( '** Apropriate permissions on {} verified.'.format( target_dir ))

    # end verify_permissions


def main( *args ):
    pass
