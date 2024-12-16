#include "SoundStrategy.h"
#include "SoundMute.h"
#include "SoundPlay.h"

//Constructor that creates and sets pattern
SoundStrategy::SoundStrategy(MuteEvents m) {
	mute = new SoundMute();
	play = new SoundPlay();
	if (m == MuteEvents::Mute) {
		currPat = mute;
	}
	else if (m == MuteEvents::Unmute) {
		currPat = play;
	}
	else {
		currPat = play;
	}
}

//Deletes Patterns
SoundStrategy::~SoundStrategy() {
	delete mute;
	delete play;
}

//Process Sounds
void SoundStrategy::ProcessSound() {
	currPat->process();
}

//Sends Commands
void SoundStrategy::SendCommand(CommandSound* c) {
	currPat->send(c);
}

//In charge of changing patterns
void SoundStrategy::changePat(MuteEvents m) {
	if (m == MuteEvents::Mute) {
		currPat = mute;
	}
	else if (m == MuteEvents::Unmute) {
		currPat = play;
	}
	else {
		currPat = play;
	}
}

void SoundStrategy::process() {}
void SoundStrategy::send(CommandSound* c) {}