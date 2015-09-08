#ifndef footizenaudiofoo
#define footizenaudiofoo

/*
 * audio-hal
 *
 * Copyright (c) 2000 - 2013 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define AUDIO_REVISION                  1

/* Error code */

#define AUDIO_IS_ERROR(ret)             (ret < 0)

typedef enum audio_return {
    AUDIO_RET_OK                        = 0,
    AUDIO_RET_USE_HW_CONTROL            = (int32_t)0x40001000,
    AUDIO_ERR_UNDEFINED                 = (int32_t)0x80001000,
    AUDIO_ERR_RESOURCE                  = (int32_t)0x80001001,
    AUDIO_ERR_PARAMETER                 = (int32_t)0x80001002,
    AUDIO_ERR_IOCTL                     = (int32_t)0x80001003,
    AUDIO_ERR_NOT_IMPLEMENTED           = (int32_t)0x80001004,
} audio_return_t ;


/* Session */
typedef enum audio_session {
    AUDIO_SESSION_MEDIA,
    AUDIO_SESSION_VOICECALL,
    AUDIO_SESSION_VIDEOCALL,
    AUDIO_SESSION_VOIP,
    AUDIO_SESSION_FMRADIO,
    AUDIO_SESSION_CAMCORDER,
    AUDIO_SESSION_NOTIFICATION,
    AUDIO_SESSION_ALARM,
    AUDIO_SESSION_EMERGENCY,
    AUDIO_SESSION_VOICE_RECOGNITION,
    AUDIO_SESSION_MAX
} audio_session_t;

/* Sub session */
typedef enum audio_subsession {
    AUDIO_SUBSESSION_NONE,
    AUDIO_SUBSESSION_VOICE,
    AUDIO_SUBSESSION_RINGTONE,
    AUDIO_SUBSESSION_MEDIA,
    AUDIO_SUBSESSION_INIT,
    AUDIO_SUBSESSION_VR_NORMAL,
    AUDIO_SUBSESSION_VR_DRIVE,
    AUDIO_SUBSESSION_STEREO_REC,
    AUDIO_SUBSESSION_MONO_REC,
    AUDIO_SUBSESSION_MAX
} audio_subsession_t;

/* Session command */
typedef enum audio_session_command {
    AUDIO_SESSION_CMD_START,
    AUDIO_SESSION_CMD_SUBSESSION,
    AUDIO_SESSION_CMD_END,
} audio_session_command_t;


/* Direction */
typedef enum audio_direction {
    AUDIO_DIRECTION_NONE,
    AUDIO_DIRECTION_IN,                 /**< Capture */
    AUDIO_DIRECTION_OUT,                /**< Playback */
} audio_direction_t;


/* Device */

typedef enum audio_device_in {
    AUDIO_DEVICE_IN_NONE,
    AUDIO_DEVICE_IN_MIC,                /**< Device builtin mic. */
    AUDIO_DEVICE_IN_WIRED_ACCESSORY,    /**< Wired input devices */
    AUDIO_DEVICE_IN_BT_SCO,             /**< Bluetooth SCO device */
    AUDIO_DEVICE_IN_MAX,
} audio_device_in_t;

typedef enum audio_device_out {
    AUDIO_DEVICE_OUT_NONE,
    AUDIO_DEVICE_OUT_SPEAKER,           /**< Device builtin speaker */
    AUDIO_DEVICE_OUT_RECEIVER,          /**< Device builtin receiver */
    AUDIO_DEVICE_OUT_WIRED_ACCESSORY,   /**< Wired output devices such as headphone, headset, and so on. */
    AUDIO_DEVICE_OUT_BT_SCO,            /**< Bluetooth SCO device */
    AUDIO_DEVICE_OUT_BT_A2DP,           /**< Bluetooth A2DP device */
    AUDIO_DEVICE_OUT_DOCK,              /**< DOCK device */
    AUDIO_DEVICE_OUT_HDMI,              /**< HDMI device */
    AUDIO_DEVICE_OUT_MIRRORING,         /**< MIRRORING device */
    AUDIO_DEVICE_OUT_USB_AUDIO,         /**< USB Audio device */
    AUDIO_DEVICE_OUT_MULTIMEDIA_DOCK,   /**< Multimedia DOCK device */
    AUDIO_DEVICE_OUT_MAX,
} audio_device_out_t;

typedef enum audio_route_flag {
    AUDIO_ROUTE_FLAG_NONE               = 0,
    AUDIO_ROUTE_FLAG_MUTE_POLICY        = 0x00000001,
    AUDIO_ROUTE_FLAG_DUAL_OUT           = 0x00000002,
    AUDIO_ROUTE_FLAG_NOISE_REDUCTION    = 0x00000010,
    AUDIO_ROUTE_FLAG_EXTRA_VOL          = 0x00000020,
    AUDIO_ROUTE_FLAG_NETWORK_WB         = 0x00000040,
    AUDIO_ROUTE_FLAG_BT_WB              = 0x00000100,
    AUDIO_ROUTE_FLAG_BT_NREC            = 0x00000200,
    AUDIO_ROUTE_FLAG_VOICE_COMMAND      = 0x00040000,
} audio_route_flag_t;

typedef enum audio_device_api {
    AUDIO_DEVICE_API_UNKNOWN,
    AUDIO_DEVICE_API_ALSA,
    AUDIO_DEVICE_API_BLUEZ,
} audio_device_api_t;

typedef enum audio_device_param {
    AUDIO_DEVICE_PARAM_NONE,
    AUDIO_DEVICE_PARAM_CHANNELS,
    AUDIO_DEVICE_PARAM_SAMPLERATE,
    AUDIO_DEVICE_PARAM_FRAGMENT_SIZE,
    AUDIO_DEVICE_PARAM_FRAGMENT_NB,
    AUDIO_DEVICE_PARAM_START_THRESHOLD,
    AUDIO_DEVICE_PARAM_USE_MMAP,
    AUDIO_DEVICE_PARAM_USE_TSCHED,
    AUDIO_DEVICE_PARAM_TSCHED_BUF_SIZE,
    AUDIO_DEVICE_PARAM_SUSPEND_TIMEOUT,
    AUDIO_DEVICE_PARAM_ALTERNATE_RATE,
    AUDIO_DEVICE_PARAM_MAX,
} audio_device_param_t;

typedef struct audio_device_param_info {
    audio_device_param_t param;
    union {
        int64_t s64_v;
        uint64_t u64_v;
        int32_t s32_v;
        uint32_t u32_v;
    };
} audio_device_param_info_t;

typedef struct audio_device_alsa_info {
    char *card_name;
    uint32_t card_idx;
    uint32_t device_idx;
} audio_device_alsa_info_t;

typedef struct audio_device_bluz_info {
    char *protocol;
    uint32_t nrec;
} audio_device_bluez_info_t;

typedef struct audio_device_info {
    audio_device_api_t api;
    audio_direction_t direction;
    char *name;
    uint8_t is_default_device;
    union {
        audio_device_alsa_info_t alsa;
        audio_device_bluez_info_t bluez;
    };
} audio_device_info_t;


/* Stream */

typedef enum audio_volume {
    AUDIO_VOLUME_TYPE_SYSTEM,           /**< System volume type */
    AUDIO_VOLUME_TYPE_NOTIFICATION,     /**< Notification volume type */
    AUDIO_VOLUME_TYPE_ALARM,            /**< Alarm volume type */
    AUDIO_VOLUME_TYPE_RINGTONE,         /**< Ringtone volume type */
    AUDIO_VOLUME_TYPE_MEDIA,            /**< Media volume type */
    AUDIO_VOLUME_TYPE_CALL,             /**< Call volume type */
    AUDIO_VOLUME_TYPE_VOIP,             /**< VOIP volume type */
    AUDIO_VOLUME_TYPE_VOICE,            /**< Voice volume type */
    AUDIO_VOLUME_TYPE_FIXED,            /**< Volume type for fixed acoustic level */
    AUDIO_VOLUME_TYPE_MAX,              /**< Volume type count */
} audio_volume_t;

typedef enum audio_gain {
    AUDIO_GAIN_TYPE_DEFAULT,
    AUDIO_GAIN_TYPE_DIALER,
    AUDIO_GAIN_TYPE_TOUCH,
    AUDIO_GAIN_TYPE_AF,
    AUDIO_GAIN_TYPE_SHUTTER1,
    AUDIO_GAIN_TYPE_SHUTTER2,
    AUDIO_GAIN_TYPE_CAMCODING,
    AUDIO_GAIN_TYPE_MIDI,
    AUDIO_GAIN_TYPE_BOOTING,
    AUDIO_GAIN_TYPE_VIDEO,
    AUDIO_GAIN_TYPE_TTS,
    AUDIO_GAIN_TYPE_MAX,
} audio_gain_t;

typedef struct audio_stream_info {
    char *name;
    uint32_t samplerate;
    uint8_t channels;
    uint32_t volume_type;
    uint32_t gain_type;
} audio_stream_info_t ;


/* Overall */

typedef struct audio_info {
    audio_device_info_t device;
    audio_stream_info_t stream;
} audio_info_t;

typedef struct audio_cb_interface {
    audio_return_t (*load_device)(void *platform_data, audio_device_info_t *device_info, audio_device_param_info_t *params);
    audio_return_t (*open_device)(void *platform_data, audio_device_info_t *device_info, audio_device_param_info_t *params);
    audio_return_t (*close_all_devices)(void *platform_data);
    audio_return_t (*close_device)(void *platform_data, audio_device_info_t *device_info);
    audio_return_t (*unload_device)(void *platform_data, audio_device_info_t *device_info);
} audio_cb_interface_t;

typedef struct audio_interface {
    audio_return_t (*init)(void **userdata, void *platform_data);
    audio_return_t (*deinit)(void **userdata);
    audio_return_t (*reset)(void **userdata);
    audio_return_t (*set_callback)(void *userdata, audio_cb_interface_t *cb_interface);
    audio_return_t (*get_volume_level_max)(void *userdata, uint32_t volume_type, uint32_t *level);
    audio_return_t (*get_volume_level)(void *userdata, uint32_t volume_type, uint32_t *level);
    audio_return_t (*get_volume_value)(void *userdata, audio_info_t *info, uint32_t volume_type, uint32_t level, double *value);
    audio_return_t (*set_volume_level)(void *userdata, audio_info_t *info, uint32_t volume_type, uint32_t level);
    audio_return_t (*set_volume_value)(void *userdata, audio_info_t *info, uint32_t volume_type, double* value);
    audio_return_t (*get_gain_value)(void *userdata, audio_info_t *info, uint32_t volume_type, double *value);
    audio_return_t (*get_mute)(void *userdata, audio_info_t *info, uint32_t volume_type, uint32_t direction, uint32_t *mute);
    audio_return_t (*set_mute)(void *userdata, audio_info_t *info, uint32_t volume_type, uint32_t direction, uint32_t mute);
    audio_return_t (*set_session)(void *userdata, uint32_t session, uint32_t subsession, uint32_t cmd);
    audio_return_t (*set_route)(void *userdata, uint32_t session, uint32_t subsession, uint32_t device_in, uint32_t device_out, uint32_t route_flag);
    audio_return_t (*alsa_pcm_open)(void *userdata, void **pcm_handle, char *device_name, uint32_t direction, int mode);
    audio_return_t (*alsa_pcm_close)(void *userdata, void *pcm_handle);
    audio_return_t (*set_mixer_value_string)(void *userdata, const char* ctl, const char* value);

} audio_interface_t;

int audio_get_revision (void);
audio_return_t audio_init (void **userdata, void *platform_data);
audio_return_t audio_deinit (void **userdata);
audio_return_t audio_reset (void **userdata);
audio_return_t audio_get_volume_level_max (void *userdata, uint32_t volume_type, uint32_t *level);
audio_return_t audio_get_volume_level (void *userdata, uint32_t volume_type, uint32_t *level);
audio_return_t audio_get_volume_value (void *userdata, audio_info_t *info, uint32_t volume_type, uint32_t level, double *value);
audio_return_t audio_set_volume_level (void *userdata, audio_info_t *info, uint32_t volume_type, uint32_t level);
audio_return_t audio_set_volume_value (void *userdata, audio_info_t *info, uint32_t volume_type, double* value);
audio_return_t audio_get_gain_value (void *userdata, audio_info_t *info, uint32_t volume_type, double *value);
audio_return_t audio_get_mute (void *userdata, audio_info_t *info, uint32_t volume_type, uint32_t direction, uint32_t *mute);
audio_return_t audio_set_mute (void *userdata, audio_info_t *info, uint32_t volume_type, uint32_t direction, uint32_t mute);
audio_return_t audio_set_session (void *userdata, uint32_t session, uint32_t subsession, uint32_t cmd);
audio_return_t audio_alsa_pcm_open (void *userdata, void **pcm_handle, char *device_name, uint32_t direction, int mode);
audio_return_t audio_alsa_pcm_close (void *userdata, void *pcm_handle);
audio_return_t audio_set_route (void *userdata, uint32_t session, uint32_t subsession, uint32_t device_in, uint32_t device_out, uint32_t route_flag);
#endif
