#include "multithreading.h"

/**
 * check_edges - checks for out of bound errors and set start/end positions
 * @portion: portion struct
 * @start_x: start position of a pixel at X-axis
 * @start_y: start position of a pixel at Y-axis
 * @end_x: end position of a pixel at X-axis
 * @end_y: end position of a pixel at Y-axis
 * @kx_start: start position of a kernel at X-axis
 * @ky_start: start position of a kernel at Y-axis
 */
void check_borders(blur_portion_t const *portion, size_t *start_x,
                   size_t *start_y, size_t *end_x, size_t *end_y,
                   size_t *kx_start, size_t *ky_start)
{
    size_t half_kernel = portion->kernel->size / 2;

    if (*start_x < half_kernel)
    {
        *kx_start = half_kernel - *start_x;
        *end_x = half_kernel + *start_x + 1;
        *start_x = 0;
    }
    else
    {
        *kx_start = 0;
        *start_x = *start_x - half_kernel;
        *end_x = MIN(*start_x + portion->kernel->size, portion->img->w);
    }
    if (*start_y < half_kernel)
    {
        *ky_start = half_kernel - *start_y;
        *end_y = half_kernel + *start_y + 1;
        *start_y = 0;
    }
    else
    {
        *ky_start = 0;
        *start_y = *start_y - half_kernel;
        *end_y = MIN(*start_y + portion->kernel->size, portion->img->h);
    }
}

/**
 * blur_pixel - blurs a pixel
 * @portion: portion struct
 * @pos_x: position of a pixel at X-axis
 * @pos_y: position of a pixel at Y-axis
 */
void blur_pixel(blur_portion_t const *portion, size_t pos_x, size_t pos_y)
{
    size_t start_x = pos_x, start_y = pos_y, end_x, end_y;
    size_t x, y, k_x, k_y, kx_start, ky_start;
    float r_sum, g_sum, b_sum, k_sum = 0;

    k_x = k_y = r_sum = g_sum = b_sum = 0;
    check_borders(portion, &start_x, &start_y, &end_x,
                  &end_y, &kx_start, &ky_start);
    x = start_x, y = start_y;
    k_x = kx_start, k_y = ky_start;
    while (y < end_y)
    {
        r_sum += portion->kernel->matrix[k_x][k_y] * portion->img->pixels[portion->img->w * y + x].r;
        g_sum += portion->kernel->matrix[k_x][k_y] * portion->img->pixels[portion->img->w * y + x].g;
        b_sum += portion->kernel->matrix[k_x][k_y] * portion->img->pixels[portion->img->w * y + x].b;
        k_sum += portion->kernel->matrix[k_x][k_y];
        ++k_x, ++x;
        if (x == end_x)
        {
            x = start_x, ++y;
            k_x = kx_start, ++k_y;
        }
    }
    portion->img_blur->pixels[portion->img->w * pos_y + pos_x].r = r_sum / k_sum;
    portion->img_blur->pixels[portion->img->w * pos_y + pos_x].g = g_sum / k_sum;
    portion->img_blur->pixels[portion->img->w * pos_y + pos_x].b = b_sum / k_sum;
}

/**
 * blur_portion - blurs an image using gaussian blur
 * @portion: portion of the image
 */
void blur_portion(blur_portion_t const *portion)
{
    size_t x, y;

    x = portion->x;
    y = portion->y;
    while (y < portion->y + portion->h)
    {
        blur_pixel(portion, x, y);
        ++x;
        if (x == portion->x + portion->w)
        {
            x = portion->x;
            ++y;
        }
    }
}
