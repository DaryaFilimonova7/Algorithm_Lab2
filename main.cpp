#include "header.h"

/* Прочитайте постфиксное выражение слева направо.
 * Когда вы читаете число, положите его в стопку. Когда вы читаете операнд,
 * извлеките из стека два верхних числа, примените к ним оператор
 * и поместите результат на вершину стека. В конце результат
 * выражения должен быть единственным числом в стеке.
 * */

class Stack {
public:
    List stack;  // стек как экземпляр списка
    int size = 0;
    void push(int x) {
        stack.add_first(x);
        size++;
    }
    Node* top() {
        return stack.search_position(0);
    }
    void pop() {
        stack.delete_position(0);
        size--;
    }
};

class Calculator
{
public:
    int calc(std::string);

};

int Calculator :: calc(std::string expr) {
    Stack calc_stack;  // стек как экземпляр списка
    int len = expr.length();
    for (int i = 0; i < len; i++) {
        if (expr[i] == ' ') {
            continue;
        }
            // считывание операнда до пробела
        else if (isdigit(expr[i])) {
            int x = 0;
            while (isdigit(expr[i])) {
                x = x * 10 + (int)(expr[i] - '0'); // (int) приведение к типу int, - '0' convert from char to int
                i++;
            }
            i--; // возврат к концу числа
            calc_stack.push(x);
        }
            // считывание оператора
        else {
            // извлечение 2-х верхних чисел из стека
            int a = calc_stack.top()->data;
            calc_stack.pop();
            int b = 0;
            bool pos = false;
            if (calc_stack.size != 0) {
                b = calc_stack.top()->data;
                calc_stack.pop();
                pos = true;
            }

            if (expr[i] == '+') {
                calc_stack.push(a+b);
            }
            else if (expr[i] == '-') {
                if (!pos) {
                    // для случая, если первое число в выражении - отрицательное
                    calc_stack.push(0-a);
                }
                else {
                    // отрицательные числа в выражении
                    if (expr[i+1]== '+' || expr[i+1]=='-' || expr[i+1]=='/' || expr[i+1]=='*') {
                        calc_stack.push(a);
                        calc_stack.push(0-b);
                    }
                    else {
                        calc_stack.push(b-a);
                    }
                }
            }
            else if (expr[i] == '*') {
                calc_stack.push(a*b);
            }
            else if (expr[i] == '/') {
                calc_stack.push(b/a);
            }
        }

    }
    // Результат - единственное оставшееся число в стеке
    if (calc_stack.size == 1) {
        return calc_stack.top()->data;
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
