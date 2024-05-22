#include <stdio.h>
#include <stdint.h>
#include <alsa/asoundlib.h>

#define CHANNELS 1
#define FORMAT SND_PCM_FORMAT_S16_LE

int main() {
    int err;
    unsigned sample_rate = 8000;
    int16_t buffer[1024];

    FILE *file = fopen("audio_data.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Открытие PCM устройства в режиме воспроизведения
    snd_pcm_t *handle;
    err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        fprintf(stderr, "Unable to open PCM device: %s\n", snd_strerror(err));
        return 1;
    }

    // Установка параметров PCM устройства
    snd_pcm_hw_params_t *params;
    snd_pcm_hw_params_malloc(&params);
    snd_pcm_hw_params_any(handle, params);
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, FORMAT);
    snd_pcm_hw_params_set_channels(handle, params, CHANNELS);
    snd_pcm_hw_params_set_rate_near(handle, params, &sample_rate, 0);
    snd_pcm_hw_params(handle, params);
    snd_pcm_hw_params_free(params);

    // Воспроизведение аудиоданных
    while (fread(buffer, sizeof(int16_t), sizeof(buffer) / sizeof(int16_t), file) > 0) {
        err = snd_pcm_writei(handle, buffer, sizeof(buffer) / sizeof(int16_t));
        if (err < 0) {
            fprintf(stderr, "Error playing audio: %s\n", snd_strerror(err));
            break;
        }
    }

    // Закрытие PCM устройства и файла
    snd_pcm_close(handle);
    fclose(file);

    return 0;
}