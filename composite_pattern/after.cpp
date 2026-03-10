#include <iostream>
#include <vector>
#include <memory>
// Component 
class ProductNode {
public:
    virtual void print(int depth = 0) const = 0;
    virtual ~ProductNode() = default;
};

// Leaf node 
class Band : public ProductNode {
public:
    void print(int depth = 0) const override {
        std::cout << std::string(depth, ' ')
                  << "Band\n";
    }
};

class TiePointGrid : public ProductNode {
public:
    void print(int depth = 0) const override {
        std::cout << std::string(depth, ' ')
                  << "TiePointGrid\n";
    }
};

class Metadata : public ProductNode {
public:
    void print(int depth = 0) const override {
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
    void add(std::unique_ptr<ProductNode> node) {
        children.push_back(std::move(node));
    }

    void print(int depth = 0) const override {
        std::cout << std::string(depth, ' ')
                  << "Group\n";

        for (const auto& c : children) {
            c->print(depth + 2);
        }
    }
};

// Client 
int main() {

    auto root = std::make_unique<ProductNodeGroup>();

    root->add(std::make_unique<Band>());
    root->add(std::make_unique<TiePointGrid>());

    auto metadataGroup = std::make_unique<ProductNodeGroup>();
    metadataGroup->add(std::make_unique<Metadata>());
    metadataGroup->add(std::make_unique<Metadata>());

    root->add(std::move(metadataGroup));

    root->print();
}