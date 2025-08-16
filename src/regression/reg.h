#include <stdio.h>

#define N 32

typedef struct {
    int32_t m_num;  // Steigung: Zähler
    int32_t m_den;  // Steigung: Nenner (immer 33344)
    int32_t b_num;  // Achsenabschnitt: Zähler
    int32_t b_den;  // Achsenabschnitt: Nenner (immer 32)
} LineFit;

LineFit linear_regression_32(const uint16_t y[N]);
