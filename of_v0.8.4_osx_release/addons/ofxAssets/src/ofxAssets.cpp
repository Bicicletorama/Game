// ofxAssets
// openFrameworks addon for loading and caching image, video and font files
// Created by Rick Companje on 2/25/11.
// Adapted for fonts by Axel Roest, 2011-03-15

// TODO: Use templates instead

#include "ofxAssets.h"

//////////////////////////////////////////////////////////////

void ofxImageAssets::add(string filename, bool preload) {
    if (assets[filename]) return; //don't reload if already exists in map
    
    ofLog(OF_LOG_VERBOSE, "ofxImageAssets::add(\"" + filename + "\", preload=" + (preload ? "true" : "false") + ")");
    
    //in case of BAD_ACCESS error see http://forum.openframeworks.cc/index.php/topic,7910.0.html
    //in case of EXIF error by FreeImage use a new version of FreeImage.a: //http://sourceforge.net/projects/freeimage/forums/forum/36110/topic/5012811
    //  of use exiftool (win & osx): https://owl.phy.queensu.ca/~phil/exiftool/
    
    ofImage *asset = new ofImage();	
    assets[filename] = asset;
    
    if (preload) {
        //cout << "(pre)loading " << filename << endl;
        //bool success = 
        if (!asset->loadImage(filename)) {
            ofLogError() << "ofxImageAssets::add(\"" << filename << "\") failed";
            //if (!asset->loadImage(filename)) std::exit(1); //hmmm.... don't always exit    
        }
    }
}

ofImage& ofxImageAssets::operator[](const string& filename) {
    if (!assets[filename]) add(filename);
    return *assets[filename];
}

///////////////////////////////////////////////////////////////

void ofxVideoAssets::add(string filename, bool preload) {
    ofVideoPlayer *mov = new ofVideoPlayer();
    
    ofLog(OF_LOG_VERBOSE, "ofxVideoAssets::add(\"" + filename + "\", preload=" + (preload ? "true" : "false") + ")");
    
    if (!mov->loadMovie(filename)) {
        ofLog(OF_LOG_ERROR, "Movie not found: " + filename);
        std::exit(1);
    };
    
    assets[filename] = mov;
}

ofVideoPlayer& ofxVideoAssets::operator[](const string& filename) {
    if (!assets[filename]) add(filename);
    return *assets[filename];
}

///////////////////////////////////////////////////////////////

void ofxSoundAssets::add(string filename, bool preload) {
    ofSoundPlayer *snd = new ofSoundPlayer();
    
    ofLog(OF_LOG_VERBOSE, "ofxSoundAssets::add(\"" + filename + "\", preload=" + (preload ? "true" : "false") + ")");
    
    snd->loadSound(filename);
    
    assets[filename] = snd;
}

ofSoundPlayer& ofxSoundAssets::operator[](const string& filename) {
    if (!assets[filename]) add(filename);
    return *assets[filename];
}

////////////////////////////////////////////////////////////////

// fontname and size is combined into one string, because we need both of them as keys in the hash table
void ofxFontAssets::add(string fontnamesize, bool preload) {
    ofTrueTypeFont *fnt = new ofTrueTypeFont();
    
    ofLog(OF_LOG_VERBOSE, "ofxFontAssets::add(\"" + fontnamesize + "\", preload=" + (preload ? "true" : "false") + ")");
    
    istringstream iss(fontnamesize);                    // split up line in words
    string  fontname;
    int    fontsize;
    
    getline(iss, fontname, '_');
    iss >> fontsize;
    
    fnt->loadFont(fontname, fontsize);      // loadFont doesn't return status
    assets[fontnamesize] = fnt;
}

ofTrueTypeFont& ofxFontAssets::operator[](const string& fontnamesize) {
    if (!assets[fontnamesize]) add(fontnamesize);
    return *assets[fontnamesize];
}
