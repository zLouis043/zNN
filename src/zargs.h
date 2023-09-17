#ifndef ZARGS_H_
#define ZARGS_H_

#define DEBUG_SHOW 0
#define DEBUG_SHOW_LOG 0 

typedef enum level{
    INFO = 0,
    DEBUG, 
    WARNING,
    ERROR
}ZA_Log_Level;

/*!
    @brief Enum that contains every type of argument.
*/
typedef enum cmd{
    NO_CMD = 0,
    IN_CMD = 1,
    TRAIN_CMD,
    PREDICT_SINGLE_IMG,
    PREDICT_MULTIPLE_IMGS,
    HELP_CMD,
    CMD_NUMBER = HELP_CMD,
    FILE_TYPE,
    SAMPLE_TYPE,
    INDEX_TYPE,
    TYPES_NUMBER = INDEX_TYPE - HELP_CMD
}ZA_Cmd;

const char* cmd_description[] = {
    [IN_CMD] = "This command is used to choose the file from which the training data will be taken.",
    [TRAIN_CMD] = "This command starts the training.",
    [PREDICT_SINGLE_IMG] = "This command load the training data and try to predict the result.",
    [PREDICT_MULTIPLE_IMGS] = "This command load the training data and returns the precision of the neural network.",
    [HELP_CMD] = "This command prints the usage of the program.",
};

const char* cmd_usage[] = {
    [IN_CMD] = "--I <filename>",
    [TRAIN_CMD] = "--I <filename> --train <training_number_of_samples>",
    [PREDICT_SINGLE_IMG] = "--I <filename> --predict <num_of_Images> <img_index>",
    [PREDICT_MULTIPLE_IMGS] = "--I <filename> --predict -m <num_of_Images>",
    [HELP_CMD] = "--h",
};

/*!
    @brief Linked list of arguments.
    @param data The data contained in that node of the list.
    @param next_arg The next argument.
    @param visited Whether the node is visited or not.
*/
typedef struct args{
    char* data;
    struct args *next_arg;
    int visited;
    ZA_Cmd type;
} ZA_Args;

/*!
    @brief Logs a message and its log level.
    @param level The log level.
    @param fmt The message to format.
    @param ... The arguments.
*/
void za_log(ZA_Log_Level level, const char *fmt, ...);

/*!
    @brief Function that prints the usage of the program.
    @param filename The name of the file that its executed.
*/
void za_usage(ZA_Log_Level log_level, const char* filename);

/*!
    @brief Returns the current argument and puts the pointer to the next one.
    @param arg The number of the arguments.
    @param argv The arguments.
    @return The current argument.
*/
char* za_next_arg(int *argc, char ***argv);

/*!
    @brief Return the file name inside the current argument.
    @param arg The number of the arguments.
    @param argv The arguments.
    @return The file name inside the current argument.
*/
char* za_get_file_name(int *argc, char ***argv);

/*!
    @brief Opens a file, read through it and the print it out.
    @param filename The file to read.
    @param buff The buffer to write in.
    @return 1 if it all went well otherwise it will 0.
*/
int za_read_file(const char* filename, char** buff);

/*!
    @brief Write the buffer to the file.
    @param filename The file to read.
    @param buff The buffer from where we write.
    @return 1 if it all went well otherwise it will 0.
*/
int za_write_file(const char* filename, char* buff);

/*!
    @brief Append the buffer to the file.
    @param filename The file to read.
    @param buff The buffer to append.
    @return 1 if it all went well otherwise it will 0.
*/
int za_append_buff_to_file(const char* filename, char* buff);

/*!
    @brief Pushes the argument inside the linked list at the start of it.
    @param root The root of the linked list.
    @param arg The number of the arguments.
    @param argv The arguments.
*/
void za_push_arg_at_start(ZA_Args** root, int *argc, char ***argv);

/*!
    @brief Pushes the argument inside the linked list at the end of it.
    @param root The root of the linked list.
    @param arg The number of the arguments.
    @param argv The arguments.
*/
void za_push_arg_at_end(ZA_Args** root, int *argc, char ***argv);

/*!
    @brief Get the linked list from the arguments given in the command line.
    @param arg The number of the arguments.
    @param argv The arguments.
    @return The linked list from the arguments given in the command line.
*/
ZA_Args* za_get_args(int *argc, char ***argv);

/*!
    @brief Get the linked list from the arguments given in the command line.
    @param n The number of the arguments you want to get.
    @param arg The number of the arguments.
    @param argv The arguments.
    @return The linked list from the arguments given in the command line.
*/
ZA_Args* za_get_n_args(int n, int *argc, char ***argv);

/*!
    @brief Get the type of a given argument.
    @param args The arguments given.
    @return The type of the argument.
*/
ZA_Cmd za_get_arg_type(ZA_Args *args);

/*!
    @brief Set the type of a given argument.
    @param args The arguments given
*/
void za_set_args_type(ZA_Args* args);

/*!
    @brief Convert the type of a given argument to a string.
    @param args The arguments given.
    @return The type of the argument as a string.
*/
char* za_arg_type_to_string(ZA_Args* arg);

/*!
    @brief Parse the every arguments.
    @param prog_name The name of the program.
    @param arg The number of the arguments.
    @param argv The arguments.
    @attention This will shift the argv pointers so do not use get_args(). Better use get_n_args().
*/
void za_parse_args(const char* prog_name, int *argc, char ***argv);

/*!
    @brief Prints the linked list of arguments in reverse order.
    @param args The arguments in the linked list.
*/
void za_print_args_reverse(ZA_Args *args);

/*!
    @brief Prints the linked list of arguments.
    @param args The arguments in the linked list.
*/
void za_print_args(ZA_Args *args);

#endif // ZARGS_H_

#ifdef ZARGS_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define ZNN_IMPLEMENTATION
#include "znn.h"

void za_log(ZA_Log_Level level, const char *fmt, ...)
{
    switch (level) {
    case INFO:
        fprintf(stderr, "\n[INFO] ");
        break;
    case DEBUG:
        #if DEBUG_SHOW_LOG
            fprintf(stderr, "\n[DEBUG] ");
            break;
        #else 
            return;
        #endif
    case WARNING:
        fprintf(stderr, "\n[WARNING] ");
        break;
    case ERROR:
        fprintf(stderr, "\n[ERROR] ");
        break;
    default:
        fprintf(stderr, "\n[ERROR] Using non-existant log_level");
    }

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void za_usage(ZA_Log_Level log_level, const char* filename){
    za_log(log_level, "COMMANDS AVAILABLE:\n", filename);
    for(int i = 1; i < CMD_NUMBER+1; i++){
        za_log(log_level, "\tDESCRIPTION: %s\n\tUSAGE: ./%s %s\n", cmd_description[i], filename, cmd_usage[i]);
    }
}

char* za_next_arg(int *argc, char ***argv){

    if(*argc < 0) return NULL;

    char* result = **argv;
    *argc -= 1;
    *argv += 1;

   return result;
}

char* za_get_file_name(int *argc, char ***argv){

    za_next_arg(argc, argv);

    char* filename = za_next_arg(argc, argv);

    return filename;

}

int za_read_file(const char* filename, char** buff){

    FILE* fp;

    fopen_s(&fp, filename, "r");

    if(fp == NULL){
        return 0;
    }

    long bytes_number;

    fseek(fp, 0L, SEEK_END);
    bytes_number = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    *buff = (char*)calloc(bytes_number, sizeof(char));

    if(!buff){
        return 0;
    }

    fread(*buff, sizeof(char), bytes_number, fp);

    fclose(fp);

    return 1;

}

int za_write_file(const char* filename, char* buff){

   FILE* fp;

   fopen_s(&fp, filename, "w");

    if(fp == NULL){
        return 0;
    } 

    int size = strlen(buff);
    
    while (size > 0) {
        size_t n = fwrite(buff, 1, size, fp);
        if (ferror(fp)) {
            return 0;
        }
        size -= n;
        buff  += n;
    }

    fclose(fp); 

    return 1;

}

int za_append_buff_to_file(const char* filename, char* buff){

    FILE* fp;

    fopen_s(&fp, filename, "a");

    if(fp == NULL){
        return 0;
    } 

    int size = strlen(buff);
    
    while (size > 0) {
        size_t n = fwrite(buff, 1, size, fp);
        if (ferror(fp)) {
            return 0;
        }
        size -= n;
        buff  += n;
    }

    fclose(fp); 

    return 1;

}

void za_push_arg_at_start(ZA_Args** root, int *argc, char ***argv){
    ZA_Args *arg= malloc(sizeof(ZA_Args));
    arg->data = za_next_arg(argc, argv);
    arg->next_arg = *root;
    arg->visited = 0; 
    arg->type = NO_CMD;
    *root = arg;
}

void za_push_arg_at_end(ZA_Args** root, int *argc, char ***argv){

    ZA_Args* arg = (ZA_Args*)malloc(sizeof(ZA_Args));
    arg->data = za_next_arg(argc, argv);
    ZA_Args* last_arg = *root;
    arg->next_arg = NULL;

    arg->visited = 0; 
    if (*root == NULL) {
        *root = arg;
        return;
    }
 
    while (last_arg->next_arg != NULL) {
        last_arg = last_arg->next_arg;
    }
 
    last_arg->next_arg = arg;

}

ZA_Args* za_get_args(int *argc, char ***argv){

    ZA_Args *args = NULL;

    int len = *argc;
    
    for(int i = 0; i < len; i++){
        za_push_arg_at_end(&args, argc, argv);
    }  

    return args;

}

ZA_Args* za_get_n_args(int n,int *argc, char ***argv){

    ZA_Args *args = NULL;
    
    if(n > *argc){
        za_log(ERROR, "N is greater that the number of arguments");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n; i++){
        za_push_arg_at_end(&args, argc, argv);
    }  

    return args;

}

ZA_Cmd za_get_arg_type(ZA_Args *args){
    if(strcmp(args->data, "--I") == 0){
        args->type = IN_CMD;
        return IN_CMD;
    }else if(strcmp(args->data, "--train") == 0){
        args->type = TRAIN_CMD;
        return TRAIN_CMD;
    }else if(strcmp(args->data, "--predict") == 0){
        args->type = PREDICT_SINGLE_IMG;
        return PREDICT_SINGLE_IMG;
    }else if(strcmp(args->data, "-m") == 0){
        args->type = PREDICT_MULTIPLE_IMGS;
        return PREDICT_MULTIPLE_IMGS;
    }else if(strcmp(args->data, "--h") == 0){
        args->type = HELP_CMD;
        return HELP_CMD;
    }else {
        args->type = NO_CMD;
        return NO_CMD;
    }
}

void za_set_args_type(ZA_Args* args){

    ZA_Args* tmp = args;

    while(tmp != NULL){
        za_get_arg_type(tmp);  
        if(tmp->type == IN_CMD){
            tmp = tmp->next_arg;
            if(za_get_arg_type(tmp) == NO_CMD){
                tmp->type = FILE_TYPE; 
                tmp = tmp->next_arg;
            }

        }else if(tmp->type == TRAIN_CMD){

            tmp = tmp->next_arg;
            tmp->type = SAMPLE_TYPE;
            tmp = tmp->next_arg;

        }else if(tmp->type == PREDICT_SINGLE_IMG){ 

            if(za_get_arg_type(tmp->next_arg) == PREDICT_MULTIPLE_IMGS ){
                tmp->type = PREDICT_MULTIPLE_IMGS;
                tmp = tmp->next_arg->next_arg;
                tmp->type = SAMPLE_TYPE;
                tmp = tmp->next_arg;
            }else {
                
                tmp = tmp->next_arg;
                tmp->type = INDEX_TYPE;
                tmp = tmp->next_arg;

            }

        }else {

            tmp = tmp->next_arg;  

        }
    }

    args = tmp;
}

char* za_arg_type_to_string(ZA_Args* arg){

    switch(arg->type){
        case IN_CMD:{
            return "IN_CMD";
        }break;
        case TRAIN_CMD:{
            return "TRAIN_CMD";
        }break;
        case PREDICT_SINGLE_IMG:{
            return "PREDICT_SINGLE_IMG";
        }break;
        case PREDICT_MULTIPLE_IMGS:{
            return "PREDICT_MULTIPLE_IMGS";
        }break;
        case HELP_CMD:{
            return "HELP_CMD";
        }break;
        case FILE_TYPE:{
            return "FILE_TYPE";
        }break;
        case SAMPLE_TYPE:{
            return "SAMPLE_TYPE";
        }break;
        case NO_CMD:{
            return "NO_CMD"; 
        }break;
    }
}

void za_parse_args(const char* prog_name, int *argc, char ***argv){

    ZA_Args *args = za_get_args(argc, argv);

    char* filename;
    char* buff;

    za_set_args_type(args);

    while(args != NULL){
        if(args->type == IN_CMD){
            if(args->next_arg != NULL){
                args = args->next_arg;

                filename = args->data;

            }else {

                za_log(ERROR, "> Missing input file token.");
                za_usage(ERROR, prog_name);
                exit(EXIT_FAILURE);  
            }

            goto next_arg;


        }else if(args->type == TRAIN_CMD){

            if(args->next_arg != NULL){
                
                args = args->next_arg;

                int n_images = atoi(args->data);
                ZI_Img **imgs = zi_csv_to_imgs(filename, n_images);
                ZN_NN* nn = zn_nn_new(784, 300, 10, 0.1);
                zn_nn_train_batch_imgs(nn, imgs, n_images);
                zn_nn_save(nn, "../NN_Saved_Data");

                zi_imgs_free(imgs, n_images);
                zn_nn_free(nn);

            }else {

                za_log(ERROR, "> Missing training sample token.");
                za_usage(ERROR, prog_name);
                exit(EXIT_FAILURE); 

            }

            goto next_arg;

        }else if(args->type == PREDICT_SINGLE_IMG){
            
            if(args->next_arg != NULL){
                
                args = args->next_arg;

                int n_images = atoi(args->data);

                if(args->next_arg == NULL){
                    
                    za_log(ERROR, "> Missing image index token.");
                    za_usage(ERROR, prog_name);
                    exit(EXIT_FAILURE); 

                }

                args = args->next_arg;

                ZI_Img **imgs = zi_csv_to_imgs(filename, n_images);
                ZI_Img* img_to_predict = imgs[atoi(args->data)];
                zi_img_print(img_to_predict);
                ZN_NN* nn = zn_nn_load("../NN_Saved_Data");
                MZ_Matrix result = zn_nn_predict_img(nn, img_to_predict);
                printf("NN Predict: %d\n", MZ_matrix_argmax(result));

                zi_imgs_free(imgs, n_images);
                zn_nn_free(nn);

            }else {

                za_log(ERROR, "> Missing image samples number token.");
                za_usage(ERROR, prog_name);
                exit(EXIT_FAILURE); 

            }

            goto next_arg;

        }else if(args->type == PREDICT_MULTIPLE_IMGS){

            if(args->next_arg != NULL && za_get_arg_type(args->next_arg) == PREDICT_MULTIPLE_IMGS){
                
                args = args->next_arg->next_arg;

                int n_images = atoi(args->data);
                ZI_Img **imgs = zi_csv_to_imgs(filename, n_images);
                ZN_NN* nn = zn_nn_load("../NN_Saved_Data");
                double score = zn_nn_predict_imgs(nn, imgs, n_images);
                printf("Score: %1.5f\n", score);

                zi_imgs_free(imgs, n_images);
                zn_nn_free(nn);

            }else {

                za_log(ERROR, "> Missing image samples number token.");
                za_usage(ERROR, prog_name);
                exit(EXIT_FAILURE); 

            }

            goto next_arg;          

        }else if(args->type == HELP_CMD){
            za_usage(INFO, prog_name);

            goto next_arg;
        }else{
            za_log(ERROR, "> Invalid token : %s.", args->data);
            za_usage(ERROR, prog_name);
            exit(EXIT_FAILURE);
        }

        next_arg: 
        
        args = args->next_arg;
    }

    free(buff);
    free(filename);

    return;
}



void za_print_args_reverse(ZA_Args *args){

    ZA_Args *tmp = args;

    ZA_Args *prev = args;

    int i = 1;

    printf("\nTokens given: {\n");

    while(tmp->visited == 0){
        while(tmp->next_arg != NULL && tmp->next_arg->visited == 0){
            tmp = tmp->next_arg;
        }
        printf("\t[Token %d] = ( Token: '%15s', type: %-20s),\n", i, tmp->data, za_arg_type_to_string(tmp));

        tmp->visited = 1;
        tmp = args;

        i++;
    }
    printf("}");
}

void za_print_args(ZA_Args *args){

    ZA_Args *tmp = args;

    int i = 1;

    za_set_args_type(tmp);
    
    printf("\nTokens given: {\n");

    while(tmp != NULL){
        printf("\t[Token %d] = ( Token: '%15s', type: %-20s)", i, tmp->data, za_arg_type_to_string(tmp));
        if(tmp->next_arg != NULL){
            printf(",\n");
        }else {
            printf("\n");
        }
        tmp = tmp->next_arg;
        i++;
    }
    printf("}");
}

#endif // ZARGS_IMPLEMENTATION