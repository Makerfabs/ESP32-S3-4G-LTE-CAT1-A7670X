#include <Arduino.h>

//HardwareSerial mySerial2(2);
#define DEBUG true

#include "FS.h"
#include <SD_MMC.h>
#include "SPI.h"

#define IO_RXD2 47
#define IO_TXD2 48


#define PIN_SD_CMD 11
#define PIN_SD_CLK 12
#define PIN_SD_D0 13

// change this to match your SD shield or module;
// ESP32-S3 4G LTE: pin 10


#define IO_GSM_PWRKEY 4
#define IO_GSM_RST    5

unsigned long currentTime;

void setup()
{
    USBSerial.begin(115200);
    delay(5000);
    SD_MMC.setPins(PIN_SD_CLK, PIN_SD_CMD, PIN_SD_D0);
    // bool begin(const char * mountpoint="/sdcard", bool mode1bit=false, bool format_if_mount_failed=false, int sdmmc_frequency=BOARD_MAX_SDMMC_FREQ, uint8_t maxOpenFiles = 5);
    if (!SD_MMC.begin("/sdcard", true, true))
    {
        USBSerial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD_MMC.cardType();

    if (cardType == CARD_NONE)
    {
        USBSerial.println("No SD_MMC card attached");
        return;
    }

    USBSerial.print("SD_MMC Card Type: ");
    if (cardType == CARD_MMC)
    {
        USBSerial.println("MMC");
    }
    else if (cardType == CARD_SD)
    {
        USBSerial.println("SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
        USBSerial.println("SDHC");
    }
    else
    {
        USBSerial.println("UNKNOWN");
    }

    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    USBSerial.printf("SD_MMC Card Size: %lluMB\n", cardSize);

    listDir(SD_MMC, "/", 0);
    listDir(SD_MMC, "/", 2);
    USBSerial.printf("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024));
    USBSerial.printf("Used space: %lluMB\n", SD_MMC.usedBytes() / (1024 * 1024));
}

void loop()
{
}

//------------------------------------------------------------------------

void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    USBSerial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        USBSerial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        USBSerial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            USBSerial.print("  DIR : ");
            USBSerial.println(file.name());
            if (levels)
            {
                listDir(fs, file.path(), levels - 1);
            }
        }
        else
        {
            USBSerial.print("  FILE: ");
            USBSerial.print(file.name());
            USBSerial.print("  SIZE: ");
            USBSerial.println(file.size());
        }
        file = root.openNextFile();
    }
}
