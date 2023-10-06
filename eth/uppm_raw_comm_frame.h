#ifndef USER_PROTOCOL_UPPM_RAW_COMM_FRAME_H_
#define USER_PROTOCOL_UPPM_RAW_COMM_FRAME_H_

#include <stdint.h>
#include "frame_defines.h"

#define UPPM_RAW_COMM_FRAME_SIZE 4

typedef struct
{
    // word 12, [31:24]
    uint8_t reserved1  :8;
    uint8_t reserved2  :8;
    uint8_t filter    :8;     //
    uint8_t phaseShifter;     //
}UPPM_Raw_Command_Frame;

typedef union
{
    UPPM_Raw_Command_Frame structData;
    uint8_t rawData[UPPM_RAW_COMM_FRAME_SIZE];
}UPPM_Raw_Command_Frame_union;

// Fields value
#define UPPM_RAW_COMM_FRAME_CTRL_OFFSET128 3
#define UPPM_RAW_COMM_FRAME_CTRL_SIZE128 1

#define UPPM_RAW_COMM_FRAME_SYNC_OFFSET128 4
#define UPPM_RAW_COMM_FRAME_SYNC_SIZE128 0

#define UPPM_RAW_COMM_FRAME_AUX_DATA_OFFSET128 4
#define UPPM_RAW_COMM_FRAME_AUX_DATA_SIZE128 0

#define UPPM_RAW_COMM_FRAME_SIGNAL_OFFSET128 4
#define UPPM_RAW_COMM_FRAME_SIGNAL_SIZE128 0


#endif /* USER_PROTOCOL_UPPM_RAW_COMM_FRAME_H_ */
