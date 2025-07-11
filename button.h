#include <Windows.h>
#include <vector>
class field;
class button {
    int i, j;
    void paint_zero();
    void paint_cross();
    void InitWindow();
    bool is_pushed;
    size_t BN_ID;
    field* parent;
    int symbol;
    HWND hW; // comment if use in linux

    button(const button& other) = delete;
    button& operator=(const button& other) = delete;
  public:
    button(button&& other) = default;
    int get_symbol() const { return symbol; }
    bool push(bool is_first);
    button(int _j, int _i, field* _parent);
};

class field {
    bool is_first;
    int _size;
    // HWND hWf;
    std::vector<std::vector<button>> arr;
    bool ChekState(size_t j, size_t i) const;
    // friend check;check Check;
    bool Go(int chek_symbol, size_t i, size_t j,
            bool (**change_i_j)(size_t& i, size_t& j, size_t size)) const;

  public:
    field(int field_size);
    void push(size_t ID);
    bool is_cross() const { return is_first; }
    int size() const { return _size; }
};

void Victory(bool is_first);
size_t get_bn_id(size_t j, size_t i);
