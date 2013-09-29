#pragma once

#include "ofMain.h"

class ofxImageAssets {
public:
    void add(string filename, bool preload=true);
    ofImage &operator[](const string& filename);
    map<string, ofImage*> assets;
};

class ofxVideoAssets {
public:
    void add(string filename, bool preload=true);
    ofVideoPlayer &operator[](const string& filename);
    map<string, ofVideoPlayer*> assets;
};

class ofxSoundAssets {
public:
    void add(string filename, bool preload=true);
    ofSoundPlayer &operator[](const string& filename);
    map<string, ofSoundPlayer*> assets;
};

class ofxFontAssets {
public:
    void add(string fontnamesize, bool preload=true);
    ofTrueTypeFont &operator[](const string& fontnamesize);
    map<string, ofTrueTypeFont*> assets;
};
