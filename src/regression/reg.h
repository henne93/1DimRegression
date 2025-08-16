#include <stdio.h>

#define N 32

typedef struct {
    int32_t m_num;  // Steigung: Zähler
    int32_t m_den;  // Steigung: Nenner (immer 33344)
    int32_t b_num;  // Achsenabschnitt: Zähler
    int32_t b_den;  // Achsenabschnitt: Nenner (immer 32)
} LineFit;

/* Variable-length regression for uint16_t arrays */
LineFit linear_regression_uint16(const uint16_t *y, uint32_t len);
