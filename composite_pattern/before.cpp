#include <iostream>
#include <vector>
#include <memory>

class Band {
public:
    void print() const {
        std::cout << "Band\n";
    }
};

class TiePointGrid {
public:
    void print() const {
        std::cout << "TiePointGrid\n";
    }
};

class Metadata {
public:
    void print() const {
        std::cout << "Metadata\n";
    }
};

class Product {
private:
    std::vector<Band> bands;
    std::vector<TiePointGrid> grids;
    std::vector<Metadata> metadata;

public:
    void addBand(const Band& b) {
        bands.push_back(b);
    }

    void addGrid(const TiePointGrid& g) {
        grids.push_back(g);
    }

    void addMetadata(const Metadata& m) {
        metadata.push_back(m);
    }

    void print() {
        std::cout << "Product:\n";

        for (auto& b : bands)
            b.print();

        for (auto& g : grids)
            g.print();

        for (auto& m : metadata)
            m.print();
    }
};

int main() {
    Product p;

    p.addBand(Band());
    p.addGrid(TiePointGrid());
    p.addMetadata(Metadata());

    p.print();
}
/* Vấn đề 
1.  Product phải biết hết các node --> Muốn thêm các node phải chỉnh sửa Product
2. Không thể tạo ra các cấu trúc phức tạp hơn
Product
 ├── BandGroup
 │      ├── Band
 │      └── Band
 └── MetadataGroup
        ├── Metadata
        └── Metadata
3. Phải xử lý riêng cho từng loại 

*/