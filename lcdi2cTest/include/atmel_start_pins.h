/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <port.h>

/**
 * \brief Set PC4 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PC4_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(4, pull_mode);
}

/**
 * \brief Set PC4 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PC4_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(4, dir);
}

/**
 * \brief Set PC4 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PC4_set_level(const bool level)
{
	PORTC_set_pin_level(4, level);
}

/**
 * \brief Toggle output level on PC4
 *
 * Toggle the pin level
 */
static inline void PC4_toggle_level()
{
	PORTC_toggle_pin_level(4);
}

/**
 * \brief Get level on PC4
 *
 * Reads the level on a pin
 */
static inline bool PC4_get_level()
{
	return PORTC_get_pin_level(4);
}

/**
 * \brief Set PC5 pull mode
 *
 * Configure pin to pull up, down or disable pull mode, supported pull
 * modes are defined by device used
 *
 * \param[in] pull_mode Pin pull mode
 */
static inline void PC5_set_pull_mode(const enum port_pull_mode pull_mode)
{
	PORTC_set_pin_pull_mode(5, pull_mode);
}

/**
 * \brief Set PC5 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void PC5_set_dir(const enum port_dir dir)
{
	PORTC_set_pin_dir(5, dir);
}

/**
 * \brief Set PC5 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void PC5_set_level(const bool level)
{
	PORTC_set_pin_level(5, level);
}

/**
 * \brief Toggle output level on PC5
 *
 * Toggle the pin level
 */
static inline void PC5_toggle_level()
{
	PORTC_toggle_pin_level(5);
}

/**
 * \brief Get level on PC5
 *
 * Reads the level on a pin
 */
static inline bool PC5_get_level()
{
	return PORTC_get_pin_level(5);
}

#endif /* ATMEL_START_PINS_H_INCLUDED */
