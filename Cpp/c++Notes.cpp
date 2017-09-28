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




