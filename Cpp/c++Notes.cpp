//C++ Notes
//Updated: 9/28/17



//[if, elseif, else]

    if ( grade >= 90 )
        lettergrade = 'A';
    else if ( grade >= 80 )
        lettergrade = 'B';
    else if ( grade >= 70 )
        lettergrade = 'C';
    else if ( grade >= 60 )
        lettergrade = 'D';
    else
        lettergrade = 'F';


//[switch]

    switch(lettergrade) 
    {
        case 'A':
            cout << "You got an A" << endl;
            break;
        case 'B':
        case 'C':
            cout << "Good Job!" << endl;
            break;
        case 'D':
            cout << "Try Harder!" << endl;
        default:
            cout << "You failed!" << endl;
    }


//[for]

    char fullName[50][50]; 
    
    for( int a=0; a < 5; a++ )
        for( int b=0; b < 5; b++ )
            cin >> fullName[a][b]; 


//[while]

    while ( a < 5 )
    {
        cout << "'a' is less than 5!" << endl;
        a++;
    }
    cout << "'a' is now greater than 5!" << endl;


//[do while]

    do
    {
        cout << "a is less than 5!" << endl;
        a++;
    } while ( a < 5 );


//[break, continue]
    
    /* Break:
     *  - used inside a switch it causes the program to exit the switch statement
     *  - used inside a for, while, or do-while loop it causes the loop to exit
     * Continue:
     *  - used in a loop and forces execution to continue at the top of the loop
     */

    for( int i = 0; i < randNum; i++ )
    {
        if ( i % 2 = 0 )
            continue;
        else
            break;
    }


//[array]

    /* array - group of consecutive memory locations with the same name and data type
     * elements - memory locations in the array
     * length - total num of elements
     * index/subscript - location in the array
     * types - {one,two,multi}-demensional arrays
     */

     //declaration:
     //<data type> <array name>[<length>];
        char myName[50];
      //initialization:
        char myName = { 'a', 'l', 'e', 'x' };
      //multi
        char myName[4][6] = {{ 'a', 'l', 'e', 'x' },
                             { 'm', 'a', 'r', 't', 'i', 'n' }}

     // Passing arrays to function

    int getNums(int *numArray);

    int main()
    {
        int myNumbers[10];
        int numEntered = getNums(myNumbers);

        return numEntered;
    }

    getNums(int numArray[])
    {
        int i = 0;
        char answer;
        do
        {
            cout << "enter number : " ;
            cin >> numArray[i];
            i++;
            cout << "another? Enter C to Continue " ;
            cin >> answer;
            
        } while ((answer == 'C' || answer == 'c') && i < MAXENTRY);
        return i;
    }

    /* Array of Objects
     * 
     * declaration  -   myClass arrayOfmyClass[5];
     *
     * access public members    -   arrayOfmyClass[i].increment();
     */

    class myClass
    {
        public:
            char fName[];
            char lName[];
            myClass()
            {
                fName = "alex\0";
                lName = "martin\0";
            }
            void getFirst
            {
                cout << fName << endl;
            }
            void getLast
            {
                cout << lName << endl;
            }
            ~myClass()
            {
                cout << "deleted " << endl;
            }
    };

    int main() {

        myClass arrayOfmyClass[5];

        for( int i = 0; i < 5; i++)
        {
            cout << arrayOfmyClass[i].getFirst() << " " 
                 << arrayOfmyClass[i].getLast() << endl;
        }
    }


//[strings]

    /* C Style Strings
     * string - a character array that is terminated by a null char '\0'
     *          a '\0' is necessary, so the array must be one larger than the 
     *          largest string it will hold
     * string literal - characters enclosed in "" 
     */

    char myStr[10] = "C++ Rocks";
    char myStr[]   = {'C','+','+',' ','R','o','c','k','s'};
    char myStr[10] = {‘C’,’+’,’+’, ‘ ‘, ‘R’, ‘o’, ‘c’, ‘k’, ‘s’, ‘\0’};

    /* VSC has gets_s() in the <stdio.h>
     * it takes in input till a '\r' is entered and replaces it with a '\0'
     */

    // input -> 1d array
    char str[50];
    cout << "What is your name?" << endl;
    gets_s(str);

    // input -> 2d array
    char myClass[27][100];
    int i;

    cout << "** Class Roster input **" << endl;
    for (i = 0; i < 27; i++)
    {
	    cout << "Please enter name " << i+1 << ":";
	    gets_s(myClass[i]);
    }

    /* String Common Library Functions
     *  (DEPRECIATED) strcpy(to, from) - copy a string from another
     *  (DEPRECIATED) strcat(to, from) - concatenate one string to another
     *  strlen(str) - get the length of a string, not including '\0'
     *  (DEPRECIATED) strcmp(str1, str2) - compare a string w/ another, return 0 if equal
     */

    
//[pointers]

    /* pointers - variables that hold memory addresses of other locations in ram
     * declaration:
     *  <type> *<variable name>
     *
     * & - address of (reference) operator
     * * - value at the address {indirection, de-referencer} operator
     */

    int *ptr;
    int k = 5;

    ptr = &k;

    /* Pointer Arithmetic
     *
     * Compiler changes (<ptr name> + 1) to (<ptr name> + (1 * sizeof(<data type>))
     * if ptr was an integer of size()=4, then the next integer will be 4 memory
     * blocks away
     */


    /* Arrarys and Pointers
     *
     * the array name itself is a pointer to the first memory location in the 
     * array, the difference between the name of an array and a pointer is
     * that array names are constant pointers
     *
     * int array[]   = {1,23,4,5,-100};
     *  array[1]    == 23
     *  *(array+1)  == 23
     *  *array + 1  == 2
     *  array[3]     = 5
     *  *(array+3)  == 5
     *  *array + 3  == 4
     */
      

//[functions]

    /* <return type> <function name> ( <paramater list> )
     * {
     *      body 
     *      return value;
     * }
     * Return Type   : The return_type is the data type of the value the function
     *                 returns. Some functions perform the desired operations 
     *                 without returning a value. In this case, the return_type is 
     *                 the keyword void.
     * Function Name : This is the actual name of the function. The function name 
     *                 and the parameter list together constitute the function 
     *                 signature.
     * Parameter List: list of variables that are passed to the function
     * Funciton body : collection of statements that define what the function 
     *                 does
     *
     * Function Prototype - declared at the begining of the program
     *    int sum( int a, int b );
     */
    
    int sum( int a, int b);

    int sum( int a, int b )
    {
        return a + b;
    }


    /* Call Types
     *
     * value     -   This method copies the actual value of an argument into the 
     *               formal parameter of the function. In this case, changes made
     *               to the parameter inside the function have no effect on the 
     *               argument
     * pointer   -   This method copies the address of an argument into the formal
     *               parameter. Inside the function, the address is used to access 
     *               the actual argument used in the call. This means that changes 
     *               made to the parameter affect the argument
     * reference -   This method copies the reference of an argument into the 
     *               formal parameter. Inside the function, the reference is 
     *               used to access the actual argument used in the call. This 
     *               means that changes made to the parameter affect the argument
     */

    // call by value
    void getDemensions( int l, int w );

    // call by pointer
    void getDemensions( int &l, int &w );

    // call by reference
    void getDemensions( int *l, int *w ); 


    /* Overloading
     *
     * functions can have the same name as long as the parameters are different
     * function overloading is used to represent real-world objects in programming
     * it allows sets of functions to be accessed using a common name and is one
     * way c++ achieves polymorphism
     */

    int myFunc( int a, int b, int c )
    {
        return a + b + c;
    }

    int myFunc ( double a, double b )
    {
        return a * b;
    }
    {

    /* Overloading and Ambiguity
     *
     * In some situations the compiler is unable to choose between two or more 
     * correctly overloaded functions.  This is due to C++’s automatic type 
     * conversions. C++ automatically attempts to convert the type of arguments 
     * used to call a function into the type of parameters defined by the 
     * function, sometimes causing ambiguity.
     */


//[variable scope]

    /* storage classes can be permanent or temporary
     * global variables are permanent and don't fall out of scope
     * local variables are temporary and fall out of scope unless they are 
     * declared as static, in which case they become permanent
     */

    int ERROR_COUNT = 0;

    int main()
    {
        static char[500] errorMsg;
        int a = 1;

        try
        { 
            a = (a/0);
        }
        catch
        {
            errorMsg = "Can not divide by 0!";
            ERROR_COUNT++;
        }
    }


//[main()]

    /* Arguments to main()
     *
     * General convention is to use argc and argv parameters
     *
     * int argc     -   holds the number of arguments on the command line. #1 is 
     *                  the program name
     * char *argv[] -   a pointer to an array of character pointers where each 
     *                  pointer in the array points to a string containing the
     *                  command line arguments
     */

    int main ( int argc, char *argv[] )
    {
        if( argc < 2 )
        {
            cout << "Error! your forgot a cli variable!" << endl;
            return 1;
        }
        else
            return 0;
    }


//[class, object]

    /* class    -   expanded concept of data structures. Like data structures, 
     *              they can contian functions as members
     * object   -   an instantiation of a class. In terms of variables, a class
     *              would be the type, and an object would be the variable
     *
     * class <class name>
     * {
     *     <access specifier>:
     *         member1;
     *     <access specifier 2>:
     *         member2;
     * };
     *
     * members  -   can be either data or function declarations and optionally
     *              access specifiers
     * access specifier -   The {private,public,protected} specifiers modify
     *                      the access rights for the members that follow them
     * private          -   members of a class are accessible only from within
     *                      other members of the same class
     * protected        -   members are accessible from other members of the 
     *                      same class, but also from members of their derived
     *                      classes
     * public           -   members are accessible from anywhere the object is 
     *                      visible
     */

    class foo
    {
        private:
            int data;
        public:
            void memfunc ( int d )
            {
                data = d;
            }
    };
             
    class smallObject
    {
        int data1;
        double data2;
        public:
            // member function to set data
            void setData(int d1, double d2)
            {
                data1 = d1;
                data2 = d2;
            };

            // member function to display data
            void displayData()
            {
                cout << data1 << endl;
                cout << data2 << endl;
            };
     };

    int main()
    {
        smallObject myObject;  // declare object
        myObject.setData(123, 56700);  // call member function to set data
        myObject.displayData();   // call member function to display data

        return 0;
    }

    /* Constructors and Destructors
     *
     * constructor  -   a special member function that is executed automatically
     *                  whenever an object is created. Its purpose is autmatic
     *                  initalization.
     *
     *                  1. it has the same name as the class
     *                  2. no return type for constructors
     *                  3. can be overloaded
     *                  4. may or may not have arguments
     *
     * destructor   -   a special member function that is executed automatically
     *                  whenever an object is destroyed
     *
     *                  1. same name as the class w/ a ~ prefix ( ~myClass() )
     *                  2. has no return type
     *                  3. commonly used to deallocate memory that was allocated
     *                     by the constructor
     *                  4. takes no arguments
     */

    class Counter
    {
        private:
            int count;

        public:
            counter()
            {
                count = 0;
            }
            void increment()
            {
                count++
            }
            void getCount()
            {
                return count;
            }
            ~counter()
            {
                cout << "destroying.." << endl;
            }
    };

    int main()
    {
        counter a, b;
        a.increment();
        a.increment();
        b.increment();
        cout << a.getCount() << " " << b.getCount() << endl;

        return 0;
    }

    // or you can declare your variables outside of the class
    
    class Counter
    {
        private:
            int count;
        public:
            counter();
            void increment();
            int getCount();
            ~counter();
    };

    counter::counter()
    {
        count = 0;
    }
    // overloaded constructor
    counter::counter(int value)
    {
        count = c;
    }
    void counter::increment()
    {
        count++;
    }
    int counter::getCount()
    {
        return count;
    }
    counter::~counter()
    {
        cout << "destroying.." << endl;
    }

    int main()
    {
        counter a, b;
        a.increment();
        a.increment();
        b.increment();
        cout << a.getCount() << " " << b.getCount() << endl;

        return 0;
    }
    

