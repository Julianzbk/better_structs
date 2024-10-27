#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <typeindex>
#include <map>

using std::cout, std::endl;

#include <vector>
template <typename T>
std::ostream& operator << (std::ostream& out, std::vector<T> const& v)
{
    out << "[";
    for (T elem: v)
    {
        out << elem << " ";
    }
    out << '\b' << "]";
    return out;
}


struct Node
{
    void* data = nullptr;
    struct Node* next = nullptr;
    std::string type = "void";
};



enum typeid_table
{
    INT = 0,
    DOUBLE,
    FLOAT,
    CHAR,
    CONST_CHAR_P,
    STD_STRING = 5,
    STD_VECTOR_INT,
    STD_FORWARD_ITERATOR_TAG,
};

static const char* const typeid_table[] = 
{
    typeid(int).name(),
    typeid(double).name(),
    typeid(float).name(),
    typeid(char).name(),
    typeid(const char*).name(),
    typeid(std::string).name(),
    typeid(std::vector<int>).name(),
    typeid(std::forward_iterator_tag).name(),
};

/*
template <typename T>
h_array make_array_from_list(std::initializer_list<T> list)
{
    return h_array{};
}
*/
struct h_array
{
    Node* head;
    size_t size;

    template <typename T>
    inline static void print_cell(Node* p, std::ostream& out)
    {
        T* data_p = (T*) p->data;
        out << *data_p << " ";
    }

public:
    h_array()
        :head(nullptr), size(0)
    {
        
    }

    template <typename T>
    h_array(std::initializer_list<T> list)
        :head(nullptr), size(0)
    {
        for (T elem: list)
        {
            push(elem);
        }
    }

    template <typename T>
    void push(T data)
    {
        Node* p;
        if (head == NULL)
        {
            head = new Node;
            p = head;
        }
        else
        {
            p = head;
            for (; p->next != NULL; p = p->next);
            p->next = new Node;
            p = p->next;
        }
        T* data_p = new T{data};
        p->data = (void*) data_p;
        p->type = typeid(T).name();
        ++size;
    }

    void print(std::ostream& out) const
    {
        out << "[";
        for (Node* p = head; p != NULL; p = p->next)
        {
            if (p->type == typeid_table[INT])
                print_cell<int>(p, out);
            else if (p->type == typeid_table[DOUBLE])
                print_cell<double>(p, out);
            else if (p->type == typeid_table[CHAR])
                print_cell<char>(p, out);
            else if (p->type == typeid_table[STD_STRING])
                print_cell<std::string>(p, out);
            else if (p->type == typeid_table[STD_VECTOR_INT])
                print_cell<std::vector<int>>(p, out);
            else if (p->type == "PKc")
                print_cell<const char*>(p, out);
        }
        out << '\b' << "]";

        out<< endl << "types:" << "[";
        for (Node* p = head; p != NULL; p = p->next)
        {
            out << p->type << " ";
        }
        out << '\b' << "]";
    }

    ~h_array()
    {
        Node* next;
        for (Node* p = head; p != NULL; p = next)
        {
            next = p->next;
            delete p->data;
            delete p;
        }
    }

    friend std::ostream& operator << (std::ostream& out, h_array const& arr)
    {
        arr.print(out);
        return out;
    }
};

int main()
{
    h_array arr;
    arr.push(1);
    arr.push(-99.99);
    arr.push('a');
    arr.push("stringingingin");
    arr.push(std::vector<int>{1, 2, 3});
    arr.push(std::forward_iterator_tag{});
    cout << arr << endl;

    cout << h_array{1, 2, 3, 4} << endl;
    return 0;
}