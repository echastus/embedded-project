#ifndef LIS_H
#define LIS_H
/*======================================*/

#define LIS302_WHO_AM_I 0x0F

// status
#define LIS302_X_NEW_DATA (0x27 & (1U << 0U))
#define LIS302_Y_NEW_DATA	(0x27 & (1U << 1U))
#define LIS302_Z_NEW_DATA (0x27 & (1U << 2U))
#define LIS302_ZYX_NEW_DATA (0x27 & (1U << 3U))

// output
#define LIS302_REG_OUT_X 0x29
#define LIS302_REG_OUT_Y 0x2B
#define LIS302_REG_OUT_Z 0x2D













#endif
