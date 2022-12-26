#include "esp_vfs_fat.h" 

void setup() {
    sd_card_mount();
}

void loop() {
}

void sd_card_mount() {
  Serial.println("Initialising SD card");

  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

  host.flags = SDMMC_HOST_FLAG_1BIT;
  slot_config.width = 1;
  esp_vfs_fat_sdmmc_mount_config_t mount_config =  {
    .format_if_mount_failed = true,
    .max_files = 2,
    .allocation_unit_size = 64 * 1024
  };
  sdmmc_card_t *card;
  esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);

  if (ret == ESP_OK) {
    Serial.println("SD card ready");
  } else {
    Serial.println("SD card error ..!");
    mount_fix();
  }
}


void mount_fix() {
  Serial.println("Mount bug fixing...");
  esp_vfs_fat_sdmmc_unmount();
  Serial.println("Mount bug is fixed. Now rebooting..");
  delay(5000);
  ESP.restart();
}
