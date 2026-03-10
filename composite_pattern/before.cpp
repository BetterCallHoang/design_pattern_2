#include <iostream>
#include <vector>
#include <memory>

class Band {
public:
    void Print() const {
        std::cout << "Band\n";
    }
};

class TiePointGrid {
public:
    void Print() const {
        std::cout << "TiePointGrid\n";
    }
};

class Metadata {
public:
    void Print() const {
        std::cout << "Metadata\n";
    }
};

class Product {
private:
    std::vector<Band> bands;
    std::vector<TiePointGrid> grids;
    std::vector<Metadata> metadata;

public:
    void AddBand(const Band& b) {
        bands.push_back(b);
    }

    void AddGrid(const TiePointGrid& g) {
        grids.push_back(g);
    }

    void AddMetadata(const Metadata& m) {
        metadata.push_back(m);
    }

    void Print() {
        std::cout << "Product:\n";

        for (auto& b : bands)
            b.Print();

        for (auto& g : grids)
            g.Print();

        for (auto& m : metadata)
            m.Print();
    }
};

int main() {
    Product p;

    p.AddBand(Band());
    p.AddGrid(TiePointGrid());
    p.AddMetadata(Metadata());

    p.Print();
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