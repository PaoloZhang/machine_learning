if !
defined(__EXP_TABLE__)
#define __EXP_TABLE__

#define EXP_TABLE_SIZE 1000
#define MAX_EXP 6

typedef float real;

class ExpTable {
private:
    real table[];
public:
    ExpTable() {
      table = (real *) malloc((EXP_TABLE_SIZE + 1) * sizeof(real));
      for (i = 0; i < EXP_TABLE_SIZE; i++) {
        table[i] = exp((i / (real) EXP_TABLE_SIZE * 2 - 1) * MAX_EXP); // Precompute the exp() table
        table[i] = table[i] / (table[i] + 1);                   // Precompute f(x) = x / (x + 1)
      }
    }
}

#endif