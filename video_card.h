#ifndef _VIDEO_CARD_H_
#define _VIDEO_CARD_H_

/** @defgroup video_card
 * @{
 *
 * video card main functions
 */

/**
 * @brief Initializes the video module in graphics mode
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
int set_graphics_mode(uint16_t mode);

/**
 * @brief Functions that draws an xpm_image_t
 * 
 * @param map xpm_image_t that is gonna be draw
 * @param x x position of the image
 * @param y y position of the image
 * 
 * @return Return 0 upon success
 */
int use_xpm(xpm_image_t *map, uint16_t x, uint16_t y);

/**
 * @brief Function used to clean the screen to change images
 * 
 * @return Returns 0 upon success
 */
int clean_screen_and_draw();

/**
 * @brief Function that passes the information from the double buffer to the video memory
 */
void DBtoVM();

#endif
