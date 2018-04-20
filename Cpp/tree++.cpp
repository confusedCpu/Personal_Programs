/* tree++
 * This is a rewrite of tree in modern c++
 * To compile the source, you need to link stdc++fs
 */

/* TODO
 *
 * take a directory path from cli           - done , should be wrapped
 * validate the paths existence             - done w/ lambda
 * create a path object from cli            - done
 * print content of the path individually   - done
 * recursively walk nested dirs             - WIP
 * print colored output                     - done
 */

#include <experimental/filesystem>
#include <iostream>
#include <string>

using namespace std;

namespace fs = std::experimental::filesystem;

namespace format
{
    /* ANSI Color Codes
     *      color    forground   background
     * ------------------------------------
     *      black    30          40
     *      red      31          41
     *      green    32          42
     *      yellow   33          43
     *      blue     34          44
     *      magenta  35          45
     *      cyan     36          46
     *      white    37          47
     *
     * Modifiers
     * ------------------------------------
     *      reset           0
     *      bold            1
     *      underline       4
     *      inverse         7
     *      bold off        21
     *      underline off   24
     *      inverse off     27
     */

    string clear = "\033[0m";      // clear formating
    string dir   = "\033[4;31m";   // red + underline
    string file  = "";             // no formating
    string sym   = "\033[36m";     // cyan

    int depth    = 0;              // keeps track of the directory depth
}


// function prototypes
void print( fs::directory_entry entry, string format );
void walk( fs::path pth );


int main( int argc, char** args  )
{
    const fs::path root_path = args[1];

    if(fs::is_directory(root_path))
    {
        walk(root_path);
    }
    else
    {
        // TODO figure out how to throw an error
        cout << "ERROR: the path provided is not a directory!" << endl;
        exit(1);
    }
}

/* walk
 * Iterates through directory_entries calling itself recursively if a directory
 * is encountered
 *
 * logic:
 *
 * create iterator
 * for each iteration
 *   if is a file       -> print
 *   if is a symlink    -> print source then dest
 *   if is a directory  -> call recusively with current entry
 *   else               -> ignore
 * exit
 */
void walk(fs::path pth)
{
    for( auto& entry : fs::directory_iterator(pth) )
    {
            if( fs::is_regular_file(entry) )
            {
                print(entry, format::file);
            }
            else if( fs::is_symlink(entry) )
            {
                print(entry, format::sym);
            }
            else if( fs::is_directory(entry) )
            {
                print(entry, format::dir);
                walk( entry.path() );
            }
            else continue;
    }
}

/* void print
* Prints a directory_entry with a specific format
 */
void print( fs::directory_entry entry, string fmt )
{
    cout << fmt << entry.path().filename() << format::clear << endl;
}
