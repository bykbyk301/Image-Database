#pragma once

#include "ofMain.h"
#include "ofxCcv.h"
#include "ofxTSNE.h"
#include "ofxGui.h"
#include "ofxCsv.h"

using namespace wng;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxCcv ccv;
    ofxTSNE tsne;
    
    vector<ofImage> images;
    vector<vector<double> > imagePoints;
    vector<vector<float> > encodings;
    
    ofxPanel gui;
    ofParameter<float> scale;
    ofParameter<float> imageSize;
    
    ofxCsv csv;
    ofxCsv csvRecorder;
    
    int t;
};
