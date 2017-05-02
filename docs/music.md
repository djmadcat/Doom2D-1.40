## Digital Music Instrument (DMI)

### File Structure

```c
typedef struct {
    uint16_t   blockSize;
    uint16_t   sampleRate;
    uint16_t   loopStart;
    uint16_t   loopLength;
} DMI_Header;
```

```c
typedef struct {
    DMI_Header  header;
    int8_t      soundData[];
} DMI_File;
```

All int-types in `DMI_Header` is in the little-endian format.

* `blockSize` is the size of `soundData`, in bytes.
* `sampleRate` is the sample rate at which the sound is to be played back, in sample frames per second (e.g. 11025, 22050, 44100, etc).
* `loopStart` is the offset from `soundData` that marks the begin position of the loop segment, in bytes.
* `loopLength` is the length of a loop, in bytes.
* `soundData` contains the sound data that make up the sound. Always stored in "LPCM 16bit Mono".

#### Looping

Sound data can be looped, allowing a portion of the sound to be repeated in order to lengthen the
sound.<br/>
A loop is marked with two points, a begin position and length.<br/>
Playback begins at the beginning of the sound, continues past the begin position and continues throughout the entire length, at which point playback restarts again at the begin position.<br/>
The loop segment is played over and over again, until interrupted by something, such as the release of a key on a sampling instrument.<br/>
If the loop length is zero, then no looping takes place.<br/>
