#include <iostream>

using namespace std;
// 2 1 2 3 4 2 3 2 1
// Function prototypes
void calculate_cube(int* x, int* x_cubed, int n);
void calculate_square(int* y, int* y_squared, int n);
void calculate_sum(int* x_cubed, int* y_squared, int* sum_result, int n);
void matrix_vector_multiply(int** A, int* result, int* final_result, int n);

int main()
{
    {
        // ÔÎĞÌÓÂÀÍÍß ÌÀÒĞÈÖ²
        int n;
        cout << "Enter n: ";
        cin >> n;
        int** a = new int* [n]; // ìàòğèöÿ À
        int** b = new int* [n]; // ìàòğèöÿ Â
        int** res = new int* [n]; // ğåçóëüòóş÷à ìàòğèöÿ
        cout << "Elements of matrix: ";
        for (int i = 0; i < n; i++)
        {
            a[i] = new int[n];
            b[i] = new int[n];
            res[i] = new int[n];
            for (int j = 0; j < n; j++)
            {
                cin >> a[i][j];
                b[i][j] = i + j - 1;
                res[i][j] = 0;
            }
        }
        // Â²ÇÓÀË²ÇÀÖ²ß ÑÔÎĞÌÎÂÀÍÈÕ ÌÀÒĞÈÖÜ
        cout << "A: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "B: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << b[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        // ÀÑÅÌÁËÅĞÍÀ ÂÑÒÀÂÊÀ (àëãîğèòì ìíîæåííÿ ìàòğèöü)
        // Äëÿ çğó÷íîñò³ öèêëè çàïèñàíî íà Ñ++ 
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                __asm
                {
                    mov edx, res // edx = res
                    mov esi, i
                    imul esi, 4
                    add edx, esi // edx = &res[i]
                    push[edx]
                    pop edx // edx = res[i]
                    mov esi, j
                    imul esi, 4
                    add edx, esi // edx = &res[i][j]
                    push edx
                    xor esi, esi
                    mov ecx, n
                    start :
                    mov eax, a
                        mov ebx, b
                        a_to_eax :
                    mov edx, i
                        mov eax, [eax + 4 * edx] // eax = a[i]
                        mov edx, esi
                        mov eax, [eax + 4 * edx] // eax = a[i][esi]
                        b_to_ebx :
                        mov edx, esi
                        mov ebx, [ebx + 4 * edx] // ebx = b[esi]
                        mov edx, j
                        mov ebx, [ebx + 4 * edx] // ebx = b[esi][j]
                        end :
                        pop edx
                        imul eax, ebx // eax = a[i][esi]*b[esi][j]
                        add[edx], eax
                        push edx
                        inc esi
                        loop start
                        pop edx
                }
            }
        }
        // ÂÈÂÅÄÅÍÍß ĞÅÇÓËÜÒÀÒÓ
        cout << "A*B: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << res[i][j] << " ";
            }
            cout << endl;
        }
    }
    system("pause");

    // Data reading
    {
        int n;
        cout << "Enter the size of the square matrix: ";
        cin >> n;

        int** A = new int* [n];
        cout << "Enter the elements of the square matrix A:" << endl;
        for (int i = 0; i < n; ++i) {
            A[i] = new int[n];
            for (int j = 0; j < n; ++j) {
                cin >> A[i][j];
            }
        }

        int* x = new int[n];
        cout << "Enter the elements of vector x:" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }

        int* y = new int[n];
        cout << "Enter the elements of vector y:" << endl;
        for (int i = 0; i < n; ++i) {
            cin >> y[i];
        }

        // Inline assembly
        int* x_cubed = new int[n];
        int* y_squared = new int[n];
        int* sum_result = new int[n];
        int* final_result = new int[n];

        calculate_cube(x, x_cubed, n);
        calculate_square(y, y_squared, n);
        calculate_sum(x_cubed, y_squared, sum_result, n);
        matrix_vector_multiply(A, sum_result, final_result, n);

        // Display result
        cout << "Resulting vector:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << final_result[i] << " ";
        }
        cout << endl;

        // Free allocated memory
        delete[] x;
        delete[] y;
        delete[] x_cubed;
        delete[] y_squared;
        delete[] sum_result;
        delete[] final_result;

        for (int i = 0; i < n; ++i) {
            delete[] A[i];
        }
        delete[] A;
    }

    system("pause");

    return 0;
}
void matrix_vector_multiply(int** A, int* result, int* final_result, int n) 
{
    for (int i = 0; i < n; ++i) {
        final_result[i] = 0;
        for (int j = 0; j < n; ++j) {
            final_result[i] += A[i][j] * result[j];
        }
    }
}

void calculate_cube(int* x, int* x_cubed, int n) {
    __asm {
        mov ecx, n
        mov esi, x
        mov edi, x_cubed
        loop_start1 :
        mov eax, [esi]
            imul eax, eax
            imul eax, [esi]
            mov[edi], eax

            add esi, 4
            add edi, 4
            loop loop_start1
    }
}

void calculate_square(int* y, int* y_squared, int n) {
    __asm {
        mov ecx, n
        mov esi, y
        mov edi, y_squared
        loop_start2 :
        mov eax, [esi]
            imul eax, eax
            mov[edi], eax

            add esi, 4
            add edi, 4
            loop loop_start2
    }
}

void calculate_sum(int* x_cubed, int* y_squared, int* sum_result, int n) {
    __asm {
        mov ecx, n
        mov esi, x_cubed
        mov edx, y_squared
        mov edi, sum_result
        loop_start3 :
        mov eax, [esi]
            add eax, [edx]
            mov[edi], eax

            add esi, 4
            add edx, 4
            add edi, 4
            loop loop_start3
    }
}

void matrix_vector_myltiply(int** A, int* result, int* final_result, int n) {
    for (int i = 0; i < n; ++i) {
        final_result[i] = 0; // Initialize the final result vector

        __asm {
            mov esi, A          // Load pointer to the matrix A
            mov esi, [esi]      // Move to the current row of A

            mov edx, result     // Load pointer to the result vector
            mov ebx, i          // Move to the corresponding element of the result vector
            imul ebx, 4         // Multiply by 4 (size of int) to get the offset
            add edx, ebx        // Move to the current element of the result vector

            lea edi, [final_result + i * 4] // Calculate pointer to the current element of the final result vector

            mov ecx, n          // Initialize loop counter for inner loop
            xor eax, eax        // Clear accumulator for dot product

            inner_loop :
            mov ebx, [esi]          // Load current element of matrix A
                imul ebx, [edx]         // Multiply current element of matrix A by corresponding element of result vector
                add eax, ebx            // Add to the accumulator for dot product

                add esi, 4              // Move to the next element in the row of matrix A
                add edx, 4              // Move to the next element in the result vector

                loop inner_loop         // Repeat inner loop if not yet done

                mov eax, [edi]      // Load the current value of final_result[i]
                add eax, ebx        // Add the dot product to the current value
                mov[edi], eax      // Store the updated value back to final_result[i]
        }
    }
}