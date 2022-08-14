/* main program */
#include <Arduino.h>

#include "main.h"
#include "ESPNexUpload.h"

static const char *TAG = "app_main";


// Steps
// 1. Create your own binaries.c !!!!!
//    This step is not implemented or documented, TODO
//    See the 'ESPIDF_example' for inspiration
// 2. Build project
// 3. Flash project

void setup() {

    bool result;  
    
    Serial.begin(115200);
    Serial.println("Hello world");


    vTaskDelay(5000 / portTICK_PERIOD_MS);

    ESP_LOGI(TAG,"Nextion display start");
    ESPNexUpload nextion(D_UART_NUM,
                         D_BAUDRATE,
                         D_TX,
                         D_RX);
  
    // prepare upload: setup serial connection, send update command and send the expected update size
    result = nextion.prepareUpload(SMALL_TJC_tft_size);

    if(!result){
        ESP_LOGE(TAG,"prepareUpload failed");
    }else{
        ESP_LOGI(TAG,"filesize: %"PRIu32" bytes", SMALL_TJC_tft_size);

        // Upload the received byte stream to the nextion
        result = nextion.upload(SMALL_TJC_tft,SMALL_TJC_tft_size);

        if(result){
            ESP_LOGI(TAG,"Succesfully updated Nextion!");
        }else{
            ESP_LOGE(TAG,"Failed updating Nextion: ");
        }

        nextion.end();
    }

}

void loop() {

    delay(1000);

}