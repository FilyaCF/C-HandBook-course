#include <iostream>
#include <vector>
#include <memory>

class TreeNode : public std::enable_shared_from_this<TreeNode> {
private:
    int value;
    std::weak_ptr<TreeNode> parent;
    std::vector<std::shared_ptr<TreeNode>> children;

public:
    TreeNode(int val): value(val) {
    }

    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;

    std::shared_ptr<TreeNode> AddChild(int child_value) {
        auto node = std::make_shared<TreeNode>(child_value);
        node->parent = shared_from_this();
        children.push_back(node);
        return node;
    }

    void Print(int depth = 0) const {
        for (int i = 0; i < depth; ++i) {
            std::cout << " ";
        }
        std::cout << "- " << value << "\n";
        for (const auto& child : children) {
            child->Print(depth + 1);
        }
    }
};

int main() {
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(1);

    auto left_son = root->AddChild(10);
    auto middle_son = root->AddChild(20);
    auto right_son = root->AddChild(30);

    left_son->AddChild(100);
    left_son->AddChild(200);

    root->Print();
}