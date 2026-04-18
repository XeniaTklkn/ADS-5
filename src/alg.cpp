// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

namespace {
int priority(char op) {
    switch (op) {
        case '(': return 0;
        case ')': return 1;
        case '+': case '-': return 2;
        case '*': case '/': return 3;
        default: return -1;
    }
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
} // namespace

std::string infx2pstfx(const std::string& inf) {
    std::string post;
    TStack<char, 100> stack;

    for (size_t i = 0; i < inf.length(); ++i) {
        char ch = inf[i];
        if (std::isspace(ch)) continue;

        if (std::isdigit(ch)) {
            while (i < inf.length() && std::isdigit(inf[i])) {
                post += inf[i];
                ++i;
            }
            post += ' ';
            --i;
            continue;
        }

        if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                post += stack.get();
                post += ' ';
                stack.pop();
            }
            if (!stack.isEmpty() && stack.get() == '(') {
                stack.pop();
            }
        } else if (isOperator(ch)) {
            int currPrior = priority(ch);
            while (!stack.isEmpty() && isOperator(stack.get()) &&
                   priority(stack.get()) >= currPrior) {
                post += stack.get();
                post += ' ';
                stack.pop();
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        post += stack.get();
        post += ' ';
        stack.pop();
    }

    if (!post.empty() && post.back() == ' ') {
        post.pop_back();
    }

    return post;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token.length() > 1 &&
            token[0] == '-' && std::isdigit(token[1]))) {
            stack.push(std::stoi(token));
        } else if (token.length() == 1 && isOperator(token[0])) {
            int op2 = stack.get(); stack.pop();
            int op1 = stack.get(); stack.pop();
            int result = 0;
            switch (token[0]) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
            }
            stack.push(result);
        }
    }

    return stack.get();
}
