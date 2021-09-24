#ifndef AST_HPP
#define AST_HPP

#include <vector>

#include <Runtime.hpp>
#include <Token.hpp>

enum class NodeType {
    ROOT = 0,
    CONST = 1,
    UNARY_OP = 2,
    BINARY_OP = 3,
    VARIABLE = 4,
};

class ASTNode {
    public: 
        ASTNode();

        bool isLeafNode();
        void addChild(ASTNode* node);
        ASTNode* getChild(int index);
        virtual value_t eval(RuntimeContext& context);

        ~ASTNode();

        virtual const NodeType getType();

        void dump(std::string prefix = "");
    protected:
        std::vector<ASTNode*> m_children;
};

class ConstNode : public ASTNode {
    public:
        ConstNode(value_t value);

        value_t eval(RuntimeContext& context);
        const NodeType getType();

       private:
        value_t m_value;
};

class UnaryOpNode : public ASTNode {
   public:
    UnaryOpNode(Token token);

    value_t eval(RuntimeContext& context);
    const NodeType getType();

   private:
    Token m_token;
};

class BinaryOpNode : public ASTNode {
   public:
    BinaryOpNode(Token token);

    value_t eval(RuntimeContext& context);
    const NodeType getType();

   private:
    Token m_token;
};

class VariableNode : public ASTNode {
   public:
    VariableNode(std::string id);

    value_t eval(RuntimeContext& context);
    const NodeType getType();

   private:
    std::string m_name;
};

class ExpressionNode : public ASTNode {
   public:
    ExpressionNode(std::string id);

    value_t eval(RuntimeContext& context);
    const NodeType getType();

   private:
    std::string m_name;
};

#endif