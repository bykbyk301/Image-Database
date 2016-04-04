#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    // load all the images
    ofLog() << "Gathering images...";
    ofDirectory dir;
    int nFiles = dir.listDir(ofToDataPath("/Volumes/MAC/database/drawings_of_god/imgs_s"));
    if(nFiles) {
        for(int i=0; i<dir.size(); i++) {
            if (i % 20 == 0)    ofLog() << " - loading image "<<i<<" / "<<dir.size();
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().load(filePath);
        }
    }
    
    // setup ofxCcv
    ccv.setup("image-net-2012.sqlite3");
    
    // encode all of the images with ofxCcv
    ofLog() << "Encoding images...";
    for (int i=0; i<images.size(); i++) {
        if (i % 20 == 0)    ofLog() << " - encoding image "<<i<<" / "<<images.size();
        vector<float> encoding = ccv.encode(images[i], ccv.numLayers()-1);
        encodings.push_back(encoding);
    }
    
    // run t-SNE and load image points to imagePoints
    ofLog() << "Run t-SNE on images";
    imagePoints = tsne.run(encodings, 2, 26, 0.5, true);
    
    // make the images the same size
    for (int i=0; i<images.size(); i++) {
        images[i].resize(100 * images[i].getWidth() / images[i].getHeight(), 100);
    }
    
    // setup gui
    gui.setup();
    gui.add(scale.set("scale", 4.0, 0.0, 10.0));
    gui.add(imageSize.set("imageSize", 1.0, 0.0, 2.0));
    
    for (int i=0; i<images.size(); i++) {
        float imgX = ofMap(imagePoints[i][0], 0, 1, 0, scale*ofGetWidth());
        float imgY = ofMap(imagePoints[i][1], 0, 1, 0, scale*ofGetHeight());
        string imgN = dir.getPath(i);
        csv.setString(i, 0, imgN);
        csv.setFloat(i, 1, imgX);
        csv.setFloat(i, 2, imgY);
        // save file
        csv.saveFile(ofToDataPath("data.csv"));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(255);
    
    ofPushMatrix();
    ofTranslate(-ofGetMouseX() * (scale - 0.5), -ofGetMouseY() * (scale - 0.5));
    for (int i=0; i<imagePoints.size(); i++) {
        float x = ofMap(imagePoints[i][0], 0, 1, 0, scale * ofGetWidth());
        float y = ofMap(imagePoints[i][1], 0, 1, 0, scale * ofGetHeight());
        images[i].draw(x, y, imageSize * images[i].getWidth(), imageSize * images[i].getHeight());
    }
    ofPopMatrix();
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
