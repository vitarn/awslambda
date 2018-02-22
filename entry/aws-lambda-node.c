#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (a < b ? a : b)
#define EXE_LIMIT_MB (160)

int main(int argc, char* argv[])
{
    // set default node path if one isn't set
    if (getenv("NODE_PATH") == NULL) {
        setenv("NODE_PATH", "/var/runtime:/var/task:/var/runtime/node_modules", 1);
    }

    // to enable use by internal test harnesses
    char interpreter_path[PATH_MAX] = "/var/lang/bin/node";
    char* interpreter_override = getenv("_NODE");
    if (interpreter_override) {
        snprintf(interpreter_path, sizeof(interpreter_path), "%s", interpreter_override);
    }

    char* exe_path = strdup(argv[0]);
    char script_path[PATH_MAX] = {0};
    snprintf(script_path, sizeof(script_path), "%s/node_modules/awslambda/index.js", dirname(exe_path));
    free(exe_path);

    char* memory_limit_mb_str = getenv("AWS_LAMBDA_FUNCTION_MEMORY_SIZE");
    if (memory_limit_mb_str == NULL) {
        exit(execvp(
            interpreter_path,
            (char* []){
                interpreter_path, "--expose-gc", script_path, NULL,
            }));
    }
    uint64_t memory_limit_mb = atoi(memory_limit_mb_str);

    // Cap exec_size to RUNTIME_EXEC_SPACE_SIZE_CAP_MB
    uint64_t max_executable_size = MIN((uint64_t)round(((double)memory_limit_mb) * .1), EXE_LIMIT_MB);
    char max_executable_size_arg[NAME_MAX] = {0};
    snprintf(
        max_executable_size_arg,
        sizeof(max_executable_size_arg),
        "--max-executable-size=%" PRIu64,
        max_executable_size);

    // Set max-new-space to 10% of sandbox's ram limit.
    uint64_t max_new_space_size = (uint64_t)round(((double)memory_limit_mb) * .1);
    uint64_t max_semi_space_size = max_new_space_size / 2;
    char max_semi_space_size_arg[NAME_MAX] = {0};
    snprintf(
        max_semi_space_size_arg,
        sizeof(max_semi_space_size_arg),
        "--max-semi-space-size=%" PRIu64,
        max_semi_space_size);

    uint64_t max_old_space_size = memory_limit_mb - max_new_space_size - max_executable_size;
    char max_old_space_size_arg[NAME_MAX] = {0};
    snprintf(
        max_old_space_size_arg, sizeof(max_old_space_size_arg), "--max-old-space-size=%" PRIu64, max_old_space_size);

    exit(execvp(
        interpreter_path,
        (char* []){
            interpreter_path, 
            "--expose-gc", 
            max_executable_size_arg, 
            max_semi_space_size_arg, 
            max_old_space_size_arg, 
            script_path, 
            NULL,
        }));
}
