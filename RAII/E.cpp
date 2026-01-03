#include <iostream>
#include <memory>
#include <string>

class Expression {
public:
    virtual int Evaluate() const = 0;
    virtual std::string ToString() const = 0;
    virtual ~Expression() {}
};

class Const_Expr : public Expression {
private:
    const int value;
public:
    Const_Expr(const int value = 0):
        value(value){};

    int Evaluate() const override {
        return this->value;
    }
    std::string ToString() const override {
        return std::to_string(this->value);
    }

    ~Const_Expr() = default;
};

class Sum_Expr : public Expression {
private:
    const std::shared_ptr<Expression> left_expr;
    const std::shared_ptr<Expression> right_expr;
public:
    Sum_Expr(const std::shared_ptr<Expression>& left_expr, const std::shared_ptr<Expression>& right_expr):
        left_expr(left_expr),
        right_expr(right_expr){};
    
    int Evaluate() const override {
        return left_expr->Evaluate() + right_expr->Evaluate();
    }

    std::string ToString() const override {
        return left_expr->ToString().append(" + ").append(right_expr->ToString());
    }

    ~Sum_Expr() = default;
};

class Product_Expr: public Expression {
private:
    const std::shared_ptr<Expression> left_expr;
    const std::shared_ptr<Expression> right_expr;
public:
    Product_Expr(const std::shared_ptr<Expression>& left_expr, const std::shared_ptr<Expression>& right_expr):
        left_expr(left_expr),
        right_expr(right_expr){};
    
    int Evaluate() const override {
        return left_expr->Evaluate() * right_expr->Evaluate();
    }

    std::string ToString() const override {
        std::string result = "";
        if (dynamic_cast<const Sum_Expr*>(left_expr.get())) {
            result.append("(");
            result.append(left_expr->ToString());
            result.append(")");
        } else {
            result.append(left_expr->ToString());
        }
        result.append(" * ");
        if (dynamic_cast<const Sum_Expr*>(right_expr.get())) {
            result.append("(");
            result.append(right_expr->ToString());
            result.append(")");
        } else {
            result.append(right_expr->ToString());
        }
        return result;
    }

    ~Product_Expr() = default;
};

using ExpressionPtr = std::shared_ptr<Expression>;

ExpressionPtr Const(const int value) {
    return std::make_shared<Const_Expr>(value);
}

ExpressionPtr Sum(const ExpressionPtr left_expr, const ExpressionPtr right_expr) {
    return std::make_shared<Sum_Expr>(left_expr, right_expr);
}

ExpressionPtr Product(const ExpressionPtr left_expr, const ExpressionPtr right_expr) {
    return std::make_shared<Product_Expr>(left_expr, right_expr);
}

int main() {
    ExpressionPtr ex1 = Sum(Product(Const(3), Const(4)), Const(5));
    std::cout << ex1->ToString() << "\n";  // 3 * 4 + 5
    std::cout << ex1->Evaluate() << "\n";  // 17

    ExpressionPtr ex2 = Product(Const(6), ex1);
    std::cout << ex2->ToString() << "\n";  // 6 * (3 * 4 + 5)
    std::cout << ex2->Evaluate() << "\n";  // 102
}