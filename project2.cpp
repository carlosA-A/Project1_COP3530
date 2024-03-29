#include<sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <math.h> 
#include <string>

using namespace std;


unordered_map <string,double> vars;//Hash map to store all of our varialbes

double shantin_yard(string expression,bool & let);//Use to stacks to perform shantin yard algorithem, keep track of if the variable assignment let was used
double add_nums (stack <double> &result,char ch);//do mathematical operations on values in stack
void check_var(string expr);//Determine if we want to set a variable ex: let x = 5+5
string get_word(int &i, string &expr );//extract a word from an expression to either use as a variable or function
double get_var(string var_name);//Get numerical value associated with the varialbe
double eval_func(stack <double> &result,char ch);//calculate value of function like sin cos log
void func_or_num(stack <double> &result,stack <char> &operators);//determine if we are working with +,-,* or functions and do appropriate operations
int main ()
{
    //Add constants that we will use into the hash map
    vars.insert({"Pi",3.14169});
    vars.insert({"e", 2.718});
    string calc;

    while (calc != "quit")
    {
        try
        {
            getline (std::cin,calc);
            if(calc.length() >= 1)
                check_var(calc);
        }
        catch(exception &e)
        {
            return EXIT_SUCCESS;
        }
        catch (const char* msg) 
        {
            cout << msg << endl;
        }

    }

    return 0;
}


//Take in a string with numbers and operations and return the calculation ex: 5+2-6 = 1

double shantin_yard(string expression,bool &let)
{

    stack <char> operators;
    stack <double> result;
    unordered_map <char, int> precedence;
    double temp_num;
    double var_val;//value of var being retrieved
    string var_name = "";
    //Set precedense operators this way we know which operations to pass to the stacj result
    precedence.insert({'(',-1}); 
    precedence.insert({')',-1}); 
    precedence.insert({'+',1}); 
    precedence.insert({'-',1});
    precedence.insert({'*',2});
    precedence.insert({'/',2});
    precedence.insert({'^',3});
    precedence.insert({'s',5});
    precedence.insert({'c',5});
    precedence.insert({'l',5});
    //Start cheching mathematical expression
    for (int i = 0; i < expression.length();i++)
    {
        //check if there is a variable value that must be retrieved

        if(isalpha(expression[i]))
        {

            var_name = get_word(i,expression);


            if(var_name == "sin" ||var_name == "cos" || var_name =="log" )
            {
                if (var_name == "sin")
                    operators.push('s');

                else if(var_name == "cos")
                    operators.push('c');
                else
                    operators.push('l');
            }
            //Value is a variable so retrieve value
            else
            {

                var_val = get_var(var_name);
                result.push(var_val);   



            }
        }

        //If it's a number make sure to take in all digits of the number ex:1 is diff than 100, for 100 we have to loop and look at the nums
        else if(isdigit(expression[i]))
        {
            string num=""; //New number will be created after every loop

            while(isdigit(expression[i]))//Grab the whole number 
            {

                num += expression[i];
                i++;

                if(expression[i] == '.')
                {

                    num += expression[i];
                    i++;
                }

            }
            result.push(stod(num));//Push number into queue after it has been read

        }

        if (expression[i] == '(' ||expression[i] == ')' ||expression[i] == '+' || expression[i] == '-' ||expression[i] == '*' ||expression[i] == '/' ||expression[i] == '^' )//Check for operators
        {

            if (operators.empty()) //If stack with operators is empty then push operator into stack, no need to compare
            {

                operators.push(expression[i]);
            }
            else //Check operator precenece, if the previous one is higher or equal than the new one then pop it from the stack and put it in the result queue 
            {

                if (expression[i] == '(')
                {
                    operators.push(expression[i]);

                }
                else if (expression[i] == ')')
                {
                    //Handle the order of operations when we see a parenthesis
                    while(operators.top() != '(')
                    {

                        //If operation intended is a function then evaluate cos, sin, log on result top which is the result of the expression inside the func ex sin(4+5)
                        //result.top()=9 so we evaluate sin(9)
                        func_or_num(result,operators);
                    }
                    operators.pop();//Remove the ( so that it doesn't stay in our result

                }
                else

                {
                   //compare precedense of operators
                   //if we have multiple ^ then put them on the stack instead sure of poping since it's a special case
                   //2^3^2 = 512 if we didn't account for this exception the result would be 64
                    while(!operators.empty() && precedence.at(operators.top()) >= precedence.at(expression[i]) && !(operators.top() =='^' && expression[i]=='^'))

                    {
                        func_or_num(result,operators);


                    }

                    operators.push(expression[i]); // push in new expression
                }
            }

        }

    }
    //push all remaining elements in the stack to our result queue 

    while(!operators.empty())
    {
        func_or_num(result,operators);

    }
    double final_result = result.top();
    //Only print out if there was a calculation performed not a variable assignment
    if(!let)
    {

        cout<< final_result<<endl;
    }

    return final_result;


}
//evaluate normal expression
double add_nums (stack <double> &result,char ch)
{
    double temp_num1 = result.top();
    result.pop();
    double temp_num2 = result.top();
    result.pop();

    if(ch == '+')
    {
        ////cout<<"ADDITION: "<< temp_num2 + temp_num1<<endl;
        return  temp_num2 + temp_num1;
    }

    else if (ch == '-')
    {
        ////cout<<"SUBSTRACTION: "<< temp_num2 - temp_num1<<endl;
        return  temp_num2 - temp_num1;
    }

    else if (ch == '*')
    {
        ////cout<<"MULT: "<< temp_num2 * temp_num1<<endl;
        return  temp_num2 * temp_num1;
    }

    else if (ch == '/')
    {
        ////cout<<"DIVISION: "<< temp_num2 / temp_num1<<endl;
        if(temp_num1==0)
        {
            throw "Division-By-Zero";
        }
        return  temp_num2/temp_num1;
    }
    else if (ch == '^')
    {
        ////cout<<"EXPNT: "<< pow(temp_num2,temp_num1)<<endl;
        return pow(temp_num2,temp_num1);
    }

}
//Calculate values of functions sin(90) sin(x+2*2), shantin_yard calculates the result and stores it at the top of the result stack so no matter how big the expression
//inside eval the final result will be on top of stack
double eval_func(stack <double> &result,char ch)
{

    double temp_num1 = result.top();
    result.pop();

    if (ch == 's')
    {
        return sin(temp_num1);
    }

    else if (ch == 'c')
    {
        return cos(temp_num1);
    }
    else if (ch == 'l')
    {
        return log(temp_num1);
    }


}
//save a var and value into a map
void save_var (string var_name,double var_num) 

{
    auto it = vars.find(var_name);//check if variable already exists
    //find returns an iterator to the end of the map
    if(it == vars.end())//check if varialbe is already in hashmap if it's not add it else update the value
    {
        //cout<<"VAR_NAME: "<<var_name<<"\n"<<"VAR_NUM: "<<var_num<<endl;
        vars.insert({var_name,var_num});

    }
    else//updates value of varialbe in map
    {
        it->second = var_num;
    }


}
//get the value associated with a variable
double get_var(string var_name)
{
    auto it = vars.find(var_name);

    if (it == vars.end())//if var is not in map return an error
    {
        if(var_name == "quit")//Throw and exception if the user types quit that will terminate the program
            throw std::exception();

        throw "Undeclared-Variable";

    }
    else//retrieve the value of the varialbe if it's in the map
    {
        return it->second;

    }
}

void check_var(string expr)//Take in expression and determine if it's setting a value to a variable or just evaluating an expression
{
    bool let = false;
    string var_name;

    string val;//used ,to check if string is "let" or just a variable name or sin  etc;

    int i = 0;
    
    val = get_word(i,expr);
    //cout<<"AFTER GET WORD: "<<val<<endl;
    if (val == "let") //Get the variable name
    {   
        let = true; // tell program that there was a let found, use this to know not to print out the value of the result

        for(;i<expr.size();i++)
        {

            if(expr[i] == '=')//stop when we see = let var = 5,stops at =
            {

                break;
            }
            else if(isalpha(expr[i])) //concatnate variable
            {
                var_name += expr[i];


            }

        }   
        //cout<<"VAR_NAME: "<<var_name<<endl;

        //create a substring with the expression to be saved in the variable name
        save_var(var_name,shantin_yard(expr.substr(i+1),let)); 

    }
    else
    {

        shantin_yard(expr,let); 

    }

}
//get the word before a space
string get_word(int &i, string &expr )
{
    string val = "";

    bool word_found = false;
    //cout<<"GET word: "<<expr<<endl;
    for(; i<expr.size();i++)
    {
        //If we already found the first word the break from the loop since we are only interested in checking if it's a let keyword
        if (word_found == true && !isalpha(expr[i]) ) //make sure that we are not still grabing the first word
        {

            break;
        }

        else if(expr[i]==' ')//Ignore whitespace
        {


        }    

        else if(isalpha(expr[i]))
        {
            //cout<<"FOUND CHAR: "<<expr[i]<<endl;
            word_found = true;
            val+=expr[i];

        }

    }
    return val;

}
//Determine if we are using functions, if so then operate on them using eval_func, else evaluate normal expressions 
void func_or_num(stack <double> &result,stack <char> &operators)
{


    if(operators.top() == 's' ||operators.top() == 'c' ||operators.top() == 'l' )
    {
        result.push(eval_func(result,operators.top()));
        operators.pop();

    }
    else
    {

        result.push(add_nums(result,operators.top()));
        operators.pop();
    }

}
