# embed_manage_system
定义WorkFlow到Hardware之间的接口，用于控制硬件或者读取设备信息

SetHwStatus     [Device]   [Status]
explain:
    / - command  -/- Device -/- Status -/
    [0:10]  command
    [11]    space
    [12:16] Device ["LED  ", "LED0 "..."BEEP ", "BEEP0"...]
    [17]    space
    [18:20] Status ["ON ", "OFF"]
    [21]    space


callback:
    / - command  -/- Device -/- Status -/

GetHwStatus [Device]
