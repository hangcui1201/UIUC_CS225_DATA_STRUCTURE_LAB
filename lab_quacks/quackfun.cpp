/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{

    // Your code here
    // stub return value (0 for primitive types). Change this!
    // Note: T() is the default value for objects, and 0 for
    // primitive types

    if(s.size() == 0){
        return T();
    }
    else{
        T add = s.top();          // get top value of stack
        s.pop();                  // delete top value of stack
        T value = add + sum(s); // recursively add top value with next reference of stack
        s.push(add);
        return value;             // stub return
    }
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    stack<char> s;

    while (!input.empty())
    {
        // Get first char of the queue and pop()
        char first_char = input.front();
        input.pop();

        if(first_char == '['){

            s.push(first_char);

        } else {

            if(first_char != ']'){
                continue; // the char is neither '[' or ']'
            } 

            if(s.empty()){
                return false;
            } 
            
            if(first_char == ']'){
                s.pop();
            }

        }

    }

    return s.empty();
    
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;

    // optional: queue<T> q2;
    // Your code here

    unsigned long a = 0;
    T temp;

    while ((a+1)*a/2 < q.size())
    {
        a++;
    }

    int c = a-1;
    int d = ((c+1)*c)/2;
    int b = q.size() - d;

    for (int i=1; i<=c; i++)
    {
        if (i%2 == 0)
        {
            for (int j=0; j<i; j++)
            {   
                temp = q.front();
                q.pop();
                s.push(temp);
            }

            for (int j=0; j<i; j++)
            {
                temp = s.top();
                s.pop();
                q.push(temp);
            }
        }

        if (i%2 != 0)
        {
            for (int j=0; j<i; j++)
            {
                temp = q.front();
                q.pop();
                q.push(temp);
            }
        }
    }

    if (a%2 == 0)
    {
        for (int i=0; i<b; i++)
        {   
            temp = q.front();
            q.pop();
            s.push(temp);
        }

        for (int i=0; i<b; i++)
        {
            temp = s.top();
            s.pop();
            q.push(temp);
        }
    }

    if (a%2 != 0)
    {
        for (int i=0; i<b; i++)
        {
            temp = q.front();
            q.pop();
            q.push(temp);
        }
    }

}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    // T temp1; // rename me
    // T temp2; // rename :)

    // Your code here
    T temp_s; //local variable
    T temp_q; //local variable

    if (s.empty())//check if the stack is empty, this is the base case for recursion, return true if the stack if empty
        return true;//return true
        //we won't check the queue because queue will never be empty. the value pop will be immediately push back.
    else//if stack if not empty, using recursion to compare the queue and stack.
    {

        temp_s = s.top();//let local variable temp_s be the value of top of stack
        s.pop();//move the pointer
        //cout<<temp_s<<endl;

        retval = retval && verifySame(s,q);//using recursion to pop all stack value
        
        s.push(temp_s);//push the element from last to first
        //we need to comparethe last of stack to the first of queue, so the queue will in recursion but the stack won't.
        temp_q = q.front();//let the local variable to be the front of stack, it will compare the first of queue with the last of stack
        q.pop();//move the pointer
        q.push(temp_q);//push back
        //cout<<temp_q<<endl;
        //cout<<retval<<endl;       

        if (temp_s == temp_q && retval == true)//if the previous are ture and the current is ture
            retval = true;//the retval will still be true
        else//if the current is not ture
            retval =  false;//return false and stop recrusion
        
        //cout<<retval<<endl;
        //cout<<temp_s<<endl;
        return retval;
    }    // optional

}


}
