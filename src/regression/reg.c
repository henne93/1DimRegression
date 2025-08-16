#include <stdio.h>
#include <stdint.h>
#include "reg.h"



/**
 * @brief Calculates linear regression parameters for 32 data points.
 *
 * This function computes the slope and intercept for a set of 32 unsigned 16-bit integer values
 * using least squares linear regression. The slope and intercept are returned as fractions
 * (numerator/denominator) in the LineFit structure.
 *
 * @param[in]  y  Array of 32 uint16_t values representing the dependent variable.
 * @return     LineFit structure containing:
 *               - m_num: numerator of the slope
 *               - m_den: denominator of the slope
 *               - b_num: numerator of the intercept
 *               - b_den: denominator of the intercept
 *
 * @note The function expects the array y to have exactly 32 elements.
 *       The calculation uses integer arithmetic and returns results as fractions.
 */
LineFit linear_regression_32(const uint16_t y[N])
{
    int32_t sum_x = 0;
    int32_t sum_x2 = 0;
    int32_t sum_y = 0;
    int32_t sum_xy = 0;
    int32_t i = 0;
    LineFit result = {0};

    /* Calculate sums */
    for (i = 0; i < (int32_t)N; i++)
    {
        sum_x += i;
        sum_x2 += i * i;
        sum_y += (int32_t)y[i];
        sum_xy += i * (int32_t)y[i];
    }

    /* Slope: m = (N * sum_xy - sum_x * sum_y) / (N * sum_x2 - sum_x * sum_x) */
    {
        int32_t m_num = ((int32_t)N * sum_xy) - (sum_x * sum_y);
        int32_t m_den = ((int32_t)N * sum_x2) - (sum_x * sum_x);
        result.m_num = m_num;
        result.m_den = m_den;
    }

    /* Intercept: b = (sum_y * m_den - m_num * sum_x) / (N * m_den) */
    {
        int64_t b_num = ((int64_t)sum_y * (int64_t)result.m_den) - ((int64_t)result.m_num * (int64_t)sum_x);
        int64_t b_den = ((int64_t)N * (int64_t)result.m_den);
        result.b_num = (int32_t)b_num;
        result.b_den = (int32_t)b_den;
    }

    return result;
}
