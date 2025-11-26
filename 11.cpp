#include <stack>
 #include <string>
 #include <stdexcept>
 #include <iostream>
 class RPNCalculator {
 private:
     std::stack<double> operands;
 public:
     void add() {
         if (operands.size() < 2) throw std::runtime_error("栈空错误");
         double b = operands.top(); operands.pop();
         double a = operands.top(); operands.pop();
         operands.push(a + b);
     }
     void subtract() {
         if (operands.size() < 2) throw std::runtime_error("栈空错误");
         double b = operands.top(); operands.pop();
         double a = operands.top(); operands.pop();
         operands.push(a - b);
     }
     void multiply() {
         if (operands.size() < 2) throw std::runtime_error("栈空错误");
         double b = operands.top(); operands.pop();
         double a = operands.top(); operands.pop();
         operands.push(a * b);
     }
     void divide() {
         if (operands.size() < 2) throw std::runtime_error("栈空错误");
         double b = operands.top(); operands.pop();
         if (b == 0) throw std::runtime_error("除数为0错误");
         double a = operands.top(); operands.pop();
         operands.push(a / b);
     }
     void pushNumber(double num) {
         operands.push(num);
     }
     void clearStack() {
         while (!operands.empty()) operands.pop();
     }
     void displayStack() {
         std::stack<double> temp = operands;
         std::cout << "当前栈: ";
         while (!temp.empty()) {
             std::cout << temp.top() << " ";
             temp.pop();
         }
         std::cout << std::endl;
     }
     double evaluateRPN(const std::string& expr) {
         clearStack();
         std::string token;
         size_t pos = 0;
         std::string exprCopy = expr;
         while ((pos = exprCopy.find(' ')) != std::string::npos) {
             token = exprCopy.substr(0, pos);
             processToken(token);
             exprCopy = exprCopy.substr(pos + 1);
         }
         processToken(exprCopy);
         if (operands.size() != 1) throw std::runtime_error("输入格式错误");
         return operands.top();
     }
 private:
     void processToken(const std::string& token) {
         if (token == "+") add();
         else if (token == "-") subtract();
         else if (token == "*") multiply();
         else if (token == "/") divide();
         else {
             try {
                 pushNumber(std::stod(token));
             } catch (...) {
                 throw std::runtime_error("输入格式错误 " + token);
             }
         }
     }
 };
int main() {
     RPNCalculator calc;
     std::string input;
     std::cout << "RPN Calculator (type 'quit'  退出, 'clear'  清空栈, 'show'  显示栈):" << std::endl;
     while (true) {
         std::cout << "> ";
         std::getline(std::cin, input);
         if (input == "quit") break;
         else if (input == "clear") calc.clearStack();
         else if (input == "show") calc.displayStack();
         else {
             try {
                 double result = calc.evaluateRPN(input);
                 std::cout << "Result: " << result << std::endl;
             } catch (const std::runtime_error& e) {
                 std::cout << "Error: " << e.what() << std::endl;
             }
         }
     }
     return 0;
 }
