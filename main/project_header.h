#ifndef PROJECT_HEADER_H
#define PROJECT_HEADER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
static void print_auth_mode(int authmode);
#define DEFAULT_SCAN_LIST_SIZE 
static const char* TAG = "wifi_scan";

void wifiScanTask(void *pvParameter)
{
    while(1) {
        printf("\nScanning nearby Wi-Fi networks...\n\n");
        esp_wifi_scan_start(NULL, true);
        uint16_t apCount = 0;
        esp_wifi_scan_get_ap_num(&apCount);
        printf("Number of networks found: %d\n", apCount);
        wifi_ap_record_t *wifiApList = (wifi_ap_record_t * )malloc(sizeof(wifi_ap_record_t)*apCount);
        esp_wifi_scan_get_ap_records(&apCount, wifiApList);
        for(int i = 0; i < apCount; i++) {
            printf("SSID %d: %s, RSSI: %d\n", i+1, wifiApList[i].ssid, wifiApList[i].rssi);
            print_auth_mode(wifiApList[i].authmode);
        }
        free(wifiApList);
        vTaskDelay(pdMS_TO_TICKS(5000)); // Delay 5 seconds before scanning again
    }
}

static void print_auth_mode(int authmode)
{
    switch (authmode) {
    case WIFI_AUTH_OPEN:
         ESP_LOGI(TAG, "Authmode \tOPEN\n");
        break;
    case WIFI_AUTH_OWE:
         ESP_LOGI(TAG, "Authmode \tOWE\n");
        break;
    case WIFI_AUTH_WEP:
         ESP_LOGI(TAG, "Authmode \tWEP\n");
        break;
    case WIFI_AUTH_WPA_PSK:
         ESP_LOGI(TAG, "Authmode \tWPA_PSK\n");
        break;
    case WIFI_AUTH_WPA2_PSK:
         ESP_LOGI(TAG, "Authmode \tWPA2_PSK\n");
        break;
    case WIFI_AUTH_WPA_WPA2_PSK:
         ESP_LOGI(TAG, "Authmode \tWPA_WPA2_PSK");
        break;
    case WIFI_AUTH_WPA2_ENTERPRISE:
         ESP_LOGI(TAG, "Authmode \tWPA2_ENTERPRISE\n");
        break;
    case WIFI_AUTH_WPA3_PSK:
         ESP_LOGI(TAG, "Authmode \tWPA3_PSK\n");
        break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
         ESP_LOGI(TAG, "Authmode \tWPA2_WPA3_PSK\n");
        break;
    default:
         ESP_LOGI(TAG, "Authmode \tUNKNOWN\n");
        break;
    }
}

#endif