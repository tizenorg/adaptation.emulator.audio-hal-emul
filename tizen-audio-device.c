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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tizen-audio-internal.h"

audio_return_t _audio_device_init (audio_mgr_t *am)
{
    AUDIO_RETURN_VAL_IF_FAIL(am, AUDIO_ERR_PARAMETER);

    am->device.active_in = AUDIO_DEVICE_IN_NONE;
    am->device.active_out = AUDIO_DEVICE_OUT_NONE;
    am->device.route_flag = AUDIO_ROUTE_FLAG_NONE;
    am->device.pcm_in = NULL;
    am->device.pcm_out = NULL;
    pthread_mutex_init(&am->device.pcm_lock, NULL);
    am->device.pcm_count = 0;

    return AUDIO_RET_OK;
}

audio_return_t _audio_device_deinit (audio_mgr_t *am)
{
    AUDIO_RETURN_VAL_IF_FAIL(am, AUDIO_ERR_PARAMETER);

    return AUDIO_RET_OK;
}

audio_return_t _reset_route (audio_mgr_t *am, int need_inactive)
{
    AUDIO_RETURN_VAL_IF_FAIL(am, AUDIO_ERR_PARAMETER);

    return AUDIO_RET_OK;
}

audio_return_t audio_set_route (void *userdata, uint32_t session, uint32_t subsession, uint32_t device_in, uint32_t device_out, uint32_t route_flag)
{
    audio_mgr_t *am = (audio_mgr_t *)userdata;

    am->device.active_in = device_in;
    am->device.active_out = device_out;
    am->device.route_flag = route_flag;

    AUDIO_RETURN_VAL_IF_FAIL(am, AUDIO_ERR_PARAMETER);

    AUDIO_LOG_INFO("session:%d,%d in:%d out:%d flag:0x%x", session, subsession, device_in, device_out, route_flag);

    /* TODO. set route path */

    return AUDIO_RET_OK;
}

audio_return_t audio_alsa_pcm_open (void *userdata, void **pcm_handle, char *device_name, uint32_t direction, int mode)
{
    audio_return_t audio_ret = AUDIO_RET_OK;
    audio_mgr_t *am = (audio_mgr_t *)userdata;
    int err;

    AUDIO_RETURN_VAL_IF_FAIL(am, AUDIO_ERR_PARAMETER);

//    pthread_mutex_lock(&am->device.pcm_lock);
   if ((err = snd_pcm_open((snd_pcm_t **)pcm_handle, device_name, (direction == AUDIO_DIRECTION_OUT) ? SND_PCM_STREAM_PLAYBACK : SND_PCM_STREAM_CAPTURE, mode)) < 0) {
        AUDIO_LOG_ERROR("Error opening PCM device %s: %s", device_name, snd_strerror(err));
        pthread_mutex_unlock(&am->device.pcm_lock);
        return AUDIO_ERR_RESOURCE;
    }
    am->device.pcm_count++;
    AUDIO_LOG_INFO("PCM handle 0x%x(%s,%s) opened(count:%d)", *pcm_handle, device_name, (direction == AUDIO_DIRECTION_OUT) ? "playback" : "capture", am->device.pcm_count);
//    pthread_mutex_unlock(&am->device.pcm_lock);

    return audio_ret;
}

audio_return_t audio_alsa_pcm_close (void *userdata, void *pcm_handle)
{
    audio_return_t audio_ret = AUDIO_RET_OK;
    audio_mgr_t *am = (audio_mgr_t *)userdata;
    int err;

    AUDIO_LOG_INFO("Try to close PCM handle 0x%x", pcm_handle);
//    pthread_mutex_lock(&am->device.pcm_lock);
    if ((err = snd_pcm_close(pcm_handle)) < 0) {
        AUDIO_LOG_ERROR("Error closing PCM handle : %s", snd_strerror(err));
        pthread_mutex_unlock(&am->device.pcm_lock);
        return AUDIO_ERR_RESOURCE;
    }

    am->device.pcm_count--;
    AUDIO_LOG_INFO("PCM handle close success (count:%d)", am->device.pcm_count);
//    pthread_mutex_unlock(&am->device.pcm_lock);

    return audio_ret;
}
