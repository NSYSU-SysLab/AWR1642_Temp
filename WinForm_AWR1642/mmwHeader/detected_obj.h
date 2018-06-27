/*
 * detect_obj.h
 *
 */

#ifndef DETECT_OBJ_H_
#define DETECT_OBJ_H_
#include <stdint.h>
/*! @brief Maximum number of detected objects by HWA. */
#define MMW_MAX_OBJ_OUT 100

/*!
 *  @brief    Detected object estimated parameters
 *
 */
typedef volatile struct MmwDemo_detectedObj_t
{
    uint16_t   rangeIdx;     /*!< @brief Range index */
    uint16_t   dopplerIdx;   /*!< @brief Dopler index */
    uint16_t  peakVal;      /*!< @brief Peak value */
    int16_t  x;             /*!< @brief x - coordinate in meters. Q format depends on the range resolution */
    int16_t  y;             /*!< @brief y - coordinate in meters. Q format depends on the range resolution */
    int16_t  z;             /*!< @brief z - coordinate in meters. Q format depends on the range resolution */
} MmwDemo_detectedObj;


#endif /* DETECT_OBJ_H_ */
