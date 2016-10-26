#include<sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <math.h> 
#include <string>
//Defining constants
#define Pi 3.14169
#define e  2.718

using namespace std;

void shantin_yard(string expression);

double add_nums (stack <string> &result,char ch);

unordered_map <string,double> vars;
int main ()
{

    string calc;
    cin>>calc;
    shantin_yard(calc);


    return 0;
}


//Take in a string with numbers and operations and return the calculation ex: 5+2-6 = 1

void shantin_yard(string expression)
{
    stack <char> operators;
    stack <string> result;
    unordered_map <char, int> precedence;
    double temp_num;
    //Set precedense operators this way we know which operations to pass to the stacj result
    precedence.insert({'(',-1}); 
    precedence.insert({')',-1}); 
    precedence.insert({'+',1}); 
    precedence.insert({'-',1});
    precedence.insert({'*',2});
    precedence.insert({'/',2});
    precedence.insert({'^',3});
    //Start cheching mathematical expression
    for (int i = 0; i < expression.length();i++)
    {
        //If it's a number make sure to take in all digits of the number ex:1 is diff than 100, for 100 we have to loop and look at the nums
        if(isdigit(expression[i]))
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
            result.push(num);//Push number into queue after it has been read
       
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
                    //Handle the order of operations whne we se a parenthesis
                    while(operators.top() != '(')
                    {
                               
                        
                        //Push operator to result queue, pop it from stack and add new operator to stack
                        result.push(to_string(add_nums(result,operators.top())));
                        operators.pop();
                    }
                    operators.pop();//Remove the ( so that it doesn't stay in our result
                
                }
                else
                
                {
                    while(!operators.empty() && precedence.at(operators.top()) >= precedence.at(expression[i]))
                    
                    {

                        result.push(to_string(add_nums(result,operators.top())));
                        operators.pop();

                    
                    }

                    operators.push(expression[i]); // push in new expression
                }
            }
        
        }

        
    
    
    }
    //push all remaining elements in the stack to our result queue 

    while(!operators.empty())
    {
       result.push(to_string(add_nums(result,operators.top())));
       operators.pop();
    
    }
    while(!result.empty())
    {
    
        cout<<result.top()<<endl;
        result.pop();
    }

}

double add_nums (stack <string> &result,char ch)
{
    double temp_num1 = stod(result.top());
    result.pop();
    double temp_num2 = stod(result.top());
    result.pop();
    
    if(ch == '+')
    {
       return  temp_num2 + temp_num1;
    }

    else if (ch == '-')
    {
       return  temp_num2 - temp_num1;
    }

    else if (ch == '*')
    {
       return  temp_num2 * temp_num1;
    }

    else if (ch == '/')
    {
       return  temp_num2/temp_num1;
    }
    else
    {
        return pow(temp_num2,temp_num1);
    }

}

void save_var (string var_name,double var_num) 

{
    vars.insert({var_name,var_num});


}

void check_var(string expr)//Take in expression and determine if it's setting a value to a variable or just evaluating an expression
{
    string val;//used ,to check if string is "let" or just a variable name or sin cos etc;
    for(int i = 0; i<expr.size();i++)
    {
        
        while(isalpha(expr[i]))
        {
            val+=       
        
        }
    
    }

}



