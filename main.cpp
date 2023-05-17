#include "header.h"

class Calculator
{
    List calc_stack;  // стек как экземпляр списка
public:
    int calc(std::string);
};

int Calculator :: calc(std::string expr) {
    int len = expr.length();
    for (int i = 0; i < len; i++) {
        if (expr[i] == ' ') {
            continue;
        }
            // считывание операнда до пробела
        else if (isdigit(expr[i])) {
            int x = 0;
            while (isdigit(expr[i])) {
                x = x * 10 + (int)(expr[i] - '0'); // (int) приведение к типу int
                // - '0' convert from char to int
                i++;
            }
            i--; // возврат к оператору
            calc_stack.add_first(x);
        }
            // считывание оператора
        else {
            int a = calc_stack.search_position(0)->data;
            calc_stack.delete_position(0);
            int b = 0;
            if (calc_stack.search_position(0) != nullptr) {
                b = calc_stack.search_position(0)->data;
                calc_stack.delete_position(0);
            }

            if (expr[i] == '+') {
                calc_stack.add_first(a+b);
            }
            else if (expr[i] == '-') {
                if (calc_stack.search_position(0) == nullptr) {
                    calc_stack.add_first(0-a);
                }
                else {
                    calc_stack.add_first(b-a);
                }
            }
            else if (expr[i] == '*') {
                calc_stack.add_first(a*b);
            }
            else if (expr[i] == '/') {
                calc_stack.add_first(b/a);
            }
        }

    }
    if (calc_stack.search_position(1) == nullptr) {
        return calc_stack.search_position(0)->data;
    }
    else {
        std::cout << "Incorrect expression. ";
        return 0;
    }
}

int main() {

    Calculator calculator;

    bool correct;
    std::string expr;
    while (expr != "s") {
        correct = true;
        std::cout << "\n Enter the expression \n or enter 's' to stop " << std::endl;
        std::getline(std::cin, expr);

        for (char i : expr) { // идем по символам
            if ((i >= 'A' && i <= 'Z' || i >= 'a' && i <= 'z') && expr != "s") {
                std::cout << "Incorrect input" << std::endl;
                correct = false;
                break;
            }
        }

        if (expr != "s" && correct) {
            std::cout << calculator.calc(expr);
            std::cout << std::endl;
        }
    }

    return 0;
}
