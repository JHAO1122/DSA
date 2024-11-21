# include<iostream>
# include"expression_evaluator.h"
int main(){
    for(int i = 0; i < 10; i++){
    std::string expression;
    std::cout << "Please put a string as a test" << i+1 << std::endl;
    std::getline(std::cin, expression);
    transfer needchanged(expression);
    if(needchanged.islegal()){
    std::string changed_expression = needchanged.change();
    std::cout << "after transfering:" << std::endl;
    std::cout << changed_expression << std::endl;
    std::string transferexpr = changed_expression;
    solution trans(transferexpr);
    double result = trans.evaluator();
    std::cout << "the result of" << i+1  << std::endl; 
    std::cout << result <<std::endl;
    }else{
        std::cout << "ILLEGAL" << std::endl;
    }
    }
    return 0; 
}
