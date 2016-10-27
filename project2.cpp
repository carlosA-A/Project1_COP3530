#include<sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <math.h> 
#include <string>

using namespace std;


static unordered_map <string,double> vars;

double shantin_yard(string expression);
double add_nums (stack <string> &result,char ch);
void check_var(string expr);
string get_word(int &i, string &expr );
double get_var(string var_name);

double eval_func(stack <string> &result,char ch);
int main ()
{

    vars.insert({"Pi",3.14169});
    vars.insert({"e", 2.718});
    string calc;

    while (calc != "exit")
    {

        getline (std::cin,calc);


        //shantin_yard(calc);
        check_var(calc);


    }

    return 0;
}


//Take in a string with numbers and operations and return the calculation ex: 5+2-6 = 1

double shantin_yard(string expression)
{

    stack <char> operators;
    stack <string> result;
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
                cout<< "WORKS FOR SIN  "<<expression[i]<<endl;
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
                if (var_val == -1)
                {

                    return -1;
                }
                else
                {
                    result.push(to_string(var_val));   

                }



            }
        }

        //If it's a number make sure to take in all digits of the number ex:1 is diff than 100, for 100 we have to loop and look at the nums
        else if(isdigit(expression[i]))
        {
            cout<<"IS digit executes"<<endl;
            string num=""; //New number will be created after every loop

            while(isdigit(expression[i]))//Grab the whole number 
            {

                cout<<"add number"<<endl;
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

            cout<<"expression executes"<<endl;
            if (operators.empty()) //If stack with operators is empty then push operator into stack, no need to compare
            {
                cout<<"empty stack"<<endl;

                operators.push(expression[i]);
            }
            else //Check operator precenece, if the previous one is higher or equal than the new one then pop it from the stack and put it in the result queue 
            {

                if (expression[i] == '(')
                {
                    cout<<"pushing ( to stack"<<endl;
                    operators.push(expression[i]);

                }
                else if (expression[i] == ')')
                {
                    cout<<"pushing operators to stack"<<endl;
                    //Handle the order of operations when we see a parenthesis
                    while(operators.top() != '(')
                    {


                        if(operators.top() == 's' ||operators.top() == 'c' ||operators.top() == 'l' )
                        {
                            cout<<"sin eval"<<endl;
                            result.push(to_string(eval_func(result,operators.top())));
                            operators.pop();

                        }
                        else
                        {

                            cout<<"calculation eval"<<endl;
                            result.push(to_string(add_nums(result,operators.top())));
                            operators.pop();
                        }
                    }
                    operators.pop();//Remove the ( so that it doesn't stay in our result

                }
                else

                {
                    cout<<"Check precedence "<<endl;
                    while(!operators.empty() && precedence.at(operators.top()) >= precedence.at(expression[i]))

                    {
                        if(operators.top() == 's' ||operators.top() == 'c' ||operators.top() == 'l' )
                        {
                            cout<<"sin eval"<<endl;
                            result.push(to_string(eval_func(result,operators.top())));
                            operators.pop();

                        }
                        else
                        {

                            cout<<"calculation eval"<<endl;
                            result.push(to_string(add_nums(result,operators.top())));
                            operators.pop();
                        }


                    }

                    operators.push(expression[i]); // push in new expression
                }
            }

        }




    }
    //push all remaining elements in the stack to our result queue 

    while(!operators.empty())
    {
        if(operators.top() == 's' ||operators.top() == 'c' ||operators.top() == 'l' )
        {
            cout<<"sin eval"<<endl;
            result.push(to_string(eval_func(result,operators.top())));
            operators.pop();

        }
        else
        {

            cout<<"calculation eval"<<endl;
            result.push(to_string(add_nums(result,operators.top())));
            operators.pop();
        }

    }
    //cout<<result.top()<<endl;
    double final_result = stod(result.top());
    cout<< final_result;
    return final_result;
    //result.pop();


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

double eval_func(stack <string> &result,char ch)
{

    double temp_num1 = stod(result.top());
    result.pop();

    cout<<"WORKS add_NUMS 3 "<< temp_num1<<endl;
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
void save_var (string var_name,double var_num) 

{
    auto it = vars.find(var_name);

    if(it == vars.end())//check if varialbe is already in hashmap if it's not add it else update the value
    {

        vars.insert({var_name,var_num});

    }
    else
    {
        it->second = var_num;
    }


}

double get_var(string var_name)
{
    auto it = vars.find(var_name);

    if (it == vars.end())//if var is not in map return an error
    {
        cout<<"error"<<endl;
        return -1;

    }
    else//retrieve the value of the varialbe if it's in the map
    {
        return it->second;

    }
}

void check_var(string expr)//Take in expression and determine if it's setting a value to a variable or just evaluating an expression
{
    string var_name;

    string val;//used ,to check if string is "let" or just a variable name or sin cos etc;

    int i = 0;

    cout<<val<<"       "<<endl;

    val = get_word(i,expr);
    if (val == "let") //Get the variable name
    {

        cout<<"works 5"<<endl;
        for(;i<expr.size();i++)
        {

            if(expr[i] == '=')//skip empty spaces
            {

                cout<<"works 2"<<endl;
                break;
            }
            else if(isalpha(expr[i]))
            {
                var_name += expr[i];


                cout<<"works 3"<<endl;
            }

            cout<<"works 6"<<endl;
        }   


        cout<<"works 8"<<endl;
        //create a substring with the expression to be saved in the variable name
        cout<<var_name<<" "<<endl;
        save_var(var_name,shantin_yard(expr.substr(i+2))); 

    }
    else
    {

        cout<<"works 9"<<endl;
        shantin_yard(expr); 

    }

}
//get the word before a space
string get_word(int &i, string &expr )
{
    string val = "";

    bool word_found = false;

    for(; i<expr.size();i++)
    {
        //If we already found the first word the break from the loop since we are only interested in checking if it's a let keyword
        cout<<"works 1"<<endl;
        if (word_found == true && !isalpha(expr[i]) ) //make sure that we are not still grabing the first word
        {

            break;
        }

        else if(expr[i]==' ')
        {

            cout<<"works 54"<<endl;

        }    

        else if(isalpha(expr[i]))
        {
            word_found = true;
            val+=expr[i];

            cout<<"works 3"<<endl;
        }

    }
    return val;

}

