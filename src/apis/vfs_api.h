/**
 * @file vfs_api.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __VFS_API__H__
#define __VFS_API__H__

#ifdef  VFS_FAT_API
#include "vfs_fat_api.h"
#else
#error "Selected API implementation not detected. Maybe, incorrect file was included."
#endif  //VFS_FAT_API

inline void vfs_mount();
inline int  vfs_file_exists(char filename[32]);
inline void vfs_write(char filename[32], char *content);
inline void vfs_read(char filename[32], char *buf);
inline void vfs_delete(char filename[32]);
inline void vfs_unmount();

/**
 * Interfacing selected API
 */

/**
 * @brief Mount vfs
 * 
 */
inline void vfs_mount(){
    #ifdef  VFS_FAT_API
    vfs_fat_api_mount();
    #endif  //VFS_FAT_API
}

/**
 * @brief Checks if file existes
 * 
 * @param filename file name 
 * @return int 1 if file exists 0 otherwise
 */
inline int  vfs_file_exists(char filename[32]){
    #ifdef  VFS_FAT_API
    return vfs_fat_file_api_exists(filename);
    #endif  //VFS_FAT_API
}

/**
 * @brief Write content to file
 * 
 * @param filename file name
 * @param content content
 */
inline void vfs_write(char filename[32], char *content){
    #ifdef  VFS_FAT_API
    return vfs_fat_api_write(filename, content);
    #endif  //VFS_FAT_API
}

/**
 * @brief Read file content
 * 
 * @param filename file name
 * @param buf buffer to read file content
 */
inline void vfs_read(char filename[32], char *buf){
    #ifdef  VFS_FAT_API
    return vfs_fat_api_read(filename, buf);
    #endif  //VFS_FAT_API
}

/**
 * @brief delete file
 * 
 * @param filename file name
 */
inline void vfs_delete(char filename[32]){
    #ifdef  VFS_FAT_API
    vfs_fat_api_delete(filename);
    #endif  //VFS_FAT_API
}

/**
 * @brief Unmount vfs
 * 
 */
inline void vfs_unmount(){
    #ifdef  VFS_FAT_API
    vfs_fat_api_unmount();
    #endif  //VFS_FAT_API
}

#endif  //!__VFS_API__H__