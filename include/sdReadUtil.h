/**
 * \file sdReadUtil.h
 * 
 * \brief Utility functions for reading files off the SD card for LVGL.
*/

#include "main.h"

namespace SDReadUtil
{
    typedef FILE* pc_file_t;

    /**
     * \brief Open a file
     * @param file_p The file pointer to write to
     * @param filename The file name
     * @param mode The file open mode
     * @return LV_FS_RES_UNKNOWN if the file could not be opened, or LV_FS_RES_OK if the file was opened
    */
    lv_fs_res_t pcfs_open(void* file_p, const char* fn, lv_fs_mode_t mode);

    /**
     * \brief Close a file
     * @param file_p The file pointer
     * @return LV_FS_RES_OK after the file is closed
    */
    lv_fs_res_t pcfs_close(void* file_p);

    /**
     * \brief Read a file to a buffer
     * @param file_p The file pointer
     * @param buf The buffer to read to
     * @param btr The number of bytes to read
     * @param br The number of bytes read
     * @return LV_FS_RES_OK after the file is read, as well as the contents in the buffer
    */
    lv_fs_res_t pcfs_read(void* file_p, void* buf, uint32_t btr, uint32_t* br);

    /**
     * \brief Seek a file
     * @param file_p The file pointer
     * @param pos The position to seek to
     * @return LV_FS_RES_OK after the position is seeked
    */
    lv_fs_res_t pcfs_seek(void* file_p, uint32_t pos);

    /**
     * \brief Get the current position in a file
     * @param file_p The file pointer
     * @param pos_p The position
     * @return LV_FS_RES_OK after the position is set
    */
    lv_fs_res_t pcfs_tell(void* file_p, uint32_t* pos_p);
}