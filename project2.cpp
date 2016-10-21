#include<sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <math.h> 
#include <string>
#include <queue>
#include <deque>
//Defining constants
#define Pi 3.14169
#define e  2.718

using namespace std;

void shantin_yard(string expression);

double add_nums (deque <string> &result,char ch);

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
    deque <string> result;
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
            result.push_back(num);//Push number into queue after it has been read
       
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
                        //char temp = operators.top();
                        //stringstream strs;
                        //string char_string;
                        //        //int n = 1;
                        //strs << temp ;
                        //strs >> char_string;
                        //result.push_back(char_string);
                        result.push_back(to_string(add_nums(result,operators.top())));
                        operators.pop();
                    }
                    operators.pop();//Remove the ( so that it doesn't stay in our result
                
                }
                else
                
                {
                    while(!operators.empty() && precedence.at(operators.top()) >= precedence.at(expression[i]))
                    
                    {
                        //Push operator to result queue, pop it from stack and add new operator to stack
                        //char temp = operators.top();
                        //stringstream strs;
                        //string char_string;
                        //        //int n = 1;
                        //strs << temp ;
                        //strs >> char_string;
                        //result.push_back(char_string);

                        result.push_back(to_string(add_nums(result,operators.top())));
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
            
      // char temp = operators.top();
      // stringstream strs;
      // string char_string;
      // strs << temp ;
      // strs >> char_string;
      // result.push_back(char_string);
       
       result.push_back(to_string(add_nums(result,operators.top())));
       operators.pop();
    
    }
    while(!result.empty())
    {
    
        cout<<result.front()<<endl;
        result.pop_front();
    }

}

double add_nums (deque <string> &result,char ch)
{
    double temp_num1 = stod(result.back());
    result.pop_back();
    double temp_num2 = stod(result.back());
    result.pop_back();
    
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









