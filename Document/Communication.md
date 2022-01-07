# embed_manage_system

1.定义WorkFlow到Hardware之间的接口，用于控制硬件或者读取设备信息
SetHwStatus [Device] [Status]
explain:
    /- command -/- Device -/- Status -/
    [0:10]  SetHwStatus
    [11]    space
    [12:16] Device ["LED  ", "LED0 "..."BEEP ", "BEEP0"...]
    [17]    space
    [18:20] Status ["ON ", "OFF"]
    [21]    space


Ack:
    /- Ack -/- command -/- Device -/- Status -/
    [0:2]   Ack
    [3]     space
    [4:x]   Command
    [x+1]   space
    [...]   Device ["LED  ", "LED0 "..."BEEP ", "BEEP0"...]
    [...]   space
    [...]   status [0~9] 0:success, other:error code

GetHwStatus [Device]
    