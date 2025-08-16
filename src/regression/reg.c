#include <stdio.h>
#include <stdint.h>
#include "reg.h"



/**
 * @brief Calculates linear regression parameters for a variable-length array of uint16_t data points.
 *
 * This function computes the slope and intercept for a set of unsigned 16-bit integer values
 * using least squares linear regression. The slope and intercept are returned as fractions
 * (numerator/denominator) in the LineFit structure.
 *
 * @param[in]  y    Pointer to array of uint16_t values representing the dependent variable.
 * @param[in]  len  Number of elements in the array (must be >= 2).
 * @return     LineFit structure containing:
 *               - m_num: numerator of the slope
 *               - m_den: denominator of the slope
 *               - b_num: numerator of the intercept
 *               - b_den: denominator of the intercept
 *
 * @note The function expects the array y to have at least 2 elements.
 *       If len < 2, the function returns a zero-initialized LineFit structure.
 *       The calculation uses integer arithmetic and returns results as fractions.
 */
LineFit linear_regression_uint16(const uint16_t *y, uint32_t len)
{
    int32_t sum_x = 0;
    int32_t sum_x2 = 0;
    int32_t sum_y = 0;
    int32_t sum_xy = 0;
    uint32_t i = 0U;
    LineFit result = {0};

    if ((y == NULL) || (len < 2U))
    {
        return result;
    }

    /* Calculate sums */
    for (i = 0U; i < len; i++)
    {
        sum_x += (int32_t)i;
        sum_x2 += (int32_t)i * (int32_t)i;
        sum_y += (int32_t)y[i];
        sum_xy += (int32_t)i * (int32_t)y[i];
    }

    /* Slope: m = (len * sum_xy - sum_x * sum_y) / (len * sum_x2 - sum_x * sum_x) */
    {
        int32_t m_num = (int32_t)len * sum_xy - sum_x * sum_y;
        int32_t m_den = (int32_t)len * sum_x2 - sum_x * sum_x;
        result.m_num = m_num;
        result.m_den = m_den;
    }

    /* Intercept: b = (sum_y * m_den - m_num * sum_x) / (len * m_den) */
    {
        int64_t b_num = ((int64_t)sum_y * (int64_t)result.m_den) - ((int64_t)result.m_num * (int64_t)sum_x);
        int64_t b_den = ((int64_t)len * (int64_t)result.m_den);
        result.b_num = (int32_t)b_num;
        result.b_den = (int32_t)b_den;
    }

    return result;
}
