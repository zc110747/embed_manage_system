/*
 * main.cpp
 *
 *  Created on: 2021 May 11 15:08:05
 */

#include "FileProcessWf.hpp"

#define MODULE_TEST 1
static void module_test(void);

int main(int argc, char **argv)
{
#if MODULE_TEST == 1
    module_test();
#endif

    
    return 0;
}

static void module_test(void)
{
    USR_READER::test_file_reader_wf();
}