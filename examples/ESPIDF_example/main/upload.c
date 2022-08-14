/* nextion upload firmware example */
#include <stdio.h>
#include <string.h>

#include "esp_system.h"
#include "esp_log.h"
#include "esp_console.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nvs_flash.h"

#include <inttypes.h>

#include "upload.h"
// #include "ESPNexUpload.h"
#include "ESPNexUploadWrapper.h"


static const char *TAG = "app_main";

// static void initialize_nvs(void);
static int uart_cmd(int argc, char **argv);

void app_main(void) {

    ESP_LOGI(TAG,"app_main started");

    esp_log_level_set("*", ESP_LOG_INFO);

    // ---------------- CONSOLE -----------------

    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    
    repl_config.prompt = "esp32 >"; // Prompt to be printed before each line, this can be customized, made dynamic, etc.
    repl_config.max_cmdline_length = CONFIG_CONSOLE_MAX_COMMAND_LINE_LENGTH;

    esp_console_register_help_command(); // Register commands

    const esp_console_cmd_t esp_cmd = {
        .command = "cmd",
        .help = "cmd 1,2,restart etc",
        .hint = NULL,
        .func = &uart_cmd,
    };
    
    ESP_ERROR_CHECK(esp_console_cmd_register(&esp_cmd) );
    ESP_ERROR_CHECK(esp_console_new_repl_uart(&uart_config, &repl_config, &repl));
    ESP_ERROR_CHECK(esp_console_start_repl(repl));


    // ------------- NEXTION UPLOAD -------------
    vTaskDelay(5000 / portTICK_PERIOD_MS);


    // struct SensorsController* c = newSensorsController();
    
    ESP_LOGI(TAG,"Nextion display start");
    struct ESPNexUpload* nextion = ESPNexUpload_New(D_UART_NUM,
                                                    D_BAUDRATE,
                                                    D_TX,
                                                    D_RX);
  
    // prepare upload: setup serial connection, send update command and send the expected update size
    bool result = ESPNexUpload_prepareUpload(nextion,SMALL_TJC_tft_size);

    if(!result){
        ESP_LOGE(TAG,"prepareUpload failed");
    }else{
        ESP_LOGI(TAG,"filesize: %"PRIu32" bytes", SMALL_TJC_tft_size);

        // Upload the received byte stream to the nextion
        result = ESPNexUpload_upload(nextion,SMALL_TJC_tft,SMALL_TJC_tft_size);

        if(result){
            ESP_LOGI(TAG,"Succesfully updated Nextion!");
        }else{
            ESP_LOGE(TAG,"Failed updating Nextion: ");
        }

        ESPNexUpload_end(nextion);
    }

    // ESPNexUpload_Delete(nextion);
}

/* UART 'cmd' command */
static int uart_cmd(int argc, char **argv) {
    int i;
    for(i=1;i<argc;i++) {

        if(strcmp(argv[1],"1") == 0) {
            printf("[cmd 1] do somthing 1 ..");
            return 0;
        }

        if(strcmp(argv[1],"2") == 0) {
            printf("[cmd 2] do somthing 2 ..\n");
            return 0;
        }

        if(strcmp(argv[1],"restart") == 0) {
            printf("restart esp\n");
            esp_restart();
        }
    }
    return 0;
}


