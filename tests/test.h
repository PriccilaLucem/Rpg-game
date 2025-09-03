
// test.h
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdbool.h>

// Estrutura para armazenar informações do teste
typedef struct {
    const char* name;
    bool (*test_func)(void);
} Test;

// Macro para criar um novo teste
#define TEST(name, func) { name, func }

// Função para executar um conjunto de testes
void run_tests(Test tests[], int num_tests) {
    int passed = 0;
    int failed = 0;
    
    printf("\nExecutando %d testes...\n\n", num_tests);
    
    for (int i = 0; i < num_tests; i++) {
        printf("Teste '%s': ", tests[i].name);
        
        if (tests[i].test_func()) {
            printf("PASSOU\n");
            passed++;
        } else {
            printf("FALHOU\n");
            failed++;
        }
    }
    
    printf("\nResultados:\n");
    printf("Passaram: %d\n", passed);
    printf("Falharam: %d\n", failed);
    printf("Total: %d\n", num_tests);
}

// Macros para asserções
#define ASSERT(condition) if (!(condition)) return false
#define ASSERT_EQUAL(a, b) if ((a) != (b)) return false
#define ASSERT_NOT_EQUAL(a, b) if ((a) == (b)) return false
#define ASSERT_NULL(ptr) if ((ptr) != NULL) return false
#define ASSERT_NOT_NULL(ptr) if ((ptr) == NULL) return false

#endif