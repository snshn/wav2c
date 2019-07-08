#include <sndfile.h>

int main(int argc, char * argv[])
{
    char * filename;
    SF_INFO file_infos;
    SNDFILE * file;
    sf_count_t i;

    if (argc < 2) {
        printf("Please specify file\n");
        return 1;
    }

    filename = argv[1];
    file = sf_open(filename, SFM_READ, &file_infos);

    if (!file) {
        printf("Unable to open sound file\n");
        return 1;
    }

    sf_count_t sample_number = file_infos.channels * file_infos.frames;
    short samples[sample_number];
    sf_read_short(file, samples, sample_number);

    sf_close(file);

    printf("\n/*\n");
    printf("File: %s\n", filename);
    printf("Channel(s): %d\n", file_infos.channels);
    printf("Frames: %lld\n", file_infos.frames);
    printf("Bitrate: %d\n", file_infos.samplerate);
    printf("Format: %d\n", file_infos.format);
    printf("*/\n");
    printf("ALshort sound[] = { ");
    for (i = 0; i < sample_number; i++) {
        printf("%d%c", samples[i], i < sample_number-1 ? ',' : ' ');
    }
    printf("};\n\n");
    printf("alBufferData(buffer, AL_FORMAT_%s16, sound, sizeof(sound), %d);\n\n",
        file_infos.channels == 1 ? "MONO" : "STEREO",
        file_infos.samplerate
    );

    return 0;
}
