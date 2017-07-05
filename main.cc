#include <errno.h>
#include <glusterfs/api/glfs-handles.h>
#include <glusterfs/api/glfs.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstring>
#include <iostream>


int main(int argc, char *argv[]) {

    std::cout << "STARTING GLUSTER THREAD\n";

    const char *file_name = "/test5.txt";
    struct stat sb;
    int ret = -1;

    glfs_t *fs = glfs_new(argv[1]);

    ret = glfs_set_logging(fs, "./example.log", 9);

    ret = glfs_set_volfile_server(fs, "tcp", argv[2], 24007);

    if(ret != 0) {
      std::cout << "Failed to configure volume: (" << ret << ") " << strerror (errno) << "\n";
      return 1;
    }

    ret = glfs_init(fs);

    if(ret != 0) {
      std::cout << "Failed to connect to gluster volume: (" << ret << ") " << strerror (errno) << "\n";
      return 1;
    }

    std::cout << "Connected to gluster volume - creating test file..." << "\n";

    glfs_fd_t *fd = glfs_creat(fs, file_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if(fd) {
      std::cout << "File created!!!" << '\n';
    }
    else {
      std::cout << "Error: " << std::strerror(errno) << '\n';
    }

    ret = glfs_fini(fs);

    if(ret != 0) {
      std::cout << "Failed to disconnect from volume: (" << ret << ") " << strerror (errno) << "\n";
      return 1;
    }


}
