#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 255
#define REQ_PIPE_NAME "REQ_PIPE_47947"
#define RESP_PIPE_NAME "RESP_PIPE_47947"
#define SHARED_MEM_NAME "/01FdCUj"
#define ALIGNMENT_VALUE 3072
#define util_free(ptr) (util_free_internal((void**)(ptr)))

typedef enum { ERROR_NONE, ERROR_REQ_PIPE, ERROR_RESP_PIPE, ERROR_MEM_ALLOC, ERROR_INVALID_CMD, ERROR_FILE } ERROR_T;

#pragma pack(push, 1)
typedef struct _HEADER_STATIC {
    uint16_t magic;
    uint16_t header_size;
    uint16_t version;
    char no_of_sections;
} HEADER_STATIC_T;

typedef struct _HEADER_SECTION {
    char name[9];
    uint16_t type;
    uint32_t offset;
    uint32_t size;
} HEADER_SECTION_T;

typedef struct _HEADER {
    HEADER_STATIC_T static_header;
    HEADER_SECTION_T* sections;
} HEADER_T;
#pragma pack(pop)

typedef struct _SECTION {
    unsigned int size;
    unsigned int logical_offset;
    unsigned int page_start;
    unsigned int page_count;
} SECTION_T;

typedef struct ECHO_MESSAGE_REQ {
} ECHO_MESSAGE_REQ_T;

typedef struct CREATE_SHM_REQ {
    unsigned int size;
} CREATE_SHM_REQ_T;

typedef struct CREATE_SHM_RESP {
    char* status;
} CREATE_SHM_RESP_T;

typedef struct ECHO_MESSAGE_RESP {
    unsigned int number;
    char* variant;
} ECHO_MESSAGE_RESP_T;

typedef struct WRITE_SHM_REQ {
    unsigned int offset;
    unsigned int value;
} WRITE_SHM_REQ_T;

typedef struct WRITE_SHM_RESP {
    char* status;
} WRITE_SHM_RESP_T;

typedef struct MAP_FILE_REQ {
    char* file_name;
} MAP_FILE_REQ_T;

typedef struct MAP_FILE_RESP {
    char* status;
} MAP_FILE_RESP_T;

typedef struct READ_FILE_OFFSET_REQ {
    unsigned int offset;
    unsigned int byte_count;
} READ_FILE_OFFSET_REQ_T;

typedef struct READ_FILE_OFFSET_RESP {
    char* status;
} READ_FILE_OFFSET_RESP_T;

typedef struct READ_FILE_SECTION_REQ {
    unsigned int section;
    unsigned int offset;
    unsigned int byte_count;
} READ_FILE_SECTION_REQ_T;

typedef struct READ_FILE_SECTION_RESP {
    char* status;
} READ_FILE_SECTION_RESP_T;

typedef struct READ_LOGICAL_OFFSET_REQ {
    unsigned int offset;
    unsigned int byte_count;
} READ_LOGICAL_OFFSET_REQ_T;

typedef struct READ_LOGICAL_OFFSET_RESP {
    char* status;
} READ_LOGICAL_OFFSET_RESP_T;

typedef struct MESSAGE {
    char* cmd;
    union {
        ECHO_MESSAGE_REQ_T echo;
        CREATE_SHM_REQ_T create_shm;
        WRITE_SHM_REQ_T write_shm;
        MAP_FILE_REQ_T map_file;
        READ_FILE_OFFSET_REQ_T read_file_offset;
        READ_FILE_SECTION_REQ_T read_file_section;
        READ_LOGICAL_OFFSET_REQ_T read_logical_offset;
    } request;

    union {
        ECHO_MESSAGE_RESP_T echo;
        CREATE_SHM_RESP_T create_shm;
        WRITE_SHM_RESP_T write_shm;
        MAP_FILE_RESP_T map_file;
        READ_FILE_OFFSET_RESP_T read_file_offset;
        READ_FILE_SECTION_RESP_T read_file_section;
        READ_LOGICAL_OFFSET_RESP_T read_logical_offset;
    } response;
} MESSAGE_T;

typedef struct BIPIPE {
    int request_pipe;
    int response_pipe;
} BIPIPE_T;

typedef struct SHM {
    volatile void* shm;
    unsigned int size;
} SHM_T;

typedef struct FILE_T {
    char* file;
    int file_size;
} FILE_T;

bool running = true;
SHM_T shared_memory = {0};
FILE_T file = {0};

HEADER_T* header_extract(char* file_path);
void header_destroy(HEADER_T** header);

void util_error_present(ERROR_T error);
void util_free_internal(void** ptr);
BIPIPE_T* bipipe_create();
void bipipe_destroy(BIPIPE_T* pipe);
MESSAGE_T* bipipe_listen(BIPIPE_T* pipe);
void bipipe_respond(BIPIPE_T* pipe, MESSAGE_T* message);
void bipipe_message_compose(BIPIPE_T* pipe, MESSAGE_T* message);
void bipipe_message_destroy(MESSAGE_T* message);

bool execute_create_shm(unsigned int size);
bool execute_write_shm(unsigned int offset, unsigned int value);
bool execute_map_file(char* file_name);
bool execute_read_file_offset(unsigned int offset, unsigned int byte_count);
bool execute_read_file_section(unsigned int section, unsigned int offset, unsigned int byte_count);
bool execute_read_logical_offset(unsigned int offset, unsigned int byte_count);

HEADER_T* header_extract(char* file) {
    if (file == NULL) return NULL;

    HEADER_T* header = malloc(sizeof(HEADER_T));
    if (header == NULL) {
        fprintf(stderr, "Unable to allocate memory in %s\n", __func__);
        return NULL;
    }

    ERROR_T status = ERROR_NONE;

    do {
        memcpy(&(header->static_header), file, sizeof(HEADER_STATIC_T));

        HEADER_SECTION_T* sections =
            (HEADER_SECTION_T*)calloc(sizeof(HEADER_SECTION_T), header->static_header.no_of_sections);
        if (sections == NULL) {
            status = ERROR_MEM_ALLOC;
            fprintf(stderr, "Unable to allocate memory in %s\n", __func__);
            break;
        }

        int offset = sizeof(HEADER_STATIC_T);
        for (int i = 0; i < header->static_header.no_of_sections; i++) {
            memcpy(&sections[i], file + offset, sizeof(HEADER_SECTION_T));
            offset += sizeof(HEADER_SECTION_T);
        }

        header->sections = sections;

    } while (false);

    if (status != ERROR_NONE) {
        header_destroy(&header);
        header = NULL;
    }

    return header;
}

void header_destroy(HEADER_T** header) {
    if (header == NULL || *header == NULL) return;
    free((*header)->sections);
    (*header)->sections = NULL;
    free((*header));
    *header = NULL;
}

void util_error_present(ERROR_T error) {
    if (error == ERROR_NONE) return;

    printf("ERROR\n");
    switch (error) {
        case ERROR_MEM_ALLOC:
            printf("cannot allocate memory\n");
            break;
        case ERROR_REQ_PIPE:
            printf("cannot open the request pipe\n");
            break;
        case ERROR_RESP_PIPE:
            printf("cannot create the response pipe\n");
            break;
        default:
            break;
    }
}

void util_free_internal(void** ptr) {
    if (*ptr == NULL) return;
    free(*ptr);
    *ptr = NULL;
}

bool util_name_validate(char* cmd) {
    const char* cmds[] = {"ECHO#",
                          "CREATE_SHM#",
                          "WRITE_TO_SHM#",
                          "MAP_FILE#",
                          "READ_FROM_FILE_OFFSET#",
                          "READ_FROM_FILE_SECTION#",
                          "READ_FROM_LOGICAL_SPACE_OFFSET#"};

    const int names_count = sizeof(cmds) / sizeof(char*);

    bool valid = false;

    for (int i = 0; i < names_count; i++) {
        if (!strcmp(cmds[i], cmd)) {
            valid = true;
            break;
        }
    }

    return valid;
}

BIPIPE_T* bipipe_create() {
    ERROR_T err = ERROR_NONE;

    BIPIPE_T* pipe = NULL;

    do {
        pipe = (BIPIPE_T*)malloc(sizeof(BIPIPE_T));
        if (pipe == NULL) {
            err = ERROR_MEM_ALLOC;
            break;
        }

        if (mkfifo(RESP_PIPE_NAME, 0644) != 0) {
            err = ERROR_RESP_PIPE;
            break;
        }

        int fd_req = open(REQ_PIPE_NAME, O_RDONLY);
        if (fd_req < 0) {
            err = ERROR_REQ_PIPE;
            break;
        }

        int fd_resp = open(RESP_PIPE_NAME, O_WRONLY);
        if (fd_resp < 0) {
            err = ERROR_RESP_PIPE;
            break;
        }

        pipe->request_pipe = fd_req;
        pipe->response_pipe = fd_resp;
    } while (false);

    if (err != ERROR_NONE) {
        printf("destroyed pipe\n");
        bipipe_destroy(pipe);
        util_error_present(err);
        return NULL;
    }

    char* buf = strdup("CONNECT#");
    write(pipe->response_pipe, buf, 8);
    util_free(&buf);

    printf("SUCCESS\n");
    return pipe;
}

void bipipe_destroy(BIPIPE_T* pipe) {
    if (pipe == NULL) return;

    close(pipe->request_pipe);
    close(pipe->response_pipe);
    unlink(REQ_PIPE_NAME);
    unlink(RESP_PIPE_NAME);

    util_free(&pipe);
}

MESSAGE_T* bipipe_listen(BIPIPE_T* pipe) {
    char* buffer = (char*)calloc(MAX_BUFFER_SIZE, 1);
    char* c = malloc(sizeof(char));
    int index = 0;
    ERROR_T err = ERROR_NONE;
    MESSAGE_T* message = NULL;

    do {
        message = (MESSAGE_T*)calloc(sizeof(MESSAGE_T), 1);
        if (message == NULL) {
            err = ERROR_MEM_ALLOC;
            break;
        }

        do {
            read(pipe->request_pipe, c, 1);
            buffer[index++] = *c;
        } while (*c != '#');

        bool valid_command = util_name_validate(buffer);
        if (!valid_command) {
            err = ERROR_INVALID_CMD;
            break;
        }

        message->cmd = strdup(buffer);
        bipipe_message_compose(pipe, message);
    } while (false);

    util_free(&buffer);
    if (err != ERROR_NONE) {
        return NULL;
    }

    return message;
};

void bipipe_respond(BIPIPE_T* pipe, MESSAGE_T* message) {
    if (message == NULL) return;

    if (!strcmp(message->cmd, "ECHO#")) {
        write(pipe->response_pipe, message->cmd, 5);                                       // ECHO#
        write(pipe->response_pipe, &message->response.echo.number, sizeof(unsigned int));  // NR
        write(pipe->response_pipe, message->response.echo.variant, 8);                     // VARIANT#
    } else if (!strcmp(message->cmd, "EXIT#")) {
        running = false;
    } else if (!strcmp(message->cmd, "CREATE_SHM#")) {
        write(pipe->response_pipe, message->cmd, 11);
        write(pipe->response_pipe, message->response.create_shm.status, strlen(message->response.create_shm.status));
    } else if (!strcmp(message->cmd, "WRITE_TO_SHM#")) {
        write(pipe->response_pipe, message->cmd, 13);
        write(pipe->response_pipe, message->response.write_shm.status, strlen(message->response.write_shm.status));
    } else if (!strcmp(message->cmd, "MAP_FILE#")) {
        write(pipe->response_pipe, message->cmd, 9);
        write(pipe->response_pipe, message->response.map_file.status, strlen(message->response.map_file.status));
    } else if (!strcmp(message->cmd, "READ_FROM_FILE_OFFSET#")) {
        write(pipe->response_pipe, message->cmd, 22);
        write(pipe->response_pipe, message->response.read_file_offset.status,
              strlen(message->response.read_file_offset.status));
    } else if (!strcmp(message->cmd, "READ_FROM_FILE_SECTION#")) {
        write(pipe->response_pipe, message->cmd, 23);
        write(pipe->response_pipe, message->response.read_file_section.status,
              strlen(message->response.read_file_section.status));
    } else if (!strcmp(message->cmd, "READ_FROM_LOGICAL_SPACE_OFFSET#")) {
        write(pipe->response_pipe, message->cmd, 31);
        write(pipe->response_pipe, message->response.read_logical_offset.status,
              strlen(message->response.read_logical_offset.status));
    }
}

void bipipe_message_compose(BIPIPE_T* pipe, MESSAGE_T* message) {
    if (message == NULL) return;

    if (!strcmp(message->cmd, "ECHO#")) {
        message->response.echo.number = 47947;
        message->response.echo.variant = strdup("VARIANT#");
    } else if (!strcmp(message->cmd, "CREATE_SHM#")) {
        unsigned int size = 0;
        read(pipe->request_pipe, &size, sizeof(unsigned int));
        message->request.create_shm.size = size;
        bool status = execute_create_shm(size);
        if (status) {
            message->response.create_shm.status = strdup("SUCCESS#");
        } else {
            message->response.create_shm.status = strdup("ERROR#");
        }
    } else if (!strcmp(message->cmd, "WRITE_TO_SHM#")) {
        unsigned int offset = 0;
        unsigned int value = 0;
        read(pipe->request_pipe, &offset, sizeof(unsigned int));
        read(pipe->request_pipe, &value, sizeof(unsigned int));
        message->request.write_shm.offset = offset;
        message->request.write_shm.value = value;
        bool status = execute_write_shm(offset, value);
        if (status) {
            message->response.write_shm.status = strdup("SUCCESS#");
        } else {
            message->response.write_shm.status = strdup("ERROR#");
        }
    } else if (!strcmp(message->cmd, "MAP_FILE#")) {
        char* buffer = (char*)calloc(MAX_BUFFER_SIZE, 1);
        char c;
        int index = 0;

        do {
            read(pipe->request_pipe, &c, 1);
            buffer[index++] = c;
        } while (c != '#');
        buffer[index - 1] = '\0';
        message->request.map_file.file_name = strdup(buffer);
        bool status = execute_map_file(message->request.map_file.file_name);
        if (status) {
            message->response.map_file.status = strdup("SUCCESS#");
        } else {
            message->response.map_file.status = strdup("ERROR#");
        }
        util_free(&buffer);
    } else if (!strcmp(message->cmd, "READ_FROM_FILE_OFFSET#")) {
        unsigned int offset = 0;
        unsigned int byte_count = 0;
        read(pipe->request_pipe, &offset, sizeof(unsigned int));
        read(pipe->request_pipe, &byte_count, sizeof(unsigned int));
        message->request.read_file_offset.offset = offset;
        message->request.read_file_offset.byte_count = byte_count;

        bool status = execute_read_file_offset(offset, byte_count);
        if (status) {
            message->response.read_file_offset.status = strdup("SUCCESS#");
        } else {
            message->response.read_file_offset.status = strdup("ERROR#");
        }
    } else if (!strcmp(message->cmd, "READ_FROM_FILE_SECTION#")) {
        unsigned int section = 0;
        unsigned int offset = 0;
        unsigned int byte_count = 0;
        read(pipe->request_pipe, &section, sizeof(unsigned int));
        read(pipe->request_pipe, &offset, sizeof(unsigned int));
        read(pipe->request_pipe, &byte_count, sizeof(unsigned int));
        message->request.read_file_section.section = section;
        message->request.read_file_section.offset = offset;
        message->request.read_file_section.byte_count = byte_count;

        bool status = execute_read_file_section(section, offset, byte_count);
        if (status) {
            message->response.read_file_section.status = strdup("SUCCESS#");
        } else {
            message->response.read_file_section.status = strdup("ERROR#");
        }
    } else if (!strcmp(message->cmd, "READ_FROM_LOGICAL_SPACE_OFFSET#")) {
        unsigned int offset = 0;
        unsigned int byte_count = 0;
        read(pipe->request_pipe, &offset, sizeof(unsigned int));
        read(pipe->request_pipe, &byte_count, sizeof(unsigned int));
        message->request.read_logical_offset.offset = offset;
        message->request.read_logical_offset.byte_count = byte_count;

        bool status = execute_read_logical_offset(offset, byte_count);
        if (status) {
            message->response.read_file_section.status = strdup("SUCCESS#");
        } else {
            message->response.read_file_section.status = strdup("ERROR#");
        }
    }
}

void bipipe_message_destroy(MESSAGE_T* message) {
    if (message == NULL) return;
    if (!strcmp(message->cmd, "ECHO#")) {
        util_free(&message->response.echo.variant);
    } else if (!strcmp(message->cmd, "CREATE_SHM#")) {
        util_free(&message->response.create_shm.status);
    } else if (!strcmp(message->cmd, "WRITE_TO_SHM#")) {
        util_free(&message->response.write_shm.status);
    } else if (!strcmp(message->cmd, "MAP_FILE#")) {
        util_free(&message->request.map_file.file_name);
        util_free(&message->response.map_file.status);
    } else if (!strcmp(message->cmd, "READ_FROM_FILE_OFFSET#")) {
        util_free(&message->response.read_file_offset.status);
    } else if (!strcmp(message->cmd, "READ_FROM_FILE_SECTION#")) {
        util_free(&message->response.read_file_section.status);
    } else if (!strcmp(message->cmd, "READ_FROM_LOGICAL_SPACE_OFFSET#")) {
        util_free(&message->response.read_logical_offset.status);
    }
    util_free(&message->cmd);
}

bool execute_create_shm(unsigned int size) {
    if (shared_memory.shm != NULL) {
        munmap((void*)shared_memory.shm, shared_memory.size);
        util_free(&shared_memory.shm);
        shared_memory.size = 0;
    }

    bool success = true;

    do {
        int fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0664);
        if (fd < 0) {
            success = false;
            break;
        }
        ftruncate(fd, size);
        shared_memory.shm = (volatile void*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (shared_memory.shm == (void*)-1) {
            success = false;
            close(fd);
            break;
        }
        shared_memory.size = size;
    } while (false);

    return success;
}

bool execute_write_shm(unsigned int offset, unsigned int value) {
    if (shared_memory.shm == NULL) return false;
    if (offset > shared_memory.size) return false;
    if (offset + sizeof(unsigned int) > shared_memory.size) return false;

    *((volatile unsigned int*)(shared_memory.shm + offset)) = value;

    return true;
}

bool execute_map_file(char* file_name) {
    if (file_name == NULL) return false;
    if (file.file != NULL) {
        munmap(file.file, file.file_size);
        util_free(&file.file);
        file.file_size = 0;
    }

    int fd = open(file_name, O_RDONLY);
    if (fd == -1) {
        return false;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    file.file = (char*)mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file.file == (void*)-1) {
        close(fd);
        return false;
    }

    file.file_size = (unsigned int)size;

    close(fd);
    return true;
}

bool execute_read_file_offset(unsigned int offset, unsigned int byte_count) {
    if (shared_memory.shm == NULL) return false;
    if (byte_count > shared_memory.size) return false;
    if (file.file == NULL) return false;
    if (offset + byte_count > file.file_size) return false;

    memcpy((void*)shared_memory.shm, file.file + offset, byte_count);

    return true;
}

bool execute_read_file_section(unsigned int section, unsigned int offset, unsigned int byte_count) {
    if (shared_memory.shm == NULL) return false;
    if (byte_count > shared_memory.size) return false;
    if (file.file == NULL) return false;

    HEADER_T* header = header_extract(file.file);

    if (section - 1 > header->static_header.no_of_sections) return false;
    if (offset + byte_count > header->sections[section - 1].size) return false;

    memcpy((void*)(shared_memory.shm), file.file + header->sections[section - 1].offset + offset, byte_count);
    header_destroy(&header);
    return true;
}

bool execute_read_logical_offset(unsigned int offset, unsigned int byte_count) {
    if (shared_memory.shm == NULL) return false;
    if (file.file == NULL) return false;

    HEADER_T* header = header_extract(file.file);

    SECTION_T sections[header->static_header.no_of_sections];
    unsigned int pages_so_far = 0;
    for (int i = 0; i < header->static_header.no_of_sections; i++) {
        sections[i].size = header->sections[i].size;
        sections[i].page_count = sections[i].size / ALIGNMENT_VALUE + 1;
        sections[i].page_start = pages_so_far;
        pages_so_far += sections[i].page_count;
        sections[i].logical_offset = sections[i].page_start * ALIGNMENT_VALUE;
    }

    unsigned int cursor = 0;
    for (int i = 0; i < header->static_header.no_of_sections; i++) {
        int s_start = sections[i].logical_offset;
        int s_end = (sections[i].page_start + sections[i].page_count) * ALIGNMENT_VALUE;
        int o_start = offset;
        int o_end = offset + byte_count;

        if ((s_start < o_end) && (o_start < s_end)) {
            unsigned int read_start = (o_start > s_start) ? o_start : s_start;
            unsigned int read_end = (o_end < s_end) ? o_end : s_end;
            unsigned int read_size = read_end - read_start;


            //TODO: No checks if the interval is outside section data (so, inside the alignment padding)
            //      or if it's partially outside

            
            //unsigned int left = read_start - s_start;
            //unsigned int size = left + read_size > header->sections[i].size ? header->sections[i].size - left: read_size;

            // If it's outsize section content (that means it's inside the padding)
            // if (read_start - s_start > header->sections[i].size) {
            //     memset((void*)shared_memory.shm + cursor, 0, read_size);
            // } else {
            //     memcpy((void*)shared_memory.shm + cursor, file.file + left, size);
            // }
            //printf("%s\n", shared_memory.shm);
            memcpy((void*)shared_memory.shm + cursor, file.file + header->sections[i].offset + read_start - s_start,
                   read_size);
            cursor += read_size;
        }
    }

    return true;
}

int main() {
    BIPIPE_T* pipe = bipipe_create();
    while (running) {
        MESSAGE_T* msg = bipipe_listen(pipe);
        bipipe_respond(pipe, msg);
        printf("%s\n", msg->cmd);
        bipipe_message_destroy(msg);
    }
    bipipe_destroy(pipe);
    // FREE SHARED MEMORY, FILE IF CREATED
    munmap(file.file, file.file_size);
    munmap((void*)shared_memory.shm, shared_memory.size);
    return 0;
}