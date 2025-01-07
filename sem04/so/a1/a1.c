#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
/*Commands:                                                     Impl.   Tests
variant                                                         DONE    DONE
list [recursive] <filtering_options> path=<dir_path>            DONE    DONE
    filtering options are:
        name_ends_with=string
        has_perm_write
parse path=<file_path>                                          DONE    DONE
extract path=<file_path> section=<sect_nr> line=<line_nr>       DONE
findall path=<dir_path>                                         DONE
*/

// TODO: Arguments can take arbitrary number of equal signs and still be valid.
//       EG: path=============f.txt
//       Fix if needed, count equal signs or play with strtok more.
// TODO: If, in the case of an argument that has multiple equal signs, it doesnt
//       throw an error; it just ignores the rest (eg. path=test=gghh will be valid
//       and the value will just be "test")

#define MAX_TOKENS 32
#define MAX_PATH 1024

typedef enum STATUS_ENUM
{
    FAIL,
    SUCCESS
} STATUS;

typedef enum COMMAND_TYPES_ENUM
{
    CMD_INVALID,
    CMD_VARIANT,
    CMD_LIST,
    CMD_PARSE,
    CMD_EXTRACT,
    CMD_FINDALL
} COMMAND_TYPE;

typedef struct _COMMAND_VARIANT_T
{
    char *option;
} COMMAND_VARIANT_T;

typedef struct _COMMAND_PARSE_T
{
    char *option;
    char *path;
} COMMAND_PARSE_T;

typedef struct _COMMAND_FINDALL_T
{
    char *option;
    char *path;
} COMMAND_FINDALL_T;

typedef struct _COMMAND_EXTRACT_T
{
    char *option;
    char *path;
    int section;
    int line;
} COMMAND_EXTRACT_T;

typedef struct _COMMAND_LIST_T
{
    char *option;
    bool is_recursive;
    char *path;
    bool is_write_perm;
    char *suffix;
} COMMAND_LIST_T;

typedef struct _COMMAND
{
    COMMAND_TYPE cmd;
    union
    {
        COMMAND_VARIANT_T cmd_variant;
        COMMAND_LIST_T cmd_list;
        COMMAND_PARSE_T cmd_parse;
        COMMAND_EXTRACT_T cmd_extract;
        COMMAND_FINDALL_T cmd_findall;
    };
} COMMAND_T;

#pragma pack(push, 1)
typedef struct _HEADER_STATIC
{
    uint16_t magic;
    uint16_t header_size;
    uint16_t version;
    char no_of_sections;
} HEADER_STATIC_T;

typedef struct _HEADER_SECTION
{
    char name[9];
    uint16_t type;
    uint32_t offset;
    uint32_t size;
} HEADER_SECTION_T;

typedef struct _HEADER
{
    HEADER_STATIC_T static_header;
    HEADER_SECTION_T *sections;
} HEADER_T;
#pragma pack(pop)

typedef struct _SECTION
{
    int line_count;
    char **lines;
} SECTION_T;

char **tokenized_string_create(char *string, int *out_count, char *delimiter);
void tokenized_string_destroy(char ***tokens, int count);
char *extract_value(char *key_value_str);

bool header_validate(HEADER_T *header, bool is_verbose);
HEADER_T *header_extract(char *file_path);
void header_destroy(HEADER_T **header);
void list_directory(char *path, COMMAND_T *command);
void list_directory_conditioned(char *path, COMMAND_T *command);

SECTION_T *section_create(char *file_path, int section_idx);
void section_destroy(SECTION_T **section);

COMMAND_T *argument_parser();
COMMAND_T *command_create(char *option, int argc, char **argv);
void command_destroy(COMMAND_T **command);

void command_interpret(COMMAND_T *command);
void command_parse(COMMAND_T *command);
void command_list(COMMAND_T *command);
void command_extract(COMMAND_T *command);
void command_findall(COMMAND_T *command);

char **tokenized_string_create(char *string, int *out_count, char *delimiter)
{
    char **substrings = (char **)malloc(MAX_TOKENS * sizeof(char *));

    if (substrings == NULL)
    {
        fprintf(stderr, "Memory allocation failed in %s.", __func__);
        exit(-1);
    }

    int capacity = MAX_TOKENS;

    STATUS status = SUCCESS;

    do
    {
        char *token = strtok(string, delimiter);
        *out_count = 0;

        while (token != NULL)
        {
            if (*out_count > capacity)
            {
                capacity *= 2;
                substrings = (char **)realloc(substrings, capacity * sizeof(char *));
            }

            substrings[*out_count] = (char *)calloc((strlen(token) + 1), sizeof(char));

            if (substrings[*out_count] == NULL)
            {
                status = FAIL;
                break;
            }

            strcpy(substrings[*out_count], token);
            (*out_count)++;
            token = strtok(NULL, delimiter);
        }
    } while (false);

    if (status == FAIL)
    {
        tokenized_string_destroy(&substrings, *out_count);
        (*out_count) = 0;
        return NULL;
    }

    return substrings;
}

void tokenized_string_destroy(char ***tokens_ptr, int count)
{
    if (tokens_ptr == NULL || *tokens_ptr == NULL)
        return;

    for (int i = 0; i < count; i++)
    {
        if ((*tokens_ptr)[i] != NULL)
        {
            free((*tokens_ptr)[i]);
            (*tokens_ptr)[i] = NULL;
        }
    }
    free(*tokens_ptr);
    *tokens_ptr = NULL;
}

char *extract_value(char *key_value_str)
{
    if (key_value_str == NULL)
        return NULL;
    char *key = strtok(key_value_str, "=");
    if (key == NULL)
        return NULL;
    return strtok(NULL, "=");
}

bool header_validate(HEADER_T *header, bool is_verbose)
{
    HEADER_STATIC_T *static_header = &(header->static_header);
    if (static_header->magic != (uint16_t)0x656E)
    {
        if (is_verbose)
            printf("ERROR\nwrong magic\n");
        return false;
    }
    if (!(static_header->version >= 57 && static_header->version <= 108))
    {
        if (is_verbose)
            printf("ERROR\nwrong version\n");
        return false;
    }
    if (!(static_header->no_of_sections == 2 ||
          (static_header->no_of_sections >= 4 &&
           static_header->no_of_sections <= 14)))
    {
        if (is_verbose)
            printf("ERROR\nwrong sect_nr\n");
        return false;
    }

    for (int i = 0; i < static_header->no_of_sections; i++)
    {
        if ((header->sections[i].type != 89 &&
             header->sections[i].type != 39 &&
             header->sections[i].type != 17))
        {
            if (is_verbose)
                printf("ERROR\nwrong sect_types\n");
            return false;
        }
    }

    return true;
}

HEADER_T *header_extract(char *file_path)
{
    if (file_path == NULL)
        return NULL;

    int fd = open(file_path, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "ERROR\ninvalid file path\n");
        return NULL;
    }

    HEADER_T *header = malloc(sizeof(HEADER_T));
    if (header == NULL)
    {
        fprintf(stderr, "Unable to allocate memory in %s\n", __func__);
        return NULL;
    }

    STATUS status = SUCCESS;

    do
    {
        HEADER_STATIC_T static_header = {0};
        int bytes_read = read(fd, &static_header, sizeof(HEADER_STATIC_T));

        if (bytes_read < sizeof(HEADER_STATIC_T))
        {
            fprintf(stderr, "ERROR\nfile too small\n");
            status = FAIL;
            break;
        }

        memcpy(&(header->static_header), &static_header, sizeof(HEADER_STATIC_T));

        HEADER_SECTION_T *sections = (HEADER_SECTION_T *)calloc(sizeof(HEADER_SECTION_T), static_header.no_of_sections);
        if (sections == NULL)
        {
            status = FAIL;
            fprintf(stderr, "Unable to allocate memory in %s\n", __func__);
            break;
        }

        for (int i = 0; i < static_header.no_of_sections; i++)
        {
            bytes_read = read(fd, &sections[i], sizeof(HEADER_SECTION_T));
            if (bytes_read < sizeof(HEADER_SECTION_T))
            {
                free(sections);
                sections = NULL;
                fprintf(stderr, "ERROR\nfile too small\n");
                status = FAIL;
                break;
            }
        }

        header->sections = sections;

    } while (false);

    if (status == FAIL)
    {
        header_destroy(&header);
        header = NULL;
    }
    close(fd);

    return header;
};

void header_destroy(HEADER_T **header)
{
    if (header == NULL || *header == NULL)
        return;
    free((*header)->sections);
    (*header)->sections = NULL;
    free((*header));
    *header = NULL;
}

void list_directory(char *path, COMMAND_T *command)
{
    if (command == NULL || path == NULL)
        return;
    DIR *directory = NULL;
    struct dirent *entry = NULL;

    directory = opendir(path);
    if (directory == NULL)
    {
        // printf("ERROR\ninvalid directory path\n");
        return;
    }

    // printf("SUCCESS\n");

    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        struct stat file_stat = {0};
        char cpath[2 * MAX_PATH] = {0};
        char cwd[MAX_PATH] = {0};
        getcwd(cwd, MAX_PATH);
        snprintf(cpath, 2 * MAX_PATH, "%s/%s/%s", cwd, path, entry->d_name);
        stat(cpath, &file_stat);

        if (command->cmd_list.suffix != NULL)
        {
            size_t file_name_size = strlen(entry->d_name);
            size_t suffix_size = strlen(command->cmd_list.suffix);

            if (file_name_size < suffix_size)
                continue;
            if (strcmp(entry->d_name + file_name_size - suffix_size, command->cmd_list.suffix) != 0)
                continue;
        }

        if (command->cmd_list.is_write_perm)
        {
            if ((file_stat.st_mode & S_IWUSR) == 0)
                continue;
        }

        printf("%s/%s\n", path, entry->d_name);

        if (command->cmd_list.is_recursive)
        {
            if (S_ISDIR(file_stat.st_mode))
            {
                char next_path[MAX_PATH];
                snprintf(next_path, sizeof(next_path), "%s/%s", path, entry->d_name);
                list_directory(next_path, command);
            }
        }
    }

    closedir(directory);
}

void list_directory_conditioned(char *path, COMMAND_T *command)
{
    if (command == NULL || path == NULL)
        return;
    DIR *directory = NULL;
    struct dirent *entry = NULL;

    directory = opendir(path);
    if (directory == NULL)
    {
        return;
    }

    while ((entry = readdir(directory)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        struct stat file_stat = {0};
        char cpath[2 * MAX_PATH] = {0};
        char cwd[MAX_PATH] = {0};
        getcwd(cwd, MAX_PATH);
        snprintf(cpath, 2 * MAX_PATH, "%s/%s/%s", cwd, path, entry->d_name);
        stat(cpath, &file_stat);

        char next_path[MAX_PATH];
        snprintf(next_path, sizeof(next_path), "%s/%s", path, entry->d_name);

        if (S_ISDIR(file_stat.st_mode))
        {
            list_directory_conditioned(next_path, command);
        }
        else
        {
            HEADER_T *header = header_extract(next_path);
            if (header == NULL)
                continue;
            if (!header_validate(header, false))
            {
                header_destroy(&header);
                continue;
            }
            int valid_section_count = 0;

            for (int i = 0; i < header->static_header.no_of_sections; i++)
            {
                SECTION_T *section = section_create(next_path, i);
                if (section == NULL)
                    continue;
                if (section->line_count == 15)
                    valid_section_count++;
                section_destroy(&section);
            }

            header_destroy(&header);
            if (valid_section_count >= 3)
                printf("%s/%s\n", path, entry->d_name);
        }
    }

    closedir(directory);
}

SECTION_T *section_create(char *file_path, int section_idx)
{
    if (file_path == NULL)
        return NULL;

    int fd = open(file_path, O_RDONLY);
    if (fd == -1)
    {
        return NULL;
    }

    HEADER_T *header = header_extract(file_path);
    if (header == NULL)
        return NULL;
    if (!header_validate(header, false))
    {
        header_destroy(&header);
        return NULL;
    }

    STATUS status = SUCCESS;
    char *buffer = (char *)malloc(sizeof(char) * (header->sections[section_idx].size + 1));
    SECTION_T *section = (SECTION_T *)calloc(sizeof(SECTION_T), 1);

    do
    {
        lseek(fd, header->sections[section_idx].offset, SEEK_SET);

        int bytes_read = read(fd, buffer, header->sections[section_idx].size);
        if (bytes_read < header->sections[section_idx].size)
        {
            status = FAIL;
            break;
        }

        buffer[header->sections[section_idx].size] = '\0';

        int count = 0;
        section->lines = tokenized_string_create(buffer, &count, "\n");
        section->line_count = count;
    } while (false);

    header_destroy(&header);
    close(fd);
    free(buffer);

    if (status == FAIL)
    {
        free(section);
        section = NULL;
    }

    return section;
}

void section_destroy(SECTION_T **section)
{
    if (section == NULL || *section == NULL)
        return;
    tokenized_string_destroy(&((*section)->lines), (*section)->line_count);
    free(*section);
    *section = NULL;
}

COMMAND_T *argument_parser(int argc, char **argv)
{
    if (argc < 2)
        return NULL;

    STATUS status = FAIL;

    const char *commands[] = {"variant", "parse", "findall", "extract", "list"};
    const int commands_count = sizeof(commands) / sizeof(char *);

    int found_idx = -1;

    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < commands_count; j++)
        {
            if (strcmp(argv[i], commands[j]) == 0)
            {
                status = SUCCESS;
                found_idx = j;
                break;
            }
        }
        if (status == SUCCESS)
            break;
    }

    if (status == FAIL)
        return NULL;

    return command_create((char *)commands[found_idx], argc, argv);
}

COMMAND_T *command_create(char *option, int argc, char **argv)
{
    COMMAND_T *command = (COMMAND_T *)calloc(sizeof(COMMAND_T), 1);

    if (command == NULL)
    {
        fprintf(stderr, "Cannot allocate memory in %s.", __func__);
        exit(-1);
    }

    STATUS status = FAIL;

    // switch needs integral type, sorry :(
    if (strcmp(option, "variant") == 0)
    {
        command->cmd = CMD_VARIANT;
        command->cmd_variant.option = strdup(option);
        status = SUCCESS;
    }
    else if (strcmp(option, "list") == 0)
    {
        command->cmd = CMD_LIST;
        command->cmd_list.is_recursive = false;
        command->cmd_list.is_write_perm = false;
        command->cmd_list.suffix = NULL;

        bool has_recursive = false;
        bool has_write_perm = false;
        bool has_suffix = false;
        bool has_path = false;

        for (int i = 1; i < argc; i++)
        {
            if (strstr(argv[i], "recursive") != NULL)
            {
                if (has_recursive)
                {
                    status = FAIL;
                    break;
                }

                has_recursive = true;
                status = SUCCESS;

                command->cmd_list.is_recursive = true;
            }
            else if (strstr(argv[i], "has_perm_write") != NULL)
            {
                if (has_write_perm)
                {
                    status = FAIL;
                    break;
                }

                has_write_perm = true;
                status = SUCCESS;

                command->cmd_list.is_write_perm = true;
            }
            else if (strstr(argv[i], "path=") != NULL)
            {
                if (has_path)
                {
                    status = FAIL;
                    break;
                }

                has_path = true;
                status = SUCCESS;

                char *arg = extract_value(argv[i]);

                if (arg == NULL || strlen(arg) < 1)
                {
                    status = FAIL;
                    break;
                }

                command->cmd_list.path = strdup(arg);
            }
            else if (strstr(argv[i], "name_ends_with=") != NULL)
            {
                if (has_suffix)
                {
                    status = FAIL;
                    break;
                }

                has_suffix = true;
                status = SUCCESS;

                char *arg = extract_value(argv[i]);

                if (arg == NULL || strlen(arg) < 1)
                {
                    status = FAIL;
                    break;
                }

                command->cmd_list.suffix = strdup(arg);
            }
        }

        if (status == SUCCESS)
        {
            command->cmd_list.option = strdup(option);
        }
        else
        {
            command->cmd_list.option = NULL;
        }
    }
    else if (strcmp(option, "parse") == 0)
    {
        command->cmd = CMD_PARSE;
        bool has_path = false;

        for (int i = 1; i < argc; i++)
        {
            if (strstr(argv[i], "path=") != NULL)
            {
                if (has_path)
                {
                    status = FAIL;
                    break;
                }

                has_path = true;
                status = SUCCESS;

                char *arg = extract_value(argv[i]);

                if (arg == NULL || strlen(arg) < 1)
                {
                    status = FAIL;
                    break;
                }

                command->cmd_parse.path = strdup(arg);
                command->cmd_parse.option = strdup(option);
            }
        }
    }
    else if (strcmp(option, "extract") == 0)
    {
        command->cmd = CMD_EXTRACT;

        bool has_path = false;
        bool has_section = false;
        bool has_line = false;

        for (int i = 1; i < argc; i++)
        {
            if (strstr(argv[i], "path=") != NULL)
            {
                if (has_path)
                {
                    status = FAIL;
                    break;
                }
                has_path = true;

                if (has_path && has_section && has_line)
                    status = SUCCESS;

                char *arg = extract_value(argv[i]);

                if (arg == NULL || strlen(arg) < 1)
                {
                    status = FAIL;
                    break;
                }

                command->cmd_extract.path = strdup(arg);
            }
            else if (strstr(argv[i], "section=") != NULL)
            {
                if (has_section)
                {
                    status = FAIL;
                    break;
                }
                has_section = true;

                if (has_path && has_section && has_line)
                    status = SUCCESS;

                char *arg = extract_value(argv[i]);

                if (arg == NULL || strlen(arg) < 1)
                {
                    status = FAIL;
                    break;
                }

                int section = atoi(arg);
                if (section == 0)
                {
                    status = FAIL;
                    break;
                }

                command->cmd_extract.section = section;
            }
            else if (strstr(argv[i], "line=") != NULL)
            {
                if (has_line)
                {
                    status = FAIL;
                    break;
                }
                has_line = true;

                if (has_path && has_section && has_line)
                    status = SUCCESS;

                char *arg = extract_value(argv[i]);

                if (arg == NULL || strlen(arg) < 1)
                {
                    status = FAIL;
                    break;
                }

                int line = atoi(arg);
                if (line == 0)
                {
                    status = FAIL;
                    break;
                }

                command->cmd_extract.line = line;
            }
        }

        if (status == SUCCESS)
        {
            command->cmd_extract.option = strdup(option);
        }
        else
        {
            command->cmd_extract.option = NULL;
        }
    }
    else if (strcmp(option, "findall") == 0)
    {
        command->cmd = CMD_FINDALL;

        bool has_path = false;

        for (int i = 1; i < argc; i++)
        {
            if (strstr(argv[i], "path=") != NULL)
            {
                if (has_path)
                {
                    status = FAIL;
                    break;
                }
                has_path = true;

                status = SUCCESS;

                char *arg = extract_value(argv[i]);

                if (arg == NULL || strlen(arg) < 1)
                {
                    status = FAIL;
                    break;
                }

                command->cmd_findall.path = strdup(arg);
                command->cmd_findall.option = strdup(option);
            }
        }
    }
    else
    {
        command->cmd = CMD_INVALID;
    }

    if (status == FAIL)
    {
        switch (command->cmd)
        {
        case CMD_INVALID:
        {
            printf("Invalid command\n");
            break;
        }
        case CMD_PARSE:
        {
            printf("Invalid arguments. Usage:\n\t./a1 parse path=<file_path>\n");
            break;
        }
        case CMD_FINDALL:
        {
            printf("Invalid arguments. Usage:\n\t./a1 findall path=<file_path>\n");
            break;
        }
        case CMD_EXTRACT:
        {
            printf("Invalid arguments. Usage:\n\t./a1 extract path=<file_path> section=<sect_nr> line=<line_nr>\n");
            break;
        }
        case CMD_LIST:
        {
            printf("Invalid arguments. Usage:\n\t./a1 list [recursive] [<filtering_options>] path=<dir_path>\n\tFiltering options are:\n\t\tname_ends_with=<suffix>\n\t\thas_perm_write\n");
            break;
        }
        default:
            break;
        }
        command->cmd = CMD_INVALID;
    }

    return command;
}

void command_destroy(COMMAND_T **command)
{
    if (command == NULL || *command == NULL)
        return;

    do
    {
        if ((*command)->cmd == CMD_INVALID)
            break;

        switch ((*command)->cmd)
        {
        case CMD_VARIANT:
        {
            free((*command)->cmd_variant.option);
            (*command)->cmd_variant.option = NULL;
            break;
        }
        case CMD_PARSE:
        {
            free((*command)->cmd_parse.path);
            (*command)->cmd_parse.path = NULL;
            free((*command)->cmd_parse.option);
            (*command)->cmd_parse.option = NULL;
            break;
        }
        case CMD_FINDALL:
        {
            free((*command)->cmd_findall.path);
            (*command)->cmd_findall.path = NULL;
            free((*command)->cmd_findall.option);
            (*command)->cmd_findall.option = NULL;
            break;
        }
        case CMD_EXTRACT:
        {
            free((*command)->cmd_extract.path);
            (*command)->cmd_extract.path = NULL;
            if ((*command)->cmd_extract.option == NULL)
                break;
            free((*command)->cmd_extract.option);
            (*command)->cmd_extract.option = NULL;
            break;
        }
        case CMD_LIST:
        {
            free((*command)->cmd_list.path);
            (*command)->cmd_list.path = NULL;
            if ((*command)->cmd_list.option != NULL)
            {
                free((*command)->cmd_list.option);
                (*command)->cmd_list.option = NULL;
            }
            if ((*command)->cmd_list.suffix != NULL)
            {
                free((*command)->cmd_list.suffix);
                (*command)->cmd_list.suffix = NULL;
            }

            break;
        }
        default:
            break;
        }
    } while (false);

    free(*command);
    *command = NULL;
}

void command_interpret(COMMAND_T *command)
{
    if (command == NULL)
        return;

    switch (command->cmd)
    {
    case CMD_INVALID:
    {
        break;
    }
    case CMD_VARIANT:
    {
        printf("47947\n");
        break;
    }
    case CMD_PARSE:
    {
        command_parse(command);
        break;
    }
    case CMD_FINDALL:
    {
        command_findall(command);
        break;
    }
    case CMD_EXTRACT:
    {
        command_extract(command);
        break;
    }
    case CMD_LIST:
    {
        command_list(command);
        break;
    }

    default:
        break;
    }
}

void command_parse(COMMAND_T *command)
{
    if (command == NULL)
        return;
    HEADER_T *header = header_extract(command->cmd_parse.path);
    if (!header_validate(header, true))
    {
        header_destroy(&header);
        return;
    }

    printf("SUCCESS\nversion=%d\nnr_sections=%d\n",
           header->static_header.version,
           header->static_header.no_of_sections);

    for (int i = 0; i < header->static_header.no_of_sections; i++)
    {
        char name[10];
        memcpy(name, header->sections[i].name, 9);
        name[9] = '\0';
        printf("section%d: %s %d %d\n",
               i + 1,
               name,
               header->sections[i].type,
               header->sections[i].size);
    }

    header_destroy(&header);
}

void command_list(COMMAND_T *command)
{
    if (command == NULL)
        return;
    DIR *directory = NULL;

    directory = opendir(command->cmd_list.path);
    if (directory == NULL)
    {
        printf("ERROR\ninvalid directory path\n");
        return;
    }
    closedir(directory);

    printf("SUCCESS\n");
    list_directory(command->cmd_list.path, command);
}

void command_extract(COMMAND_T *command)
{
    if (command == NULL)
        return;

    int fd = open(command->cmd_extract.path, O_RDONLY);
    if (fd == -1)
    {
        printf("ERROR\ninvalid file\n");
        return;
    }
    close(fd);

    HEADER_T *header = header_extract(command->cmd_extract.path);
    if (!header_validate(header, false))
    {
        header_destroy(&header);
        return;
    }

    if (command->cmd_extract.section - 1 > header->static_header.no_of_sections ||
        command->cmd_extract.section <= 0)
    {
        printf("ERROR\ninvalid section\n");
        header_destroy(&header);
        return;
    }

    SECTION_T *section = section_create(
        command->cmd_extract.path,
        command->cmd_extract.section - 1);

    if (command->cmd_extract.line - 1 > section->line_count ||
        command->cmd_extract.line <= 0)
    {
        printf("ERROR\ninvalid line\n");
        header_destroy(&header);
        section_destroy(&section);
        return;
    }

    if (section != NULL)
    {
        int size = strlen(section->lines[section->line_count - command->cmd_extract.line]) - 1;

        for (int i = 0; i < size / 2 + 1; i++)
        {
            char temp = section->lines[section->line_count - command->cmd_extract.line][i];
            section->lines[section->line_count - command->cmd_extract.line][i] = section->lines[section->line_count - command->cmd_extract.line][size - i];
            section->lines[section->line_count - command->cmd_extract.line][size - i] = temp;
        }

        printf("SUCCESS\n%s\n", section->lines[section->line_count - command->cmd_extract.line]);
    }

    section_destroy(&section);
    header_destroy(&header);
    header = NULL;
    close(fd);
};

void command_findall(COMMAND_T *command)
{
    if (command == NULL)
        return;

    int fd = open(command->cmd_findall.path, O_RDONLY);
    if (fd == -1)
    {
        printf("ERROR\ninvalid file\n");
        return;
    }
    close(fd);

    printf("SUCCESS\n");
    list_directory_conditioned(command->cmd_findall.path, command);
}

int main(int argc, char **argv)
{
    COMMAND_T *cmd = argument_parser(argc, argv);

    if (cmd == NULL)
    {
        printf("Available commands. Use them as is for individual details:\n\t\
variant - Display variant\n\t\
list - List directory\n\t\
parse - Parse file header\n\t\
extract - Extract a line from a section\n\t\
findall - List recursive but only files that have at least 3\
sections with exactly 15 lines\n");
        ;
        return -1;
    }

    command_interpret(cmd);
    command_destroy(&cmd);
    return 0;
}