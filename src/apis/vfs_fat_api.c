/**
 * @file vfs_fat_api.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "vfs_fat_api.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_system.h"

static const char *TAG = "vfs_fat_api";

static wl_handle_t s_wl_handle = WL_INVALID_HANDLE;
const char *base_path = "/spiflash";

void vfs_fat_api_mount(){
    const esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = true,
        .allocation_unit_size = CONFIG_WL_SECTOR_SIZE
    };
    esp_err_t err = esp_vfs_fat_spiflash_mount(base_path, "storage", &mount_config, &s_wl_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount partition FATFS (%s)", esp_err_to_name(err));
    }else{
        ESP_LOGI(TAG, "FATFS partition successfully mounted.");
    }
}

int  vfs_fat_api_file_exists(char filename[32]){
    int ret;
    FILE *f = fopen(filename, "rb");
    ret = f != NULL;
    fclose(f);
    return ret;
}

void vfs_fat_api_write(char filename[32], char *content){
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open %s for write.", filename);
        return;
    }
    fprintf(f, content);
    fclose(f);
}

void vfs_fat_api_read(char filename[32], char *buf){
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open %s for write.", filename);
        return;
    }
    char  c;
    int idx=0;
    while (fscanf(f , "%c" ,&c) == 1) {
        buf[idx] = c;
        idx++;
    }
    buf[idx] = 0;
}

void vfs_fat_api_delete(char filename[32]){
    remove(filename);
}

void vfs_fat_api_unmount(){
    ESP_ERROR_CHECK(esp_vfs_fat_spiflash_unmount(base_path, s_wl_handle));
}