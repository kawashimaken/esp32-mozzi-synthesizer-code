#include "song_library.h"
#include "songs/eurobeat/structure.h"
#include "songs/eurobeat/drums.h"
#include "songs/eurobeat/melody.h"
#include "songs/hiphop/structure.h"
#include "songs/hiphop/drums.h"
#include "songs/hiphop/melody.h"
#include "songs/kpop/structure.h"
#include "songs/kpop/drums.h"
#include "songs/kpop/melody.h"
#include "songs/ambient/structure.h"
#include "songs/ambient/drums.h"
#include "songs/ambient/melody.h"
#include "songs/classical/structure.h"
#include "songs/classical/drums.h" 
#include "songs/classical/melody.h"

int current_song_id = SONG_EUROBEAT;

static const SongInfo song_database[MAX_SONGS] = {
    {"Eurobeat Dance",
     "Eurobeat/Dance",
     120,
     eurobeat_song_structure,
     eurobeat_drum_patterns,
     eurobeat_melo_patterns,
     eurobeat_melo_trig_patterns},
    {"Hiphop",
     "Hiphop",
     120,
     hiphop_song_structure,
     hiphop_drum_patterns,
     hiphop_melo_patterns,
     hiphop_melo_trig_patterns},
    {"Kpop",
     "Kpop",
     120,
     kpop_song_structure,
     kpop_drum_patterns,
     kpop_melo_patterns,
     kpop_melo_trig_patterns},
    {"Ambient",
     "Ambient",
     120,
     ambient_song_structure,
     ambient_drum_patterns,
     ambient_melo_patterns,
     ambient_melo_trig_patterns},
    {"Mozart Electronica",
     "Classical/Electronic",
     100,
     classical_song_structure,
     classical_drum_patterns,
     classical_melo_patterns,
     classical_melo_trig_patterns}
};

void init_song_library()
{
    current_song_id = SONG_EUROBEAT;
    Serial.println("Song library initialized");
}

void set_current_song(int song_id)
{
    if (song_id >= 0 && song_id < MAX_SONGS && song_database[song_id].title != nullptr)
    {
        current_song_id = song_id;
        Serial.print("Switched to song: ");
        Serial.println(song_database[current_song_id].title);
    }
}

const SongInfo *get_current_song_info()
{
    return &song_database[current_song_id];
}

int get_song_count()
{
    int count = 0;
    for (int i = 0; i < MAX_SONGS; i++)
    {
        if (song_database[i].title != nullptr)
            count++;
    }
    return count;
}