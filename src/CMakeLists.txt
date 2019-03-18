cmake_minimum_required(VERSION 3.6)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(base)
enable_language(CXX)

set(BASE_TARGET_NAME "base")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if(x86 MATCHES ${BASE_ARCH_PLATFORM})
    if(Linux MATCHES ${BASE_BUILD_PLATFORM} OR Android MATCHES ${BASE_BUILD_PLATFORM})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    endif()

    if(macOSX MATCHES ${BASE_BUILD_PLATFORM})
        set(CMAKE_OSX_ARCHITECTURES x86)
    endif()
endif()

if(x64 MATCHES ${BASE_ARCH_PLATFORM})
    if(Linux MATCHES ${BASE_BUILD_PLATFORM} OR Android MATCHES ${BASE_BUILD_PLATFORM})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    endif()

    if(macOSX MATCHES ${BASE_BUILD_PLATFORM})
        set(CMAKE_OSX_ARCHITECTURES x86_64)
    endif()
endif()

message(STATUS *******************************************************)
message(STATUS CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME})
message(STATUS CMAKE_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION})
message(STATUS CMAKE_HOST_SYSTEM_NAME=${CMAKE_HOST_SYSTEM_NAME})
message(STATUS CMAKE_GENERATOR=${CMAKE_GENERATOR})
message(STATUS CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
message(STATUS CMAKE_CONFIGURATION_TYPES=${CMAKE_CONFIGURATION_TYPES})
message(STATUS CMAKE_C_COMPILER=${CMAKE_C_COMPILER})
message(STATUS CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER})
message(STATUS CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES=${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES})
message(STATUS CMAKE_CXX_STANDARD_LIBRARIES=${CMAKE_CXX_STANDARD_LIBRARIES})
message(STATUS CMAKE_C_FLAGS=${CMAKE_C_FLAGS})
message(STATUS CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS})
message(STATUS CMAKE_SHARED_LINKER_FLAGS=${CMAKE_SHARED_LINKER_FLAGS})
message(STATUS CMAKE_MODULE_LINKER_FLAGS=${CMAKE_MODULE_LINKER_FLAGS})
message(STATUS CMAKE_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS})
message(STATUS CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR})
message(STATUS CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR})
message(STATUS CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
message(STATUS CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME})
message(STATUS CMAKE_FIND_LIBRARY_SUFFIXES=${CMAKE_FIND_LIBRARY_SUFFIXES})
message(STATUS CMAKE_STATIC_LIBRARY_PREFIX=${CMAKE_STATIC_LIBRARY_PREFIX})
message(STATUS *******************************************************)

set(BASE_PLATFORM_SOURCE)
set(BASE_PLATFORM_DEFINITIONS)
set(BASE_LINK_PLATFORM_LIBRARIES)
set(BASE_INCLUDE_PLATFORM_DIRECTORIES)
if(Linux MATCHES ${BASE_BUILD_PLATFORM})
    set(BASE_BUILD_CONFIGURATION_TYPE SHARED)

    set(BASE_PLATFORM_DEFINITIONS 
        -DUSE_SYSTEM_LIBEVENT
    )

    set(BASE_LINK_PLATFORM_LIBRARIES    
        glib-2.0
        pthread
    )

    set(BASE_INCLUDE_PLATFORM_DIRECTORIES   
        /usr/local/include/glib-2.0
        /usr/local/lib/glib-2.0/include # for glibconfig.h
    )

    set(BASE_PLATFORM_SOURCE  
        base/atomicops_internals_x86_gcc.h
        base/atomicops_internals_x86_gcc.cc
        
        base/base_paths_posix.cc
        base/base_paths_posix.h
        base/file_descriptor_posix.h
        base/file_util_posix.cc
        base/global_descriptors_posix.cc
        base/global_descriptors_posix.h
        base/guid_posix.cc
        base/hi_res_timer_manager_posix.cc
        base/native_library_posix.cc
        base/platform_file_posix.cc
        base/process_posix.cc
        base/process_util_posix.cc
        base/rand_util_posix.cc
        base/safe_strerror_posix.cc
        base/safe_strerror_posix.h
        base/shared_memory_posix.cc
        base/string_util_posix.h
        base/sync_socket_posix.cc
        base/sys_info_posix.cc
        base/sys_string_conversions_posix.cc
        base/time_posix.cc
        base/debug/stack_trace_posix.cc
        base/files/dir_reader_posix.h
        base/synchronization/condition_variable_posix.cc
        base/synchronization/lock_impl_posix.cc
        base/synchronization/waitable_event_posix.cc
        base/synchronization/waitable_event_watcher_posix.cc
        base/system_monitor/system_monitor_posix.cc
        base/threading/platform_thread_posix.cc
        base/threading/thread_local_posix.cc
        base/threading/thread_local_storage_posix.cc
        base/threading/worker_pool_posix.cc
        base/threading/worker_pool_posix.h
        base/file_util_linux.cc
        base/linux_util.cc
        base/linux_util.h
        base/process_linux.cc
        base/process_util_linux.cc
        base/sys_info_linux.cc
        base/files/dir_reader_linux.h
        base/files/file_path_watcher_linux.cc
        base/third_party/nspr/prcpucfg_linux.h
        base/message_pump_libevent.h
    )
endif()

set(BASE_INCLUDE_DIRECTORIES    
    .
    ./base
    ./build
)

set(BASE_LINK_DIRECTORIES   
)

set(BASE_DEFINITIONS    
    -DBASE_IMPLEMENTATION
    ${BASE_PLATFORM_DEFINITIONS}
)

set(BASE_SOURCE 
    base/atomicops.h
    base/atomic_ref_count.h
    base/atomic_sequence_num.h
    base/at_exit.h
    base/auto_reset.h
    base/base64.h
    base/base_export.h
    base/base_paths.h
    base/base_switches.h
    base/basictypes.h
    base/bind.h
    base/bind_helpers.h
    base/bind_internal.h
    base/bits.h
    base/build_time.h
    base/callback.h
    base/callback_forward.h
    base/callback_helpers.h
    base/callback_internal.h
    base/cancelable_callback.h
    base/command_line.h
    base/compiler_specific.h
    base/cpu.h
    base/critical_closure.h
    base/debug/alias.h
    base/debug/leak_tracker.h
    base/debug/stack_trace.h
    base/dispatchers.h
    base/eintr_wrapper.h
    base/environment.h
    base/event_types.h
    base/files/dir_reader_fallback.h
    base/files/file_path_watcher.h
    base/file_descriptor_shuffle.h
    base/file_path.h
    base/file_util.h
    base/file_util_proxy.h
    base/file_version_info.h
    base/float_util.h
    base/format_macros.h
    base/guid.h
    base/hash.h
    base/hash_tables.h
    base/hi_res_timer_manager.h
    base/id_map.h
    base/json/json_file_value_serializer.h
    base/json/json_parser.h
    base/json/json_reader.h
    base/json/json_string_value_serializer.h
    base/json/json_value_converter.h
    base/json/json_writer.h
    base/json/string_escape.h
    base/lazy_instance.h
    base/linked_list.h
    base/location.h
    base/logging.h
    base/md5.h
    base/memory/aligned_memory.h
    base/memory/linked_ptr.h
    base/memory/mru_cache.h
    base/memory/ref_counted.h
    base/memory/ref_counted_memory.h
    base/memory/scoped_handle.h
    base/memory/scoped_open_process.h
    base/memory/scoped_policy.h
    base/memory/scoped_ptr.h
    base/memory/scoped_vector.h
    base/memory/singleton.h
    base/memory/weak_ptr.h
    base/message_loop.h
    base/message_loop_proxy.h
    base/message_loop_proxy_impl.h
    base/message_pump.h
    base/message_pump_default.h
    base/message_pump_dispatcher.h
    base/message_pump_observer.h
    base/native_library.h
    base/nullable_string16.h
    base/observer_list.h
    base/observer_list_threadsafe.h
    base/path_service.h
    base/pending_task.h
    base/pickle.h
    base/platform_file.h
    base/port.h
    base/process.h
    base/process_info.h
    base/process_util.h
    base/rand_util.h
    base/run_loop.h
    base/scoped_native_library.h
    base/scoped_observer.h
    base/scoped_temp_dir.h
    base/sequenced_task_runner.h
    base/sequenced_task_runner_helpers.h
    base/sha1.h
    base/shared_memory.h
    base/single_thread_task_runner.h
    base/stack_container.h
    base/stl_util.h
    base/string16.h
    base/stringize_macros.h
    base/stringprintf.h
    base/string_number_conversions.h
    base/string_piece.h
    base/string_split.h
    base/string_tokenizer.h
    base/string_util.h
    base/supports_user_data.h
    base/synchronization/cancellation_flag.h
    base/synchronization/condition_variable.h
    base/synchronization/lock.h
    base/synchronization/lock_impl.h
    base/synchronization/spin_wait.h
    base/synchronization/waitable_event.h
    base/synchronization/waitable_event_watcher.h
    base/sync_socket.h
    base/system_monitor/system_monitor.h
    base/sys_byteorder.h
    base/sys_info.h
    base/sys_string_conversions.h
    base/task_runner.h
    base/task_runner_util.h
    base/template_util.h
    base/third_party/dmg_fp/dmg_fp.h
    base/third_party/icu/icu_utf.h
    base/third_party/modp_b64/modp_b64.h
    base/third_party/modp_b64/modp_b64_data.h
    base/third_party/nspr/prcpucfg.h
    base/third_party/nspr/prtime.h
    base/third_party/nspr/prtypes.h
    base/threading/non_thread_safe.h
    base/threading/non_thread_safe_impl.h
    base/threading/platform_thread.h
    base/threading/post_task_and_reply_impl.h
    base/threading/sequenced_worker_pool.h
    base/threading/simple_thread.h
    base/threading/thread.h
    base/threading/thread_checker.h
    base/threading/thread_checker_impl.h
    base/threading/thread_collision_warner.h
    base/threading/thread_local.h
    base/threading/thread_local_storage.h
    base/threading/thread_restrictions.h
    base/threading/watchdog.h
    base/threading/worker_pool.h
    base/thread_task_runner_handle.h
    base/base_time.h
    base/timer.h
    base/utf_offset_string_conversions.h
    base/utf_string_conversions.h
    base/utf_string_conversion_utils.h
    base/values.h
    base/value_conversions.h
    base/version.h
    base/vlog.h
    build/build_config.h
    base/at_exit.cc
    base/base64.cc
    base/base_paths.cc
    base/base_switches.cc
    base/bind_helpers.cc
    base/build_time.cc
    base/callback_internal.cc
    base/check_example.cc
    base/command_line.cc
    base/cpu.cc
    base/debug/alias.cc
    base/debug/stack_trace.cc
    base/environment.cc
    base/files/file_path_watcher.cc
    base/file_descriptor_shuffle.cc
    base/file_path.cc
    base/file_util.cc
    base/file_util_proxy.cc
    base/guid.cc
    base/hash.cc
    base/json/json_file_value_serializer.cc
    base/json/json_parser.cc
    base/json/json_reader.cc
    base/json/json_string_value_serializer.cc
    base/json/json_writer.cc
    base/json/string_escape.cc
    base/lazy_instance.cc
    base/location.cc
    base/logging.cc
    base/md5.cc
    base/memory/aligned_memory.cc
    base/memory/ref_counted.cc
    base/memory/ref_counted_memory.cc
    base/memory/singleton.cc
    base/memory/weak_ptr.cc
    base/message_loop.cc
    base/message_loop_proxy.cc
    base/message_loop_proxy_impl.cc
    base/message_pump.cc
    base/message_pump_default.cc
    base/path_service.cc
    base/pending_task.cc
    base/pickle.cc
    base/platform_file.cc
    base/process_util.cc
    base/rand_util.cc
    base/run_loop.cc
    base/scoped_native_library.cc
    base/scoped_temp_dir.cc
    base/sequenced_task_runner.cc
    base/sha1_portable.cc
    base/string16.cc
    base/stringprintf.cc
    base/string_number_conversions.cc
    base/string_piece.cc
    base/string_split.cc
    base/string_util.cc
    base/supports_user_data.cc
    base/synchronization/cancellation_flag.cc
    base/synchronization/lock.cc
    base/system_monitor/system_monitor.cc
    base/task_runner.cc
    base/third_party/dmg_fp/dtoa_wrapper.cc
    base/third_party/dmg_fp/g_fmt.cc
    base/third_party/icu/icu_utf.cc
    base/third_party/modp_b64/modp_b64.cc
    base/third_party/nspr/prtime.cc
    base/threading/non_thread_safe_impl.cc
    base/threading/post_task_and_reply_impl.cc
    base/threading/sequenced_worker_pool.cc
    base/threading/simple_thread.cc
    base/threading/thread.cc
    base/threading/thread_checker_impl.cc
    base/threading/thread_collision_warner.cc
    base/threading/thread_restrictions.cc
    base/threading/watchdog.cc
    base/threading/worker_pool.cc
    base/thread_task_runner_handle.cc
    base/base_time.cc
    base/timer.cc
    base/utf_offset_string_conversions.cc
    base/utf_string_conversions.cc
    base/utf_string_conversion_utils.cc
    base/values.cc
    base/value_conversions.cc
    base/version.cc
    base/vlog.cc
)

set(BASE_LINK_LIBRARIES 
)

include_directories(
    ${BASE_INCLUDE_DIRECTORIES}
    ${BASE_INCLUDE_PLATFORM_DIRECTORIES}
)

add_definitions(
    ${BASE_DEFINITIONS}
)

link_directories(
    ${BASE_LINK_DIRECTORIES}
)

add_library(${BASE_TARGET_NAME} ${BASE_BUILD_CONFIGURATION_TYPE}
    ${BASE_SOURCE}
    ${BASE_PLATFORM_SOURCE}
)

target_link_libraries(${BASE_TARGET_NAME}
    ${BASE_LINK_LIBRARIES}
    ${BASE_LINK_PLATFORM_LIBRARIES}
)

set_property(TARGET ${BASE_TARGET_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)