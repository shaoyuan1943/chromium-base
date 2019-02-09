### 1. base::AtExitManager
描述：AtExitManager类似CRT函数```atexit()```，在生命周期内接受注册多个回调函数，在对象被销毁时所有注册的回调都将被调用，用来在某个作用区域内做善后工作。AtExitManager以栈容器存放回调函数，访问和遍历由栈特性所决定。
头文件: at_exit.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| RegisterCallback | M | 注册一个签名为```void(void*)```的函数指针作为回调函数 |
| RegisterTask | M | 注册一个```base::Callback```对象作为回调函数 |
| ProcessCallbacksNow| M | 执行所有已注册的回调函数 |


### 2. base::Time::Exploded
描述：表达已格式化之后的时间，类似Win32 ```SYSTEMTIME```结构或Unix ```struct tm```。  
头文件：base_time.h  

### 3. base::Time
描述：日期时间  
头文件：base_time.h  
API:

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| is_null | M | Time对象未被初始化时返回true |
| is_max | M | Time对象到达最大时间值时返回true |
| UnixEpoch | S | 返回从1970.1.1开始的Unix时间戳 |
| Now | S | 返回当前时间，由于存在系统时钟更改的可能性，不保证Now返回值一直时增加的 |
| Max | S | 返回最大时间值，这个时间应该大于我们可能比较它的任何合理时间 |
| NowFromSystemTime | S | 返回当前时间， 与Now不同的是：该函数始终使用系统时间 |
| FromTimeT/ToTimeT | S/M | time_t和base::Time互转 |
| FromDoubleT/ToDoubleT | S/M | epoch(from 1970.1.1)和base::Time互转 |
| FromTimeVal/ToTimeVal | S/M | POSIX ONLY, struct timeval和base::Time互转 |
| FromCFAbsoluteTime/ToCFAbsoluteTime | S/M | MACOS ONLY, CFAbsoluteTime和base::Time 互转 |
| FromFileTime/ToFileTime | S/M | WINDOWS ONLY, FILETIME和base::Time互转 |
| EnableHighResolutionTimer | S | WINDOWS ONLY, 是否开启高精度Timer |
| ActivateHighResolutionTimer | S | WINDOWS ONLY, 设置高精度Timer是否活跃状态，如果禁用了高精度Timer，这个操作将返回false |
| IsHighResolutionTimerInUse | S | WINDOWS ONLY, 如果启用了高精度Timer且处于活跃状态将返回true，否则返回false |
| FromUTCExploded/FromLocalExploded | S | 通过本地时间或者UTC时间创建base::Time  |
| FromInternalValue/ToInternalValue | S/M | 微秒数与base::Time互转 |
| FromString | S | 通过标准时间字符串创建base::Time |
| UTCExplode/LocalExplode | M | 根据UTC时间或本地时间填充base::Exploded |
| LocalMidnight | M | 返回base::Time描述的本地午夜时间 |


### 4. base::TimeTicks
描述: 以Tick为单位表达CPU时间。  
头文件：base_time.h  
API:

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Now | S | 返回当前与平台相关的Tick计数 |
| HighResNow | S | 返回当前平台相关的高精度Tick技术，内部实现取决于硬件。调用此函数的开销高于Now |
| NowFromSystemTraceTime | S | 如果定义了全局跟踪时钟，则返回当前系统跟踪时间，否则等价于HighResNow |
| is_null | M | 当此对象未被初始化时将返回true  |
| FromInternalValue/ToInternalValue | S/M | Tick计算和base::TimeTicks互转 |


### 5. base64
描述：base64编解码  
头文件：base64.h  
API:

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Base64Encode | G | base64编码，成功时返回true |
| Base64EncodeLength | G | 返回base64编码所需的长度，比计算长度多10字节 |
| Base64Decode | G | base64解码，成功时返回true |
| Base64DecodeLength | G | 返回base64解码所需的长度，比计算长度多10字节 |


### 6. base::Callback/base::Bind
描述：类似std::function/std::bind  
头文件：callback.h/bind.h  
API:

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Bind | G | 将可执行对象连同参数绑定到Callback上 |


### 7. base::CancelableCallback
描述：可取消操作的Callback  
头文件：cancelable_callback.h  
API:

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Cancel | M | 取消Callback，后续的调用无效果 |
| IsCancelled | M | 是否已取消 |
| Reset | M | 重设 |
| callback | M | 返回内部的base::Callback |


### 8. build_time
描述：二进制编译时间  
头文件：build_time.h  
API:

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| GetBuildTime | G | 返回当前二进制编译时间 |


### 9. base::CommandLine
描述：可执行程序的命令行解析对象  
头文件：command_line.h  
API：

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Init | S | 创建当前进程CommandLine单例  |
| Reset | S | 销毁当前进程的CommandLine对象，销毁之后如需再次使用必须重新调用Init创建新的CommandLine对象 |
| ForCurrentProcess | S | 获取当前进程的CommandLine对象，返回的值是可修改的且非线程安全 |
| InitFromArgv | M | 从参数容器中初始化CommandLine |
| GetCommandLineString | M | 返回字符串形式的命令行参数 |
| argv | M | 返回容器形式的命令行参数 |
| GetProgram/SetProgram | M | 返回或设置当前程序路径（命令行第一个参数） |
| SetProgram | M | 设置当前程序路径|
| HasSwitch | M | 是否存在switch形式的命令行参数，即："--"、"="|
| GetSwitches | M | 以map方式返回当前所有的switch命令行参数 |
| AppendSwitch* | M | 以switch方式添加命令行参数 |
| CopySwitchesFrom | M | 拷贝另外一个CommandLine对象的switch命令行参数 |
| GetArgs | M | 获取命令行的其余参数|
| AppendArg* | M | 添加一个命令行参数 |
| PrependWrapper | M | 在当前命令的最前面插入命令 |
| ParseFromString | M | WINDOWS ONLY， 通过给定的命令行参数字符串初始化CommandLine对象 |


### 10. base::CPU
描述：当前CPU信息，具体参见头文件  
头文件：cpu.h  

### 11. base::Environment
描述：环境变量相关  
头文件：environment.h  
API:

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Create | S | 创建Environment对象 |
| GetVar | M | 获取环境变量的值，如果环境变量未设置则返回false |
| HasVar | M | 检测环境变量是否存在，存在则返回true |
| SetVar | M | 设置环境变量，操作成功则返回true |
| UnSetVar | M | 重置环境变量，操作成功则返回true |


### 12. base::EventRecorder
描述：用于录制和播放键盘和鼠标输入事件。当在记录或回放时，必须将相关窗口移动到恒定的大小和位置，仅考虑在有窗口的情况下  
头文件：event_recorder.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| current | S | 返回base::EventRecorder对象，单例 |
| StartRecording | M | 开始记录，具体结果记录在给定的FilePath文件里 |
| StopRecording | M | 停止记录 |
| is_recording | M | 是否记录中 |
| StartPlayback | M | 回放事件记录到FilePath文件里 |
| StopPlayback | M | 停止回放 |
| is_playing | M | 是否回放中 |
| RecordWndProc | M | WINDOWS ONLY C风格的记录回调函数 |
| PlaybackWndProc | M | WINDOWS ONLY C风格的回放回调函数 |


### 13. base::FilePath
描述：表达文件路径    
头文件：file_path.h    
API：

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Separators | S | 返回路径分割符，与系统相关 |
| CurrentDirectory | S | 返回当前目录字符串，即： "." |
| ParentDirectory | S | 返回父目录字符串，即：".."|
| ExtensionSeparator | S | 返回扩展分割符 |
| value | M | 以字符串形式返回当前所表达的路径 |
| empty | M | 当前路径是否为空 |
| clear | M | 清空当前路径 |
| IsSeparator | S | 判断给定的字符串是否是分割符 |
| GetComponents | M | 返回当前目录下的目录或文件，非递归深入 |
| IsParent | M | 判断当前路径是否是给定路径的父目录 |
| AppendRelativePath | M | 添加基于当前路径下的相对路径，给定的路径必须是当前路径的子路径 |
| DirName | M | 返回当前对象所代表的路径的目录FilePath |
| BaseName | M | 返回当前对象的最后一个路径组件（文件或目录）对应的FilePath |
| Extension | M | 以字符串形式返回当前文件扩展名，如：".jpg"|
| RemoveExtension | M | 以字符串形式返回不包括扩展名的FilePath |
| InsertBeforeExtension | M | 在扩展名之前插入 |
| AddExtension | M | 添加扩展名，如果扩展名为空，则返回空的FilePath，如果BaseName() == "."/".." 则返回"" |
| ReplaceExtension | M | 替换扩展名，返回规则与AddExtension相同 |
| MatchesExtension | M | 判断当前是否是给定的扩展名 |
| Append | M | 通过分割符或提供的路径附加到当前路径返回新的FilePath |
| IsAbsolute | M | 如果此FilePath包含绝对路径，则返回true |
| StripTrailingSeparators | M | 返回当前路径的副本，但不以尾随分隔符结尾 |
| ReferencesParent | M | 如果此FilePath企图包含任何父目录的引用（即路径组件为“..”），则返回true。 |
| LossyDisplayName | M | 以人类可读的Unicode方式返回当前路径 |
| MaybeAsASCII | M | 以ASCII方式返回当前路径 |
| AsUTF8Unsafe | M | 以UTF8方式返回当前路径|
| FromUTF8Unsafe | S | 以UTF8编码的路径字符串创建FilePath |
| FromWStringHack | S | wstring表示的路径字符串创建FilePath |
| WriteToPickle/ReadFromPickle | M | 写入/读取Pickle对象 |
| NormalizePathSeparators | M | 在Windows上将所有路径分隔符规范化为反斜杠 |
| CompareIgnoreCase | S | 以与文件系统相同的方式比较两个字符串 |
| CompareEqualIgnoreCase | S | 以与文件系统相同的方式比较两个字符串 |
| CompareLessIgnoreCase | S | 以与文件系统相同的方式比较两个字符串 |
| GetHFSDecomposedForm | S | MACOS ONLY 返回以HFS定义的特殊规范分解形式的字符串 |
| HFSFastUnicodeCompare | S | MACOS ONLY 比较以HFS定义的两个字符串 |


### 14. file_util
描述：文件相关操作  
头文件：file_util.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| EndsWithSeparator | G | 判断给定的FilePath是否以分割符结尾 |
| EnsureEndsWithSeparator | G | 确保给定的FilePath是以分隔符结尾的，如果FilePath存在则返回true |
| AbsolutePath | G | 将给定的FilePath转为绝对路径，如果发生错误返回false |
| ContainsPath | G | 判断两个FilePath是否是父子关系 |
| CountFilesCreatedAfter | G | 返回给定的FilePath中在某个时间之后创建的文件数目 |
| ComputeDirectorySize | G | 返回给定的FilePath下所有目录的字节数 |
| ComputeFilesSize | G | 返回给定的FilePath下所有文件的字节数 |
| Delete | G | 删除给定的FilePath，操作成功返回true |
| DeleteAfterReboot | G | WINDOWS ONLY 删除给定的FilePath并重启系统，操作成功返回true |
| Move | G | 移动给定路径，如果无法进行简单重命名，例如路径位于不同硬盘上，则会尝试复制和删除。操作成功返回true|
| ReplaceFile | G | 重命名文件From FilePath到To FilePath，两个路径必须位于同一个硬盘上，如果目标文件不存在，将创建它。在处理临时文件时，首选此功能而不是Move。在Windows上，它保留目标文件的属性。操作成功时返回true |
| CopyFile | G | 复制文件，操作成功返回true |
| CopyDirectory | G | 复制目录，如果目录已存在则覆盖，操作成功返回true |
| PathExists | G | 判断路径是否存在 |
| PathIsWritable | G | 判断路径是否可写 |
| DirectoryExists | G | 判断目录是否存在 |
| GetFileCreationLocalTime | G | WINDOWS ONLY 获取文件创建时的本地时间 |
| GetFileCreationLocalTimeFromHandle | G | WINDOWS ONLY 通过文件句柄获取文件创建时的本地时间 |
| ContentsEqual | G | 判断两个文件内容是否相等，内部以memcmp实现 |
| TextContentsEqual | G | 以文本方式判断两个文件内容是否相等 |
| ReadFileToString | G | 以文本方式读取文件内容 |
| ReadFromFD | G | POSIX ONLY 从文件描述符fd中读取内容 |
| CreateSymbolicLink| G | POSIX ONLY 创建symbolic link链接 |
| ReadSymbolicLink | G | POSIX ONLY 读取symbolic link链接|
| GetPosixFilePermissions | G | POSIX ONLY 读取文件或目录权限 |
| SetPosixFilePermissions | G | POSIX ONLY 设置文件或目录权限 |
| CopyAndDeleteDirectory | G | WINDOWS ONLY 以递归方式拷贝目录之后删掉原始目录 |
| IsDirectoryEmpty | G | 判断是否空目录 |
| GetTempDir | G | 获取windows下临时目录 |
| GetHomeDir | G | 获取Home目录 |
| CreateTemporaryFile | G | 创建临时文件，操作成功返回true |
| CreateTemporaryFileInDir | G | 在给定的目录下创建临时文件，操作成功返回true |
| CreateAndOpenTemporaryFile | G | 创建并打开临时文件，操作成功返回true |
| CreateAndOpenTemporaryFileInDir | G | 在给定的目录下创建并打开临时文件，操作成功返回true |
| CreateNewTempDirectory | G | 创建临时目录，操作成功返回true |
| CreateTemporaryDirInDir | G | 在给定的目录下创建临时目录，操作成功返回true |
| CreateDirectory | G | 创建目录，如果某个路径不存在，会新创建，操作成功返回true |
| GetFileSize | G | 获取文件大小 |
| IsDot | G | 判断FilePath是否是"." |
| IsDotDot | G | 判断FilePath是否是".."|
| NormalizeFilePath | G | 将FilePath代表的路径以symbolic links的方式设置到另外一个FilePath上，在windows上必须是以字母驱动器开头的路径，\|path\|必须指向的是文件,如果\|path\|是目录或者不存在则返回false |
| DevicePathToDriveLetterPath | G | WINDOWS ONLY 返回以驱动器开头的路径 如果路径不存在则会返回false |
| NormalizeToNativeFilePath | G | WINDOWS ONLY 根据给定的路径返回基于Native NT format的路径，如果路径不存在则返回false |
| IsLink | G | 判断给定的FilePath是否是symbolic link |
| GetFileInfo | G | 获取文件信息，操作成功返回true |
| TouchFile | G | 修改文件最后访问时间和修改时间，操作成功返回true |
| SetLastModifiedTime | G | 修改文件最后修改时间，操作成功返回true |
| GetInode | G | POSIX ONLY 获取文件索引节点号，操作成功返回true |
| OpenFile | G | 打开文件，fopen的封装 |
| CloseFile | G | 关闭文件 |
| TruncateFile | G | 拼接文件 |
| ReadFile/WriteFile | G | 读写文件|
| WriteFileDescriptor | G | POSIX ONLY 通过fd写入文件描述符 |
| AppendToFile | G | 追加文件内容 |
| GetCurrentDirectory | G | 获取当前工作目录 |
| SetCurrentDirectory | G | 设置当前工作目录 |
| GetUniquePathNumber | G | 尝试查找可以附件到FilePath后的数字使其唯一，类似"Dir(1)","Dir(2)",如果FilPath不存在则返回0，如果找不到这样的数字则返回-1，如果后缀不为空，则也用给定的后缀去检查，适用于复制或者移动文件名或目录名冲突时的善后处理 |
| VerifyPathControlledByUser | G | POSIX ONLY 验证给定的FilePath是否只能被给定的User或者用户组成员变更 |
| VerifyPathControlledByAdmin | G | MACOSX ONLY 验证给定的FilePath是否能被管理员权限变更修改 |
| ScopedFILEClose | G | 自动关闭FILE |
| ScopedFDClose | G | POSIX ONLY 自动关闭FD |
| HasFileBeenModifiedSince | G | 返回距离上一次修改的多长时间 |
| GetFileSystemType | G | LINUX ONLY 返回文件的系统类型 |


### 15. base::FileEnumerator
描述：文件枚举器，用于遍历目录  
头文件：file_util.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Next | M | 当前枚举器所指向的下一个FilePath，最后一个是空的FilePath |
| GetFindInfo | M | 获取FindInfo |
| IsDirectory | M | 是否是目录 |
| GetFilename | M | 获取文件名 |
| GetFilesize | M | 获取文件大小 |
| GetLastModifiedTime | M | 获取文件最后修改时间 |


### 16. base::MemoryMappedFile
描述：内存映射文件  
头文件：file_util.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Initialize | M | 将一个存在的文件映射到内存，如果无法打开文件或者文件不存在或者内存映射失败将会返回false |
| InitializeAsImageSection | M | WINDOWS ONLY 打开现有文件并将其映射为图像部分，一般用来操作图像文件 |
| data | M | 内存数据 |
| length | M | 内存数据长度|
| IsValid | M | 是否合法 |

### 17. base::FileUtilProxy
描述：提供对文件的异步访问
头文件：file_util_proxy.h
API:

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| CreateOrOpen | S | 在task runner下创建或打开文件，返回值不代表文件创建或打开成功 |
| CreateTemporary | S | 创建临时目录 |
| Close | S | 关闭文件 |
| GetFileInfo | S | 获取文件信息 |
| GetFileInfoFromPlatformFile | S | 通过平台文件句柄获取文件信息 |
| Delete | S | 删除，可能是文件也可能是目录 |
| RecursiveDelete | S | 删除目录，会递归删除所有内容 |
| Read | S | 读取文件 |
| Write | S | 写入文件 |
| Touch | S | 访问文件 |
| Truncate | S | 将文件截断为给定长度。 如果给定长度大于文件的当前长度，则文件将以零扩展 |
| Flush | S | 刷新文件 |
| RelayFileTask | S | FileTask形式 |
| RelayCreateOrOpen | S | FileTask形式，类同CreateOrOpen |
| RelayClose | S | FileTask形式，类同Close |

### 18. base::FileVersionInfo
描述：访问文件版本信息  
头文件：file_version_info.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| CreateFileVersionInfo | S | WINDOWS AND MACOSX ONLY 创建文件的版本信息 |
| CreateFileVersionInfoForModule | S | WINDOWS ONLY 创建文件的版本信息 |
| CreateFileVersionInfoForCurrentModule | S | 给exe创建文件版本信息 |

### 19. float_util
描述：判断float是否为无限浮点数  
头文件：float_util.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| IsFinite | G | 判断是否为无限浮点数 |

### 20. guid
描述：生成guid  
头文件：guid.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| GenerateGUID | G | 生成GUID |
| IsValidGUID | G | 是否合法GUID |

### 21. hash
描述：生成hash值  
头文件：hash.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| SuperFastHash | G | 生成hash值 |

### 22. HighResolutionTimerManager
描述：高精度Timer  
头文件：hi_res_timer_manager.h  
API：  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| OnPowerStateChange | M | 设置当前是否电池供电，当电源接通时候高精度时钟才会启用 |
| hi_res_clock_available | M | 高精度时钟是否可用 |

### 23. IDMap
描述：此对象维护一个ID列表，可以快速转换为指向对象的指针,内部实现为哈希表，针对小数据进行优化。可以使用任意ID将项插入到容器中，调用者必须确保ID唯一，不要依赖生成的ID。base::IDMap没有虚析构函数，所以不要轻易继承此类。  
头文件：base/id\_map.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| set_check_on_null_data | M | 插入数据时是否检查数据为空，如果设置此项，后续每次插入时都会检查数据项 |
| Add | M | 添加对象指针，添加成功返回索引ID |
| AddWithID | M | 通过自有ID添加对象指针，调用必须保证此ID是唯一且不与IDMap内部自动生成的ID重复，不推荐使用此函数 |
| Remove | M | 通过索引ID移除对象指针 |
| IsEmpty | M | 是否为空 |
| Lookup | M | 查找对象指针 |
| size | M | 内部已存对象指针数量 |
| iterator | M | 内部实现的迭代器用于遍历，具体迭代器实现参见头文件 |

### 24. LazyInstance
描述：延迟创建，在使用时初始化对象  
头文件：base/lazy\_instance.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Get | M | 获取对象引用 |
| Pointer | M | 获取对象指针 |


### 25. LinkedList
描述：base::LinkedList是std::list的一个轻量级实现。从base::LinkedList<T>中删除类型为T *的元素是O(1)操作，std::list<T*>的删除操作是O(n)。这是因为使用std::list<T*>，必须先获取T *元素的迭代器，然后才能调用erase（迭代器）, base::LinkedList<T>的插入操作永远不需要堆分配。元素类型必须继承自base::LinkNode    
头文件：base/linked_list.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Append | M | 向尾部添加元素 |
| head | M | 第一个元素 |
| tail | M | 最后一个有效元素 |
| end | M | 链表最尾 |

### 26. Location
描述：用于Debug的helper，标记了调用位置（文件、行号、函数名、函数地址）  
头文件：base/location.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| function_name | M | 函数名 |
| file_name | M | 文件名 |
| line_number | M | 行号 |
| program_counter | M | 函数地址 |
| ToString | M | 将以上信息写成特定格式字符串 |
| Write | M | 将以上信息写成特定格式的传入字符串 |
| WriteFunctionName | M | 以HTML方式将函数名写入传入字符串 |

### 27. MD5
描述：生成MD5值  
头文件：base/md5.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| MD5Digest | G | MD5输出结构 |
| MD5Context | G | 用于在MD5计算期间存储中间数据 |
| MD5Sum | G | 使用给定长度计算给定数据缓冲区的MD5总和 |
| MD5Init | G | 初始化MD5Context用以调用MD5Update |
| MD5Update | G | 更新计算MD5值得上下文，可以函数多次调用，调用此函数之前必须先调用MD5Init |
| MD5Final | G | 将MD5的结果填充到MD5Digest |
| MD5DigestToBase16 | G | 将MD5结果转换为std::string |
| MD5String | G | 返回十六进制的MD5字符串 |

### 28. native_library
描述：加载动态库  
头文件：base/native_library.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| LoadNativeLibrary | G | 加载动态库，error为错误信息 |
| UnloadNativeLibrary | G | 卸载动态库 |
| LoadNativeLibraryDynamically | G | WINDOWS ONLY 此函数检索从kernel32.dll导出的LoadLibrary函数并调用它，而不是通过导入表直接调用LoadLibrary函数 |
| GetFunctionPointerFromNativeLibrary | G | 从已加载的动态库中根据函数名获取函数指针 |
| GetNativeLibraryName | G | 返回动态库名字，"mylib" returns "mylib.dll" on Windows, "libmylib.so" on Linux, "mylib.dylib" on Mac |

### 29. base::ObserverList
描述：观察者列表的容器。不同于std::vector和std::list，ObserverList可以在迭代期间修改此容器，而不会使迭代器失效。因此，当观察者被通知时，它安全地处理观察者从列表中移除自身或其他观察者的情况。  
头文件：base/observer_list.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| AddObserver | M | 添加一个观察者 |
| RemoveObserver | M | 移除一个观察者 |
| HasObserver | M | 当前观察者列表中是否存在给定的观察者 |
| Clear | M | 清除当前列表中的所有观察者 |
| size | M | 返回当前列表的大小 |
| FOR_EACH_OBSERVER | G | 遍历当前观察者列表，func是观察者需要执行的成员函数 |

### 30. base::ObserverListThreadSafe
描述：观察者列表的线程安全实现。  
头文件：base/observer_list_threadsafe.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| AddObserver | M | 添加一个观察者，内部有锁。如果当前执行线程不存在message loop，添加操作不会成功 |
| RemoveObserver | M | 移除一个观察者，内部有锁 |
| Notify | M | 通知观察者，真正的执行在添加时的message loop中 |

### 31. base::PathService
描述：获取路径  
头文件：base/path_service.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| Get | S | 获取给定的Key所代表的路径，关于key可以参考：base_paths.h，base_paths_mac.h，base_paths_win.h，base_paths_posix.h |
| Override | S | 通过给定的路径覆写key所代表的路径，DIR_CURRENT 无法修改 |
| OverrideAndCreateIfNeeded | S | 与Overrride类似，不同点在于可以决定是否创建在key所代表的路径不存在时 |
| RegisterProvider | S | 注册新的provider，调用此函数之后Get调用将会执行指定的ProviderFunc |

### 32. base::PendingTask
描述：待处理任务，存储在TaskQueue和DelayedTaskQueue中，供队列和执行任务的类使用。主要的使用场景是：提前将一堆需要执行的Task存储在TaskQueue或DelayedTaskQueue中，根据时间排序执行。  
头文件：base/pengding_task.h  

### 33. base::PickleIterator
描述：base::Pickle的读取迭代器。    
头文件：base/pickle.h  
API：  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
| ReadBool | M | 读取bool类型值 |

### 34. base::Pickle
描述：提供基本二进制值的序列化和反序列化。Pickle类支持将原始值（整数，字符串等）附加到pickle实例。Pickle实例动态增长其内部内存缓冲区以保存原始值序列，内部存储器缓冲区作为Pickle的“数据”公开，这个“数据”可以传递给Pickle对象以初始化它以供读取。从Pickle对象读取时，使用者必须知道要读取的值类型以及读取它们的顺序，因为Pickle不会跟踪写入其中的数据类型。Pickle的数据有一个header，其中包含Pickle有效负载的大小，它可以选择支持header中的额外空间，该空间由传递给Pickle构造函数的header_size参数控制。      
头文件：base/pickle.h  
API:  

| 函数名 | 属性 | 说明 |
| ------ | :------: | ------ |
