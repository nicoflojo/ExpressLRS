#include "targets.h"
#include <SPI.h>

/**
 * @brief An extension to the platform SPI class that provides some performance enhancements.
 *
 * 1. The provided data buffer is expected to be word-aligned and word-padded, this allow the
 *    data to be copied to the SPI fifo in word-sized chunks.
 * 2. The wait for non-busy is removed from the end of the write call so the processor can
 *    continue to do work while the SPI module is pumping the data from the FIFO to the external
 *    device.
 */
class SPIExClass : public SPIClass
{
public:
#if defined(PLATFORM_ESP32)
    explicit SPIExClass(uint8_t spi_bus=HSPI) : SPIClass(spi_bus) {}
#else
    explicit SPIExClass() : SPIClass() {}
#endif

    /**
     * @brief Perform an SPI read operation on the SPI bus.
     *
     * If the SPI bus is busy the processor waits for the current operation to complete before starting
     * this operation.
     * Once the SPI bus is free, the data is copied to the SPI fifo and the processor waits for the operation
     * to complete then copies the incoming data back into the provided data buffer.
     *
     * @param cs_mask mask of CS pins to enable for this operation
     * @param data word-aligned and padded data buffer
     * @param size the number of bytes to be read into in the data buffer
     */
    void inline ICACHE_RAM_ATTR read(uint8_t cs_mask, uint8_t *data, uint32_t size) { _transfer(cs_mask, data, size, true); }

    /**
     * @brief Perform an SPI write operation on the SPI bus.
     *
     * If the SPI bus is busy the processor waits for the current operation to complete before starting
     * this operation.
     * One the SPI bus is not busy, it copies the data to the SPI fifo then returns without waiting for
     * the operation to complete allowing the processor to do other work.
     *
     * @param cs_mask mask of CS pins to enable for this operation
     * @param data word-aligned and padded data buffer
     * @param size the number of bytes to be written to the SPI device
     */
    void inline ICACHE_RAM_ATTR write(uint8_t cs_mask, uint8_t * data, uint32_t size) { _transfer(cs_mask, data, size, false); }

    /**
     * @brief Enable software (bit-banged) chip-select instead of the SPI peripheral's hardware CS.
     *
     * The ESP32 hardware SPI chip-select does not reliably drive RTC-domain pads (e.g. GPIO0 =
     * XTAL_32K_P). When a radio's NSS is on such a pin the hardware CS never asserts and the device
     * reads back 0xFF. Providing the CS GPIOs here makes _transfer drive them with digitalWrite.
     * Pass -1 for an unused select. Default (both -1) keeps the hardware-CS behaviour unchanged.
     *
     * @param cs0 GPIO for CS bit0 (SX12XX_Radio_1), or -1
     * @param cs1 GPIO for CS bit1 (SX12XX_Radio_2), or -1
     */
    void setSoftwareCS(int8_t cs0, int8_t cs1) { _swCs0 = cs0; _swCs1 = cs1; }

private:
    int8_t _swCs0 = -1;
    int8_t _swCs1 = -1;
    void _transfer(uint8_t cs_mask, uint8_t *data, uint32_t size, bool reading);
};

extern SPIExClass SPIEx;
