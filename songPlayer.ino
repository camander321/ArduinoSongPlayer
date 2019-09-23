
#include <Math.h>

int speaker = 12;   // speaker output pin
int bpm = 120;


/* 
 * song notes. Each note is represented by 5 characters as follows
 * 1. note letter: 'A' 'B' 'C' ... 'G'
 * 2. key signature: flat = 'b'; sharp = 's'; natural = 'n'
 * 3. octave #: middle C is 4th octave, so middle C would be '4'. an active starts at C so B before middle C would be '3'
 * 4. note duration: whole = '1'; half = '2'; quarter = '4'; eighth = '8'; 16th = '6'; 32nd = '3'
 * 5. delimiter: this can be any single character, including a space (I like '|'). purely for user convenience
 * 
 * note: you may remove all delimiter chars if you choose to save space. just be sure to change 'noteSizeInString' to 4
 */
char nggyu[] =
"R008|Bb38|Cn48|Db48|Db48|Eb48|Cn48|Cn46|Bb36|Ab32|R004|R008|Bb38|"
"Bb38|Cn48|Db48|Bb38|R008|Ab38|Ab48|R008|Ab48|Eb42|R008|Bb38|Bb38|Cn48|Db48|Bb38|Db48|Eb48|R008|Cn48|"
"Bb38|Bb38|Ab34|Ab38|R004|Bb38|Bb38|Cn48|Db48|Bb38|Ab38|R008|Eb48|Eb48|Eb48|Fn48|Eb44|R004|Db42|Db48|"
"Eb48|Fn48|Db48|Eb48|Eb48|Eb48|Fn48|Eb48|Ab38|Ab34|Ab38|R008|R004|Bb38|Cn48|Db48|Bb34|Eb48|"
"Fn48|Eb48|Eb44|R008|Ab36|Bb36|Db46|Bb36|Fn48|Fn46|Fn48|Eb44|R008|Ab36|Bb33|Db46|Bb36|Eb48|Eb46|Eb48|"
"Db48|Cn48|Bb38|Ab36|Bb33|Db46|Bb36|Db44|Eb48|Cn44|Ab38|R008|Ab38|Eb48}R008|Db44|R004|";

int noteSizeInString = 5;
float measureTime;
char* song;

void setup() {
  measureTime = 60000.00 * 4 / bpm;
  song = nggyu;
}

// formula for note frequency found here: https://pages.mtu.edu/~suits/NoteFreqCalcs.html
float getFreq(char note, char mod, char oct) {
  if(note == 'R') return 0;

  if(note >= 'C') oct--;
  int octMod = (oct - '4') * 12;
  
  int modHStep = 0;
  if(mod == 'b') modHStep = -1;
  else if (mod == 's') modHStep = 1;

  int noteMod = (note - 'A') * 2;
  if (note >= 'C') {
    noteMod--;
    if(note >= 'F')
      noteMod--;
  }

  float base = 440.0;
  int hSteps = octMod + noteMod + modHStep;
  float a = 1.059463094359;

  float freq = base * pow(a, hSteps);

  return freq;
}

void playNote(char note, char mod, char oct, char dur) {
  int freq = round(getFreq(note, mod, oct));
  int duration = dur - '0';
  if(duration == 6) duration = 16;
  if(duration == 3) duration = 32;
  int noteLength = measureTime / (duration);
  tone(speaker, freq, noteLength);
  delay(noteLength);
}

void loop() {
  for (int i = 0; song[i*noteSizeInString] != 0; i++) {
    playNote(song[i*noteSizeInString], song[i*noteSizeInString+1], song[i*noteSizeInString+2], song[i*noteSizeInString+3]);
  }
  while(1) delay(10000);
}
