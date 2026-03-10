  // SNAP code like this
#include <iostream>
#include <memory>

// Interface filter
class Filter {
public:
    virtual void doSth() const = 0;
    virtual ~Filter() = default;
};

class LeeFilter : public Filter {
public:    
    void doSth() const override{
        std::cout << "Do LeeFilter techniques"<<std::endl;
    }
};

class MedianFilter : public Filter{
public:
    void doSth() const override {
        std::cout << "Do MedianFilter techniques"<<std::endl;
    }
};

// IFactory 
class FilterFactory {
public:
    virtual std::unique_ptr<Filter> create() const = 0;
    virtual ~FilterFactory() = default;
};

// Concrete Factory
class LeeFilterFactory : public FilterFactory {
public:
    std::unique_ptr<Filter> create() const override {
        return std::make_unique<LeeFilter>();
    }
};

class MedianFilterFactory : public FilterFactory {
public:
    std::unique_ptr<Filter> create() const override {
        return std::make_unique<MedianFilter>();
    }
};



int main() {
    // User choose "Lee Filter Button" --> Program call "LeeFilterFactory"
    LeeFilterFactory b;
    auto a = b.create();
    a->doSth();
    return 0;

}