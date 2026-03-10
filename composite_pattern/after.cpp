#include <iostream>
#include <vector>
#include <memory>
// Component 
class ProductNode {
public:
    virtual void Print(int depth = 0) const = 0;
    virtual ~ProductNode() = default;
};

// Leaf node 
class Band : public ProductNode {
public:
    void Print(int depth = 0) const override {
        std::cout << std::string(depth, ' ')
                  << "Band\n";
    }
};

class TiePointGrid : public ProductNode {
public:
    void Print(int depth = 0) const override {
        std::cout << std::string(depth, ' ')
                  << "TiePointGrid\n";
    }
};

class Metadata : public ProductNode {
public:
    void Print(int depth = 0) const override {
        std::cout << std::string(depth, ' ')
                  << "Metadata\n";
    }
};
// end Leaf node
// Composite 
class ProductNodeGroup : public ProductNode {
private:
    std::vector<std::unique_ptr<ProductNode>> children;

public:
    void Add(std::unique_ptr<ProductNode> node) {
        children.push_back(std::move(node));
    }

    void Print(int depth = 0) const override {
        std::cout << std::string(depth, ' ')
                  << "Group\n";

        for (const auto& c : children) {
            c->Print(depth + 2);
        }
    }
};

// Client 
int main() {

    auto root = std::make_unique<ProductNodeGroup>();

    root->Add(std::make_unique<Band>());
    root->Add(std::make_unique<TiePointGrid>());

    auto metadata_group = std::make_unique<ProductNodeGroup>();
    metadata_group->Add(std::make_unique<Metadata>());
    metadata_group->Add(std::make_unique<Metadata>());

    root->Add(std::move(metadata_group));

    root->Print();
}