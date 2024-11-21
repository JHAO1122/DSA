# include<iostream>
# include<stack>
# include<string>
# include<cctype>

class transfer //中缀表达式转换为后缀表达式的类
{
private:
    std::string expression;
public:
    transfer(const std::string & _expression):expression(_expression){};
        bool isoperator(char a){
        if(a == '+'||a == '-'||a == '*'||a == '/')
        return 1;
        else {return 0;}
    }//判断是否为运算符
    int operatorrank(char a){
        if(a == '+'||a == '-') 
        return 1;
        else if (a == '*'||a == '/')
        return 2;
        return 0;       
    }//比较运算符优先级
    int count(char a,int k){
       int num = 0;
       for(int i=0; i <= k && i < expression.length(); i++)
       {
        if(expression[i] == a) num++;
       } 
       return num;
    }  //一个计算运算符数量的函数 
    bool islegal()
    {
        int size = expression.length();
        for(int j = 0; j < expression.length()-1; j++)
        {
            if(isoperator(expression[j]) && isoperator(expression[j+1]) && expression[j+1] != '-') //如果运算符连续使用 
            return 0;
            else if(expression[j] == '(' && isoperator(expression[j+1]) && expression[j+1] != '-') //如果左括号后面是运算符
            return 0;
            else if(isoperator(expression[j]) && expression[j+1] == ')') //如果右括号的前面是运算符
            return 0;
            else if(isdigit(expression[j]) && expression[j+1] == '(') //如果左括号的前面是数字
            return 0;
            else if(expression[j] == ')' && isdigit(expression[j+1])) //如果右括号的后面是数字
            return 0;
            else if(expression[j] == '(' && expression[j+1] == ')')//如果左右括号相邻
            return 0;
            else if(count('(', j) < count(')', j)) return 0; //如果左括号数量小于右括号数量
            else if(expression[j] == '/' && isdigit(expression[j+1])){
                char divisor = expression[j+1];
                if(divisor == '0') return 0;
            }
        }        
        if(isoperator(expression[size-1]) || (isoperator(expression[0]) && expression[0] != '-'))//如果字符串以操作符开头或者结尾
        {return 0;}
        else if(count(')', size-1) != count('(', size-1))//如果左右括号数量不一致
        {return 0;}
        return 1;
    }
    std::string change()
    {
        std::stack<char> operatorstack;//装载运算符的栈
        std::string changed;//输出的字符串
        for(int i = 0; i < expression.length(); i++){
        char ch = expression[i];
        if(ch == ' ') continue;//如果输入的是空格，直接跳过
        if(std::isdigit(ch)){
            while(i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.' || expression[i] == 'e' 
            || (expression[i] == '-' && expression[i-1] == 'e'))){
            changed += expression[i];//如果输入的是数字，直接放入后缀表达式中，此时考虑有限位小数和科学计数法
            i++;
            }
            i--;
            changed += ' ';//用空格隔开
        }
        else if(ch == '(' && expression[i+1] != '-'){
            operatorstack.push(ch);
        }//如果是左括号，则直接将左括号放入运算符栈中
        else if(ch == '(' && expression[i+1] == '-'){
            operatorstack.push(ch);
            changed += '-';
            i++;
        }//如果左括号后面是减号，当作负数处理
        else if(ch == ')'){
            while(!operatorstack.empty()  && operatorstack.top()!= '(')
            {
                changed += operatorstack.top();
                changed += ' ';
                operatorstack.pop();//如果是右括号，则将运算符栈中的运算符输出直到遇到左括号
            }
                operatorstack.pop();//左括号直接出栈
        }
        else if(expression[i] == '-' && i == 0){
            changed += '-';
        }
        else if(isoperator(ch) && expression[i+1] != '-'){
            while(!operatorstack.empty() && operatorrank(ch) <= operatorrank(operatorstack.top()))//如果操作符栈不为空然后比较和栈顶操作符的优先级
            {
                changed += operatorstack.top();
                changed += ' ';
                operatorstack.pop();//如果优先级小于等于栈顶操作符优先级，则弹出栈顶操作符
            }
            operatorstack.push(ch);//将操作符压入栈中
        }
        else if(isoperator(ch)  && expression[i+1] == '-'){
            while(!operatorstack.empty() && operatorrank(ch) <= operatorrank(operatorstack.top()))
            {
                changed + operatorstack.top();
                changed += ' ';
                operatorstack.pop();
            }
            operatorstack.push(ch);
            changed += '-';
            i++;
        }//如果运算符后面有负号，则将运算符压入栈后直接把符号放在后缀表达式中并跳过处理减号
    }
        while(!operatorstack.empty()){
            changed += operatorstack.top();
            changed += ' ';
            operatorstack.pop(); 
        }  
        return changed;//返回后缀表达式      
    }
};
class solution//计算后缀表达式的类
{
    private:
    std::string transferexpr;
    public:
    solution(const std::string & transfer_expr):transferexpr(transfer_expr){};
    bool isoperator(char a){
        if(a == '+'||a == '-'||a == '*'||a == '/')
        return 1;
        else {return 0;}
    }
    double evaluator(){
    std::stack<double> evaluatorstack;
    for(int i = 0; i < transferexpr.length(); i++)
    {
        char ch = transferexpr[i];
        if(isdigit(ch) || (ch == '-' && transferexpr[i+1] != ' ')){//在此处考虑负数
            std::string number;
            while(transferexpr[i] != ' ')
            {
                number += transferexpr[i];
                i++;
            }
            double num = stod(number);
            evaluatorstack.push(num);//计算后缀表达式，如果是数字直接压入栈中
        }
        if(ch == ' '){;}
        if(isoperator(ch) && transferexpr[i+1] == ' '){
            double num1 = evaluatorstack.top();
            evaluatorstack.pop();
            double num2 = evaluatorstack.top();
            evaluatorstack.pop();//将栈顶的两个数字弹出
            double num = 0;
            switch(ch){
                case '+': num = num2+num1;break;
                case '-': num = num2-num1;break;
                case '*': num = num2*num1;break;
                case '/': num = num2/num1;break;
            }
            evaluatorstack.push(num);//将计算后的结果压入栈中
        }
    }
    return evaluatorstack.top();//最后栈中存留的数字即为结果
    }
};
