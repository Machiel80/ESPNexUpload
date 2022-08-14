#include "ESPNexUpload.h"
#include "ESPNexUploadWrapper.h"

static const char *TAG = "upload_wrapper";

extern "C" {
        
  // 1-7 ESPNexUpload(..)
  ESPNexUpload_t* ESPNexUpload_New(uart_port_t uart_num, uint32_t baud_rate, gpio_num_t tx_io_num, gpio_num_t rx_io_num) {
    return new ESPNexUpload(uart_num,baud_rate,tx_io_num,rx_io_num);
  }

  // 2-7 ~ESPNexUpload()
  void ESPNexUpload_Delete(ESPNexUpload_t *esp_scruct) {

    if (esp_scruct == NULL) {
      ESP_LOGE(TAG,"function ESPNexUpload_Delete failed");
      return;
    }

    delete static_cast<ESPNexUpload *>(esp_scruct);
    free(esp_scruct);
  }

  // 3-7 connect()
  bool ESPNexUpload_connect(ESPNexUpload_t *esp_scruct) {
    ESPNexUpload *esp_obj;

    if (esp_scruct == NULL) {
      ESP_LOGE(TAG,"function ESPNexUpload_connect failed");
      return false;
    }
                        
    esp_obj = static_cast<ESPNexUpload *>(esp_scruct);
    return esp_obj->connect();
  }

  // 4-7 prepareUpload(..)
  bool ESPNexUpload_prepareUpload(ESPNexUpload_t *esp_scruct, uint32_t file_size) {
    ESPNexUpload *esp_obj;

    if (esp_scruct == NULL) {
      ESP_LOGE(TAG,"function ESPNexUpload_prepareUpload failed");
      return false;
    }
                        
    esp_obj = static_cast<ESPNexUpload *>(esp_scruct);
    return esp_obj->prepareUpload(file_size);
  }

  // 5-7 upload(..)
  bool ESPNexUpload_upload(ESPNexUpload_t *esp_scruct, const uint8_t *file_buf, size_t buf_size) {
    ESPNexUpload *esp_obj;

    if (esp_scruct == NULL) {
      ESP_LOGE(TAG,"function ESPNexUpload_upload failed");
      return false;
    }
                        
    esp_obj = static_cast<ESPNexUpload *>(esp_scruct);
    return esp_obj->upload(file_buf,buf_size);
  }


  // 6-7 softReset()
  void ESPNexUpload_softReset(ESPNexUpload_t *esp_scruct) {
    ESPNexUpload *esp_obj;

    if (esp_scruct == NULL) {
      ESP_LOGE(TAG,"function ESPNexUpload_softReset failed");
      return;
    }

    esp_obj = static_cast<ESPNexUpload *>(esp_scruct);
    esp_obj->softReset();
  }

  // 7-7 end(..)
  void ESPNexUpload_end(ESPNexUpload_t *esp_scruct) {
    ESPNexUpload *esp_obj;

    if (esp_scruct == NULL) {
      ESP_LOGE(TAG,"function ESPNexUpload_end failed");
      return;
    }
                        
    esp_obj = static_cast<ESPNexUpload *>(esp_scruct);
    return esp_obj->end();
  }
}