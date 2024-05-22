#include <stdio.h>
#include <stdint.h>
#include <alsa/asoundlib.h>

#define SAMPLE_SIZE 160  // Размер одного сэмпла (миллисекунды) для G.711 (A-law)

int encode(uint8_t *data_in, int16_t *data_out, int size) {
    // Применяем му-закон для каждого 8-битного входного значения
    for (int i = 0; i < size; ++i) {
        // Применяем формулу му-закона
        int sample = (int)data_in[i] - 128; // Преобразуем беззнаковое значение к знаковому
        sample = (sample << 7) + 0x8000; // Применяем масштабирование и смещение
        data_out[i] = (int16_t)sample; // Преобразуем обратно к 16-битному значению
    }
    return size;
}

int main() {
    int err;
    uint8_t buffer[SAMPLE_SIZE];
    int16_t encoded_data[SAMPLE_SIZE];
    unsigned int sample_rate = 8000; // Частота дискретизации 8000 Гц

    FILE *file = fopen("audio_data.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;

    // Открытие устройства захвата звука (микрофона)
    err = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
    if (err < 0) {
        fprintf(stderr, "Unable to open PCM device: %s\n", snd_strerror(err));
        return 1;
    }

    // Установка параметров захвата звука
    snd_pcm_hw_params_malloc(&params);
    snd_pcm_hw_params_any(handle, params);
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(handle, params, 1);
    snd_pcm_hw_params_set_rate_near(handle, params, &sample_rate, &err);
    if (err < 0) {
        fprintf(stderr, "Unable to set sample rate: %s\n", snd_strerror(err));
        return 1;
    }

    // Применение установленных параметров
    err = snd_pcm_hw_params(handle, params);
    if (err < 0) {
        fprintf(stderr, "Unable to set HW parameters: %s\n", snd_strerror(err));
        return 1;
    }

    // Запись данных с микрофона в файл
    while (1) {
        err = snd_pcm_readi(handle, buffer, SAMPLE_SIZE);
        if (err < 0) {
            fprintf(stderr, "Error capturing audio: %s\n", snd_strerror(err));
            break;
        }
        int encoded_size = encode(buffer, encoded_data, SAMPLE_SIZE);
        fwrite(encoded_data, sizeof(int16_t), encoded_size, file);
    }

    // Освобождение ресурсов
    fclose(file);
    snd_pcm_hw_params_free(params);
    snd_pcm_close(handle);

    return 0;
}