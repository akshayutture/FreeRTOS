/*
 * FreeRTOS memory safety proofs with CBMC.
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * https://aws.amazon.com/freertos
 * https://www.FreeRTOS.org
 */

#include <stdint.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

void vSetGlobalVariables( void );
BaseType_t xPrepareTaskLists( void );

/*
 * We prepare task lists by inserting one item in each list,
 * and with the macro redefinition we ensure only valid ready
 * task lists are checked in `taskSELECT_HIGHEST_PRIORITY_TASK()`
 * 
 * Note: All loop unwinding for this proof is set to 8, 
 * because configMAX_PRIORITIES is set to 7 in FreeRTOS.h. 
 * Should that value change, the unwinding
 * length should be adjusted accordingly.
 */
void harness()
{
    BaseType_t xTasksPrepared;

    vSetGlobalVariables();
    xTasksPrepared = xPrepareTaskLists();

    if( xTasksPrepared != pdFAIL )
    {
        vTaskSwitchContext();
    }
}
