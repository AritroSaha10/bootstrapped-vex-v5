#include "sdReadUtil.h"

typedef FILE* pc_file_t;

lv_fs_res_t SDReadUtil::pcfs_open(void* file_p, const char *fn, lv_fs_mode_t mode) {
    errno = 0;
    const char *flags = "";

    // Convert the file access mode
    if (mode == LV_FS_MODE_WR)
        flags = "wb";
    else if (mode == LV_FS_MODE_RD)
        flags = "rb";
    else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
        flags = "a+";

    // Open the file
    char buf[256];
    sprintf(buf, "/%s", fn);
    pc_file_t f = fopen(buf, flags);

    if (f == NULL) {
        // File open failed
        return LV_FS_RES_UNKNOWN;
    }
    else {
        // Load the file and change the file pointer
        fseek(f, 0, SEEK_SET);
        pc_file_t* fp = (pc_file_t*) file_p;
        *fp = f;
    }

    return LV_FS_RES_OK;
}

lv_fs_res_t SDReadUtil::pcfs_close(void* file_p) {
    pc_file_t* fp = (pc_file_t*) file_p;
    fclose(*fp);
    return LV_FS_RES_OK;
}

lv_fs_res_t SDReadUtil::pcfs_read(void* file_p, void* buf, uint32_t btr, uint32_t* br) {
    pc_file_t* fp = (pc_file_t*) file_p;
    *br = fread(buf, 1, btr, *fp);
    return LV_FS_RES_OK;
}

lv_fs_res_t SDReadUtil::pcfs_seek(void* file_p, uint32_t pos) {
    pc_file_t* fp = (pc_file_t*) file_p;
    fseek(*fp, pos, SEEK_SET);
    return LV_FS_RES_OK;
}

lv_fs_res_t SDReadUtil::pcfs_tell(void* file_p, uint32_t *pos_p) {
    pc_file_t* fp = (pc_file_t*) file_p;
    *pos_p = ftell(*fp);
    return LV_FS_RES_OK;
}