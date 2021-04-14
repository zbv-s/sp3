
#include <iostream>
#include <cstdint>
class ArrayNN
{
private:
	int32_t** array;
	int32_t column_size, string_size;
	void create_array();
	void fill_array_NN();
public:
	ArrayNN();
	~ArrayNN();
	void output_array();
};

ArrayNN::ArrayNN()
{
        do
        {
                std::cout << "Input:" <<std::endl;
                std::cin >> column_size;
                std::cin >> string_size;
        } while (column_size * string_size <= 0);
        create_array();
        fill_array_NN();
}

ArrayNN::~ArrayNN()
{
        for (int32_t i = 0; i < column_size; i++)
        {
                delete[] array[i];
        }
        delete[] array;
}

void ArrayNN::create_array()
{
        array = new int32_t* [column_size];
        for (int32_t i = 0; i < column_size; i++)
        {
                array[i] = new int32_t [string_size];
        }
}

void ArrayNN::fill_array_NN()
{
        int32_t** array_start = array;
        int32_t strings_count = column_size;
        int32_t columns_count = string_size;
        array[0][0] = 7;
        asm(
                "movl %[start], %%eax\n\t"
                "movl (%%eax), %%ebx\n\t"
                "xorl %%ecx, %%ecx\n\t"
                "xorl %%edx, %%edx\n\t"
                "xorl %%edi, %%edi\n\t"
                "loop_start:\n\t"
                        "cmpl %[cc], %%edx\n\t"
                        "je loop_next_string\n\t"
                        "incl %%edi\n\t"
                        "movl %%edi, (%%ebx)\n\t"
                        "incl %%edx\n\t"
                        "addl $4, %%ebx\n\t"
                        "jmp loop_start\n\t"
                "loop_next_string:\n\t"
                        "incl %%ecx\n\t"
                        "cmpl %[sc], %%ecx\n\t"
                        "je loop_end\n\t"
                        "addl $4, %%eax\n\t"
                        "xorl %%edx, %%edx\n\t"
                        "movl (%%eax), %%ebx\n\t"
                        "jmp loop_start\n\t"
                "loop_end:\n\t"
                :
                :[start]"m"(array_start), [cc]"m"(strings_count), [sc]"m"(columns_count)
                :"%eax", "%ebx", "%ecx", "%edx", "%edi", "cc", "memory"
        );
}

void ArrayNN::output_array()
{
        for (int32_t i = 0; i < column_size; i++)
        {
                for (int32_t j = 0; j < string_size; j++)
                {
                        std::cout << array[j][i] << "\t";
                }
                std::cout << std::endl;
        }
        std::cout << std::endl;
};

int main() {
        ArrayNN array;
        array.output_array();
}


