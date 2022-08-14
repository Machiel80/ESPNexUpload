/**
 * @file ESPNexUploadWrapper.h
 * 
 * This code makes the ESPNexUpload functionality accessible and usable for C project.
 * This is a C++ wrapper for the ESPNexUpload Class.
 * 
 * For example, webservers like ‘libesphttpd’ that are only written in C.
 *
 * @author Machiel Mastenbroek (machiel.mastenbroek@gmail.com)
 * @date   2022/08/14
 * @version 1.0.0
 **/

#ifndef __ESPNEXUPLOADWRAPPER_H__
#define __ESPNEXUPLOADWRAPPER_H__

#include "esp_log.h"
#include "hal/uart_types.h"
#include "hal/gpio_types.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct ESPNexUpload ESPNexUpload_t;

    ESPNexUpload_t* ESPNexUpload_New(uart_port_t uart_num, uint32_t baud_rate
                                   , gpio_num_t tx_io_num, gpio_num_t rx_io_num);                   // 1-7 ESPNexUpload(..)
    void ESPNexUpload_Delete(ESPNexUpload_t *esp_scruct);                                           // 2-7 ~ESPNexUpload()
    bool ESPNexUpload_connect(ESPNexUpload_t *esp_scruct);                                          // 3-7 connect()
    bool ESPNexUpload_prepareUpload(ESPNexUpload_t *esp_scruct, uint32_t file_size);                // 4-7 prepareUpload(..)
    bool ESPNexUpload_upload(ESPNexUpload_t *esp_scruct, const uint8_t *file_buf, size_t buf_size); // 5-7 upload(..)
    void ESPNexUpload_softReset(ESPNexUpload_t *esp_scruct);                                        // 6-7 softReset()
    void ESPNexUpload_end(ESPNexUpload_t *esp_scruct);                                              // 7-7 end(..)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __ESPNEXUPLOADWRAPPER_H__ */