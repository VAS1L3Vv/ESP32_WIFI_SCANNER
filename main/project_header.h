#ifndef PROJECT_HEADER_H
#define PROJECT_HEADER_H

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
static char* auth_mode(int authmode);
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
        printf("__________________________________________________________________________________\n");
        printf("|  Num  |             SSID              |       RSSI         |      SECURITY       |\n");
        printf("|_______|_______________________________|____________________|_____________________|\n");
        for(int i = 0; i < apCount; i++) 
        {
            if (i+1 <10)
            printf("|   %d   |    ", i+1);
            else printf("|   %d  |    ", i+1);
            char SSID[100];
            sprintf(SSID,"%s",wifiApList[i].ssid);
            char SSID_str[30] = "                              ";
            for(int j = 0; j < strlen(SSID);j++)
            {
            SSID_str[j] = SSID[j];
            }
            int SSID_length = strlen(SSID_str);
            printf("%s  ",SSID_str);
            printf("      %d        ",wifiApList[i].rssi);
            printf("     %s \n",auth_mode(wifiApList[i].authmode));
        }
        free(wifiApList);
        vTaskDelay(pdMS_TO_TICKS(30000)); // Delay 30 seconds before scanning again
    }
}

static char* auth_mode(int authmode)
{
    switch (authmode) {
    case WIFI_AUTH_OPEN:
         return "OPEN";
        break;
    case WIFI_AUTH_OWE:
         return "OWE";
        break;
    case WIFI_AUTH_WEP:
         return "WEP";
        break;
    case WIFI_AUTH_WPA_PSK:
         return "WPA_PSK";
        break;
    case WIFI_AUTH_WPA2_PSK:
         return "WPA2_PSK";
        break;
    case WIFI_AUTH_WPA_WPA2_PSK:
         return "WPA_WPA2_PSK";
        break;
    case WIFI_AUTH_WPA2_ENTERPRISE:
         return "WPA2_ENTERPRISE";
        break;
    case WIFI_AUTH_WPA3_PSK:
         return "WPA3_PSK";
        break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
         return "WPA2_WPA3_PSK";
        break;
    default:
         return "UNKNOWN";
        break;
    }
}

#endif